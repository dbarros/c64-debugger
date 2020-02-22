#ifndef _CVIEWC64STATECIA_H_
#define _CVIEWC64STATECIA_H_

#include "SYS_Defs.h"
#include "CGuiView.h"
#include "CGuiEditHex.h"
#include <vector>
#include <list>

class CSlrFont;
class CSlrDataAdapter;
class CViewMemoryMap;
class CSlrMutex;
class C64DebugInterface;

// TODO: make base class to have Vice specific state rendering and editing
//       class CViewC64ViceStateCIA : public CViewC64StateCIA

class CViewC64StateCIA : public CGuiView, CGuiEditHexCallback
{
public:
	CViewC64StateCIA(GLfloat posX, GLfloat posY, GLfloat posZ, GLfloat sizeX, GLfloat sizeY, C64DebugInterface *debugInterface);
	
	virtual bool KeyDown(u32 keyCode, bool isShift, bool isAlt, bool isControl);
	virtual bool KeyUp(u32 keyCode, bool isShift, bool isAlt, bool isControl);
	
	virtual bool DoTap(GLfloat x, GLfloat y);
	
	CSlrFont *fontBytes;
	CSlrFont *fontCharacters;
	
	C64DebugInterface *debugInterface;

	float fontSize;	
	
	virtual void SetPosition(GLfloat posX, GLfloat posY, GLfloat posZ, GLfloat sizeX, GLfloat sizeY);
	
	virtual void Render();
	virtual void DoLogic();	
	
	virtual bool SetFocus(bool focus);
	
	bool renderCIA1;
	bool renderCIA2;

	//
	virtual void RenderStateCIA(float px, float py, float posZ, CSlrFont *fontBytes, float fontSize, int ciaId);
	
	// editing registers
	bool showRegistersOnly;
	int editingRegisterValueIndex;		// -1 means no editing
	int editingCIAIndex;
	CGuiEditHex *editHex;
	virtual void GuiEditHexEnteredValue(CGuiEditHex *editHex, u32 lastKeyCode, bool isCancelled);
	
	//
	virtual void RenderFocusBorder();

};


#endif

