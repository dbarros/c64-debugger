#include "C64D_Version.h"
#include "NesDebugInterface.h"
#include "RES_ResourceManager.h"
#include "CByteBuffer.h"
#include "CSlrString.h"
#include "SYS_CommandLine.h"
#include "CGuiMain.h"
#include "SYS_KeyCodes.h"
#include "SND_SoundEngine.h"
#include "C64Tools.h"
#include "C64KeyMap.h"
#include "C64SettingsStorage.h"
#include "CViewC64.h"
#include "SND_Main.h"
#include "CSlrFileFromOS.h"
#include "CDebuggerEmulatorPlugin.h"

#include "NesDataAdapters.h"
#include "NesWrapper.h"
#include "CNesAudioChannel.h"

NesDebugInterface *debugInterfaceNes;

NesDebugInterface::NesDebugInterface(CViewC64 *viewC64) //, uint8 *memory)
: CDebugInterface(viewC64)
{
	LOGM("NesDebugInterface: NestopiaUE v%s init", NST_VERSION);
	
	debugInterfaceNes = this;
	
	CreateScreenData();
	
	audioChannel = NULL;
	
	dataAdapter = new NesDataAdapter(this);

	isDebugOn = true;
	
	NestopiaUE_Initialize();	
}

NesDebugInterface::~NesDebugInterface()
{
	debugInterfaceNes = NULL;
	if (screenImage)
	{
		delete screenImage;
	}
	
	if (dataAdapter)
	{
		delete dataAdapter;
	}
	
	if (audioChannel)
	{
		SND_RemoveChannel(audioChannel);
		delete audioChannel;
	}
	
//	Atari800_Exit_Internal(0);
//	
//	SYS_Sleep(100);
}

void NesDebugInterface::RestartEmulation()
{
//	NES_Exit_Internal(0);

	if (audioChannel)
	{
		SND_RemoveChannel(audioChannel);
		delete audioChannel;
	}
	
//	int ret = NES_Initialise(&sysArgc, sysArgv);
//	if (ret != 1)
//	{
//		SYS_FatalExit("NES restart failed, err=%d", ret);
//	}

}

int NesDebugInterface::GetEmulatorType()
{
	return EMULATOR_TYPE_NESTOPIA;
}

CSlrString *NesDebugInterface::GetEmulatorVersionString()
{
	return new CSlrString("NestopiaUE v" NST_VERSION);
}

CSlrString *NesDebugInterface::GetPlatformNameString()
{
	return new CSlrString("NES");
}

void NesDebugInterface::RunEmulationThread()
{
	LOGM("NesDebugInterface::RunEmulationThread");
	CDebugInterface::RunEmulationThread();

	this->isRunning = true;
	
#if defined(RUN_NES)
	NestopiaUE_Run();
	audioChannel->Stop();
#endif
	
}


void NesDebugInterface::DoFrame()
{
	CDebugInterface::DoFrame();
}

//	UBYTE MEMORY_mem[65536 + 2];

void NesDebugInterface::SetByte(uint16 addr, uint8 val)
{
	u8 *nesRam = nesd_get_ram();
	nesRam[addr] = val;
}

uint8 NesDebugInterface::GetByte(uint16 addr)
{
	u8 v;
	
//	u8 *nesRam = nesd_get_ram();
//	v = nesRam[addr];
	
//
//	v = nesd_peek_io(addr);
	
	LockRenderScreenMutex();
	LockMutex();
	v = nesd_peek_safe_io(addr);
	UnlockMutex();
	UnlockRenderScreenMutex();
	
	return v;
}

void NesDebugInterface::GetMemory(uint8 *buffer, int addrStart, int addrEnd)
{
//	u8 *nesRam = nesd_get_ram();
//
	int addr;
	u8 *bufPtr = buffer + addrStart;
	for (addr = addrStart; addr < addrEnd; addr++)
	{
		*bufPtr++ = GetByte(addr);
	}

}

int NesDebugInterface::GetCpuPC()
{
	return nesd_get_cpu_pc();
}

void NesDebugInterface::GetWholeMemoryMap(uint8 *buffer)
{
//	u8 *nesRam = nesd_get_ram();
//	for (int addr = 0; addr < 0x10000; addr++)
//	{
//		buffer[addr] = nesRam[addr];
//	}

	int addr;
	u8 *bufPtr = buffer;
	for (addr = 0; addr < 0x10000; addr++)
	{
		*bufPtr++ = GetByte(addr);
	}

}

void NesDebugInterface::GetWholeMemoryMapFromRam(uint8 *buffer)
{
	return GetWholeMemoryMap(buffer);
}

void NesDebugInterface::GetCpuRegs(u16 *PC,
				u8 *A,
				u8 *X,
				u8 *Y,
				u8 *P,						/* Processor Status Byte (Partial) */
				u8 *S,
				u8 *IRQ)
{
	return nesd_get_cpu_regs(PC, A, X, Y, P, S, IRQ);
}


//
int NesDebugInterface::GetScreenSizeX()
{
	return 256;
}

int NesDebugInterface::GetScreenSizeY()
{
	return 240;
}

//
void NesDebugInterface::SetDebugMode(uint8 debugMode)
{
	LOGD("NesDebugInterface::SetDebugMode: debugMode=%d", debugMode);
	nesd_debug_mode = debugMode;
	
	CDebugInterface::SetDebugMode(debugMode);
}

uint8 NesDebugInterface::GetDebugMode()
{
	this->debugMode = nesd_debug_mode;
	return debugMode;
}

// make jmp without resetting CPU depending on dataAdapter
void NesDebugInterface::MakeJmpNoReset(CSlrDataAdapter *dataAdapter, uint16 addr)
{
	this->LockMutex();
	
//	c64d_atari_set_cpu_pc(addr);
	
	this->UnlockMutex();
}

// make jmp and reset CPU
void NesDebugInterface::MakeJmpAndReset(uint16 addr)
{
	LOGTODO("NesDebugInterface::MakeJmpAndReset");
}

// keyboard & joystick mapper
void NesDebugInterface::KeyboardDown(uint32 mtKeyCode)
{
	LOGD("NesDebugInterface::KeyboardDown: mtKeyCode=%04x", mtKeyCode);

	for (std::list<CDebuggerEmulatorPlugin *>::iterator it = this->plugins.begin(); it != this->plugins.end(); it++)
	{
		CDebuggerEmulatorPlugin *plugin = *it;
		mtKeyCode = plugin->KeyDown(mtKeyCode);
		
		if (mtKeyCode == 0)
			return;
	}
}

void NesDebugInterface::KeyboardUp(uint32 mtKeyCode)
{
	LOGD("NesDebugInterface::KeyboardUp: mtKeyCode=%04x", mtKeyCode);
	
	for (std::list<CDebuggerEmulatorPlugin *>::iterator it = this->plugins.begin(); it != this->plugins.end(); it++)
	{
		CDebuggerEmulatorPlugin *plugin = *it;
		mtKeyCode = plugin->KeyUp(mtKeyCode);
		
		if (mtKeyCode == 0)
			return;
	}
	
}

void NesDebugInterface::JoystickDown(int port, uint32 axis)
{
	LOGD("NesDebugInterface::JoystickDown: %d %d", port, axis);
	
	nesd_joystick_down(port, axis);
}

void NesDebugInterface::JoystickUp(int port, uint32 axis)
{
	LOGD("NesDebugInterface::JoystickUp: %d %d", port, axis);

	nesd_joystick_up(port, axis);
}

void NesDebugInterface::Reset()
{
	LOGM("NesDebugInterface::Reset");
	
	nesd_reset();
}

void NesDebugInterface::HardReset()
{
	LOGM("NesDebugInterface::HardReset");

	nesd_reset();
}

bool NesDebugInterface::LoadExecutable(char *fullFilePath)
{
	LOGM("NesDebugInterface::LoadExecutable: %s", fullFilePath);
	return true;
}

bool NesDebugInterface::MountDisk(char *fullFilePath, int diskNo, bool readOnly)
{
	return true;
}

bool NesDebugInterface::InsertCartridge(char *fullFilePath)
{
	LOGM("NesDebugInterface::InsertCartridge: %s", fullFilePath);
	bool ret = nesd_insert_cartridge(fullFilePath);
	return ret;
}

bool NesDebugInterface::AttachTape(char *fullFilePath, bool readOnly)
{
	return true;
}

bool NesDebugInterface::LoadFullSnapshot(char *filePath)
{
	guiMain->LockMutex();
	this->LockMutex();
	
	bool ret = false;
	CSlrFileFromOS *file = new CSlrFileFromOS(filePath, SLR_FILE_MODE_READ);
	if (file->Exists())
	{
		CByteBuffer *byteBuffer = new CByteBuffer(file, false);
		if (nesd_restore_state(byteBuffer))
		{
			ret = true;
		}
		
		delete byteBuffer;
	}
	
	delete file;
	
	this->UnlockMutex();
	guiMain->UnlockMutex();
	return ret;
}

void NesDebugInterface::SaveFullSnapshot(char *filePath)
{
	LOGD("NesDebugInterface::SaveFullSnapshot: %s", filePath);
	guiMain->LockMutex();
	this->LockMutex();

	CByteBuffer *byteBuffer = nesd_store_state();
	byteBuffer->storeToFileNoHeader(filePath);
	
	delete byteBuffer;

	this->UnlockMutex();
	guiMain->UnlockMutex();
}


void NesDebugInterface::SetVideoSystem(u8 videoSystem)
{
	LOGD("NesDebugInterface::SetVideoSystem: %d", videoSystem);
}


void NesDebugInterface::SetMachineType(u8 machineType)
{
}

