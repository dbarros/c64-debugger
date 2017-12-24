#ifndef _C64COMMANDLINE_H_
#define _C64COMMANDLINE_H_

class CByteBuffer;

void C64DebuggerParseCommandLine1();
void C64DebuggerParseCommandLine2();

void C64DebuggerPerformStartupTasks();

typedef enum c64d_pass_config_data_e {
	C64D_PASS_CONFIG_DATA_EOF = 0,
	C64D_PASS_CONFIG_DATA_BREAKPOINTS_FILE,
	C64D_PASS_CONFIG_DATA_SYMBOLS_FILE,
	C64D_PASS_CONFIG_DATA_WATCHES_FILE,
	C64D_PASS_CONFIG_DATA_DEBUG_INFO,
	C64D_PASS_CONFIG_DATA_WAIT,
	C64D_PASS_CONFIG_DATA_PATH_TO_PRG,
	C64D_PASS_CONFIG_DATA_PATH_TO_D64,
	C64D_PASS_CONFIG_DATA_PATH_TO_CRT,
	C64D_PASS_CONFIG_DATA_JMP,
	C64D_PASS_CONFIG_DATA_SET_AUTOJMP,
	C64D_PASS_CONFIG_DATA_LOAD_SNAPSHOT,
	C64D_PASS_CONFIG_DATA_LAYOUT,
	C64D_PASS_CONFIG_DATA_FORCE_UNPAUSE,
	C64D_PASS_CONFIG_DATA_AUTO_RUN_DISK,
	C64D_PASS_CONFIG_DATA_ALWAYS_JMP,
	C64D_PASS_CONFIG_DATA_SOUND_DEVICE_OUT
} c64d_pass_config_data_t;


void C64DebuggerPerformNewConfigurationTasks(CByteBuffer *byteBuffer);

#endif

