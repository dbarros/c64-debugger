#include "CVicEditorLayerUnrestrictedBitmap.h"
#include "VID_Main.h"
#include "VID_ImageBinding.h"
#include "CViewC64.h"
#include "C64DebugInterface.h"
#include "CViewVicEditor.h"
#include "C64VicDisplayCanvas.h"
#include "CVicEditorLayerC64Canvas.h"

#define PIXEL_TRANSPARENT	0xFF

CVicEditorLayerUnrestrictedBitmap::CVicEditorLayerUnrestrictedBitmap(CViewVicEditor *vicEditor, char *layerName)
: CVicEditorLayer(vicEditor, layerName)
{
	C64DebugInterface *debugInterface = viewC64->debugInterfaceC64;
	
	this->isVisible = false;
	
	int w = 512;
	int h = 512;
	imageDataUnrestricted = new CImageData(w, h, IMG_TYPE_RGBA);
	imageDataUnrestricted->AllocImage(false, true);
	
	imageUnrestricted = new CSlrImage(true, true);
	imageUnrestricted->LoadImage(imageDataUnrestricted, RESOURCE_PRIORITY_STATIC, false);
	imageUnrestricted->resourceType = RESOURCE_TYPE_IMAGE_DYNAMIC;
	imageUnrestricted->resourcePriority = RESOURCE_PRIORITY_STATIC;
	VID_PostImageBinding(imageUnrestricted, NULL);

	// c64 screen texture boundaries
	screenTexEndX = (float)debugInterface->GetScreenSizeX() / 512.0f;
	screenTexEndY = 1.0f - (float)debugInterface->GetScreenSizeY() / 512.0f;
	
	///
	
	memset(map, PIXEL_TRANSPARENT, 384*272);

}

CVicEditorLayerUnrestrictedBitmap::~CVicEditorLayerUnrestrictedBitmap()
{
	
}

void CVicEditorLayerUnrestrictedBitmap::RefreshImage()
{
	imageUnrestricted->SetLoadImageData(imageDataUnrestricted);
	imageUnrestricted->ReBindImage();
	imageUnrestricted->loadImageData = NULL;
}

void CVicEditorLayerUnrestrictedBitmap::RenderMain(vicii_cycle_state_t *viciiState)
{
	RefreshImage();
	
	// nearest neighbour
	{
		glBindTexture(GL_TEXTURE_2D, imageUnrestricted->texture[0]);
		
		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);
	}
	
	if (vicEditor->viewVicDisplayMain->showDisplayBorderType == VIC_DISPLAY_SHOW_BORDER_VISIBLE_AREA
		|| vicEditor->viewVicDisplayMain->showDisplayBorderType == VIC_DISPLAY_SHOW_BORDER_NONE)
	{
		Blit(imageUnrestricted,
			 vicEditor->viewVicDisplayMain->visibleScreenPosX,
			 vicEditor->viewVicDisplayMain->visibleScreenPosY, -1,
			 vicEditor->viewVicDisplayMain->visibleScreenSizeX,
			 vicEditor->viewVicDisplayMain->visibleScreenSizeY,
			 0.0f, 1.0f, screenTexEndX, screenTexEndY);
		
	}
	
}

void CVicEditorLayerUnrestrictedBitmap::RenderPreview(vicii_cycle_state_t *viciiState)
{
	RefreshImage();
	
	// nearest neighbour
	{
		glBindTexture(GL_TEXTURE_2D, imageUnrestricted->texture[0]);
		
		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);
	}
	
	if (vicEditor->viewVicDisplayMain->showDisplayBorderType == VIC_DISPLAY_SHOW_BORDER_VISIBLE_AREA
		|| vicEditor->viewVicDisplayMain->showDisplayBorderType == VIC_DISPLAY_SHOW_BORDER_NONE)
	{
		Blit(imageUnrestricted,
			 vicEditor->viewVicDisplaySmall->visibleScreenPosX,
			 vicEditor->viewVicDisplaySmall->visibleScreenPosY, -1,
			 vicEditor->viewVicDisplaySmall->visibleScreenSizeX,
			 vicEditor->viewVicDisplaySmall->visibleScreenSizeY,
			 0.0f, 1.0f, screenTexEndX, screenTexEndY);
		
	}
}

void CVicEditorLayerUnrestrictedBitmap::ClearScreen()
{
	ClearScreen(0x00, 0x00);
}

void CVicEditorLayerUnrestrictedBitmap::ClearScreen(u8 charValue, u8 colorValue)
{
	memset(map, PIXEL_TRANSPARENT, 384*272);
	UpdateBitmapFromMap();
}

int CVicEditorLayerUnrestrictedBitmap::NumVisiblePixels()
{
	int numPixels = 0;
	for (int i = 0; i < (384*272); i++)
	{
		if (map[i] != PIXEL_TRANSPARENT)
		{
			numPixels++;
		}
	}
	
	return numPixels;
}

u8 CVicEditorLayerUnrestrictedBitmap::Paint(bool forceColorReplace, bool isDither, int x, int y, u8 colorLMB, u8 colorRMB, u8 colorSource, int charValue)
{
	if (isDither)
	{
		return this->PaintDither(x, y, colorLMB, colorRMB, colorSource);
	}
	else
	{
		this->ClearDitherMask();
		
		return this->PutColorAtPixel(x, y, colorLMB, colorRMB, colorSource);
	}
}

bool CVicEditorLayerUnrestrictedBitmap::GetColorAtPixel(int x, int y, u8 *color)
{
	int x2 = x+32;
	int y2 = y+35;

	if (x2 < 0 || x2 > 383
		|| y2 < 0 || y2 > 271)
		return false;
	
	u8 v = map[y2 * 384 + x2];
	
	if (v == PIXEL_TRANSPARENT)
		return false;
	
	*color = v;
	
	return true;
}

u8 CVicEditorLayerUnrestrictedBitmap::PutPixelUnrestrictedBitmap(int x, int y, u8 paintColor)
{
	LOGD(">>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>> PutPixelUnrestrictedBitmap %d %d %02x", x, y, paintColor);
	
	int x2 = x+32;
	int y2 = y+35;
	
	if (x2 < 0 || x2 > 383
		|| y2 < 0 || y2 > 271)
		return PAINT_RESULT_OUTSIDE;
	

	u8 result = PAINT_RESULT_OK;
	
	map[y2 * 384 + x2] = paintColor;
	
	C64DebugInterface *debugInterface = vicEditor->viewVicDisplayMain->debugInterface;
	
	u8 r, g, b;
	debugInterface->GetCBMColor(paintColor, &r, &g, &b);

	imageDataUnrestricted->SetPixelResultRGBA(x2, y2, r, g, b, 255);
	
	return result;
}

u8 CVicEditorLayerUnrestrictedBitmap::PaintDither(int x, int y, u8 colorLMB, u8 colorRMB, u8 colorSource)
{
	u8 color1, color2;
	if (colorSource == VICEDITOR_COLOR_SOURCE_LMB)
	{
		color1 = colorLMB;
		color2 = colorRMB;
	}
	else if (colorSource == VICEDITOR_COLOR_SOURCE_RMB)
	{
		color1 = colorRMB;
		color2 = colorLMB;
	}
	
	u8 paintColor = color1;
	
	// check if starting dither
	{
		LOGD("													---- isAltPressed: dither -----");
		{
			if (ditherMaskPosX == -1 || ditherMaskPosY == -1)
			{
				LOGD("******** START DITHER ********");
				// start dither painting
				if (colorSource == VICEDITOR_COLOR_SOURCE_LMB)
				{
					ditherMaskPosX = x;
				}
				else if (colorSource == VICEDITOR_COLOR_SOURCE_RMB)
				{
					ditherMaskPosX = x;
				}
				
				ditherMaskPosY = y;
			}
			
			int dX = abs(x - ditherMaskPosX) % 2;
			int dY = abs(y - ditherMaskPosY) % 2;
			
			int d = (dX + dY) % 2;
			
			LOGD("==================== dX=%d dY=%d d=%d", dX, dY, d);
			
			if (d != 0)
			{
				paintColor = color2;
			}
		}
	}
	
	return this->PutPixelUnrestrictedBitmap(x, y, paintColor);
	
}

// @returns painting status (ok, replaced color, blocked)
u8 CVicEditorLayerUnrestrictedBitmap::PutColorAtPixel(int x, int y, u8 colorLMB, u8 colorRMB, u8 colorSource)
{
	if (colorSource == VICEDITOR_COLOR_SOURCE_LMB)
	{
		return this->PutPixelUnrestrictedBitmap(x, y, colorLMB);
	}
	else
	{
		return this->PutPixelUnrestrictedBitmap(x, y, colorRMB);
	}
}

void CVicEditorLayerUnrestrictedBitmap::ClearDitherMask()
{
	ditherMaskPosX = -1;
	ditherMaskPosY = -1;
}

void CVicEditorLayerUnrestrictedBitmap::UpdateBitmapFromMap()
{
	C64DebugInterface *debugInterface = vicEditor->viewVicDisplayMain->debugInterface;
	
	for (int y = 0; y < 272; y++)
	{
		for (int x = 0; x < 384; x++)
		{
			u8 paintColor = map[y * 384 + x];
			
			if (paintColor == PIXEL_TRANSPARENT)
			{
				imageDataUnrestricted->SetPixelResultRGBA(x, y, 0, 0, 0, 0);
			}
			else
			{
				u8 r, g, b;
				debugInterface->GetCBMColor(paintColor, &r, &g, &b);
				
				imageDataUnrestricted->SetPixelResultRGBA(x, y, r, g, b, 255);
			}
			
		}
	}
}

bool CVicEditorLayerUnrestrictedBitmap::LoadFrom(CImageData *imageData)
{
	SYS_FatalExit("CVicEditorLayerUnrestrictedBitmap::LoadFrom: not implemented");
	
	if (imageData->width == 384 && imageData->height == 272)
	{
		
	}
	return false;
}

void CVicEditorLayerUnrestrictedBitmap::Serialise(CByteBuffer *byteBuffer)
{
	CVicEditorLayer::Serialise(byteBuffer);

	byteBuffer->PutBytes(map, 384*272);
}

void CVicEditorLayerUnrestrictedBitmap::Deserialise(CByteBuffer *byteBuffer, int version)
{
	CVicEditorLayer::Deserialise(byteBuffer, version);

	byteBuffer->GetBytes(map, 384*272);
}
