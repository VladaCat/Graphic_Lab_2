#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <fstream> 
#include <cstdlib>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <cmath>

#ifndef MAIN_H_INCLUDED
#define MAIN_H_INCLUDED
typedef int FXPT2DOT30;
using namespace std;
double log(double a, double b)
{
	return log(b) / log(a);
}
typedef struct {
	FXPT2DOT30 ciexyzX;
	FXPT2DOT30 ciexyzY;
	FXPT2DOT30 ciexyzZ;
} CIEXYZ;

typedef struct {
	CIEXYZ  ciexyzRed;
	CIEXYZ  ciexyzGreen;
	CIEXYZ  ciexyzBlue;
} CIEXYZTRIPLE;

typedef struct
{
	unsigned int    bfType;
	unsigned long   bfSize;
	unsigned int    bfReserved1;
	unsigned int    bfReserved2;
	unsigned long   bfOffBits;
} BITMAPFILEHEADER;

typedef struct
{
	unsigned int    biSize;
	int             biWidth;
	int             biHeight;
	unsigned short  biPlanes;
	unsigned short  biBitCount;
	unsigned int    biCompression;
	unsigned int    biSizeImage;
	int             biXPelsPerMeter;
	int             biYPelsPerMeter;
	unsigned int    biClrUsed;
	unsigned int    biClrImportant;
	unsigned int   biRedMask;
	unsigned int   biGreenMask;
	unsigned int   biBlueMask;
	unsigned int   biAlphaMask;
	unsigned int   biCSType;
	CIEXYZTRIPLE   biEndpoints;
	unsigned int   biGammaRed;
	unsigned int   biGammaGreen;
	unsigned int   biGammaBlue;
	unsigned int   biIntent;
	unsigned int   biProfileData;
	unsigned int   biProfileSize;
	unsigned int   biReserved;
} BITMAPINFOHEADER;

typedef struct
{
	int   rgbBlue;
	int   rgbGreen;
	int   rgbRed;
	int   rgbReserved;
} RGBQUAD;


static unsigned short read_u16(FILE *fp);
static unsigned int   read_u32(FILE *fp);
static int            read_s32(FILE *fp);

static void write_u16(unsigned short input, FILE *fp);
static void write_u32(unsigned int input, FILE *fp);
static void write_s32(int input, FILE *fp);
#endif // MAIN_H_INCLUDEDs

int main()
{
	printf("Starting...\n");
	//считывание бмп
	FILE *pFile = fopen("C:/photo/cat.bmp", "rb");


	BITMAPFILEHEADER header;

	header.bfType = read_u16(pFile);
	header.bfSize = read_u32(pFile);
	header.bfReserved1 = read_u16(pFile);
	header.bfReserved2 = read_u16(pFile);
	header.bfOffBits = read_u32(pFile);
	BITMAPINFOHEADER bmiHeader;

	bmiHeader.biSize = read_u32(pFile);
	if (bmiHeader.biSize >= 40)
	{
		bmiHeader.biWidth = read_u32(pFile);
		bmiHeader.biHeight = read_u32(pFile);
		bmiHeader.biPlanes = read_u16(pFile);
		bmiHeader.biBitCount = read_u16(pFile);
		bmiHeader.biCompression = read_u32(pFile);
		bmiHeader.biSizeImage = read_u32(pFile);
		bmiHeader.biXPelsPerMeter = read_s32(pFile);
		bmiHeader.biYPelsPerMeter = read_s32(pFile);
		bmiHeader.biClrUsed = read_u32(pFile);
		bmiHeader.biClrImportant = read_u32(pFile);
	}
	if (bmiHeader.biSize >= 52)
	{
		bmiHeader.biRedMask = read_u32(pFile);
		bmiHeader.biGreenMask = read_u32(pFile);
		bmiHeader.biBlueMask = read_u32(pFile);
	}
	if (bmiHeader.biSize >= 56)
	{
		bmiHeader.biAlphaMask = read_u32(pFile);
	}
	if (bmiHeader.biSize >= 108)
	{
		bmiHeader.biCSType = read_u32(pFile);
		fread(&bmiHeader.biEndpoints, 36, 1, pFile);
		bmiHeader.biGammaRed = read_u32(pFile);
		bmiHeader.biGammaGreen = read_u32(pFile);
		bmiHeader.biGammaBlue = read_u32(pFile);
	}
	if (bmiHeader.biSize >= 124)
	{
		bmiHeader.biIntent = read_u32(pFile);
		bmiHeader.biProfileData = read_u32(pFile);
		bmiHeader.biProfileSize = read_u32(pFile);
		bmiHeader.biReserved = read_u32(pFile);
	}
	cout << "Width:" << bmiHeader.biWidth << "  " << "Height:" << bmiHeader.biHeight << endl;
	cout << "BitCount:" << bmiHeader.biBitCount << endl;
	cout << "ColorUsed:" << bmiHeader.biClrUsed << endl;
	RGBQUAD *pixels = new RGBQUAD[bmiHeader.biHeight * bmiHeader.biWidth + 1024];
	int c = bmiHeader.biHeight * bmiHeader.biWidth;
	for (int i = 0; i < c; i++)
	{
		pixels[i].rgbBlue = getc(pFile);
		pixels[i].rgbGreen = getc(pFile);
		pixels[i].rgbRed = getc(pFile);
		pixels[i].rgbReserved = getc(pFile);
	}


	fclose(pFile);
	//засветленная
	FILE *test1 = fopen("C:/photo/test1.bmp", "w+b");

	write_u16(header.bfType, test1);
	write_u32(header.bfSize, test1);
	write_u16(header.bfReserved1, test1);
	write_u16(header.bfReserved2, test1);
	write_u32(header.bfOffBits, test1);

	write_u32(bmiHeader.biSize, test1);
	if (bmiHeader.biSize >= 40)
	{
		write_s32(bmiHeader.biWidth, test1);
		write_s32(bmiHeader.biHeight, test1);
		write_u16(bmiHeader.biPlanes, test1);
		write_u16(bmiHeader.biBitCount, test1);
		write_u32(bmiHeader.biCompression, test1);
		write_u32(bmiHeader.biSizeImage, test1);
		write_s32(bmiHeader.biXPelsPerMeter, test1);
		write_s32(bmiHeader.biYPelsPerMeter, test1);
		write_u32(bmiHeader.biClrUsed, test1);
		write_u32(bmiHeader.biClrImportant, test1);
	}
	if (bmiHeader.biSize >= 52)
	{
		write_u32(bmiHeader.biRedMask, test1);
		write_u32(bmiHeader.biGreenMask, test1);
		write_u32(bmiHeader.biBlueMask, test1);
	}

	if (bmiHeader.biSize >= 56)
	{
		write_u32(bmiHeader.biAlphaMask, test1);
	}
	if (bmiHeader.biSize >= 108)
	{
		write_u32(bmiHeader.biCSType, test1);
		fwrite(&bmiHeader.biEndpoints, 36, 1, test1);
		write_u32(bmiHeader.biGammaRed, test1);
		write_u32(bmiHeader.biGammaGreen, test1);
		write_u32(bmiHeader.biGammaBlue, test1);
	}
	if (bmiHeader.biSize >= 124)
	{
		write_u32(bmiHeader.biIntent, test1);
		write_u32(bmiHeader.biProfileData, test1);
		write_u32(bmiHeader.biProfileSize, test1);
		write_u32(bmiHeader.biReserved, test1);
	}

	for (int i = 0; i < c; i++)
	{
		float a = ((pixels[i].rgbGreen + pixels[i].rgbBlue + pixels[i].rgbBlue) / 3);
		if (a > 200)
		{
			putc(250, test1);
			putc(250, test1);
			putc(250, test1);
			putc(pixels[i].rgbReserved, test1);
		}
		else
		{
			putc((pixels[i].rgbGreen + pixels[i].rgbBlue + pixels[i].rgbRed) / 3 + 40, test1);
			putc((pixels[i].rgbGreen + pixels[i].rgbBlue + pixels[i].rgbRed) / 3 + 40, test1);
			putc((pixels[i].rgbGreen + pixels[i].rgbBlue + pixels[i].rgbRed) / 3 + 40, test1);
			putc(pixels[i].rgbReserved, test1);
		}
	}
	fclose(test1);
	//затемненная
	FILE* test2 = fopen("C:/photo/test2.bmp", "w+b");
	write_u16(header.bfType, test2);
	write_u32(header.bfSize, test2);
	write_u16(header.bfReserved1, test2);
	write_u16(header.bfReserved2, test2);
	write_u32(header.bfOffBits, test2);

	write_u32(bmiHeader.biSize, test2);
	if (bmiHeader.biSize >= 40)
	{
		write_s32(bmiHeader.biWidth, test2);
		write_s32(bmiHeader.biHeight, test2);
		write_u16(bmiHeader.biPlanes, test2);
		write_u16(bmiHeader.biBitCount, test2);
		write_u32(bmiHeader.biCompression, test2);
		write_u32(bmiHeader.biSizeImage, test2);
		write_s32(bmiHeader.biXPelsPerMeter, test2);
		write_s32(bmiHeader.biYPelsPerMeter, test2);
		write_u32(bmiHeader.biClrUsed, test2);
		write_u32(bmiHeader.biClrImportant, test2);
	}
	if (bmiHeader.biSize >= 52)
	{
		write_u32(bmiHeader.biRedMask, test2);
		write_u32(bmiHeader.biGreenMask, test2);
		write_u32(bmiHeader.biBlueMask, test2);
	}

	if (bmiHeader.biSize >= 56)
	{
		write_u32(bmiHeader.biAlphaMask, test2);
	}
	if (bmiHeader.biSize >= 108)
	{
		write_u32(bmiHeader.biCSType, test2);
		fwrite(&bmiHeader.biEndpoints, 36, 1, test2);
		write_u32(bmiHeader.biGammaRed, test2);
		write_u32(bmiHeader.biGammaGreen, test2);
		write_u32(bmiHeader.biGammaBlue, test2);
	}
	if (bmiHeader.biSize >= 124)
	{
		write_u32(bmiHeader.biIntent, test2);
		write_u32(bmiHeader.biProfileData, test2);
		write_u32(bmiHeader.biProfileSize, test2);
		write_u32(bmiHeader.biReserved, test2);
	}

	for (int i = 0; i < c; i++)
	{
		putc((pixels[i].rgbGreen + pixels[i].rgbBlue + pixels[i].rgbRed) / 6, test2);
		putc((pixels[i].rgbGreen + pixels[i].rgbBlue + pixels[i].rgbRed) / 6, test2);
		putc((pixels[i].rgbGreen + pixels[i].rgbBlue + pixels[i].rgbRed) / 6, test2);
		putc(pixels[i].rgbReserved, test2);

	}
	int*mas = new int[c];
	int*chek = new int[256];
	float*gist = new float[256];
	for (int j = 0; j < 256; j++)
	{
		chek[j] = j;
		gist[j] = 0;
	}
	for (int i = 0; i < c; i++)
	{
		mas[i] = (pixels[i].rgbGreen + pixels[i].rgbBlue + pixels[i].rgbBlue) / 3;
	}

	for (int j = 0; j < 256; j++)
		for (int i = 0; i < c; i++)
		{
			if (mas[i] == chek[j])
			{
				gist[j]++;
			}
		}
	//delete[]pixels;


	fclose(test2);
	//бинаризация
	FILE* test3 = fopen("C:/photo/test3.bmp", "w+b");
	write_u16(header.bfType, test3);
	write_u32(header.bfSize, test3);
	write_u16(header.bfReserved1, test3);
	write_u16(header.bfReserved2, test3);
	write_u32(header.bfOffBits, test3);

	write_u32(bmiHeader.biSize, test3);
	if (bmiHeader.biSize >= 40)
	{
		write_s32(bmiHeader.biWidth, test3);
		write_s32(bmiHeader.biHeight, test3);
		write_u16(bmiHeader.biPlanes, test3);
		write_u16(bmiHeader.biBitCount, test3);
		write_u32(bmiHeader.biCompression, test3);
		write_u32(bmiHeader.biSizeImage, test3);
		write_s32(bmiHeader.biXPelsPerMeter, test3);
		write_s32(bmiHeader.biYPelsPerMeter, test3);
		write_u32(bmiHeader.biClrUsed, test3);
		write_u32(bmiHeader.biClrImportant, test3);
	}
	if (bmiHeader.biSize >= 52)
	{
		write_u32(bmiHeader.biRedMask, test3);
		write_u32(bmiHeader.biGreenMask, test3);
		write_u32(bmiHeader.biBlueMask, test3);
	}

	if (bmiHeader.biSize >= 56)
	{
		write_u32(bmiHeader.biAlphaMask, test3);
	}
	if (bmiHeader.biSize >= 108)
	{
		write_u32(bmiHeader.biCSType, test3);
		fwrite(&bmiHeader.biEndpoints, 36, 1, test3);
		write_u32(bmiHeader.biGammaRed, test3);
		write_u32(bmiHeader.biGammaGreen, test3);
		write_u32(bmiHeader.biGammaBlue, test3);
	}
	if (bmiHeader.biSize >= 124)
	{
		write_u32(bmiHeader.biIntent, test3);
		write_u32(bmiHeader.biProfileData, test3);
		write_u32(bmiHeader.biProfileSize, test3);
		write_u32(bmiHeader.biReserved, test3);
	}

	for (int i = 0; i < c; i++)
	{
		if ((pixels[i].rgbGreen + pixels[i].rgbBlue + pixels[i].rgbBlue) / 3 > 64)
		{
			putc(255, test3);
			putc(255, test3);
			putc(255, test3);
			putc(255, test3);
		}
		else
		{
			putc(0, test3);
			putc(0, test3);
			putc(0, test3);
			putc(pixels[i].rgbReserved, test3);
		}
	}
	fclose(test3);
	//Логарифмическая корекция

	FILE* test4 = fopen("C:/photo/test4.bmp", "w+b");
	write_u16(header.bfType, test4);
	write_u32(header.bfSize, test4);
	write_u16(header.bfReserved1, test4);
	write_u16(header.bfReserved2, test4);
	write_u32(header.bfOffBits, test4);

	write_u32(bmiHeader.biSize, test4);
	if (bmiHeader.biSize >= 40)
	{
		write_s32(bmiHeader.biWidth, test4);
		write_s32(bmiHeader.biHeight, test4);
		write_u16(bmiHeader.biPlanes, test4);
		write_u16(bmiHeader.biBitCount, test4);
		write_u32(bmiHeader.biCompression, test4);
		write_u32(bmiHeader.biSizeImage, test4);
		write_s32(bmiHeader.biXPelsPerMeter, test4);
		write_s32(bmiHeader.biYPelsPerMeter, test4);
		write_u32(bmiHeader.biClrUsed, test4);
		write_u32(bmiHeader.biClrImportant, test4);
	}
	if (bmiHeader.biSize >= 52)
	{
		write_u32(bmiHeader.biRedMask, test4);
		write_u32(bmiHeader.biGreenMask, test4);
		write_u32(bmiHeader.biBlueMask, test4);
	}

	if (bmiHeader.biSize >= 56)
	{
		write_u32(bmiHeader.biAlphaMask, test4);
	}
	if (bmiHeader.biSize >= 108)
	{
		write_u32(bmiHeader.biCSType, test4);
		fwrite(&bmiHeader.biEndpoints, 36, 1, test4);
		write_u32(bmiHeader.biGammaRed, test4);
		write_u32(bmiHeader.biGammaGreen, test4);
		write_u32(bmiHeader.biGammaBlue, test4);
	}
	if (bmiHeader.biSize >= 124)
	{
		write_u32(bmiHeader.biIntent, test4);
		write_u32(bmiHeader.biProfileData, test4);
		write_u32(bmiHeader.biProfileSize, test4);
		write_u32(bmiHeader.biReserved, test4);
	}
	double y = 3;
	for (int i = 0; i < c; i++)
	{

		putc(pixels[i].rgbBlue*log(2, 1 + y) , test4);
		//cout << (int)log(y, pixels[i].rgbBlue) << endl;
		putc(pixels[i].rgbGreen*log(2, 1 + y), test4);
		putc(pixels[i].rgbRed*log(2, 1 + y), test4);
		putc(pixels[i].rgbReserved, test4);

	}
	fclose(test4);
	//гистограмма картинки
	FILE *gisto = fopen("C:/photo/gisto1.bmp", "w+b");
	write_u16(header.bfType, gisto);
	write_u32(header.bfSize, gisto);
	write_u16(header.bfReserved1, gisto);
	write_u16(header.bfReserved2, gisto);
	write_u32(header.bfOffBits, gisto);

	write_u32(bmiHeader.biSize, gisto);
	if (bmiHeader.biSize >= 40)
	{
		write_s32(255, gisto);
		write_s32(255, gisto);
		write_u16(bmiHeader.biPlanes, gisto);
		write_u16(bmiHeader.biBitCount, gisto);
		write_u32(bmiHeader.biCompression, gisto);
		write_u32(bmiHeader.biSizeImage, gisto);
		write_s32(bmiHeader.biXPelsPerMeter, gisto);
		write_s32(bmiHeader.biYPelsPerMeter, gisto);
		write_u32(bmiHeader.biClrUsed, gisto);
		write_u32(bmiHeader.biClrImportant, gisto);
	}
	if (bmiHeader.biSize >= 52)
	{
		write_u32(bmiHeader.biRedMask, gisto);
		write_u32(bmiHeader.biGreenMask, gisto);
		write_u32(bmiHeader.biBlueMask, gisto);
	}

	if (bmiHeader.biSize >= 56)
	{
		write_u32(bmiHeader.biAlphaMask, gisto);
	}
	if (bmiHeader.biSize >= 108)
	{
		write_u32(bmiHeader.biCSType, gisto);
		fwrite(&bmiHeader.biEndpoints, 36, 1, gisto);
		write_u32(bmiHeader.biGammaRed, gisto);
		write_u32(bmiHeader.biGammaGreen, gisto);
		write_u32(bmiHeader.biGammaBlue, gisto);
	}
	if (bmiHeader.biSize >= 124)
	{
		write_u32(bmiHeader.biIntent, gisto);
		write_u32(bmiHeader.biProfileData, gisto);
		write_u32(bmiHeader.biProfileSize, gisto);
		write_u32(bmiHeader.biReserved, gisto);
	}
	int k = 0;
	for (int j = 254; j >= 0; j--)
	{

		for (int l = 254; l >= 0; l--)
		{
			if (k - gist[l] / 100 < 0)
			{
				putc(0, gisto);
				putc(0, gisto);
				putc(0, gisto);
				putc(255, gisto);

			}
			else
			{
				putc(255, gisto);
				putc(255, gisto);
				putc(255, gisto);
				putc(255, gisto);
			}
		}
		k++;
	}
	fclose(gisto);
	//Логарифмически коректированая гистограмма
	FILE *gisto1 = fopen("C:/photo/gisto2.bmp", "w+b");
	write_u16(header.bfType, gisto1);
	write_u32(header.bfSize, gisto1);
	write_u16(header.bfReserved1, gisto1);
	write_u16(header.bfReserved2, gisto1);
	write_u32(header.bfOffBits, gisto1);

	write_u32(bmiHeader.biSize, gisto1);
	if (bmiHeader.biSize >= 40)
	{
		write_s32(255, gisto1);
		write_s32(255, gisto1);
		write_u16(bmiHeader.biPlanes, gisto1);
		write_u16(bmiHeader.biBitCount, gisto1);
		write_u32(bmiHeader.biCompression, gisto1);
		write_u32(bmiHeader.biSizeImage, gisto1);
		write_s32(bmiHeader.biXPelsPerMeter, gisto1);
		write_s32(bmiHeader.biYPelsPerMeter, gisto1);
		write_u32(bmiHeader.biClrUsed, gisto1);
		write_u32(bmiHeader.biClrImportant, gisto1);
	}
	if (bmiHeader.biSize >= 52)
	{
		write_u32(bmiHeader.biRedMask, gisto1);
		write_u32(bmiHeader.biGreenMask, gisto1);
		write_u32(bmiHeader.biBlueMask, gisto1);
	}

	if (bmiHeader.biSize >= 56)
	{
		write_u32(bmiHeader.biAlphaMask, gisto1);
	}
	if (bmiHeader.biSize >= 108)
	{
		write_u32(bmiHeader.biCSType, gisto1);
		fwrite(&bmiHeader.biEndpoints, 36, 1, gisto1);
		write_u32(bmiHeader.biGammaRed, gisto1);
		write_u32(bmiHeader.biGammaGreen, gisto1);
		write_u32(bmiHeader.biGammaBlue, gisto1);
	}
	if (bmiHeader.biSize >= 124)
	{
		write_u32(bmiHeader.biIntent, gisto1);
		write_u32(bmiHeader.biProfileData, gisto1);
		write_u32(bmiHeader.biProfileSize, gisto1);
		write_u32(bmiHeader.biReserved, gisto1);
	}
	k = 0;
	for (int j = 254; j >= 0; j--)
	{

		for (int l = 254; l >= 0; l--)
		{
			if (k - gist[l]*log(1+y,2)/100 < 0)
			{
				putc(0, gisto1);
				putc(0, gisto1);
				putc(0, gisto1);
				putc(255, gisto1);

			}
			else
			{
				putc(255, gisto1);
				putc(255, gisto1);
				putc(255, gisto1);
				putc(255, gisto1);
			}
		}
		k++;
	}
	fclose(gisto1);
	system("pause");
	printf("Complete\n");
	return 0;
}


static unsigned short read_u16(FILE *fp)
{
	unsigned char b0, b1;

	b0 = getc(fp);
	b1 = getc(fp);

	return ((b1 << 8) | b0);
}


static unsigned int read_u32(FILE *fp)
{
	unsigned char b0, b1, b2, b3;

	b0 = getc(fp);
	b1 = getc(fp);
	b2 = getc(fp);
	b3 = getc(fp);

	return ((((((b3 << 8) | b2) << 8) | b1) << 8) | b0);
}


static int read_s32(FILE *fp)
{
	unsigned char b0, b1, b2, b3;

	b0 = getc(fp);
	b1 = getc(fp);
	b2 = getc(fp);
	b3 = getc(fp);

	return ((int)(((((b3 << 8) | b2) << 8) | b1) << 8) | b0);
}

static void write_u16(unsigned short input, FILE *fp)
{
	putc(input, fp);
	putc(input >> 8, fp);
}

static void write_u32(unsigned int input, FILE *fp)
{
	putc(input, fp);
	putc(input >> 8, fp);
	putc(input >> 16, fp);
	putc(input >> 24, fp);
}

static void write_s32(int input, FILE *fp)
{
	putc(input, fp);
	putc(input >> 8, fp);
	putc(input >> 16, fp);
	putc(input >> 24, fp);
}
unsigned char bitextract(const unsigned int byte, const unsigned int mask) {
	if (mask == 0) {
		return 0;
	}

	// определение количества нулевых бит справа от маски
	int
		maskBufer = mask,
		maskPadding = 0;

	while (!(maskBufer & 1)) {
		maskBufer >>= 1;
		maskPadding++;
	}

	// применение маски и смещение
	return (byte & mask) >> maskPadding;
}
