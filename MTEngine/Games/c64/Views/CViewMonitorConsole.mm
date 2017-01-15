#include "CViewMonitorConsole.h"
#include "CGuiViewConsole.h"
#include "CSlrString.h"
#include "C64DebugInterface.h"
#include "SYS_CFileSystem.h"
#include "C64SettingsStorage.h"
#include "CSlrFileFromOS.h"
#include "CViewDataDump.h"
#include "CGuiMain.h"
#include "CViewDisassemble.h"
#include "CViewMemoryMap.h"

#define C64DEBUGGER_MONITOR_HISTORY_FILE_VERSION	1

#define C64MONITOR_DEVICE_C64			1
#define C64MONITOR_DEVICE_DISK1541_8	2

CViewMonitorConsole::CViewMonitorConsole(GLfloat posX, GLfloat posY, GLfloat posZ, GLfloat sizeX, GLfloat sizeY, C64DebugInterface *debugInterface)
: CGuiView(posX, posY, posZ, sizeX, sizeY)
{
	this->debugInterface = debugInterface;
	
	this->viewConsole = new CGuiViewConsole(posX, posY, posZ, sizeX, sizeY, viewC64->fontCBMShifted, 1.250f, 20, true, this);
	
	this->viewConsole->SetPrompt(".");

	this->viewConsole->textColorR = 0.23f;
	this->viewConsole->textColorG = 0.988f;
	this->viewConsole->textColorB = 0.203f;
	this->viewConsole->textColorA = 1.0f;

	
	this->device = C64MONITOR_DEVICE_C64;
	this->dataAdapter = viewC64->viewC64MemoryDataDump->dataAdapter;
	
	memoryExtensions.push_back(new CSlrString("bin"));
	prgExtensions.push_back(new CSlrString("prg"));
	disassembleExtensions.push_back(new CSlrString("asm"));
	
	char *buf = SYS_GetCharBuf();
	sprintf(buf, "C64 Debugger v%s monitor", C64DEBUGGER_VERSION_STRING);
	this->viewConsole->PrintLine(buf);
	
	RestoreMonitorHistory();
}

void CViewMonitorConsole::SetPosition(GLfloat posX, GLfloat posY, GLfloat posZ, GLfloat sizeX, GLfloat sizeY, float fontScale, int numLines)
{
	this->viewConsole->SetPosition(posX, posY, posZ, sizeX, sizeY);
	this->viewConsole->SetFontScale(fontScale);
	this->viewConsole->SetNumLines(numLines);
	
	CGuiElement::SetPosition(posX, posY, posZ, sizeX, sizeY);
}

bool CViewMonitorConsole::KeyDown(u32 keyCode, bool isShift, bool isAlt, bool isControl)
{
	u32 upKey;
 
	//LOGD("commandLineCursorPos=%d", viewConsole->commandLineCursorPos);

	// hack for case-sensitive file names ;)
	if (viewConsole->commandLine[0] == 'S')
	{
		// 0123456789012345678
		// S XXXX YYYY filename
		// S PRG XXXX YYYY filename

		if (viewConsole->commandLine[2] != 'P' && viewConsole->commandLineCursorPos >= 11)
		{
			upKey = keyCode;
		}
		else if (viewConsole->commandLine[2] == 'P' && viewConsole->commandLineCursorPos >= 15)
		{
			upKey = keyCode;
		}
		else
		{
			upKey = toupper(keyCode);
		}
	}
	else if (viewConsole->commandLine[0] == 'L')
	{
		// 0123456789012345678
		// L XXXX filename
		// L PRG filename
		if (viewConsole->commandLine[2] != 'P' && viewConsole->commandLineCursorPos >= 6)
		{
			upKey = keyCode;
		}
		else if (viewConsole->commandLine[2] == 'P' && viewConsole->commandLineCursorPos >= 5)
		{
			upKey = keyCode;
		}
		else
		{
			upKey = toupper(keyCode);
		}
	}
	else
	{
		upKey = toupper(keyCode);
	}

	return this->viewConsole->KeyDown(upKey);
}

void CViewMonitorConsole::Render()
{
	BlitFilledRectangle(posX, posY, posZ, sizeX, sizeY, 0.15f, 0.15f, 0.15f, 1.0f);
	this->viewConsole->Render();
}

void CViewMonitorConsole::GuiViewConsoleExecuteCommand(char *commandText)
{
	UpdateDataAdapters();
	
	this->viewConsole->mutex->Lock();
	
	char *buf = SYS_GetCharBuf();
	sprintf(buf, "%s%s", this->viewConsole->prompt, commandText);
	
	this->viewConsole->PrintLine(buf);
	
	SYS_ReleaseCharBuf(buf);
	
	// tokenize command
	tokenIndex = 0;
	strCommandText = new CSlrString(commandText);
	tokens = strCommandText->Split(' ');
	
	// interpret
	if (tokens->size() > 0)
	{
		CSlrString *token = (*tokens)[tokenIndex];
		
		tokenIndex++;
		
		if (token->CompareWith("HELP") || token->CompareWith("help"))
		{
			CommandHelp();
		}
		else if (token->CompareWith("DEVICE") || token->CompareWith("device"))
		{
			CommandDevice();
		}
		else if (token->CompareWith("F") || token->CompareWith("f"))
		{
			CommandFill();
		}
		else if (token->CompareWith("C") || token->CompareWith("c"))
		{
			CommandCompare();
		}
		else if (token->CompareWith("T") || token->CompareWith("t"))
		{
			CommandTransfer();
		}
		else if (token->CompareWith("H") || token->CompareWith("h"))
		{
			CommandHunt();
		}
		else if (token->CompareWith("S") || token->CompareWith("s"))
		{
			CommandMemorySave();
		}
		else if (token->CompareWith("SPRG") || token->CompareWith("sprg"))
		{
			CommandMemorySavePRG();
		}
		else if (token->CompareWith("L") || token->CompareWith("l"))
		{
			CommandMemoryLoad();
		}
		else if (token->CompareWith("G") || token->CompareWith("g"))
		{
			CommandGoJMP();
		}
		else if (token->CompareWith("D") || token->CompareWith("d"))
		{
			CommandDisassemble();
		}
		else
		{
			this->viewConsole->PrintLine("Unknown command.");
			LOGD("commandText='%s'", commandText);
			token->DebugPrint("token=");
		}
	}
	
	// delete tokens
	while(!tokens->empty())
	{
		CSlrString *token = tokens->back();
		tokens->pop_back();
		delete token;
	}
	
	delete tokens; tokens = NULL;
	delete strCommandText; strCommandText = NULL;
	
	this->viewConsole->ResetCommandLine();
	
	StoreMonitorHistory();

	this->viewConsole->mutex->Unlock();
}

bool CViewMonitorConsole::GetToken(CSlrString **token)
{
	if (tokenIndex >= tokens->size())
	{
		return false;
	}
	
	*token = (*tokens)[tokenIndex];

	return true;
}

bool CViewMonitorConsole::GetTokenValueHex(int *value)
{
	CSlrString *token;
	
	if (GetToken(&token) == false)
		return false;
	
	char *hexStr = token->GetStdASCII();
	
	// check chars
	for (int i = 0; i < strlen(hexStr); i++)
	{
		if ((hexStr[i] >= '0' && hexStr[i] <= '9')
			|| (hexStr[i] >= 'A' && hexStr[i] <= 'F')
			|| (hexStr[i] >= 'a' && hexStr[i] <= 'f'))
			continue;
		
		delete hexStr;
		return false;
	}
	
	sscanf(hexStr, "%x", value);

	delete [] hexStr;
	
	tokenIndex++;
	
	return true;
}

void CViewMonitorConsole::CommandHelp()
{
	this->viewConsole->PrintLine("DEVICE C / D / 8");
	this->viewConsole->PrintLine("    set current device (C64/Disk/Disk)");
	this->viewConsole->PrintLine("F <from address> <to address> <value>");
	this->viewConsole->PrintLine("    fill memory with value");
	this->viewConsole->PrintLine("C <from address> <to address> <destination address>");
	this->viewConsole->PrintLine("    compare memory with memory");
	this->viewConsole->PrintLine("H <from address> <to address> <value> [<value> ...]");
	this->viewConsole->PrintLine("    compare memory with values");
	this->viewConsole->PrintLine("T <from address> <to address> <destination address>");
	this->viewConsole->PrintLine("    copy memory");
	this->viewConsole->PrintLine("L [PRG] [from address] [file name]");
	this->viewConsole->PrintLine("    load memory");
	this->viewConsole->PrintLine("S [PRG] <from address> <to address> [file name]");
	this->viewConsole->PrintLine("    save memory (with option as PRG file)");
//	this->viewConsole->PrintLine("SPRG <from address> <to address> [file name]");
//	this->viewConsole->PrintLine("    save memory as PRG file");
	this->viewConsole->PrintLine("D [NH] <from address> <to address> [file name]");
	this->viewConsole->PrintLine("    disassemble memory (with option NH without hex)");
	this->viewConsole->PrintLine("G <address>");
	this->viewConsole->PrintLine("    jmp to address");


}

void CViewMonitorConsole::CommandGoJMP()
{
	int addrStart;
	
	if (GetTokenValueHex(&addrStart) == false)
	{
		this->viewConsole->PrintLine("Usage: G <address>");
		return;
	}
	
	if (addrStart < 0x0000 || addrStart > 0xFFFF)
	{
		this->viewConsole->PrintLine("Bad address value.");
		return;
	}
	
	if (this->device == C64MONITOR_DEVICE_C64)
	{
		viewC64->debugInterface->MakeJmpNoResetC64(addrStart);
	}
	else
	{
		viewC64->debugInterface->MakeJmpNoReset1541(addrStart);
	}
}


void CViewMonitorConsole::CommandDevice()
{
	CSlrString *token;
	
	if (!GetToken(&token))
	{
		if (this->device == C64MONITOR_DEVICE_C64)
		{
			this->viewConsole->PrintLine("Current device: C64");
		}
		else
		{
			this->viewConsole->PrintLine("Current device: 1541 DISK (8)");
		}
		return;
	}
	
	if (token->CompareWith("C"))
	{
		this->device = C64MONITOR_DEVICE_C64;
	}
	else if (token->CompareWith("D") || token->CompareWith("8"))
	{
		this->device= C64MONITOR_DEVICE_DISK1541_8;
	}
	else
	{
		this->viewConsole->PrintLine("Usage: DEVICE C|D|8");
		return;
	}
	
	UpdateDataAdapters();
}

void CViewMonitorConsole::UpdateDataAdapters()
{
	bool v1, v2;
	if (device == C64MONITOR_DEVICE_C64)
	{
		this->dataAdapter = viewC64->viewC64MemoryDataDump->dataAdapter;
		
		v1 = true;
		v2 = false;
	}
	else if (device == C64MONITOR_DEVICE_DISK1541_8)
	{
		this->dataAdapter = viewC64->viewDrive1541MemoryDataDump->dataAdapter;

		v1 = false;
		v2 = true;
	}
	
	bool v;
	v = v1;
	viewC64->viewC64Disassemble->SetVisible(v);
	viewC64->viewC64MemoryDataDump->SetVisible(v);
	viewC64->viewC64MemoryMap->SetVisible(v);
	viewC64->debugInterface->debugOnC64 = v;
	v = v2;
	viewC64->viewDrive1541Disassemble->SetVisible(v);
	viewC64->viewDrive1541MemoryDataDump->SetVisible(v);
	viewC64->viewDrive1541MemoryMap->SetVisible(v);
	viewC64->debugInterface->debugOnDrive1541 = v;

}

void CViewMonitorConsole::CommandFill()
{
	int addrStart, addrEnd, value;
	
	if (GetTokenValueHex(&addrStart) == false)
	{
		this->viewConsole->PrintLine("Usage: F <from addres> <to address> <value>");
		return;
	}
	
	if (addrStart < 0x0000 || addrStart > 0xFFFF)
	{
		this->viewConsole->PrintLine("Bad 'from' address value.");
		return;
	}

	//
	if (GetTokenValueHex(&addrEnd) == false)
	{
		this->viewConsole->PrintLine("Missing 'to' address value.");
		return;
	}
	
	if (addrEnd < 0x0000 || addrEnd > 0xFFFF)
	{
		this->viewConsole->PrintLine("Bad 'to' address value.");
		return;
	}

	//
	if (GetTokenValueHex(&value) == false)
	{
		this->viewConsole->PrintLine("Missing fill value.");
		return;
	}
	
	if (value < 0x00 || value > 0xFF)
	{
		this->viewConsole->PrintLine("Bad fill value.");
		return;
	}
	
	if (addrEnd <= addrStart)
	{
		this->viewConsole->PrintLine("Usage: F <from addres> <to address> <value>");
		return;
	}

	LOGD("Fill: %04x %04x %02x", addrStart, addrEnd, value);
	
	bool avail;
	
	for (int i = addrStart; i < addrEnd; i++)
	{
		dataAdapter->AdapterWriteByte(i, value, &avail);
	}
}

void CViewMonitorConsole::CommandCompare()
{
	int addrStart, addrEnd, addrDestination;
	
	if (GetTokenValueHex(&addrStart) == false)
	{
		this->viewConsole->PrintLine("Usage: C <from addres> <to address> <destination address>");
		return;
	}
	
	if (addrStart < 0x0000 || addrStart > 0xFFFF)
	{
		this->viewConsole->PrintLine("Bad 'from' address value.");
		return;
	}
	
	//
	if (GetTokenValueHex(&addrEnd) == false)
	{
		this->viewConsole->PrintLine("Missing 'to' address value.");
		return;
	}
	
	if (addrEnd < 0x0000 || addrEnd > 0xFFFF)
	{
		this->viewConsole->PrintLine("Bad 'to' address value.");
		return;
	}
	
	//
	if (GetTokenValueHex(&addrDestination) == false)
	{
		this->viewConsole->PrintLine("Missing 'destination' address value.");
		return;
	}
	
	if (addrDestination < 0x0000 || addrDestination > 0xFFFF)
	{
		this->viewConsole->PrintLine("Bad 'destination' address value.");
		return;
	}
	
	if (addrEnd <= addrStart)
	{
		this->viewConsole->PrintLine("From address must be less than to address.");
		this->viewConsole->PrintLine("Usage: C <from addres> <to address> <destination address>");
		return;
	}
	
	LOGD("Compare: %04x %04x %04x", addrStart, addrEnd, addrDestination);
	
	bool a;
	
	char *buf = SYS_GetCharBuf();
	
	int len = addrEnd - addrStart;
	
	int addr1 = addrStart;
	int addr2 = addrDestination;
	
	for (int i = 0; i < len; i++)
	{
		uint8 v1, v2;
		dataAdapter->AdapterReadByte(addr1, &v1, &a);
		dataAdapter->AdapterReadByte(addr2, &v2, &a);
		
		if (v1 != v2)
		{
			sprintf (buf, " %04X %04X %02X %02X", addr1, addr2, v1, v2);
			viewConsole->PrintLine(buf);
		}
		
		addr1++;
		addr2++;
	}
	
	SYS_ReleaseCharBuf(buf);
}

void CViewMonitorConsole::CommandTransfer()
{
	int addrStart, addrEnd, addrDestination;
	
	if (GetTokenValueHex(&addrStart) == false)
	{
		this->viewConsole->PrintLine("Usage: T <from addres> <to address> <destination address>");
		return;
	}
	
	if (addrStart < 0x0000 || addrStart > 0xFFFF)
	{
		this->viewConsole->PrintLine("Bad 'from' address value.");
		return;
	}
	
	//
	if (GetTokenValueHex(&addrEnd) == false)
	{
		this->viewConsole->PrintLine("Missing 'to' address value.");
		return;
	}
	
	if (addrEnd < 0x0000 || addrEnd > 0xFFFF)
	{
		this->viewConsole->PrintLine("Bad 'to' address value.");
		return;
	}
	
	//
	if (GetTokenValueHex(&addrDestination) == false)
	{
		this->viewConsole->PrintLine("Missing 'destination' address value.");
		return;
	}
	
	if (addrDestination < 0x0000 || addrDestination > 0xFFFF)
	{
		this->viewConsole->PrintLine("Bad 'destination' address value.");
		return;
	}
	
	if (addrEnd <= addrStart)
	{
		this->viewConsole->PrintLine("From address must be less than to address.");
		this->viewConsole->PrintLine("Usage: T <from addres> <to address> <destination address>");
		return;
	}
	
	LOGD("Transfer: %04x %04x %04x", addrStart, addrEnd, addrDestination);
	
	bool a;
	
	int len = addrEnd - addrStart;
	
	uint8 *memoryBuffer = new uint8[0x10000];
	dataAdapter->AdapterReadBlockDirect(memoryBuffer, addrStart, addrEnd);
	
	uint8 *writeBuffer = new uint8[len];
	memcpy(writeBuffer, memoryBuffer + addrStart, len);

	int addr = addrDestination;
	for (int i = 0; i < len; i++)
	{
		dataAdapter->AdapterWriteByte(addr, writeBuffer[i], &a);
		addr++;
	}
	
	delete [] memoryBuffer;
	delete [] writeBuffer;
}

void CViewMonitorConsole::CommandHunt()
{
	int addrStart, addrEnd;
	
	if (GetTokenValueHex(&addrStart) == false)
	{
		this->viewConsole->PrintLine("Usage: H <from addres> <to address> <value> [<value> ...]");
		return;
	}
	
	if (addrStart < 0x0000 || addrStart > 0xFFFF)
	{
		this->viewConsole->PrintLine("Bad 'from' address value.");
		return;
	}
	
	//
	if (GetTokenValueHex(&addrEnd) == false)
	{
		this->viewConsole->PrintLine("Missing 'to' address value.");
		return;
	}
	
	if (addrEnd < 0x0000 || addrEnd > 0xFFFF)
	{
		this->viewConsole->PrintLine("Bad 'to' address value.");
		return;
	}
	
	if (addrEnd <= addrStart)
	{
		this->viewConsole->PrintLine("From address must be less than to address.");
		this->viewConsole->PrintLine("Usage: H <from addres> <to address> <value> [<value> ...]");
		return;
	}

	std::list<uint8> values;

	int val;
	
	while (GetTokenValueHex(&val))
	{
		if (val < 0x00 || val > 0xFF)
		{
			this->viewConsole->PrintLine("Bad hunt value.");
			return;
		}
		values.push_back(val);
	}
	
	if (values.size() == 0)
	{
		this->viewConsole->PrintLine("No values entered.");
		this->viewConsole->PrintLine("Usage: H <from addres> <to address> <value> [<value> ...]");
		return;
	}
	
	bool a;
	
	char *buf = SYS_GetCharBuf();
	char *buf2 = SYS_GetCharBuf();
	
	int numAddresses = 0;
	
	for (int i = addrStart; i < addrEnd; i++)
	{
		if (addrEnd + values.size() > 0xFFFF)
			break;
		
		bool found = true;

		int addr = i;
		
		for (std::list<uint8>::iterator it = values.begin(); it != values.end(); it++)
		{
			uint8 v;
			dataAdapter->AdapterReadByte(addr, &v, &a);
			
			if (a == false)
			{
				found = false;
				break;
			}
			
			if (v != *it)
			{
				found = false;
				break;
			}
			
			addr++;
		}
		
		if (found)
		{
			sprintf(buf2, " %04X", i);
			strcat(buf, buf2);
			numAddresses++;
			
			if (numAddresses == 8)	
			{
				viewConsole->PrintLine(buf);
				buf[0] = 0x00;
				numAddresses = 0;
			}
		}
	}
	
	if (numAddresses != 0)
	{
		viewConsole->PrintLine(buf);
	}
	
	SYS_ReleaseCharBuf(buf);
	SYS_ReleaseCharBuf(buf2);
}

void CViewMonitorConsole::CommandMemorySave()
{
	CSlrString *token;
	if (GetToken(&token) == false)
	{
		this->viewConsole->PrintLine("Usage: S [PRG] <from addres> <to address> [file name]");
		return;
	}
	
	if (token->CompareWith("prg") || token->CompareWith("PRG"))
	{
		tokenIndex++;
		CommandMemorySavePRG();
		return;
	}
	
	if (GetTokenValueHex(&addrStart) == false)
	{
		this->viewConsole->PrintLine("Usage: S [PRG] <from addres> <to address> [file name]");
		return;
	}
	
	if (addrStart < 0x0000 || addrStart > 0xFFFF)
	{
		this->viewConsole->PrintLine("Bad 'from' address value.");
		return;
	}
	
	//
	if (GetTokenValueHex(&addrEnd) == false)
	{
		this->viewConsole->PrintLine("Missing 'to' address value.");
		return;
	}
	
	if (addrEnd < 0x0000 || addrEnd > 0xFFFF)
	{
		this->viewConsole->PrintLine("Bad 'to' address value.");
		return;
	}
	
	if (addrEnd <= addrStart)
	{
		this->viewConsole->PrintLine("Usage: S [PRG] <from addres> <to address> [file name]");
		return;
	}
	
	memoryDumpAsPRG = false;
	CommandMemorySaveDump();
}

void CViewMonitorConsole::CommandMemorySavePRG()
{
	if (GetTokenValueHex(&addrStart) == false)
	{
		this->viewConsole->PrintLine("Usage: S [PRG] <from addres> <to address> [file name]");
		return;
	}
	
	if (addrStart < 0x0000 || addrStart > 0xFFFF)
	{
		this->viewConsole->PrintLine("Bad 'from' address value.");
		return;
	}
	
	//
	if (GetTokenValueHex(&addrEnd) == false)
	{
		this->viewConsole->PrintLine("Missing 'to' address value.");
		return;
	}
	
	if (addrEnd < 0x0000 || addrEnd > 0xFFFF)
	{
		this->viewConsole->PrintLine("Bad 'to' address value.");
		return;
	}
	
	if (addrEnd <= addrStart)
	{
		this->viewConsole->PrintLine("Usage: S [PRG] <from addres> <to address> [file name]");
		return;
	}
	
	memoryDumpAsPRG = true;
	CommandMemorySaveDump();
}

void CViewMonitorConsole::CommandMemorySaveDump()
{
	CSlrString *fileName = NULL;
	if (GetToken(&fileName) == false)
	{
		// no file name supplied, open dialog
		CSlrString *defaultFileName = new CSlrString("c64memory");
		
		CSlrString *windowTitle = new CSlrString("Dump C64 memory");
		
		if (memoryDumpAsPRG == false)
		{
			SYS_DialogSaveFile(this, &memoryExtensions, defaultFileName, c64SettingsDefaultMemoryDumpFolder, windowTitle);
		}
		else
		{
			SYS_DialogSaveFile(this, &prgExtensions, defaultFileName, c64SettingsDefaultMemoryDumpFolder, windowTitle);
		}
		
		delete windowTitle;
		delete defaultFileName;
	}
	else
	{
		CSlrString *filePath = new CSlrString();

		if (c64SettingsDefaultMemoryDumpFolder != NULL)
		{
			if (SYS_FileDirExists(c64SettingsDefaultMemoryDumpFolder))
			{
				filePath->Concatenate(c64SettingsDefaultMemoryDumpFolder);
			}
		}
		filePath->Concatenate(fileName);
		
		if (DoMemoryDumpToFile(addrStart, addrEnd, memoryDumpAsPRG, filePath) == false)
		{
			char *cPath = filePath->GetStdASCII();
			this->viewConsole->PrintLine("Save memory dump failed to file %s", cPath);
			delete [] cPath;
		}
		
		delete filePath;
	}
}

void CViewMonitorConsole::SystemDialogFileSaveSelected(CSlrString *filePath)
{
	if (DoMemoryDumpToFile(addrStart, addrEnd, memoryDumpAsPRG, filePath) == false)
	{
		char *cPath = filePath->GetStdASCII();
		this->viewConsole->PrintLine("Save memory dump failed to file %s", cPath);
		delete [] cPath;
	}
	
	delete filePath;
}

void CViewMonitorConsole::SystemDialogFileSaveCancelled()
{
}


bool CViewMonitorConsole::DoMemoryDumpToFile(int addrStart, int addrEnd, bool isPRG, CSlrString *filePath)
{
	filePath->DebugPrint("DoMemoryDumpToFile: ");
	
	if (c64SettingsDefaultMemoryDumpFolder != NULL)
		delete c64SettingsDefaultMemoryDumpFolder;
	c64SettingsDefaultMemoryDumpFolder = filePath->GetFilePathWithoutFileNameComponentFromPath();
	C64DebuggerStoreSettings();
	
	// Correct addrEnd:
	// VICE monitor saves memory to file from addrStart to *addrEnd inclusive*
	addrEnd += 1;

	// get file path
	char *cFilePath = filePath->GetStdASCII();
	
	FILE *fp;
	fp = fopen(cFilePath, "wb");

	delete [] cFilePath;

	if (!fp)
	{
		return false;
	}
	
	int len = addrEnd - addrStart;
	uint8 *memoryBuffer = new uint8[0x10000];
	dataAdapter->AdapterReadBlockDirect(memoryBuffer, addrStart, addrEnd);
	
	uint8 *writeBuffer = new uint8[len];
	memcpy(writeBuffer, memoryBuffer + addrStart, len);
	
	if (isPRG)
	{
		// write header
		uint8 buf[2];
		buf[0] = addrStart & 0x00FF;
		buf[1] = (addrStart >> 8) & 0x00FF;
		
		fwrite(buf, 1, 2, fp);
	}
	
	
	int lenWritten = fwrite(writeBuffer, 1, len, fp);
	fclose(fp);
	
	delete [] writeBuffer;
	delete [] memoryBuffer;
	
	if (lenWritten != len)
	{
		return false;
	}
	
	char *buf = SYS_GetCharBuf();
	
	CSlrString *fileName = filePath->GetFileNameComponentFromPath();
	char *cFileName = fileName->GetStdASCII();
	
	sprintf(buf, "Stored %04X bytes to file %s", lenWritten, cFileName);
	viewConsole->PrintLine(buf);
	
	delete [] cFileName;
	delete fileName;
	
	SYS_ReleaseCharBuf(buf);
	
	return true;
}

void CViewMonitorConsole::CommandMemoryLoad()
{
	CSlrString *token;
	if (GetToken(&token) == false)
	{
		//this->viewConsole->PrintLine("Usage: L [PRG] [from addres] [file name]");
		// no tokens - just open LOAD PRG dialog
		viewC64->viewC64MainMenu->OpenDialogLoadPRG();
		return;
	}

	memoryDumpAsPRG = false;

	if (token->CompareWith("prg") || token->CompareWith("PRG"))
	{
		tokenIndex++;
		
		memoryDumpAsPRG = true;

		addrStart = -1;
	}
	
	if (memoryDumpAsPRG == false || tokens->size() == 4)
	{
		if (GetTokenValueHex(&addrStart) == false)
		{
			this->viewConsole->PrintLine("Usage: L [PRG] [from addres] [file name]");
			return;
		}
		
		if (addrStart < 0x0000 || addrStart > 0xFFFF)
		{
			this->viewConsole->PrintLine("Bad 'from' address value.");
			return;
		}
	}
	
	CommandMemoryLoadDump();
}

void CViewMonitorConsole::CommandMemoryLoadDump()
{
	CSlrString *fileName = NULL;
	if (GetToken(&fileName) == false)
	{
		// no file name supplied, open dialog
		CSlrString *defaultFileName = new CSlrString("c64memory");
		
		CSlrString *windowTitle = new CSlrString("Load C64 memory dump");
		
		if (memoryDumpAsPRG == false)
		{
			SYS_DialogOpenFile(this, NULL, c64SettingsDefaultMemoryDumpFolder, windowTitle);
		}
		else
		{
			SYS_DialogOpenFile(this, &prgExtensions, c64SettingsDefaultMemoryDumpFolder, windowTitle);
		}
		
		delete windowTitle;
		delete defaultFileName;
	}
	else
	{
		CSlrString *filePath = new CSlrString();
		
		if (c64SettingsDefaultMemoryDumpFolder != NULL)
		{
			if (SYS_FileDirExists(c64SettingsDefaultMemoryDumpFolder))
			{
				filePath->Concatenate(c64SettingsDefaultMemoryDumpFolder);
			}
		}
		filePath->Concatenate(fileName);
		
		if (DoMemoryDumpFromFile(addrStart, memoryDumpAsPRG, filePath) == false)
		{
			char *cPath = filePath->GetStdASCII();
			this->viewConsole->PrintLine("Loading memory dump failed from file %s", cPath);
			delete [] cPath;
		}
		
		delete filePath;
	}
}

void CViewMonitorConsole::SystemDialogFileOpenSelected(CSlrString *filePath)
{
	if (DoMemoryDumpFromFile(addrStart, memoryDumpAsPRG, filePath) == false)
	{
		char *cPath = filePath->GetStdASCII();
		this->viewConsole->PrintLine("Loading memory dump failed from file %s", cPath);
		delete [] cPath;
	}
	
	delete filePath;
}

void CViewMonitorConsole::SystemDialogFileOpenCancelled()
{
}

// addrStart -1 means take start address from PRG
bool CViewMonitorConsole::DoMemoryDumpFromFile(int addrStart, bool isPRG, CSlrString *filePath)
{
	filePath->DebugPrint("DoMemoryDumpFromFile: ");
	
	if (c64SettingsDefaultMemoryDumpFolder != NULL)
		delete c64SettingsDefaultMemoryDumpFolder;
	c64SettingsDefaultMemoryDumpFolder = filePath->GetFilePathWithoutFileNameComponentFromPath();
	C64DebuggerStoreSettings();
	
	char *cFilePath = filePath->GetStdASCII();
	
	CSlrFileFromOS *file = new CSlrFileFromOS(cFilePath);
	
	if (!file->Exists())
	{
		char *buf = SYS_GetCharBuf();
		sprintf(buf, "File does not exist at path: %s", cFilePath);
		viewConsole->PrintLine(buf);
		
		delete [] cFilePath;
		delete file;
		
		SYS_ReleaseCharBuf(buf);
		
		return false;
	}
	
	CByteBuffer *byteBuffer = new CByteBuffer();
	byteBuffer->readFromFileNoHeader(file);
	
	delete file;

	bool a;
	int addr = addrStart;
	int len = byteBuffer->length;
	
	if (isPRG)
	{
		u16 b1 = byteBuffer->GetByte();
		u16 b2 = byteBuffer->GetByte();
		
		u16 loadPoint = (b2 << 8) | b1;
		
		if (addrStart == -1)
		{
			addr = loadPoint;
		}
		
		len -= 2;
	}
	
	for (int i = 0; i < len; i++)
	{
		uint8 val = byteBuffer->GetU8();
		dataAdapter->AdapterWriteByte(addr, val, &a);
		
		if (a == false)
			break;
		
		addr++;
	}
	
	char *buf = SYS_GetCharBuf();
	CSlrString *fileName = filePath->GetFileNameComponentFromPath();
	char *cFileName = fileName->GetStdASCII();

	sprintf(buf, "Read %04X bytes from file %s", len, cFileName);
	viewConsole->PrintLine(buf);
	
	SYS_ReleaseCharBuf(buf);

	delete [] cFileName;
	delete fileName;
	
	return true;
}

void CViewMonitorConsole::StoreMonitorHistory()
{
	CByteBuffer *byteBuffer = new CByteBuffer();
	byteBuffer->PutU16(C64DEBUGGER_MONITOR_HISTORY_FILE_VERSION);
	
	byteBuffer->PutByte(viewC64->viewMonitorConsole->viewConsole->commandLineHistory.size());
	for (std::list<char *>::iterator it = viewC64->viewMonitorConsole->viewConsole->commandLineHistory.begin();
		 it != viewC64->viewMonitorConsole->viewConsole->commandLineHistory.end(); it++)
	{
		byteBuffer->PutString(*it);
	}
	
	CSlrString *fileName = new CSlrString("/monitor.dat");
	byteBuffer->storeToSettings(fileName);
	delete fileName;
	
	delete byteBuffer;
}

void CViewMonitorConsole::RestoreMonitorHistory()
{
	CByteBuffer *byteBuffer = new CByteBuffer();
	
	CSlrString *fileName = new CSlrString("/monitor.dat");
	byteBuffer->loadFromSettings(fileName);
	delete fileName;
	
	if (byteBuffer->length == 0)
	{
		LOGD("... no monitor settings found");
		delete byteBuffer;
		return;
	}
	
	u16 version = byteBuffer->GetU16();
	if (version != C64DEBUGGER_MONITOR_HISTORY_FILE_VERSION)
	{
		LOGError("C64DebuggerReadSettings: incompatible version %04x", version);
		delete byteBuffer;
		return;
	}
	
	int historySize = byteBuffer->GetByte();
	for (int i = 0; i < historySize; i++)
	{
		char *cmd = byteBuffer->GetString();
		viewConsole->commandLineHistory.push_back(cmd);
	}
	viewConsole->commandLineHistoryIt = viewConsole->commandLineHistory.end();
	
	delete byteBuffer;
}



////

void CViewMonitorConsole::CommandDisassemble()
{
	disassembleHexCodes = true;
	
	CSlrString *token;
	if (GetToken(&token) == false)
	{
		this->viewConsole->PrintLine("Usage: D [NOHEX] <from addres> <to address> [file name]");
		return;
	}
	
	if (token->CompareWith("nohex") || token->CompareWith("NOHEX")
		|| token->CompareWith("nh") || token->CompareWith("NH"))
	{
		tokenIndex++;
		disassembleHexCodes = false;
	}
	
	if (GetTokenValueHex(&addrStart) == false)
	{
		this->viewConsole->PrintLine("Usage: D [NOHEX] <from addres> <to address> [file name]");
		return;
	}
	
	if (addrStart < 0x0000 || addrStart > 0xFFFF)
	{
		this->viewConsole->PrintLine("Bad 'from' address value.");
		return;
	}
	
	//
	if (GetTokenValueHex(&addrEnd) == false)
	{
		this->viewConsole->PrintLine("Missing 'to' address value.");
		return;
	}
	
	if (addrEnd < 0x0000 || addrEnd > 0xFFFF)
	{
		this->viewConsole->PrintLine("Bad 'to' address value.");
		return;
	}
	
	if (addrEnd <= addrStart)
	{
		this->viewConsole->PrintLine("Usage: D [NOHEX] <from addres> <to address> [file name]");
		return;
	}
	
	CommandDoDisassemble();
}

void CViewMonitorConsole::CommandDoDisassemble()
{
	CSlrString *fileName = NULL;
	if (GetToken(&fileName) == false)
	{
//		// no file name supplied, open dialog
//		CSlrString *defaultFileName = new CSlrString("c64disassemble");
//		
//		CSlrString *windowTitle = new CSlrString("Disassemble C64 memory");
//		
//		SYS_DialogSaveFile(this, &disassembleExtensions, defaultFileName, c64SettingsDefaultMemoryDumpFolder, windowTitle);
//		
//		delete windowTitle;
//		delete defaultFileName;
		
		if (DoDisassembleMemory(addrStart, addrEnd, false, NULL) == false)
		{
			this->viewConsole->PrintLine("Disassemble memory failed.");
		}
	}
	else
	{
		CSlrString *filePath = new CSlrString();
		
		if (c64SettingsDefaultMemoryDumpFolder != NULL)
		{
			c64SettingsDefaultMemoryDumpFolder->DebugPrint("c64SettingsDefaultMemoryDumpFolder=");
			
			if (SYS_FileDirExists(c64SettingsDefaultMemoryDumpFolder))
			{
				filePath->Concatenate(c64SettingsDefaultMemoryDumpFolder);
			}
		}
		filePath->Concatenate(fileName);
		
		if (DoDisassembleMemory(addrStart, addrEnd, false, filePath) == false)
		{
			this->viewConsole->PrintLine("Disassemble memory failed.");
		}
	}
}

bool CViewMonitorConsole::DoDisassembleMemory(int startAddress, int endAddress, bool withLabels, CSlrString *filePath)
{
	FILE *fp = NULL;

	if (filePath != NULL)
	{
		filePath->DebugPrint("DoDisassembleMemory: ");

		if (c64SettingsDefaultMemoryDumpFolder != NULL)
			delete c64SettingsDefaultMemoryDumpFolder;
		c64SettingsDefaultMemoryDumpFolder = filePath->GetFilePathWithoutFileNameComponentFromPath();
		C64DebuggerStoreSettings();
		
		// get file path
		char *cFilePath = filePath->GetStdASCII();
		LOGD("cFilePath='%s'", cFilePath);
		
		fp = fopen(cFilePath, "wb");
		
		delete [] cFilePath;
		
		if (!fp)
		{
			return false;
		}
	}
	
	LOGTODO("!! set correct memory map !!");
	memoryMap = viewC64->viewC64MemoryMap;

	memoryLength = dataAdapter->AdapterGetDataLength();

	int len = addrEnd - addrStart;
	memory = new uint8[0x10000];
	dataAdapter->AdapterReadBlockDirect(memory, startAddress, endAddress);
	
	
	//// perform disassemble
//	viewConsole->PrintLine("Disassemble %04X to %04X", addrStart, addrEnd);

	CByteBuffer *byteBuffer = new CByteBuffer();
	
	int addr = startAddress;
	int renderAddress = startAddress;
	int i;
	bool done = false;
	uint8 opcode;
	uint8 op[3];

	do
	{
		//LOGD("renderAddress=%4.4x l=%4.4x", renderAddress, memoryLength);
		if (addr >= memoryLength)
			break;
		
		if (addr == memoryLength-1)
		{
			DisassembleHexLine(addr, byteBuffer);
			break;
		}
		
		addr = renderAddress;
		
		for (i=0; i<3; i++, addr++)
		{
			if (addr == endAddress)
			{
				done = true;
			}
			
			op[i] = memory[addr];
		}
		
		{
			addr = renderAddress;
			
			// +0
			CViewMemoryMapCell *cell0 = memoryMap->memoryCells[addr];	//% memoryLength
			if (cell0->isExecuteCode)
			{
				opcode = memory[addr ];	//% memoryLength
				renderAddress += DisassembleLine(renderAddress, op[0], op[1], op[2], byteBuffer);
			}
			else
			{
				// +1
				CViewMemoryMapCell *cell1 = memoryMap->memoryCells[ (addr+1) ];	//% memoryLength
				if (cell1->isExecuteCode)
				{
					// check if at addr is 1-length opcode
					opcode = memory[ (renderAddress) ];	//% memoryLength
					if (opcodes[opcode].addressingLength == 1)
					{
						DisassembleLine(renderAddress, op[0], op[1], op[2], byteBuffer);
					}
					else
					{
						DisassembleHexLine(renderAddress, byteBuffer);
					}
					
					renderAddress += 1;
					
					addr = renderAddress;
					for (i=0; i<3; i++, addr++)
					{
						if (addr == endAddress)
						{
							done = true;
						}
						
						op[i] = memory[addr];
					}
					
					opcode = memory[ (renderAddress) ];	//% memoryLength
					renderAddress += DisassembleLine(renderAddress, op[0], op[1], op[2], byteBuffer);
				}
				else
				{
					// +2
					CViewMemoryMapCell *cell2 = memoryMap->memoryCells[ (addr+2) ];	//% memoryLength
					if (cell2->isExecuteCode)
					{
						// check if at addr is 2-length opcode
						opcode = memory[ (renderAddress) ];	//% memoryLength
						if (opcodes[opcode].addressingLength == 2)
						{
							renderAddress += DisassembleLine(renderAddress, op[0], op[1], op[2], byteBuffer);
						}
						else
						{
							DisassembleHexLine(renderAddress, byteBuffer);
							renderAddress += 1;
							
							DisassembleHexLine(renderAddress, byteBuffer);
							renderAddress += 1;
						}
						
						addr = renderAddress;
						for (i=0; i<3; i++, addr++)
						{
							if (addr == endAddress)
							{
								done = true;
							}
							
							op[i] = memory[addr];
						}
						
						opcode = memory[ (renderAddress) ];	//% memoryLength
						renderAddress += DisassembleLine(renderAddress, op[0], op[1], op[2], byteBuffer);
					}
					else
					{
						if (cell0->isExecuteArgument == false)
						{
							// execute not found, just render line
							renderAddress += DisassembleLine(renderAddress, op[0], op[1], op[2], byteBuffer);
						}
						else
						{
							// it is argument
							DisassembleHexLine(renderAddress, byteBuffer);
							renderAddress++;
						}
					}
				}
			}
		}
		
		byteBuffer->PutByte('\n');
		
		if (renderAddress >= endAddress)
			break;
	}
	while (!done);
	
	// end
	byteBuffer->PutByte(0x00);
	
	///
	if (fp != NULL)
	{
		fprintf(fp, "%s", byteBuffer->data);
		fclose(fp);
		
		char *buf = SYS_GetCharBuf();
		
		CSlrString *fileName = filePath->GetFileNameComponentFromPath();
		char *cFileName = fileName->GetStdASCII();
		
		sprintf(buf, "Disassembled %04X to %04X to file %s", addrStart, addrEnd, cFileName);
		viewConsole->PrintLine(buf);
		
		delete [] cFileName;
		delete fileName;
		
		SYS_ReleaseCharBuf(buf);
	}
	else
	{
		viewConsole->PrintString((char*)byteBuffer->data);
	}
	
	return true;
}

//

// Disassemble one hex-only value (for disassemble up)
void CViewMonitorConsole::DisassembleHexLine(int addr, CByteBuffer *outBuffer)
{
	//	LOGD("addr=%4.4x op=%2.2x", addr, op);
	
	// check if this 1-length opcode
	uint8 op = memory[ (addr) % memoryLength];
	if (opcodes[op].addressingLength == 1)
	{
		DisassembleLine(addr, op, 0x00, 0x00, outBuffer);
		return;
	}
	
	
	char buf[128];
	char buf1[16];
	
//	CViewMemoryMapCell *cell = memoryMap->memoryCells[addr];
//	if (cell->isExecuteCode)
	
	
//	if (showLabels)
//	{
//		px += fontSize5*4.0f;
//		
//		std::map<u16, CDisassembleCodeLabel *>::iterator it = codeLabels.find(addr);
//		
//		if (it != codeLabels.end())
//		{
//			CDisassembleCodeLabel *label = it->second;
//			// found a label
//			fontDisassemble->BlitTextColor(label->labelText, label->px, py, -1, fontSize, cr, cg, cb, ca);
//		}
//	}
	
	// addr
	sprintfHexCode16(buf, addr);
	DisassemblePrint(outBuffer, buf);
	
	if (disassembleHexCodes)
	{
		sprintfHexCode8(buf1, op);
		DisassemblePrint(outBuffer, buf1);
	}
	
	if (disassembleHexCodes)
	{
		DisassemblePrint(outBuffer, "???");
	}
	else
	{
		sprintfHexCode8(buf1, op);
		DisassemblePrint(outBuffer, buf1);
	}
	
//	if (addr == currentPC)
//	{
//		BlitFilledRectangle(posX, py, -1.0f,
//							markerSizeX, fontSize, cr, cg, cb, 0.3f);
//	}

}

// Disassemble one instruction, return length
int CViewMonitorConsole::DisassembleLine(int addr, uint8 op, uint8 lo, uint8 hi, CByteBuffer *outBuffer)
{
	//	LOGD("adr=%4.4x op=%2.2x", adr, op);
	
	char buf[128];
	char buf1[16];
	char buf2[2] = {0};
	char buf3[16];
	char buf4[16];
	char bufHexCodes[16];
	int length;
	
//	CViewMemoryMapCell *cell = memoryMap->memoryCells[addr];
//	if (cell->isExecuteCode)
	
	length = opcodes[op].addressingLength;
	
	
	// TODO:
//	if (disassembleShowLabels)
//	{
//		for (int i = 0; i < length; i++)
//		{
//			std::map<u16, CDisassembleCodeLabel *>::iterator it = codeLabels.find(addr + i);
//			
//			if (it != codeLabels.end())
//			{
//				CDisassembleCodeLabel *label = it->second;
//				// found a label
//				fontDisassemble->BlitTextColor(label->labelText, label->px, py, -1, fontSize, cr, cg, cb, ca);
//				
//				break;
//			}
//		}
//	}
	
	
	// addr
	sprintfHexCode16(buf, addr);
	DisassemblePrint(outBuffer, buf);
	
	DisassemblePrint(outBuffer, " ");
	
	if (disassembleHexCodes)
	{
		strcpy(buf1, "         ");
		
		switch (length)
		{
			case 1:
				//sprintf(buf1, "%2.2x       ", op);
				// "xx       "
				sprintfHexCode8WithoutZeroEnding(buf1, op);
				break;
				
			case 2:
				//sprintf(buf1, "%2.2x %2.2x    ", op, lo);
				// "xx xx    "
				sprintfHexCode8WithoutZeroEnding(buf1, op);
				sprintfHexCode8WithoutZeroEnding(buf1+3, lo);
				break;
				
			case 3:
				//sprintf(buf1, "%2.2x %2.2x %2.2x ", op, lo, hi);
				// "xx xx xx "
				sprintfHexCode8WithoutZeroEnding(buf1, op);
				sprintfHexCode8WithoutZeroEnding(buf1+3, lo);
				sprintfHexCode8WithoutZeroEnding(buf1+6, hi);
				break;
		}
		
		strcpy(bufHexCodes, buf1);
		strcat(bufHexCodes, buf2);
		DisassemblePrint(outBuffer, bufHexCodes);
		
		// illegal opcode?
		if (opcodes[op].isIllegal == OP_ILLEGAL)
		{
			DisassemblePrint(outBuffer, "*");
		}
		else
		{
			DisassemblePrint(outBuffer, " ");
		}
	}
	
	// mnemonic
	strcpy(buf3, opcodes[op].name);
	strcat(buf3, " ");
	
	
	switch (opcodes[op].addressingMode)
	{
		case ADDR_IMP:
			sprintf(buf4, "");
			break;
			
		case ADDR_IMM:
			//sprintf(buf4, "#%2.2x", lo);
			buf4[0] = '#';
			sprintfHexCode8(buf4+1, lo);
			break;
			
		case ADDR_ZP:
			//sprintf(buf4, "%2.2x", lo);
			sprintfHexCode8(buf4, lo);
			break;
			
		case ADDR_ZPX:
			//sprintf(buf4, "%2.2x,x", lo);
			sprintfHexCode8WithoutZeroEnding(buf4, lo);
			buf4[2] = ',';
			buf4[3] = 'x';
			buf4[4] = 0x00;
			break;
			
		case ADDR_ZPY:
			//sprintf(buf4, "%2.2x,y", lo);
			sprintfHexCode8WithoutZeroEnding(buf4, lo);
			buf4[2] = ',';
			buf4[3] = 'y';
			buf4[4] = 0x00;
			break;
			
		case ADDR_IZX:
			//sprintf(buf4, "(%2.2x,x)", lo);
			buf4[0] = '(';
			sprintfHexCode8WithoutZeroEnding(buf4+1, lo);
			buf4[3] = ',';
			buf4[4] = 'x';
			buf4[5] = ')';
			buf4[6] = 0x00;
			break;
			
		case ADDR_IZY:
			//sprintf(buf4, "(%2.2x),y", lo);
			buf4[0] = '(';
			sprintfHexCode8WithoutZeroEnding(buf4+1, lo);
			buf4[3] = ')';
			buf4[4] = ',';
			buf4[5] = 'y';
			buf4[6] = 0x00;
			break;
			
		case ADDR_ABS:
			//sprintf(buf4, "%4.4x", (hi << 8) | lo);
			sprintfHexCode8WithoutZeroEnding(buf4, hi);
			sprintfHexCode8(buf4+2, lo);
			break;
			
		case ADDR_ABX:
			//sprintf(buf4, "%4.4x,x", (hi << 8) | lo);
			sprintfHexCode8WithoutZeroEnding(buf4, hi);
			sprintfHexCode8WithoutZeroEnding(buf4+2, lo);
			buf4[4] = ',';
			buf4[5] = 'x';
			buf4[6] = 0x00;
			break;
			
		case ADDR_ABY:
			//sprintf(buf4, "%4.4x,y", (hi << 8) | lo);
			sprintfHexCode8WithoutZeroEnding(buf4, hi);
			sprintfHexCode8WithoutZeroEnding(buf4+2, lo);
			buf4[4] = ',';
			buf4[5] = 'y';
			buf4[6] = 0x00;
			break;
			
		case ADDR_IND:
			//sprintf(buf4, "(%4.4x)", (hi << 8) | lo);
			buf4[0] = '(';
			sprintfHexCode8WithoutZeroEnding(buf4+1, hi);
			sprintfHexCode8WithoutZeroEnding(buf4+3, lo);
			buf4[5] = ')';
			buf4[6] = 0x00;
			break;
			
		case ADDR_REL:
			//sprintf(buf4, "%4.4x", ((addr + 2) + (int8)lo) & 0xFFFF);
			sprintfHexCode16(buf4, ((addr + 2) + (int8)lo) & 0xFFFF);
			break;
		default:
			break;
	}
	
	//sprintf(buf, "%s%s", buf3, buf4);
	strcpy(buf, buf3);
	strcat(buf, buf4);
	
	DisassemblePrint(outBuffer, buf);
	
	int numBytesPerOp = opcodes[op].addressingLength;
	return numBytesPerOp;
}

void CViewMonitorConsole::DisassemblePrint(CByteBuffer *byteBuffer, char *text)
{
	char *t = text;
	while (*t != '\0')
	{
		byteBuffer->PutByte(*t);
		t++;
	}
}

