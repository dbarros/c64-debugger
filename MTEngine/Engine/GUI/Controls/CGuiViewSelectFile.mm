/*
 *  CGuiViewSelectFile.mm
 *  MobiTracker
 *
 *  Created by Marcin Skoczylas on 10-03-25.
 *  Copyright 2010 Marcin Skoczylas. All rights reserved.
 *
 */

#include "CGuiViewSelectFile.h"
#include "CGuiMain.h"
#include "GuiConsts.h"
#include "CGuiFolderFavorite.h"

#define TOP_LABEL_FONT_SIZE	12
#define TOP_LABEL_SIZEY		(TOP_LABEL_FONT_SIZE)+5

CGuiViewSelectFile::CGuiViewSelectFile(GLfloat posX, GLfloat posY, GLfloat posZ, GLfloat sizeX, GLfloat sizeY, bool cancelButton, CGuiViewSelectFileCallback *callback)
: CGuiView(posX, posY, posZ, sizeX, sizeY)
{
	pthread_mutex_init(&renderMutex, NULL);

	this->files = NULL;

	this->callback = callback;

	this->currentDirectoryPath = NULL;
	this->startDirectoryPath = NULL;
	
	CSlrFont *font = guiMain->fntConsole;
	float fontScale = 17.0f;
	float upGap = 1.0f;
	float elementsGap = 2.0f;

//	// TODO: workaround ... rewrite the CGuiViewSelectFile to support theming
//	CSlrFont *font = RES_GetFont("/Tracker/font/fixedsys");
//	float fontScale = 0.15f;
//	float upGap = 1.0f;
//	float elementsGap = -6.0f;
	
	this->listBoxFiles = new CGuiList(posX, posY + TOP_LABEL_SIZEY, posZ+0.01, this->sizeX, this->sizeY - TOP_LABEL_SIZEY*2, fontScale,
									  NULL, 0, false,
									  font,
									  guiMain->theme->imgBackground, 1.0f,
									  this);
	this->listBoxFiles->SetGaps(upGap, elementsGap);
	this->AddGuiElement(this->listBoxFiles);

	if (cancelButton)
	{
		btnDone = new CGuiButton("CANCEL", posEndX - (guiButtonSizeX + guiButtonGapX),
								 posEndY - (guiButtonSizeY + guiButtonGapY), posZ + 0.04,
								 guiButtonSizeX, guiButtonSizeY,
								 BUTTON_ALIGNED_DOWN, this);
		this->AddGuiElement(btnDone);
	}

	httpFileUploadedCallbacks.push_back(this);
}

CGuiViewSelectFile::~CGuiViewSelectFile()
{
	httpFileUploadedCallbacks.remove(this);
	pthread_mutex_destroy(&renderMutex);
}

void CGuiViewSelectFile::Init(std::list<UTFString *> *extensions)
{
	LOGD("CGuiViewSelectFile::Init");

	this->LockRenderMutex();
	this->extensions = extensions;
	this->UpdatePath();
	this->UnlockRenderMutex();
}

void CGuiViewSelectFile::Init(UTFString *directoryPath, std::list<UTFString *> *extensions)
{
	LOGD("CGuiViewSelectFile::Init");
	
	this->LockRenderMutex();
	this->extensions = extensions;
	this->currentDirectoryPath = UTFALLOC(directoryPath);	//strdup
	
	LOGD("directoryPath=");
	LOGD(directoryPath);
	
	LOGD("run CGuiViewSelectFile::UpdatePath");
	this->UpdatePath();
	LOGD("run CGuiViewSelectFile::UpdatePath done");
	
	this->UnlockRenderMutex();
}

void CGuiViewSelectFile::InitWithStartPath(UTFString *directoryPath, std::list<UTFString *> *extensions)
{
	LOGD("CGuiViewSelectFile::InitWithStartPath");

	this->LockRenderMutex();
	this->extensions = extensions;
	this->startDirectoryPath = UTFALLOC(directoryPath);		//strdup
	this->currentDirectoryPath = UTFALLOC(directoryPath);	//strdup

	LOGD("startDirectoryPath=");
	LOGD(directoryPath);

	LOGD("run CGuiViewSelectFile::UpdatePath");
	this->UpdatePath();
	LOGD("run CGuiViewSelectFile::UpdatePath done");

	this->UnlockRenderMutex();
}

void CGuiViewSelectFile::InitFavorites(std::list<CGuiFolderFavorite *> favorites)
{
	int numButs = 2;
	float butSizeX = 70.0f;
	float butSizeY = 10.0f;
	float butGap = 2.0f;
	
	float startX = sizeX - (butSizeX+butGap)*(float)numButs;
	float px = startX;
	float py = butGap;
	
	int i = 0;
	for (std::list<CGuiFolderFavorite *>::iterator it = favorites.begin(); it != favorites.end(); it++)
	{
		CGuiFolderFavorite *fav = *it;
		this->favorites.push_back(fav);
		
		CGuiButton *btn = new CGuiButton(fav->name, px, py, posZ + 0.04,
										 butSizeX, butSizeY,
										 BUTTON_ALIGNED_CENTER, this);
		btn->userData = fav;
		this->buttonsFavorites.push_back(btn);
		
		this->AddGuiElement(btn);
		
		i++;
		if (i < numButs)
		{
			px += butSizeX+butGap;
		}
		else
		{
			i = 0;
			px = startX;
			py += butSizeY+butGap;
		}
	}
}

void CGuiViewSelectFile::Refresh()
{
	this->LockRenderMutex();

	this->UpdatePath();

	this->UnlockRenderMutex();
}

void CGuiViewSelectFile::DeleteItems()
{
	int numFiles = files->size();
	for (int i = 0; i < numFiles; i++)
	{
		CFileItem *file = (*files)[i];

		//[file->name release];
		delete file;
	}

	delete this->files;
	this->files = NULL;
}

void CGuiViewSelectFile::UpdatePath()
{
	LOGD("CGuiViewSelectFile::UpdatePath");
	if (this->files && this->files->size() > 0)
		DeleteItems();

	this->files = gFileSystem->GetFiles(currentDirectoryPath, extensions);

	int numFiles = files->size();

	char **fileN = NULL;
#if defined(WIN32) || defined(LINUX) || defined(ANDROID) || defined(MACOS)
	LOGD("currentDirectoryPath='%s'", currentDirectoryPath);
	LOGD("  startDirectoryPath='%s'", startDirectoryPath);

	FixFileNameSlashes(currentDirectoryPath);
	FixFileNameSlashes(startDirectoryPath);

	if (!strcmp(currentDirectoryPath, startDirectoryPath))
#elif defined(IOS)
	if ([currentDirectoryPath isEqualToString:startDirectoryPath])
#endif
	{
		LOGD("EQUAL - we're in base dir");
		fileN = new char *[numFiles];

		for (int i = 0; i < numFiles; i++)
		{
			CFileItem *file = (*files)[i];
			UTFString *fname = file->name;

#if defined(WIN32) || defined(LINUX) || defined(ANDROID) || defined(MACOS)
			char *fileNameChars = fname;
#elif defined(IOS)
			const char *fileNameChars = [fname UTF8String];
#endif
			int len = strlen(fileNameChars)+1;
			fileN[i] = new char[len];
			memset(fileN[i], 0, len);
			strcpy(fileN[i], fileNameChars);
		}
		this->listBoxFiles->Init(fileN, numFiles, true);
	}
	else
	{
		LOGD("NOT EQUAL - we're not in base dir");

		fileN = new char *[numFiles+1];
		fileN[0] = new char[3];
		fileN[0][0] = '.';
		fileN[0][1] = '.';
		fileN[0][2] = 0x00;

		for (int i = 0; i < numFiles; i++)
		{
			CFileItem *file = (*files)[i];
			UTFString *fname = file->name;

#if defined(WIN32) || defined(LINUX) || defined(ANDROID) || defined(MACOS)
			char *fileNameChars = fname;
#elif defined(IOS)
			const char *fileNameChars = [fname UTF8String];
#endif
			int len = strlen(fileNameChars)+1;
			fileN[i+1] = new char[len]; //strdup(fileNameChars);
			memset(fileN[i+1], 0, len);
			strcpy(fileN[i+1], fileNameChars);
		}
		this->listBoxFiles->Init(fileN, numFiles+1, true);
	}
	
	this->UpdateDisplayDirectoryPath();

	LOGD("CGuiViewSelectFile::UpdatePath done");
}

void CGuiViewSelectFile::ListElementSelected(CGuiList *listBox)
{
	LOGD("ListElementSelected callback");

	if (listBox->selectedElement < 0)
		return;

	this->LockRenderMutex();

	CFileItem *file = NULL;

#if defined(WIN32) || defined(LINUX) || defined(ANDROID) || defined(MACOS)
	if (!strcmp(currentDirectoryPath, startDirectoryPath))
#elif defined(IOS)
	if ([currentDirectoryPath isEqualToString:startDirectoryPath])
#endif
	{
		file = (*files)[listBox->selectedElement];
	}
	else
	{
		if (listBox->selectedElement == 0)
		{
			LOGD("selected '..'");

#if defined(WIN32) || defined(LINUX) || defined(ANDROID) || defined(MACOS)
			char buf[4096];
			sprintf(buf, "%s", this->currentDirectoryPath);
			for (int i = strlen(buf)-2; i > 0; i--)
			{
				if (buf[i] == '\\' || buf[i] == '/')
				{
					buf[i] = '/';
					buf[i+1] = 0x00;
					break;
				}
			}

			UTFString *newPath = strdup(buf);
			free(this->currentDirectoryPath);
#elif defined(IOS)
			NSString *newPath = [[NSString alloc] initWithFormat:@"%@/", [this->currentDirectoryPath stringByDeletingLastPathComponent]];
			LOGD("newPath=");
			LOGD(newPath);
			[this->currentDirectoryPath release];
#endif
			this->currentDirectoryPath = newPath;

			this->UnlockRenderMutex();
			this->UpdatePath();
			return;
		}

		file = (*files)[listBox->selectedElement-1];
	}

	LOGD("selected %s:", (file->isDir ? "dir" : "file"));
	LOGD(file->name);

#if defined(WIN32) || defined(LINUX) || defined(ANDROID) || defined(MACOS)
	char buf[4096];
#elif defined(IOS)
	NSString *newPath = [[NSString alloc] initWithString:[this->currentDirectoryPath stringByAppendingPathComponent:file->name]];
#endif

	if (file->isDir)
	{
#if defined(WIN32) || defined(LINUX) || defined(ANDROID) || defined(MACOS)
		sprintf(buf, "%s%s/", this->currentDirectoryPath, file->name);
		UTFString *newPath = strdup(buf);
		free(this->currentDirectoryPath);
#elif defined(IOS)
		[this->currentDirectoryPath release];
#endif
		this->currentDirectoryPath = newPath;

		LOGD("currentDirectoryPath='%f'", newPath);

		this->UpdateDisplayDirectoryPath();

		this->UnlockRenderMutex();
		this->UpdatePath();
	}
	else
	{
#if defined(WIN32) || defined(LINUX) || defined(ANDROID) || defined(MACOS)
		sprintf(buf, "%s%s", this->currentDirectoryPath, file->name);
		UTFString *newPath = strdup(buf);
#endif
		// file selected
		this->UnlockRenderMutex();

		if (this->callback != NULL)
		{
			this->callback->FileSelected(newPath);
		}
	}
}

void CGuiViewSelectFile::UpdateDisplayDirectoryPath()
{
#if !defined(IOS)
	u32 p = 0;
	u32 l = strlen(currentDirectoryPath);
	for (u32 i = strlen(startDirectoryPath)-1; i < l; i++)
	{
		displayDirectoryPath[p] = currentDirectoryPath[i];
		p++;
	}
	displayDirectoryPath[p] = 0x00;
	
	LOGD("displayDirectoryPath='%s'", displayDirectoryPath);
#else
	LOGTODO("CGuiViewSelectFolder::UpdateDisplayDirectoryPath()");
#endif
	
}

void CGuiViewSelectFile::SetPath(char *setPath)
{
#if defined(IOS)
	LOGTODO("CGuiViewSelectFile::SetPath");
	return;
#else
	
	this->LockRenderMutex();

	GET_CHARBUF(buf);

#if defined(WIN32) || defined(LINUX) || defined(ANDROID) || defined(MACOS)
	if (setPath[0] == '/' && setPath[1] == 0x00)
	{
		sprintf(buf, "%s/", gPathToDocuments);
	}
	else
	{
		sprintf(buf, "%s%s/", gPathToDocuments, setPath);
	}
	UTFString *newPath = strdup(buf);
	free(this->currentDirectoryPath);
#elif defined(IOS)
	[this->currentDirectoryPath release];
#endif
	
	
	this->currentDirectoryPath = newPath;

	LOGD("currentDirectoryPath='%f'", newPath);

	REL_CHARBUF(buf);

	this->UnlockRenderMutex();
	this->UpdatePath();

#endif
}


bool CGuiViewSelectFile::ButtonPressed(CGuiButton *button)
{
	if (button == btnDone)
	{
		this->callback->FileSelectionCancelled();
		GUI_SetPressConsumed(true);
		return true;
	}

	// check favorites
	for (std::vector<CGuiButton *>::iterator it = buttonsFavorites.begin(); it != buttonsFavorites.end(); it++)
	{
		CGuiButton *btnFav = *it;
		if (btnFav == button)
		{
			CGuiFolderFavorite *fav = (CGuiFolderFavorite *)btnFav->userData;
			this->SetPath(fav->folderPath);
			return true;
		}
	}

	return true;
}

void CGuiViewSelectFile::HttpFileUploadedCallback()
{
	this->Refresh();
}

void CGuiViewSelectFile::SetCallback(CGuiViewSelectFileCallback *callback)
{
	this->callback = callback;
}

void CGuiViewSelectFile::Render()
{
	this->Render(this->posX, this->posY, this->posZ, this->sizeX, this->sizeY);
}

void CGuiViewSelectFile::Render(GLfloat posX, GLfloat posY, GLfloat posZ, GLfloat sizeX, GLfloat sizeY)
{
	this->LockRenderMutex();

	BlitFilledRectangle(posX, posY, posZ, sizeX, TOP_LABEL_SIZEY, 0.3f, 0.3f, 0.8f, 1.0f);
	//guiMain->imgBackground->Render(posX, posY, posZ, sizeX, sizeY);
	
	CGuiView::Render();
	
	guiMain->fntConsole->BlitText(this->displayDirectoryPath, posX, posY, posZ, TOP_LABEL_FONT_SIZE);

	this->UnlockRenderMutex();
}

void CGuiViewSelectFile::LockRenderMutex()
{
	pthread_mutex_lock(&this->renderMutex);
}

void CGuiViewSelectFile::UnlockRenderMutex()
{
	pthread_mutex_unlock(&this->renderMutex);
}

void CGuiViewSelectFileCallback::FileSelected(UTFString *filePath)
{
	return;
}

void CGuiViewSelectFileCallback::FileSelectionCancelled()
{
}

