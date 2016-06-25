#include "CViewDataDump.h"
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
#include "SYS_Threading.h"
#include "CGuiEditHex.h"
#include "VID_ImageBinding.h"
#include "CViewDisassemble.h"
#include "C64DebugInterface.h"
#include "C64SettingsStorage.h"
#include "C64KeyboardShortcuts.h"
#include <math.h>

CViewDataDump::CViewDataDump(GLfloat posX, GLfloat posY, GLfloat posZ, GLfloat sizeX, GLfloat sizeY,
							 CSlrDataAdapter *dataAdapter, CViewMemoryMap *viewMemoryMap, CViewDisassemble *viewDisassemble,
							 C64DebugInterface *debugInterface)
: CGuiView(posX, posY, posZ, sizeX, sizeY)
{
	this->name = "CViewDataDump";
	this->dataAdapter = dataAdapter;
	this->viewMemoryMap = viewMemoryMap;
	this->viewDisassemble = viewDisassemble;
	
	this->debugInterface = debugInterface;
	
	this->viewMemoryMap->SetViewC64DataDump(this);

	fontCBM1 = viewC64->fontCBM1;
	fontCBM2 = viewC64->fontCBM2;
	
	fontSize = 5.0f;
	
	fontBytes = guiMain->fntConsole;
	
	fontCharacters = fontCBM1;

	dataShowStart = 0;
	dataShowEnd = 0;
	dataShowSize = 0;
	dataAddr = 0;
	
	numberOfBytesPerLine = 8;
	
	numberOfLines = 0;
	editCursorPositionX = 0;
	editCursorPositionY = 0;
	
	numberOfCharactersToShow = 5;
	numberOfSpritesToShow = 4;
	
	editHex = new CGuiEditHex(this);
	editHex->isCapitalLetters = false;
	isEditingValue = false;
	
	isEditingValueAddr = false;
	
	strTemp = new CSlrString();

	mutex = new CSlrMutex();

	renderDataWithColors = false;
	
	// init images for characters
	for (int i = 0; i < numberOfCharactersToShow; i++)
	{
		// alloc image that will store character pixels
		CImageData *imageData = new CImageData(16, 16, IMG_TYPE_RGBA);
		imageData->AllocImage(false, true);
		
		charactersImageData.push_back(imageData);
		
		/// init CSlrImage with empty image (will be deleted by loader)
		CImageData *emptyImageData = new CImageData(16, 16, IMG_TYPE_RGBA);
		emptyImageData->AllocImage(false, true);
		
		CSlrImage *imageCharacter = new CSlrImage(true, false);
		imageCharacter->LoadImage(emptyImageData, RESOURCE_PRIORITY_STATIC, false);
		imageCharacter->resourceType = RESOURCE_TYPE_IMAGE_DYNAMIC;
		imageCharacter->resourcePriority = RESOURCE_PRIORITY_STATIC;
		VID_PostImageBinding(imageCharacter, NULL);

		charactersImages.push_back(imageCharacter);
	}
	
	// init images for sprites
	for (int i = 0; i < numberOfSpritesToShow; i++)
	{
		// alloc image that will store character pixels
		CImageData *imageData = new CImageData(32, 32, IMG_TYPE_RGBA);
		imageData->AllocImage(false, true);
		
		spritesImageData.push_back(imageData);
		
		/// init CSlrImage with empty image (will be deleted by loader)
		CImageData *emptyImageData = new CImageData(32, 32, IMG_TYPE_RGBA);
		emptyImageData->AllocImage(false, true);
		
		CSlrImage *imageSprite = new CSlrImage(true, false);
		imageSprite->LoadImage(emptyImageData, RESOURCE_PRIORITY_STATIC, false);
		imageSprite->resourceType = RESOURCE_TYPE_IMAGE_DYNAMIC;
		imageSprite->resourcePriority = RESOURCE_PRIORITY_STATIC;
		VID_PostImageBinding(imageSprite, NULL);
		
		spritesImages.push_back(imageSprite);
	}
	
	previousClickTime = SYS_GetCurrentTimeInMillis();
	
	this->SetPosition(posX, posY, posZ, sizeX, sizeY);
}

void CViewDataDump::SetDataAdapter(CSlrDataAdapter *newDataAdapter)
{
	this->dataAdapter = newDataAdapter;
}

void CViewDataDump::SetPosition(GLfloat posX, GLfloat posY, GLfloat posZ, GLfloat sizeX, GLfloat sizeY)
{
	// calculate font sizes
	
//	fontBytesSize = 10.0f * fontScale;
//	fontCharactersSize = 2.1f * fontScale;
//	fontCharactersWidth = 8.4f * fontScale;

	fontBytesSize = fontSize;
	fontCharactersSize = fontSize * 0.21f;
	fontCharactersWidth = fontSize * 0.84f;
	
	markerSizeX = fontSize*2.0f;
	markerSizeY = fontSize;

	gapAddress = fontSize;
	gapHexData = 0.5f*fontBytesSize;
	gapDataCharacters = 0.5f*fontBytesSize;

	
	CGuiView::SetPosition(posX, posY, posZ, sizeX, sizeY);
}

void CViewDataDump::DoLogic()
{	
}

bool CViewDataDump::FindDataPosition(float x, float y, int *dataPositionX, int *dataPositionY, int *dataPositionAddr)
{
	float px = posX;
	float py = posY;
	
	int addr = dataShowStart;
	
	int dy = 0;
	while (true)
	{
		px = posX;
		int a = addr;
		
		px += 5*fontBytesSize;
		
		float nextpy = py + fontCharactersWidth;
		
		// data bytes
		for (int dx = 0; dx < numberOfBytesPerLine; dx++)
		{
			float nextpx = px + 2.0*fontBytesSize;
			if (y >= py && y <= nextpy && x >= px && x <= nextpx)
			{
				*dataPositionX = dx;
				*dataPositionY = dy;
				*dataPositionAddr = a;
				
				//LOGD("found data position=%d %d %4.4x", *dataPositionX, *dataPositionY, *dataPositionAddr);

				return true;
			}
			
			a++;
			px = nextpx + 0.5*fontBytesSize;
		}
		
		px += 0.5f*fontBytesSize;
		
		addr += numberOfBytesPerLine;
		
		dy++;
		
		py += fontCharactersWidth;
		if (py+fontCharactersWidth > posEndY)
			break;
	}
	
	return false;
}

int CViewDataDump::GetAddrFromDataPosition(int dataPositionX, int dataPositionY)
{
	return dataShowStart + dataPositionY*numberOfBytesPerLine + dataPositionX;
}


void CViewDataDump::Render()
{
//	if (debugInterface->GetSettingIsWarpSpeed() == true)
//		return;

	char buf[256+64];
	
	float px = posX;
	float py = posY;
	
	int addr = dataShowStart;
		
	int dy = 0;
	
	int numberOfLines2 = numberOfLines/2;
	
	float cx = 0.0f;
	float cy = 0.0f;
	
	float fontBytesSize40 = 4*fontBytesSize;
	float fontBytesSize40_gap = fontBytesSize40 + gapAddress;
	float fontBytesSize20_gap = 2.0*fontBytesSize + gapHexData;
	float fontBytesSize05 = gapDataCharacters; //0.5f*fontBytesSize;
	
	while (true)
	{
		px = posX;
		int a = addr;
		
		if (isEditingValueAddr == false)
		{
//			if (isVisibleEditCursor == false)
//			{
//				sprintfHexCode16(buf, addr);
//			}
//			else
			{
				if (dy == editCursorPositionY)
				{
					int addrEdit = GetAddrFromDataPosition(editCursorPositionX, editCursorPositionY);
					sprintfHexCode16(buf, addrEdit);
					
					BlitFilledRectangle(px, py, posZ, fontBytesSize40, fontBytesSize, 0.0f, 0.7f, 0.0f, 1.0f);
				}
				else
				{
					sprintfHexCode16(buf, addr);
				}
			}
			fontBytes->BlitText(buf, px, py, posZ, fontBytesSize);
		}
		else
		{
			if (dy == numberOfLines2)
			{
				fontBytes->BlitTextColor(editHex->textWithCursor, px, py, posZ, fontBytesSize, 1.0f, 1.0f, 1.0f, 1.0f);
			}
			else
			{
				sprintfHexCode16(buf, addr);
				fontBytes->BlitText(buf, px, py, posZ, fontBytesSize);
			}
		}
		
		px += fontBytesSize40_gap;
		
		// data bytes
		for (int dx = 0; dx < numberOfBytesPerLine; dx++)
		{
			bool isAvailable;
			byte value;
			dataAdapter->AdapterReadByte(a, &value, &isAvailable);
			if (isAvailable)
			{
				CViewMemoryMapCell *cell = viewMemoryMap->memoryCells[a];
				
				if (cell->isExecuteCode)
				{
					BlitFilledRectangle(px, py, posZ, markerSizeX, markerSizeY,
										colorExecuteCodeR, colorExecuteCodeG, colorExecuteCodeB, colorExecuteCodeA);
				}
				else if (cell->isExecuteArgument)
				{
					BlitFilledRectangle(px, py, posZ, markerSizeX, markerSizeY,
										colorExecuteArgumentR, colorExecuteArgumentG, colorExecuteArgumentB, colorExecuteArgumentA);
				}
				BlitFilledRectangle(px, py, posZ, markerSizeX, markerSizeY, cell->sr, cell->sg, cell->sb, cell->sa);
								
				//BlitTextColor(CSlrString *text, GLfloat posX, GLfloat posY, GLfloat posZ, GLfloat scale, GLfloat colorR, GLfloat colorG, GLfloat colorB, GLfloat alpha)
				
				if (/*isVisibleEditCursor &&*/ editCursorPositionY == dy && editCursorPositionX == dx)
				{
					cx = px;
					cy = py;
					
					if (isEditingValue == false)
					{
						sprintfHexCode8(buf, value);
						fontBytes->BlitText(buf, px, py, posZ, fontBytesSize);
					}
					else
					{
//						if (cell->isExecute)
						{
							fontBytes->BlitTextColor(editHex->textWithCursor, px, py, posZ, fontBytesSize, 1.0f, 1.0f, 1.0f, 1.0f);
						}
//						else
//						{
//							fontBytes->BlitTextColor(editHex->textWithCursor, px, py, posZ, fontBytesSize, 0.8f, 0.8f, 0.8f, 1.0f);
//						}
					}
					
					dataAddr = a;
				}
				else
				{
					sprintfHexCode8(buf, value);
//					if (cell->isExecute)
					{
						fontBytes->BlitTextColor(buf, px, py, posZ, fontBytesSize, 1.0f, 1.0f, 1.0f, 1.0f);
					}
//					else
//					{
//						fontBytes->BlitTextColor(buf, px, py, posZ, fontBytesSize, 0.8f, 0.8f, 0.8f, 1.0f);
//					}
				}
			}
			
			a++;
			px += fontBytesSize20_gap;
		}
		
		px += fontBytesSize05;
		
		// data characters
		a = addr;
		for (int dx = 0; dx < numberOfBytesPerLine; dx++)
		{
			byte value;
			dataAdapter->AdapterReadByte(a, &value);
			
			fontCharacters->BlitChar((u16)value, px, py, posZ, fontCharactersSize);
			
			px += fontCharactersWidth;
			a++;
		}

		addr += numberOfBytesPerLine;
		
		dy++;
		
		py += fontCharactersWidth;
		if (py+fontCharactersWidth > posEndY)
			break;
	}
	
	dataShowEnd = addr;
	dataShowSize = dataShowEnd - dataShowStart;
	numberOfLines = dy;
	
	// blit data cursor
	//if (isVisibleEditCursor)
	{
		BlitRectangle(cx, cy, posZ, fontBytesSize*2.0f, fontCharactersWidth, 0.3f, 1.0f, 0.3f, 0.5f, 1.3f);
	}
//	else
//	{
//		dataAddr = dataShowStart;
//	}
	
	// get VIC colors
	byte cD021, cD022, cD023;
	byte cD800;
	byte cD025, cD026, cD027;
	viewC64->debugInterface->GetVICColors(&cD021, &cD022, &cD023, &cD025, &cD026, &cD027, &cD800);

	// render characters
	UpdateCharacters(renderDataWithColors, cD021, cD022, cD023, cD800);

	px += 5.0f;
	py = posY;

	const float characterSize = 32.0f;
	
	for (std::list<CSlrImage *>::iterator it = charactersImages.begin(); it != charactersImages.end(); it++)
	{
		CSlrImage *image = *it;
		
		const float characterTexStartX = 4.0/16.0;
		const float characterTexStartY = 4.0/16.0;
		const float characterTexEndX = (4.0+8.0)/16.0;
		const float characterTexEndY = (4.0+8.0)/16.0;

		//BlitFilledRectangle(px, py, posZ, 32, 32, 0.5, 0.5, 1.0f, 1.0f);

		Blit(image, px, py, posZ, characterSize, characterSize, characterTexStartX, characterTexStartY, characterTexEndX, characterTexEndY);
		
		py += characterSize;
	}

	// render sprites
	UpdateSprites(renderDataWithColors, cD021, cD025, cD026, cD027);
	
	px += 40.0f;
	py = posY;
	
	const float scale = 1.9f;
	const float spriteSizeX = 24.0f * scale;
	const float spriteSizeY = 21.0f * scale;
	
	for (std::list<CSlrImage *>::iterator it = spritesImages.begin(); it != spritesImages.end(); it++)
	{
		CSlrImage *image = *it;
		
		// sprites are rendered upside down
		const float spriteTexStartX = 4.0/32.0;
		const float spriteTexStartY = (32.0-4.0)/32.0;
		const float spriteTexEndX = (4.0+24.0)/32.0;
		const float spriteTexEndY = (32.0-(4.0+21.0))/32.0;
		
		//BlitFilledRectangle(px, py, posZ, 32, 32, 0.5, 0.5, 1.0f, 1.0f);
		
		Blit(image, px, py, posZ, spriteSizeX, spriteSizeY, spriteTexStartX, spriteTexStartY, spriteTexEndX, spriteTexEndY);
		
		py += spriteSizeY;
	}

}

void CViewDataDump::UpdateCharacters(bool useColors, byte colorD021, byte colorD022, byte colorD023, byte colorD800)
{
	std::list<CSlrImage *>::iterator itImage = charactersImages.begin();
	std::list<CImageData *>::iterator itImageData =  charactersImageData.begin();
	
	int addr = dataAddr;

	while(itImage != charactersImages.end())
	{
		//LOGD("char#=%d dataAddr=%4.4x", zi++, addr);

		CSlrImage *image = *itImage;
		CImageData *imageData = *itImageData;
		
		byte characterData[8];
		
		for (int i = 0; i < 8; i++)
		{
			byte v;
			dataAdapter->AdapterReadByte(addr, &v);
			characterData[7-i] = v;
			addr++;
		}
		
		if (useColors == false)
		{
			ConvertCharacterDataToImage(characterData, imageData);
		}
		else
		{
			ConvertColorCharacterDataToImage(characterData, imageData, colorD021, colorD022, colorD023, colorD800, debugInterface);
		}

		
		// re-bind image
		image->ReplaceImageData(imageData);
		
		itImage++;
		itImageData++;
	}
}

void CViewDataDump::UpdateSprites(bool useColors, byte colorD021, byte colorD025, byte colorD026, byte colorD027)
{
	std::list<CSlrImage *>::iterator itImage = spritesImages.begin();
	std::list<CImageData *>::iterator itImageData =  spritesImageData.begin();
	
	int addr = dataAddr;
	
//	int zi = 0;
	while(itImage != spritesImages.end())
	{
//		LOGD("sprite#=%d dataAddr=%4.4x", zi++, addr);
		
		CSlrImage *image = *itImage;
		CImageData *imageData = *itImageData;
		
		byte spriteData[63];
		
		for (int i = 0; i < 63; i++)
		{
			byte v;
			dataAdapter->AdapterReadByte(addr, &v);
			spriteData[i] = v;
			addr++;
		}
		
		if (useColors == false)
		{
			ConvertSpriteDataToImage(spriteData, imageData);
		}
		else
		{
			ConvertColorSpriteDataToImage(spriteData, imageData, colorD021, colorD025, colorD026, colorD027, debugInterface);
		}
		
		addr++;
		
		// re-bind image
		image->ReplaceImageData(imageData);
		
		itImage++;
		itImageData++;
	}
}


bool CViewDataDump::DoTap(GLfloat x, GLfloat y)
{
	guiMain->LockMutex();
	
//	if (x >= posX && x <= posX+5*fontBytesSize)
//	{
//		isVisibleEditCursor = false;
//		return true;
//	}
	
	int dataPositionX;
	int dataPositionY;
	int dataPositionAddr;
	
	if (isEditingValue)
		editHex->FinalizeEntering(MTKEY_ENTER, true);

	bool found = FindDataPosition(x, y, &dataPositionX, &dataPositionY, &dataPositionAddr);
	if (found == false)
	{
//		isVisibleEditCursor = false;
		
		guiMain->UnlockMutex();
		return true;
	}
	
//	if (isVisibleEditCursor && dataPositionX == editCursorPositionX && dataPositionY == editCursorPositionY)
//	{
//		isVisibleEditCursor = false;
//		
//		if (isEditingValue)
//			editHex->FinalizeEntering(MTKEY_ENTER);
//		
//		return true;
//	}

	if (dataPositionAddr == previousClickAddr)
	{
		long time = SYS_GetCurrentTimeInMillis() - previousClickTime;
		if (time < c64SettingsDoubleClickMS)
		{
			// double click
			viewDisassemble->ScrollToAddress(dataPositionAddr);
		}
	}
	
	previousClickTime = SYS_GetCurrentTimeInMillis();
	previousClickAddr = dataPositionAddr;
	
	editCursorPositionX = dataPositionX;
	editCursorPositionY = dataPositionY;
	
	isEditingValue = false;

	
//	isVisibleEditCursor = true;

	guiMain->UnlockMutex();
	return true;
}

bool CViewDataDump::DoScrollWheel(float deltaX, float deltaY)
{
//	LOGD("CViewDataDump::DoScrollWheel: %f %f", deltaX, deltaY);
	guiMain->LockMutex();
	
	int dy = fabs(round(deltaY));
	
	bool scrollUp = (deltaY > 0);
	
	for (int i = 0; i < dy; i++)
	{
		if (scrollUp)
		{
			ScrollDataUp();
		}
		else
		{
			ScrollDataDown();
		}
	}
	
	guiMain->UnlockMutex();
	return true;
	return false;
}



void CViewDataDump::ScrollDataUp()
{
	int newDataAddr;
	newDataAddr = dataShowStart - numberOfBytesPerLine;
	if (newDataAddr < 0)
	{
		newDataAddr = 0;
	}
	
	dataShowStart = newDataAddr;
}

void CViewDataDump::ScrollDataPageUp()
{
	int newDataAddr;
	newDataAddr = dataShowStart - dataShowSize;
	if (newDataAddr < 0)
	{
		newDataAddr = 0;
	}
	
	dataShowStart = newDataAddr;
}

void CViewDataDump::ScrollDataDown()
{
	int newDataAddr;
	newDataAddr = dataShowStart + numberOfBytesPerLine;
	
	if (newDataAddr + dataShowSize > dataAdapter->AdapterGetDataLength())
	{
		newDataAddr = dataAdapter->AdapterGetDataLength() - dataShowSize;
	}
	
	dataShowStart = newDataAddr;
}

void CViewDataDump::ScrollDataPageDown()
{
	int newDataAddr;
	newDataAddr = dataShowEnd;
	
	if (newDataAddr + dataShowSize > dataAdapter->AdapterGetDataLength())
	{
		newDataAddr = dataAdapter->AdapterGetDataLength() - dataShowSize;
	}
	
	dataShowStart = newDataAddr;
}

void CViewDataDump::ScrollToAddress(int address)
{
	LOGD("CViewDataDump::ScrollToAddress: address=%4.4x", address);

	if (this->visible == false || numberOfBytesPerLine == 0)
		return;
	
	int laddr = floor((double)(address / numberOfBytesPerLine)) * numberOfBytesPerLine;
	
	//LOGD("laddr=%4.4x", laddr);
	
	int saddr = laddr - (numberOfLines/2 * numberOfBytesPerLine);
	
	//LOGD("saddr=%4.4x", saddr);
	
	if (saddr < 0)
	{
		saddr = 0;
	}
	
	int saddr2 = saddr + (numberOfLines * numberOfBytesPerLine);
	
	if (saddr2 > dataAdapter->AdapterGetDataLength())
	{
		saddr = dataAdapter->AdapterGetDataLength() - dataShowSize;
	}
	
	int caddr = address - saddr;
	
	dataShowStart = saddr;

	//isVisibleEditCursor = true;
	editCursorPositionY = floor((double)(caddr / numberOfBytesPerLine));
	editCursorPositionX = caddr - (numberOfBytesPerLine * editCursorPositionY);
	dataAddr = address;

}


bool CViewDataDump::KeyDown(u32 keyCode, bool isShift, bool isAlt, bool isControl)
{
	//LOGD("CViewDataDump::keyDown=%4.4x", keyCode);
	
	// change charset
	if ((keyCode == MTKEY_LSHIFT && isAlt) || (keyCode == MTKEY_LALT && isShift))
	{
		if (fontCharacters == fontCBM1)
		{
			fontCharacters = fontCBM2;
		}
		else
		{
			fontCharacters = fontCBM1;
		}
		
		//viewC64->viewC64Screen->KeyUpModifierKeys(isShift, isAlt, isControl);
		return false;
	}
	
	if (isEditingValue || isEditingValueAddr)
	{
		editHex->KeyDown(keyCode);
		return true;
	}
	
	CSlrKeyboardShortcut *keyboardShortcut = viewC64->keyboardShortcuts->FindShortcut(KBZONE_DISASSEMBLE, keyCode, isShift, isAlt, isControl);
	if (keyboardShortcut == viewC64->keyboardShortcuts->kbsToggleTrackPC)
	{
		return viewDisassemble->KeyDown(keyCode, isShift, isAlt, isControl);
	}
	
	keyboardShortcut = viewC64->keyboardShortcuts->FindShortcut(KBZONE_MEMORY, keyCode, isShift, isAlt, isControl);
	
	if (keyboardShortcut == viewC64->keyboardShortcuts->kbsGoToAddress)
	{
		int adr = dataShowStart + dataShowSize/2;
		editHex->SetValue(adr, 4);
		
		isEditingValue = false;
		isEditingValueAddr = true;
		
		viewC64->viewC64Screen->KeyUpModifierKeys(isShift, isAlt, isControl);
		return true;
	}
	
	// mimic shift+cursor up/down as page up/down
	if (keyCode == MTKEY_PAGE_DOWN)
	{
		keyCode = MTKEY_ARROW_DOWN;
		isShift = true;
	}
	else if (keyCode == MTKEY_PAGE_UP)
	{
		keyCode = MTKEY_ARROW_UP;
		isShift = true;
	}

//	// simple data show/scroll
//	if (isVisibleEditCursor == false)
//	{
//		if (keyCode == MTKEY_ARROW_DOWN)
//		{
//			if (isShift == false)
//			{
//				ScrollDataDown();
//			}
//			else
//			{
//				ScrollDataPageDown();
//			}
//			return true;
//		}
//		else if (keyCode == MTKEY_ARROW_UP)
//		{
//			if (isShift == false)
//			{
//				ScrollDataUp();
//			}
//			else
//			{
//				ScrollDataPageUp();
//			}
//			return true;
//		}
//		else if (keyCode == MTKEY_ARROW_LEFT || keyCode == MTKEY_ARROW_RIGHT)
//		{
//			return true;
//		}
//	}
//	else
	{
		// show editing cursor
		if (keyCode == MTKEY_ARROW_DOWN)
		{
			if (isShift == false)
			{
				if (editCursorPositionY < numberOfLines-1)
				{
					editCursorPositionY++;
				}
				else
				{
					ScrollDataDown();
				}
			}
			else
			{
				ScrollDataPageDown();
			}
			return true;
		}
		else if (keyCode == MTKEY_ARROW_UP)
		{
			if (isShift == false)
			{
				if (editCursorPositionY > 0)
				{
					editCursorPositionY--;
				}
				else
				{
					ScrollDataUp();
				}
			}
			else
			{
				ScrollDataPageUp();
			}
			return true;
		}
		else if (keyCode == MTKEY_ARROW_LEFT)
		{
			if (editCursorPositionX > 0)
			{
				editCursorPositionX--;
			}
			else
			{
				if (editCursorPositionY > 0)
				{
					editCursorPositionX = numberOfBytesPerLine-1;
					editCursorPositionY--;
				}
				else
				{
					if (dataShowStart > 0)
					{
						ScrollDataUp();
						editCursorPositionX = numberOfBytesPerLine-1;
					}
				}
			}
			return true;
		}
		else if (keyCode == MTKEY_ARROW_RIGHT)
		{
			if (editCursorPositionX < numberOfBytesPerLine-1)
			{
				editCursorPositionX++;
			}
			else
			{
				if (editCursorPositionY < numberOfLines-1)
				{
					editCursorPositionX = 0;
					editCursorPositionY++;
				}
				else
				{
					if (dataShowStart + dataShowSize < dataAdapter->AdapterGetDataLength())
					{
						ScrollDataDown();
						editCursorPositionX = 0;
					}
				}
			}
			return true;
		}
		else if (keyCode == MTKEY_ENTER)
		{
			int addr = GetAddrFromDataPosition(editCursorPositionX, editCursorPositionY);
			byte v;
			dataAdapter->AdapterReadByte(addr, &v);
			editHex->SetValue(v, 2);
			isEditingValue = true;
			return true;
		}
		else if ((keyCode >= '0' && keyCode <= '9') || (keyCode >= 'a' && keyCode <= 'f'))
		{
			// mimic start editing
			this->KeyDown(MTKEY_ENTER, false, false, false);
			editHex->KeyDown(keyCode);
			return true;
		}
	}

	
	return false;
}

bool CViewDataDump::KeyUp(u32 keyCode, bool isShift, bool isAlt, bool isControl)
{
	if (isEditingValue || isEditingValueAddr)
		return true;
	
	if (keyCode == MTKEY_ARROW_DOWN || keyCode == MTKEY_ARROW_UP || keyCode == MTKEY_ARROW_LEFT || keyCode == MTKEY_ARROW_RIGHT || keyCode == MTKEY_ENTER)
		return true;
	
	return false;
}

void CViewDataDump::GuiEditHexEnteredValue(CGuiEditHex *editHex, u32 lastKeyCode, bool isCancelled)
{
	if (isCancelled)
		return;
	
	if (isEditingValue)
	{
		int addr = GetAddrFromDataPosition(editCursorPositionX, editCursorPositionY);
		byte v = editHex->value;
		dataAdapter->AdapterWriteByte(addr, v);
		
		isEditingValue = false;
		
		// move to next value?
	}
	else
	{
		int addr = editHex->value;
		ScrollToAddress(addr);
		isEditingValueAddr = false;
	}
	
}

