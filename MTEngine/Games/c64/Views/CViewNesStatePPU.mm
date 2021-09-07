#include "C64D_Version.h"
#if defined(RUN_NES)

#include "NstApiMachine.hpp"
#include "NstMachine.hpp"
#include "NstApiEmulator.hpp"
#include "NstCpu.hpp"

#include "CViewNesStatePPU.h"
#include "SYS_Main.h"
#include "RES_ResourceManager.h"
#include "CGuiMain.h"
#include "CSlrDataAdapter.h"
#include "CSlrString.h"
#include "SYS_KeyCodes.h"
#include "CViewC64.h"
#include "CViewMemoryMap.h"
#include "C64Tools.h"
#include "CViewC64Screen.h"
#include "NesDebugInterface.h"
#include "CViewC64StateSID.h"
#include "SYS_Threading.h"
#include "CGuiEditHex.h"
#include "VID_ImageBinding.h"
#include "C64SIDFrequencies.h"

// TODO: move me
#include "CViewNesPianoKeyboard.h"

extern Nes::Api::Emulator nesEmulator;

CViewNesStatePPU::CViewNesStatePPU(GLfloat posX, GLfloat posY, GLfloat posZ, GLfloat sizeX, GLfloat sizeY, NesDebugInterface *debugInterface)
: CGuiView(posX, posY, posZ, sizeX, sizeY)
{
	this->name = "CViewNesStatePPU";

	this->debugInterface = debugInterface;
	
	fontSize = 5.0f;
	
	fontBytes = guiMain->fntConsole;
	
	showRegistersOnly = false;
	editHex = new CGuiEditHex(this);
	editHex->isCapitalLetters = false;
	editingRegisterValueIndex = -1;

	this->SetPosition(posX, posY, posZ, sizeX, sizeY);
	
}

void CViewNesStatePPU::SetPosition(GLfloat posX, GLfloat posY, GLfloat posZ, GLfloat sizeX, GLfloat sizeY)
{
	CGuiView::SetPosition(posX, posY, posZ, sizeX, sizeY);
}

void CViewNesStatePPU::SetVisible(bool isVisible)
{
	CGuiElement::SetVisible(isVisible);
}


void CViewNesStatePPU::DoLogic()
{
}

void CViewNesStatePPU::Render()
{
//	if (debugInterface->GetSettingIsWarpSpeed() == true)
//		return;

	this->RenderState(posX, posY, posZ);
}


void CViewNesStatePPU::RenderState(float px, float py, float posZ)
{
//	LOGD("CViewNesStatePPU::RenderState px=%f py=%f", px, py);
	
	float startX = px;
	float startY = py;
	
	float psx = startX;
	float psy = startY;
	float sx = fontSize*16.2f + 1.0f;
	
	char buf[256] = {0};
	sprintf(buf, "PPU");

	fontBytes->BlitText(buf, px, py, -1, fontSize); py += fontSize;
	py += fontSize*0.5f;

	Nes::Core::Machine& machine = nesEmulator;
	u8 regs[0x09];
	for (int i = 0; i < 0x09; i++)
	{
		regs[i] = machine.ppu.registers[i];
	}
	
	psy = py;
	
	py = psy;
	
	for (int i = 0; i < 9; i++)
	{
		int addr = 0x2000 + i;
		if (i == 4)
		{
			py = psy;
			px += fontSize * 8;
		}
		if (i == 8)
		{
			addr = 0x4014;
		}
		sprintf(buf, "%04x %02x", addr, regs[i]);
		fontBytes->BlitText(buf, px, py, -1, fontSize); py += fontSize;
	}
	
	py = psy;
	px += fontSize * 8;
	
	sprintf(buf, "ADDR  %04x", machine.ppu.scroll.address);
	fontBytes->BlitText(buf, px, py, -1, fontSize); py += fontSize;
	sprintf(buf, "LATCH %04x", machine.ppu.scroll.latch);
	fontBytes->BlitText(buf, px, py, -1, fontSize); py += fontSize;
	sprintf(buf, "TOGGL %04x", machine.ppu.scroll.toggle);
	fontBytes->BlitText(buf, px, py, -1, fontSize); py += fontSize;
	sprintf(buf, "XFINE %04x", machine.ppu.scroll.xFine);
	fontBytes->BlitText(buf, px, py, -1, fontSize); py += fontSize;

	/*
//	if (viewC64->currentScreenLayoutId != SCREEN_LAYOUT_NES_MEMORY_MAP)
	{
		py = psy;
		
		double cpuClockFreq = debugInterfaceNes->GetCpuClockFrequency();

		char *space = "    ";
		
		u16 regOffset = 0;
		
		// PULSE 1
		{
			u16 envelopeDivider = regs[0x00 + regOffset] & 0x0F;
			u16 constVolumeOrEnvelopeFlag = (regs[0x00 + regOffset] >> 4) & 0x01;
			u16 lengthCounterHalt = (regs[0x00 + regOffset] >> 5) & 0x01;
			u16 dutyCycle = (regs[0x00 + regOffset] >> 6) & 0x03;
		
			u16 sweepEnabled = (regs[0x01 + regOffset] >> 7) & 0x01;
			u16 sweepDividerPeriod = (regs[0x01 + regOffset] >> 4) & 0x07;
			u16 sweepNegateFlag = (regs[0x01 + regOffset] >> 3) & 0x01;
			u16 sweepShiftCount = regs[0x01 + regOffset] & 0x07;
			
			u16 pulseTimer = ((regs[0x03 + regOffset] & 0x07) << 8) | regs[0x02 + regOffset];
			
			double freqPulse = 0.0;
			
			if (pulseTimer != 0)
			{
				freqPulse = cpuClockFreq / 16.0 / (((double)pulseTimer) + 1.0);
			}
					
			u16 pulseLen = (regs[0x03 + regOffset] >> 3) & 0x1F;
			
			const sid_frequency_t *freq = FrequencyToSidFrequency(freqPulse);

			sprintf(buf, "PULSE 1    %s", freq->name);
			fontBytes->BlitText(buf, px, py, posZ, fontSize); py += fontSize;

			sprintf(buf, "FREQ  %8.2f", freqPulse);
			fontBytes->BlitText(buf, px, py, posZ, fontSize); py += fontSize;

			sprintf(buf, "TIMER     %4x", pulseTimer);
			fontBytes->BlitText(buf, px, py, posZ, fontSize); py += fontSize;

			sprintf(buf, "DUTY      %4x", dutyCycle);
			fontBytes->BlitText(buf, px, py, posZ, fontSize); py += fontSize;
			
			sprintf(buf, "LCH       %4x", lengthCounterHalt);
			fontBytes->BlitText(buf, px, py, posZ, fontSize); py += fontSize;

			sprintf(buf, "CV/EN     %4x", constVolumeOrEnvelopeFlag);
			fontBytes->BlitText(buf, px, py, posZ, fontSize); py += fontSize;

			sprintf(buf, "ENVDIV    %4x", envelopeDivider);
			fontBytes->BlitText(buf, px, py, posZ, fontSize); py += fontSize;

			sprintf(buf, "LEN       %4x", pulseLen);
			fontBytes->BlitText(buf, px, py, posZ, fontSize); py += fontSize;

			sprintf(buf, "SWEEP      %s", (sweepEnabled == 0x01 ? " ON" : "OFF"));
			fontBytes->BlitText(buf, px, py, posZ, fontSize); py += fontSize;

			sprintf(buf, "PERIOD    %4x", sweepDividerPeriod);
			fontBytes->BlitText(buf, px, py, posZ, fontSize); py += fontSize;

			sprintf(buf, "NEGATE    %4x", sweepNegateFlag);
			fontBytes->BlitText(buf, px, py, posZ, fontSize); py += fontSize;

			sprintf(buf, "SHIFT     %4x", sweepShiftCount);
			fontBytes->BlitText(buf, px, py, posZ, fontSize); py += fontSize;
		}
	
*/
	
}


bool CViewNesStatePPU::DoTap(GLfloat x, GLfloat y)
{
	guiMain->LockMutex();
	
	if (editingRegisterValueIndex != -1)
	{
		editHex->FinalizeEntering(MTKEY_ENTER, true);
	}


	
	// check if tap register
	if (showRegistersOnly)
	{
		/*
		float px = posX;
		
		if (x >= posX && x < posX+190)
		{
			float fs2 = fontSize;
			float sx = fs2 * 9;
			
			float plx = posX;	//+ fontSize * 5.0f
			float plex = posX + fontSize * 7.0f;
			float ply = posY + fontSize;
			for (int i = 0; i < 0x10; i++)
			{
				if (x >= plx && x <= plex
					&& y >= ply && y <= ply+fontSize)
				{
					LOGD("CViewNesStatePPU::DoTap: tapped register %02x", i);
					
					editingRegisterValueIndex = i;

					u8 v = debugInterface->GetCiaRegister(editingCIAIndex, editingRegisterValueIndex);
					editHex->SetValue(v, 2);
					
					guiMain->UnlockMutex();
					return true;
				}
				
				ply += fs2;
				
				if (i % 0x08 == 0x07)
				{
					ply = posY + fontSize;
					plx += sx;
					plex += sx;
				}
			}
		}
		 */
	}
	
	showRegistersOnly = !showRegistersOnly;

	guiMain->UnlockMutex();
	return false;
}

void CViewNesStatePPU::GuiEditHexEnteredValue(CGuiEditHex *editHex, u32 lastKeyCode, bool isCancelled)
{
	if (isCancelled)
		return;
	
	/*
	if (editingRegisterValueIndex != -1)
	{
		byte v = editHex->value;
		debugInterface->SetCiaRegister(editingCIAIndex, editingRegisterValueIndex, v);
		
		editHex->SetCursorPos(0);
	}
	 */

}

bool CViewNesStatePPU::KeyDown(u32 keyCode, bool isShift, bool isAlt, bool isControl)
{
	/*
	if (editingRegisterValueIndex != -1)
	{
		if (keyCode == MTKEY_ARROW_UP)
		{
			if (editingRegisterValueIndex > 0)
			{
				editingRegisterValueIndex--;
				u8 v = debugInterface->GetCiaRegister(editingCIAIndex, editingRegisterValueIndex);
				editHex->SetValue(v, 2);
				return true;
			}
		}
		
		if (keyCode == MTKEY_ARROW_DOWN)
		{
			if (editingRegisterValueIndex < 0x0F)
			{
				editingRegisterValueIndex++;
				u8 v = debugInterface->GetCiaRegister(editingCIAIndex, editingRegisterValueIndex);
				editHex->SetValue(v, 2);
				return true;
			}
		}
		
		if (keyCode == MTKEY_ARROW_LEFT)
		{
			if (editHex->cursorPos == 0 && editingRegisterValueIndex > 0x08)
			{
				editingRegisterValueIndex -= 0x08;
				u8 v = debugInterface->GetCiaRegister(editingCIAIndex, editingRegisterValueIndex);
				editHex->SetValue(v, 2);
				return true;
			}
		}
		
		if (keyCode == MTKEY_ARROW_RIGHT)
		{
			if (editHex->cursorPos == 1 && editingRegisterValueIndex < 0x10-0x08)
			{
				editingRegisterValueIndex += 0x08;
				u8 v = debugInterface->GetCiaRegister(editingCIAIndex, editingRegisterValueIndex);
				editHex->SetValue(v, 2);
				return true;
			}
		}
		
		editHex->KeyDown(keyCode);
		return true;
	}
	 */
	return false;
}

bool CViewNesStatePPU::KeyUp(u32 keyCode, bool isShift, bool isAlt, bool isControl)
{
	return false;
}

bool CViewNesStatePPU::SetFocus(bool focus)
{
	return true;
}

void CViewNesStatePPU::RenderFocusBorder()
{
	CGuiView::RenderFocusBorder();
	//
}

#else
// dummy

/*
CViewNesStatePPU::CViewNesStatePPU(GLfloat posX, GLfloat posY, GLfloat posZ, GLfloat sizeX, GLfloat sizeY, NesDebugInterface *debugInterface)
: CGuiView(posX, posY, posZ, sizeX, sizeY)
{
}

void CViewNesStatePPU::SetPosition(GLfloat posX, GLfloat posY, GLfloat posZ, GLfloat sizeX, GLfloat sizeY) {}
void CViewNesStatePPU::DoLogic() {}
void CViewNesStatePPU::Render() {}
void CViewNesStatePPU::RenderState(float px, float py, float posZ, CSlrFont *fontBytes, float fontSize, int ciaId) {}
bool CViewNesStatePPU::DoTap(GLfloat x, GLfloat y) { return false; }
void CViewNesStatePPU::GuiEditHexEnteredValue(CGuiEditHex *editHex, u32 lastKeyCode, bool isCancelled) {}
bool CViewNesStatePPU::KeyDown(u32 keyCode, bool isShift, bool isAlt, bool isControl) { return false; }
bool CViewNesStatePPU::KeyUp(u32 keyCode, bool isShift, bool isAlt, bool isControl) { return false; }
bool CViewNesStatePPU::SetFocus(bool focus) { return true; }
void CViewNesStatePPU::RenderFocusBorder() {}
void CViewNesStatePPU::SetVisible(bool isVisible) {}
void CViewNesStatePPU::AddWaveformData(int pokeyNumber, int v1, int v2, int v3, int v4, short mix) {}
*/

#endif
