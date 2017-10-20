#ifndef _CViewBaseStateCPU_H_
#define _CViewBaseStateCPU_H_

#include "SYS_Defs.h"
#include "CGuiView.h"
#include "CGuiEditHex.h"

class CSlrFont;
class C64DebugInterface;

enum StateCPURegister : uint8
{
	STATE_CPU_REGISTER_NONE = 0,
	STATE_CPU_REGISTER_PC,
	STATE_CPU_REGISTER_A,
	STATE_CPU_REGISTER_X,
	STATE_CPU_REGISTER_Y,
	STATE_CPU_REGISTER_SP,
	STATE_CPU_REGISTER_FLAGS,
	STATE_CPU_REGISTER_MEM01
};

typedef struct {
	StateCPURegister reg;
	float characterPos;
	int numCharacters;
} register_def;

class CViewBaseStateCPU : public CGuiView, CGuiEditHexCallback
{
public:
	CViewBaseStateCPU(GLfloat posX, GLfloat posY, GLfloat posZ, GLfloat sizeX, GLfloat sizeY, C64DebugInterface *debugInterface);
	
	virtual bool KeyDown(u32 keyCode, bool isShift, bool isAlt, bool isControl);
	virtual bool KeyUp(u32 keyCode, bool isShift, bool isAlt, bool isControl);
	
	virtual bool DoTap(GLfloat x, GLfloat y);

	CSlrFont *font;
	float fontSize;
	void SetFont(CSlrFont *font, float fontSize);
	
	virtual void SetPosition(GLfloat posX, GLfloat posY);
	virtual void SetPosition(GLfloat posX, GLfloat posY, GLfloat posZ, GLfloat sizeX, GLfloat sizeY);
	
	virtual void Render();
	virtual void DoLogic();

	virtual bool SetFocus(bool focus);

	C64DebugInterface *debugInterface;
	
	register_def *regs;
	int numRegisters;
	
	int editingCpuRegisterIndex;
	
	virtual int GetCpuRegisterIndexFromCharacterPos(float x);
	virtual StateCPURegister GetCpuRegisterFromCharacterPos(float x);
	virtual float GetCharacterPosByCpuRegister(StateCPURegister cpuRegister);
	
	virtual void FinishEditingRegister();
	virtual void StartEditingRegister();
	
	CGuiEditHex *editBoxHex;
	virtual void GuiEditHexEnteredValue(CGuiEditHex *editHex, u32 lastKeyCode, bool isCancelled);
	
	//
	virtual void RenderRegisters();
	virtual void SetRegisterValue(StateCPURegister reg, int value);
	virtual int GetRegisterValue(StateCPURegister reg);
};



#endif

