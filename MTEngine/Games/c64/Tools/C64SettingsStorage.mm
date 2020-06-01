#include "C64SettingsStorage.h"
#include "CViewMemoryMap.h"
#include "CSlrFileFromOS.h"
#include "CByteBuffer.h"
#include "CViewC64.h"
#include "CGuiMain.h"
#include "CGuiTheme.h"
#include "CColorsTheme.h"
#include "CViewMonitorConsole.h"
#include "SND_SoundEngine.h"
#include "CViewC64Screen.h"
#include "CViewC64VicDisplay.h"
#include "CViewC64VicControl.h"
#include "CViewC64StateSID.h"
#include "CViewVicEditor.h"
#include "CSnapshotsManager.h"
#include "C64Palette.h"
#include "CViewAtariScreen.h"
#include "CViewNesScreen.h"

#include "C64DebugInterface.h"
#include "AtariDebugInterface.h"
#include "NesDebugInterface.h"

#include "DebuggerDefs.h"

// this is used for temporarily allow quick switch for loading settings from other path than default
//#define DEBUG_SETTINGS_FILE_PATH	"/Users/mars/Downloads/settings.dat.old.bin"


extern "C" {
#include "sid-resources.h"
}

#define C64DEBUGGER_SETTINGS_FILE_VERSION 0x0002

///
#define C64DEBUGGER_SETTING_BLOCK	0
#define C64DEBUGGER_SETTING_STRING	1
#define C64DEBUGGER_SETTING_U8		2
#define C64DEBUGGER_SETTING_BOOL	3
#define C64DEBUGGER_SETTING_CUSTOM	4
#define C64DEBUGGER_SETTING_U16		5
#define C64DEBUGGER_SETTING_FLOAT	6
#define C64DEBUGGER_SETTING_I32		7

/// blocks
#define C64DEBUGGER_BLOCK_EOF			0

/// settings
int c64SettingsDefaultScreenLayoutId = -1; //SCREEN_LAYOUT_MONITOR_CONSOLE; //SCREEN_LAYOUT_C64_DEBUGGER;
//SCREEN_LAYOUT_C64_DEBUGGER);
//SCREEN_LAYOUT_C64_1541_MEMORY_MAP; //SCREEN_LAYOUT_C64_ONLY //
//SCREEN_LAYOUT_SHOW_STATES; //SCREEN_LAYOUT_C64_DATA_DUMP
//SCREEN_LAYOUT_C64_1541_DEBUGGER

bool c64SettingsIsInVicEditor = false;

bool c64SettingsSkipConfig = false;
bool c64SettingsPassConfigToRunningInstance = false;

int c64SettingsScreenSupersampleFactor = 1;

bool c64SettingsUsePipeIntegration = true;

uint8 c64SettingsJoystickPort = 0;
bool c64SettingsUseKeyboardAsJoystick = false;

bool c64SettingsWindowAlwaysOnTop = false;

bool c64SettingsRenderDisassembleExecuteAware = true;

uint8 c64SettingsMemoryValuesStyle = MEMORY_MAP_VALUES_STYLE_RGB;
uint8 c64SettingsMemoryMarkersStyle = MEMORY_MAP_MARKER_STYLE_DEFAULT;
bool c64SettingsUseMultiTouchInMemoryMap = false;
bool c64SettingsMemoryMapInvertControl = false;
uint8 c64SettingsMemoryMapRefreshRate = 2;
int c64SettingsMemoryMapFadeSpeed = 100;		// percentage

uint8 c64SettingsC64Model = 0;
int c64SettingsEmulationMaximumSpeed = 100;		// percentage
bool c64SettingsFastBootKernalPatch = false;
bool c64SettingsEmulateVSPBug = false;

// TODO: refactor SID to Sid for better readability

uint8 c64SettingsSIDEngineModel = 0;	// 4=8580 FastSID
uint8 c64SettingsRESIDSamplingMethod = SID_RESID_SAMPLING_RESAMPLING;
bool c64SettingsRESIDEmulateFilters = true;
uint32 c64SettingsRESIDPassBand = 90;
uint32 c64SettingsRESIDFilterBias = 500;

uint8 c64SettingsSIDStereo = 0;					// "SidStereo" 0=none, 1=stereo, 2=triple
uint16 c64SettingsSIDStereoAddress = 0xD420;	// "SidStereoAddressStart"
uint16 c64SettingsSIDTripleAddress = 0xDF00;	// "SidTripleAddressStart"

extern u8 c64SettingsC64SidImportMode = SID_IMPORT_MODE_PSID64;

int c64SettingsDatasetteSpeedTuning = 0;
int c64SettingsDatasetteZeroGapDelay = 20000;
int c64SettingsDatasetteTapeWobble = 10;
bool c64SettingsDatasetteResetWithCPU = false;

//
bool c64SettingsReuEnabled = false;
int c64SettingsReuSize = 16384;

bool c64SettingsMuteSIDOnPause = false;

int c64SettingsAudioVolume = 100;				// percentage
bool c64SettingsRunSIDEmulation = true;
uint8 c64SettingsMuteSIDMode = MUTE_SID_MODE_ZERO_VOLUME;

uint16 c64SettingsVicPalette = 0;
bool c64SettingsC64ProfilerDoVicProfile = false;

int c64SettingsWaitOnStartup = 0; //500;

// snapshots recorder
bool c64SettingsTimelineIsActive = true;

bool c64SettingsSnapshotsRecordIsActive = true;
// snapshots interval
int c64SettingsSnapshotsIntervalNumFrames = 10;
// max number of snapshots. TODO: get fps from debuginterface. 50 frames per second * 60 seconds = 3 mins
int c64SettingsSnapshotsLimit = (50 * 60 * 3) / 10;

CSlrString *c64SettingsPathToD64 = NULL;
CSlrString *c64SettingsDefaultD64Folder = NULL;

CSlrString *c64SettingsPathToPRG = NULL;
CSlrString *c64SettingsDefaultPRGFolder = NULL;

CSlrString *c64SettingsPathToCartridge = NULL;
CSlrString *c64SettingsDefaultCartridgeFolder = NULL;

CSlrString *c64SettingsPathToViceSnapshot = NULL;
CSlrString *c64SettingsPathToAtariSnapshot = NULL;
CSlrString *c64SettingsDefaultSnapshotsFolder = NULL;

CSlrString *c64SettingsPathToTAP = NULL;
CSlrString *c64SettingsDefaultTAPFolder = NULL;

CSlrString *c64SettingsPathToReu = NULL;
CSlrString *c64SettingsDefaultReuFolder = NULL;

CSlrString *c64SettingsDefaultVicEditorFolder = NULL;

bool c64SettingsAtariPokeyStereo = false;

CSlrString *c64SettingsPathToXEX = NULL;
CSlrString *c64SettingsDefaultXEXFolder = NULL;

CSlrString *c64SettingsPathToCAS = NULL;
CSlrString *c64SettingsDefaultCASFolder = NULL;

CSlrString *c64SettingsPathToAtariCartridge = NULL;
CSlrString *c64SettingsDefaultAtariCartridgeFolder = NULL;

CSlrString *c64SettingsPathToATR = NULL;
CSlrString *c64SettingsDefaultATRFolder = NULL;

CSlrString *c64SettingsPathToAtariROMs = NULL;

CSlrString *c64SettingsPathToNES = NULL;
CSlrString *c64SettingsDefaultNESFolder = NULL;

CSlrString *c64SettingsDefaultMemoryDumpFolder = NULL;

CSlrString *c64SettingsPathToC64MemoryMapFile = NULL;
CSlrString *c64SettingsPathToAtari800MemoryMapFile = NULL;

CSlrString *c64SettingsPathToSymbols = NULL;
CSlrString *c64SettingsPathToBreakpoints = NULL;
CSlrString *c64SettingsPathToWatches = NULL;
CSlrString *c64SettingsPathToDebugInfo = NULL;

bool c64SettingsUseNativeEmulatorMonitor = false;

CSlrString *c64SettingsPathToJukeboxPlaylist = NULL;

// priority
bool c64SettingsIsProcessPriorityBoostDisabled = true;
u8 c64SettingsProcessPriority = MT_PRIORITY_ABOVE_NORMAL;

// profiler
CSlrString *c64SettingsC64ProfilerFileOutputPath = NULL;

CSlrString *c64SettingsAudioOutDevice = NULL;

float c64SettingsScreenGridLinesAlpha = 0.3f;
uint8 c64SettingsScreenGridLinesColorScheme = 0;	// 0=red, 1=green, 2=blue, 3=black, 4=dark gray 5=light gray 6=white 7=yellow
float c64SettingsScreenRasterViewfinderScale = 1.5f; //5.0f; //1.5f;

float c64SettingsScreenRasterCrossLinesAlpha = 0.5f;
uint8 c64SettingsScreenRasterCrossLinesColorScheme = 5;	// 0=red, 1=green, 2=blue, 3=black, 4=dark gray 5=light gray 6=white 7=yellow
float c64SettingsScreenRasterCrossAlpha = 0.85f;
uint8 c64SettingsScreenRasterCrossInteriorColorScheme = 6;	// 0=red, 1=green, 2=blue, 3=black, 4=dark gray 5=light gray 6=white 7=yellow
uint8 c64SettingsScreenRasterCrossExteriorColorScheme = 0;	// 0=red, 1=green, 2=blue, 3=black, 4=dark gray 5=light gray 6=white 7=yellow
uint8 c64SettingsScreenRasterCrossTipColorScheme = 3;	// 0=red, 1=green, 2=blue, 3=black, 4=dark gray 5=light gray 6=white 7=yellow

uint8 c64SettingsVicStateRecordingMode = C64D_VICII_RECORD_MODE_EVERY_CYCLE;
bool c64SettingsRenderScreenNearest = true;

int c64SettingsJmpOnStartupAddr = -1;

u8 c64SettingsVicDisplayBorderType = VIC_DISPLAY_SHOW_BORDER_FULL;

bool c64SettingsAutoJmp = false;
bool c64SettingsAutoJmpAlwaysToLoadedPRGAddress = false;	// will jump to loaded address when PRG is loaded from menu
bool c64SettingsAutoJmpFromInsertedDiskFirstPrg = false;	// will load first PRG from attached disk
u8 c64SettingsAutoJmpDoReset = MACHINE_RESET_NONE;
int c64SettingsAutoJmpWaitAfterReset = 1300;				// this is to let c64 drive finish reset

bool c64SettingsForceUnpause = false;						// unpause debugger on jmp if code is stopped

bool c64SettingsResetCountersOnAutoRun = true;

bool c64SettingsRunSIDWhenInWarp = true;

float c64SettingsPaintGridCharactersColorR = 0.7f;
float c64SettingsPaintGridCharactersColorG = 0.7f;
float c64SettingsPaintGridCharactersColorB = 0.7f;
float c64SettingsPaintGridCharactersColorA = 1.0f;

float c64SettingsPaintGridPixelsColorR = 0.5f;
float c64SettingsPaintGridPixelsColorG = 0.5f;
float c64SettingsPaintGridPixelsColorB = 0.5f;
float c64SettingsPaintGridPixelsColorA = 0.3f;

float c64SettingsFocusBorderLineWidth = 0.7f;

int c64SettingsDisassemblyBackgroundColor = C64D_COLOR_BLACK;
int c64SettingsDisassemblyExecuteColor = C64D_COLOR_WHITE;
int c64SettingsDisassemblyNonExecuteColor = C64D_COLOR_LIGHT_GRAY;

int c64SettingsMenusColorTheme = 0;

float c64SettingsPaintGridShowZoomLevel = 5.0;
float c64SettingsPaintGridShowValuesZoomLevel = 26.0;

bool c64SettingsVicEditorForceReplaceColor = false;
u8 c64SettingsVicEditorDefaultBackgroundColor = 0;

bool c64SettingsUseSystemFileDialogs = true;
bool c64SettingsUseOnlyFirstCPU = true;

int c64SettingsDoubleClickMS = 600;

// automatically load VICE labels if filename matched PRG (*.labels)
bool c64SettingsLoadViceLabels = true;

// automatically load watches if filename matched PRG (*.watch)
bool c64SettingsLoadWatches = true;

// automatically load debug info if filename matched PRG (*.dbg)
bool c64SettingsLoadDebugInfo = true;

// atari
u8 c64SettingsAtariVideoSystem = ATARI_VIDEO_SYSTEM_PAL;
u8 c64SettingsAtariMachineType = 0;
u8 c64SettingsAtariRamSizeOption = 0;

void storeSettingBlock(CByteBuffer *byteBuffer, u8 value)
{
	byteBuffer->PutU8(C64DEBUGGER_SETTING_BLOCK);
	byteBuffer->PutU8(value);
}

void storeSettingU8(CByteBuffer *byteBuffer, char *name, u8 value)
{
	byteBuffer->PutU8(C64DEBUGGER_SETTING_U8);
	byteBuffer->PutString(name);
	byteBuffer->PutU8(value);
}

void storeSettingU16(CByteBuffer *byteBuffer, char *name, u16 value)
{
	byteBuffer->PutU8(C64DEBUGGER_SETTING_U16);
	byteBuffer->PutString(name);
	byteBuffer->PutU16(value);
}

void storeSettingI32(CByteBuffer *byteBuffer, char *name, i32 value)
{
	byteBuffer->PutU8(C64DEBUGGER_SETTING_I32);
	byteBuffer->PutString(name);
	byteBuffer->PutI32(value);
}

void storeSettingFloat(CByteBuffer *byteBuffer, char *name, float value)
{
	byteBuffer->PutU8(C64DEBUGGER_SETTING_FLOAT);
	byteBuffer->PutString(name);
	byteBuffer->PutFloat(value);
}

void storeSettingBool(CByteBuffer *byteBuffer, char *name, bool value)
{
	byteBuffer->PutU8(C64DEBUGGER_SETTING_BOOL);
	byteBuffer->PutString(name);
	byteBuffer->PutBool(value);
}

void storeSettingString(CByteBuffer *byteBuffer, char *name, CSlrString *value)
{
	byteBuffer->PutU8(C64DEBUGGER_SETTING_STRING);
	byteBuffer->PutString(name);
	byteBuffer->PutSlrString(value);
}

void storeSettingCustom(CByteBuffer *byteBuffer, char *name)
{
	byteBuffer->PutU8(C64DEBUGGER_SETTING_CUSTOM);
	byteBuffer->PutString(name);
}

void C64DebuggerClearSettings()
{
	CByteBuffer *byteBuffer = new CByteBuffer();
	byteBuffer->PutU16(C64DEBUGGER_SETTINGS_FILE_VERSION);

	storeSettingBlock(byteBuffer, C64DEBUGGER_BLOCK_EOF);
	
#if !defined(DEBUG_SETTINGS_FILE_PATH)
	CSlrString *fileName = new CSlrString(C64D_SETTINGS_FILE_PATH);
	byteBuffer->storeToSettings(fileName);
	delete fileName;
#else
	LOGWarning("C64DebuggerClearSettings: DEBUG_SETTINGS_FILE_PATH is defined as '%s'. NOT CLEARING SETTINGS.", DEBUG_SETTINGS_FILE_PATH);
#endif
	
	delete byteBuffer;
}

void C64DebuggerStoreSettings()
{
	CByteBuffer *byteBuffer = new CByteBuffer();
	byteBuffer->PutU16(C64DEBUGGER_SETTINGS_FILE_VERSION);
	
	storeSettingBlock(byteBuffer, C64DEBUGGER_BLOCK_PRELAUNCH);
	storeSettingString(byteBuffer, "FolderD64", c64SettingsDefaultD64Folder);
	storeSettingString(byteBuffer, "FolderPRG", c64SettingsDefaultPRGFolder);
	storeSettingString(byteBuffer, "FolderCRT", c64SettingsDefaultCartridgeFolder);
	storeSettingString(byteBuffer, "FolderTAP", c64SettingsDefaultTAPFolder);
	storeSettingString(byteBuffer, "FolderREU", c64SettingsDefaultReuFolder);
	storeSettingString(byteBuffer, "FolderVicEditor", c64SettingsDefaultVicEditorFolder);
	storeSettingString(byteBuffer, "FolderSnaps", c64SettingsDefaultSnapshotsFolder);
	storeSettingString(byteBuffer, "FolderMemDumps", c64SettingsDefaultMemoryDumpFolder);
	storeSettingString(byteBuffer, "PathD64", c64SettingsPathToD64);
	storeSettingString(byteBuffer, "PathPRG", c64SettingsPathToPRG);
	storeSettingString(byteBuffer, "PathCRT", c64SettingsPathToCartridge);
	storeSettingString(byteBuffer, "PathTAP", c64SettingsPathToTAP);
	storeSettingString(byteBuffer, "PathREU", c64SettingsPathToReu);

	storeSettingString(byteBuffer, "FolderAtariROMs", c64SettingsPathToAtariROMs);
	storeSettingString(byteBuffer, "FolderATR", c64SettingsDefaultATRFolder);
	storeSettingString(byteBuffer, "PathATR", c64SettingsPathToATR);
	storeSettingString(byteBuffer, "FolderXEX", c64SettingsDefaultXEXFolder);
	storeSettingString(byteBuffer, "PathXEX", c64SettingsPathToXEX);
	storeSettingString(byteBuffer, "FolderCAS", c64SettingsDefaultCASFolder);
	storeSettingString(byteBuffer, "PathCAS", c64SettingsPathToCAS);
	storeSettingString(byteBuffer, "FolderAtariCart", c64SettingsDefaultAtariCartridgeFolder);
	storeSettingString(byteBuffer, "PathAtariCart", c64SettingsPathToAtariCartridge);
	storeSettingString(byteBuffer, "FolderNES", c64SettingsDefaultNESFolder);
	storeSettingString(byteBuffer, "PathNES", c64SettingsPathToNES);

	storeSettingBool(byteBuffer, "UsePipeIntegration", c64SettingsUsePipeIntegration);
	
	storeSettingBool(byteBuffer, "AutoJmp", c64SettingsAutoJmp);
	storeSettingBool(byteBuffer, "AutoJmpAlwaysToLoadedPRGAddress", c64SettingsAutoJmpAlwaysToLoadedPRGAddress);
	storeSettingBool(byteBuffer, "AutoJmpFromInsertedDiskFirstPrg", c64SettingsAutoJmpFromInsertedDiskFirstPrg);

	storeSettingString(byteBuffer, "PathMemMapFile", c64SettingsPathToC64MemoryMapFile);

	storeSettingString(byteBuffer, "AudioOutDevice", c64SettingsAudioOutDevice);
	
	storeSettingBool(byteBuffer, "FastBootPatch", c64SettingsFastBootKernalPatch);
	
	storeSettingU8(byteBuffer, "ScreenLayoutId", c64SettingsDefaultScreenLayoutId);
	storeSettingBool(byteBuffer, "IsInVicEditor", c64SettingsIsInVicEditor);
	
	storeSettingBool(byteBuffer, "DisassembleExecuteAware", c64SettingsRenderDisassembleExecuteAware);
	
	storeSettingBool(byteBuffer, "WindowAlwaysOnTop", c64SettingsWindowAlwaysOnTop);

	storeSettingU16(byteBuffer, "ScreenSupersampleFactor", c64SettingsScreenSupersampleFactor);

	storeSettingBool(byteBuffer, "DisableProcessPriorityBoost", c64SettingsIsProcessPriorityBoostDisabled);
	storeSettingU8(byteBuffer, "ProcessPriority", c64SettingsProcessPriority);

	storeSettingBool(byteBuffer, "UseNativeEmulatorMonitor", c64SettingsUseNativeEmulatorMonitor);
	
#if !defined(WIN32)
	storeSettingBool(byteBuffer, "UseSystemDialogs", c64SettingsUseSystemFileDialogs);
#endif

#if defined(WIN32)
	storeSettingBool(byteBuffer, "UseOnlyFirstCPU", c64SettingsUseOnlyFirstCPU);
#endif

#if defined(RUN_COMMODORE64)
	storeSettingU8(byteBuffer, "C64Model", c64SettingsC64Model);
	storeSettingString(byteBuffer, "C64ProfilerOutputPath", c64SettingsC64ProfilerFileOutputPath);
	storeSettingBool(byteBuffer, "C64ProfilerDoVic", c64SettingsC64ProfilerDoVicProfile);
#endif
	
	storeSettingBlock(byteBuffer, C64DEBUGGER_BLOCK_POSTLAUNCH);
	storeSettingU8(byteBuffer, "JoystickPort", c64SettingsJoystickPort);
	storeSettingBool(byteBuffer, "UseKeyboardAsJoystick", c64SettingsUseKeyboardAsJoystick);
	storeSettingU8(byteBuffer, "MemoryValuesStyle", c64SettingsMemoryValuesStyle);
	storeSettingU8(byteBuffer, "MemoryMarkersStyle", c64SettingsMemoryMarkersStyle);

	storeSettingU16(byteBuffer, "AudioVolume", c64SettingsAudioVolume);

#if defined(RUN_COMMODORE64)
	storeSettingU16(byteBuffer, "SIDStereoAddress", c64SettingsSIDStereoAddress);
	storeSettingU16(byteBuffer, "SIDTripleAddress", c64SettingsSIDTripleAddress);
	storeSettingU8(byteBuffer, "SIDStereo", c64SettingsSIDStereo);

	storeSettingU8(byteBuffer, "RESIDSamplingMethod", c64SettingsRESIDSamplingMethod);
	storeSettingBool(byteBuffer, "RESIDEmulateFilters", c64SettingsRESIDEmulateFilters);
	storeSettingI32(byteBuffer, "RESIDPassBand", c64SettingsRESIDPassBand);
	storeSettingI32(byteBuffer, "RESIDFilterBias", c64SettingsRESIDFilterBias);
	
	storeSettingU8(byteBuffer, "SIDEngineModel", c64SettingsSIDEngineModel);

	storeSettingBool(byteBuffer, "MuteSIDOnPause", c64SettingsMuteSIDOnPause);
	storeSettingBool(byteBuffer, "RunSIDWhenWarp", c64SettingsRunSIDWhenInWarp);

	storeSettingBool(byteBuffer, "RunSIDEmulation", c64SettingsRunSIDEmulation);
	storeSettingU8(byteBuffer, "MuteSIDMode", c64SettingsMuteSIDMode);

	storeSettingU8(byteBuffer, "SIDImportMode", c64SettingsC64SidImportMode);
	
	
	storeSettingU8(byteBuffer, "VicStateRecording", c64SettingsVicStateRecordingMode);
	storeSettingU16(byteBuffer, "VicPalette", c64SettingsVicPalette);
	storeSettingBool(byteBuffer, "RenderScreenNearest", c64SettingsRenderScreenNearest);
	
	storeSettingU16(byteBuffer, "EmulationMaximumSpeed", c64SettingsEmulationMaximumSpeed);
	
	storeSettingBool(byteBuffer, "EmulateVSPBug", c64SettingsEmulateVSPBug);
	
	storeSettingU8(byteBuffer, "VicDisplayBorder", c64SettingsVicDisplayBorderType);
	
	storeSettingBool (byteBuffer, "VicEditorForceReplaceColor", c64SettingsVicEditorForceReplaceColor);
	storeSettingU8(byteBuffer, "VicEditorDefaultBackgroundColor", c64SettingsVicEditorDefaultBackgroundColor);
	
	storeSettingI32(byteBuffer, "DatasetteSpeedTuning", c64SettingsDatasetteSpeedTuning);
	storeSettingI32(byteBuffer, "DatasetteZeroGapDelay", c64SettingsDatasetteZeroGapDelay);
	storeSettingI32(byteBuffer, "DatasetteTapeWobble", c64SettingsDatasetteTapeWobble);
	storeSettingBool(byteBuffer, "DatasetteResetWithCPU", c64SettingsDatasetteResetWithCPU);
	
	storeSettingBool(byteBuffer, "ReuEnabled", c64SettingsReuEnabled);
	storeSettingI32(byteBuffer, "ReuSize", c64SettingsReuSize);
#endif
	
#if defined(RUN_ATARI)
	storeSettingU8(byteBuffer, "AtariVideoSystem", c64SettingsAtariVideoSystem);
	storeSettingU8(byteBuffer, "AtariMachineType", c64SettingsAtariMachineType);
	storeSettingU8(byteBuffer, "AtariRamSizeOption", c64SettingsAtariRamSizeOption);
	storeSettingBool(byteBuffer, "AtariPokeyStereo", c64SettingsAtariPokeyStereo);
#endif

	storeSettingBool(byteBuffer, "MemMapMultiTouch", c64SettingsUseMultiTouchInMemoryMap);
	storeSettingBool(byteBuffer, "MemMapInvert", c64SettingsMemoryMapInvertControl);
	storeSettingU8(byteBuffer, "MemMapRefresh", c64SettingsMemoryMapRefreshRate);
	storeSettingU16(byteBuffer, "MemMapFadeSpeed", c64SettingsMemoryMapFadeSpeed);

	storeSettingFloat(byteBuffer, "GridLinesAlpha", c64SettingsScreenGridLinesAlpha);
	storeSettingU8(byteBuffer, "GridLinesColor", c64SettingsScreenGridLinesColorScheme);
	storeSettingFloat(byteBuffer, "ViewfinderScale", c64SettingsScreenRasterViewfinderScale);
	storeSettingFloat(byteBuffer, "CrossLinesAlpha", c64SettingsScreenRasterCrossLinesAlpha);
	storeSettingU8(byteBuffer, "CrossLinesColor", c64SettingsScreenRasterCrossLinesColorScheme);
	storeSettingFloat(byteBuffer, "CrossAlpha", c64SettingsScreenRasterCrossAlpha);
	storeSettingU8(byteBuffer, "CrossInteriorColor", c64SettingsScreenRasterCrossInteriorColorScheme);
	storeSettingU8(byteBuffer, "CrossExteriorColor", c64SettingsScreenRasterCrossExteriorColorScheme);
	storeSettingU8(byteBuffer, "CrossTipColor", c64SettingsScreenRasterCrossTipColorScheme);
	
	storeSettingFloat(byteBuffer, "FocusBorderWidth", c64SettingsFocusBorderLineWidth);

	//
	storeSettingU8(byteBuffer, "DisassemblyBackgroundColor", c64SettingsDisassemblyBackgroundColor);
	storeSettingU8(byteBuffer, "DisassemblyExecuteColor", c64SettingsDisassemblyExecuteColor);
	storeSettingU8(byteBuffer, "DisassemblyNonExecuteColor", c64SettingsDisassemblyNonExecuteColor);
	storeSettingU8(byteBuffer, "MenusColorTheme", c64SettingsMenusColorTheme);
	
	//
	storeSettingU8(byteBuffer, "AutoJmpDoReset", c64SettingsAutoJmpDoReset);
	storeSettingI32(byteBuffer, "AutoJmpWaitAfterReset", c64SettingsAutoJmpWaitAfterReset);
	
	storeSettingFloat (byteBuffer, "PaintGridCharactersColorR", c64SettingsPaintGridCharactersColorR);
	storeSettingFloat (byteBuffer, "PaintGridCharactersColorG", c64SettingsPaintGridCharactersColorG);
	storeSettingFloat (byteBuffer, "PaintGridCharactersColorB", c64SettingsPaintGridCharactersColorB);
	storeSettingFloat (byteBuffer, "PaintGridCharactersColorA", c64SettingsPaintGridCharactersColorA);
	
	storeSettingFloat (byteBuffer, "PaintGridPixelsColorR", c64SettingsPaintGridPixelsColorR);
	storeSettingFloat (byteBuffer, "PaintGridPixelsColorG", c64SettingsPaintGridPixelsColorG);
	storeSettingFloat (byteBuffer, "PaintGridPixelsColorB", c64SettingsPaintGridPixelsColorB);
	storeSettingFloat (byteBuffer, "PaintGridPixelsColorA", c64SettingsPaintGridPixelsColorA);
	
	storeSettingFloat (byteBuffer, "PaintGridShowZoomLevel", c64SettingsPaintGridShowZoomLevel);
	
	storeSettingBool(byteBuffer, "SnapshotsManagerIsActive", c64SettingsSnapshotsRecordIsActive);
	storeSettingI32(byteBuffer, "SnapshotsManagerStoreInterval", c64SettingsSnapshotsIntervalNumFrames);
	storeSettingI32(byteBuffer, "SnapshotsManagerLimit", c64SettingsSnapshotsLimit);

	storeSettingBool(byteBuffer, "TimelineIsActive", c64SettingsTimelineIsActive);

	storeSettingBlock(byteBuffer, C64DEBUGGER_BLOCK_EOF);

	
#if !defined(DEBUG_SETTINGS_FILE_PATH)
	LOGD("C64D_SETTINGS_FILE_PATH is set to=%s", C64D_SETTINGS_FILE_PATH);
	CSlrString *fileName = new CSlrString(C64D_SETTINGS_FILE_PATH);
	fileName->DebugPrint("fileName=");
	byteBuffer->storeToSettings(fileName);
	delete fileName;
#else
	LOGWarning("DEBUG_SETTINGS_FILE_PATH is defined as '%s'. NOT STORING SETTINGS.", DEBUG_SETTINGS_FILE_PATH);
#endif
	
	delete byteBuffer;
}

void C64DebuggerRestoreSettings(uint8 settingsBlockType)
{
	LOGD("C64DebuggerRestoreSettings: settingsBlockType=%d", settingsBlockType);
	
	if (c64SettingsSkipConfig)
	{
		LOGD("... skipping loading config and clearing settings");
		C64DebuggerClearSettings();
		return;
	}
	
	CByteBuffer *byteBuffer = new CByteBuffer();

#if !defined(DEBUG_SETTINGS_FILE_PATH)
	CSlrString *fileName = new CSlrString(C64D_SETTINGS_FILE_PATH);
	byteBuffer->loadFromSettings(fileName);
	delete fileName;
#else
	LOGWarning("Restoring settings from DEBUG_SETTINGS_FILE_PATH defined as '%s'", DEBUG_SETTINGS_FILE_PATH);

	CSlrString *fileName = new CSlrString(DEBUG_SETTINGS_FILE_PATH);
	byteBuffer->readFromFile(fileName);
	delete fileName;
#endif

	
	if (byteBuffer->length == 0)
	{
		LOGD("... no stored settings found");
		delete byteBuffer;
		return;
	}
	
	u16 version = byteBuffer->GetU16();
	if (version > C64DEBUGGER_SETTINGS_FILE_VERSION)
	{
		LOGError("C64DebuggerReadSettings: incompatible version %04x", version);
		delete byteBuffer;
		return;
	}

	C64DebuggerReadSettingsValues(byteBuffer, settingsBlockType);
	
	delete byteBuffer;
}

void C64DebuggerReadSettingsValues(CByteBuffer *byteBuffer, uint8 settingsBlockType)
{
	LOGM("------------- C64DebuggerReadSettingsValues, blockType=%d", settingsBlockType);
	
	u8 blockType = 0xFF;
	
	int valueInt;
	bool valueBool;
	float valueFloat;
	
	// read block
	while (blockType != C64DEBUGGER_BLOCK_EOF)
	{
		u8 dataType = byteBuffer->GetU8();
		
		if (dataType == C64DEBUGGER_SETTING_BLOCK)
		{
			blockType = byteBuffer->GetU8();
			continue;
		}
		
		char *name = byteBuffer->GetString();
		
		LOGD("read setting '%s'", name);
		
		void *value = NULL;
		
		if (dataType == C64DEBUGGER_SETTING_U8)
		{
			valueInt = byteBuffer->GetU8();
			value = &valueInt;
		}
		else if (dataType == C64DEBUGGER_SETTING_U16)
		{
			valueInt = byteBuffer->GetU16();
			value = &valueInt;
		}
		else if (dataType == C64DEBUGGER_SETTING_I32)
		{
			valueInt = byteBuffer->GetI32();
			value = &valueInt;
		}
		else if (dataType == C64DEBUGGER_SETTING_FLOAT)
		{
			valueFloat = byteBuffer->GetFloat();
			value = &valueFloat;
		}
		else if (dataType == C64DEBUGGER_SETTING_BOOL)
		{
			valueBool = byteBuffer->GetBool();
			value = &valueBool;
		}
		else if (dataType == C64DEBUGGER_SETTING_STRING)
		{
			value = byteBuffer->GetSlrString();
		}
		else
		{
			LOGError("C64DebuggerReadSettingsValues: unknown dataType=%d", dataType);
		}
		
		if (blockType == settingsBlockType)
		{
			if (dataType == C64DEBUGGER_SETTING_CUSTOM)
			{
				CByteBuffer *byteBufferCustom = byteBuffer->getByteBuffer();
				C64DebuggerReadSettingCustom(name, byteBufferCustom);
				delete byteBufferCustom;
			}
			else
			{
				if (value != NULL)
					C64DebuggerSetSetting(name, value);
			}
		}
		
		free(name);
		
		if (dataType == C64DEBUGGER_SETTING_STRING)
		{
			delete (CSlrString*)value;
		}
	}
}

void C64DebuggerReadSettingCustom(char *name, CByteBuffer *byteBuffer)
{
//	if (!strcmp(name, "MonitorHistory"))
//	{
//		int historySize = byteBuffer->GetByte();
//		for (int i = 0; i < historySize; i++)
//		{
//			char *cmd = byteBuffer->GetString();
//			viewC64->viewMonitorConsole->viewConsole->commandLineHistory.push_back(cmd);
//		}
//		viewC64->viewMonitorConsole->viewConsole->commandLineHistoryIt = viewC64->viewMonitorConsole->viewConsole->commandLineHistory.end();
//	}
}


void C64DebuggerSetSetting(char *name, void *value)
{
	LOGD("C64DebuggerSetSetting: name='%s'", name);
	
	if (!strcmp(name, "FolderD64"))
	{
		if (c64SettingsDefaultD64Folder != NULL)
			delete c64SettingsDefaultD64Folder;
		
		c64SettingsDefaultD64Folder = new CSlrString((CSlrString*)value);
		return;
	}
	else if (!strcmp(name, "FolderPRG"))
	{
		if (c64SettingsDefaultPRGFolder != NULL)
			delete c64SettingsDefaultPRGFolder;
		
		c64SettingsDefaultPRGFolder = new CSlrString((CSlrString*)value);
		return;
	}
	else if (!strcmp(name, "FolderCRT"))
	{
		if (c64SettingsDefaultCartridgeFolder != NULL)
			delete c64SettingsDefaultCartridgeFolder;
		
		c64SettingsDefaultCartridgeFolder = new CSlrString((CSlrString*)value);
		return;
	}
	else if (!strcmp(name, "FolderTAP"))
	{
		if (c64SettingsDefaultTAPFolder != NULL)
			delete c64SettingsDefaultTAPFolder;
		
		c64SettingsDefaultTAPFolder = new CSlrString((CSlrString*)value);
		return;
	}
	else if (!strcmp(name, "FolderSnaps"))
	{
		if (c64SettingsDefaultSnapshotsFolder != NULL)
			delete c64SettingsDefaultSnapshotsFolder;
		
		c64SettingsDefaultSnapshotsFolder = new CSlrString((CSlrString*)value);
		return;
	}
	else if (!strcmp(name, "FolderMemDumps"))
	{
		if (c64SettingsDefaultMemoryDumpFolder != NULL)
			delete c64SettingsDefaultMemoryDumpFolder;
		
		c64SettingsDefaultMemoryDumpFolder = new CSlrString((CSlrString*)value);
		return;
	}
	
	else if (!strcmp(name, "PathD64"))
	{
		if (c64SettingsPathToD64 != NULL)
			delete c64SettingsPathToD64;
		
		c64SettingsPathToD64 = new CSlrString((CSlrString*)value);
		
		// the setting will be updated later by c64PerformStartupTasksThreaded
		if (viewC64->debugInterfaceC64 && viewC64->debugInterfaceC64->isRunning)
		{
			viewC64->viewC64MainMenu->InsertD64(c64SettingsPathToD64, false, c64SettingsAutoJmpFromInsertedDiskFirstPrg, 0, true);
		}
		return;
	}
	else if (!strcmp(name, "PathPRG"))
	{
		if (c64SettingsPathToPRG != NULL)
			delete c64SettingsPathToPRG;
		
		c64SettingsPathToPRG = new CSlrString((CSlrString*)value);
		c64SettingsPathToPRG->DebugPrint("PathPRG=");
		// the setting will be updated later by c64PerformStartupTasksThreaded
		if (viewC64->debugInterfaceC64 && viewC64->debugInterfaceC64->isRunning)
		{
			viewC64->viewC64MainMenu->LoadPRG(c64SettingsPathToPRG, false, false, true, false);
		}
		return;
	}
	else if (!strcmp(name, "PathTAP"))
	{
		if (c64SettingsPathToTAP != NULL)
			delete c64SettingsPathToTAP;
		
		c64SettingsPathToTAP = new CSlrString((CSlrString*)value);
		// the setting will be updated later by c64PerformStartupTasksThreaded
		if (viewC64->debugInterfaceC64 && viewC64->debugInterfaceC64->isRunning)
		{
			viewC64->viewC64MainMenu->LoadTape(c64SettingsPathToTAP, false, false, false);
		}
		return;
	}
	else if (!strcmp(name, "PathCRT"))
	{
		if (c64SettingsPathToCartridge != NULL)
			delete c64SettingsPathToCartridge;
		
		c64SettingsPathToCartridge = new CSlrString((CSlrString*)value);
		
		// the setting will be updated later by c64PerformStartupTasksThreaded
		if (viewC64->debugInterfaceC64 && viewC64->debugInterfaceC64->isRunning)
		{
			viewC64->viewC64MainMenu->InsertCartridge(c64SettingsPathToCartridge, false);
		}
		return;
	}
	else if (!strcmp(name, "ScreenSupersampleFactor"))
	{
		u16 v = *((u16*)value);
		c64SettingsScreenSupersampleFactor = v;
		if (viewC64->debugInterfaceC64 && viewC64->debugInterfaceC64->isRunning)
		{
			viewC64->viewC64Screen->SetSupersampleFactor(c64SettingsScreenSupersampleFactor);
		}
		if (viewC64->debugInterfaceAtari && viewC64->debugInterfaceAtari->isRunning)
		{
			viewC64->viewAtariScreen->SetSupersampleFactor(c64SettingsScreenSupersampleFactor);
		}
		if (viewC64->debugInterfaceNes && viewC64->debugInterfaceNes->isRunning)
		{
			viewC64->viewNesScreen->SetSupersampleFactor(c64SettingsScreenSupersampleFactor);
		}
		return;
	}
	else if (!strcmp(name, "UsePipeIntegration"))
	{
		bool v = *((bool*)value);
		c64SettingsUsePipeIntegration = v;
		return;
	}
	else if (!strcmp(name, "AutoJmpFromInsertedDiskFirstPrg"))
	{
		bool v = *((bool*)value);
		c64SettingsAutoJmpFromInsertedDiskFirstPrg = v;
		return;
	}
	else if (!strcmp(name, "AutoJmp"))
	{
		bool v = *((bool*)value);
		c64SettingsAutoJmp = v;
		return;
	}
	else if (!strcmp(name, "AutoJmpAlwaysToLoadedPRGAddress"))
	{
		bool v = *((bool*)value);
		c64SettingsAutoJmpAlwaysToLoadedPRGAddress = v;
		return;
	}
	
	if (!strcmp(name, "SnapshotsManagerStoreInterval"))
	{
		i32 v = *((i32*)value);
		if (viewC64->debugInterfaceC64)
		{
			viewC64->debugInterfaceC64->snapshotsManager->SetRecordingStoreInterval(v);
		}
		if (viewC64->debugInterfaceAtari)
		{
			viewC64->debugInterfaceAtari->snapshotsManager->SetRecordingStoreInterval(v);
		}
		
		if (viewC64->debugInterfaceC64 || viewC64->debugInterfaceAtari)
		{
			viewC64->viewC64SettingsMenu->menuItemC64SnapshotsManagerStoreInterval->SetValue(v, false);
		}
		return;
	}
	else if (!strcmp(name, "SnapshotsManagerLimit"))
	{
		i32 v = *((i32*)value);
		if (viewC64->debugInterfaceC64)
		{
			viewC64->debugInterfaceC64->snapshotsManager->SetRecordingLimit(v);
		}
		if (viewC64->debugInterfaceAtari)
		{
			viewC64->debugInterfaceAtari->snapshotsManager->SetRecordingLimit(v);
		}
		if (viewC64->debugInterfaceC64 || viewC64->debugInterfaceAtari)
		{
			viewC64->viewC64SettingsMenu->menuItemC64SnapshotsManagerLimit->SetValue(v, false);
		}
		return;
	}
	else if (!strcmp(name, "TimelineIsActive"))
	{
		bool v = *((bool*)value);
		c64SettingsTimelineIsActive = v;
		
		if (viewC64->debugInterfaceC64 || viewC64->debugInterfaceAtari)
		{
			viewC64->viewC64SettingsMenu->menuItemC64TimelineIsActive->SetSelectedOption(v, false);
		}
		return;
	}
	else if (!strcmp(name, "UseNativeEmulatorMonitor"))
	{
		bool v = *((bool*)value);
		c64SettingsUseNativeEmulatorMonitor = v;
		return;
	}
	
#if defined(WIN32)
	else if (!strcmp(name, "DisableProcessPriorityBoost"))
	{
		bool v = *((bool*)value);
		c64SettingsIsProcessPriorityBoostDisabled = v;
		SYS_SetMainProcessPriorityBoostDisabled(c64SettingsIsProcessPriorityBoostDisabled);
		return;
	}
	else if (!strcmp(name, "ProcessPriority"))
	{
		u8 v = *((u8*)value);
		c64SettingsProcessPriority = v;
		SYS_SetMainProcessPriority(c64SettingsProcessPriority);
		return;
	}
#endif
	
//	if (viewC64->debugInterfaceC64)
#if defined(RUN_COMMODORE64)
	{
		if (!strcmp(name, "FastBootPatch"))
		{
			bool v = *((bool*)value);
			c64SettingsFastBootKernalPatch = v;
			return;
		}
		else if (!strcmp(name, "IsInVicEditor"))
		{
			bool v = *((bool*)value);
			c64SettingsIsInVicEditor = v;
			return;
		}
		else if (!strcmp(name, "C64Model"))
		{
			int v = *((int*)value);
			//viewC64->viewC64SettingsMenu->SetOptionC64ModelType(v);
			c64SettingsC64Model = v;
			
			if (viewC64->debugInterfaceC64 && viewC64->debugInterfaceC64->isRunning)
			{
				viewC64->debugInterfaceC64->SetC64ModelType(c64SettingsC64Model);
			}
			return;
		}
		else if (!strcmp(name, "VicStateRecording"))
		{
			int v = *((int*)value);
			viewC64->viewC64SettingsMenu->menuItemVicStateRecordingMode->SetSelectedOption(v, false);
			
			c64SettingsVicStateRecordingMode = v;
			viewC64->debugInterfaceC64->SetVicRecordStateMode(v);
			return;
		}
		else if (!strcmp(name, "VicPalette"))
		{
			int v = *((int*)value);
			viewC64->viewC64SettingsMenu->menuItemVicPalette->SetSelectedOption(v, false);
			
			c64SettingsVicPalette = v;
			C64SetPaletteNum(v);
			return;
		}

		else if (!strcmp(name, "SIDEngineModel"))
		{
			int v = *((int*)value);
			viewC64->viewC64SettingsMenu->menuItemSIDModel->SetSelectedOption(v, false);
			c64SettingsSIDEngineModel = v;
			
			// the setting will be updated later by c64PerformStartupTasksThreaded
			if (viewC64->debugInterfaceC64 && viewC64->debugInterfaceC64->isRunning)
			{
				viewC64->debugInterfaceC64->SetSidType(c64SettingsSIDEngineModel);
			}
			return;
		}
		else if (!strcmp(name, "RESIDSamplingMethod"))
		{
			int v = *((int*)value);
			viewC64->viewC64SettingsMenu->menuItemRESIDSamplingMethod->SetSelectedOption(v, false);
			c64SettingsRESIDSamplingMethod = v;
			
			viewC64->debugInterfaceC64->SetSidSamplingMethod(c64SettingsRESIDSamplingMethod);
			return;
		}
		else if (!strcmp(name, "RESIDEmulateFilters"))
		{
			bool v = *((bool*)value);
			
			if (v)
			{
				viewC64->viewC64SettingsMenu->menuItemRESIDEmulateFilters->SetSelectedOption(1, false);
				c64SettingsRESIDEmulateFilters = true;
			}
			else
			{
				viewC64->viewC64SettingsMenu->menuItemRESIDEmulateFilters->SetSelectedOption(0, false);
				c64SettingsRESIDEmulateFilters = false;
			}
			
			viewC64->debugInterfaceC64->SetSidEmulateFilters(c64SettingsRESIDEmulateFilters);
			return;
		}
		else if (!strcmp(name, "RESIDPassBand"))
		{
			int v = *((int*)value);
			viewC64->viewC64SettingsMenu->menuItemRESIDPassBand->SetValue(v, false);
			c64SettingsRESIDPassBand = v;
			
			viewC64->debugInterfaceC64->SetSidPassBand(c64SettingsRESIDPassBand);
			return;
		}
		else if (!strcmp(name, "RESIDFilterBias"))
		{
			int v = *((int*)value);
			viewC64->viewC64SettingsMenu->menuItemRESIDFilterBias->SetValue(v, false);
			c64SettingsRESIDFilterBias = v;
			
			viewC64->debugInterfaceC64->SetSidFilterBias(c64SettingsRESIDFilterBias);
			return;
		}
		else if (!strcmp(name, "SIDStereo"))
		{
			int v = *((int*)value);
			viewC64->viewC64SettingsMenu->menuItemSIDStereo->SetSelectedOption(v, false);
			c64SettingsSIDStereo = v;
			
			viewC64->debugInterfaceC64->SetSidStereo(c64SettingsSIDStereo);
			viewC64->viewC64StateSID->UpdateSidButtonsState();
			return;
		}
		else if (!strcmp(name, "SIDStereoAddress"))
		{
			int v = *((int*)value);
			c64SettingsSIDStereoAddress = v;
			
			int optNum = viewC64->viewC64SettingsMenu->GetOptionNumFromSidAddress(v);
			viewC64->viewC64SettingsMenu->menuItemSIDStereoAddress->SetSelectedOption(optNum, false);
			
			viewC64->debugInterfaceC64->SetSidStereoAddress(c64SettingsSIDStereoAddress);
			viewC64->viewC64StateSID->UpdateSidButtonsState();
			return;
		}
		else if (!strcmp(name, "SIDTripleAddress"))
		{
			int v = *((int*)value);
			c64SettingsSIDTripleAddress = v;
			
			int optNum = viewC64->viewC64SettingsMenu->GetOptionNumFromSidAddress(v);
			viewC64->viewC64SettingsMenu->menuItemSIDTripleAddress->SetSelectedOption(optNum, false);
			
			viewC64->debugInterfaceC64->SetSidTripleAddress(c64SettingsSIDTripleAddress);
			viewC64->viewC64StateSID->UpdateSidButtonsState();
			return;
		}
		else if (!strcmp(name, "MuteSIDOnPause"))
		{
			bool v = *((bool*)value);
			
			if (v)
			{
				viewC64->viewC64SettingsMenu->menuItemMuteSIDOnPause->SetSelectedOption(1, false);
				c64SettingsMuteSIDOnPause = true;
			}
			else
			{
				viewC64->viewC64SettingsMenu->menuItemMuteSIDOnPause->SetSelectedOption(0, false);
				c64SettingsMuteSIDOnPause = false;
			}
			return;
		}
		else if (!strcmp(name, "RunSIDWhenWarp"))
		{
			bool v = *((bool*)value);
			
			if (v)
			{
				viewC64->viewC64SettingsMenu->menuItemRunSIDWhenInWarp->SetSelectedOption(1, false);
				c64SettingsRunSIDWhenInWarp = true;
			}
			else
			{
				viewC64->viewC64SettingsMenu->menuItemRunSIDWhenInWarp->SetSelectedOption(0, false);
				c64SettingsRunSIDWhenInWarp = false;
			}
			viewC64->debugInterfaceC64->SetRunSIDWhenInWarp(c64SettingsRunSIDWhenInWarp);
			return;
		}
		else if (!strcmp(name, "RunSIDEmulation"))
		{
			bool v = *((bool*)value);
			
			if (v)
			{
				viewC64->viewC64SettingsMenu->menuItemRunSIDEmulation->SetSelectedOption(1, false);
				c64SettingsRunSIDEmulation = true;
			}
			else
			{
				viewC64->viewC64SettingsMenu->menuItemRunSIDEmulation->SetSelectedOption(0, false);
				c64SettingsRunSIDEmulation = false;
			}
			viewC64->debugInterfaceC64->SetRunSIDEmulation(c64SettingsRunSIDEmulation);
			return;
		}
		else if (!strcmp(name, "MuteSIDMode"))
		{
			u8 v = *((u8*)value);
			c64SettingsMuteSIDMode = v;
			viewC64->viewC64SettingsMenu->menuItemMuteSIDMode->SetSelectedOption(v, false);
			viewC64->UpdateSIDMute();
			return;
		}
		else if (!strcmp(name, "SIDImportMode"))
		{
			u8 v = *((u8*)value);
			c64SettingsC64SidImportMode = v;
			viewC64->viewC64SettingsMenu->menuItemSIDImportMode->SetSelectedOption(v, false);
			return;
		}
		
		else if (!strcmp(name, "EmulationMaximumSpeed"))
		{
			int v = *((int*)value);
			if (v == 10)
			{
				viewC64->viewC64SettingsMenu->menuItemMaximumSpeed->SetSelectedOption(0, false);
			}
			else if (v == 20)
			{
				viewC64->viewC64SettingsMenu->menuItemMaximumSpeed->SetSelectedOption(1, false);
			}
			else if (v == 50)
			{
				viewC64->viewC64SettingsMenu->menuItemMaximumSpeed->SetSelectedOption(2, false);
			}
			else if (v == 100)
			{
				viewC64->viewC64SettingsMenu->menuItemMaximumSpeed->SetSelectedOption(3, false);
			}
			else if (v == 200)
			{
				viewC64->viewC64SettingsMenu->menuItemMaximumSpeed->SetSelectedOption(4, false);
			}
			
			c64SettingsEmulationMaximumSpeed = v;
			
			viewC64->debugInterfaceC64->SetEmulationMaximumSpeed(v);
			return;
		}
		else if (!strcmp(name, "EmulateVSPBug"))
		{
			bool v = *((bool*)value);
			c64SettingsEmulateVSPBug = v;
			viewC64->debugInterfaceC64->SetVSPBugEmulation(c64SettingsEmulateVSPBug);
			return;
		}
		else if (!strcmp(name, "AutoJmpDoReset"))
		{
			int v = *((int*)value);
			viewC64->viewC64SettingsMenu->menuItemAutoJmpDoReset->SetSelectedOption(v, false);
			c64SettingsAutoJmpDoReset = v;
			return;
		}
		else if (!strcmp(name, "AutoJmpWaitAfterReset"))
		{
			int v = *((int*)value);
			c64SettingsAutoJmpWaitAfterReset = v;
			viewC64->viewC64SettingsMenu->menuItemAutoJmpWaitAfterReset->SetValue(v, false);
			return;
		}
		
		else if (!strcmp(name, "VicDisplayBorder"))
		{
			u8 v = *((u8*)value);
			c64SettingsVicDisplayBorderType = v;
			viewC64->viewC64VicControl->SetBorderType(c64SettingsVicDisplayBorderType);
			return;
		}
		else if (!strcmp(name, "VicEditorForceReplaceColor"))
		{
			bool v = *((bool*)value);
			c64SettingsVicEditorForceReplaceColor = v;
			viewC64->viewC64SettingsMenu->menuItemVicEditorForceReplaceColor->SetSelectedOption(v, false);
			return;
		}
		else if (!strcmp(name, "VicEditorDefaultBackgroundColor"))
		{
			u8 v = *((u8*)value);
			c64SettingsVicEditorDefaultBackgroundColor = v;
			return;
		}
		else if (!strcmp(name, "AudioVolume"))
		{
			u16 v = *((u16*)value);
			c64SettingsAudioVolume = v;
			viewC64->viewC64SettingsMenu->menuItemAudioVolume->SetValue(v, false);
			viewC64->debugInterfaceC64->SetAudioVolume((float)(c64SettingsAudioVolume) / 100.0f);
			return;
		}

		//
		else if (!strcmp(name, "CrossLinesAlpha"))
		{
			float v = *((float*)value);
			c64SettingsScreenRasterCrossLinesAlpha = v;
			viewC64->viewC64SettingsMenu->menuItemScreenRasterCrossLinesAlpha->SetValue(v, false);
			
			if (viewC64->debugInterfaceC64)
			{
				viewC64->viewC64Screen->InitRasterColorsFromScheme();
			}
			return;
		}
		else if (!strcmp(name, "CrossLinesColor"))
		{
			u8 v = *((u8*)value);
			c64SettingsScreenRasterCrossLinesColorScheme = v;
			viewC64->viewC64SettingsMenu->menuItemScreenRasterCrossLinesColorScheme->SetSelectedOption(v, false);
			
			if (viewC64->debugInterfaceC64)
			{
				viewC64->viewC64Screen->InitRasterColorsFromScheme();
				
			}
			return;
		}
		else if (!strcmp(name, "CrossAlpha"))
		{
			float v = *((float*)value);
			c64SettingsScreenRasterCrossAlpha = v;
			viewC64->viewC64SettingsMenu->menuItemScreenRasterCrossAlpha->SetValue(v, false);
			if (viewC64->debugInterfaceC64)
			{
				viewC64->viewC64Screen->InitRasterColorsFromScheme();
			}
			return;
		}
		else if (!strcmp(name, "CrossInteriorColor"))
		{
			u8 v = *((u8*)value);
			c64SettingsScreenRasterCrossInteriorColorScheme = v;
			viewC64->viewC64SettingsMenu->menuItemScreenRasterCrossInteriorColorScheme->SetSelectedOption(v, false);
			
			if (viewC64->debugInterfaceC64)
			{
				viewC64->viewC64Screen->InitRasterColorsFromScheme();
			}
			return;
		}
		else if (!strcmp(name, "CrossExteriorColor"))
		{
			u8 v = *((u8*)value);
			c64SettingsScreenRasterCrossExteriorColorScheme = v;
			viewC64->viewC64SettingsMenu->menuItemScreenRasterCrossExteriorColorScheme->SetSelectedOption(v, false);
			
			if (viewC64->debugInterfaceC64)
			{
				viewC64->viewC64Screen->InitRasterColorsFromScheme();
			}
			return;
		}
		else if (!strcmp(name, "CrossTipColor"))
		{
			u8 v = *((u8*)value);
			c64SettingsScreenRasterCrossTipColorScheme = v;
			viewC64->viewC64SettingsMenu->menuItemScreenRasterCrossTipColorScheme->SetSelectedOption(v, false);
			
			if (viewC64->debugInterfaceC64)
			{
				viewC64->viewC64Screen->InitRasterColorsFromScheme();
			}
			return;
		}
		
		//
		else if (!strcmp(name, "DatasetteSpeedTuning"))
		{
			int v = *((int*)value);
			c64SettingsDatasetteSpeedTuning = v;
			viewC64->viewC64SettingsMenu->menuItemDatasetteSpeedTuning->SetValue((float)v, false);
			
			viewC64->debugInterfaceC64->DatasetteSetSpeedTuning(v);
			return;
		}
		else if (!strcmp(name, "DatasetteZeroGapDelay"))
		{
			int v = *((int*)value);
			c64SettingsDatasetteZeroGapDelay = v;
			viewC64->viewC64SettingsMenu->menuItemDatasetteZeroGapDelay->SetValue((float)v, false);

			viewC64->debugInterfaceC64->DatasetteSetZeroGapDelay(v);
			return;
		}
		else if (!strcmp(name, "DatasetteTapeWobble"))
		{
			int v = *((int*)value);
			c64SettingsDatasetteTapeWobble = v;
			viewC64->viewC64SettingsMenu->menuItemDatasetteTapeWobble->SetValue((float)v, false);

			viewC64->debugInterfaceC64->DatasetteSetTapeWobble(v);
			return;
		}
		else if (!strcmp(name, "DatasetteResetWithCPU"))
		{
			bool v = *((bool*)value);
			c64SettingsDatasetteResetWithCPU = v;
			viewC64->viewC64SettingsMenu->menuItemDatasetteResetWithCPU->SetSelectedOption(v ? 1:0, false);

			viewC64->debugInterfaceC64->DatasetteSetResetWithCPU(v);
			return;
		}
		else if (!strcmp(name, "ReuEnabled"))
		{
			bool v = *((bool*)value);
			c64SettingsReuEnabled = v;
			
			LOGD("c64SettingsReuEnabled=%s", STRBOOL(c64SettingsReuEnabled));
			viewC64->viewC64SettingsMenu->menuItemReuEnabled->SetSelectedOption(v ? 1:0, false);
			
			viewC64->debugInterfaceC64->SetReuEnabled(v);
			return;
		}
		else if (!strcmp(name, "ReuSize"))
		{
			int v = *((int*)value);
			c64SettingsReuSize = v;

			for (int i = 0; i < 8; i++)
			{
				if (settingsReuSizes[i] == v)
				{
					viewC64->viewC64SettingsMenu->menuItemReuSize->SetSelectedOption(i, false);
					break;
				}
			}
			
			viewC64->debugInterfaceC64->SetReuSize(v);
			return;
		}
		else if (!strcmp(name, "C64ProfilerOutputPath"))
		{
			if (c64SettingsC64ProfilerFileOutputPath != NULL)
			{
				delete c64SettingsC64ProfilerFileOutputPath;
			}
			
			c64SettingsC64ProfilerFileOutputPath = new CSlrString((CSlrString*)value);
			return;
		}
		else if (!strcmp(name, "C64ProfilerDoVic"))
		{
			bool v = *((bool*)value);
			c64SettingsC64ProfilerDoVicProfile = v;
			return;
		}
		
		else if (!strcmp(name, "SnapshotsManagerIsActive"))
		{
			bool v = *((bool*)value);
			viewC64->debugInterfaceC64->snapshotsManager->SetRecordingIsActive(v);
			viewC64->viewC64SettingsMenu->menuItemC64SnapshotsManagerIsActive->SetSelectedOption(v, false);
			return;
		}
	}
#endif
	
#if defined(RUN_ATARI)
	{
		/*
		if (!strcmp(name, "AtariPokeyStereo"))
		{
			bool v = *((bool*)value);
			c64SettingsAtariPokeyStereo = v;
			debugInterfaceAtari->SetPokeyStereo(v);
			viewC64->viewC64SettingsMenu->menuItemAtariPokeyStereo->SetSelectedOption(v, false);
			return;
		}
		else
		 */
		
		 if (!strcmp(name, "FolderAtariROMs"))
		{
			if (c64SettingsPathToAtariROMs != NULL)
				delete c64SettingsPathToAtariROMs;
			
			c64SettingsPathToAtariROMs = new CSlrString((CSlrString*)value);
			return;
		}
		else if (!strcmp(name, "FolderATR"))
		{
			if (c64SettingsDefaultATRFolder != NULL)
				delete c64SettingsDefaultATRFolder;
			
			c64SettingsDefaultATRFolder = new CSlrString((CSlrString*)value);
			return;
		}
		else if (!strcmp(name, "PathATR"))
		{
			if (c64SettingsPathToATR != NULL)
				delete c64SettingsPathToATR;
			
			c64SettingsPathToATR = new CSlrString((CSlrString*)value);
			
			// the setting will be updated later by c64PerformStartupTasksThreaded
			if (viewC64->debugInterfaceAtari && viewC64->debugInterfaceAtari->isRunning)
			{
				viewC64->viewC64MainMenu->InsertATR(c64SettingsPathToATR, false, c64SettingsAutoJmpFromInsertedDiskFirstPrg, 0, true);
			}
			return;
		}
		else if (!strcmp(name, "FolderXEX"))
		{
			if (c64SettingsDefaultXEXFolder != NULL)
				delete c64SettingsDefaultXEXFolder;
			
			c64SettingsDefaultXEXFolder = new CSlrString((CSlrString*)value);
			return;
		}
		else if (!strcmp(name, "PathXEX"))
		{
			if (c64SettingsPathToXEX != NULL)
				delete c64SettingsPathToXEX;
			
			c64SettingsPathToXEX = new CSlrString((CSlrString*)value);
			
			// the setting will be updated later by c64PerformStartupTasksThreaded
			if (viewC64->debugInterfaceAtari && viewC64->debugInterfaceAtari->isRunning)
			{
				viewC64->viewC64MainMenu->LoadXEX(c64SettingsPathToXEX, false, false, true);
			}
			return;
		}
		
		else if (!strcmp(name, "FolderCAS"))
		{
			if (c64SettingsDefaultCASFolder != NULL)
				delete c64SettingsDefaultCASFolder;
			
			c64SettingsDefaultCASFolder = new CSlrString((CSlrString*)value);
			return;
		}
		else if (!strcmp(name, "PathCAS"))
		{
			if (c64SettingsPathToCAS != NULL)
				delete c64SettingsPathToCAS;
			
			c64SettingsPathToCAS = new CSlrString((CSlrString*)value);
			
			// the setting will be updated later by c64PerformStartupTasksThreaded
			if (viewC64->debugInterfaceAtari && viewC64->debugInterfaceAtari->isRunning)
			{
				viewC64->viewC64MainMenu->LoadCAS(c64SettingsPathToCAS, false, false, true);
			}
			return;
		}

		else if (!strcmp(name, "FolderAtariCart"))
		{
			if (c64SettingsDefaultAtariCartridgeFolder != NULL)
				delete c64SettingsDefaultAtariCartridgeFolder;
			
			c64SettingsDefaultAtariCartridgeFolder = new CSlrString((CSlrString*)value);
			return;
		}
		else if (!strcmp(name, "PathAtariCart"))
		{
			if (c64SettingsPathToAtariCartridge != NULL)
				delete c64SettingsPathToAtariCartridge;
			
			c64SettingsPathToAtariCartridge = new CSlrString((CSlrString*)value);
			
			// the setting will be updated later by c64PerformStartupTasksThreaded
			if (viewC64->debugInterfaceAtari && viewC64->debugInterfaceAtari->isRunning)
			{
				viewC64->viewC64MainMenu->InsertAtariCartridge(c64SettingsPathToAtariCartridge, false, false, true);
			}
			return;
		}

		
		else if (!strcmp(name, "AtariVideoSystem"))
		{
			u8 v = *((u8*)value);
			viewC64->viewC64SettingsMenu->menuItemAtariVideoSystem->SetSelectedOption(v, false);

			c64SettingsAtariVideoSystem = v;
			
			// the setting will be updated later by c64PerformStartupTasksThreaded
			if (viewC64->debugInterfaceAtari && viewC64->debugInterfaceAtari->isRunning)
			{
				viewC64->debugInterfaceAtari->SetVideoSystem(v);
			}
			return;
		}
		else if (!strcmp(name, "AtariMachineType"))
		{
			u8 v = *((u8*)value);
			viewC64->viewC64SettingsMenu->menuItemAtariMachineType->SetSelectedOption(v, false);
			viewC64->viewC64SettingsMenu->UpdateAtariRamSizeOptions();
			
			c64SettingsAtariMachineType = v;
			
			// the setting will be updated later by c64PerformStartupTasksThreaded
			if (viewC64->debugInterfaceAtari && viewC64->debugInterfaceAtari->isRunning)
			{
				viewC64->debugInterfaceAtari->SetMachineType(v);
			}
			return;
		}

		else if (!strcmp(name, "AtariRamSizeOption"))
		{
			u8 v = *((u8*)value);
			viewC64->viewC64SettingsMenu->menuItemAtariRamSize->SetSelectedOption(v, false);
			
			c64SettingsAtariRamSizeOption = v;
			
			// the setting will be updated later by c64PerformStartupTasksThreaded
			if (viewC64->debugInterfaceAtari && viewC64->debugInterfaceAtari->isRunning)
			{
				viewC64->debugInterfaceAtari->SetRamSizeOption(v);
			}
			return;
		}

	}
#endif
	
#if defined(RUN_NES)
	{
		if (!strcmp(name, "FolderNES"))
		{
			if (c64SettingsDefaultNESFolder != NULL)
				delete c64SettingsDefaultNESFolder;
			
			c64SettingsDefaultNESFolder = new CSlrString((CSlrString*)value);
			return;
		}
		else if (!strcmp(name, "PathNES"))
		{
			if (c64SettingsPathToNES != NULL)
				delete c64SettingsPathToNES;
			
			c64SettingsPathToNES = new CSlrString((CSlrString*)value);
			
			// the setting will be updated later by c64PerformStartupTasksThreaded
			if (viewC64->debugInterfaceNes && viewC64->debugInterfaceNes->isRunning)
			{
				viewC64->viewC64MainMenu->LoadNES(c64SettingsPathToNES, false);
			}
			return;
		}

	}
#endif

	if (!strcmp(name, "PathMemMapFile"))
	{
		if (c64SettingsPathToC64MemoryMapFile != NULL)
			delete c64SettingsPathToC64MemoryMapFile;
		
		c64SettingsPathToC64MemoryMapFile = new CSlrString((CSlrString*)value);
		return;
	}
	else if (!strcmp(name, "DisassembleExecuteAware"))
	{
		bool v = *((bool*)value);
		c64SettingsRenderDisassembleExecuteAware = v;
		return;
	}
	else if (!strcmp(name, "WindowAlwaysOnTop"))
	{
		bool v = *((bool*)value);
		c64SettingsWindowAlwaysOnTop = v;
		
		VID_SetWindowAlwaysOnTop(c64SettingsWindowAlwaysOnTop);
		return;
	}
	
#if !defined(WIN32)
	else if (!strcmp(name, "UseSystemDialogs"))
	{
		bool v = *((bool*)value);
		c64SettingsUseSystemFileDialogs = v;
		return;
	}
#endif
	
#if defined(WIN32)
	else if (!strcmp(name, "UseOnlyFirstCPU"))
	{
		bool v = *((bool*)value);
		c64SettingsUseOnlyFirstCPU = v;
		return;
	}
#endif


	
	else if (!strcmp(name, "ScreenLayoutId"))
	{
		int v = *((int*)value);
		c64SettingsDefaultScreenLayoutId = v;
		return;
	}
	else if (!strcmp(name, "JoystickPort"))
	{
		int v = *((int*)value);
		viewC64->viewC64SettingsMenu->menuItemJoystickPort->SetSelectedOption(v, false);
		c64SettingsJoystickPort = v;
		return;
	}
	else if (!strcmp(name, "UseKeyboardAsJoystick"))
	{
		bool v = *((bool*)value);
		c64SettingsUseKeyboardAsJoystick = v;
		viewC64->viewC64SettingsMenu->menuItemUseKeyboardAsJoystick->SetSelectedOption(v, false);
		return;
	}
	
	else if (!strcmp(name, "MemoryValuesStyle"))
	{
		int v = *((int*)value);
		viewC64->viewC64SettingsMenu->menuItemMemoryCellsColorStyle->SetSelectedOption(v, false);
		c64SettingsMemoryValuesStyle = v;
		C64DebuggerComputeMemoryMapColorTables(v);
		return;
	}
	else if (!strcmp(name, "MemoryMarkersStyle"))
	{
		int v = *((int*)value);
		viewC64->viewC64SettingsMenu->menuItemMemoryMarkersColorStyle->SetSelectedOption(v, false);
		
		c64SettingsMemoryMarkersStyle = v;
		C64DebuggerSetMemoryMapMarkersStyle(v);
		return;
	}
	else if (!strcmp(name, "AudioOutDevice"))
	{
		if (c64SettingsAudioOutDevice != NULL)
			delete c64SettingsAudioOutDevice;
		
		c64SettingsAudioOutDevice = new CSlrString((CSlrString*)value);
		
		gSoundEngine->SetOutputAudioDevice(c64SettingsAudioOutDevice);
		return;
	}
	
	
	else if (!strcmp(name, "RenderScreenNearest"))
	{
		bool v = *((bool*)value);
		
		if (v)
		{
			viewC64->viewC64SettingsMenu->menuItemRenderScreenInterpolation->SetSelectedOption(1, false);
			c64SettingsRenderScreenNearest = true;
		}
		else
		{
			viewC64->viewC64SettingsMenu->menuItemRenderScreenInterpolation->SetSelectedOption(0, false);
			c64SettingsRenderScreenNearest = false;
		}
		return;
	}
	
	else if (!strcmp(name, "MemMapMultiTouch"))
	{
#if defined(MACOS)
		bool v = *((bool*)value);
		
		if (v)
		{
			viewC64->viewC64SettingsMenu->menuItemMultiTouchMemoryMap->SetSelectedOption(1, false);
			c64SettingsUseMultiTouchInMemoryMap = true;
		}
		else
		{
			viewC64->viewC64SettingsMenu->menuItemMultiTouchMemoryMap->SetSelectedOption(0, false);
			c64SettingsUseMultiTouchInMemoryMap = false;
		}
		return;
#endif
	}
	else if (!strcmp(name, "MemMapInvert"))
	{
		bool v = *((bool*)value);
		
		if (v)
		{
			viewC64->viewC64SettingsMenu->menuItemMemoryMapInvert->SetSelectedOption(1, false);
			c64SettingsMemoryMapInvertControl = true;
		}
		else
		{
			viewC64->viewC64SettingsMenu->menuItemMemoryMapInvert->SetSelectedOption(0, false);
			c64SettingsMemoryMapInvertControl = false;
		}
		return;
	}
	else if (!strcmp(name, "MemMapRefresh"))
	{
		int v = *((int*)value);
		if (v == 1)
		{
			viewC64->viewC64SettingsMenu->menuItemMemoryMapRefreshRate->SetSelectedOption(0, false);
		}
		else if (v == 2)
		{
			viewC64->viewC64SettingsMenu->menuItemMemoryMapRefreshRate->SetSelectedOption(1, false);
		}
		else if (v == 4)
		{
			viewC64->viewC64SettingsMenu->menuItemMemoryMapRefreshRate->SetSelectedOption(2, false);
		}
		else if (v == 10)
		{
			viewC64->viewC64SettingsMenu->menuItemMemoryMapRefreshRate->SetSelectedOption(3, false);
		}
		else if (v == 20)
		{
			viewC64->viewC64SettingsMenu->menuItemMemoryMapRefreshRate->SetSelectedOption(4, false);
		}

		c64SettingsMemoryMapRefreshRate = v;
		return;
	}
	else if (!strcmp(name, "MemMapFadeSpeed"))
	{
		int v = *((int*)value);
		if (v == 1)
		{
			viewC64->viewC64SettingsMenu->menuItemMemoryMapFadeSpeed->SetSelectedOption(0, false);
		}
		else if (v == 10)
		{
			viewC64->viewC64SettingsMenu->menuItemMemoryMapFadeSpeed->SetSelectedOption(1, false);
		}
		else if (v == 20)
		{
			viewC64->viewC64SettingsMenu->menuItemMemoryMapFadeSpeed->SetSelectedOption(2, false);
		}
		else if (v == 50)
		{
			viewC64->viewC64SettingsMenu->menuItemMemoryMapFadeSpeed->SetSelectedOption(3, false);
		}
		else if (v == 100)
		{
			viewC64->viewC64SettingsMenu->menuItemMemoryMapFadeSpeed->SetSelectedOption(4, false);
		}
		else if (v == 200)
		{
			viewC64->viewC64SettingsMenu->menuItemMemoryMapFadeSpeed->SetSelectedOption(5, false);
		}
		else if (v == 300)
		{
			viewC64->viewC64SettingsMenu->menuItemMemoryMapFadeSpeed->SetSelectedOption(6, false);
		}
		else if (v == 400)
		{
			viewC64->viewC64SettingsMenu->menuItemMemoryMapFadeSpeed->SetSelectedOption(7, false);
		}
		else if (v == 500)
		{
			viewC64->viewC64SettingsMenu->menuItemMemoryMapFadeSpeed->SetSelectedOption(8, false);
		}
		else if (v == 1000)
		{
			viewC64->viewC64SettingsMenu->menuItemMemoryMapFadeSpeed->SetSelectedOption(9, false);
		}
		
		c64SettingsMemoryMapFadeSpeed = v;
		
		float fadeSpeed = v / 100.0f;
		C64DebuggerSetMemoryMapCellsFadeSpeed(fadeSpeed);
		return;
	}
	else if (!strcmp(name, "GridLinesAlpha"))
	{
		float v = *((float*)value);
		c64SettingsScreenGridLinesAlpha = v;
		viewC64->viewC64SettingsMenu->menuItemScreenGridLinesAlpha->SetValue(v, false);
		
		if (viewC64->debugInterfaceC64)
		{
			viewC64->viewC64Screen->InitRasterColorsFromScheme();
		}
		return;
	}
	else if (!strcmp(name, "GridLinesColor"))
	{
		u8 v = *((u8*)value);
		c64SettingsScreenGridLinesColorScheme = v;
		viewC64->viewC64SettingsMenu->menuItemScreenGridLinesColorScheme->SetSelectedOption(v, false);
		
		if (viewC64->debugInterfaceC64)
		{
			viewC64->viewC64Screen->InitRasterColorsFromScheme();
			viewC64->viewC64VicDisplay->InitRasterColorsFromScheme();
		}
		return;
	}
	else if (!strcmp(name, "ViewfinderScale"))
	{
		float v = *((float*)value);
		c64SettingsScreenRasterViewfinderScale = v;
		viewC64->viewC64SettingsMenu->menuItemScreenRasterViewfinderScale->SetValue(v, false);

		if (viewC64->debugInterfaceC64)
		{
			viewC64->viewC64Screen->SetZoomedScreenLevel(v);
		}
		return;
	}
	else if (!strcmp(name, "FocusBorderWidth"))
	{
		float v = *((float*)value);
		c64SettingsFocusBorderLineWidth = v;
		viewC64->viewC64SettingsMenu->menuItemFocusBorderLineWidth->SetValue(v, false);
		guiMain->theme->focusBorderLineWidth = v;
		return;
	}
	else if (!strcmp(name, "DisassemblyBackgroundColor"))
	{
		u8 v = *((u8*)value);
		c64SettingsDisassemblyBackgroundColor = v;
		viewC64->viewC64SettingsMenu->menuItemDisassemblyBackgroundColor->SetSelectedOption(v, false);
		return;
	}
	else if (!strcmp(name, "DisassemblyExecuteColor"))
	{
		u8 v = *((u8*)value);
		c64SettingsDisassemblyExecuteColor = v;
		viewC64->viewC64SettingsMenu->menuItemDisassemblyExecuteColor->SetSelectedOption(v, false);
		return;
	}
	else if (!strcmp(name, "DisassemblyNonExecuteColor"))
	{
		u8 v = *((u8*)value);
		c64SettingsDisassemblyNonExecuteColor = v;
		viewC64->viewC64SettingsMenu->menuItemDisassemblyNonExecuteColor->SetSelectedOption(v, false);
		return;
	}
	else if (!strcmp(name, "MenusColorTheme"))
	{
		u8 v = *((u8*)value);
		c64SettingsMenusColorTheme = v;
		viewC64->viewC64SettingsMenu->menuItemMenusColorTheme->SetSelectedOption(v, false);
		viewC64->colorsTheme->InitColors(c64SettingsMenusColorTheme);
		return;
	}
	else if (!strcmp(name, "PaintGridCharactersColorR"))
	{
		float v = *((float*)value);
		c64SettingsPaintGridCharactersColorR = v;
		viewC64->viewC64SettingsMenu->menuItemPaintGridCharactersColorR->SetValue(v, false);
		
		if (viewC64->debugInterfaceC64)
		{
			viewC64->viewVicEditor->InitPaintGridColors();
		}
		return;
	}
	else if (!strcmp(name, "PaintGridCharactersColorG"))
	{
		float v = *((float*)value);
		c64SettingsPaintGridCharactersColorG = v;
		viewC64->viewC64SettingsMenu->menuItemPaintGridCharactersColorG->SetValue(v, false);
		
		if (viewC64->debugInterfaceC64)
		{
			viewC64->viewVicEditor->InitPaintGridColors();
		}
		return;
	}
	else if (!strcmp(name, "PaintGridCharactersColorB"))
	{
		float v = *((float*)value);
		c64SettingsPaintGridCharactersColorB = v;
		viewC64->viewC64SettingsMenu->menuItemPaintGridCharactersColorB->SetValue(v, false);

		if (viewC64->debugInterfaceC64)
		{
			viewC64->viewVicEditor->InitPaintGridColors();
		}
		return;
	}
	else if (!strcmp(name, "PaintGridCharactersColorA"))
	{
		float v = *((float*)value);
		c64SettingsPaintGridCharactersColorA = v;
		viewC64->viewC64SettingsMenu->menuItemPaintGridCharactersColorA->SetValue(v, false);

		if (viewC64->debugInterfaceC64)
		{
			viewC64->viewVicEditor->InitPaintGridColors();
		}
		return;
	}
	else if (!strcmp(name, "PaintGridPixelsColorR"))
	{
		float v = *((float*)value);
		c64SettingsPaintGridPixelsColorR = v;
		viewC64->viewC64SettingsMenu->menuItemPaintGridPixelsColorR->SetValue(v, false);
		
		if (viewC64->debugInterfaceC64)
		{
			viewC64->viewVicEditor->InitPaintGridColors();
		}
		return;
	}
	else if (!strcmp(name, "PaintGridPixelsColorG"))
	{
		float v = *((float*)value);
		c64SettingsPaintGridPixelsColorG = v;
		viewC64->viewC64SettingsMenu->menuItemPaintGridPixelsColorG->SetValue(v, false);
		
		if (viewC64->debugInterfaceC64)
		{
			viewC64->viewVicEditor->InitPaintGridColors();
		}
		return;
	}
	else if (!strcmp(name, "PaintGridPixelsColorB"))
	{
		float v = *((float*)value);
		c64SettingsPaintGridPixelsColorB = v;
		viewC64->viewC64SettingsMenu->menuItemPaintGridPixelsColorB->SetValue(v, false);

		if (viewC64->debugInterfaceC64)
		{
			viewC64->viewVicEditor->InitPaintGridColors();
		}
		return;
	}
	else if (!strcmp(name, "PaintGridPixelsColorA"))
	{
		float v = *((float*)value);
		c64SettingsPaintGridPixelsColorA = v;
		viewC64->viewC64SettingsMenu->menuItemPaintGridPixelsColorA->SetValue(v, false);

		if (viewC64->debugInterfaceC64)
		{
			viewC64->viewVicEditor->InitPaintGridColors();
		}
		return;
	}
	else if (!strcmp(name, "PaintGridShowZoomLevel"))
	{
		float v = *((float*)value);
		c64SettingsPaintGridShowZoomLevel = v;
		viewC64->viewC64SettingsMenu->menuItemPaintGridShowZoomLevel->SetValue(v, false);
		
		if (viewC64->debugInterfaceC64)
		{
			viewC64->viewVicEditor->InitPaintGridShowZoomLevel();
		}
		return;
	}
	
	LOGError("C64DebuggerSetSetting: unknown setting '%s'", name);
}

//

