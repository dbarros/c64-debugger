#include "CViewSourceCode.h"
#include "CColorsTheme.h"
#include "VID_GLViewController.h"
#include "CGuiMain.h"
#include "CSlrDataAdapter.h"
#include "CViewC64.h"
#include "CViewMemoryMap.h"
#include "SYS_KeyCodes.h"
#include "CViewC64Screen.h"
#include "C64DebugInterface.h"
#include "AtariDebugInterface.h"
#include "CGuiEditBoxText.h"
#include "C64Tools.h"
#include "CSlrString.h"
#include "CSlrKeyboardShortcuts.h"
#include "C64KeyboardShortcuts.h"
#include "C64SettingsStorage.h"
#include "CViewC64VicDisplay.h"
#include "CViewDataDump.h"
#include "CViewDisassemble.h"
#include "C64Symbols.h"
#include "C64AsmSourceSymbols.h"

CViewSourceCode::CViewSourceCode(GLfloat posX, GLfloat posY, GLfloat posZ, GLfloat sizeX, GLfloat sizeY,
										 CSlrDataAdapter *dataAdapter, CViewMemoryMap *memoryMap,
										 CViewDisassemble *viewDisassemble,
										 CDebugInterface *debugInterface)
: CGuiView(posX, posY, posZ, sizeX, sizeY)
{
	this->name = "CViewSourceCode";
	
	this->viewDisassemble = viewDisassemble;
	this->memoryMap = memoryMap;
	this->dataAdapter = dataAdapter;
	this->memoryLength = dataAdapter->AdapterGetDataLength();
	this->memory = new uint8[memoryLength];
	
	this->debugInterface = debugInterface;

	this->font = NULL;
	
	this->changedByUser = false;
	this->cursorAddress = -1;
	this->currentPC = -1;
	
	this->showFilePath = true;
	this->showLineNumbers = true;
	
//	// keyboard shortcut zones for this view
//	shortcutZones.push_back(KBZONE_DISASSEMBLE);
//	shortcutZones.push_back(KBZONE_MEMORY);

	/// debug

	// render execute-aware version of disassemble?
	//c64SettingsRenderDisassembleExecuteAware = true;
	
//	this->AddCodeLabel(0xE5D1, "labE5D1x:");
//	this->AddCodeLabel(0xE5D3, "labE5D3x:");
//	this->AddCodeLabel(0xFD6E, "labFD6Ex:");
//	this->AddCodeLabel(0x1000, "lab1000x:");
}

CViewSourceCode::~CViewSourceCode()
{
}


void CViewSourceCode::ScrollToAddress(int addr)
{
//	LOGD("CViewSourceCode::ScrollToAddress=%04x", addr);

	this->cursorAddress = addr;
}

void CViewSourceCode::SetViewParameters(float posX, float posY, float posZ, float sizeX, float sizeY, CSlrFont *font,
										 float fontSize)
{
	CGuiView::SetPosition(posX, posY, posZ, sizeX, sizeY);
	
	this->font = font;
	this->fontSize = fontSize;

}

void CViewSourceCode::UpdateLocalMemoryCopy(int startAddress, int endAddress)
{
	int beginAddress = startAddress; // - numberOfLinesBack3;

	//LOGD("UpdateLocalMemoryCopy: %04x %04x (size=%04x)", beginAddress, endAddress, endAddress-beginAddress);

	if (beginAddress < 0)
	{
		beginAddress = 0;
	}
	
	dataAdapter->AdapterReadBlockDirect(memory, beginAddress, endAddress);
}

void CViewSourceCode::DoLogic()
{
}

void CViewSourceCode::Render()
{
//	this->font->BlitText("CViewSourceCode", 0, 0, -1, fontSize);
	
	float pe = this->posEndY;
	
	if (showFilePath)
	{
		pe -= fontSize;
	}

	
//	if (debugInterface->GetSettingIsWarpSpeed() == true)
//		return;
	
//	this->renderBreakpointsMutex->Lock();
	
	
	float colorExecuteR, colorExecuteG, colorExecuteB;
	float colorExecuteA = 1.0f;
//	float colorNonExecuteR, colorNonExecuteG, colorNonExecuteB;
//	float colorNonExecuteA = 1.0f;
	
	GetColorsFromScheme(c64SettingsDisassemblyExecuteColor, &colorExecuteR, &colorExecuteG, &colorExecuteB);
//	GetColorsFromScheme(c64SettingsDisassemblyNonExecuteColor, &colorNonExecuteR, &colorNonExecuteG, &colorNonExecuteB);

	float cr = colorExecuteR;
	float cg = colorExecuteG;
	float cb = colorExecuteB;

	
	float colorBackgroundR, colorBackgroundG, colorBackgroundB;
	float colorBackgroundA = 1.0f;
	
	GetColorsFromScheme(c64SettingsDisassemblyBackgroundColor, &colorBackgroundR, &colorBackgroundG, &colorBackgroundB);

	BlitFilledRectangle(this->posX, this->posY, -1, this->sizeX, this->sizeY, colorBackgroundR, colorBackgroundG, colorBackgroundB, colorBackgroundA);
	
	
	//
	if (showFilePath)
	{
		BlitFilledRectangle(posX, pe + 1.0f, -1.0f,
							sizeX, fontSize, 0.7, 0.7, 1, 0.5f);
		
	}

	// TODO: Generalize me
	CDebugInterface *debugInterface = NULL;
	if (viewC64->debugInterfaceC64)
	{
		debugInterface = viewC64->debugInterfaceC64;
	}
	else if (viewC64->debugInterfaceAtari)
	{
		debugInterface = viewC64->debugInterfaceAtari;
	}
	
	
	C64AsmSourceSymbols *asmSource = debugInterface->symbols->asmSource;
	
	if (asmSource == NULL)
		return;
	
	if (debugInterface->symbols->asmSource->segments.empty())
		return;

//	fontSize = 5.0f;
	
	float px = this->posX;
	float py = this->posY + fontSize*21;
	
	float sx = this->sizeX;
	float nx = this->posEndX;
	
	if (showLineNumbers)
	{
		sx -= fontSize*4;
		nx -= fontSize*4;
	}
	
	char buf[16];
	
	C64AsmSourceLine *sourceLine = NULL;
	
	C64AsmSourceSegment *sourceSegment = debugInterface->symbols->asmSource->currentSelectedSegment;
	
	// blit segment name
	// TODO: make this in-line with UI, this is UI workaround
	const float segmentFontSize = 6.0f;
	font->BlitTextColor(sourceSegment->name, posX, 0.0f, -1, segmentFontSize, 1, 1, 1, 1);
	
	this->cursorAddress = viewDisassemble->cursorAddress;

	if (this->cursorAddress >= 0 && this->cursorAddress < asmSource->maxMemoryAddress)
	{
		sourceLine = sourceSegment->codeSourceLineByMemoryAddress[this->cursorAddress];
	}
	
	if (sourceLine != NULL && sourceLine->codeFile != NULL)
	{
		font->BlitTextColor(sourceLine->block->name, posX, 0.0f + segmentFontSize, -1, segmentFontSize, 1, 1, 1, 1);

		BlitFilledRectangle(posX, py, -1.0f,
							sizeX, fontSize, cr, cg, cb, 0.3f);

		VID_SetClipping(this->posX, this->posY, sx, this->sizeY);

		int lineNum = sourceLine->codeLineNumberStart;

		if (sourceLine->codeFile->codeTextByLineNum.size() < lineNum)
		{
			// file not loaded properly?
			//LOGError("lineNum exceeds codeTextByLineNum");
			return;
		}

		std::vector<CSlrString *>::iterator itDown = sourceLine->codeFile->codeTextByLineNum.begin();
		std::advance(itDown, lineNum);

		std::vector<CSlrString *>::iterator itUp = itDown;
		
		float pyb = py;
		
		for ( ; itDown != sourceLine->codeFile->codeTextByLineNum.end(); itDown++)
		{
			CSlrString *str = *itDown;
			
			font->BlitTextColor(str, px, py, -1, fontSize, 1, 1, 1, 1);

			py += fontSize;
			lineNum++;
			
			if (py > pe)
				break;
		}
		
		py = pyb - fontSize;
		itUp--;
		lineNum = sourceLine->codeLineNumberStart-1;

		for ( ; itUp != sourceLine->codeFile->codeTextByLineNum.begin(); itUp--)
		{
			CSlrString *str = *itUp;
			
			font->BlitTextColor(str, px, py, -1, fontSize, 1, 1, 1, 1);
			
			py -= fontSize;
			lineNum--;
			
			if (py < this->posY)
				break;
		}

		VID_ResetClipping();

		if (showLineNumbers)
		{
			py = pyb;
			lineNum = sourceLine->codeLineNumberStart-1;

			itDown = sourceLine->codeFile->codeTextByLineNum.begin();
			std::advance(itDown, lineNum);

			itUp = itDown;
			
			lineNum = sourceLine->codeLineNumberStart;
			
			for ( ; itDown != sourceLine->codeFile->codeTextByLineNum.end(); itDown++)
			{
				sprintf(buf, "%4d", lineNum);
				font->BlitTextColor(buf, nx, py, -1, fontSize, 0.7, 0.7, 0.7, 1);
				
				py += fontSize;
				lineNum++;
				
				if (py > pe)
					break;
			}
			
			py = pyb - fontSize;
			itUp--;
			lineNum = sourceLine->codeLineNumberStart-1;
			
			for ( ; itUp != sourceLine->codeFile->codeTextByLineNum.begin(); itUp--)
			{
				sprintf(buf, "%4d", lineNum);
				font->BlitTextColor(buf, nx, py, -1, fontSize, 0.7, 0.7, 0.7, 1);
				
				py -= fontSize;
				lineNum--;
				
				if (py < this->posY)
					break;
			}
		}

		if (showFilePath)
		{
			font->BlitTextColor(sourceLine->codeFile->sourceFileName, px, pe+1.5f, -1, fontSize, 0.9, 0.7, 0.7, 1);
		}
	}
	
	
	//	this->renderBreakpointsMutex->Unlock();

}

void CViewSourceCode::Render(GLfloat posX, GLfloat posY)
{
	this->Render();
}

bool CViewSourceCode::IsInside(GLfloat x, GLfloat y)
{
	const float segmentFontSize = 6.0f;
	if (x > posX && x < posX + (segmentFontSize*18)
		&& y > 0 && y < (segmentFontSize * 3.0f))
	{
		return true;
	}
	
	return CGuiView::IsInside(x, y);
}

//@returns is consumed
bool CViewSourceCode::DoTap(GLfloat x, GLfloat y)
{
	LOGG("CViewSourceCode::DoTap:  x=%f y=%f", x, y);
	
	if (this->visible == false)
		return false;
	
	// TODO: Generalize me
	CDebugInterface *debugInterface = NULL;
	if (viewC64->debugInterfaceC64)
	{
		debugInterface = viewC64->debugInterfaceC64;
	}
	else if (viewC64->debugInterfaceAtari)
	{
		debugInterface = viewC64->debugInterfaceAtari;
	}
	
	const float segmentFontSize = 6.0f;
	if (x > posX && x < posX + (segmentFontSize*18)
		&& y > 0 && y < (segmentFontSize * 3.0f))
	{
		// tapped on Segment, switch Segment to next
		if (debugInterface->symbols && debugInterface->symbols->asmSource)
		{
			debugInterface->symbols->asmSource->SelectNextSegment();
		}
		return true;
	}

	return true;
}

bool CViewSourceCode::KeyDown(u32 keyCode, bool isShift, bool isAlt, bool isControl)
{
	LOGI("CViewSourceCode::KeyDown: %x %s %s %s", keyCode, STRBOOL(isShift), STRBOOL(isAlt), STRBOOL(isControl));

	return CGuiView::KeyDown(keyCode, isShift, isAlt, isControl);
}

void CViewSourceCode::SetCursorToNearExecuteCodeAddress(int newCursorAddress)
{
//	isTrackingPC = false;
//	
	for (int addr = newCursorAddress; addr > newCursorAddress-3; addr--)
	{
		if (viewC64->viewC64MemoryMap->IsExecuteCodeAddress(addr))
		{
			cursorAddress = addr;
			return;
		}
	}
	
	for (int addr = newCursorAddress; addr < newCursorAddress+3; addr++)
	{
		if (viewC64->viewC64MemoryMap->IsExecuteCodeAddress(addr))
		{
			cursorAddress = addr;
			return;
		}
	}
	
	cursorAddress = newCursorAddress;
}


bool CViewSourceCode::KeyUp(u32 keyCode, bool isShift, bool isAlt, bool isControl)
{
	return CGuiView::KeyUp(keyCode, isShift, isAlt, isControl);
}

void CViewSourceCode::ScrollDown()
{
//	isTrackingPC = false;
	changedByUser = true;

}

void CViewSourceCode::ScrollUp()
{
//	isTrackingPC = false;
	changedByUser = true;
	
}

bool CViewSourceCode::DoScrollWheel(float deltaX, float deltaY)
{
	//LOGD("CViewSourceCode::DoScrollWheel: %f %f", deltaX, deltaY);
	int dy = fabs(round(deltaY));
	
	bool scrollUp = (deltaY > 0);
	
	for (int i = 0; i < dy; i++)
	{
		if (scrollUp)
		{
			ScrollUp();
		}
		else
		{
			ScrollDown();
		}
	}
	return true;
}

void CViewSourceCode::RenderFocusBorder()
{
	// do not render border
	
}

