#include "C64D_Version.h"

#if defined(RUN_ATARI)
extern "C" {
#include "atari.h"
#include "memory.h"
#include "screen.h"
#include "videomode.h"
#include "a-video.h"
#include "a-palette.h"
#include "akey.h"
#include "input.h"
#include "statesav.h"
#include "AtariWrapper.h"
}
#endif

#include "AtariDebugInterface.h"
#include "RES_ResourceManager.h"
#include "CByteBuffer.h"
#include "CSlrString.h"
#include "AtariDataAdapters.h"
#include "SYS_CommandLine.h"
#include "CGuiMain.h"
#include "SYS_KeyCodes.h"
#include "SND_SoundEngine.h"
#include "C64Tools.h"
#include "C64KeyMap.h"
#include "C64SettingsStorage.h"
#include "CViewC64.h"
#include "SND_Main.h"
#include "CDebuggerEmulatorPlugin.h"

#include "CAtariAudioChannel.h"

AtariDebugInterface *debugInterfaceAtari;

#if defined(RUN_ATARI)

AtariDebugInterface::AtariDebugInterface(CViewC64 *viewC64) //, uint8 *memory)
: CDebugInterface(viewC64)
{
	LOGM("AtariDebugInterface: %s init", Atari800_TITLE);
	
	debugInterfaceAtari = this;
	
	CreateScreenData();
	
	audioChannel = NULL;
	
	dataAdapter = new AtariDataAdapter(this);

	isDebugOn = true;
	
	for (int i = 0; i < NUM_ATARI_JOYSTICKS; i++)
	{
		joystickState[i] = JOYPAD_IDLE;
	}
	
	// initialise Atari800 core
	int ret = Atari800_Initialise(&sysArgc, sysArgv);
	if (ret != 1)
	{
		SYS_FatalExit("Atari800 failed, err=%d", ret);
	}

}

extern "C" {
	int Atari800_Exit_Internal(int run_monitor);
}

AtariDebugInterface::~AtariDebugInterface()
{
	debugInterfaceAtari = NULL;
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
	
	Atari800_Exit_Internal(0);
	
//	SYS_Sleep(100);
}

void AtariDebugInterface::RestartEmulation()
{
	Atari800_Exit_Internal(0);

	if (audioChannel)
	{
		SND_RemoveChannel(audioChannel);
		delete audioChannel;
	}
	
	int ret = Atari800_Initialise(&sysArgc, sysArgv);
	if (ret != 1)
	{
		SYS_FatalExit("Atari800 failed, err=%d", ret);
	}

}

int AtariDebugInterface::GetEmulatorType()
{
	return EMULATOR_TYPE_ATARI800;
}

CSlrString *AtariDebugInterface::GetEmulatorVersionString()
{
	return new CSlrString(Atari800_TITLE);
}

CSlrString *AtariDebugInterface::GetPlatformNameString()
{
	return new CSlrString("Atari");
}

void ADI_VIDEO_BlitNormal32(Uint32 *dest, Uint8 *src, int pitch, int width, int height, Uint32 *palette32)
{
		register Uint32 quad;
		register Uint32 *start32 = dest;
		register Uint8 c;
		register int pos;
		while (height > 0) {
			pos = width;
			do {
				pos--;
				c = src[pos];
				quad = palette32[c];
				start32[pos] = quad;
			} while (pos > 0);
			src += Screen_WIDTH;
			start32 += pitch;
			height--;
		}
}

extern "C" {
void SDL_VIDEO_GL_PaletteUpdate(void);
}

void AtariDebugInterface::RunEmulationThread()
{
	LOGM("AtariDebugInterface::RunEmulationThread");
	CDebugInterface::RunEmulationThread();

	this->isRunning = true;
	
	while (true)
	{
		atrd_async_check();

//		INPUT_key_code = PLATFORM_Keyboard();
		//SDL_INPUT_Mouse();
		Atari800_Frame();
		
//		//
//#ifdef USE_UI_BASIC_ONSCREEN_KEYBOARD
//		if (INPUT_key_code == AKEY_KEYB) {
//			Sound_Pause();
//			UI_BASIC_in_kbui = TRUE;
//			INPUT_key_code = UI_BASIC_OnScreenKeyboard(NULL, 0);
//			UI_BASIC_in_kbui = FALSE;
//			switch (INPUT_key_code) {
//				case AKEY_OPTION: INPUT_key_consol &= (~INPUT_CONSOL_OPTION); break;
//				case AKEY_SELECT: INPUT_key_consol &= (~INPUT_CONSOL_SELECT); break;
//				case AKEY_START: INPUT_key_consol &= (~INPUT_CONSOL_START); break;
//			}
//			
//			Sound_Continue();
//		}
//#endif

		
		
		// update screen
		this->LockRenderScreenMutex();
		
		Uint8 *screenBuffer = (Uint8 *)Screen_atari;// + Screen_WIDTH * VIDEOMODE_src_offset_top + VIDEOMODE_src_offset_left;
		
		// dest screen width is 512
		
		uint8 *srcScreenPtr = screenBuffer;
		uint8 *destScreenPtr = (uint8 *)this->screenImage->resultData;
		
		int screenHeight = this->GetScreenSizeY();
		
		int *palette = SDL_PALETTE_tab[VIDEOMODE_MODE_NORMAL].palette;

		int superSample = this->screenSupersampleFactor;
		
		if (superSample == 1)
		{
			for (int y = 0; y < screenHeight; y++)
			{
				for (int x = 0; x < this->GetScreenSizeX(); x++)
				{
					byte v = *srcScreenPtr++;

					int i  = v;
					u8 r, g, b;

					u32 rgb = palette[i];
					r = (rgb & 0x00ff0000) >> 16;
					g = (rgb & 0x0000ff00) >> 8;
					b = (rgb & 0x000000ff) >> 0;

					*destScreenPtr++ = r;
					*destScreenPtr++ = g;
					*destScreenPtr++ = b;
					*destScreenPtr++ = 255;
				}
				
				destScreenPtr += (512-384)*4;
			}
		}
		else
		{
			for (int y = 0; y < screenHeight; y++)
			{
				for (int j = 0; j < superSample; j++)
				{
					uint8 *pScreenPtrSrc = srcScreenPtr;
					uint8 *pScreenPtrDest = destScreenPtr;
					
					for (int x = 0; x < this->GetScreenSizeX(); x++)
					{
						byte v = *pScreenPtrSrc++;
						
						int i  = v;
						u8 r, g, b;
						
						u32 rgb = palette[i];
						r = (rgb & 0x00ff0000) >> 16;
						g = (rgb & 0x0000ff00) >> 8;
						b = (rgb & 0x000000ff) >> 0;
						
						for (int i = 0; i < superSample; i++)
						{
							*pScreenPtrDest++ = r;
							*pScreenPtrDest++ = g;
							*pScreenPtrDest++ = b;
							*pScreenPtrDest++ = 255;
						}
					}
					destScreenPtr += (512)*superSample*4;
				}
				
				srcScreenPtr += 384;
			}
		}
		
		this->UnlockRenderScreenMutex();

		this->DoFrame();
				
		
////		for (int i = 0; i < 256; i++)
////		{
////			LOGD("SDL_Palette_buffer.bpp32[%d]=%d", i, SDL_PALETTE_buffer.bpp32[i]);
////		}
//		
//		ADI_VIDEO_BlitNormal32((Uint32*)this->screenImage->resultData, screen, VIDEOMODE_actual_width, VIDEOMODE_src_width, VIDEOMODE_src_height, SDL_PALETTE_buffer.bpp32);
		
		//	if (bpp_32)
		//		SDL_VIDEO_BlitNormal32((Uint32*)dest, screen, VIDEOMODE_actual_width, VIDEOMODE_src_width, VIDEOMODE_src_height, SDL_PALETTE_buffer.bpp32);
		//	else {
		//		int pitch;
		//		if (VIDEOMODE_actual_width & 0x01)
		//			pitch = VIDEOMODE_actual_width / 2 + 1;
		//		else
		//			pitch = VIDEOMODE_actual_width / 2;
		//		SDL_VIDEO_BlitNormal16((Uint32*)dest, screen, pitch, VIDEOMODE_src_width, VIDEOMODE_src_height, SDL_PALETTE_buffer.bpp16);
		//	}
		//


	}
	
	audioChannel->Stop();
}


void AtariDebugInterface::DoFrame()
{
	CDebugInterface::DoFrame();
}

//	UBYTE MEMORY_mem[65536 + 2];

void AtariDebugInterface::SetByte(uint16 addr, uint8 val)
{
	MEMORY_PutByte(addr, val);
//	MEMORY_mem[addr] = val;
}

uint8 AtariDebugInterface::GetByte(uint16 addr)
{
	return MEMORY_SafeGetByte(addr);
	
//	return MEMORY_mem[addr];
}

void AtariDebugInterface::GetMemory(uint8 *buffer, int addrStart, int addrEnd)
{
	int addr;
	BYTE *bufPtr = buffer + addrStart;
	for (addr = addrStart; addr < addrEnd; addr++)
	{
		*bufPtr++ = GetByte(addr);
	}

}

extern "C" {
	int Atari800_GetPC();
}

int AtariDebugInterface::GetCpuPC()
{
	return Atari800_GetPC();
}

void AtariDebugInterface::GetWholeMemoryMap(uint8 *buffer)
{
	for (int addr = 0; addr < 0x10000; addr++)
	{
		buffer[addr] = GetByte(addr);
	}
}

void AtariDebugInterface::GetWholeMemoryMapFromRam(uint8 *buffer)
{
	for (int addr = 0; addr < 0x10000; addr++)
	{
		buffer[addr] = MEMORY_mem[addr];
	}
}

//
extern "C" {
	void Atari800_GetCpuRegs(UWORD *ret_CPU_regPC,
							 UBYTE *ret_CPU_regA,
							 UBYTE *ret_CPU_regX,
							 UBYTE *ret_CPU_regY,
							 UBYTE *ret_CPU_regP,						/* Processor Status Byte (Partial) */
							 UBYTE *ret_CPU_regS,
							 UBYTE *ret_CPU_IRQ);
}

void AtariDebugInterface::GetCpuRegs(u16 *PC,
				u8 *A,
				u8 *X,
				u8 *Y,
				u8 *P,						/* Processor Status Byte (Partial) */
				u8 *S,
				u8 *IRQ)
{
	Atari800_GetCpuRegs(PC, A, X, Y, P, S, IRQ);
}


//
int AtariDebugInterface::GetScreenSizeX()
{
	return ATARI_DEFAULT_SCREEN_WIDTH;
}

int AtariDebugInterface::GetScreenSizeY()
{
	return ATARI_DEFAULT_SCREEN_HEIGHT;
}

//
void AtariDebugInterface::SetDebugMode(uint8 debugMode)
{
	LOGD("AtariDebugInterface::SetDebugMode: debugMode=%d", debugMode);
	atrd_debug_mode = debugMode;
	
	CDebugInterface::SetDebugMode(debugMode);
}

uint8 AtariDebugInterface::GetDebugMode()
{
	this->debugMode = atrd_debug_mode;
	return debugMode;
}

extern "C" {
	void c64d_atari_set_cpu_pc(u16 addr);
}

// make jmp without resetting CPU depending on dataAdapter
void AtariDebugInterface::MakeJmpNoReset(CSlrDataAdapter *dataAdapter, uint16 addr)
{
	this->LockMutex();
	
	c64d_atari_set_cpu_pc(addr);
	
	this->UnlockMutex();
}

// make jmp and reset CPU
void AtariDebugInterface::MakeJmpAndReset(uint16 addr)
{
	LOGTODO("AtariDebugInterface::MakeJmpAndReset");
}

int AtariDebugInterface::MapMTKeyToAKey(uint32 mtKeyCode, int shiftctrl, int key_control)
{
	switch(mtKeyCode)
	{
		case 'A':
			return AKEY_A;
		case 'B':
			return AKEY_B;
		case 'C':
			return AKEY_C;
		case 'D':
			return AKEY_D;
		case 'E':
			return AKEY_E;
		case 'F':
			return AKEY_F;
		case 'G':
			return AKEY_G;
		case 'H':
			return AKEY_H;
		case 'I':
			return AKEY_I;
		case 'J':
			return AKEY_J;
		case 'K':
			return AKEY_K;
		case 'L':
			return AKEY_L;
		case 'M':
			return AKEY_M;
		case 'N':
			return AKEY_N;
		case 'O':
			return AKEY_O;
		case 'P':
			return AKEY_P;
		case 'Q':
			return AKEY_Q;
		case 'R':
			return AKEY_R;
		case 'S':
			return AKEY_S;
		case 'T':
			return AKEY_T;
		case 'U':
			return AKEY_U;
		case 'V':
			return AKEY_V;
		case 'W':
			return AKEY_W;
		case 'X':
			return AKEY_X;
		case 'Y':
			return AKEY_Y;
		case 'Z':
			return AKEY_Z;
		case ':':
			return AKEY_COLON;
		case '!':
			return AKEY_EXCLAMATION;
		case '@':
			return AKEY_AT;
		case '#':
			return AKEY_HASH;
		case '$':
			return AKEY_DOLLAR;
		case '%':
			return AKEY_PERCENT;
		case '^':
			return AKEY_CARET;
		case '&':
			return AKEY_AMPERSAND;
		case '*':
			return AKEY_ASTERISK;
		case '(':
			return AKEY_PARENLEFT;
		case ')':
			return AKEY_PARENRIGHT;
		case '+':
			return AKEY_PLUS;
		case '_':
			return AKEY_UNDERSCORE;
		case '"':
			return AKEY_DBLQUOTE;
		case '?':
			return AKEY_QUESTION;
		case '<':
			return AKEY_LESS;
		case '>':
			return AKEY_GREATER;
		case 'a':
			return AKEY_a;
		case 'b':
			return AKEY_b;
		case 'c':
			return AKEY_c;
		case 'd':
			return AKEY_d;
		case 'e':
			return AKEY_e;
		case 'f':
			return AKEY_f;
		case 'g':
			return AKEY_g;
		case 'h':
			return AKEY_h;
		case 'i':
			return AKEY_i;
		case 'j':
			return AKEY_j;
		case 'k':
			return AKEY_k;
		case 'l':
			return AKEY_l;
		case 'm':
			return AKEY_m;
		case 'n':
			return AKEY_n;
		case 'o':
			return AKEY_o;
		case 'p':
			return AKEY_p;
		case 'q':
			return AKEY_q;
		case 'r':
			return AKEY_r;
		case 's':
			return AKEY_s;
		case 't':
			return AKEY_t;
		case 'u':
			return AKEY_u;
		case 'v':
			return AKEY_v;
		case 'w':
			return AKEY_w;
		case 'x':
			return AKEY_x;
		case 'y':
			return AKEY_y;
		case 'z':
			return AKEY_z;
		case ';':
			return AKEY_SEMICOLON;
		case '0':
			return AKEY_0;
		case '1':
			return AKEY_1;
		case '2':
			return AKEY_2;
		case '3':
			return AKEY_3;
		case '4':
			return AKEY_4;
		case '5':
			return AKEY_5;
		case '6':
			return AKEY_6;
		case '7':
			return AKEY_7;
		case '8':
			return AKEY_8;
		case '9':
			return AKEY_9;
		case ',':
			return AKEY_COMMA;
		case '.':
			return AKEY_FULLSTOP;
		case '=':
			return AKEY_EQUAL;
		case '-':
			return AKEY_MINUS;
		case '\'':
			return AKEY_QUOTE;
		case '/':
			return AKEY_SLASH;
		case '\\':
			return AKEY_BACKSLASH;
		case '[':
			return AKEY_BRACKETLEFT;
		case ']':
			return AKEY_BRACKETRIGHT;
		case '|':
			return AKEY_BAR;
		case MTKEY_F6:
			return AKEY_HELP ^ shiftctrl;
		case MTKEY_PAGE_DOWN:
			return AKEY_F2 | AKEY_SHFT;
		case MTKEY_PAGE_UP:
			return AKEY_F1 | AKEY_SHFT;
		case MTKEY_HOME:
			return AKEY_CLEAR;	//key_control ? AKEY_LESS|shiftctrl :

		case MTKEY_SPACEBAR:
			return AKEY_SPACE ^ shiftctrl;
		case MTKEY_BACKSPACE:
			return AKEY_BACKSPACE|shiftctrl;
		case MTKEY_ENTER:
			return AKEY_RETURN ^ shiftctrl;
		case MTKEY_ARROW_LEFT:
			return (INPUT_key_shift ? AKEY_PLUS : AKEY_LEFT) ^ shiftctrl;
		case MTKEY_ARROW_RIGHT:
			return (INPUT_key_shift ? AKEY_ASTERISK : AKEY_RIGHT) ^ shiftctrl;
		case MTKEY_ARROW_UP:
			return (INPUT_key_shift ? AKEY_MINUS : AKEY_UP) ^ shiftctrl;
		case MTKEY_ARROW_DOWN:
			return (INPUT_key_shift ? AKEY_EQUAL : AKEY_DOWN) ^ shiftctrl;

			
		default:
			LOGError("MapMTKeyToAKey: unknown mtKeyCode %d", mtKeyCode);
			return AKEY_NONE;
	}

}

int key_control = 0;

// keyboard & joystick mapper
void AtariDebugInterface::KeyboardDown(uint32 mtKeyCode)
{
	LOGD("AtariDebugInterface::KeyboardDown: mtKeyCode=%04x INPUT_key_consol=%02x", mtKeyCode, INPUT_key_consol);

	for (std::list<CDebuggerEmulatorPlugin *>::iterator it = this->plugins.begin(); it != this->plugins.end(); it++)
	{
		CDebuggerEmulatorPlugin *plugin = *it;
		mtKeyCode = plugin->KeyDown(mtKeyCode);
		
		if (mtKeyCode == 0)
			return;
	}
	
	

	int shiftctrl = 0;

	if (mtKeyCode == MTKEY_LSHIFT || mtKeyCode == MTKEY_RSHIFT)
	{
		INPUT_key_shift = 1;
	}

	if (mtKeyCode == MTKEY_LCONTROL || mtKeyCode == MTKEY_RCONTROL)
	{
		key_control = 1;
	}

	//	/* SHIFT STATE */
	//	if ((kbhits[SDLK_LSHIFT]) || (kbhits[SDLK_RSHIFT]))
	//		INPUT_key_shift = 1;
	//	else
	//		INPUT_key_shift = 0;
	//
	//	/* CONTROL STATE */
	//	if ((kbhits[SDLK_LCTRL]) || (kbhits[SDLK_RCTRL]))
	//		key_control = 1;
	//	else
	//		key_control = 0;


	// OPTION / SELECT / START keys
	if (mtKeyCode == MTKEY_F2)
	{
		INPUT_key_consol &= ~INPUT_CONSOL_OPTION;
		return;
	}

	if (mtKeyCode == MTKEY_F3)
	{
		INPUT_key_consol &= ~INPUT_CONSOL_SELECT;
		return;
	}
	
	if (mtKeyCode == MTKEY_F4)
	{
		INPUT_key_consol &= ~INPUT_CONSOL_START;
		return;
	}
	
	if (INPUT_key_shift)
		shiftctrl ^= AKEY_SHFT;

	int akey = MapMTKeyToAKey(mtKeyCode, shiftctrl, key_control);
	
	INPUT_key_code = akey;
}

void AtariDebugInterface::KeyboardUp(uint32 mtKeyCode)
{
	LOGD("AtariDebugInterface::KeyboardUp: mtKeyCode=%04x INPUT_key_consol=%02x", mtKeyCode, INPUT_key_consol);
	
	for (std::list<CDebuggerEmulatorPlugin *>::iterator it = this->plugins.begin(); it != this->plugins.end(); it++)
	{
		CDebuggerEmulatorPlugin *plugin = *it;
		mtKeyCode = plugin->KeyUp(mtKeyCode);
		
		if (mtKeyCode == 0)
			return;
	}
	
	
	// OPTION / SELECT / START keys
	if (mtKeyCode == MTKEY_F2)
	{
		INPUT_key_consol |= INPUT_CONSOL_OPTION;
		return;
	}
	
	if (mtKeyCode == MTKEY_F3)
	{
		INPUT_key_consol |= INPUT_CONSOL_SELECT;
		return;
	}
	
	if (mtKeyCode == MTKEY_F4)
	{
		INPUT_key_consol |= INPUT_CONSOL_START;
		return;
	}
	
	
	INPUT_key_code = AKEY_NONE;

	if (mtKeyCode == MTKEY_LSHIFT || mtKeyCode == MTKEY_RSHIFT)
	{
		INPUT_key_shift = 0;
	}
	
	if (mtKeyCode == MTKEY_LCONTROL || mtKeyCode == MTKEY_RCONTROL)
	{
		key_control = 0;
	}
	
}

void AtariDebugInterface::JoystickDown(int port, uint32 axis)
{
	LOGD("AtariDebugInterface::JoystickDown: %d %d", port, axis);

	this->joystickState[port-1] |= axis;
}

void AtariDebugInterface::JoystickUp(int port, uint32 axis)
{
	LOGD("AtariDebugInterface::JoystickUp: %d %d", port, axis);
	
	this->joystickState[port-1] &= ~axis;
}

//
extern "C" {
	void CPU_Reset(void);
	void Colours_SetVideoSystem(int mode);
}
void AtariDebugInterface::Reset()
{
	LOGM("AtariDebugInterface::Reset");
	CPU_Reset();

}

void AtariDebugInterface::HardReset()
{
	LOGM("AtariDebugInterface::HardReset");
	Atari800_Coldstart();
}

extern "C" {
	int BINLOAD_Loader(const char *filename);
	int AFILE_OpenFile(const char *filename, int reboot, int diskno, int readonly);
}

bool AtariDebugInterface::LoadExecutable(char *fullFilePath)
{
	LOGM("AtariDebugInterface::LoadExecutable: %s", fullFilePath);

	int ret = BINLOAD_Loader(fullFilePath);
	if (ret != 0)
		return false;
	
//	Colours_SetVideoSystem(Atari800_tv_mode);

	return true;
}

bool AtariDebugInterface::MountDisk(char *fullFilePath, int diskNo, bool readOnly)
{
	int reboot = 0;
	int retType = AFILE_OpenFile(fullFilePath, reboot, diskNo, readOnly);

//	if (retType != ???)
//		return false;
	
//	Colours_SetVideoSystem(Atari800_tv_mode);
	
	return true;
}

bool AtariDebugInterface::InsertCartridge(char *fullFilePath, bool readOnly)
{
	int reboot = 1;
	int retType = AFILE_OpenFile(fullFilePath, reboot, 0, readOnly);
	
//	if (retType != ??)
//		return false;
	
//	Colours_SetVideoSystem(Atari800_tv_mode);
	
	return true;
}

bool AtariDebugInterface::AttachTape(char *fullFilePath, bool readOnly)
{
	int reboot = 1;
	int retType = AFILE_OpenFile(fullFilePath, reboot, 0, readOnly);
	
//	if (retType != ???)
//		return false;
	
//	Colours_SetVideoSystem(Atari800_tv_mode);

	return true;
}

extern "C" {
	void atrd_async_load_snapshot(char *filePath);
	void atrd_async_save_snapshot(char *filePath);
}

bool AtariDebugInterface::LoadFullSnapshot(char *filePath)
{
	guiMain->LockMutex();
	this->LockMutex();
	
	atrd_async_load_snapshot(filePath);
	
	this->UnlockMutex();
	guiMain->UnlockMutex();
	return true;
}

void AtariDebugInterface::SaveFullSnapshot(char *filePath)
{
	LOGD("AtariDebugInterface::SaveFullSnapshot: %s", filePath);
	guiMain->LockMutex();
	this->LockMutex();
	
	atrd_async_save_snapshot(filePath);

	this->UnlockMutex();
	guiMain->UnlockMutex();
}


void AtariDebugInterface::SetVideoSystem(u8 videoSystem)
{
	LOGD("AtariDebugInterface::SetVideoSystem: %d", videoSystem);
	if (videoSystem == ATARI_VIDEO_SYSTEM_PAL)
	{
		Atari800_SetTVMode(Atari800_TV_PAL);
	}
	else
	{
		Atari800_SetTVMode(Atari800_TV_NTSC);
	}
	Atari800_InitialiseMachine();
}

static struct {
	int type;
	int ram;
	int basic;
	int leds;
	int f_keys;
	int jumper;
	int game;
	int keyboard;
} const atariMachinesDefs[] = {
	{ Atari800_MACHINE_800, 16, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE },
	{ Atari800_MACHINE_800, 48, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE },
	{ Atari800_MACHINE_XLXE, 64, FALSE, TRUE, TRUE, TRUE, FALSE, FALSE },
	{ Atari800_MACHINE_XLXE, 16, TRUE, FALSE, FALSE, FALSE, FALSE, FALSE },
	{ Atari800_MACHINE_XLXE, 64, TRUE, FALSE, FALSE, FALSE, FALSE, FALSE },
	{ Atari800_MACHINE_XLXE, 128, TRUE, FALSE, FALSE, FALSE, FALSE, FALSE },
	{ Atari800_MACHINE_XLXE, 64, TRUE, FALSE, FALSE, FALSE, TRUE, TRUE },
	{ Atari800_MACHINE_5200, 16, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE }
};

void AtariDebugInterface::SetMachineType(u8 machineType)
{
	Atari800_machine_type = atariMachinesDefs[machineType].type;
	MEMORY_ram_size = atariMachinesDefs[machineType].ram;
	Atari800_builtin_basic = atariMachinesDefs[machineType].basic;
	Atari800_keyboard_leds = atariMachinesDefs[machineType].leds;
	Atari800_f_keys = atariMachinesDefs[machineType].f_keys;
	if (!atariMachinesDefs[machineType].jumper)
		Atari800_jumper = FALSE;
	Atari800_builtin_game = atariMachinesDefs[machineType].game;
	if (!atariMachinesDefs[machineType].keyboard)
		Atari800_keyboard_detached = FALSE;
	Atari800_InitialiseMachine();
}

void AtariDebugInterface::SetRamSizeOption(u8 ramSizeOption)
{
	if (Atari800_machine_type == Atari800_MACHINE_800)
	{
		switch(ramSizeOption)
		{
			case 0:
			default:
				MEMORY_ram_size = 8;
				break;
			case 1:
				MEMORY_ram_size = 16;
				break;
			case 2:
				MEMORY_ram_size = 24;
				break;
			case 3:
				MEMORY_ram_size = 32;
				break;
			case 4:
				MEMORY_ram_size = 40;
				break;
			case 5:
				MEMORY_ram_size = 48;
				break;
			case 6:
				MEMORY_ram_size = 52;
				break;
		}
	}
	else if (Atari800_machine_type == Atari800_MACHINE_XLXE)
	{
		switch(ramSizeOption)
		{
			case 0:
			default:
				MEMORY_ram_size = 16;
				break;
			case 1:
				MEMORY_ram_size = 32;
				break;
			case 2:
				MEMORY_ram_size = 48;
				break;
			case 3:
				MEMORY_ram_size = 64;
				break;
			case 4:
				MEMORY_ram_size = 128;
				break;
			case 5:
				MEMORY_ram_size = 192;
				break;
			case 6:
				MEMORY_ram_size = MEMORY_RAM_320_RAMBO;
				break;
			case 7:
				MEMORY_ram_size = MEMORY_RAM_320_COMPY_SHOP;
				break;
			case 8:
				MEMORY_ram_size = 576;
				break;
			case 9:
				MEMORY_ram_size = 1088;
				break;
		}
	}
	else if (Atari800_machine_type == Atari800_MACHINE_5200)
	{
		MEMORY_ram_size = 16;
	}

}

#else
// dummy interface for atari

AtariDebugInterface::AtariDebugInterface(CViewC64 *viewC64) //, uint8 *memory)
: CDebugInterface(viewC64)
{
}
AtariDebugInterface::~AtariDebugInterface() {}
void AtariDebugInterface::RestartEmulation() {}
int AtariDebugInterface::GetEmulatorType() { return EMULATOR_TYPE_ATARI800; }
CSlrString *AtariDebugInterface::GetEmulatorVersionString() { return NULL; }
CSlrString *AtariDebugInterface::GetPlatformNameString() { return NULL; }
void AtariDebugInterface::RunEmulationThread() {}
void AtariDebugInterface::DoFrame() {}
void AtariDebugInterface::SetByte(uint16 addr, uint8 val) {}
uint8 AtariDebugInterface::GetByte(uint16 addr) { return 0; }
void AtariDebugInterface::GetMemory(uint8 *buffer, int addrStart, int addrEnd) {}
int AtariDebugInterface::GetCpuPC() { return -1; }
void AtariDebugInterface::GetWholeMemoryMap(uint8 *buffer) {}
void AtariDebugInterface::GetWholeMemoryMapFromRam(uint8 *buffer) {}
void AtariDebugInterface::GetCpuRegs(u16 *PC, u8 *A,u8 *X, u8 *Y, u8 *P,u8 *S,u8 *IRQ) {}
int AtariDebugInterface::GetScreenSizeX() { return -1; }
int AtariDebugInterface::GetScreenSizeY() { return -1; }
void AtariDebugInterface::SetDebugMode(uint8 debugMode) {}
uint8 AtariDebugInterface::GetDebugMode() { return 0; }
void AtariDebugInterface::MakeJmpNoReset(CSlrDataAdapter *dataAdapter, uint16 addr) {}
void AtariDebugInterface::MakeJmpAndReset(uint16 addr) {}
int AtariDebugInterface::MapMTKeyToAKey(uint32 mtKeyCode, int shiftctrl, int key_control) { return -1; }
void AtariDebugInterface::KeyboardDown(uint32 mtKeyCode) {}
void AtariDebugInterface::KeyboardUp(uint32 mtKeyCode) {}
void AtariDebugInterface::JoystickDown(int port, uint32 axis) {}
void AtariDebugInterface::JoystickUp(int port, uint32 axis) {}
void AtariDebugInterface::Reset() {}
void AtariDebugInterface::HardReset() {}
bool AtariDebugInterface::LoadExecutable(char *fullFilePath) { return false; }
bool AtariDebugInterface::MountDisk(char *fullFilePath, int diskNo, bool readOnly) { return false; }
bool AtariDebugInterface::InsertCartridge(char *fullFilePath, bool readOnly) { return false; }
bool AtariDebugInterface::AttachTape(char *fullFilePath, bool readOnly) { return false; }
bool AtariDebugInterface::LoadFullSnapshot(char *filePath) { return false; }
void AtariDebugInterface::SaveFullSnapshot(char *filePath) {}
void AtariDebugInterface::SetVideoSystem(u8 videoSystem) {}
void AtariDebugInterface::SetMachineType(u8 machineType) {}
void AtariDebugInterface::SetRamSizeOption(u8 ramSizeOption) {}

#endif
