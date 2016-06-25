#include "CViewC64.h"
#include "CViewAbout.h"
#include "VID_GLViewController.h"
#include "CGuiMain.h"
#include "CSlrString.h"
#include "C64Tools.h"
#include "SYS_KeyCodes.h"
#include "CSlrKeyboardShortcuts.h"
#include "CSlrFileFromOS.h"
#include "C64SettingsStorage.h"

#include "C64KeyboardShortcuts.h"
#include "CViewBreakpoints.h"
#include "CViewSnapshots.h"
#include "C64DebugInterface.h"
#include "MTH_Random.h"

#include "CViewMemoryMap.h"

#include "CGuiMain.h"

CViewAbout::CViewAbout(GLfloat posX, GLfloat posY, GLfloat posZ, GLfloat sizeX, GLfloat sizeY)
: CGuiView(posX, posY, posZ, sizeX, sizeY)
{
	this->name = "CViewAbout";
	
	font = viewC64->fontCBMShifted;
	fontScale = 1.5;
	fontHeight = font->GetCharHeight('@', fontScale) + 2;
	
	strHeader = new CSlrString("About C64 Debugger");
	
	/// colors
	tr = 0.64; //163/255;
	tg = 0.59; //151/255;
	tb = 1.0; //255/255;
}

CViewAbout::~CViewAbout()
{
}

void CViewAbout::DoLogic()
{
	
}

void CViewAbout::Render()
{
	BlitFilledRectangle(0, 0, -1, sizeX, sizeY, 0.5, 0.5, 1.0, 1.0);
	
	float sb = 20;
	float gap = 4;
	
	float tr = 0.64; //163/255;
	float tg = 0.59; //151/255;
	float tb = 1.0; //255/255;
	
	float lr = 0.64;
	float lg = 0.65;
	float lb = 0.65;
	float lSizeY = 3;
	
	float scrx = sb;
	float scry = sb;
	float scrsx = sizeX - sb*2.0f;
	float scrsy = sizeY - sb*2.0f;
	float cx = scrsx/2.0f + sb;
	
	BlitFilledRectangle(scrx, scry, -1, scrsx, scrsy, 0, 0, 1.0, 1.0);
	
	float px = scrx + gap;
	float py = scry + gap;
	
	fontScale = 3.0f;
	fontHeight = font->GetCharHeight('@', fontScale) + 1;

	font->BlitTextColor(strHeader, cx, py, -1, fontScale, tr, tg, tb, 1, FONT_ALIGN_CENTER);
	py += fontHeight;
	//	font->BlitTextColor(strHeader2, cx, py, -1, fontScale, tr, tg, tb, 1, FONT_ALIGN_CENTER);
	//	py += fontHeight;
	py += 4.0f;
	
	BlitFilledRectangle(scrx, py, -1, scrsx, lSizeY, lr, lg, lb, 1);
	
	py += lSizeY + gap + 4.0f;
	
	
	//// TODO: this is a quick way to have it immediately implemented
	//// this needs of course to be changed into some more meaningful
	
	fontScale = 2.0f;
	fontHeight = font->GetCharHeight('@', fontScale) + 1;

	font->BlitTextColor("C64 Debugger is (C) Marcin Skoczylas, aka Slajerek/Samar", px, py, posZ, fontScale, tr, tg, tb, 1); py += fontHeight;
//	font->BlitTextColor("http://samar.untergrund.net", 338, py, posZ, 2.0f, 0.0f, 0.0f, 0.0f, 1);
	
	py += fontHeight;
	
	font->BlitTextColor("VICE, the Versatile Commodore Emulator", px, py, posZ, fontScale, tr, tg, tb, 1); py += fontHeight;
	font->BlitTextColor("Copyright C 1998-2008 Andreas Boose", px, py, posZ, fontScale, tr, tg, tb, 1); py += fontHeight;
	font->BlitTextColor("Copyright C 1998-2008 Dag Lem", px, py, posZ, fontScale, tr, tg, tb, 1); py += fontHeight;
	font->BlitTextColor("Copyright C 1998-2008 Tibor Biczo", px, py, posZ, fontScale, tr, tg, tb, 1); py += fontHeight;
	font->BlitTextColor("Copyright C 1999-2008 Andreas Matthies", px, py, posZ, fontScale, tr, tg, tb, 1); py += fontHeight;
	font->BlitTextColor("Copyright C 1999-2008 Martin Pottendorfer", px, py, posZ, fontScale, tr, tg, tb, 1); py += fontHeight;
	font->BlitTextColor("Copyright C 2000-2008 Spiro Trikaliotis", px, py, posZ, fontScale, tr, tg, tb, 1); py += fontHeight;
	font->BlitTextColor("Copyright C 2005-2008 Marco van den Heuvel", px, py, posZ, fontScale, tr, tg, tb, 1); py += fontHeight;
	font->BlitTextColor("Copyright C 2006-2008 Christian Vogelgsang", px, py, posZ, fontScale, tr, tg, tb, 1); py += fontHeight;
	font->BlitTextColor("Copyright C 2007-2008 Fabrizio Gennari", px, py, posZ, fontScale, tr, tg, tb, 1); py += fontHeight;
	font->BlitTextColor("Copyright C 1999-2007 Andreas Dehmel", px, py, posZ, fontScale, tr, tg, tb, 1); py += fontHeight;
	font->BlitTextColor("Copyright C 2003-2005 David Hansel", px, py, posZ, fontScale, tr, tg, tb, 1); py += fontHeight;
	font->BlitTextColor("Copyright C 2000-2004 Markus Brenner", px, py, posZ, fontScale, tr, tg, tb, 1); py += fontHeight;
	font->BlitTextColor("", px, py, posZ, fontScale, tr, tg, tb, 1); py += fontHeight;
	font->BlitTextColor("Copyright C 1999-2004 Thomas Bretz", px, py, posZ, fontScale, tr, tg, tb, 1); py += fontHeight;
	font->BlitTextColor("Copyright C 1997-2001 Daniel Sladic", px, py, posZ, fontScale, tr, tg, tb, 1); py += fontHeight;
	font->BlitTextColor("Copyright C 1996-1999 Ettore Perazzoli", px, py, posZ, fontScale, tr, tg, tb, 1); py += fontHeight;
	font->BlitTextColor("Copyright C 1996-1999 André Fachat", px, py, posZ, fontScale, tr, tg, tb, 1); py += fontHeight;
	font->BlitTextColor("Copyright C 1993-1994, 1997-1999 Teemu Rantanen", px, py, posZ, fontScale, tr, tg, tb, 1); py += fontHeight;
	font->BlitTextColor("Copyright C 1993-1996 Jouko Valta", px, py, posZ, fontScale, tr, tg, tb, 1); py += fontHeight;
	font->BlitTextColor("Copyright C 1993-1994 Jarkko Sonninen", px, py, posZ, fontScale, tr, tg, tb, 1); py += fontHeight;
	font->BlitTextColor("", px, py, posZ, fontScale, tr, tg, tb, 1); py += fontHeight;

	fontScale = 0.8f;
	font->BlitTextColor("The ROM files embedded in the source code are Copyright C by Commodore Business Machines.", px, py, posZ, fontScale, tr, tg, tb, 1); py += fontHeight;

	
	
	fontScale = 0.8f;
	fontHeight = font->GetCharHeight('@', fontScale) + 1;

	font->BlitTextColor("This program is free software; you can redistribute it and/or", px, py, posZ, fontScale, tr, tg, tb, 1); py += fontHeight;
	font->BlitTextColor("modify it under the terms of the GNU General Public License as", px, py, posZ, fontScale, tr, tg, tb, 1); py += fontHeight;
	font->BlitTextColor("published by the Free Software Foundation; either version 2 of the", px, py, posZ, fontScale, tr, tg, tb, 1); py += fontHeight;
	font->BlitTextColor("License, or (at your option) any later version.", px, py, posZ, fontScale, tr, tg, tb, 1); py += fontHeight;
	font->BlitTextColor("", px, py, posZ, fontScale, tr, tg, tb, 1); py += fontHeight;
	font->BlitTextColor("This program is distributed in the hope that it will be useful,", px, py, posZ, fontScale, tr, tg, tb, 1); py += fontHeight;
	font->BlitTextColor("but WITHOUT ANY WARRANTY; without even the implied warranty of", px, py, posZ, fontScale, tr, tg, tb, 1); py += fontHeight;
	font->BlitTextColor("MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the", px, py, posZ, fontScale, tr, tg, tb, 1); py += fontHeight;
	font->BlitTextColor("GNU General Public License for more details.", px, py, posZ, fontScale, tr, tg, tb, 1); py += fontHeight;
	font->BlitTextColor("You should have received a copy of the GNU General Public License", px, py, posZ, fontScale, tr, tg, tb, 1); py += fontHeight;
	font->BlitTextColor("along with this program; if not, write to the Free Software", px, py, posZ, fontScale, tr, tg, tb, 1); py += fontHeight;
	
	font->BlitTextColor("Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA", px, py, posZ, fontScale, tr, tg, tb, 1); py += fontHeight;
	
	font->BlitTextColor("02111-1307  USA", px, py, posZ, fontScale, tr, tg, tb, 1);

	font->BlitTextColor("Click anywhere to close this", 330, py, posZ, 2.0f, tr, tg, tb, 1);
	
}

void CViewAbout::Render(GLfloat posX, GLfloat posY)
{
	CGuiView::Render(posX, posY);
}

//@returns is consumed
bool CViewAbout::DoTap(GLfloat x, GLfloat y)
{
	LOGG("CViewAbout::DoTap:  x=%f y=%f", x, y);
	guiMain->SetView(viewC64->viewC64MainMenu);
	return CGuiView::DoTap(x, y);
}

bool CViewAbout::DoFinishTap(GLfloat x, GLfloat y)
{
	LOGG("CViewAbout::DoFinishTap: %f %f", x, y);
	return CGuiView::DoFinishTap(x, y);
}

//@returns is consumed
bool CViewAbout::DoDoubleTap(GLfloat x, GLfloat y)
{
	LOGG("CViewAbout::DoDoubleTap:  x=%f y=%f", x, y);
	return CGuiView::DoDoubleTap(x, y);
}

bool CViewAbout::DoFinishDoubleTap(GLfloat x, GLfloat y)
{
	LOGG("CViewAbout::DoFinishTap: %f %f", x, y);
	return CGuiView::DoFinishDoubleTap(x, y);
}


bool CViewAbout::DoMove(GLfloat x, GLfloat y, GLfloat distX, GLfloat distY, GLfloat diffX, GLfloat diffY)
{
	return CGuiView::DoMove(x, y, distX, distY, diffX, diffY);
}

bool CViewAbout::FinishMove(GLfloat x, GLfloat y, GLfloat distX, GLfloat distY, GLfloat accelerationX, GLfloat accelerationY)
{
	return CGuiView::FinishMove(x, y, distX, distY, accelerationX, accelerationY);
}

bool CViewAbout::InitZoom()
{
	return CGuiView::InitZoom();
}

bool CViewAbout::DoZoomBy(GLfloat x, GLfloat y, GLfloat zoomValue, GLfloat difference)
{
	return CGuiView::DoZoomBy(x, y, zoomValue, difference);
}

bool CViewAbout::DoMultiTap(COneTouchData *touch, float x, float y)
{
	return CGuiView::DoMultiTap(touch, x, y);
}

bool CViewAbout::DoMultiMove(COneTouchData *touch, float x, float y)
{
	return CGuiView::DoMultiMove(touch, x, y);
}

bool CViewAbout::DoMultiFinishTap(COneTouchData *touch, float x, float y)
{
	return CGuiView::DoMultiFinishTap(touch, x, y);
}

void CViewAbout::FinishTouches()
{
	return CGuiView::FinishTouches();
}

void CViewAbout::SwitchAboutScreen()
{
	if (guiMain->currentView == this)
	{
		guiMain->SetView(viewC64->viewC64MainMenu);
	}
	else
	{
		guiMain->SetView(this);
	}
}

bool CViewAbout::KeyDown(u32 keyCode, bool isShift, bool isAlt, bool isControl)
{
	guiMain->SetView(viewC64->viewC64MainMenu);

//	if (keyCode == MTKEY_BACKSPACE)
//	{
//		guiMain->SetView(viewC64->viewC64MainMenu);
//		return true;
//	}
	
	return CGuiView::KeyDown(keyCode, isShift, isAlt, isControl);
}

bool CViewAbout::KeyUp(u32 keyCode, bool isShift, bool isAlt, bool isControl)
{
	return CGuiView::KeyUp(keyCode, isShift, isAlt, isControl);
}

bool CViewAbout::KeyPressed(u32 keyCode, bool isShift, bool isAlt, bool isControl)
{
	return CGuiView::KeyPressed(keyCode, isShift, isAlt, isControl);
}

void CViewAbout::ActivateView()
{
	LOGG("CViewAbout::ActivateView()");
}

void CViewAbout::DeactivateView()
{
	LOGG("CViewAbout::DeactivateView()");
}

