#include "C64SharedMemory.h"
#include "SYS_CFileSystem.h"
#include "SYS_SharedMemory.h"
#include "CViewC64.h"
#include "C64CommandLine.h"

// 16kB should be enough for everybody
#define C64D_SHARED_MEMORY_SIZE		1024*16
#define C64D_SHARED_MEMORY_KEY		12666

bool c64dSharedMemoryInit = false;

void C64DebuggerInitSharedMemory()
{
	LOGD("C64DebuggerInitSharedMemory");
	
	if (c64dSharedMemoryInit == false)
	{
		SYS_InitSharedMemory(C64D_SHARED_MEMORY_KEY, C64D_SHARED_MEMORY_SIZE);
		SYS_InitSharedMemorySignalHandlers();
		
		c64dSharedMemoryInit = true;
	}
}

int C64DebuggerSendConfiguration(CByteBuffer *byteBuffer)
{
	int result = SYS_SendConfigurationToOtherAppInstance(byteBuffer);
	
	LOGD("C64DebuggerSendConfiguration: pid=%d", result);
	return result;
}

void C64DebuggerReceivedConfiguration(CByteBuffer *byteBuffer)
{
	LOGD("C64DebuggerReceivedConfiguration");
	
	C64DebuggerPerformNewConfigurationTasks(byteBuffer);
}