#ifndef _CDEBUGINTERFACE_H_
#define _CDEBUGINTERFACE_H_

#include "CDebuggerBreakpoints.h"
#include "CSlrDataAdapter.h"
#include "CByteBuffer.h"
#include "DebuggerDefs.h"
#include <map>
#include <list>

class CViewC64;
class CSlrMutex;
class CImageData;

class CDebuggerEmulatorPlugin;

// abstract class
class CDebugInterface
{
public:
	CDebugInterface(CViewC64 *viewC64);
	~CDebugInterface();
	CViewC64 *viewC64;
	
	virtual int GetEmulatorType();
	virtual CSlrString *GetEmulatorVersionString();
	virtual CSlrString *GetPlatformNameString();
	
	bool isRunning;
	bool isSelected;
	
	unsigned int emulationFrameCounter;

	virtual void RunEmulationThread();
	
	virtual void InitPlugins();
	
	// all cycles in frame finished, vsync
	virtual void DoVSync();

	// frame is painted on canvas and ready to be consumed
	virtual void DoFrame();
	
	virtual void ResetMainCpuCycleCounter();
	virtual unsigned int GetMainCpuCycleCounter();
	virtual void ResetEmulationFrameCounter();
	virtual unsigned int GetEmulationFrameNumber();
	
	virtual int GetScreenSizeX();
	virtual int GetScreenSizeY();
	
	CImageData *screenImage;
	virtual void CreateScreenData();
	int screenSupersampleFactor;
	virtual void SetSupersampleFactor(int factor);
	virtual CImageData *GetScreenImageData();
	
	// keyboard & joystick mapper
	virtual void KeyboardDown(uint32 mtKeyCode);
	virtual void KeyboardUp(uint32 mtKeyCode);
	
	virtual void JoystickDown(int port, uint32 axis);
	virtual void JoystickUp(int port, uint32 axis);
	
	// TODO: mouse
	virtual void MouseDown(float x, float y);
	virtual void MouseMove(float x, float y);
	virtual void MouseUp(float x, float y);
	
	// state
	virtual int GetCpuPC();
	
	virtual void GetWholeMemoryMap(uint8 *buffer);
	virtual void GetWholeMemoryMapFromRam(uint8 *buffer);
	
	//
	virtual void SetDebugMode(uint8 debugMode);
	virtual uint8 GetDebugMode();

	//
	virtual void Reset();
	virtual void HardReset();
	
	virtual bool LoadExecutable(char *fullFilePath);
	virtual bool MountDisk(char *fullFilePath, int diskNo, bool readOnly);

	//
	virtual bool LoadFullSnapshot(char *filePath);
	virtual void SaveFullSnapshot(char *filePath);

	//
	virtual bool GetSettingIsWarpSpeed();
	virtual void SetSettingIsWarpSpeed(bool isWarpSpeed);

	// cpu control

	// make jmp without resetting CPU depending on dataAdapter
	virtual void MakeJmpNoReset(CSlrDataAdapter *dataAdapter, uint16 addr);
	
	// make jmp and reset CPU
	virtual void MakeJmpAndReset(uint16 addr);
	

	// breakpoints
	bool isDebugOn;
	virtual void SetDebugOn(bool debugOn);

	bool breakOnPC;
	std::map<uint16, CAddrBreakpoint *> breakpointsPC;
	bool breakOnMemory;
	std::map<uint16, CMemoryBreakpoint *> breakpointsMemory;
	bool breakOnRaster;
	std::map<uint16, CAddrBreakpoint *> breakpointsRaster;
	
	virtual void ClearAddrBreakpoints(std::map<uint16, CAddrBreakpoint *> *breakpointsMap);
	virtual void AddAddrBreakpoint(std::map<uint16, CAddrBreakpoint *> *breakpointsMap, CAddrBreakpoint *breakpoint);
	virtual void RemoveAddrBreakpoint(std::map<uint16, CAddrBreakpoint *> *breakpointsMap, uint16 addr);
	virtual void ClearMemoryBreakpoints(std::map<uint16, CMemoryBreakpoint *> *breakpointsMap);
	virtual void ClearBreakpoints();

	int temporaryBreakpointPC;
	virtual int GetTemporaryBreakpointPC();
	virtual void SetTemporaryBreakpointPC(int address);

	virtual CSlrDataAdapter *GetDataAdapter();

	//
	
	virtual void Shutdown();

	//
	std::list<CDebuggerEmulatorPlugin *> plugins;
	void RegisterPlugin(CDebuggerEmulatorPlugin *plugin);
	void RemovePlugin(CDebuggerEmulatorPlugin *plugin);
	
	//
	CSlrMutex *breakpointsMutex;
	virtual void LockMutex();
	virtual void UnlockMutex();
	
	CSlrMutex *renderScreenMutex;
	virtual void LockRenderScreenMutex();
	virtual void UnlockRenderScreenMutex();
	
	CSlrMutex *ioMutex;
	virtual void LockIoMutex();
	virtual void UnlockIoMutex();
	
protected:
	volatile int debugMode;

};


#endif
