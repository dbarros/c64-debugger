#ifndef __CViewDataWatch__
#define __CViewDataWatch__

#include "CGuiView.h"
#include "DebuggerDefs.h"
#include <map>

class C64;
class CImageData;
class CSlrImage;
class CViewDataDump;
class C64DebugInterface;
class CSlrFont;
class CViewMemoryMap;
class CSlrDataAdapter;

class CDataWatchDetails
{
public:
	CDataWatchDetails(char *name, int addr);
	CDataWatchDetails(char *name, int addr, uint8 representation, int numberOfValues, uint8 bits);
	~CDataWatchDetails();
	
	void SetName(char *name);
	
	char *watchName;
	int addr;
	
	uint8 representation;
	int numberOfValues;
	uint8 bits;
	
};

class CViewDataWatch : public CGuiView
{
public:
	CViewDataWatch(GLfloat posX, GLfloat posY, GLfloat posZ, GLfloat sizeX, GLfloat sizeY,
				   CSlrDataAdapter *dataAdapter, CViewMemoryMap *viewMemoryMap, C64DebugInterface *c64);
	~CViewDataWatch();
	
	virtual void SetPosition(GLfloat posX, GLfloat posY, GLfloat posZ, GLfloat sizeX, GLfloat sizeY);

	virtual bool KeyDown(u32 keyCode, bool isShift, bool isAlt, bool isControl);
	virtual bool KeyUp(u32 keyCode, bool isShift, bool isAlt, bool isControl);
	virtual void DoLogic();
	virtual void Render();
	
	virtual bool DoTap(GLfloat x, GLfloat y);

	virtual bool DoScrollWheel(float deltaX, float deltaY);
	virtual bool InitZoom();
	virtual bool DoZoomBy(GLfloat x, GLfloat y, GLfloat zoomValue, GLfloat difference);
	virtual bool DoMove(GLfloat x, GLfloat y, GLfloat distX, GLfloat distY, GLfloat diffX, GLfloat diffY);
	virtual bool FinishMove(GLfloat x, GLfloat y, GLfloat distX, GLfloat distY, GLfloat accelerationX, GLfloat accelerationY);

	virtual bool DoRightClick(GLfloat x, GLfloat y);
	virtual bool DoRightClickMove(GLfloat x, GLfloat y, GLfloat distX, GLfloat distY, GLfloat diffX, GLfloat diffY);
	virtual bool FinishRightClickMove(GLfloat x, GLfloat y, GLfloat distX, GLfloat distY, GLfloat accelerationX, GLfloat accelerationY);

	virtual bool DoNotTouchedMove(GLfloat x, GLfloat y);

	CSlrFont *font;
	float fontSize;
	
	C64DebugInterface *debugInterface;
	CViewMemoryMap *viewMemoryMap;
	CSlrDataAdapter *dataAdapter;
	
	CViewDataDump *viewDataDump;
	void SetViewC64DataDump(CViewDataDump *viewDataDump);
	
	float markerSizeX, markerSizeY;

	void AddNewWatch(int addr, char *watchName);
	void AddNewWatch(int addr, char *watchName, uint8 representation, int numberOfValues, uint8 bits);
	CDataWatchDetails *CreateWatch(int address, char *watchName, uint8 representation, int numberOfValues, uint8 bits);
	
	void DeleteWatch(int addr);
	void DeleteAllWatches();
	
	std::map<int, CDataWatchDetails *> watches;
	
	bool isShowAddr;
	
	int startItemIndex;
	
	void ScrollDataUp();
	void ScrollDataDown();
};

#endif
