extern "C" {
#include "sid.h"
}

#include "CViewSIDPianoKeyboard.h"
#include "C64Tools.h"
#include "C64SIDFrequencies.h"
#include "CViewC64.h"
#include "CViewC64StateSID.h"
#include "CViewSIDTrackerHistory.h"
#include "C64DebugInterface.h"
#include "SYS_KeyCodes.h"

CSIDPianoKeyboard::CSIDPianoKeyboard(float posX, float posY, float posZ, float sizeX, float sizeY, CPianoKeyboardCallback *callback)
: CPianoKeyboard(posX, posY, posZ, sizeX, sizeY, callback)
{
	this->name = "CSIDPianoKeyboard";
	for (int sidNum = 0; sidNum < 3; sidNum++)
	{
		for (int chanNum = 0; chanNum < 3; chanNum++)
		{
			prevFreq[sidNum][chanNum] = 0;
		}
	}
}

void CSIDPianoKeyboard::DoLogic()
{
	CPianoKeyboard::DoLogic();
}

void CSIDPianoKeyboard::Render()
{
	// refresh keys
	int numSids = viewC64->debugInterfaceC64->GetNumSids();
	
	for (int sidNum = 0; sidNum < numSids; sidNum++)
	{
		if (this->doKeysFadeOut == false)
		{
			for (int i = 0; i < pianoKeys.size(); i++)
			{
				CPianoKey *key = pianoKeys[i];
				if (!key->isBlackKey)
				{
					key->cr = key->cg = key->cb = 1.0f;
				}
				else
				{
					key->cr = key->cg = key->cb = 0.0f;
				}
			}
		}
		
		uint16 sidBase = GetSidAddressByChipNum(sidNum);
		
		for (int chanNum = 0; chanNum < 3; chanNum++)
		{
			// check if channel is not muted
			if (viewC64->viewC64StateSID->sidChannelWaveform[sidNum][chanNum]->isMuted)
				continue;
			
			u16 voiceBase = sidBase + chanNum * 0x07;
			
			u8 loFreq = sid_peek(voiceBase + 0x00);
			u8 hiFreq = sid_peek(voiceBase + 0x01);
			u16 freq = (hiFreq << 8) | loFreq;
			
			bool noteOn = false;
			
			if (this->doKeysFadeOut == true)
			{
				// update also on note changes
				if (freq != prevFreq[sidNum][chanNum])
				{
					noteOn = true;
					prevFreq[sidNum][chanNum] = freq;
				}
				
				u8 ctrl = sid_peek(voiceBase + 4);
				if ((ctrl & 0x01) == 0x01)
				{
					noteOn = true;
				}
			}
			else
			{
				noteOn = true;
			}
			
			if (noteOn)
			{
				const sid_frequency_t *sidFrequencyData = SidFrequencyToNote(freq);
				
				if (sidFrequencyData->note >= 0 && sidFrequencyData->note < 96)
				{
					CPianoKey *key = pianoKeys[sidFrequencyData->note];
					
					// TODO: how to do mixing?
					if (chanNum == 0)
					{
						key->cr = 1.0f;
						key->cg = 0.0;
						key->cb = 0.0;
					}
					else if (chanNum == 1)
					{
						key->cr = 0.0f;
						key->cg = 1.0;
						key->cb = 0.0;
					}
					else if (chanNum == 2)
					{
						if (key->isBlackKey)
						{
							key->cr = 0.2f;
							key->cg = 0.2;
							key->cb = 1.0;
						}
						else
						{
							key->cr = 0.0f;
							key->cg = 0.0;
							key->cb = 1.0;
						}
					}
				}
			}
		}
	}

	CPianoKeyboard::Render();
}

bool CSIDPianoKeyboard::KeyDown(u32 keyCode, bool isShift, bool isAlt, bool isControl)
{
	LOGD("CSIDPianoKeyboard::KeyDown: keyCode=%d", keyCode);
	if (keyCode == MTKEY_SPACEBAR || keyCode == MTKEY_ARROW_UP || keyCode == MTKEY_ARROW_DOWN
		|| keyCode == MTKEY_PAGE_UP || keyCode == MTKEY_PAGE_DOWN)
		
	{
		return viewC64->viewC64AllSids->viewTrackerHistory->KeyDown(keyCode, isShift, isAlt, isControl);
	}
	
	if (this->HasFocus()
		|| viewC64->viewC64AllSids->viewTrackerHistory->HasFocus())
	{
		return CPianoKeyboard::KeyDown(keyCode, isShift, isAlt, isControl);
	}
	
	return false;
}

bool CSIDPianoKeyboard::KeyUp(u32 keyCode, bool isShift, bool isAlt, bool isControl)
{
	if (this->HasFocus()
		|| viewC64->viewC64AllSids->viewTrackerHistory->HasFocus())
	{
		return CPianoKeyboard::KeyUp(keyCode, isShift, isAlt, isControl);
	}
	
	return false;
}
