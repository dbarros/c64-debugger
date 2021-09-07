#ifndef _NESPPUDATAADAPTER_H_
#define _NESPPUDATAADAPTER_H_

#include "CSlrDataAdapter.h"

class NesDebugInterface;

class NesPpuDataAdapter : public CSlrDataAdapter
{
public:
	NesPpuDataAdapter(NesDebugInterface *debugInterface);
	NesDebugInterface *debugInterface;
	
	virtual int AdapterGetDataLength();
	
	virtual void AdapterReadByte(int pointer, uint8 *value);
	virtual void AdapterWriteByte(int pointer, uint8 value);
	virtual void AdapterReadByte(int pointer, uint8 *value, bool *isAvailable);
	virtual void AdapterWriteByte(int pointer, uint8 value, bool *isAvailable);
	virtual void AdapterReadBlockDirect(uint8 *buffer, int pointerStart, int pointerEnd);
};



#endif

