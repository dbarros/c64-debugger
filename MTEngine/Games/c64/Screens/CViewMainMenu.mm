#include "CViewC64.h"
#include "CViewMainMenu.h"
#include "VID_GLViewController.h"
#include "CGuiMain.h"
#include "CSlrString.h"
#include "C64Tools.h"
#include "SYS_KeyCodes.h"
#include "CSlrKeyboardShortcuts.h"
#include "CSlrFileFromOS.h"
#include "C64D_Version.h"

#include "C64KeyboardShortcuts.h"
#include "CViewBreakpoints.h"
#include "CViewSnapshots.h"
#include "CViewAbout.h"
#include "C64DebugInterface.h"
#include "CViewMemoryMap.h"
#include "CViewFileD64.h"

#include "C64SettingsStorage.h"

#include "CGuiMain.h"
#include "CViewVicEditor.h"

#define VIEWC64SETTINGS_OPEN_NONE	0
#define VIEWC64SETTINGS_OPEN_D64	1
#define VIEWC64SETTINGS_OPEN_CRT	2
#define VIEWC64SETTINGS_OPEN_PRG	3

CViewMainMenu::CViewMainMenu(GLfloat posX, GLfloat posY, GLfloat posZ, GLfloat sizeX, GLfloat sizeY)
: CGuiView(posX, posY, posZ, sizeX, sizeY)
{
	this->name = "CViewMainMenu";

	font = viewC64->fontCBMShifted;
	fontScale = 3;
	fontHeight = font->GetCharHeight('@', fontScale) + 2;

	diskExtensions.push_back(new CSlrString("d64"));
	diskExtensions.push_back(new CSlrString("x64"));
	diskExtensions.push_back(new CSlrString("g64"));
	diskExtensions.push_back(new CSlrString("p64"));
	
	prgExtensions.push_back(new CSlrString("prg"));

	crtExtensions.push_back(new CSlrString("crt"));

	char *buf = SYS_GetCharBuf();
	
	sprintf(buf, "C64 Debugger v%s by Slajerek/Samar", C64DEBUGGER_VERSION_STRING);
	strHeader = new CSlrString(buf);

	SYS_ReleaseCharBuf(buf);
	
	strHeader2 = viewC64->debugInterface->GetEmulatorVersionString();
	
	/// colors
	tr = 0.64; //163/255;
	tg = 0.59; //151/255;
	tb = 1.0; //255/255;
	
	/// menu
	viewMenu = new CGuiViewMenu(35, 76, -1, sizeX-70, sizeY-76, this);

#if defined(MACOS)
	kbsQuitApplication = new CSlrKeyboardShortcut(KBZONE_GLOBAL, "Quit application", 'q', false, false, true);
#elif defined(LINUX)
	kbsQuitApplication = new CSlrKeyboardShortcut(KBZONE_GLOBAL, "Quit application", MTKEY_F4, false, true, false);
#elif defined(WIN32)
	kbsQuitApplication = new CSlrKeyboardShortcut(KBZONE_GLOBAL, "Quit application", MTKEY_F4, false, true, false);
#endif
	
	viewC64->keyboardShortcuts->AddShortcut(kbsQuitApplication);
	
	kbsMainMenuScreen = new CSlrKeyboardShortcut(KBZONE_GLOBAL, "Main menu screen", MTKEY_F9, false, false, false);
	viewC64->keyboardShortcuts->AddShortcut(kbsMainMenuScreen);
	
	//
	
	kbsScreenLayout1 = new CSlrKeyboardShortcut(KBZONE_GLOBAL, "Layout #1", MTKEY_F1, false, false, true);
	viewC64->keyboardShortcuts->AddShortcut(kbsScreenLayout1);

	kbsScreenLayout2 = new CSlrKeyboardShortcut(KBZONE_GLOBAL, "Layout #2", MTKEY_F2, false, false, true);
	viewC64->keyboardShortcuts->AddShortcut(kbsScreenLayout2);

	kbsScreenLayout3 = new CSlrKeyboardShortcut(KBZONE_GLOBAL, "Layout #3", MTKEY_F3, false, false, true);
	viewC64->keyboardShortcuts->AddShortcut(kbsScreenLayout3);

	kbsScreenLayout4 = new CSlrKeyboardShortcut(KBZONE_GLOBAL, "Layout #4", MTKEY_F4, false, false, true);
	viewC64->keyboardShortcuts->AddShortcut(kbsScreenLayout4);

	kbsScreenLayout5 = new CSlrKeyboardShortcut(KBZONE_GLOBAL, "Layout #5", MTKEY_F5, false, false, true);
	viewC64->keyboardShortcuts->AddShortcut(kbsScreenLayout5);

	kbsScreenLayout6 = new CSlrKeyboardShortcut(KBZONE_GLOBAL, "Layout #6", MTKEY_F6, false, false, true);
	viewC64->keyboardShortcuts->AddShortcut(kbsScreenLayout6);

	kbsScreenLayout7 = new CSlrKeyboardShortcut(KBZONE_GLOBAL, "Layout #7", MTKEY_F7, false, false, true);
	viewC64->keyboardShortcuts->AddShortcut(kbsScreenLayout7);

	kbsScreenLayout8 = new CSlrKeyboardShortcut(KBZONE_GLOBAL, "Layout #8", MTKEY_F8, false, false, true);
	viewC64->keyboardShortcuts->AddShortcut(kbsScreenLayout8);

	kbsScreenLayout9 = new CSlrKeyboardShortcut(KBZONE_GLOBAL, "Layout #9", MTKEY_F1, true, false, true);
	viewC64->keyboardShortcuts->AddShortcut(kbsScreenLayout9);
	
	kbsScreenLayout10 = new CSlrKeyboardShortcut(KBZONE_GLOBAL, "Layout #10", MTKEY_F2, true, false, true);
	viewC64->keyboardShortcuts->AddShortcut(kbsScreenLayout10);

	kbsScreenLayout11 = new CSlrKeyboardShortcut(KBZONE_GLOBAL, "Layout #11", MTKEY_F4, true, false, true);
	viewC64->keyboardShortcuts->AddShortcut(kbsScreenLayout11);
	
	kbsScreenLayout12 = new CSlrKeyboardShortcut(KBZONE_GLOBAL, "Layout #12", MTKEY_F5, true, false, true);
	viewC64->keyboardShortcuts->AddShortcut(kbsScreenLayout12);
	
	//
	
	kbsVicEditorScreen = new CSlrKeyboardShortcut(KBZONE_GLOBAL, "VIC Editor screen", MTKEY_F6, true, false, true);
	viewC64->keyboardShortcuts->AddShortcut(kbsVicEditorScreen);
	
	//
	
	kbsInsertD64 = new CSlrKeyboardShortcut(KBZONE_GLOBAL, "Insert Device #8", '8', false, false, true);
	viewC64->keyboardShortcuts->AddShortcut(kbsInsertD64);
	menuItemInsertD64 = new CViewC64MenuItem(fontHeight*2.5, new CSlrString("1541 Device 8..."), kbsInsertD64, tr, tg, tb);
	viewMenu->AddMenuItem(menuItemInsertD64);
	

	
	// TODO: add shortcut to second line of menuItemInsertD64 (browse)
	kbsBrowseD64 = new CSlrKeyboardShortcut(KBZONE_GLOBAL, "Browse Device #8", MTKEY_F7, false, false, false);
	viewC64->keyboardShortcuts->AddShortcut(kbsBrowseD64);
	
	kbsStartFromDisk = new CSlrKeyboardShortcut(KBZONE_GLOBAL, "Start from Device #8", MTKEY_F3, false, false, false);
	viewC64->keyboardShortcuts->AddShortcut(kbsStartFromDisk);

	//
	
	kbsLoadPRG = new CSlrKeyboardShortcut(KBZONE_GLOBAL, "Load PRG", 'o', false, false, true);
	viewC64->keyboardShortcuts->AddShortcut(kbsLoadPRG);
	menuItemLoadPRG = new CViewC64MenuItem(fontHeight*2.5, new CSlrString("Load PRG..."), kbsLoadPRG, tr, tg, tb);
	viewMenu->AddMenuItem(menuItemLoadPRG);

	kbsReloadAndRestart = new CSlrKeyboardShortcut(KBZONE_GLOBAL, "Reload & Start PRG", 'l', false, false, true);
	viewC64->keyboardShortcuts->AddShortcut(kbsReloadAndRestart);
	menuItemReloadAndRestart = new CViewC64MenuItem(fontHeight, new CSlrString("Reload PRG & Start"), kbsReloadAndRestart, tr, tg, tb);
	viewMenu->AddMenuItem(menuItemReloadAndRestart);

	kbsRestartPRG = new CSlrKeyboardShortcut(KBZONE_GLOBAL, "Reload & Restart PRG", MTKEY_F5, false, false, false);
	viewC64->keyboardShortcuts->AddShortcut(kbsRestartPRG);
	
	kbsSoftReset = new CSlrKeyboardShortcut(KBZONE_GLOBAL, "Soft Reset", 'r', false, false, true);
	viewC64->keyboardShortcuts->AddShortcut(kbsSoftReset);
	menuItemSoftReset = new CViewC64MenuItem(fontHeight, new CSlrString("Soft Reset"), kbsSoftReset, tr, tg, tb);
	viewMenu->AddMenuItem(menuItemSoftReset);

	kbsHardReset = new CSlrKeyboardShortcut(KBZONE_GLOBAL, "Hard Reset", 'r', true, false, true);
	viewC64->keyboardShortcuts->AddShortcut(kbsHardReset);
	menuItemHardReset = new CViewC64MenuItem(fontHeight*2, new CSlrString("Hard Reset"), kbsHardReset, tr, tg, tb);
	viewMenu->AddMenuItem(menuItemHardReset);

	kbsDiskDriveReset = new CSlrKeyboardShortcut(KBZONE_GLOBAL, "Disk Drive Reset", 'r', false, true, true);
	viewC64->keyboardShortcuts->AddShortcut(kbsDiskDriveReset);
//	menuItemDiskDriveReset = new CViewC64MenuItem(fontHeight, new CSlrString("Disk Drive Reset"), kbsDiskDriveReset, tr, tg, tb);
//	viewMenu->AddMenuItem(menuItemDiskDriveReset);

	kbsInsertCartridge = new CSlrKeyboardShortcut(KBZONE_GLOBAL, "Insert Cartridge", '0', false, false, true);
	viewC64->keyboardShortcuts->AddShortcut(kbsInsertCartridge);
	menuItemInsertCartridge = new CViewC64MenuItem(fontHeight*3, new CSlrString("Insert cartridge..."), kbsInsertCartridge, tr, tg, tb);
	viewMenu->AddMenuItem(menuItemInsertCartridge);
	
	kbsSnapshots = new CSlrKeyboardShortcut(KBZONE_GLOBAL, "Snapshots screen", 's', true, false, true);
	viewC64->keyboardShortcuts->AddShortcut(kbsSnapshots);
	menuItemSnapshots = new CViewC64MenuItem(fontHeight*1.7, new CSlrString("Snapshots..."), kbsSnapshots, tr, tg, tb);
	viewMenu->AddMenuItem(menuItemSnapshots);
	
	kbsBreakpoints = new CSlrKeyboardShortcut(KBZONE_GLOBAL, "Breakpoints screen", 'b', false, false, true);
	viewC64->keyboardShortcuts->AddShortcut(kbsBreakpoints);
	menuItemBreakpoints = new CViewC64MenuItem(fontHeight*1.7, new CSlrString("Breakpoints..."), kbsBreakpoints, tr, tg, tb);
	viewMenu->AddMenuItem(menuItemBreakpoints);


//	kbsEmulationSettings = new CSlrKeyboardShortcut(KBZONE_GLOBAL, KBFUN_BREAKPOINTS, 'b', false, false, true);
//	viewC64->keyboardShortcuts->AddShortcut(kbsEmulationSettings);
	menuItemSettings = new CViewC64MenuItem(fontHeight*1.7, new CSlrString("Settings..."), NULL, tr, tg, tb);
	viewMenu->AddMenuItem(menuItemSettings);

	menuItemAbout = new CViewC64MenuItem(fontHeight, new CSlrString("About..."), NULL, tr, tg, tb);
	viewMenu->AddMenuItem(menuItemAbout);

	
	
	kbsStepOverInstruction = new CSlrKeyboardShortcut(KBZONE_GLOBAL, "Step over instruction", MTKEY_F10, false, false, false);
	viewC64->keyboardShortcuts->AddShortcut(kbsStepOverInstruction);
	
	kbsStepOneCycle = new CSlrKeyboardShortcut(KBZONE_GLOBAL, "Step one cycle", MTKEY_F10, true, false, false);
	viewC64->keyboardShortcuts->AddShortcut(kbsStepOneCycle);

	kbsRunContinueEmulation = new CSlrKeyboardShortcut(KBZONE_GLOBAL, "Run/Continue code", MTKEY_F11, false, false, false);
	viewC64->keyboardShortcuts->AddShortcut(kbsRunContinueEmulation);

	kbsIsDataDirectlyFromRam = new CSlrKeyboardShortcut(KBZONE_GLOBAL, "Show data from RAM", 'm', false, false, true);
	viewC64->keyboardShortcuts->AddShortcut(kbsIsDataDirectlyFromRam);

	kbsToggleMulticolorImageDump = new CSlrKeyboardShortcut(KBZONE_GLOBAL, "Show multicolor data", 'k', false, false, true);
	viewC64->keyboardShortcuts->AddShortcut(kbsToggleMulticolorImageDump);

	kbsShowRasterBeam = new CSlrKeyboardShortcut(KBZONE_GLOBAL, "Show Raster Beam", 'e', false, false, true);
	viewC64->keyboardShortcuts->AddShortcut(kbsShowRasterBeam);

	//
	kbsMoveFocusToNextView = new CSlrKeyboardShortcut(KBZONE_GLOBAL, "Move focus to next view", MTKEY_TAB, false, false, false);
	viewC64->keyboardShortcuts->AddShortcut(kbsMoveFocusToNextView);

	kbsMoveFocusToPreviousView = new CSlrKeyboardShortcut(KBZONE_GLOBAL, "Move focus to previous view", MTKEY_TAB, true, false, false);
	viewC64->keyboardShortcuts->AddShortcut(kbsMoveFocusToPreviousView);
	
	//
	kbsSaveScreenImageAsPNG = new CSlrKeyboardShortcut(KBZONE_GLOBAL, "Save screenshot as PNG", 'p', true, false, true);
	viewC64->keyboardShortcuts->AddShortcut(kbsSaveScreenImageAsPNG);
	
	viewMenu->InitSelection();
	
	
//	std::list<u32> zones;
//	zones.push_back(KBZONE_GLOBAL);
//	CSlrKeyboardShortcut *sr = viewC64->keyboardShortcuts->FindShortcut(zones, '8', false, true, false);
	
	//LOGD("---done");
	

	loadPrgByteBuffer = NULL;
}

CViewMainMenu::~CViewMainMenu()
{
}

void CViewMainMenu::MenuCallbackItemEntered(CGuiViewMenuItem *menuItem)
{
	//		void SYS_DialogSaveFile(CSystemFileDialogCallback *callback, std::list<CSlrString *> *extensions, CSlrString *defaultFileName, CSlrString *windowTitle);

	if (menuItem == menuItemInsertD64)
	{
		OpenDialogInsertD64();
	}
	else if (menuItem == menuItemInsertCartridge)
	{
		OpenDialogInsertCartridge();
	}
	else if (menuItem == menuItemLoadPRG)
	{
		OpenDialogLoadPRG();
	}
	else if (menuItem == menuItemHardReset)
	{
		viewC64->debugInterface->HardReset();
	}
	else if (menuItem == menuItemSoftReset)
	{
		viewC64->debugInterface->Reset();
	}	
	else if (menuItem == menuItemBreakpoints)
	{
		viewC64->viewC64Breakpoints->SwitchBreakpointsScreen();
	}
	else if (menuItem == menuItemSnapshots)
	{
		viewC64->viewC64Snapshots->SwitchSnapshotsScreen();
	}
	else if (menuItem == menuItemReloadAndRestart)
	{
		ReloadAndRestartPRG();
	}
	else if (menuItem == menuItemSettings)
	{
		viewC64->viewC64SettingsMenu->SwitchMainMenuScreen();
	}
	else if (menuItem == menuItemAbout)
	{
		viewC64->viewAbout->SwitchAboutScreen();
	}
	
}

void CViewMainMenu::MenuCallbackItemChanged(CGuiViewMenuItem *menuItem)
{
	LOGD("CViewMainMenu::MenuCallbackItemChanged");
}

void CViewMainMenu::OpenDialogInsertD64()
{
	LOGM("OpenDialogInsertD64");
	openDialogFunction = VIEWC64SETTINGS_OPEN_D64;

	CSlrString *windowTitle = new CSlrString("Open D64 disk image");
	windowTitle->DebugPrint("windowTitle=");
	SYS_DialogOpenFile(this, &diskExtensions, c64SettingsDefaultD64Folder, windowTitle);
	delete windowTitle;
}

void CViewMainMenu::OpenDialogInsertCartridge()
{
	LOGM("OpenDialogInsertCartridge");
	openDialogFunction = VIEWC64SETTINGS_OPEN_CRT;
	
	CSlrString *windowTitle = new CSlrString("Open CRT cartridge image");
	SYS_DialogOpenFile(this, &crtExtensions, c64SettingsDefaultCartridgeFolder, windowTitle);
	delete windowTitle;
}


void CViewMainMenu::OpenDialogLoadPRG()
{
	LOGM("OpenDialogLoadPRG");
	openDialogFunction = VIEWC64SETTINGS_OPEN_PRG;
	
	CSlrString *windowTitle = new CSlrString("Open PRG file");
	SYS_DialogOpenFile(this, &prgExtensions, c64SettingsDefaultPRGFolder, windowTitle);
	delete windowTitle;	
}

void CViewMainMenu::SystemDialogFileOpenSelected(CSlrString *path)
{
	LOGM("CViewMainMenu::SystemDialogFileOpenSelected, path=%x", path);
	path->DebugPrint("path=");

	if (openDialogFunction == VIEWC64SETTINGS_OPEN_D64)
	{
		InsertD64(path, true);
		C64DebuggerStoreSettings();
	}
	else if (openDialogFunction == VIEWC64SETTINGS_OPEN_CRT)
	{
		InsertCartridge(path, true);
		C64DebuggerStoreSettings();
	}
	else if (openDialogFunction == VIEWC64SETTINGS_OPEN_PRG)
	{
		LoadPRG(path, true, true);
		C64DebuggerStoreSettings();
	}
	
	openDialogFunction = VIEWC64SETTINGS_OPEN_NONE;
	
	delete path;
}

void CViewMainMenu::InsertD64(CSlrString *path, bool updatePathToD64)
{
	LOGD("CViewMainMenu::InsertD64: path=%x", path);
	
	if (SYS_FileExists(path) == false)
	{
		if (c64SettingsPathToD64 != NULL)
			delete c64SettingsPathToD64;
		
		c64SettingsPathToD64 = NULL;
		LOGError("InsertD64: file not found, skipping");
		return;
	}
	
	if (c64SettingsPathToD64 != path)
	{
		if (c64SettingsPathToD64 != NULL)
			delete c64SettingsPathToD64;
		c64SettingsPathToD64 = new CSlrString(path);
	}
	
	if (updatePathToD64)
	{
		LOGD("...updatePathToD64");
		if (c64SettingsDefaultD64Folder != NULL)
			delete c64SettingsDefaultD64Folder;
		c64SettingsDefaultD64Folder = path->GetFilePathWithoutFileNameComponentFromPath();
		
		c64SettingsDefaultD64Folder->DebugPrint("c64SettingsDefaultD64Folder=");
	}
	
	// insert D64
	viewC64->debugInterface->InsertD64(path);

	
	// TODO: support UTF paths
	char *asciiPath = c64SettingsPathToD64->GetStdASCII();
	
	// display file name in menu
	char *fname = SYS_GetFileNameFromFullPath(asciiPath);

	guiMain->LockMutex();
	if (menuItemInsertD64->str2 != NULL)
		delete menuItemInsertD64->str2;
	
	menuItemInsertD64->str2 = new CSlrString(fname);
	delete fname;
	
	guiMain->UnlockMutex();

	LOGM("Inserted new d64: %s", asciiPath);
	delete asciiPath;
	
	if (guiMain->currentView == viewC64->viewFileD64)
		viewC64->viewFileD64->StartSelectedDiskImageBrowsing();
	
	if (c64SettingsAutoJmpFromInsertedDiskFirstPrg)
	{
		viewC64->viewFileD64->StartFirstDiskPRGEntry();
	}
}

void CViewMainMenu::InsertCartridge(CSlrString *path, bool updatePathToCRT)
{
	path->DebugPrint("CViewMainMenu::InsertCartridge, path=");
	
	if (c64SettingsPathToCartridge != path)
	{
		if (c64SettingsPathToCartridge != NULL)
			delete c64SettingsPathToCartridge;
		c64SettingsPathToCartridge = new CSlrString(path);
	}
	
	if (updatePathToCRT)
	{
		LOGD("...updatePathToCRT");
		if (c64SettingsDefaultCartridgeFolder != NULL)
			delete c64SettingsDefaultCartridgeFolder;
		c64SettingsDefaultCartridgeFolder = path->GetFilePathWithoutFileNameComponentFromPath();
		
		c64SettingsDefaultCartridgeFolder->DebugPrint("strDefaultCartridgeFolder=");
	}
	
	// insert CRT
	viewC64->debugInterface->AttachCartridge(path);
	
	
	// TODO: support UTF paths
	char *asciiPath = c64SettingsPathToCartridge->GetStdASCII();
	
	// display file name in menu
	char *fname = SYS_GetFileNameFromFullPath(asciiPath);

	guiMain->LockMutex();
	if (menuItemInsertCartridge->str2 != NULL)
		delete menuItemInsertCartridge->str2;
	
	menuItemInsertCartridge->str2 = new CSlrString(fname);
	delete fname;

	guiMain->UnlockMutex();
	
	LOGM("Attached new cartridge: %s", asciiPath);
	delete asciiPath;
}

bool CViewMainMenu::LoadPRG(CSlrString *path, bool autoStart, bool updatePRGFolderPath)
{
	path->DebugPrint("CViewMainMenu::LoadPRG: path=");
	
	LOGD("   >>> LoadPRG, autostart=%d", autoStart);
	
	// TODO: p00 http://vice-emu.sourceforge.net/vice_15.html#SEC299
	
	if (c64SettingsPathToPRG != path)
	{
		if (c64SettingsPathToPRG != NULL)
			delete c64SettingsPathToPRG;
		c64SettingsPathToPRG = new CSlrString(path);
	}
	
	if (updatePRGFolderPath)
	{
		LOGD("...updatePRGFolderPath");
		if (c64SettingsDefaultPRGFolder != NULL)
			delete c64SettingsDefaultPRGFolder;
		c64SettingsDefaultPRGFolder = path->GetFilePathWithoutFileNameComponentFromPath();
		
		c64SettingsDefaultPRGFolder->DebugPrint("c64SettingsDefaultPRGFolder=");
	}
	
	LOGD("... LoadPRG (2)");
	
	c64SettingsPathToPRG->DebugPrint("c64SettingsPathToPRG=");
	
	// TODO: make CSlrFileFromOS support UTF paths
	char *asciiPath = c64SettingsPathToPRG->GetStdASCII();

	LOGD("asciiPath='%s'", asciiPath);
	
	CSlrFileFromOS *file = new CSlrFileFromOS(asciiPath);
	if (!file->Exists())
	{
		delete file;
		guiMain->ShowMessage("Error loading PRG file");
		return false;
	}
	
	CByteBuffer *byteBuffer = new CByteBuffer(file, false);
	
	bool ret = LoadPRG(byteBuffer, autoStart, true);
	
	if (ret)
	{
		// display file name in menu
		char *fname = SYS_GetFileNameFromFullPath(asciiPath);
		
		guiMain->LockMutex();
		if (menuItemLoadPRG->str2 != NULL)
			delete menuItemLoadPRG->str2;
		
		menuItemLoadPRG->str2 = new CSlrString(fname);
		delete fname;
		guiMain->UnlockMutex();
	}
	
	delete asciiPath;
	delete file;

	delete byteBuffer;
	
	return ret;
}

bool CViewMainMenu::LoadPRG(CByteBuffer *byteBuffer, bool autoStart, bool showAddressInfo)
{
	LOGM("CViewMainMenu::LoadPRG: autoStart=%d showAddressInfo=%d c64SettingsAutoJmpDoReset=%d", autoStart, showAddressInfo, c64SettingsAutoJmpDoReset);
	this->loadPrgByteBuffer = new CByteBuffer(byteBuffer);
	this->loadPrgAutoStart = autoStart;
	this->loadPrgShowAddressInfo = showAddressInfo;
	
	SYS_StartThread(this);
	return true;
}

// TODO: move LoadPRG logic to C64 Tools
void CViewMainMenu::ThreadRun(void *data)
{
	LOGD("CViewMainMenu::ThreadRun");
	
	if (loadPrgAutoStart && c64SettingsAutoJmpDoReset != AUTOJMP_RESET_NONE)
	{
		viewC64->debugInterface->SetDebugMode(C64_DEBUG_RUNNING);
		viewC64->debugInterface->SetPatchKernalFastBoot(true);

		if (c64SettingsAutoJmpDoReset == AUTOJMP_RESET_SOFT)
		{
			viewC64->debugInterface->Reset();
		}
		else if (c64SettingsAutoJmpDoReset == AUTOJMP_RESET_HARD)
		{
			viewC64->debugInterface->HardReset();
		}
		
		SYS_Sleep(c64SettingsAutoJmpWaitAfterReset);
		
		viewC64->viewFileD64->UpdateDriveDiskID();
	}
	
	LoadPRGNotThreaded(loadPrgByteBuffer, loadPrgAutoStart, loadPrgShowAddressInfo);
	delete loadPrgByteBuffer;
	loadPrgByteBuffer = NULL;
}

bool CViewMainMenu::LoadPRGNotThreaded(CByteBuffer *byteBuffer, bool autoStart, bool showAddressInfo)
{
	viewC64->debugInterface->LockMutex();

	u16 startAddr;
	u16 endAddr;
	
	LoadPRG(byteBuffer, &startAddr, &endAddr);
	
	bool foundBasicSys = false;
	
	if (autoStart == true)
	{
		LOGD("LoadPRG: autostart");
		
		//http://www.lemon64.com/forum/viewtopic.php?t=870&sid=a13a63a952d295ff70c67d93409bc392
		
		if (startAddr == 0x0801)
		{
			// 1001 SYS 2066
			
			// hidden SYS:          $0805    1  0  0  1 SYS   B
			// 0800: 00 10 08 E9 03    00   31 30 30 31  9E  32 30 36 36 00
			
			// not hidden SYS:
			// 0800: 00 0C 08 E9 03 9E      20 32 30 36 36 00
			
			int sysNumberAddr = -1;
			
			u8 b = viewC64->debugInterface->GetByteC64(0x0805);
			
			if (b == 0x9E)
			{
				// regular SYS
				sysNumberAddr = 0x0806;
			}
			else if (b == 0x00)
			{
				// hidden SYS, scan for SYS ($9E), hope $0900 is enough :)
				for (int i = 0x0806; i < 0x0900; i++)
				{
					if (viewC64->debugInterface->GetByteC64(i) == 0x9E)
					{
						sysNumberAddr = i + 1;
						break;
					}
				}
			}
			
			if (sysNumberAddr != -1)
			{
				char *buf = SYS_GetCharBuf();
				int i = 0;
				
				u16 addr = sysNumberAddr;
				
				bool isOK = true;
				
				while (true)
				{
					byte c = viewC64->debugInterface->GetByteC64(addr);
					
					LOGD("addr=%4.4x c=%2.2x '%c'", addr, c, c);
					buf[i] = c;
					
					if (c == 0x20)
					{
						addr++;
						continue;
					}
					
					if (c < 0x30 || c > 0x39)
						break;
					
					addr++;
					i++;
					
					if (i == 254)
					{
						isOK = false;
						break;
					}
				}
				
				if (isOK)
				{
					foundBasicSys = true;
					
					int startAddr = atoi(buf);
					
					// some decrunchers need correct basic pointers
					
					// set beginning of BASIC area
					viewC64->debugInterface->SetByteC64(0x002B, 0x01);
					viewC64->debugInterface->SetByteC64(0x002C, 0x08);
					
					// set beginning of variable/arrays area
					viewC64->debugInterface->SetByteC64(0x002D, endAddr & 0x00FF);
					viewC64->debugInterface->SetByteC64(0x002F, endAddr & 0x00FF);
					viewC64->debugInterface->SetByteC64(0x0031, endAddr & 0x00FF);
					viewC64->debugInterface->SetByteC64(0x00AE, endAddr & 0x00FF);
					
					viewC64->debugInterface->SetByteC64(0x002E, (endAddr >> 8) & 0x00FF);
					viewC64->debugInterface->SetByteC64(0x0030, (endAddr >> 8) & 0x00FF);
					viewC64->debugInterface->SetByteC64(0x0032, (endAddr >> 8) & 0x00FF);
					viewC64->debugInterface->SetByteC64(0x00AF, (endAddr >> 8) & 0x00FF);
					
					// set end of BASIC area
					viewC64->debugInterface->SetByteC64(0x0033, 0x00);
					viewC64->debugInterface->SetByteC64(0x0037, 0x00);
					
					viewC64->debugInterface->SetByteC64(0x0034, 0xA0);
					viewC64->debugInterface->SetByteC64(0x0038, 0xA0);
					
					// stop cursor flash
					viewC64->debugInterface->SetByteC64(0x00CC, 0x01);
					
					LOGD("LoadPRG: ... JMP '%s' (%d)", buf, startAddr);
					
					viewC64->viewC64MemoryMap->ClearReadWriteMarkers();
					viewC64->viewDrive1541MemoryMap->ClearReadWriteMarkers();
					
					viewC64->debugInterface->MakeJsrC64(startAddr);
					
					viewC64->ShowMainScreen();

					if (viewC64->debugInterface->IsCpuJam())
					{
						viewC64->debugInterface->ForceRunAndUnJamCpu();
					}
				}
				
				SYS_ReleaseCharBuf(buf);
			}
		}
	}
	
	if (autoStart && c64SettingsAutoJmpAlwaysToLoadedPRGAddress && !foundBasicSys)
	{
		LOGD("LoadPRG: c64SettingsAutoJmpAlwaysToLoadedPRGAddress");
		viewC64->debugInterface->MakeJsrC64(startAddr);
		viewC64->ShowMainScreen();
		
		if (viewC64->debugInterface->IsCpuJam())
		{
			viewC64->debugInterface->ForceRunAndUnJamCpu();
		}

	}

	if ((c64SettingsAutoJmpAlwaysToLoadedPRGAddress || autoStart) && showAddressInfo)
	{
		char *buf = SYS_GetCharBuf();
		
		sprintf(buf, "Loaded from $%04X to $%04X", startAddr, endAddr);
		guiMain->ShowMessage(buf);
		
		SYS_ReleaseCharBuf(buf);
	}
	
	if (c64SettingsForceUnpause)
	{
		LOGD("LoadPRG: unpause");
		viewC64->debugInterface->SetDebugMode(C64_DEBUG_RUNNING);
	}
	
	viewC64->debugInterface->UnlockMutex();
	
	return true;
}


void CViewMainMenu::LoadPRG(CByteBuffer *byteBuffer, u16 *startAddr, u16 *endAddr)
{
	u16 b1 = byteBuffer->GetByte();
	u16 b2 = byteBuffer->GetByte();
	
	u16 loadPoint = (b2 << 8) | b1;
	
	LOGD("..loadPoint=%4.4x", loadPoint);
	
	u16 addr = loadPoint;
	while (!byteBuffer->isEof())
	{
		u8 b = byteBuffer->GetByte();
		
		
		//		viewC64->debugInterface->SetByteC64(addr, b);
		
		viewC64->debugInterface->SetByteToRamC64(addr, b);
		addr++;
	}
	
	LOGD("LoadPRG: ..loaded till=%4.4x", addr);
	
	*startAddr = loadPoint;
	*endAddr = addr;
}

void CViewMainMenu::ResetAndJSR(int startAddr)
{
	viewC64->debugInterface->Reset();	
	viewC64->debugInterface->MakeJsrC64(startAddr);

}

void CViewMainMenu::ReloadAndRestartPRG()
{
	if (c64SettingsPathToPRG != NULL)
	{
		char *asciiPath = c64SettingsPathToPRG->GetStdASCII();
		LOGD("asciiPath='%s'", asciiPath);
		
		CSlrFileFromOS *file = new CSlrFileFromOS(asciiPath);
		if (!file->Exists())
		{
			delete file;
			guiMain->ShowMessage("Error loading PRG file");
			return;
		}
		
		CByteBuffer *byteBuffer = new CByteBuffer(file, false);
		
		bool ret = LoadPRG(byteBuffer, true, false);
		
		delete asciiPath;
		delete file;
		
		delete byteBuffer;
		
		return;
	}
	else
	{
		guiMain->ShowMessage("Select PRG first");
	}
}


void CViewMainMenu::SystemDialogFileOpenCancelled()
{
}


void CViewMainMenu::DoLogic()
{
	CGuiView::DoLogic();
}

void CViewMainMenu::Render()
{
	//LOGD("CViewMainMenu::Render");
	
//	guiMain->fntConsole->BlitText("CViewMainMenu", 0, 0, 0, 11, 1.0);

	BlitFilledRectangle(0, 0, -1, sizeX, sizeY, 0.5, 0.5, 1.0, 1.0);
		
	float sb = 20;
	float gap = 10;
	
	float tr = 0.64; //163/255;
	float tg = 0.59; //151/255;
	float tb = 1.0; //255/255;
	
	float lr = 0.64;
	float lg = 0.65;
	float lb = 0.65;
	float lSizeY = 3;
	
	float ar = lr;
	float ag = lg;
	float ab = lb;
	
	float scrx = sb;
	float scry = sb;
	float scrsx = sizeX - sb*2.0f;
	float scrsy = sizeY - sb*2.0f;
	float cx = scrsx/2.0f + sb;
	float ax = scrx + scrsx - sb;
	
	BlitFilledRectangle(scrx, scry, -1, scrsx, scrsy, 0, 0, 1.0, 1.0);
	
	float px = scrx + gap;
	float py = scry + gap;
	
	font->BlitTextColor(strHeader, cx, py, -1, fontScale, tr, tg, tb, 1, FONT_ALIGN_CENTER);
	py += fontHeight;
	font->BlitTextColor(strHeader2, cx, py, -1, fontScale, tr, tg, tb, 1, FONT_ALIGN_CENTER);
	py += fontHeight;
	py += 4.0f;
	
	BlitFilledRectangle(scrx, py, -1, scrsx, lSizeY, lr, lg, lb, 1);
	
	py += lSizeY + gap + 4.0f;

	viewMenu->Render();
	
//	font->BlitTextColor("1541 Device 8...", px, py, -1, fontScale, tr, tg, tb, 1);
//	font->BlitTextColor("Alt+8", ax, py, -1, fontScale, tr, tg, tb, 1);
	
	CGuiView::Render();
}

void CViewMainMenu::Render(GLfloat posX, GLfloat posY)
{
	CGuiView::Render(posX, posY);
}

bool CViewMainMenu::ButtonClicked(CGuiButton *button)
{
	return false;
}

bool CViewMainMenu::ButtonPressed(CGuiButton *button)
{
	/*
	if (button == btnDone)
	{
		guiMain->SetView((CGuiView*)guiMain->viewMainEditor);
		GUI_SetPressConsumed(true);
		return true;
	}
	*/
	return false;
}

//@returns is consumed
bool CViewMainMenu::DoTap(GLfloat x, GLfloat y)
{
	LOGG("CViewMainMenu::DoTap:  x=%f y=%f", x, y);
	
	viewMenu->DoTap(x, y);
	return CGuiView::DoTap(x, y);
}

bool CViewMainMenu::DoFinishTap(GLfloat x, GLfloat y)
{
	LOGG("CViewMainMenu::DoFinishTap: %f %f", x, y);
	return CGuiView::DoFinishTap(x, y);
}

//@returns is consumed
bool CViewMainMenu::DoDoubleTap(GLfloat x, GLfloat y)
{
	LOGG("CViewMainMenu::DoDoubleTap:  x=%f y=%f", x, y);
	return CGuiView::DoDoubleTap(x, y);
}

bool CViewMainMenu::DoFinishDoubleTap(GLfloat x, GLfloat y)
{
	LOGG("CViewMainMenu::DoFinishTap: %f %f", x, y);
	return CGuiView::DoFinishDoubleTap(x, y);
}

bool CViewMainMenu::DoScrollWheel(float deltaX, float deltaY)
{
	return viewMenu->DoScrollWheel(deltaX, deltaY);
}

bool CViewMainMenu::DoMove(GLfloat x, GLfloat y, GLfloat distX, GLfloat distY, GLfloat diffX, GLfloat diffY)
{
	return CGuiView::DoMove(x, y, distX, distY, diffX, diffY);
}

bool CViewMainMenu::FinishMove(GLfloat x, GLfloat y, GLfloat distX, GLfloat distY, GLfloat accelerationX, GLfloat accelerationY)
{
	return CGuiView::FinishMove(x, y, distX, distY, accelerationX, accelerationY);
}

bool CViewMainMenu::InitZoom()
{
	return CGuiView::InitZoom();
}

bool CViewMainMenu::DoZoomBy(GLfloat x, GLfloat y, GLfloat zoomValue, GLfloat difference)
{
	return CGuiView::DoZoomBy(x, y, zoomValue, difference);
}

bool CViewMainMenu::DoMultiTap(COneTouchData *touch, float x, float y)
{
	return CGuiView::DoMultiTap(touch, x, y);
}

bool CViewMainMenu::DoMultiMove(COneTouchData *touch, float x, float y)
{
	return CGuiView::DoMultiMove(touch, x, y);
}

bool CViewMainMenu::DoMultiFinishTap(COneTouchData *touch, float x, float y)
{
	return CGuiView::DoMultiFinishTap(touch, x, y);
}

void CViewMainMenu::FinishTouches()
{
	return CGuiView::FinishTouches();
}

void CViewMainMenu::SwitchMainMenuScreen()
{
	if (guiMain->currentView == this)
	{
		viewC64->ShowMainScreen();
	}
	else
	{
		guiMain->SetView(this);
	}
}

bool CViewMainMenu::KeyDown(u32 keyCode, bool isShift, bool isAlt, bool isControl)
{
	if (keyCode == MTKEY_BACKSPACE)
	{
		SwitchMainMenuScreen();
		return true;
	}
	
	if (viewMenu->KeyDown(keyCode, isShift, isAlt, isControl))
		return true;

	if (viewC64->ProcessGlobalKeyboardShortcut(keyCode, isShift, isAlt, isControl))
	{
		return true;
	}

	if (keyCode == MTKEY_ESC)
	{
		SwitchMainMenuScreen();
		return true;
	}


	return CGuiView::KeyDown(keyCode, isShift, isAlt, isControl);
}

bool CViewMainMenu::KeyUp(u32 keyCode, bool isShift, bool isAlt, bool isControl)
{
	if (viewMenu->KeyUp(keyCode, isShift, isAlt, isControl))
		return true;
	
	return CGuiView::KeyUp(keyCode, isShift, isAlt, isControl);
}

bool CViewMainMenu::KeyPressed(u32 keyCode, bool isShift, bool isAlt, bool isControl)
{
	return CGuiView::KeyPressed(keyCode, isShift, isAlt, isControl);
}

void CViewMainMenu::ActivateView()
{
	LOGG("CViewMainMenu::ActivateView()");
	
	viewC64->ShowMouseCursor();
}

void CViewMainMenu::DeactivateView()
{
	LOGG("CViewMainMenu::DeactivateView()");
}

CViewC64MenuItem::CViewC64MenuItem(float height, CSlrString *str, CSlrKeyboardShortcut *shortcut, float r, float g, float b)
: CGuiViewMenuItem(height)
{
	this->str = NULL;
	this->str2 = NULL;
	this->shortcut = shortcut;
	this->r = r;
	this->g = g;
	this->b = b;
	
	if (str != NULL)
		this->SetString(str);
}

// sub item
CViewC64MenuItem::CViewC64MenuItem(float height, CSlrString *str, CSlrKeyboardShortcut *shortcut, float r, float g, float b,
								   CGuiViewMenu *mainMenu)
: CGuiViewMenuItem(height, mainMenu)
{
	this->str = NULL;
	this->str2 = NULL;
	this->shortcut = shortcut;
	this->r = r;
	this->g = g;
	this->b = b;
	
	if (str != NULL)
		this->SetString(str);
}

void CViewC64MenuItem::SetString(CSlrString *str)
{
	if (this->str != NULL)
		delete this->str;
	this->str = str;
	if (this->isSelected)
	{
		this->isSelected = false;
		this->SetSelected(true);
		this->isSelected = true;
	}
}

void CViewC64MenuItem::Execute()
{
}

void CViewC64MenuItem::DebugPrint()
{
	LOGD("CGuiViewMenuItem: %x menu=%x subMenu=%x", this, this->menu, this->subMenu);

	if (this->str != NULL)
	{
		this->str->DebugPrint("menu item str=");
	}
}

void CViewC64MenuItem::SetSelected(bool selected)
{
	if (this->isSelected != selected == true)
	{
		for (int i = 0; i < str->GetLength(); i++)
		{
			u16 chr = str->GetChar(i);
			chr ^= CBMSHIFTEDFONT_INVERT;
			str->SetChar(i, chr);
		}
		return;
	}
}

void CViewC64MenuItem::RenderItem(float px, float py, float pz)
{
	viewC64->viewC64MainMenu->font->BlitTextColor(str, px, py, pz,
												  viewC64->viewC64MainMenu->fontScale, r, g, b, 1);

	if (shortcut != NULL && shortcut->str != NULL)
	{
		viewC64->viewC64MainMenu->font->BlitTextColor(shortcut->str, px + 510, py, pz,
													  viewC64->viewC64MainMenu->fontScale, 0.5, 0.5, 0.5, 1, FONT_ALIGN_RIGHT);
	}
	
	if (str2 != NULL)
	{
		py += viewC64->viewC64MainMenu->fontHeight;
		viewC64->viewC64MainMenu->font->BlitTextColor(str2, px, py, pz,
													  viewC64->viewC64MainMenu->fontScale, r, g, b, 1);
	}
}

//

CViewC64MenuItemOption::CViewC64MenuItemOption(float height, CSlrString *str, CSlrKeyboardShortcut *shortcut, float r, float g, float b,
					   std::vector<CSlrString *> *options, CSlrFont *font, float fontScale)
: CViewC64MenuItem(height, NULL, shortcut, r, g, b)
{
	this->options = options;
	this->selectedOption = 0;
	
	textStr = NULL;

	// update display string
	this->SetString(str);
}

void CViewC64MenuItemOption::SetOptions(std::vector<CSlrString *> *options)
{
	if (this->options != NULL)
	{
		while (!this->options->empty())
		{
			CSlrString *opt = this->options->back();
			this->options->pop_back();
			delete opt;
		}
		delete this->options;
	}
	
	this->options = options;
	
	UpdateDisplayString();
}

void CViewC64MenuItemOption::SetString(CSlrString *str)
{
	if (this->textStr != NULL)
		delete this->textStr;
	
	this->textStr = str;
	
	UpdateDisplayString();
	
}

void CViewC64MenuItemOption::UpdateDisplayString()
{
	if (this->options != NULL)
	{
		CSlrString *newStr = new CSlrString(this->textStr);
		newStr->Concatenate((*this->options)[selectedOption]);
		
		CViewC64MenuItem::SetString(newStr);
	}
}

void CViewC64MenuItemOption::SwitchToPrev()
{
	if (selectedOption == 0)
	{
		selectedOption = options->size()-1;
	}
	else
	{
		selectedOption--;
	}
	
	this->UpdateDisplayString();
	
	this->menu->callback->MenuCallbackItemChanged(this);
}

void CViewC64MenuItemOption::SwitchToNext()
{
	if (selectedOption == options->size()-1)
	{
		selectedOption = 0;
	}
	else
	{
		selectedOption++;
	}
	
	this->UpdateDisplayString();
	
	this->menu->callback->MenuCallbackItemChanged(this);
}

void CViewC64MenuItemOption::SetSelectedOption(int newSelectedOption, bool runCallback)
{
	selectedOption = newSelectedOption;
	this->UpdateDisplayString();
	
	if (runCallback)
		this->menu->callback->MenuCallbackItemChanged(this);
}

bool CViewC64MenuItemOption::KeyDown(u32 keyCode)
{
	if (keyCode == MTKEY_ARROW_LEFT)
	{
		SwitchToPrev();
		return true;
	}
	else if (keyCode == MTKEY_ARROW_RIGHT || keyCode == MTKEY_ENTER)
	{
		SwitchToNext();
		return true;
	}
	
	return false;
}

void CViewC64MenuItemOption::Execute()
{
	SwitchToNext();
}

//


CViewC64MenuItemFloat::CViewC64MenuItemFloat(float height, CSlrString *str, CSlrKeyboardShortcut *shortcut, float r, float g, float b,
											 float minimum, float maximum, float step, CSlrFont *font, float fontScale)
: CViewC64MenuItem(height, NULL, shortcut, r, g, b)
{
	this->minimum = minimum;
	this->maximum = maximum;
	this->step = step;
	
	textStr = NULL;
	
	// update display string
	this->SetString(str);
}

void CViewC64MenuItemFloat::SetValue(float value, bool runCallback)
{
	this->value = value;
	
	UpdateDisplayString();
	
	if (runCallback)
		this->menu->callback->MenuCallbackItemChanged(this);
}

void CViewC64MenuItemFloat::SetString(CSlrString *str)
{
	if (this->textStr != NULL)
		delete this->textStr;
	
	this->textStr = str;
	
	UpdateDisplayString();
	
}

void CViewC64MenuItemFloat::UpdateDisplayString()
{
	char *buf = SYS_GetCharBuf();
	sprintf(buf, "%-5.2f", value);
	CSlrString *valStr = new CSlrString(buf);
	SYS_ReleaseCharBuf(buf);
	
	CSlrString *newStr = new CSlrString(this->textStr);
	newStr->Concatenate(valStr);
	CViewC64MenuItem::SetString(newStr);
	
	delete valStr;
}

void CViewC64MenuItemFloat::SwitchToPrev()
{
	value -= step;
	
	if (value < minimum)
		value = minimum;
	
	this->UpdateDisplayString();
	
	this->menu->callback->MenuCallbackItemChanged(this);
}

void CViewC64MenuItemFloat::SwitchToNext()
{
	value += step;
	
	if (value > maximum)
		value = maximum;
	
	this->UpdateDisplayString();
	
	this->menu->callback->MenuCallbackItemChanged(this);
}

bool CViewC64MenuItemFloat::KeyDown(u32 keyCode)
{
	if (keyCode == MTKEY_ARROW_LEFT)
	{
		SwitchToPrev();
		return true;
	}
	else if (keyCode == MTKEY_ARROW_RIGHT || keyCode == MTKEY_ENTER)
	{
		SwitchToNext();
		return true;
	}
	
	return false;
}

void CViewC64MenuItemFloat::Execute()
{
	SwitchToNext();
}

