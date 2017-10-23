#include "CJukeboxPlaylist.h"
#include "SYS_Main.h"
#include "C64SettingsStorage.h"
#include "C64DebugInterface.h"
#include "CViewC64.h"
#include "libjson.h"

#define DEFAULT_PRESS_TIME_MS	100

CJukeboxPlaylist::CJukeboxPlaylist(char *json)
{
	fastBootPatch = true;
	sleepAfterResetMs = 1000;
	showLoadAddressInfo = false;
	fadeSoundVolume = true;
	setLayoutViewNumber = -1; //C64_SCREEN_LAYOUT_C64_ONLY;

	showTextInfo = true;
	showTextFadeTime = 0.75f;
	showTextVisibleTime = 1.5f;

	this->InitFromJSON(json);
}

CJukeboxPlaylist::~CJukeboxPlaylist()
{
	while (!this->entries.empty())
	{
		CJukeboxPlaylistEntry *entry = this->entries.back();
		this->entries.pop_back();
		delete entry;
	}
}

void CJukeboxPlaylist::InitFromJSON(char *json)
{
	LOGD("CJukeboxPlaylist::InitFromJSON: json=\n>>\"%s\"<<", json);
	
	LOGTODO("windows: jeszcze taka mysl luzna... pamietaj ze w pliku JSON na windows sciezki musisz escapowac \
			bo znak \ jest nielegalnym znakiem JSON \
			musi byc \\");
	
	JSONNode n = libjson::parse(json);
	
	JSONNode::iterator it = n.begin();
	while(it != n.end())
	{
		std::string nodeName = it->name();
		LOGD("node='%s'", nodeName.c_str());
		
		if (nodeName == "FastBootPatch")
		{
			fastBootPatch = it->as_bool();
			LOGD("   FastBootPatch=%s", STRBOOL(fastBootPatch));
		}
		else if (nodeName == "WaitAfterResetTime")
		{
			sleepAfterResetMs = it->as_float() * 1000.0f;
			LOGD("   WaitAfterResetTime=%fms", sleepAfterResetMs);
		}
		else if (nodeName == "ShowLoadAddress")
		{
			showLoadAddressInfo = it->as_bool();
			LOGD("   ShowLoadAddress=%s", STRBOOL(showLoadAddressInfo));
		}
		else if (nodeName == "FadeAudioVolume")
		{
			fadeSoundVolume = it->as_bool();
			LOGD("   FadeAudioVolume=%s", STRBOOL(fadeSoundVolume));
		}
		else if (nodeName == "SetLayout")
		{
			setLayoutViewNumber = it->as_int();
			LOGD("   SetLayout=%d", setLayoutViewNumber);
		}
		else if (nodeName == "ShowPopup")
		{
			showTextInfo = it->as_bool();
			LOGD("   ShowPopup=%s", STRBOOL(showTextInfo));
		}
		else if (nodeName == "PopupFadeTime")
		{
			showTextFadeTime = it->as_float();
			LOGD("   PopupFadeTime=%f", showTextFadeTime);
		}
		else if (nodeName == "PopupVisibleTime")
		{
			showTextVisibleTime = it->as_float();
			LOGD("   PopupVisibleTime=%f", showTextVisibleTime);
		}
		else if (nodeName == "Playlist")
		{
			LOGD("Playlist");
			JSONNode entries = *it;
			JSONNode::iterator itEntries = entries.begin();
			
			while(itEntries != entries.end())
			{
				JSONNode jsonEntry = *itEntries;
				JSONNode::iterator itEntry = jsonEntry.begin();
				
				CJukeboxPlaylistEntry *playlistEntry = new CJukeboxPlaylistEntry();
				this->entries.push_back(playlistEntry);
				
				while(itEntry != jsonEntry.end())
				{
					nodeName = itEntry->name();
					if (nodeName == "Name")
					{
						char *buf = (char*)(itEntry->as_string().c_str());
						playlistEntry->name = new CSlrString(buf);
						LOGD("                        Name = %s", buf);
					}
					else if (nodeName == "Path")
					{
						char *buf = (char*)(itEntry->as_string().c_str());
						playlistEntry->path = new CSlrString(buf);
						LOGD("                        Path = %s", buf);
					}
					else if (nodeName == "Reset")
					{
						char *buf = (char*)(itEntry->as_string().c_str());
						if (!strcmp(buf, "hard"))
						{
							playlistEntry->resetMode = MACHINE_RESET_HARD;
						}
						else if (!strcmp(buf, "soft"))
						{
							playlistEntry->resetMode = MACHINE_RESET_SOFT;
						}
						LOGD("                       Reset = %d", playlistEntry->resetMode);
					}
					else if (nodeName == "AutoRun")
					{
						playlistEntry->autoRun = itEntry->as_bool();
						LOGD("                     AutoRun = %s", STRBOOL(playlistEntry->autoRun));
					}
					else if (nodeName == "RunFile")
					{
						playlistEntry->runFileNum = itEntry->as_int();
						LOGD("                     RunFile = %d", playlistEntry->runFileNum);
					}
					else if (nodeName == "WaitTime")
					{
						playlistEntry->waitTime = itEntry->as_float();
						LOGD("                    WaitTime = %f", playlistEntry->waitTime);
					}
					else if (nodeName == "WaitAfterResetTime")
					{
						playlistEntry->waitAfterResetTime = itEntry->as_float() * 1000.0f;
						LOGD("          WaitAfterResetTime = %fms", playlistEntry->waitAfterResetTime);
					}
					else if (nodeName == "FadeInTime")
					{
						playlistEntry->fadeInTime = itEntry->as_float();
						LOGD("                   FadeInTime = %f", playlistEntry->fadeInTime);
					}
					else if (nodeName == "FadeOutTime")
					{
						playlistEntry->fadeOutTime = itEntry->as_float();
						LOGD("                  FadeOutTime = %f", playlistEntry->fadeOutTime);
					}
					else if (nodeName == "Actions")
					{
						if (itEntry->type() != JSON_ARRAY)
							SYS_FatalExit("Parsing Jukebox JSON: actions is not array");
						
						JSONNode actions = *itEntry;
						JSONNode::iterator itActions = actions.begin();
						
						u32 i = 0;
						while(itActions != actions.end())
						{
							LOGD("..... action #%d", i++);
							if (itActions->type() != JSON_NODE)
								SYS_FatalExit("Parsing Jukebox JSON: actions is not node");
							
							
							CJukeboxPlaylistAction *playlistAction = new CJukeboxPlaylistAction();
							playlistEntry->actions.push_back(playlistAction);
							
							JSONNode action = *itActions;
							JSONNode::iterator itAction = action.begin();
							
							while(itAction != action.end())
							{
								nodeName = itAction->name();
								LOGD("action node='%s'", nodeName.c_str());
								
								if (nodeName == "AfterTime")
								{
									playlistAction->afterTime = itAction->as_float();
									LOGD("  action afterTime=%f", playlistAction->afterTime);
								}
								else if (nodeName == "KeyDown")
								{
									playlistAction->actionType = JUKEBOX_ACTION_KEY_DOWN;
									char *buf = (char*)(itAction->as_string().c_str());
									if (strlen(buf) < 1)
									{
										SYS_FatalExit("Parsing Jukebox JSON: KeyDown action empty");
									}
									playlistAction->code = buf[0];
									LOGD("  action keyDown=%x", playlistAction->code);
								}
								else if (nodeName == "KeyUp")
								{
									playlistAction->actionType = JUKEBOX_ACTION_KEY_UP;
									char *buf = (char*)(itAction->as_string().c_str());
									if (strlen(buf) < 1)
									{
										SYS_FatalExit("Parsing Jukebox JSON: KeyDown action empty");
									}
									playlistAction->code = buf[0];
									LOGD("  action keyUp=%x", playlistAction->code);
								}
								else if (nodeName == "KeyDownCode")
								{
									playlistAction->actionType = JUKEBOX_ACTION_KEY_DOWN;
									playlistAction->code = itAction->as_int();
									LOGD("  action KeyDownCode=%x", playlistAction->code);
								}
								else if (nodeName == "KeyUpCode")
								{
									playlistAction->actionType = JUKEBOX_ACTION_KEY_UP;
									playlistAction->code = itAction->as_int();
									LOGD("  action keyUpCode=%x", playlistAction->code);
								}
								else if (nodeName == "Joystick1Down" || nodeName == "Joystick1Up" ||
										 nodeName == "Joystick2Down" || nodeName == "Joystick2Up")
								{
									if (nodeName == "Joystick1Down")
									{
										playlistAction->actionType = JUKEBOX_ACTION_JOYSTICK1_DOWN;
									}
									else if (nodeName == "Joystick1Up")
									{
										playlistAction->actionType = JUKEBOX_ACTION_JOYSTICK1_UP;
									}
									else if (nodeName == "Joystick2Down")
									{
										playlistAction->actionType = JUKEBOX_ACTION_JOYSTICK2_DOWN;
									}
									else if (nodeName == "Joystick2Up")
									{
										playlistAction->actionType = JUKEBOX_ACTION_JOYSTICK2_UP;
									}
									
									std::string joyAxis = itAction->as_string();

									if (joyAxis == "fire" || joyAxis == "f")
									{
										playlistAction->code = JOYPAD_FIRE;
									}
									else if (joyAxis == "up" || joyAxis == "n" || joyAxis == "north")
									{
										playlistAction->code = JOYPAD_N;
									}
									else if (joyAxis == "down" || joyAxis == "s" || joyAxis == "south")
									{
										playlistAction->code = JOYPAD_S;
									}
									else if (joyAxis == "left" || joyAxis == "e" || joyAxis == "east")
									{
										playlistAction->code = JOYPAD_E;
									}
									else if (joyAxis == "right" || joyAxis == "w" || joyAxis == "west")
									{
										playlistAction->code = JOYPAD_W;
									}
									else if (joyAxis == "sw" || joyAxis == "southwest")
									{
										playlistAction->code = JOYPAD_SW;
									}
									else if (joyAxis == "nw" || joyAxis == "northwest")
									{
										playlistAction->code = JOYPAD_NW;
									}
									else if (joyAxis == "se" || joyAxis == "southeast")
									{
										playlistAction->code = JOYPAD_SE;
									}
									else if (joyAxis == "sw" || joyAxis == "southwest")
									{
										playlistAction->code = JOYPAD_SW;
									}
									
									LOGD("  action joystick=%d %x", playlistAction->actionType, playlistAction->code);
								}
								else if (nodeName == "Warp")
								{
									playlistAction->actionType = JUKEBOX_ACTION_SET_WARP;
									playlistAction->code = (itAction->as_bool() ? 1 : 0);
									
									if (playlistAction->afterTime < 0.01f)
									{
										playlistAction->afterTime = 0.01f;
									}
									LOGD("  action warp=%d", playlistAction->code);
								}
								else if (nodeName == "DumpC64Memory")
								{
									playlistAction->actionType = JUKEBOX_ACTION_DUMP_C64_MEMORY;
									char *buf = (char*)(itAction->as_string().c_str());
									playlistAction->text = new CSlrString(buf);
								}
								else if (nodeName == "DumpDiskMemory")
								{
									playlistAction->actionType = JUKEBOX_ACTION_DUMP_DISK_MEMORY;
									char *buf = (char*)(itAction->as_string().c_str());
									playlistAction->text = new CSlrString(buf);
								}
								else if (nodeName == "DetachCartridge")
								{
									playlistAction->actionType = JUKEBOX_ACTION_DETACH_CARTRIDGE;
								}
								
								itAction++;
							}
							
							itActions++;
						}
					}
					
					itEntry++;
				}
				
				itEntries++;
			}
		}
		
		it++;
	}

	this->DebugPrint();
	LOGD("CJukeboxPlaylist::InitFromJSON: done");
}

CJukeboxPlaylistEntry::CJukeboxPlaylistEntry()
{
	name = NULL;
	path = NULL;
	
	autoRun = false;
	runFileNum = 0;
	resetMode = MACHINE_RESET_NONE;
	
	waitTime = -1;
	fadeInTime = -1;
	fadeOutTime = -1;
	
	fadeColorR = 0.0f;
	fadeColorG = 0.0f;
	fadeColorB = 0.0f;
	
	waitAfterResetTime = -1;
}

CJukeboxPlaylistEntry::~CJukeboxPlaylistEntry()
{
	while (!this->actions.empty())
	{
		CJukeboxPlaylistAction *action = this->actions.back();
		this->actions.pop_back();
		delete action;
	}
}

void CJukeboxPlaylist::DebugPrint()
{
	LOGD("===== CJukeboxPlaylist::DebugPrint (%d entries) =====", entries.size());
	
	int e = 1;
	for (std::vector<CJukeboxPlaylistEntry *>::iterator it = entries.begin(); it != entries.end(); it++)
	{
		LOGD(">> Entry #%d:", e++);
		CJukeboxPlaylistEntry *entry = *it;
		entry->DebugPrint();
	}
	
	LOGD("== CJukeboxPlaylist::DebugPrint done ===");
}

void CJukeboxPlaylistEntry::DebugPrint()
{
	if (name != NULL)
	{
		name->DebugPrint("         Name=");
	}
	else
	{
		LOGD("         Name NULL");
	}

	if (path != NULL)
	{
		path->DebugPrint("         Path=");
	}
	else
	{
		LOGD("         Path NULL");
	}
	
	LOGD("      AutoRun=%s", STRBOOL(autoRun));
	LOGD("      RunFile=%d", runFileNum);
	LOGD("        Reset=%d", resetMode);
	LOGD("     WaitTime=%-8.2f", waitTime);
	LOGD("  FadeOutTime=%-8.2f", fadeOutTime);
	
	LOGD("      Actions=%d", this->actions.size());
	int e = 1;
	for (std::vector<CJukeboxPlaylistAction *>::iterator it = actions.begin(); it != actions.end(); it++)
	{
		LOGD("      ]] Action #%d:", e++);
		CJukeboxPlaylistAction *action = *it;
		action->DebugPrint();
	}
}

CJukeboxPlaylistAction::CJukeboxPlaylistAction()
{
	afterTime = -1;
	actionType = JUKEBOX_ACTION_NONE;
	code = -1;
	text = NULL;
}

CJukeboxPlaylistAction::~CJukeboxPlaylistAction()
{
	if (text != NULL)
		delete text;
}

void CJukeboxPlaylistAction::DebugPrint()
{
	LOGD("         ActionType=%d", actionType);
	LOGD("          AfterTime=%-8.2f", afterTime);
	LOGD("               Code=0x%x", code);
}
