extern "C" {
#include "vice.h"
#include "main.h"
#include "types.h"
#include "viciitypes.h"
#include "vicii.h"
#include "c64mem.h"
}

#include "CViewC64VicControl.h"
#include "VID_GLViewController.h"
#include "CGuiMain.h"
#include "VID_ImageBinding.h"
#include "CViewC64.h"
#include "SYS_KeyCodes.h"
#include "C64DebugInterface.h"
#include "C64SettingsStorage.h"
#include "CViewC64Screen.h"
#include "CSlrFont.h"
#include "CGuiLabel.h"
#include "CViewC64StateVIC.h"
#include "CViewMemoryMap.h"
#include "CViewDataDump.h"
#include "CViewDisassemble.h"
#include "CViewC64VicDisplay.h"


CViewC64VicControl::CViewC64VicControl(GLfloat posX, GLfloat posY, GLfloat posZ, GLfloat sizeX, GLfloat sizeY,
									   CViewC64VicDisplay *vicDisplay)
: CGuiView(posX, posY, posZ, sizeX, sizeY)
{
	this->name = "CViewC64VicControl";
	
	this->debugInterface = vicDisplay->debugInterface;
	
	this->vicDisplay = vicDisplay;
	this->vicDisplay->SetVicControlView(this);
	
	viewFrame = NULL;
	//	viewFrame = new CGuiViewFrame(this, new CSlrString("VIC Display"));
	//	this->AddGuiElement(viewFrame);
	
	
	this->AddGuiButtons();
	
	forceGrayscaleColors = false;
	
	//
	txtAutolockRasterPC = new CSlrString("RASTER");
	txtAutolockBitmapAddress = new CSlrString("BITMAP");
	txtAutolockTextAddress = new CSlrString("SCREEN");
	txtAutolockColourAddress = new CSlrString("COLOUR");
	txtAutolockCharsetAddress = new CSlrString("CHARSET");
	
	// init display default vars
	this->fontSize = 8.0f;
	
	this->SetPosition(posX, posY);
	
	this->vicDisplay->SetAutoScrollMode(AUTOSCROLL_DISASSEMBLE_RASTER_PC);

}

void CViewC64VicControl::AddGuiButtons()
{
	font = viewC64->fontCBMShifted;
	fontScale = 0.8;
	fontHeight = font->GetCharHeight('@', fontScale) + 2;
	
	float px = posX;
	float py = posY;
	
	float buttonSizeX = 25.0f;
	float buttonSizeY = 10.0f;
	float gapY = 5.0f;
	
	btnModeStandard = new CGuiButtonSwitch(NULL, NULL, NULL,
										   px, py, posZ, buttonSizeX, buttonSizeY,
										   new CSlrString("STD"),
										   FONT_ALIGN_CENTER, buttonSizeX/2, 3.5,
										   font, fontScale,
										   1.0, 1.0, 1.0, 1.0,
										   1.0, 1.0, 1.0, 1.0,
										   0.3, 0.3, 0.3, 1.0,
										   this);
	btnModeStandard->SetOn(false);
	SetLockableButtonDefaultColors(btnModeStandard);
	this->AddGuiElement(btnModeStandard);
	
	px += buttonSizeX;
	btnModeExtended = new CGuiButtonSwitch(NULL, NULL, NULL,
										   px, py, posZ, buttonSizeX, buttonSizeY,
										   new CSlrString("EXT"),
										   FONT_ALIGN_CENTER, buttonSizeX/2, 3.5,
										   font, fontScale,
										   1.0, 1.0, 1.0, 1.0,
										   1.0, 1.0, 1.0, 1.0,
										   0.3, 0.3, 0.3, 1.0,
										   this);
	btnModeExtended->SetOn(false);
	SetLockableButtonDefaultColors(btnModeExtended);
	this->AddGuiElement(btnModeExtended);
	
	px = posX;
	py += buttonSizeY + gapY;
	
	//
	btnModeText = new CGuiButtonSwitch(NULL, NULL, NULL,
									   px, py, posZ, buttonSizeX, buttonSizeY,
									   new CSlrString("TEXT"),
									   FONT_ALIGN_CENTER, buttonSizeX/2, 3.5,
									   font, fontScale,
									   1.0, 1.0, 1.0, 1.0,
									   1.0, 1.0, 1.0, 1.0,
									   0.3, 0.3, 0.3, 1.0,
									   this);
	btnModeText->SetOn(false);
	SetLockableButtonDefaultColors(btnModeText);
	this->AddGuiElement(btnModeText);
	
	px += buttonSizeX;
	btnModeBitmap = new CGuiButtonSwitch(NULL, NULL, NULL,
										 px, py, posZ, buttonSizeX, buttonSizeY,
										 new CSlrString("BITMAP"),
										 FONT_ALIGN_CENTER, buttonSizeX/2, 3.5,
										 font, fontScale,
										 1.0, 1.0, 1.0, 1.0,
										 1.0, 1.0, 1.0, 1.0,
										 0.3, 0.3, 0.3, 1.0,
										 this);
	btnModeBitmap->SetOn(false);
	SetLockableButtonDefaultColors(btnModeBitmap);
	this->AddGuiElement(btnModeBitmap);
	
	//
	px = posX;
	py += buttonSizeY + gapY;
	
	btnModeHires = new CGuiButtonSwitch(NULL, NULL, NULL,
										px, py, posZ, buttonSizeX, buttonSizeY,
										new CSlrString("HIRES"),
										FONT_ALIGN_CENTER, buttonSizeX/2, 3.5,
										font, fontScale,
										1.0, 1.0, 1.0, 1.0,
										1.0, 1.0, 1.0, 1.0,
										0.3, 0.3, 0.3, 1.0,
										this);
	btnModeHires->SetOn(false);
	SetLockableButtonDefaultColors(btnModeHires);
	this->AddGuiElement(btnModeHires);
	
	px += buttonSizeX;
	btnModeMulti = new CGuiButtonSwitch(NULL, NULL, NULL,
										px, py, posZ, buttonSizeX, buttonSizeY,
										new CSlrString("MULTI"),
										FONT_ALIGN_CENTER, buttonSizeX/2, 3.5,
										font, fontScale,
										1.0, 1.0, 1.0, 1.0,
										1.0, 1.0, 1.0, 1.0,
										0.3, 0.3, 0.3, 1.0,
										this);
	btnModeMulti->SetOn(false);
	SetLockableButtonDefaultColors(btnModeMulti);
	this->AddGuiElement(btnModeMulti);
	
	// list of screen addresses
	px = SCREEN_WIDTH - 50;
	py = posY + 200;
	
	
	char **txtScreenAddresses = new char *[0x40];
	
	u16 addr = 0x0000;
	for (int i = 0; i < 0x40; i++)
	{
		char *txtAddr = new char[5];
		sprintf(txtAddr, "%04x", addr);
		addr += 0x0400;
		
		txtScreenAddresses[i] = txtAddr;
	}
	
	float lstFontSize = 4.0f;
	
	this->lstScreenAddresses = new CGuiLockableList(px, py, posZ+0.01, lstFontSize*6.5f, 45.0f, lstFontSize,
													NULL, 0, false,
													guiMain->fntConsole,
													guiMain->theme->imgBackground, 1.0f,
													this);
	this->lstScreenAddresses->Init(txtScreenAddresses, 0x40, true);
	this->lstScreenAddresses->SetGaps(0.0f, -0.25f);
	this->AddGuiElement(this->lstScreenAddresses);
	
	//
	py += 50;
	
	char **txtCharsetAddresses = new char *[0x20];
	
	addr = 0x0000;
	for (int i = 0; i < 0x20; i++)
	{
		char *txtAddr = new char[5];
		sprintf(txtAddr, "%04x", addr);
		addr += 0x0800;
		
		txtCharsetAddresses[i] = txtAddr;
	}
	
	this->lstCharsetAddresses = new CGuiLockableList(px, py, posZ+0.01, lstFontSize*6.5f, 45.0f, lstFontSize,
													 NULL, 0, false,
													 guiMain->fntConsole,
													 guiMain->theme->imgBackground, 1.0f,
													 this);
	this->lstCharsetAddresses->Init(txtCharsetAddresses, 0x20, true);
	this->lstCharsetAddresses->SetGaps(0.0f, -0.25f);
	this->AddGuiElement(this->lstCharsetAddresses);
	
	//
	py += 50;
	
	char **txtBitmapAddresses = new char *[0x40];
	
	addr = 0x0000;
	for (int i = 0; i < 0x08; i++)
	{
		char *txtAddr = new char[5];
		sprintf(txtAddr, "%04x", addr);
		addr += 0x2000;
		
		txtBitmapAddresses[i] = txtAddr;
	}
	
	this->lstBitmapAddresses = new CGuiLockableList(px, py, posZ+0.01, lstFontSize*6.5f, 45.0f, lstFontSize,
													NULL, 0, false,
													guiMain->fntConsole,
													guiMain->theme->imgBackground, 1.0f,
													this);
	this->lstBitmapAddresses->Init(txtBitmapAddresses, 0x08, true);
	this->lstBitmapAddresses->SetGaps(0.0f, -0.25f);
	this->AddGuiElement(this->lstBitmapAddresses);
	
	float listSizeX = 45.0f;
	
	lblScreenAddress = new CGuiLabel("Screen", false, px, py, posZ, listSizeX, lstFontSize, LABEL_ALIGNED_LEFT, lstFontSize, lstFontSize, NULL);
	this->AddGuiElement(lblScreenAddress);
	
	lblCharsetAddress = new CGuiLabel("Charset", false, px, py, posZ, listSizeX, lstFontSize, LABEL_ALIGNED_LEFT, lstFontSize, lstFontSize, NULL);
	this->AddGuiElement(lblCharsetAddress);
	
	lblBitmapAddress = new CGuiLabel("Bitmap", false, px, py, posZ, listSizeX, lstFontSize, LABEL_ALIGNED_LEFT, lstFontSize, lstFontSize, NULL);
	this->AddGuiElement(lblBitmapAddress);
	
	///
	btnApplyScrollRegister = new CGuiButtonSwitch(NULL, NULL, NULL,
											 px, py, posZ, buttonSizeX, buttonSizeY,
											 new CSlrString("SCROLL"),
											 FONT_ALIGN_CENTER, buttonSizeX/2, 3.5,
											 font, fontScale,
											 1.0, 1.0, 1.0, 1.0,
											 1.0, 1.0, 1.0, 1.0,
											 0.3, 0.3, 0.3, 1.0,
											 this);
	btnApplyScrollRegister->SetOn(false);
	SetSwitchButtonDefaultColors(btnApplyScrollRegister);
	this->AddGuiElement(btnApplyScrollRegister);
	
	//
	btnShowBadLines = new CGuiButtonSwitch(NULL, NULL, NULL,
												  px, py, posZ, buttonSizeX, buttonSizeY,
												  new CSlrString("BADLINE"),
												  FONT_ALIGN_CENTER, buttonSizeX/2, 3.5,
												  font, fontScale,
												  1.0, 1.0, 1.0, 1.0,
												  1.0, 1.0, 1.0, 1.0,
												  0.3, 0.3, 0.3, 1.0,
												  this);
	btnShowBadLines->SetOn(false);
	SetSwitchButtonDefaultColors(btnShowBadLines);
	this->AddGuiElement(btnShowBadLines);
	
	//
	btnShowWithBorder = new CGuiButtonSwitch(NULL, NULL, NULL,
											 px, py, posZ, buttonSizeX, buttonSizeY,
											 new CSlrString("BORDER"),
											 FONT_ALIGN_CENTER, buttonSizeX/2, 3.5,
											 font, fontScale,
											 1.0, 1.0, 1.0, 1.0,
											 1.0, 1.0, 1.0, 1.0,
											 0.3, 0.3, 0.3, 1.0,
											 this);
	btnShowWithBorder->SetOn(true);
	SetSwitchButtonDefaultColors(btnShowWithBorder);
	this->AddGuiElement(btnShowWithBorder);
	
	btnShowGrid = new CGuiButtonSwitch(NULL, NULL, NULL,
												px, py, posZ, buttonSizeX, buttonSizeY,
												new CSlrString("GRID"),
												FONT_ALIGN_CENTER, buttonSizeX/2, 3.5,
												font, fontScale,
												1.0, 1.0, 1.0, 1.0,
												1.0, 1.0, 1.0, 1.0,
												0.3, 0.3, 0.3, 1.0,
												this);
	btnShowGrid->SetOn(true);
	SetSwitchButtonDefaultColors(btnShowGrid);
	this->AddGuiElement(btnShowGrid);
	
	///
	
	btnShowSpritesGraphics = new CGuiButtonSwitch(NULL, NULL, NULL,
											   px, py, posZ, buttonSizeX, buttonSizeY,
											   new CSlrString("SPRITES"),
											   FONT_ALIGN_CENTER, buttonSizeX/2, 3.5,
											   font, fontScale,
											   1.0, 1.0, 1.0, 1.0,
											   1.0, 1.0, 1.0, 1.0,
											   0.3, 0.3, 0.3, 1.0,
											   this);
	btnShowSpritesGraphics->SetOn(true);
	SetSwitchButtonDefaultColors(btnShowSpritesGraphics);
	this->AddGuiElement(btnShowSpritesGraphics);
	
	btnShowSpritesFrames = new CGuiButtonSwitch(NULL, NULL, NULL,
												px, py, posZ, buttonSizeX, buttonSizeY,
												new CSlrString("FRAMES"),
												FONT_ALIGN_CENTER, buttonSizeX/2, 3.5,
												font, fontScale,
												1.0, 1.0, 1.0, 1.0,
												1.0, 1.0, 1.0, 1.0,
												0.3, 0.3, 0.3, 1.0,
												this);
	btnShowSpritesFrames->SetOn(true);
	SetSwitchButtonDefaultColors(btnShowSpritesFrames);
	this->AddGuiElement(btnShowSpritesFrames);
	
	//
	btnToggleBreakpoint = new CGuiButtonSwitch(NULL, NULL, NULL,
											   px, py, posZ, buttonSizeX, buttonSizeY,
											   new CSlrString("BREAK"),
											   FONT_ALIGN_CENTER, buttonSizeX/2, 3.5,
											   font, fontScale,
											   1.0, 1.0, 1.0, 1.0,
											   1.0, 1.0, 1.0, 1.0,
											   0.3, 0.3, 0.3, 1.0,
											   this);
	btnToggleBreakpoint->SetOn(false);
	SetLockableButtonDefaultColors(btnToggleBreakpoint);
	this->AddGuiElement(btnToggleBreakpoint);

	//
	float fs = buttonSizeX*2+gapX;
	
	lblAutolockText =	new CGuiLabel(new CSlrString("Show PC for:"), px, py, posZ, fs, fontHeight, LABEL_ALIGNED_LEFT, font, fontScale,
									  0.0f, 0.0f, 0.0f, 0.0f,
									  1.0f, 1.0f, 1.0f, 1.0f,
									  0.0f, 0.0f, NULL);
	lblAutolockText->image = NULL;
	this->AddGuiElement(lblAutolockText);
	
	lblAutolockScrollMode =	new CGuiLabel(new CSlrString(""), px, py, posZ, fs, fontHeight*2, LABEL_ALIGNED_CENTER, font, fontScale*2,
										  0.0f, 0.0f, 0.0f, 0.0f,
										  0.9f, 0.9f, 0.9f, 1.0f,
										  0.0f, 0.0f, NULL);
	lblAutolockScrollMode->image = NULL;
	this->AddGuiElement(lblAutolockScrollMode);
	
	
	btnLockCursor = new CGuiButtonSwitch(NULL, NULL, NULL,
										 px, py, posZ, buttonSizeX*2+gapX, buttonSizeY,
										 new CSlrString("LOCK CURSOR"),
										 FONT_ALIGN_CENTER, (buttonSizeX*2+gapX)/2, 3.5,
										 font, fontScale,
										 1.0, 1.0, 1.0, 1.0,
										 1.0, 1.0, 1.0, 1.0,
										 0.3, 0.3, 0.3, 1.0,
										 this);
	btnLockCursor->SetOn(false);
	SetSwitchButtonDefaultColors(btnLockCursor);
	this->AddGuiElement(btnLockCursor);
	
	
	// n/a todo
	//btnShowWithBorder->SetEnabled(false);
	
	UpdateApplyScrollRegister();
	
}

void CViewC64VicControl::HideGuiButtons()
{
	btnModeStandard->visible = false;
	btnModeExtended->visible = false;
	btnModeText->visible = false;
	btnModeBitmap->visible = false;
	btnModeHires->visible = false;
	btnModeMulti->visible = false;
	this->lstScreenAddresses->visible = false;
	this->lstCharsetAddresses->visible = false;
	this->lstBitmapAddresses->visible = false;
	lblScreenAddress->visible = false;
	lblCharsetAddress->visible = false;
	lblBitmapAddress->visible = false;
	btnShowSpritesGraphics->visible = false;
	btnShowSpritesFrames->visible = false;
	btnShowGrid->visible = false;
	btnShowWithBorder->visible = false;
	btnToggleBreakpoint->visible = false;
	btnLockCursor->visible = false;
	lblAutolockScrollMode->visible = false;
	lblAutolockText->visible = false;
}

void CViewC64VicControl::SetAutoScrollModeUI(int newMode)
{
	LOGD("CViewC64VicControl::SetAutoScrollModeUI: %d", newMode);
	
	if (newMode == AUTOSCROLL_DISASSEMBLE_RASTER_PC)
	{
		lblAutolockScrollMode->SetText(txtAutolockRasterPC);
	}
	else if (newMode == AUTOSCROLL_DISASSEMBLE_BITMAP_ADDRESS)
	{
		lblAutolockScrollMode->SetText(txtAutolockBitmapAddress);
	}
	else if (newMode == AUTOSCROLL_DISASSEMBLE_TEXT_ADDRESS)
	{
		lblAutolockScrollMode->SetText(txtAutolockTextAddress);
	}
	else if (newMode == AUTOSCROLL_DISASSEMBLE_COLOUR_ADDRESS)
	{
		lblAutolockScrollMode->SetText(txtAutolockColourAddress);
	}
	else if (newMode == AUTOSCROLL_DISASSEMBLE_CHARSET_ADDRESS)
	{
		lblAutolockScrollMode->SetText(txtAutolockCharsetAddress);
	}
}

void CViewC64VicControl::SetViciiPointersFromUI(uint16 *screenAddress, int *charsetAddress, int *bitmapBank)
{
	if (lstScreenAddresses->isLocked)
	{
		*screenAddress = lstScreenAddresses->selectedElement * 0x0400;
	}
	else
	{
		bool updatePosition = true;
		
		if (lstScreenAddresses->IsInside(guiMain->mousePosX, guiMain->mousePosY))
			updatePosition = false;
		
		// update controls
		int addrItemNum = *screenAddress / 0x0400;
		lstScreenAddresses->SetElement(addrItemNum, updatePosition, false);
	}
	
	if (lstCharsetAddresses->isLocked)
	{
		*charsetAddress = lstCharsetAddresses->selectedElement * 0x0800;
	}
	else
	{
		bool updatePosition = true;
		
		if (lstCharsetAddresses->IsInside(guiMain->mousePosX, guiMain->mousePosY))
			updatePosition = false;
		
		// update controls
		int addrItemNum = *charsetAddress / 0x0800;
		lstCharsetAddresses->SetElement(addrItemNum, updatePosition, false);
	}
	
	if (lstBitmapAddresses->isLocked)
	{
		*bitmapBank = lstBitmapAddresses->selectedElement * 0x2000;
	}
	else
	{
		// update controls
		int addrItemNum = *bitmapBank / 0x2000;
		lstBitmapAddresses->SetElement(addrItemNum, false, false);
	}

}

void CViewC64VicControl::RefreshStateButtonsUI(u8 *mc, u8 *eb, u8 *bm, u8 *blank)
{
	// text / bitmap
	if (btnModeText->IsOn())
	{
		SetButtonState(btnModeText, false);
		SetButtonState(btnModeBitmap, false);
		
		*bm = 0;
		*blank = 1;
	}
	else if (btnModeBitmap->IsOn())
	{
		SetButtonState(btnModeText, false);
		SetButtonState(btnModeBitmap, false);
		
		*bm = 1;
		*blank = 1;
	}
	else
	{
		if (*bm == 0)
		{
			SetButtonState(btnModeText, true);
			SetButtonState(btnModeBitmap, false);
		}
		else
		{
			SetButtonState(btnModeText, false);
			SetButtonState(btnModeBitmap, true);
		}
	}
	
	// hires / multi
	if (btnModeHires->IsOn())
	{
		SetButtonState(btnModeHires, false);
		SetButtonState(btnModeMulti, false);
		
		*mc = 0;
		*blank = 1;
	}
	else if (btnModeMulti->IsOn())
	{
		SetButtonState(btnModeHires, false);
		SetButtonState(btnModeMulti, false);
		
		*mc = 1;
		*blank = 1;
	}
	else
	{
		if (*mc == 0)
		{
			SetButtonState(btnModeHires, true);
			SetButtonState(btnModeMulti, false);
		}
		else
		{
			SetButtonState(btnModeHires, false);
			SetButtonState(btnModeMulti, true);
		}
	}
	
	// standard / extended
	if (btnModeStandard->IsOn())
	{
		SetButtonState(btnModeStandard, false);
		SetButtonState(btnModeExtended, false);
		
		*eb = 0;
		*blank = 1;
	}
	else if (btnModeExtended->IsOn())
	{
		SetButtonState(btnModeStandard, false);
		SetButtonState(btnModeExtended, false);
		
		*eb = 1;
		*blank = 1;
	}
	else
	{
		if (*eb == 0)
		{
			SetButtonState(btnModeStandard, true);
			SetButtonState(btnModeExtended, false);
		}
		else
		{
			SetButtonState(btnModeStandard, false);
			SetButtonState(btnModeExtended, true);
		}
	}

}


bool CViewC64VicControl::IsInside(GLfloat x, GLfloat y)
{
	if (viewFrame != NULL)
	{
		return viewFrame->IsInside(x, y);
	}
	
	return CGuiView::IsInside(x, y);
	
}

void CViewC64VicControl::SetPosition(GLfloat posX, GLfloat posY)
{
	CGuiView::SetPosition(posX, posY, posZ, this->sizeX, this->sizeY);
	
	float buttonSizeX = 25.0f;
	float buttonSizeY = 10.0f;
	float gapX = 2.0f;
	float gapY = 5.0f;
	float gapY2 = gapY/2.0f;
	
	float startX = posX; // + fontSize*40 + 8.0f;
	float px = startX;
	float py = posY + 0.0f;
	
	btnModeText->SetPosition(px, py, posZ, buttonSizeX, buttonSizeY);
	
	px += buttonSizeX + gapX;
	btnModeBitmap->SetPosition(px, py, posZ, buttonSizeX, buttonSizeY);
	
	py += buttonSizeY + gapY2;
	
	px = startX;
	
	btnModeHires->SetPosition(px, py, posZ, buttonSizeX, buttonSizeY);
	
	px += buttonSizeX + gapX;
	btnModeMulti->SetPosition(px, py, posZ, buttonSizeX, buttonSizeY);
	
	py += buttonSizeY + gapY2;
	px = startX;
	
	btnModeStandard->SetPosition(px, py, posZ, buttonSizeX, buttonSizeY);
	
	px += buttonSizeX + gapX;
	btnModeExtended->SetPosition(px, py, posZ, buttonSizeX, buttonSizeY);
	
	py += buttonSizeY + gapY2;
	px = startX;
	
	float listSizeX = 25.0f; //lstScreenAddresses->sizeX;
	float listSizeY = 49.5f;
	float listGapY = 3.0f;
	float listGapX = 1.0f;
	
	lblScreenAddress->SetPosition(px, py, posZ, lblScreenAddress->sizeX, lblScreenAddress->sizeY);
	
	px += listSizeX;
	
	lblCharsetAddress->SetPosition(px, py, posZ, lblCharsetAddress->sizeX, lblCharsetAddress->sizeY);
	
	px = startX + listGapX;
	py += lblScreenAddress->sizeY;
	
	
	lstScreenAddresses->SetPosition(px, py, posZ, listSizeX, listSizeY);
	
	px += listSizeX + listGapX;
	
	lstCharsetAddresses->SetPosition(px, py, posZ, listSizeX, listSizeY);
	py += listSizeY + listGapY;
	
	px = startX + listSizeX + listGapX;
	lblBitmapAddress->SetPosition(px, py, posZ, lblBitmapAddress->sizeX, lblBitmapAddress->sizeY);
	py += lblBitmapAddress->sizeY;
	
	lstBitmapAddresses->SetPosition(px, py, posZ, listSizeX, 32.0f);
	
	px = startX + listGapX;
	py += listSizeY + listGapY;
	
	
	//py += 4.0f;
	py -= 18.0f;

	btnApplyScrollRegister->SetPosition(px, py, posZ, buttonSizeX, buttonSizeY);
	
	px += buttonSizeX + gapX;
	btnShowBadLines->SetPosition(px, py, posZ, buttonSizeX, buttonSizeY);
	
	
	//
	px = startX + listGapX;
	py += buttonSizeY + gapY2;
	
	btnShowWithBorder->SetPosition(px, py, posZ, buttonSizeX, buttonSizeY);
	
	px += buttonSizeX + gapX;
	btnShowGrid->SetPosition(px, py, posZ, buttonSizeX, buttonSizeY);
	
	py += buttonSizeY + gapY2;
	
	//
	px = startX + listGapX;
	
	btnShowSpritesGraphics->SetPosition(px, py, posZ, buttonSizeX, buttonSizeY);
	
	px += buttonSizeX + gapX;
	btnShowSpritesFrames->SetPosition(px, py, posZ, buttonSizeX, buttonSizeY);
	
	py += buttonSizeY + gapY;
	
	//
	px = startX + listGapX;
	btnToggleBreakpoint->SetPosition(px, py, posZ, buttonSizeX, buttonSizeY);
	txtCursorPosX = px + buttonSizeX + gapX + 1.0f;
	txtCursorPosY = py + 1.0f;
	
	txtCursorCharPosX = txtCursorPosX;
	txtCursorCharPosY = py + 1.0f + 5.0f;
	
	py += 16.0f; //buttonSizeY + gapY;
	
	
	px = startX + listGapX;
	lblAutolockText->SetPosition(px, py, posZ, buttonSizeX*2 + gapX, buttonSizeY);
	
	py += 6.0f;
	lblAutolockScrollMode->SetPosition(px, py, posZ, buttonSizeX*2+gapX, fontHeight*2);
	
	btnLockCursor->visible = false; //SetPosition(px, py, posZ, buttonSizeX*2 + gapX, buttonSizeY);
	
}


CViewC64VicControl::~CViewC64VicControl()
{
}

void CViewC64VicControl::SetSwitchButtonDefaultColors(CGuiButtonSwitch *btn)
{
	btn->buttonSwitchOffColorR = 0.0f;
	btn->buttonSwitchOffColorG = 0.0f;
	btn->buttonSwitchOffColorB = 0.0f;
	btn->buttonSwitchOffColorA = 1.0f;
	
	btn->buttonSwitchOffColor2R = 0.3f;
	btn->buttonSwitchOffColor2G = 0.3f;
	btn->buttonSwitchOffColor2B = 0.3f;
	btn->buttonSwitchOffColor2A = 1.0f;
	
	btn->buttonSwitchOnColorR = 0.0f;
	btn->buttonSwitchOnColorG = 0.7f;
	btn->buttonSwitchOnColorB = 0.0f;
	btn->buttonSwitchOnColorA = 1.0f;
	
	btn->buttonSwitchOnColor2R = 0.3f;
	btn->buttonSwitchOnColor2G = 0.3f;
	btn->buttonSwitchOnColor2B = 0.3f;
	btn->buttonSwitchOnColor2A = 1.0f;
	
}

void CViewC64VicControl::SetLockableButtonDefaultColors(CGuiButtonSwitch *btn)
{
	btn->buttonSwitchOffColorR = 0.0f;
	btn->buttonSwitchOffColorG = 0.0f;
	btn->buttonSwitchOffColorB = 0.0f;
	btn->buttonSwitchOffColorA = 1.0f;
	
	btn->buttonSwitchOffColor2R = 0.3f;
	btn->buttonSwitchOffColor2G = 0.3f;
	btn->buttonSwitchOffColor2B = 0.3f;
	btn->buttonSwitchOffColor2A = 1.0f;
	
	btn->buttonSwitchOnColorR = 0.7f;
	btn->buttonSwitchOnColorG = 0.0f;
	btn->buttonSwitchOnColorB = 0.0f;
	btn->buttonSwitchOnColorA = 1.0f;
	
	btn->buttonSwitchOnColor2R = 0.3f;
	btn->buttonSwitchOnColor2G = 0.3f;
	btn->buttonSwitchOnColor2B = 0.3f;
	btn->buttonSwitchOnColor2A = 1.0f;
	
}


void CViewC64VicControl::SetButtonState(CGuiButtonSwitch *btn, bool isSet)
{
	if (isSet)
	{
		btn->buttonSwitchOffColorR = 0.0f;
		btn->buttonSwitchOffColorG = 0.7f;
		btn->buttonSwitchOffColorB = 0.0f;
		btn->buttonSwitchOffColorA = 1.0f;
	}
	else
	{
		btn->buttonSwitchOffColorR = 0.0f;
		btn->buttonSwitchOffColorG = 0.0f;
		btn->buttonSwitchOffColorB = 0.0f;
		btn->buttonSwitchOffColorA = 1.0f;
	}
	
	
}


void CViewC64VicControl::DoLogic()
{
	CGuiView::DoLogic();
}

void CViewC64VicControl::UnlockAll()
{
	vicDisplay->ResetCursorLock();

	lstScreenAddresses->SetListLocked(false);
	lstCharsetAddresses->SetListLocked(false);
	lstBitmapAddresses->SetListLocked(false);
	
	btnModeText->SetOn(false);
	btnModeBitmap->SetOn(false);
	btnModeHires->SetOn(false);
	btnModeMulti->SetOn(false);
	btnModeStandard->SetOn(false);
	btnModeExtended->SetOn(false);
}

void CViewC64VicControl::RefreshScreenStateOnly(vicii_cycle_state_t *viciiState)
{
	u8 mc;
	u8 eb;
	u8 bm;
	u8 blank;
	
	mc = (viciiState->regs[0x16] & 0x10) >> 4;
	eb = (viciiState->regs[0x11] & 0x40) >> 6;
	bm = (viciiState->regs[0x11] & 0x20) >> 5;
	
	blank = (vicii.regs[0x11] & 0x10) >> 4;
	
	
	// text / bitmap
	if (btnModeText->IsOn())
	{
		SetButtonState(btnModeText, false);
		SetButtonState(btnModeBitmap, false);
		
		bm = 0;
		blank = 1;
	}
	else if (btnModeBitmap->IsOn())
	{
		SetButtonState(btnModeText, false);
		SetButtonState(btnModeBitmap, false);
		
		bm = 1;
		blank = 1;
	}
	else
	{
		if (bm == 0)
		{
			SetButtonState(btnModeText, true);
			SetButtonState(btnModeBitmap, false);
		}
		else
		{
			SetButtonState(btnModeText, false);
			SetButtonState(btnModeBitmap, true);
		}
	}
	
	// hires / multi
	if (btnModeHires->IsOn())
	{
		SetButtonState(btnModeHires, false);
		SetButtonState(btnModeMulti, false);
		
		mc = 0;
		blank = 1;
	}
	else if (btnModeMulti->IsOn())
	{
		SetButtonState(btnModeHires, false);
		SetButtonState(btnModeMulti, false);
		
		mc = 1;
		blank = 1;
	}
	else
	{
		if (mc == 0)
		{
			SetButtonState(btnModeHires, true);
			SetButtonState(btnModeMulti, false);
		}
		else
		{
			SetButtonState(btnModeHires, false);
			SetButtonState(btnModeMulti, true);
		}
	}
	
	// standard / extended
	if (btnModeStandard->IsOn())
	{
		SetButtonState(btnModeStandard, false);
		SetButtonState(btnModeExtended, false);
		
		eb = 0;
		blank = 1;
	}
	else if (btnModeExtended->IsOn())
	{
		SetButtonState(btnModeStandard, false);
		SetButtonState(btnModeExtended, false);
		
		eb = 1;
		blank = 1;
	}
	else
	{
		if (eb == 0)
		{
			SetButtonState(btnModeStandard, true);
			SetButtonState(btnModeExtended, false);
		}
		else
		{
			SetButtonState(btnModeStandard, false);
			SetButtonState(btnModeExtended, true);
		}
	}
	
	// refresh texture of C64's character mode screen
	u8 *screen_ptr;
	u8 *color_ram_ptr;
	u8 *chargen_ptr;
	u8 *bitmap_low_ptr;
	u8 *bitmap_high_ptr;
	u8 colors[0x0F];
	
	this->vicDisplay->GetViciiPointers(viciiState, &screen_ptr, &color_ram_ptr, &chargen_ptr, &bitmap_low_ptr, &bitmap_high_ptr, colors);
}

void CViewC64VicControl::RenderFocusBorder()
{
	if (this->focusElement != NULL)
	{
		this->focusElement->RenderFocusBorder();
	}
}

void CViewC64VicControl::Render()
{
	// update lock label brightness based on if PC is correct
	float fBright = 1.0f;
	
	if (c64SettingsVicStateRecordingMode == C64D_VICII_RECORD_MODE_NONE && vicDisplay->autoScrollMode == AUTOSCROLL_DISASSEMBLE_RASTER_PC)
	{
		fBright = 0.0f;
	}
	else if (vicDisplay->autoScrollMode != AUTOSCROLL_DISASSEMBLE_RASTER_PC
			 && vicDisplay->foundMemoryCellPC == false)
	{
		fBright = 0.3f;
	}
	
	if (btnLockCursor->IsOn())
	{
		lblAutolockScrollMode->textColorR = 1.0f * fBright;
		lblAutolockScrollMode->textColorG = 0.3f * fBright;
		lblAutolockScrollMode->textColorB = 0.3f * fBright;
		
	}
	else
	{
		lblAutolockScrollMode->textColorR = 0.9f * fBright;
		lblAutolockScrollMode->textColorG = 0.9f * fBright;
		lblAutolockScrollMode->textColorB = 0.9f * fBright;
	}
	
	//BlitRectangle(lblAutolockScrollMode->posX, lblAutolockScrollMode->posY, posZ, lblAutolockScrollMode->sizeX, lblAutolockScrollMode->sizeY, 1, 1, 0, 1);
	
	char buf[32];
	
	int rx = (int)(vicDisplay->rasterCursorPosX); // + 0x88);
	int ry = (int)(vicDisplay->rasterCursorPosY); // + 0x32);
	
	if (rx >= 0 && rx < 320 && ry >= 0 && ry < 200)
	{
		sprintf(buf, "%3d %3d", rx, ry);
		this->font->BlitText(buf, txtCursorPosX, txtCursorPosY, posZ, fontScale);
		
		int cx = (int) rx/8;
		int cy = (int) ry/8;
		sprintf(buf, "%3d %3d", cx, cy);
		this->font->BlitText(buf, txtCursorCharPosX, txtCursorCharPosY, posZ, fontScale);
	}
	
	//
	bool rasterCursorInsideScreen = vicDisplay->IsRasterCursorInsideScreen();
	
	if (rasterCursorInsideScreen || viewC64->isShowingRasterCross)
	{
		btnToggleBreakpoint->SetEnabled(true);
		
		if (viewC64->debugInterfaceC64->breakOnRaster)
		{
			int rasterLine;

			if (viewC64->isShowingRasterCross)
			{
				rasterLine = viewC64->rasterToShowY;
			}
			else
			{
				rasterLine = (int)(vicDisplay->rasterCursorPosY) + 0x32;
			}
			
			LOGD("rasterLine=%02x", rasterLine);
			

			std::map<uint16, CAddrBreakpoint *> *breakpointsMap = &(viewC64->debugInterfaceC64->breakpointsRaster);
			
			// find if breakpoint exists
			std::map<uint16, CAddrBreakpoint *>::iterator it = breakpointsMap->find(rasterLine);
			if (it == breakpointsMap->end())
			{
				btnToggleBreakpoint->SetOn(false);
			}
			else
			{
				btnToggleBreakpoint->SetOn(true);
			}
		}
		else
		{
			btnToggleBreakpoint->SetOn(false);
		}
	}
	else
	{
		btnToggleBreakpoint->SetEnabled(false);
	}

	// show badlines
	if (btnShowBadLines->IsOn())
	{
		this->vicDisplay->RenderBadLines();
	}
	
	vicii_cycle_state_t *viciiState = &(viewC64->viciiStateToShow);
	if (viciiState->bad_line)
	{
		btnShowBadLines->textColorR = 1.0f;
		btnShowBadLines->textColorOffR = 1.0f;
		btnShowBadLines->textColorG = 0.0f;
		btnShowBadLines->textColorOffG = 0.0f;
		btnShowBadLines->textColorB = 0.0f;
		btnShowBadLines->textColorOffB = 0.0f;
	}
	else
	{
		btnShowBadLines->textColorR = 1.0f;
		btnShowBadLines->textColorOffR = 1.0f;
		btnShowBadLines->textColorG = 1.0f;
		btnShowBadLines->textColorOffG = 1.0f;
		btnShowBadLines->textColorB = 1.0f;
		btnShowBadLines->textColorOffB = 1.0f;
	}
	
	
	// render UI
	CGuiView::Render();
}

bool CViewC64VicControl::ListElementPreSelect(CGuiList *listBox, int elementNum)
{
	LOGD("CViewC64VicControl::ListElementPreSelect");
	guiMain->LockMutex();
	
	CGuiLockableList *list = (CGuiLockableList*)listBox;
	
	if (list->isLocked)
	{
		// click on the same element - unlock
		if (list->selectedElement == elementNum)
		{
			list->SetListLocked(false);
			guiMain->UnlockMutex();
			return true;
		}
	}
	
	list->SetListLocked(true);
	
	guiMain->UnlockMutex();
	
	return true;
}

void CViewC64VicControl::UpdateApplyScrollRegister()
{
	this->vicDisplay->applyScrollRegister = btnApplyScrollRegister->IsOn();
}

bool CViewC64VicControl::ButtonSwitchChanged(CGuiButtonSwitch *button)
{
	if (button == btnShowGrid)
	{
		this->vicDisplay->showGridLines = btnShowGrid->IsOn();
		return true;
	}
	
	if (button == btnApplyScrollRegister)
	{
		UpdateApplyScrollRegister();
		return true;
	}
	
	if (button == btnShowWithBorder)
	{
		SwitchBorderType();
		return true;
	}
	
	if (button == btnShowSpritesFrames)
	{
		this->vicDisplay->showSpritesFrames = btnShowSpritesFrames->IsOn();
		return true;
	}

	if (button == btnShowSpritesGraphics)
	{
		this->vicDisplay->showSpritesGraphics = btnShowSpritesGraphics->IsOn();
		return true;
	}

	if (button == btnToggleBreakpoint)
	{
		vicDisplay->ToggleVICRasterBreakpoint();
		return true;
	}
	
	if (button->IsOn())
	{
		if (button == btnModeText)
		{
			btnModeBitmap->SetOn(false);
		}
		else if (button == btnModeBitmap)
		{
			btnModeText->SetOn(false);
		}
		else if (button == btnModeStandard)
		{
			btnModeExtended->SetOn(false);
		}
		else if (button == btnModeExtended)
		{
			btnModeStandard->SetOn(false);
		}
		else if (button == btnModeHires)
		{
			btnModeMulti->SetOn(false);
		}
		else if (button == btnModeMulti)
		{
			btnModeHires->SetOn(false);
		}
	}
	
	return true;
}

void CViewC64VicControl::SwitchBorderType()
{
	u8 borderType = this->vicDisplay->showDisplayBorderType;
	
	if (borderType == VIC_DISPLAY_SHOW_BORDER_NONE)
	{
		borderType = VIC_DISPLAY_SHOW_BORDER_VISIBLE_AREA;
		this->btnShowWithBorder->SetOn(true);
	}
	else if (borderType == VIC_DISPLAY_SHOW_BORDER_VISIBLE_AREA)
	{
		borderType = VIC_DISPLAY_SHOW_BORDER_FULL;
		this->btnShowWithBorder->SetOn(true);
	}
	else if (borderType == VIC_DISPLAY_SHOW_BORDER_FULL)
	{
		borderType = VIC_DISPLAY_SHOW_BORDER_NONE;
		this->btnShowWithBorder->SetOn(false);
	}
	
	this->vicDisplay->SetShowDisplayBorderType(borderType);
	
	c64SettingsVicDisplayBorderType = borderType;
	C64DebuggerStoreSettings();

}

void CViewC64VicControl::SetBorderType(u8 newBorderType)
{
	this->vicDisplay->showDisplayBorderType = newBorderType;
	
	if (newBorderType == VIC_DISPLAY_SHOW_BORDER_FULL
		|| newBorderType == VIC_DISPLAY_SHOW_BORDER_VISIBLE_AREA)
	{
		this->btnShowWithBorder->SetOn(true);
	}
	else if (newBorderType == VIC_DISPLAY_SHOW_BORDER_NONE)
	{
		this->btnShowWithBorder->SetOn(false);
	}
	
	this->vicDisplay->SetShowDisplayBorderType(newBorderType);
	
}

void CViewC64VicControl::Render(GLfloat posX, GLfloat posY)
{
	CGuiView::Render(posX, posY);
}


//@returns is consumed
bool CViewC64VicControl::DoTap(GLfloat x, GLfloat y)
{
	LOGG("CViewC64VicControl::DoTap:  x=%f y=%f", x, y);
	
	if (lblAutolockText->IsInside(x, y) || lblAutolockScrollMode->IsInside(x, y))
	{
		LOGTODO("tap does not work sometimes due to too small area size of CViewC64VicControl");
		
		this->vicDisplay->SetNextAutoScrollMode();
	}
	
	return CGuiView::DoTap(x, y);
}

bool CViewC64VicControl::DoRightClick(GLfloat x, GLfloat y)
{
	if (viewC64->viewC64Screen->IsInsideViewNonVisible(x, y))
	{
		if (viewC64->viewC64Screen->visible)
		{
			viewC64->viewC64Screen->showZoomedScreen = true;
			viewC64->viewC64Screen->visible = false;
		}
		else
		{
			viewC64->viewC64Screen->showZoomedScreen = false;
			viewC64->viewC64Screen->visible = true;
		}
		
		return true;
	}
	
	return CGuiView::DoRightClick(x, y);
}

bool CViewC64VicControl::DoFinishTap(GLfloat x, GLfloat y)
{
	LOGG("CViewC64VicControl::DoFinishTap: %f %f", x, y);
	return CGuiView::DoFinishTap(x, y);
}

//@returns is consumed
bool CViewC64VicControl::DoDoubleTap(GLfloat x, GLfloat y)
{
	LOGG("CViewC64VicControl::DoDoubleTap:  x=%f y=%f", x, y);
	return CGuiView::DoDoubleTap(x, y);
}

bool CViewC64VicControl::DoFinishDoubleTap(GLfloat x, GLfloat y)
{
	LOGG("CViewC64VicControl::DoFinishTap: %f %f", x, y);
	return CGuiView::DoFinishDoubleTap(x, y);
}

bool CViewC64VicControl::DoNotTouchedMove(GLfloat x, GLfloat y)
{
	return CGuiView::DoNotTouchedMove(x, y);
}

bool CViewC64VicControl::DoMove(GLfloat x, GLfloat y, GLfloat distX, GLfloat distY, GLfloat diffX, GLfloat diffY)
{
	return CGuiView::DoMove(x, y, distX, distY, diffX, diffY);
}

bool CViewC64VicControl::FinishMove(GLfloat x, GLfloat y, GLfloat distX, GLfloat distY, GLfloat accelerationX, GLfloat accelerationY)
{
	return CGuiView::FinishMove(x, y, distX, distY, accelerationX, accelerationY);
}

bool CViewC64VicControl::DoScrollWheel(float deltaX, float deltaY)
{
	return CGuiView::DoScrollWheel(deltaX, deltaY);
}

bool CViewC64VicControl::InitZoom()
{
	return CGuiView::InitZoom();
}

bool CViewC64VicControl::DoZoomBy(GLfloat x, GLfloat y, GLfloat zoomValue, GLfloat difference)
{
	return false;
}

bool CViewC64VicControl::DoMultiTap(COneTouchData *touch, float x, float y)
{
	return CGuiView::DoMultiTap(touch, x, y);
}

bool CViewC64VicControl::DoMultiMove(COneTouchData *touch, float x, float y)
{
	return CGuiView::DoMultiMove(touch, x, y);
}

bool CViewC64VicControl::DoMultiFinishTap(COneTouchData *touch, float x, float y)
{
	return CGuiView::DoMultiFinishTap(touch, x, y);
}

void CViewC64VicControl::FinishTouches()
{
	return CGuiView::FinishTouches();
}

bool CViewC64VicControl::KeyDown(u32 keyCode, bool isShift, bool isAlt, bool isControl)
{
	if ((keyCode == 'l' || keyCode == 'L') && !isShift && !isAlt && !isControl)
	{
		btnLockCursor->DoSwitch();
		viewC64->viewC64Disassemble->changedByUser = false;
		if (btnLockCursor->IsOn())
		{
			this->vicDisplay->LockCursor();
		}
		else
		{
			this->vicDisplay->UnlockCursor();
		}
		return true;
	}
	
	if ((keyCode == ' ') && !isShift && !isAlt && !isControl)
	{
		this->vicDisplay->UnlockCursor();
		this->vicDisplay->SetAutoScrollMode(AUTOSCROLL_DISASSEMBLE_RASTER_PC);
		viewC64->viewC64Disassemble->isTrackingPC = true;
		viewC64->viewC64Disassemble->changedByUser = false;
		return true;
	}
	
	if ((keyCode == 'x' || keyCode == 'X') && !isShift && !isAlt && !isControl)
	{
		this->vicDisplay->SetNextAutoScrollMode();
		return true;
	}
	
	if ((keyCode == 'r' || keyCode == 'R') && !isShift && !isAlt && !isControl)
	{
		// Raster
		this->vicDisplay->SetAutoScrollMode(AUTOSCROLL_DISASSEMBLE_RASTER_PC);
		return true;
	}
	else if ((keyCode == 's' || keyCode == 'S') && !isShift && !isAlt && !isControl)
	{
		// Screen
		this->vicDisplay->SetAutoScrollMode(AUTOSCROLL_DISASSEMBLE_TEXT_ADDRESS);
		return true;
	}
	else if ((keyCode == 'b' || keyCode == 'B') && !isShift && !isAlt && !isControl)
	{
		// Screen
		this->vicDisplay->SetAutoScrollMode(AUTOSCROLL_DISASSEMBLE_BITMAP_ADDRESS);
		return true;
	}
	else if ((keyCode == 'c' || keyCode == 'C') && !isShift && !isAlt && !isControl)
	{
		// Screen
		this->vicDisplay->SetAutoScrollMode(AUTOSCROLL_DISASSEMBLE_COLOUR_ADDRESS);
		return true;
	}
	else if ((keyCode == 't' || keyCode == 'T') && !isShift && !isAlt && !isControl)
	{
		// Screen
		this->vicDisplay->SetAutoScrollMode(AUTOSCROLL_DISASSEMBLE_CHARSET_ADDRESS);
		return true;
	}
	else if ((keyCode == 'v' || keyCode == 'V') && !isShift && !isAlt && !isControl)
	{
		this->SwitchBorderType();
		return true;
	}
	
	
	return false; //CGuiView::KeyDown(keyCode, isShift, isAlt, isControl);
}

bool CViewC64VicControl::KeyUp(u32 keyCode, bool isShift, bool isAlt, bool isControl)
{
	if (keyCode == MTKEY_ARROW_UP
		|| keyCode == MTKEY_ARROW_DOWN
		|| keyCode == MTKEY_ARROW_LEFT
		|| keyCode == MTKEY_ARROW_RIGHT)
	{
		return this->vicDisplay->KeyUp(keyCode, isShift, isAlt, isControl);
	}
	
	return CGuiView::KeyUp(keyCode, isShift, isAlt, isControl);
}

bool CViewC64VicControl::KeyPressed(u32 keyCode, bool isShift, bool isAlt, bool isControl)
{
	return CGuiView::KeyPressed(keyCode, isShift, isAlt, isControl);
}

void CViewC64VicControl::ActivateView()
{
	LOGG("CViewC64VicControl::ActivateView()");
}

void CViewC64VicControl::DeactivateView()
{
	LOGG("CViewC64VicControl::DeactivateView()");
	
	if (!this->btnLockCursor->IsOn())
	{
		vicDisplay->ResetCursorLock();
		
		vicDisplay->UpdateRasterCursorPos();
		vicDisplay->UpdateViciiState();
	}
	
}

