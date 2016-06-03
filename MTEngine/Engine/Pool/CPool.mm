#include "CPool.h"
#include "DBG_Log.h"

// Create a new pool by defining the number of items to preallocate, and the
// size of each item.  For situations where you do not want the allocation
// pool increase in size, set bGrow to false.
CPool::CPool(const WORD nPoolSize, const size_t nItemSize, const bool bGrow) :
	m_pPrev(0),
	m_pNext(0),
	m_nPoolSize(nPoolSize),
	m_nItemSize(nItemSize),
	m_nTOS(0),
	m_bGrow(bGrow)
{
	//LOGD("CPool::CPool (1)");
	m_pPool = reinterpret_cast<BYTE*>(::operator new(m_nItemSize * m_nPoolSize));
	m_pFreeStack = new BYTE*[m_nPoolSize];
	m_pAvailable = m_pPool;
	m_pLast = m_pPool + m_nItemSize * m_nPoolSize;
	
	pthread_mutex_init(&mutex, NULL);
}

// Add a new pool to the end of the linked list, this can only be called from
// another CPool.
CPool::CPool(CPool* const pPrev) :
	m_pPrev(pPrev),
	m_pNext(0),
	m_nPoolSize(pPrev->m_nPoolSize),
	m_nItemSize(pPrev->m_nItemSize),
	m_nTOS(0),
	m_bGrow(true)
{
	//LOGD("CPool::CPool (2)");
	m_pPool = reinterpret_cast<BYTE*>(::operator new(m_nItemSize * m_nPoolSize));
	m_pFreeStack = new BYTE*[m_nPoolSize];
	m_pAvailable = m_pPool;
	m_pLast = m_pPool + m_nItemSize * m_nPoolSize;
	
	pthread_mutex_init(&mutex, NULL);
}

CPool::~CPool()
{
	//LOGD("~CPool()");
	delete m_pNext;
	delete m_pPool;
	delete [] m_pFreeStack;
	
	pthread_mutex_destroy(&mutex);
}

void* CPool::New(const size_t size)
{
	//LOGD("CPool::New: size=%d pool=%x", (u64)size, m_pPool);

	// If the item being requested is not the right size then use the generalised
	// new operator.  This will occur if the object is derived from the allocated
	// class.
	if (size != m_nItemSize)
	{
		LOGError("size=%d != m_nItemSize=%d", size, m_nItemSize);
		return ::operator new(size);
	}

	pthread_mutex_lock(&mutex);

	// If there are any holes in the free stack then fill them up.
	if (m_nTOS == 0)
	{
		// If there is any space left in this pool then use it, otherwise move
		// on to the next in the linked list.
		if (m_pAvailable < m_pLast)
		{
			BYTE*	pReturn = m_pAvailable;
			m_pAvailable += m_nItemSize;
			pthread_mutex_unlock(&mutex);
			return reinterpret_cast<void*>(pReturn);
		}
		else
		{
			// If there is another pool in the list then pass the request on to
			// it, otherwise try to create a new pool.
			if (m_pNext)
			{
				pthread_mutex_unlock(&mutex);
				return m_pNext->New(size);
			}
			else
			{
				if (m_bGrow)
				{
					m_pNext = new CPool(this);
					if (m_pNext)
					{
						pthread_mutex_unlock(&mutex);
						return m_pNext->New(size);
					}
				}
				// If we cannot allocate a new pool then return 0.
				pthread_mutex_unlock(&mutex);
				return 0;
			}
		}
	}
	else
	{
		pthread_mutex_unlock(&mutex);
		return reinterpret_cast<void*>(m_pFreeStack[--m_nTOS]);
	}
}

void CPool::Delete(void* pVoid)
{
	//LOGD("CPool::Delete pVoid=%x pool=%x", pVoid, m_pPool);
	
	pthread_mutex_lock(&mutex);
	if (pVoid)
	{
		BYTE*	pItem = reinterpret_cast<BYTE*>(pVoid);

		// Check if the item being deleted is within this pool's memory range.
		if (pItem < m_pPool || pItem >= m_pLast)
		{
			// If there is another pool in the list then try to delete from it,
			// otherwise call the generalised delete operator.
			if (m_pNext)
				m_pNext->Delete(pItem);
			else
				::operator delete(pVoid);
		}
		else
		{
			// Add a hole to the free stack.
			m_pFreeStack[m_nTOS++] = pItem;

			// If this pool is empty and it is the last in the linked list
			// then delete it and set the previous pool to the last.
			if (m_pPrev && !m_pNext &&
				static_cast<long>(m_nTOS * m_nItemSize) == m_pAvailable - m_pPool)
			{
				m_pPrev->m_pNext = 0;
				delete this;
			}
		}
	}
	
	pthread_mutex_unlock(&mutex);
}

// Reset all the pointers and indices, effectively deleting the allocated
// items without actually calling their destructors.  This function should
// be used with extreme caution since all sorts of horrible things can result
// from it's misuse.
void CPool::Purge()
{
	m_nTOS = 0;
	m_pAvailable = m_pPool;
	if (m_pNext)
		m_pNext->Purge();
}


