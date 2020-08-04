#include "CDebuggerEmulatorPlugin.h"
#include "DebuggerDefs.h"
#include "CViewC64.h"

CDebuggerEmulatorPlugin::CDebuggerEmulatorPlugin(u8 emulatorType)
{
	this->SetEmulatorType(emulatorType);
	this->api = new CDebuggerAPI();
}

CDebuggerEmulatorPlugin::~CDebuggerEmulatorPlugin()
{
}

void CDebuggerEmulatorPlugin::SetEmulatorType(u8 emulatorType)
{
	this->emulatorType = emulatorType;
}

CDebugInterface *CDebuggerEmulatorPlugin::GetDebugInterface()
{
	return viewC64->GetDebugInterface(this->emulatorType);
}

void CDebuggerEmulatorPlugin::Init()
{
}

void CDebuggerEmulatorPlugin::DoFrame()
{
}

void CDebuggerEmulatorPlugin::RenderGUI()
{
}

u32 CDebuggerEmulatorPlugin::KeyDown(u32 keyCode)
{
	return keyCode;
}

u32 CDebuggerEmulatorPlugin::KeyUp(u32 keyCode)
{
	return keyCode;
}

bool CDebuggerEmulatorPlugin::WindowMouseDown(float x, float y)
{
	return false;
}

bool CDebuggerEmulatorPlugin::WindowMouseUp(float x, float y)
{
	return false;
}

bool CDebuggerEmulatorPlugin::ScreenMouseDown(float x, float y)
{
	return false;
}

bool CDebuggerEmulatorPlugin::ScreenMouseUp(float x, float y)
{
	return false;
}

