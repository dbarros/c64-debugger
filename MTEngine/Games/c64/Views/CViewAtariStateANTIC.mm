#include "C64D_Version.h"
#if defined(RUN_ATARI)

extern "C" {
#include "antic.h"
}
#endif

#include "CViewAtariStateANTIC.h"
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
#include "AtariDebugInterface.h"
#include "SYS_Threading.h"
#include "CGuiEditHex.h"
#include "VID_ImageBinding.h"

#if defined(RUN_ATARI)

CViewAtariStateANTIC::CViewAtariStateANTIC(GLfloat posX, GLfloat posY, GLfloat posZ, GLfloat sizeX, GLfloat sizeY, AtariDebugInterface *debugInterface)
: CGuiView(posX, posY, posZ, sizeX, sizeY)
{
	this->name = "CViewAtariStateANTIC";

	this->debugInterface = debugInterface;
	
	fontSize = 5.0f;
	
	fontBytes = guiMain->fntConsole;
	
	showRegistersOnly = false;
	editHex = new CGuiEditHex(this);
	editHex->isCapitalLetters = false;
	editingRegisterValueIndex = -1;

	this->SetPosition(posX, posY, posZ, sizeX, sizeY);
}

void CViewAtariStateANTIC::SetPosition(GLfloat posX, GLfloat posY, GLfloat posZ, GLfloat sizeX, GLfloat sizeY)
{
	CGuiView::SetPosition(posX, posY, posZ, sizeX, sizeY);
}

void CViewAtariStateANTIC::DoLogic()
{
}

void CViewAtariStateANTIC::Render()
{
//	if (debugInterface->GetSettingIsWarpSpeed() == true)
//		return;

	this->RenderState(posX, posY, posZ, fontBytes, fontSize, 1);
}

extern "C" {
	int get_hex(UWORD *hexval);
}

void CViewAtariStateANTIC::RenderState(float px, float py, float posZ, CSlrFont *fontBytes, float fontSize, int ciaId)
{
	float startY = py;
	char buf[256];
	char buf2[256];

	sprintf(buf, "ANTIC");
	fontBytes->BlitText(buf, px, py, posZ, fontSize); py += fontSize;
	py += fontSize*0.5f;
	
	/*

	if (showRegistersOnly)
	{
		float fs2 = fontSize;
		
		float plx = px;
		float ply = py;
		for (int i = 0; i < 0x10; i++)
		{
			if (editingCIAIndex == ciaId && editingRegisterValueIndex == i)
			{
				sprintf(buf, "D%c%02x", addr, i);
				fontBytes->BlitText(buf, plx, ply, posZ, fs2);
				fontBytes->BlitTextColor(editHex->textWithCursor, plx + fontSize*5.0f, ply, posZ, fontSize, 1.0f, 1.0f, 1.0f, 1.0f);
			}
			else
			{
				u8 v = c64d_ciacore_peek(cia_context, i);
				sprintf(buf, "D%c%02x %02x", addr, i, v);
				fontBytes->BlitText(buf, plx, ply, posZ, fs2);
			}
			
			ply += fs2;
			
			if (i % 0x08 == 0x07)
			{
				ply = py;
				plx += fs2 * 9;
			}
		}
		
		return;
	}*/
	
//	printf("DMACTL=%02X    CHACTL=%02X    DLISTL=%02X    "
//		   "DLISTH=%02X    HSCROL=%02X    VSCROL=%02X\n",
//		   ANTIC_DMACTL, ANTIC_CHACTL, ANTIC_dlist & 0xff, ANTIC_dlist >> 8, ANTIC_HSCROL, ANTIC_VSCROL);
//	printf("PMBASE=%02X    CHBASE=%02X    VCOUNT=%02X    "
//		   "NMIEN= %02X    ypos=%4d\n",
//		   ANTIC_PMBASE, ANTIC_CHBASE, ANTIC_GetByte(ANTIC_OFFSET_VCOUNT, TRUE), ANTIC_NMIEN, ANTIC_ypos);

	// TODO:
	if (viewC64->currentScreenLayoutId != SCREEN_LAYOUT_ATARI_MEMORY_MAP)
	{
		sprintf(buf, "RASTER: x %4d  y %4d",
				ANTIC_xpos, ANTIC_ypos);
		fontBytes->BlitText(buf, px, py, posZ, fontSize); py += fontSize;
	}
	
	sprintf(buf, "DMACTL %02X  CHACTL %02X",	//    DLIST=%04X",
			ANTIC_DMACTL, ANTIC_CHACTL);		//, ANTIC_dlist);
	fontBytes->BlitText(buf, px, py, posZ, fontSize); py += fontSize;

	sprintf(buf, "DLISTL %02X  DLISTH %02X", ANTIC_dlist & 0xff, ANTIC_dlist >> 8);
	fontBytes->BlitText(buf, px, py, posZ, fontSize); py += fontSize;
	
	sprintf(buf, "HSCROL %02X  VSCROL %02X",
			ANTIC_HSCROL, ANTIC_VSCROL);
	fontBytes->BlitText(buf, px, py, posZ, fontSize); py += fontSize;

	sprintf(buf, "PMBASE %02X  CHBASE %02X",
			ANTIC_PMBASE, ANTIC_CHBASE);
	fontBytes->BlitText(buf, px, py, posZ, fontSize); py += fontSize;

	sprintf(buf, "VCOUNT %02X  NMIEN  %02X",
			ANTIC_GetByte(ANTIC_OFFSET_VCOUNT, TRUE), ANTIC_NMIEN);
	fontBytes->BlitText(buf, px, py, posZ, fontSize); py += fontSize;

	//
	py = startY;
	px += 24 * fontSize;
	
	// display list
	/* group identical instructions */
	UWORD tdlist = ANTIC_dlist;
	UWORD new_tdlist;
	UBYTE IR;
	int scrnaddr = -1;
//	get_hex(&tdlist);
	
	new_tdlist = tdlist;
	IR = ANTIC_GetDLByte(&new_tdlist);
	
	int numLines = 0;
	for (;;)
	{
//		LOGD("tdlist=%04X", tdlist);
		sprintf(buf, "%04X: ", tdlist);

		if ((IR & 0x0f) == 0)
		{
			UBYTE new_IR;
			tdlist = new_tdlist;
			new_IR = ANTIC_GetDLByte(&new_tdlist);
			if (new_IR == IR)
			{
				int count = 1;
				do
				{
					count++;
					tdlist = new_tdlist;
					new_IR = ANTIC_GetDLByte(&new_tdlist);
				} while (new_IR == IR && count < 240);
				
				sprintf(buf2, "%dx ", count);
				strcat(buf, buf2);
			}
			if (IR & 0x80)
			{
				sprintf(buf2, "DLI ");
				strcat(buf, buf2);
			}
			sprintf(buf2, "%c BLANK", ((IR >> 4) & 0x07) + '1');
			strcat(buf, buf2);
			fontBytes->BlitText(buf, px, py, posZ, fontSize); py += fontSize;
			numLines++;
			if (numLines == 25)
				break;

			IR = new_IR;
		}
		else if ((IR & 0x0f) == 1)
		
		{
			tdlist = ANTIC_GetDLWord(&new_tdlist);
			if (IR & 0x80)
			{
				sprintf(buf2, "DLI ");
				strcat(buf, buf2);
			}
			
			if (IR & 0x40)
			{
				sprintf(buf2, "JVB %04X", tdlist);
				strcat(buf, buf2);
				fontBytes->BlitText(buf, px, py, posZ, fontSize); py += fontSize;
				break;
			}
			
			sprintf(buf2, "JMP %04X", tdlist);
			strcat(buf, buf2);
			fontBytes->BlitText(buf, px, py, posZ, fontSize); py += fontSize;
			numLines++;
			if (numLines == 25)
				break;

			new_tdlist = tdlist;
			IR = ANTIC_GetDLByte(&new_tdlist);
		}
		else
		{
			UBYTE new_IR;
			int new_scrnaddr;
			int count;
			if ((IR & 0x40) && scrnaddr < 0)
			{
				scrnaddr = ANTIC_GetDLWord(&new_tdlist);
			}
			
			for (count = 1;; count++)
			{
				tdlist = new_tdlist;
				new_IR = ANTIC_GetDLByte(&new_tdlist);
				if (new_IR != IR || count >= 240)
				{
					new_scrnaddr = -1;
					break;
				}
				if (IR & 0x40)
				{
					new_scrnaddr = ANTIC_GetDLWord(&new_tdlist);
					if (new_scrnaddr != scrnaddr)
						break;
				}
			}
			if (count > 1)
			{
				sprintf(buf2, "%dx ", count);
				strcat(buf, buf2);
			}
			
			if (IR & 0x80)
			{
				sprintf(buf2, "DLI ");
				strcat(buf, buf2);
			}
			if (IR & 0x40)
			{
				sprintf(buf2, "LMS %04X ", scrnaddr);
				strcat(buf, buf2);
			}
			if (IR & 0x20)
			{
				sprintf(buf2, "VSCROL ");
				strcat(buf, buf2);
			}
			if (IR & 0x10)
			{
				sprintf(buf2, "HSCROL ");
				strcat(buf, buf2);
			}
			sprintf(buf2, "MODE %X", IR & 0x0f);
			strcat(buf, buf2);
			
			fontBytes->BlitText(buf, px, py, posZ, fontSize); py += fontSize;
			numLines++;
			if (numLines == 25)
				break;
			
			scrnaddr = new_scrnaddr;
			IR = new_IR;
		}

	}

}


bool CViewAtariStateANTIC::DoTap(GLfloat x, GLfloat y)
{
	guiMain->LockMutex();
	
	if (editingRegisterValueIndex != -1)
	{
		editHex->FinalizeEntering(MTKEY_ENTER, true);
	}

	/*
	// check if tap register
	if (showRegistersOnly)
	{
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
					LOGD("CViewAtariStateANTIC::DoTap: tapped register %02x", i);
					
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
	}
	*/
	showRegistersOnly = !showRegistersOnly;
	
	guiMain->UnlockMutex();
	return false;
}

void CViewAtariStateANTIC::GuiEditHexEnteredValue(CGuiEditHex *editHex, u32 lastKeyCode, bool isCancelled)
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

bool CViewAtariStateANTIC::KeyDown(u32 keyCode, bool isShift, bool isAlt, bool isControl)
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

bool CViewAtariStateANTIC::KeyUp(u32 keyCode, bool isShift, bool isAlt, bool isControl)
{
	return false;
}

bool CViewAtariStateANTIC::SetFocus(bool focus)
{
	return true;
}

void CViewAtariStateANTIC::RenderFocusBorder()
{
//	CGuiView::RenderFocusBorder();
	//
}

#else

CViewAtariStateANTIC::CViewAtariStateANTIC(GLfloat posX, GLfloat posY, GLfloat posZ, GLfloat sizeX, GLfloat sizeY, AtariDebugInterface *debugInterface)
: CGuiView(posX, posY, posZ, sizeX, sizeY) {}
void CViewAtariStateANTIC::SetPosition(GLfloat posX, GLfloat posY, GLfloat posZ, GLfloat sizeX, GLfloat sizeY) {}
void CViewAtariStateANTIC::DoLogic() {}
void CViewAtariStateANTIC::Render() {}
void CViewAtariStateANTIC::RenderState(float px, float py, float posZ, CSlrFont *fontBytes, float fontSize, int ciaId) {}
bool CViewAtariStateANTIC::DoTap(GLfloat x, GLfloat y) { return false; }
void CViewAtariStateANTIC::GuiEditHexEnteredValue(CGuiEditHex *editHex, u32 lastKeyCode, bool isCancelled) {}
bool CViewAtariStateANTIC::KeyDown(u32 keyCode, bool isShift, bool isAlt, bool isControl) { return false; }
bool CViewAtariStateANTIC::KeyUp(u32 keyCode, bool isShift, bool isAlt, bool isControl) { return false; }
bool CViewAtariStateANTIC::SetFocus(bool focus) { return true; }
void CViewAtariStateANTIC::RenderFocusBorder() {}

#endif
