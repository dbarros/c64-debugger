#ifndef IMG_CIMAGEDATA_H_
#define IMG_CIMAGEDATA_H_

#include "./../SYS_Defs.h"
#include "./../SYS_Main.h"
#include "./../SYS_Funct.h"
#include "CBufferOffsets.h"
#include "./../libpng/png.h"
#include "./../libpng/pnginfo.h"
#include "./../libpng/pngpriv.h"

using namespace std;

typedef enum
{
	IMG_TYPE_UNKNOWN = 0,
	IMG_TYPE_GRAYSCALE,
	IMG_TYPE_SHORT_INT,
	IMG_TYPE_LONG_INT,
	IMG_TYPE_RGB,
	IMG_TYPE_RGBA,		// =5
	IMG_TYPE_CIELAB
} imageTypes;

typedef enum
{
	//IMG_ORIG = 0,
	IMG_TEMP = 1,
	IMG_RESULT
} imageSources;

//TODO: access pointers
/*	access = new T*[h];   // allocate space for row pointers

	//initialize row pointers
 	for (int i = 0; i < h; i++)
		access[i] = data + (i * w);
*/


class CImageData
{
private:
	//void *origData;
	void *tempData;
	void *resultData;
	byte type;
	
	byte *mask;
	
public:
	CImageData(char *fileName);
	CImageData(int width, int height, byte type);
	CImageData(int width, int height, byte type, void *data);
	CImageData(CImageData *src);
	~CImageData();
	
	CBufferOffsets *bufferOffsets;
	
	//int originalWidth, originalHeight;
	int width, height;
	void AllocImage(/*bool allocOrig,*/ bool allocTemp, bool allocResult);
	void AllocTempImage();	// additional alloc if necessary
	void AllocResultImage();
	void DeallocTemp();
	void DeallocResult();
	void DeallocImage();
	
	byte getImageType();
	void setImageType(byte type);
	void setResultImage(void *data, byte type);
	
	// grayscale
	byte GetPixelResultByte(int x, int y);
	void SetPixelResultByte(int x, int y, byte val);
	byte GetPixelResultByteSafe(int x, int y);
	void SetPixelResultByteSafe(int x, int y, byte val);
	byte GetPixelResultByteBorder(int x, int y);
	byte GetPixelTemporaryByte(int x, int y);
	void SetPixelTemporaryByte(int x, int y, byte val);
	byte *getGrayscaleResultData();
	byte *getGrayscaleTemporaryData();
	void setGrayscaleResultData(byte *data);
	// rgb
	void GetPixelResultRGB(int x, int y, byte *r, byte *g, byte *b);
	void SetPixelResultRGB(int x, int y, byte r, byte g, byte b);
	void GetPixelTemporaryRGB(int x, int y, byte *r, byte *g, byte *b);
	void SetPixelTemporaryRGB(int x, int y, byte r, byte g, byte b);
	byte *getRGBResultData();
	void setRGBResultData(byte *data);
	// rgba
	void GetPixelResultRGBA(int x, int y, byte *r, byte *g, byte *b, byte *a);
	void SetPixelResultRGBA(int x, int y, byte r, byte g, byte b, byte a);
	void GetPixelTemporaryRGBA(int x, int y, byte *r, byte *g, byte *b, byte *a);
	void SetPixelTemporaryRGBA(int x, int y, byte r, byte g, byte b, byte a);
	byte *getRGBAResultData();
	void setRGBAResultData(byte *data);
	// cielab
	void GetPixelResultCIELAB(int x, int y, int *l, int *a, int *b);
	void SetPixelResultCIELAB(int x, int y, int l, int a, int b);
	void GetPixelTemporaryCIELAB(int x, int y, int *l, int *a, int *b);
	void SetPixelTemporaryCIELAB(int x, int y, int l, int a, int b);
	int *getCIELABResultData();
	void setCIELABResultData(int *data);
	// short int (grayscale)
	short unsigned int GetPixelResultShort(int x, int y);
	void SetPixelResultShort(int x, int y, short unsigned int val);
	short unsigned int GetPixelTemporaryShort(int x, int y);
	void SetPixelTemporaryShort(int x, int y, short unsigned int val);
	short unsigned int *getShortIntResultData();
	void setShortIntResultData(short unsigned int *data);
	// long int (grayscale)
	long unsigned int GetPixelResultLong(int x, int y);
	void SetPixelResultLong(int x, int y, long unsigned int val);
	long unsigned int GetPixelTemporaryLong(int x, int y);
	void SetPixelTemporaryLong(int x, int y, long unsigned int val);
	long unsigned int *getLongIntResultData();
	void setLongIntResultData(long unsigned int *data);
	
	void copyTemporaryToResult();
	void copyResultToTemporary()	;
	
	void ConvertToByte();
	void ConvertToShortCount();
	void ConvertToShort();
		
	void Save(char *fileName);
	void SaveScaled(char *fileName, short int min, short int max);
	bool Load(char *fileName, bool dealloc);
	void RawSave(char *fileName);
	void RawLoad(char *fileName);
	
	// temporary here -> move to image filters
	void Scale(float scaleX, float scaleY);
	
	bool isInsideCircularMask(int x, int y);
	
	void debugPrint();

private:
	png_bytep *row_pointers;
};


#endif /*IMG_CIMAGEDATA_H_*/
