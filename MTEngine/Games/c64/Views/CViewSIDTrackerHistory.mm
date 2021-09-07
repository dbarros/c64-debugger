extern "C" {
#include "sid.h"
}
#include "CViewSIDTrackerHistory.h"
#include "C64Tools.h"
#include "C64SIDFrequencies.h"
#include "C64DebugInterfaceVice.h"
#include "CViewC64.h"
#include "C64SIDFrequencies.h"
#include "CGuiMain.h"
#include "SND_Main.h"
#include "SYS_KeyCodes.h"

// TODO: load tracker font from MG Tracker

CViewSIDTrackerHistory::CViewSIDTrackerHistory(float posX, float posY, float posZ, float sizeX, float sizeY, C64DebugInterfaceVice *debugInterface)
: CGuiView(posX, posY, posZ, sizeX, sizeY)
{
	this->name = "CViewSIDTrackerHistory";
	
	this->debugInterface = debugInterface;
	
	this->selectedNumSteps = 1;
	this->fScrollPosition = 0;
	this->scrollPosition = 0;
	
	// this value is calculated automatically
	this->numVisibleTrackLines = 1;
	
	fontSize = 5;
	
	CSlrFont *fontButton = viewC64->fontCBMShifted;
	float fontScale = 0.8;
	float fontHeight = fontButton->GetCharHeight('@', fontScale) + 2;
	
	float psx = posX + fontSize * 65;
	float psy = posY;
	float px = psx;
	float py = psy;
	
	float buttonSizeX = 19.0f;
	float buttonSizeY = 7.5f;
	float textButtonOffsetY = buttonSizeY/2.0f - fontHeight/4.0f;
	float gapX = 1.0f;
	float gapY = 0.5f;

	btnFade = new CGuiButtonSwitch(NULL, NULL, NULL,
									px, py, posZ, buttonSizeX, buttonSizeY,
									new CSlrString("FADE"),
									FONT_ALIGN_CENTER, buttonSizeX/2, textButtonOffsetY,
									fontButton, fontScale,
									1.0, 1.0, 1.0, 1.0,
									1.0, 1.0, 1.0, 1.0,
									0.3, 0.3, 0.3, 1.0,
									this);
	btnFade->SetOn(true);
	this->AddGuiElement(btnFade);
	
	py += buttonSizeY + gapY;

	btnScrub = new CGuiButtonSwitch(NULL, NULL, NULL,
								   px, py, posZ, buttonSizeX, buttonSizeY,
								   new CSlrString("SCRUB"),
								   FONT_ALIGN_CENTER, buttonSizeX/2, textButtonOffsetY,
								   fontButton, fontScale,
								   1.0, 1.0, 1.0, 1.0,
								   1.0, 1.0, 1.0, 1.0,
								   0.3, 0.3, 0.3, 1.0,
								   this);
	btnScrub->SetOn(true);
	this->AddGuiElement(btnScrub);

	//
	px = psx;
	py = psy + 17;
	gapY = 5.0f;
	buttonSizeY = 8.0f;
	lblStep = new CGuiLabel("STEPS", false, px, py, posZ, buttonSizeX, fontSize, LABEL_ALIGNED_LEFT, fontSize, fontSize, NULL);
	this->AddGuiElement(lblStep);

	py += fontSize;
	
	buttonSizeX = 14;
	btnStep1 = new CGuiButtonSwitch(NULL, NULL, NULL,
										  px, py, posZ, buttonSizeX, buttonSizeY,
										  new CSlrString("1"),
										  FONT_ALIGN_CENTER, buttonSizeX/2, textButtonOffsetY,
										  fontButton, fontScale,
										  1.0, 1.0, 1.0, 1.0,
										  1.0, 1.0, 1.0, 1.0,
										  0.3, 0.3, 0.3, 1.0,
										  this);
	btnStep1->SetOn(true);
	this->AddGuiElement(btnStep1);
	btnsStepSwitches.push_back(btnStep1);

	px += buttonSizeX + gapX;

	btnStep2 = new CGuiButtonSwitch(NULL, NULL, NULL,
									px, py, posZ, buttonSizeX, buttonSizeY,
									new CSlrString("2"),
									FONT_ALIGN_CENTER, buttonSizeX/2, textButtonOffsetY,
									fontButton, fontScale,
									1.0, 1.0, 1.0, 1.0,
									1.0, 1.0, 1.0, 1.0,
									0.3, 0.3, 0.3, 1.0,
									this);
	this->AddGuiElement(btnStep2);
	btnsStepSwitches.push_back(btnStep2);

	px += buttonSizeX + gapX;
	
	btnStep3 = new CGuiButtonSwitch(NULL, NULL, NULL,
									px, py, posZ, buttonSizeX, buttonSizeY,
									new CSlrString("3"),
									FONT_ALIGN_CENTER, buttonSizeX/2, textButtonOffsetY,
									fontButton, fontScale,
									1.0, 1.0, 1.0, 1.0,
									1.0, 1.0, 1.0, 1.0,
									0.3, 0.3, 0.3, 1.0,
									this);
	this->AddGuiElement(btnStep3);
	btnsStepSwitches.push_back(btnStep3);

	px += buttonSizeX + gapX;
	
	btnStep4 = new CGuiButtonSwitch(NULL, NULL, NULL,
									px, py, posZ, buttonSizeX, buttonSizeY,
									new CSlrString("4"),
									FONT_ALIGN_CENTER, buttonSizeX/2, textButtonOffsetY,
									fontButton, fontScale,
									1.0, 1.0, 1.0, 1.0,
									1.0, 1.0, 1.0, 1.0,
									0.3, 0.3, 0.3, 1.0,
									this);
	this->AddGuiElement(btnStep4);
	btnsStepSwitches.push_back(btnStep4);

	px += buttonSizeX + gapX;

	btnStep5 = new CGuiButtonSwitch(NULL, NULL, NULL,
									px, py, posZ, buttonSizeX, buttonSizeY,
									new CSlrString("5"),
									FONT_ALIGN_CENTER, buttonSizeX/2, textButtonOffsetY,
									fontButton, fontScale,
									1.0, 1.0, 1.0, 1.0,
									1.0, 1.0, 1.0, 1.0,
									0.3, 0.3, 0.3, 1.0,
									this);
	this->AddGuiElement(btnStep5);
	btnsStepSwitches.push_back(btnStep5);

	px += buttonSizeX + gapX;
	
	btnStep6 = new CGuiButtonSwitch(NULL, NULL, NULL,
									px, py, posZ, buttonSizeX, buttonSizeY,
									new CSlrString("6"),
									FONT_ALIGN_CENTER, buttonSizeX/2, textButtonOffsetY,
									fontButton, fontScale,
									1.0, 1.0, 1.0, 1.0,
									1.0, 1.0, 1.0, 1.0,
									0.3, 0.3, 0.3, 1.0,
									this);
	this->AddGuiElement(btnStep6);
	btnsStepSwitches.push_back(btnStep6);
	
	px += buttonSizeX + gapX;

	btnStep8 = new CGuiButtonSwitch(NULL, NULL, NULL,
									px, py, posZ, buttonSizeX, buttonSizeY,
									new CSlrString("8"),
									FONT_ALIGN_CENTER, buttonSizeX/2, textButtonOffsetY,
									fontButton, fontScale,
									1.0, 1.0, 1.0, 1.0,
									1.0, 1.0, 1.0, 1.0,
									0.3, 0.3, 0.3, 1.0,
									this);
	this->AddGuiElement(btnStep8);
	btnsStepSwitches.push_back(btnStep8);

	py += buttonSizeY + gapY;
	px = psx;
	gapY = 1.0f;
	
	lblMidiIn = new CGuiLabel("KEY IN", false, px, py, posZ, buttonSizeX, fontSize, LABEL_ALIGNED_LEFT, fontSize, fontSize, NULL);
	this->AddGuiElement(lblMidiIn);

	py -= 1.0f;
	px += fontSize * 6.5f;

	btnJazz = new CGuiButtonSwitch(NULL, NULL, NULL,
									px, py, posZ, buttonSizeX, buttonSizeY,
									new CSlrString("JAZZ"),
									FONT_ALIGN_CENTER, buttonSizeX/2, textButtonOffsetY,
									fontButton, fontScale,
									1.0, 1.0, 1.0, 1.0,
									1.0, 1.0, 1.0, 1.0,
									0.3, 0.3, 0.3, 1.0,
									this);
	btnJazz->SetOn(false);
	this->AddGuiElement(btnJazz);
	
	py += 1.0f;
	
	px = psx;
	py += fontSize + gapY;

	float lstFontSize = fontSize;
	float listWidth = lstFontSize*19;
	float listHeight = lstFontSize*9;

	this->lstMidiIn = new CGuiLockableList(px, py, posZ+0.01, listWidth, listHeight, lstFontSize,
										NULL, 0, false,
										guiMain->fntConsole,
										guiMain->theme->imgBackground, 1.0f,
										this);
	this->lstMidiIn->name = "CViewSIDTrackerHistory::lstMidiIn";
	this->lstMidiIn->SetGaps(0.0f, -0.25f);
	this->lstMidiIn->drawFocusBorder = false;
	this->lstMidiIn->allowFocus = false;
	this->AddGuiElement(this->lstMidiIn);

	py += listHeight;
	
	/*

	lblMidiOut = new CGuiLabel("MIDI OUT", false, px, py, posZ, buttonSizeX, fontSize, LABEL_ALIGNED_LEFT, fontSize, fontSize, NULL);
	this->AddGuiElement(lblMidiOut);

	py += fontSize + gapY;
	this->lstMidiOut = new CGuiLockableList(px, py, posZ+0.01, listWidth, listHeight, lstFontSize,
								   NULL, 0, false,
								   guiMain->fntConsole,
								   guiMain->theme->imgBackground, 1.0f,
								   this);
	this->lstMidiOut->name = "CViewSIDTrackerHistory::lstMidiOut";
	this->lstMidiOut->SetGaps(0.0f, -0.25f);
	this->lstMidiOut->drawFocusBorder = false;
	this->lstMidiOut->allowFocus = false;
	this->AddGuiElement(this->lstMidiOut);
	 */
	
	txtSidChannels = NULL;
	UpdateMidiListSidChannels();
	
	///
	
	bool showTrackerButtons = true;
	if (showTrackerButtons)
	{
		buttonSizeX = 18.6f;
		px = 320;
		py = psy + 137.6;
		
		btnShowNotes = new CGuiButtonSwitch(NULL, NULL, NULL,
									   px, py, posZ, buttonSizeX, buttonSizeY,
									   new CSlrString("NOTES"),
									   FONT_ALIGN_CENTER, buttonSizeX/2, textButtonOffsetY,
									   fontButton, fontScale,
									   1.0, 1.0, 1.0, 1.0,
									   1.0, 1.0, 1.0, 1.0,
									   0.3, 0.3, 0.3, 1.0,
									   this);
		btnShowNotes->SetOn(true);
		this->AddGuiElement(btnShowNotes);

		px += buttonSizeX;

		btnShowInstruments = new CGuiButtonSwitch(NULL, NULL, NULL,
											px, py, posZ, buttonSizeX, buttonSizeY,
											new CSlrString("WAVE"),
											FONT_ALIGN_CENTER, buttonSizeX/2, textButtonOffsetY,
											fontButton, fontScale,
											1.0, 1.0, 1.0, 1.0,
											1.0, 1.0, 1.0, 1.0,
											0.3, 0.3, 0.3, 1.0,
											this);
		btnShowInstruments->SetOn(true);
		this->AddGuiElement(btnShowInstruments);
		
		px += buttonSizeX;

		btnShowPWM = new CGuiButtonSwitch(NULL, NULL, NULL,
												  px, py, posZ, buttonSizeX, buttonSizeY,
												  new CSlrString("PWM"),
												  FONT_ALIGN_CENTER, buttonSizeX/2, textButtonOffsetY,
												  fontButton, fontScale,
												  1.0, 1.0, 1.0, 1.0,
												  1.0, 1.0, 1.0, 1.0,
												  0.3, 0.3, 0.3, 1.0,
												  this);
		btnShowPWM->SetOn(true);
		this->AddGuiElement(btnShowPWM);
		
		px += buttonSizeX;

		btnShowAdsr = new CGuiButtonSwitch(NULL, NULL, NULL,
										  px, py, posZ, buttonSizeX, buttonSizeY,
										  new CSlrString("ADSR"),
										  FONT_ALIGN_CENTER, buttonSizeX/2, textButtonOffsetY,
										  fontButton, fontScale,
										  1.0, 1.0, 1.0, 1.0,
										  1.0, 1.0, 1.0, 1.0,
										  0.3, 0.3, 0.3, 1.0,
										  this);
		btnShowAdsr->SetOn(true);
		this->AddGuiElement(btnShowAdsr);
		
		px += buttonSizeX;

		btnShowFilterCutoff = new CGuiButtonSwitch(NULL, NULL, NULL,
										   px, py, posZ, buttonSizeX, buttonSizeY,
										   new CSlrString("CUTOFF"),
										   FONT_ALIGN_CENTER, buttonSizeX/2, textButtonOffsetY,
										   fontButton, fontScale,
										   1.0, 1.0, 1.0, 1.0,
										   1.0, 1.0, 1.0, 1.0,
										   0.3, 0.3, 0.3, 1.0,
										   this);
		btnShowFilterCutoff->SetOn(true);
		this->AddGuiElement(btnShowFilterCutoff);
		
		px += buttonSizeX;

		btnShowFilterCtrl = new CGuiButtonSwitch(NULL, NULL, NULL,
												   px, py, posZ, buttonSizeX, buttonSizeY,
												   new CSlrString("FILT"),
												   FONT_ALIGN_CENTER, buttonSizeX/2, textButtonOffsetY,
												   fontButton, fontScale,
												   1.0, 1.0, 1.0, 1.0,
												   1.0, 1.0, 1.0, 1.0,
												   0.3, 0.3, 0.3, 1.0,
												   this);
		btnShowFilterCtrl->SetOn(true);
		this->AddGuiElement(btnShowFilterCtrl);
		
		px += buttonSizeX;

		btnShowVolume = new CGuiButtonSwitch(NULL, NULL, NULL,
												 px, py, posZ, buttonSizeX, buttonSizeY,
												 new CSlrString("VOLUME"),
												 FONT_ALIGN_CENTER, buttonSizeX/2, textButtonOffsetY,
												 fontButton, fontScale,
												 1.0, 1.0, 1.0, 1.0,
												 1.0, 1.0, 1.0, 1.0,
												 0.3, 0.3, 0.3, 1.0,
												 this);
		btnShowVolume->SetOn(true);
		this->AddGuiElement(btnShowVolume);
		
		px += buttonSizeX;
	 }

	
}

void CViewSIDTrackerHistory::UpdateMidiListSidChannels()
{
	guiMain->LockMutex();

	// TODO: when number of SIDs changes we need to rebuild the list
	int numSids = debugInterface->numSids;
	
	if (txtSidChannels != NULL)
	{
		for (int i = 0; i < numSids * 3; i++)
		{
			delete [] txtSidChannels[i];
		}
		delete txtSidChannels;
	}
	
	txtSidChannels = new char *[numSids * 3];

	int i = 0;
	for (int sidNum = 0; sidNum < numSids; sidNum++)
	{
		for (int chanNum = 0; chanNum < 3; chanNum++)
		{
			char *txtChan = new char[40];
			
			if (numSids == 1)
			{
				sprintf(txtChan, "CHANNEL #%d", chanNum+1);
			}
			else
			{
				sprintf(txtChan, "SID %d CHANNEL #%d", sidNum+1, chanNum+1);
			}
			
			txtSidChannels[i] = txtChan;
			i++;
		}
	}

	this->lstMidiIn->Init(txtSidChannels, numSids * 3, false);
//	this->lstMidiOut->Init(txtSidChannels, numSids * 3, false);
	
	this->lstMidiIn->SetElement(0, false, false);
//	this->lstMidiOut->SetElement(0, false, false);

	guiMain->UnlockMutex();
}

bool CViewSIDTrackerHistory::DoTap(GLfloat x, GLfloat y)
{	
	return CGuiView::DoTap(x, y);
}

void CViewSIDTrackerHistory::SetSidWithCurrentPositionData()
{
	gSoundEngine->LockMutex("CViewSIDTrackerHistory::SetSidWithCurrentPositionData");
	debugInterface->mutexSidDataHistory->Lock();

	std::list<CSidData *>::iterator it = debugInterface->sidDataHistory.begin();
	int sy = scrollPosition;
	std::advance(it, sy);
	
	CSidData *pSidDataCurrent  = *it;
	debugInterface->SetSid(pSidDataCurrent);
	
	debugInterface->mutexSidDataHistory->Unlock();
	gSoundEngine->UnlockMutex("CViewSIDTrackerHistory::SetSidWithCurrentPositionData");
}

void CViewSIDTrackerHistory::PianoKeyboardNotePressed(CPianoKeyboard *pianoKeyboard, u8 note)
{
	LOGD("CViewSIDTrackerHistory::PianoKeyboardNotePressed: note=%d", note);
	// TODO: SID SELECT
	
	int sidNum = 0;
	
	if (lstMidiIn->selectedElement < 0)
		return;
	
	int chanNum = lstMidiIn->selectedElement;

	debugInterface->mutexSidDataHistory->Lock();
	
	std::list<CSidData *>::iterator it = debugInterface->sidDataHistory.begin();
	int sy = scrollPosition;
	std::advance(it, sy);
	
	CSidData *pSidDataCurrent  = *it;

	const sid_frequency_t *sidFrequencyData = SidNoteToFrequency(note);
	
	int o = chanNum * 0x07;
	pSidDataCurrent->sidData[sidNum][o + 1] = (sidFrequencyData->sidValue & 0xFF00) >> 8;
	pSidDataCurrent->sidData[sidNum][o    ] = (sidFrequencyData->sidValue & 0x00FF);

	// gate on
	pSidDataCurrent->sidData[sidNum][o + 4] = pSidDataCurrent->sidData[sidNum][o + 4] | 0x01;

	debugInterface->SetSid(pSidDataCurrent);

	if (btnJazz->IsOn())
	{
		chanNum++;
		if (chanNum == 3)
			chanNum = 0;
		
		lstMidiIn->SetElement(chanNum, false, false);
	}
	
	debugInterface->mutexSidDataHistory->Unlock();
}

// store new SidData in history at current position
void CViewSIDTrackerHistory::UpdateHistoryWithCurrentSidData()
{
	int sidNum = 0;
	
	debugInterface->mutexSidDataHistory->Lock();
	
	std::list<CSidData *>::iterator it = debugInterface->sidDataHistory.begin();
	int sy = scrollPosition;
	std::advance(it, sy);
	
	CSidData *pSidDataCurrent  = *it;

	// update with current SID state
	pSidDataCurrent->PeekFromSids();

	debugInterface->mutexSidDataHistory->Unlock();
}

void CViewSIDTrackerHistory::PianoKeyboardNoteReleased(CPianoKeyboard *pianoKeyboard, u8 note)
{
	LOGD("CViewSIDTrackerHistory::PianoKeyboardNoteReleased: note=%d", note);
	if (lstMidiIn->selectedElement < 0)
		return;
	
	debugInterface->mutexSidDataHistory->Lock();
	
	std::list<CSidData *>::iterator it = debugInterface->sidDataHistory.begin();
	int sy = scrollPosition;
	std::advance(it, sy);
	
	CSidData *pSidDataCurrent  = *it;
	
	const sid_frequency_t *sidFrequencyData = SidNoteToFrequency(note);
	
	if (btnJazz->IsOn())
	{
		for (int sidNum = 0; sidNum < debugInterface->numSids; sidNum++)
		{
			for (int chanNum = 0; chanNum < 3; chanNum++)
			{
				int o = chanNum * 0x07;
				if (	(pSidDataCurrent->sidData[sidNum][o + 1] = (sidFrequencyData->sidValue & 0xFF00) >> 8)
					&&	(pSidDataCurrent->sidData[sidNum][o    ] = (sidFrequencyData->sidValue & 0x00FF))
					&& ((pSidDataCurrent->sidData[sidNum][o + 4] & 0x01) == 0x01))
				{
					// found frequency, gate off
					pSidDataCurrent->sidData[sidNum][o + 4] = pSidDataCurrent->sidData[sidNum][o + 4] & 0xFE;
					
					debugInterface->SetSid(pSidDataCurrent);
					break;
				}
			}
		}
	}
	else
	{
		int sidNum = 0; /// TODO: FIX ME
		int chanNum = lstMidiIn->selectedElement;
		int o = chanNum * 0x07;
		pSidDataCurrent->sidData[sidNum][o + 4] = pSidDataCurrent->sidData[sidNum][o + 4] & 0xFE;
		debugInterface->SetSid(pSidDataCurrent);
	}
	
	debugInterface->mutexSidDataHistory->Unlock();
}


bool CViewSIDTrackerHistory::DoScrollWheel(float deltaX, float deltaY)
{
	LOGD("CViewSIDTrackerHistory::DoScrollWheel: deltaY=%f", deltaY);
	
	MoveTracksY(deltaY);
	return true;
}

bool CViewSIDTrackerHistory::DoMove(GLfloat x, GLfloat y, GLfloat distX, GLfloat distY, GLfloat diffX, GLfloat diffY)
{
//	LOGD("CViewSIDTrackerHistory::DoMove: diffY=%f", diffY);
	
	MoveTracksY(diffY/4.0f);
	return true;
}

// this is a callback from debug interface:
// when music plays we would like to keep the position, so we need to scroll it automatically up every time new data is fetched
// this is sanitized on render and scroll events
void CViewSIDTrackerHistory::VSyncStepsAdded()
{
	if (scrollPosition > 0)
	{
		scrollPosition += (float)selectedNumSteps;
	}
}

void CViewSIDTrackerHistory::EnsureCorrectScrollPosition()
{
	// when we reach end of buffer, then data will be scrolled, but we would like to see all screen filled with data
	if (scrollPosition >= (int)debugInterface->sidDataHistory.size()-numVisibleTrackLines)
		scrollPosition = (int)debugInterface->sidDataHistory.size()-numVisibleTrackLines-1;
	
	if (scrollPosition < 0)
		scrollPosition = 0;
}

void CViewSIDTrackerHistory::ResetScroll()
{
	SetTracksScrollPos(0);
}

void CViewSIDTrackerHistory::MoveTracksY(float deltaY)
{
	LOGD("MoveTracksY: %f", deltaY);
	fScrollPosition += deltaY;
	float d = floor(fScrollPosition);
	
	fScrollPosition -= d;
	
	int newPos = scrollPosition + (int)d * selectedNumSteps;
	SetTracksScrollPos(newPos);
}

void CViewSIDTrackerHistory::SetTracksScrollPos(int newPos)
{
	guiMain->LockMutex();
	debugInterface->mutexSidDataHistory->Lock();
	
	scrollPosition = newPos;
	
	LOGD("new scrollPosition=%d",  scrollPosition);
	EnsureCorrectScrollPosition();
	
	LOGD("size=%d scrollPosition=%d",  debugInterface->sidDataHistory.size(), scrollPosition);
	
	if (btnScrub->IsOn())
	{
		SetSidWithCurrentPositionData();
	}
	
	debugInterface->mutexSidDataHistory->Unlock();
	guiMain->UnlockMutex();
}

void CViewSIDTrackerHistory::Render()
{
//	LOGD("CViewSIDTrackerHistory");
	float gap = 2.0f;
	
	font = viewC64->fontDisassemble;
	fontSize = 5;
	
	// start rendering
	debugInterface->mutexSidDataHistory->Lock();

	EnsureCorrectScrollPosition();

	float py = posY + sizeY - fontSize + gap;
	float pEndY = posY - fontSize + gap;
	int skip = debugInterface->sidDataHistoryCurrentStep;

	
//		   0         1         2         3         4         5         6
//		   01234567890123456789012345678901234567890123456789012345678901234
//		  "C-5 CT PWPW ADSR  C-5 CT PWPW ADSR  C-5 CT PWPW ADSR  FILT FM VL\0";

//        NOTE: scanning is done backwards in history of SID states
//              we need to keep text buffer filled with spaces first because we scan history and display buffer only every selectedNumSteps step
//              this is to allow to not loose a note when it was played in-between current stepNum=0 and selectedNumSteps,
//              so when we scan and there was a note the text buffer is updated and thus it is kept even though we move back next steps, example:
//
//              ... <- display (stepNum == selectedNumSteps), note the note C-0 will be displayed even though it was in-between displayable steps
//              C-0 <- skip
//              ... <- skip
//              ... <- stepNum == 0
//
//        TODO: when channel is muted show it with darker color
//              to solve this we need different buffers for each channel (i.e. numSids * 3 buffers)
//              remember its pos and then display them when all data is collected. we need to keep buffers because of the note above.

	char *buf = SYS_GetCharBuf();
	
	char e = '.';
	bool checkNotesChange = true;	// check notes change, not freq
	
	int stepNum = 0;
	memset(buf, 0x20, 63);
	
	std::list<CSidData *>::iterator it = debugInterface->sidDataHistory.begin();
	
	int sy = scrollPosition;
//	LOGD("size=%d scrollPosition=%d",  debugInterface->sidDataHistory[sidNum].size(), sy);
	std::advance(it, sy);
	
	int currentLine = 0;
	while (it != debugInterface->sidDataHistory.end())
	{
		std::list<CSidData *>::iterator itPrevious = it;
		itPrevious++;
		
		if (itPrevious == debugInterface->sidDataHistory.end())
			break;
		
		if (skip > 0)
		{
			skip--;
			it++;
			continue;
		}
		
		int pos = 0;
		CSidData *pSidDataCurrent  = *it;
		CSidData *pSidDataPrevious = *itPrevious;

		for (int sidNum = 0; sidNum < debugInterface->numSids; sidNum++)
		{
			u8 *sidDataCurrent = pSidDataCurrent->sidData[sidNum];
			u8 *sidDataPrevious = pSidDataPrevious->sidData[sidNum];

			for (int chanNum = 0; chanNum < 3; chanNum++)
			{
				bool noteDisplayed = false;
				
				u16 chanAddr = chanNum * 0x07;
				
				int notePos = 0;
				u16 freqCurrent  = (sidDataCurrent[chanAddr + 1] << 8)  | sidDataCurrent[chanAddr];
				u16 freqPrevious = (sidDataPrevious[chanAddr + 1] << 8) | sidDataPrevious[chanAddr];
				
				if (btnShowNotes->IsOn())
				{
					notePos = pos;
					if (checkNotesChange == false)
					{
						// mark change on each freq change
						if (freqCurrent == freqPrevious)
						{
							if (stepNum == 0)
							{
								buf[pos] = e; buf[pos+1] = e; buf[pos+2] = e;
							}
						}
						else
						{
							if (buf[pos] == 0x20 || buf[pos] == e)
							{
								const sid_frequency_t *sidFrequencyData = SidFrequencyToNote(freqCurrent);
								
								if (sidFrequencyData->note >= 0 && sidFrequencyData->note < 96)
								{
									buf[pos  ] = sidFrequencyData->name[0];
									buf[pos+1] = sidFrequencyData->name[1];
									buf[pos+2] = sidFrequencyData->name[2];
									noteDisplayed = true;
								}
							}
						}
					}
					else
					{
						// mark change only on note change
						const sid_frequency_t *sidFrequencyDataCurrent  = SidFrequencyToNote(freqCurrent);
						const sid_frequency_t *sidFrequencyDataPrevious = SidFrequencyToNote(freqPrevious);
						
						//				LOGD("py=%-5.0f chan=%d sidDataCurrent=%x sidDataPrevious=%x | freqCurrent=%04x sidFrequencyDataCurrent=%x %s freqPrevious=%04x sidFrequencyDataPrevious=%x %s",
						//					 py, chanNum, sidDataCurrent, sidDataPrevious,
						//					 freqCurrent, sidFrequencyDataCurrent, sidFrequencyDataCurrent->name,
						//					 freqPrevious, sidFrequencyDataPrevious, sidFrequencyDataPrevious->name);
						
						if (sidFrequencyDataCurrent == sidFrequencyDataPrevious)
						{
							if (stepNum == 0)
							{
								buf[pos] = e; buf[pos+1] = e; buf[pos+2] = e;
							}
						}
						else
						{
							if (buf[pos] == 0x20 || buf[pos] == e)
							{
								if (sidFrequencyDataCurrent->note >= 0 && sidFrequencyDataCurrent->note < 96)
								{
									buf[pos  ] = sidFrequencyDataCurrent->name[0];
									buf[pos+1] = sidFrequencyDataCurrent->name[1];
									buf[pos+2] = sidFrequencyDataCurrent->name[2];
									noteDisplayed = true;
								}
							}
						}
					}
					
					pos += 4;
				}
				
				{
					u8 ctrlCurrent  = sidDataCurrent[chanAddr + 4];
					u8 ctrlPrevious = sidDataPrevious[chanAddr + 4];
					
					if (ctrlCurrent == ctrlPrevious)
					{
						if (btnShowInstruments->IsOn())
						{
							if (stepNum == 0)
							{
								buf[pos] = e; buf[pos + 1] = e;
							}
						}
					}
					else
					{
						if (btnShowInstruments->IsOn())
						{
							if (buf[pos] == 0x20 || buf[pos + 1] == e)
							{
								sprintfHexCode8WithoutZeroEnding(buf + pos, ctrlCurrent);
							}
						}
						
						if (btnShowNotes->IsOn())
						{
							if (buf[notePos] == 0x20 || buf[notePos] == e)
							{
								if ((ctrlCurrent & 0x01) == 0x01 && noteDisplayed == false)
								{
									const sid_frequency_t *sidFrequencyData = SidFrequencyToNote(freqCurrent);
									
									if (sidFrequencyData->note >= 0 && sidFrequencyData->note < 96)
									{
										buf[notePos  ] = sidFrequencyData->name[0];
										buf[notePos+1] = sidFrequencyData->name[1];
										buf[notePos+2] = sidFrequencyData->name[2];
										noteDisplayed = true;
									}
								}
							}
							
						}
					}
					
					if (btnShowInstruments->IsOn())
					{
						pos += 3;
					}
				}
				
				if (btnShowPWM->IsOn())
				{
					u16 pwCurrent  = (sidDataCurrent[chanAddr + 3] << 8)  | sidDataCurrent[chanAddr + 2];
					u16 pwPrevious = (sidDataPrevious[chanAddr + 3] << 8) | sidDataPrevious[chanAddr + 2];
					
					if (pwCurrent == pwPrevious)
					{
						if (stepNum == 0)
						{
							buf[pos] = e; buf[pos + 1] = e; buf[pos + 2] = e; buf[pos + 3] = e;
						}
					}
					else
					{
						if (buf[pos] == 0x20 || buf[pos] == e)
						{
							sprintfHexCode16WithoutZeroEnding(buf + pos, pwCurrent);
						}
					}
					
					pos += 5;
				}
				
				if (btnShowAdsr->IsOn())
				{
					u16 adsrCurrent  = (sidDataCurrent[chanAddr + 5] << 8)  | sidDataCurrent[chanAddr + 6];
					u16 adsrPrevious = (sidDataPrevious[chanAddr + 5] << 8) | sidDataPrevious[chanAddr + 6];
					
					if (adsrCurrent == adsrPrevious)
					{
						if (stepNum == 0)
						{
							buf[pos] = e; buf[pos + 1] = e; buf[pos + 2] = e; buf[pos + 3] = e;
						}
					}
					else
					{
						if (buf[pos] == 0x20 || buf[pos + 1] == e)
						{
							sprintfHexCode16WithoutZeroEnding(buf + pos, adsrCurrent);
						}
					}
					pos += 5;
				}
			}
			
			if (btnShowFilterCutoff->IsOn())
			{
				// filt cutoff
				u16 filtCurrent  = (sidDataCurrent[0x15] << 8)  | sidDataCurrent[0x16];
				u16 filtPrevious = (sidDataPrevious[0x15] << 8) | sidDataPrevious[0x16];
				
				if (filtCurrent == filtPrevious)
				{
					if (stepNum == 0)
					{
						buf[pos] = e; buf[pos + 1] = e; buf[pos + 2] = e; buf[pos + 3] = e;
					}
				}
				else
				{
					if (buf[pos] == 0x20 || buf[pos] == e)
					{
						sprintfHexCode16WithoutZeroEnding(buf + pos, filtCurrent);
					}
				}
				
				pos += 5;
			}
			
			if (btnShowFilterCtrl->IsOn())
			{
				// filt control
				u8 filtCtrlCurrent  = sidDataCurrent[0x17];
				u8 filtCtrlPrevious = sidDataPrevious[0x17];
				
				if (filtCtrlCurrent == filtCtrlPrevious)
				{
					if (stepNum == 0)
					{
						buf[pos] = e; buf[pos+1] = e;
					}
				}
				else
				{
					if (buf[pos] == 0x20 || buf[pos] == e)
					{
						sprintfHexCode8WithoutZeroEnding(buf + pos, filtCtrlCurrent);
					}
				}
				
				pos += 3;
			}
			
			if (btnShowVolume->IsOn())
			{
				// volume
				u8 volCurrent  = sidDataCurrent[0x18];
				u8 volPrevious = sidDataPrevious[0x18];
				
				if (volCurrent == volPrevious)
				{
					if (stepNum == 0)
					{
						buf[pos] = e; buf[pos + 1] = e;
					}
				}
				else
				{
					if (buf[pos] == 0x20 || buf[pos + 1] == e)
					{
						sprintfHexCode8WithoutZeroEnding(buf + pos, volCurrent);
					}
				}
				
				pos += 3;
			}
		}
		
		buf[pos] = 0x00;

		stepNum++;
		if (stepNum == selectedNumSteps)
		{
			currentLine++;
			
//	FIIIXME				printf("strlen=%d\n", strlen(buf));
			buf[64] = 0x00;
			font->BlitText(buf, posX, py, -1, fontSize);
			
			py -= fontSize;
			
			if (py <= (pEndY))
				break;

			stepNum = 0;
			memset(buf, 0x20, 63);
		}
		
		it++;
	}
	
	numVisibleTrackLines = currentLine;
	
	debugInterface->mutexSidDataHistory->Unlock();
	
	SYS_ReleaseCharBuf(buf);
	CGuiView::Render();
}

bool CViewSIDTrackerHistory::ButtonClicked(CGuiButton *button)
{
	return false;
}

bool CViewSIDTrackerHistory::ButtonPressed(CGuiButton *button)
{
	LOGD("CViewSIDTrackerHistory::ButtonPressed");
	
	return false;
}

void CViewSIDTrackerHistory::UpdateButtonsGroup(CGuiButtonSwitch *btn)
{
	// TODO: add group of buttons as GuiElement
	for (std::list<CGuiButtonSwitch *>::iterator it = btnsStepSwitches.begin(); it != btnsStepSwitches.end(); it++)
	{
		CGuiButtonSwitch *btn = *it;
		btn->SetOn(false);
	}
	
	btn->SetOn(true);
}

void CViewSIDTrackerHistory::SetNumSteps(int numSteps)
{
	this->selectedNumSteps = numSteps;
	debugInterface->SetSidDataHistorySteps(numSteps);
}

bool CViewSIDTrackerHistory::ButtonSwitchChanged(CGuiButtonSwitch *button)
{
	LOGD("CViewSIDTrackerHistory::ButtonSwitchChanged");
	if (button == btnFade)
	{
		// TODO: ohh, fixme and move to CViewC64AllSIDs
		viewC64->viewC64AllSids->viewPianoKeyboard->SetKeysFadeOut(button->IsOn());
	}
	else if (button == btnStep1)
	{
		UpdateButtonsGroup(button);
		SetNumSteps(1);
	}
	else if (button == btnStep2)
	{
		UpdateButtonsGroup(button);
		SetNumSteps(2);
	}
	else if (button == btnStep3)
	{
		UpdateButtonsGroup(button);
		SetNumSteps(3);
	}
	else if (button == btnStep4)
	{
		UpdateButtonsGroup(button);
		SetNumSteps(4);
	}
	else if (button == btnStep5)
	{
		UpdateButtonsGroup(button);
		SetNumSteps(5);
	}
	else if (button == btnStep6)
	{
		UpdateButtonsGroup(button);
		SetNumSteps(6);
	}
	else if (button == btnStep8)
	{
		UpdateButtonsGroup(button);
		SetNumSteps(8);
	}
	
	return false;
}

// temporary hack
bool CViewSIDTrackerHistory::IsFocusable()
{
	return true;
}

bool CViewSIDTrackerHistory::KeyDown(u32 keyCode, bool isShift, bool isAlt, bool isControl)
{
	if (keyCode == MTKEY_ARROW_UP)
	{
		if (isShift)
		{
			MoveTracksY(16);
		}
		else
		{
			MoveTracksY(1);
		}
		return true;
	}
	if (keyCode == MTKEY_ARROW_DOWN)
	{
		if (isShift)
		{
			MoveTracksY(-16);
		}
		else
		{
			MoveTracksY(-1);
		}
		return true;
	}
	if (keyCode == MTKEY_PAGE_UP)
	{
		MoveTracksY(16);
		return true;
	}
	if (keyCode == MTKEY_PAGE_DOWN)
	{
		MoveTracksY(-16);
		return true;
	}
	if (keyCode == MTKEY_SPACEBAR)
	{
		if (debugInterface->GetDebugMode() == DEBUGGER_MODE_RUNNING)
		{
			debugInterface->SetDebugMode(DEBUGGER_MODE_PAUSED);
			return true;
		}
		if (scrollPosition == 0
			&& debugInterface->GetDebugMode() == DEBUGGER_MODE_PAUSED)
		{
			debugInterface->SetDebugMode(DEBUGGER_MODE_RUNNING);
			return true;
		}
		
		viewC64->viewC64AllSids->viewTrackerHistory->ResetScroll();
		return true;
	}
	
	if (this->HasFocus())
	{
		return viewC64->viewC64AllSids->viewPianoKeyboard->KeyDown(keyCode, isShift, isAlt, isControl);
	}
	return false;
}

bool CViewSIDTrackerHistory::KeyUp(u32 keyCode, bool isShift, bool isAlt, bool isControl)
{
	if (keyCode == MTKEY_ARROW_UP)
	{
		return true;
	}
	if (keyCode == MTKEY_ARROW_DOWN)
	{
		return true;
	}
	if (keyCode == MTKEY_PAGE_UP)
	{
		return true;
	}
	if (keyCode == MTKEY_PAGE_DOWN)
	{
		return true;
	}
	if (keyCode == MTKEY_SPACEBAR)
	{
		return true;
	}
	
	if (this->HasFocus())
	{
		return viewC64->viewC64AllSids->viewPianoKeyboard->KeyUp(keyCode, isShift, isAlt, isControl);
	}
	return false;
}

void CViewSIDTrackerHistory::RenderFocusBorder()
{
	// TODO: fix me, this is because allsids view does not conform protocol
	if (visible && drawFocusBorder && viewC64->viewC64AllSids->IsVisible())
	{
		// TODO: make border offsets as parameters of the generic view
		const float lineWidth = 0.7f;
		BlitRectangle(this->posX, this->posY, this->posZ, this->sizeX, this->sizeY + 5, 1.0f, 0.0f, 0.0f, 0.5f, lineWidth);
	}
}


