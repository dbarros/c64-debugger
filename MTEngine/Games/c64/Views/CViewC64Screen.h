#ifndef _CVIEWC64SCREEN_H_
#define _CVIEWC64SCREEN_H_

#include "CGuiView.h"

class CSlrMutex;
class C64DebugInterface;

class CViewC64Screen : public CGuiView
{
public:
	CViewC64Screen(GLfloat posX, GLfloat posY, GLfloat posZ, GLfloat sizeX, GLfloat sizeY, C64DebugInterface *debugInterface);
	virtual ~CViewC64Screen();

	virtual void Render();
	virtual void Render(GLfloat posX, GLfloat posY);
	//virtual void Render(GLfloat posX, GLfloat posY, GLfloat sizeX, GLfloat sizeY);
	virtual void DoLogic();

	virtual bool DoTap(GLfloat x, GLfloat y);
	virtual bool DoFinishTap(GLfloat x, GLfloat y);

	virtual bool DoDoubleTap(GLfloat x, GLfloat y);
	virtual bool DoFinishDoubleTap(GLfloat posX, GLfloat posY);

	virtual bool DoMove(GLfloat x, GLfloat y, GLfloat distX, GLfloat distY, GLfloat diffX, GLfloat diffY);
	virtual bool FinishMove(GLfloat x, GLfloat y, GLfloat distX, GLfloat distY, GLfloat accelerationX, GLfloat accelerationY);

	virtual bool InitZoom();
	virtual bool DoZoomBy(GLfloat x, GLfloat y, GLfloat zoomValue, GLfloat difference);
	
	// multi touch
	virtual bool DoMultiTap(COneTouchData *touch, float x, float y);
	virtual bool DoMultiMove(COneTouchData *touch, float x, float y);
	virtual bool DoMultiFinishTap(COneTouchData *touch, float x, float y);

	virtual void FinishTouches();

	virtual bool KeyDown(u32 keyCode, bool isShift, bool isAlt, bool isControl);
	virtual bool KeyUp(u32 keyCode, bool isShift, bool isAlt, bool isControl);
	virtual bool KeyPressed(u32 keyCode, bool isShift, bool isAlt, bool isControl);	// repeats
	
	virtual void ActivateView();
	virtual void DeactivateView();

	CImageData *imageDataScreen;
	CSlrImage *imageScreen;
	
	void RefreshScreen();

	float screenTexEndX, screenTexEndY;
	
	void KeyUpModifierKeys(bool isShift, bool isAlt, bool isControl);
	
	C64DebugInterface *debugInterface;
	
	virtual void SetPosition(GLfloat posX, GLfloat posY, GLfloat posZ, GLfloat sizeX, GLfloat sizeY);

	void UpdateRasterCrossFactors();
	
	float rasterScaleFactorX;
	float rasterScaleFactorY;
	
	float rasterCrossOffsetX;
	float rasterCrossOffsetY;
	
	float rasterCrossWidth;
	float rasterCrossWidth2;
	
	float rasterCrossSizeX;
	float rasterCrossSizeY;
	float rasterCrossSizeX2;
	float rasterCrossSizeY2;
	float rasterCrossSizeX34;
	float rasterCrossSizeY34;
	float rasterCrossSizeX3;
	float rasterCrossSizeY3;
	float rasterCrossSizeX4;
	float rasterCrossSizeY4;
	float rasterCrossSizeX6;
	float rasterCrossSizeY6;
	
	void RenderRaster(int rasterX, int rasterY);
	
	bool showMarkers;
	
	void SetZoomedScreenPos(float zoomedScreenPosX, float zoomedScreenPosY, float zoomedScreenSizeX, float zoomedScreenSizeY);
	void SetZoomedScreenLevel(float zoomedScreenLevel);
	void CalcZoomedScreenTextureFromRaster(int rasterX, int rasterY);
	void RenderZoomedScreen(int rasterX, int rasterY);
	
	bool showZoomedScreen;
	float zoomedScreenPosX;
	float zoomedScreenPosY;
	float zoomedScreenSizeX;
	float zoomedScreenSizeY;
	float zoomedScreenCenterX;
	float zoomedScreenCenterY;
	float zoomedScreenLevel;
	
	float zoomedScreenImageStartX;
	float zoomedScreenImageStartY;
	float zoomedScreenImageSizeX;
	float zoomedScreenImageSizeY;

	float zoomedScreenRasterScaleFactorX;
	float zoomedScreenRasterScaleFactorY;
	float zoomedScreenRasterOffsetX;
	float zoomedScreenRasterOffsetY;
	
};

#endif //_CVIEWC64SCREEN_H_
