#ifndef _C64SETTINGS_STORAGE_H_
#define _C64SETTINGS_STORAGE_H_

#include "SYS_Defs.h"
#include "SYS_Types.h"
#include "CSlrString.h"

// settings that need to be initialized pre-launch
#define C64DEBUGGER_BLOCK_PRELAUNCH		1

// settings that need to be set when emulation is initialized
#define C64DEBUGGER_BLOCK_POSTLAUNCH	2


// settings
extern bool c64SettingsSkipConfig;

extern uint8 c64SettingsDefaultScreenLayoutId;

extern uint8 c64SettingsMemoryValuesStyle;
extern uint8 c64SettingsMemoryMarkersStyle;
extern bool c64SettingsUseMultiTouchInMemoryMap;
extern bool c64SettingsMemoryMapInvertControl;
extern uint8 c64SettingsMemoryMapRefreshRate;

extern uint8 c64SettingsC64Model;

extern uint8 c64SettingsSIDEngineModel;
extern bool c64SettingsMuteSIDOnPause;

extern uint8 c64SettingsJoystickPort;

// startup
extern int c64SettingsWaitOnStartup;
extern CSlrString *c64SettingsPathD64;
extern CSlrString *c64SettingsDefaultD64Folder;
extern CSlrString *c64SettingsPathPRG;
extern CSlrString *c64SettingsDefaultPRGFolder;
extern CSlrString *c64SettingsPathCartridge;
extern CSlrString *c64SettingsDefaultCartridgeFolder;
extern CSlrString *c64SettingsPathSnapshot;
extern CSlrString *c64SettingsDefaultSnapshotsFolder;
extern CSlrString *c64SettingsDefaultMemoryDumpFolder;

extern int c64SettingsJmpOnStartupAddr;

extern int c64SettingsDoubleClickMS;

void C64DebuggerSetSettingInt(char *settingName, int param);
void C64DebuggerSetSettingString(char *settingName, CSlrString *param);


void C64DebuggerStoreSettings();
void C64DebuggerRestoreSettings(uint8 settingsBlockType);

void C64DebuggerReadSettingCustom(char *name, CByteBuffer *byteBuffer);

// set setting
void C64DebuggerSetSetting(char *name, void *value);


#endif
