extern "C" {
#include "drivetypes.h"
}
#include "CViewDrive1541StateVIA.h"
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
#include "C64DebugInterface.h"
#include "SYS_Threading.h"
#include "CGuiEditHex.h"
#include "VID_ImageBinding.h"

CViewDrive1541StateVIA::CViewDrive1541StateVIA(GLfloat posX, GLfloat posY, GLfloat posZ, GLfloat sizeX, GLfloat sizeY, C64DebugInterface *debugInterface)
: CGuiView(posX, posY, posZ, sizeX, sizeY)
{
	this->name = "CViewDrive1541StateVIA";
	
	this->debugInterface = debugInterface;
	
	fontSize = 5.0f;
	
	fontBytes = guiMain->fntConsole;
	
	renderVIA1 = true;
	renderVIA2 = true;
	renderDriveLED = true;
	isVertical = false;
	
	showRegistersOnly = false;
	editHex = new CGuiEditHex(this);
	editHex->isCapitalLetters = false;
	editingRegisterValueIndex = -1;
	editingVIAIndex = -1;
	
	this->SetPosition(posX, posY, posZ, sizeX, sizeY);
}

void CViewDrive1541StateVIA::SetPosition(GLfloat posX, GLfloat posY, GLfloat posZ, GLfloat sizeX, GLfloat sizeY)
{
	CGuiView::SetPosition(posX, posY, posZ, sizeX, sizeY);
}

void CViewDrive1541StateVIA::DoLogic()
{
}

void CViewDrive1541StateVIA::Render()
{
//	if (debugInterface->GetSettingIsWarpSpeed() == true)
//		return;
	
	int driveId = 0;
	this->RenderStateDrive1541(posX, posY, posZ, fontBytes, fontSize, driveId, renderVIA1, renderVIA2, renderDriveLED, isVertical);
}

extern "C" {
	BYTE c64d_via1d1541_peek(drive_context_t *ctxptr, WORD addr);
	BYTE c64d_via2d_peek(drive_context_t *ctxptr, WORD addr);
};

#define VIA_PRB         0  /* Port B */
#define VIA_PRA         1  /* Port A */
#define VIA_DDRB        2  /* Data direction register for port B */
#define VIA_DDRA        3  /* Data direction register for port A */

#define VIA_T1CL        4  /* Timer 1 count low */
#define VIA_T1CH        5  /* Timer 1 count high */
#define VIA_T1LL        6  /* Timer 1 latch low */
#define VIA_T1LH        7  /* Timer 1 latch high */
#define VIA_T2CL        8  /* Timer 2 count low - read only */
#define VIA_T2LL        8  /* Timer 2 latch low - write only */
#define VIA_T2CH        9  /* Timer 2 latch/count high */

#define VIA_SR          10 /* Serial port shift register */
#define VIA_ACR         11 /* Auxiliary control register */
#define VIA_PCR         12 /* Peripheral control register */

#define VIA_IFR         13 /* Interrupt flag register */
#define VIA_IER         14 /* Interrupt control register */

void CViewDrive1541StateVIA::RenderStateDrive1541(float posX, float posY, float posZ, CSlrFont *fontBytes, float fontSize,
												  int driveId, 
												 bool renderVia1, bool renderVia2, bool renderDriveLed,
												 bool isVertical)
{
	drive_context_t *drivectx = drive_context[driveId];

	char buf[256];
	float px = posX;
	float py = posY;
	byte v1, v2;
	byte counterlo;
	byte counterhi;
	byte latchlo;
	byte latchhi;
	
	if (showRegistersOnly)
	{
		float fs2 = fontSize;
		
		if (renderVia1)
		{
			sprintf(buf, "VIA 1:");
			fontBytes->BlitText(buf, px, py, posZ, fontSize); py += fontSize;
			
			float plx = px;
			float ply = py;
			
			for (int i = 0; i < 0x0F; i++)
			{
				if (editingVIAIndex == 1 && editingRegisterValueIndex == i)
				{
					sprintf(buf, "18%02x", i);
					fontBytes->BlitText(buf, plx, ply, posZ, fs2);
					fontBytes->BlitTextColor(editHex->textWithCursor, plx + fontSize*5.0f, ply, posZ, fontSize, 1.0f, 1.0f, 1.0f, 1.0f);
				}
				else
				{
					u8 v = c64d_via1d1541_peek(drivectx, i);
					sprintf(buf, "18%02x %02x", i, v);
					fontBytes->BlitText(buf, plx, ply, posZ, fs2);
				}
				
				ply += fs2;
				
				if (i % 0x08 == 0x07)
				{
					ply = py;
					plx += fs2 * 9;
				}
			}
			
			if (isVertical)
			{
			}
			else
			{
				py = posY;
				px = posX + 120;
			}
		}

		if (renderVia2)
		{
			sprintf(buf, "VIA 2:");
			fontBytes->BlitText(buf, px, py, posZ, fontSize); py += fontSize;
			
			float plx = px;
			float ply = py;
			
			for (int i = 0; i < 0x0F; i++)
			{
				if (editingVIAIndex == 2 && editingRegisterValueIndex == i)
				{
					sprintf(buf, "1C%02x", i);
					fontBytes->BlitText(buf, plx, ply, posZ, fs2);
					fontBytes->BlitTextColor(editHex->textWithCursor, plx + fontSize*5.0f, ply, posZ, fontSize, 1.0f, 1.0f, 1.0f, 1.0f);
				}
				else
				{
					u8 v = c64d_via2d_peek(drivectx, i);
					sprintf(buf, "1C%02x %02x", i, v);
					fontBytes->BlitText(buf, plx, ply, posZ, fs2);
				}
				
				ply += fs2;
				
				if (i % 0x08 == 0x07)
				{
					ply = py;
					plx += fs2 * 9;
				}
			}
		}

	}
	else
	{
		if (renderVia1)
		{
			sprintf(buf, "VIA 1:");
			fontBytes->BlitText(buf, px, py, posZ, fontSize); py += fontSize;
			
			v1 = c64d_via1d1541_peek(drivectx, 0x1800);
			v2 = c64d_via1d1541_peek(drivectx, 0x1801);
			sprintf(buf, " PRB: %02x PRA: %02x", v1, v2);
			fontBytes->BlitText(buf, px, py, posZ, fontSize); py += fontSize;
			
			
			counterlo = c64d_via1d1541_peek(drivectx, 0x1804);
			counterhi = c64d_via1d1541_peek(drivectx, 0x1805);
			latchlo = c64d_via1d1541_peek(drivectx, 0x1806);
			latchhi = c64d_via1d1541_peek(drivectx, 0x1807);
			sprintf(buf, " Timer Counter: %02x%02x", counterhi, counterlo); // Latch: %02x%02x", counterhi, counterlo, latchlo, latchhi);
			fontBytes->BlitText(buf, px, py, posZ, fontSize); py += fontSize;
			
			//	counterlo = c64d_via1d1541_peek(drivectx, 0x1804);
			//	counterhi = c64d_via1d1541_peek(drivectx, 0x1805);
			//	sprintf(buf, " Timer 2 Counter: %02x%02x", counterhi, counterlo);
			//	fontBytes->BlitText(buf, px, py, posZ, fontSize); py += fontSize;
			
			v1 = c64d_via1d1541_peek(drivectx, 0x180B);
			v2 = c64d_via1d1541_peek(drivectx, 0x180C);
			
			if (isVertical)
			{
				sprintf(buf, " ACR: %02x PCR: %02x", v1, v2);
				fontBytes->BlitText(buf, px, py, posZ, fontSize); py += fontSize;
			}
			else
			{
				sprintf(buf, " ACR: %02x", v1);
				fontBytes->BlitText(buf, px, py, posZ, fontSize); py += fontSize;
				
				sprintf(buf, " PCR: %02x", v2);
				fontBytes->BlitText(buf, px, py, posZ, fontSize); py += fontSize;
			}
			
			v1 = c64d_via1d1541_peek(drivectx, 0x180D);
			v2 = c64d_via1d1541_peek(drivectx, 0x180E);
			sprintf(buf, " IFR: %02x IER: %02x", v1, v2);
			fontBytes->BlitText(buf, px, py, posZ, fontSize); py += fontSize;
			
			
			//	TODO: pending interrupts & enabled interrupts
			
			
			if (isVertical)
			{
			}
			else
			{
				py = posY;
				px = posX + 120;
			}
		}
		
		if (renderVia2)
		{
			sprintf(buf, "VIA 2:");
			fontBytes->BlitText(buf, px, py, posZ, fontSize); py += fontSize;
			v1 = c64d_via2d_peek(drivectx, 0x1C00);
			v2 = c64d_via2d_peek(drivectx, 0x1C01);
			sprintf(buf, " PRB: %02x PRA: %02x", v1, v2);
			fontBytes->BlitText(buf, px, py, posZ, fontSize); py += fontSize;
			
			
			counterlo = c64d_via2d_peek(drivectx, 0x1C04);
			counterhi = c64d_via2d_peek(drivectx, 0x1C05);
			latchlo = c64d_via2d_peek(drivectx, 0x1C06);
			latchhi = c64d_via2d_peek(drivectx, 0x1C07);
			sprintf(buf, " Timer Counter: %02x%02x", counterhi, counterlo); // Latch: %02x%02x", counterhi, counterlo, latchlo, latchhi);
			fontBytes->BlitText(buf, px, py, posZ, fontSize); py += fontSize;
			
			//	counterlo = c64d_via2d_peek(drivectx, 0x1C04);
			//	counterhi = c64d_via2d_peek(drivectx, 0x1C05);
			//	sprintf(buf, " Timer 2 Counter: %02x%02x", counterhi, counterlo);
			//	fontBytes->BlitText(buf, px, py, posZ, fontSize); py += fontSize;
			
			v1 = c64d_via2d_peek(drivectx, 0x1C0B);
			v2 = c64d_via2d_peek(drivectx, 0x1C0C);
			
			if (isVertical)
			{
				sprintf(buf, " ACR: %02x PCR: %02x", v1, v2);
				fontBytes->BlitText(buf, px, py, posZ, fontSize); py += fontSize;
			}
			else
			{
				sprintf(buf, " ACR: %02x", v1);
				fontBytes->BlitText(buf, px, py, posZ, fontSize); py += fontSize;
				
				sprintf(buf, " PCR: %02x", v2);
				fontBytes->BlitText(buf, px, py, posZ, fontSize); py += fontSize;
			}
			
			
			v1 = c64d_via2d_peek(drivectx, 0x1C0D);
			v2 = c64d_via2d_peek(drivectx, 0x1C0E);
			sprintf(buf, " IFR: %02x IER: %02x", v1, v2);
			fontBytes->BlitText(buf, px, py, posZ, fontSize); py += fontSize;
			
		}
	}
	

	
	if (renderDriveLed)
	{
		if (showRegistersOnly)
		{
			px = posX;// + fontSize * 1.0f;
			py = posY + fontSize * 8.25f;
		}
		else
		{
			px = posX;
			py += fontSize * 2.25f;
			fontBytes->BlitText("Drive LED: ", px, py, posZ, fontSize);
		}
		
		float ledSizeX = fontSize*4.0f;
		float gap = fontSize * 0.1f;
		float ledSizeY = fontSize + gap + gap;
		
		float ledX = px + fontSize * 12.0f;
		float ledY = py - gap;
		
		float color = viewC64->debugInterfaceC64->ledState[driveId];
		
		BlitFilledRectangle(ledX, ledY, posZ, ledSizeX, ledSizeY,
							0.0f, color, 0.0f, 1.0f);
		BlitRectangle(ledX, py - gap, posZ, ledSizeX, ledSizeY,
					  0.3f, 0.3f, 0.3f, 1.0f, gap);
	}
	
}

bool CViewDrive1541StateVIA::DoTap(GLfloat x, GLfloat y)
{
	int driveId = 0;

	guiMain->LockMutex(); //"CViewDrive1541StateVIA::DoTap");
	
	if (editingRegisterValueIndex != -1)
	{
		editHex->FinalizeEntering(MTKEY_ENTER, true);
	}
	
	if (showRegistersOnly)
	{
		drive_context_t *drivectx = drive_context[driveId];

		float fs2 = fontSize;
		
		float px = posX;
		float py = posY + fontSize;
		
		if (renderVIA1)
		{
			float plx = px;
			float plex = px + fontSize * 7.0f;
			float ply = py;
			float sx = fs2 * 9;

			for (int i = 0; i < 0x0F; i++)
			{
				if (x >= plx && x <= plex
					&& y >= ply && y <= ply+fontSize)
				{
					LOGD("CViewC64StateVIA::DoTap: tapped register via1 %02x", i);
					
					u8 v = c64d_via1d1541_peek(drivectx, i);
					editHex->SetValue(v, 2);
					
					editingVIAIndex = 1;
					editingRegisterValueIndex = i;
					
					guiMain->UnlockMutex(); //"CViewDrive1541StateVIA::DoTap");
					return true;
				}
				
				ply += fs2;
				
				if (i % 0x08 == 0x07)
				{
					ply = py;
					plx += sx;
					plex += sx;
				}
			}
			
			if (isVertical)
			{
			}
			else
			{
				py = posY + fontSize;
				px = posX + 120;
			}
		}
		
		if (renderVIA2)
		{
			float plx = px;
			float plex = px + fontSize * 7.0f;
			float ply = py;
			float sx = fs2 * 9;

			for (int i = 0; i < 0x0F; i++)
			{
				if (x >= plx && x <= plex
					&& y >= ply && y <= ply+fontSize)
				{
					LOGD("CViewC64StateVIA::DoTap: tapped register via2 %02x", i);
					
					u8 v = c64d_via2d_peek(drivectx, i);
					editHex->SetValue(v, 2);
					
					editingVIAIndex = 2;
					editingRegisterValueIndex = i;
					
					guiMain->UnlockMutex(); //"CViewDrive1541StateVIA::DoTap");
					return true;
				}
				
				ply += fs2;
				
				if (i % 0x08 == 0x07)
				{
					ply = py;
					plx += sx;
					plex += sx;
				}
			}
		}
		
	}
	showRegistersOnly = !showRegistersOnly;

	guiMain->UnlockMutex(); //"CViewDrive1541StateVIA::DoTap");

	return false;
}


void CViewDrive1541StateVIA::GuiEditHexEnteredValue(CGuiEditHex *editHex, u32 lastKeyCode, bool isCancelled)
{
	if (isCancelled)
		return;
	
	int driveId = 0;
	
	if (editingRegisterValueIndex != -1)
	{
		byte v = editHex->value;
		debugInterface->SetViaRegister(driveId, editingVIAIndex, editingRegisterValueIndex, v);
		
		editHex->SetCursorPos(0);
	}
	

}

bool CViewDrive1541StateVIA::KeyDown(u32 keyCode, bool isShift, bool isAlt, bool isControl)
{
	int driveId = 0;
	
	if (editingRegisterValueIndex != -1)
	{
		if (keyCode == MTKEY_ARROW_UP)
		{
			if (editingRegisterValueIndex > 0)
			{
				editingRegisterValueIndex--;
				u8 v = debugInterface->GetViaRegister(driveId, editingVIAIndex, editingRegisterValueIndex);
				editHex->SetValue(v, 2);
				return true;
			}
		}
		
		if (keyCode == MTKEY_ARROW_DOWN)
		{
			if (editingRegisterValueIndex < 0x0F)
			{
				editingRegisterValueIndex++;
				u8 v = debugInterface->GetViaRegister(driveId, editingVIAIndex, editingRegisterValueIndex);
				editHex->SetValue(v, 2);
				return true;
			}
		}
		
		if (keyCode == MTKEY_ARROW_LEFT)
		{
			if (editHex->cursorPos == 0 && editingRegisterValueIndex > 0x08)
			{
				editingRegisterValueIndex -= 0x08;
				u8 v = debugInterface->GetViaRegister(driveId, editingVIAIndex, editingRegisterValueIndex);
				editHex->SetValue(v, 2);
				return true;
			}
		}
		
		if (keyCode == MTKEY_ARROW_RIGHT)
		{
			if (editHex->cursorPos == 1 && editingRegisterValueIndex < 0x10-0x08)
			{
				editingRegisterValueIndex += 0x08;
				u8 v = debugInterface->GetViaRegister(driveId, editingVIAIndex, editingRegisterValueIndex);
				editHex->SetValue(v, 2);
				return true;
			}
		}
		
		editHex->KeyDown(keyCode);
		return true;
	}
	return false;
}

bool CViewDrive1541StateVIA::KeyUp(u32 keyCode, bool isShift, bool isAlt, bool isControl)
{
	return false;
}

bool CViewDrive1541StateVIA::SetFocus(bool focus)
{
	return true;
}

void CViewDrive1541StateVIA::RenderFocusBorder()
{
//		CGuiView::RenderFocusBorder();
	//
}

