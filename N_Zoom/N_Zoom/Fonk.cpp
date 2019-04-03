#include "Fonk.h"
#include <Windows.h>

using namespace System;
using namespace System::ComponentModel;
using namespace System::Collections;
using namespace System::Windows::Forms;
using namespace System::Data;
using namespace System::Drawing;

BYTE* LoadBMP(int* width, int* height, long* size, LPCTSTR bmpfile)
{
	// declare bitmap structures
	BITMAPFILEHEADER bmpheader;
	BITMAPINFOHEADER bmpinfo;
	// value to be used in ReadFile funcs
	DWORD bytesread;
	// open file to read from
	HANDLE file = CreateFile(bmpfile, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_FLAG_SEQUENTIAL_SCAN, NULL);
	if (NULL == file)
		return NULL; // coudn't open file

					 // read file header
	if (ReadFile(file, &bmpheader, sizeof(BITMAPFILEHEADER), &bytesread, NULL) == false) {
		CloseHandle(file);
		return NULL;
	}
	//read bitmap info
	if (ReadFile(file, &bmpinfo, sizeof(BITMAPINFOHEADER), &bytesread, NULL) == false) {
		CloseHandle(file);
		return NULL;
	}
	// check if file is actually a bmp
	if (bmpheader.bfType != 'MB') {
		CloseHandle(file);
		return NULL;
	}
	// get image measurements
	*width = bmpinfo.biWidth;
	*height = abs(bmpinfo.biHeight);

	// check if bmp is uncompressed
	if (bmpinfo.biCompression != BI_RGB) {
		CloseHandle(file);
		return NULL;
	}
	// check if we have 24 bit bmp
	if (bmpinfo.biBitCount != 24) {
		CloseHandle(file);
		return NULL;
	}

	// create buffer to hold the data
	*size = bmpheader.bfSize - bmpheader.bfOffBits;
	BYTE* Buffer = new BYTE[*size];
	// move file pointer to start of bitmap data
	SetFilePointer(file, bmpheader.bfOffBits, NULL, FILE_BEGIN);
	// read bmp data
	if (ReadFile(file, Buffer, *size, &bytesread, NULL) == false) {
		delete[] Buffer;
		CloseHandle(file);
		return NULL;
	}
	// everything successful here: close file and return buffer
	CloseHandle(file);

	return Buffer;
}//LOADPMB

BYTE* ConvertBMPToIntensity(BYTE* Buffer, int width, int height)
{
	// first make sure the parameters are valid
	if ((NULL == Buffer) || (width == 0) || (height == 0))
		return NULL;

	// find the number of padding bytes

	int padding = 0;
	int scanlinebytes = width * 3;
	while ((scanlinebytes + padding) % 4 != 0)     // DWORD = 4 bytes
		padding++;
	// get the padded scanline width
	int psw = scanlinebytes + padding;

	// create new buffer
	BYTE* newbuf = new BYTE[width*height];

	// now we loop trough all bytes of the original buffer, 
	// swap the R and B bytes and the scanlines
	long bufpos = 0;
	long newpos = 0;
	for (int row = 0; row < height; row++)
		for (int column = 0; column < width; column++) {
			newpos = row * width + column;
			bufpos = (height - row - 1) * psw + column * 3;
			newbuf[newpos] = BYTE(0.11*Buffer[bufpos + 2] + 0.59*Buffer[bufpos + 1] + 0.3*Buffer[bufpos]);
		}

	return newbuf;
}

int* Dilation(int* aramatris, int width, int height) {
	
	int* orgmatris = new int[width*height];

	for (int m = 0; m < width*height; m++) {
		orgmatris[m] = 0;
	}
	int temp, temp2, temp3;


	for (int row = 0; row < height; row++)
	{
		for (int column = 0; column < width; column++) {
			temp = row * width + column;		//now
			temp2 = (row + 1)*width + column;   //down
			temp3 = (row - 1)*width + column;   //up
			if (aramatris[temp] == 1) {

				if (row == 0 && column == 0) {

					orgmatris[temp + 1] = 1;
					orgmatris[temp2] = 1;
					orgmatris[temp2 + 1] = 1;
				}

				else if (row == 0 && column != 0) {
					orgmatris[temp + 1] = 1;
					orgmatris[temp - 1] = 1;
					orgmatris[temp2] = 1;
					orgmatris[temp2 - 1] = 1;
					orgmatris[temp2 + 1] = 1;
				}

				else if (row == 0 && column == (width - 1)) {
					orgmatris[temp - 1] = 1;
					orgmatris[temp2] = 1;
					orgmatris[temp2 - 1] = 1;

				}
				else if (row != 0 && row != (height - 1) && column == 0) {
					orgmatris[temp + 1] = 1;
					orgmatris[temp2] = 1;
					orgmatris[temp2 + 1] = 1;
					orgmatris[temp3] = 1;
					orgmatris[temp3 + 1] = 1;
				}
				else if (row != 0 && column == (width - 1)) {
					orgmatris[temp3] = 1;
					orgmatris[temp3 - 1] = 1;
					orgmatris[temp - 1] = 1;
					orgmatris[temp2] = 1;
					orgmatris[temp2 - 1] = 1;
				}

				else if (row == (height - 1) && column == 0) {
					orgmatris[temp3] = 1;
					orgmatris[temp3 + 1] = 1;
					orgmatris[temp + 1] = 1;
				}
				else if (row == (height - 1) && column != 0 && column != (width - 1)) {
					orgmatris[temp3 - 1] = 1;
					orgmatris[temp3] = 1;
					orgmatris[temp3 + 1] = 1;
					orgmatris[temp - 1] = 1;
					orgmatris[temp + 1] = 1;
				}
				else if (row == (height - 1) && column == (width - 1)) {
					orgmatris[temp3] = 1;
					orgmatris[temp3 - 1] = 1;
					orgmatris[temp - 1] = 1;
				}
				else {
					orgmatris[temp3 - 1] = 1;
					orgmatris[temp3] = 1;
					orgmatris[temp3 + 1] = 1;
					orgmatris[temp - 1] = 1;
					orgmatris[temp + 1] = 1;
					orgmatris[temp2 - 1] = 1;
					orgmatris[temp2] = 1;
					orgmatris[temp2 + 1] = 1;


				}


			}
		}
	}
	for (int i = 0; i < width*height; i++) {
		if (orgmatris[i] == 1)
		{
			orgmatris[i] = 0;
		}
		else {
			orgmatris[i] = 255;
		}
	}




	return orgmatris;


}

int* Erosion(int* aramatris, int width, int height) {
	int matris[9] = { 1,1,1,1,1,1,1,1,1 };

	int* orgmatris = new int[width*height];

	for (int m = 0; m < width*height; m++) {
		orgmatris[m] = 0;
	}
	int temp, temp2, temp3;


	for (int row = 0; row < height; row++)
	{
		for (int column = 0; column < width; column++) {
			temp = row * width + column;		//now
			temp2 = (row + 1)*width + column;   //down
			temp3 = (row - 1)*width + column;   //up
			if (aramatris[temp] == 1) {

				if (row == 0 && column == 0) {

					if (aramatris[temp + 1] == matris[5] &&
						aramatris[temp2] == matris[7] &&
						aramatris[temp2 + 1] == matris[8]) {
						orgmatris[temp] = 1;
					}
				}

				else if (row == 0 && column != 0) {
					if (aramatris[temp + 1] == matris[5] &&
						aramatris[temp - 1] == matris[3] &&
						aramatris[temp2] == matris[7] &&
						aramatris[temp2 - 1] == matris[6] &&
						aramatris[temp2 + 1] == matris[8]  ) 
					{
						orgmatris[temp] = 1;
					}
				}

				else if (row == 0 && column == (width - 1)) {
					if (aramatris[temp - 1] == matris[3] &&
						aramatris[temp2] == matris[7] &&
						aramatris[temp2 - 1] == matris[6] ) 
					{
						orgmatris[temp] = 1;
					}

				}
				else if (row != 0 && row != (height - 1) && column == 0) {
					if(aramatris[temp + 1] == matris[5] &&
					aramatris[temp2] == matris[7]  &&
					aramatris[temp2 + 1] == matris[8] &&
					aramatris[temp3] == matris[1] &&
					aramatris[temp3 + 1] == matris[2] ) 
					{
						orgmatris[temp] = 1;
					}
				}

				else if (row != 0 && column == (width - 1)) {
					if (aramatris[temp3] == matris[1] &&
						aramatris[temp3 - 1] == matris[0] &&
						aramatris[temp - 1] == matris[3] &&
						aramatris[temp2] == matris[7] &&
						aramatris[temp2 - 1] == matris[6])
					{
						orgmatris[temp] = 1;
					}
				}

				else if (row == (height - 1) && column == 0) {
					if (aramatris[temp3] == matris[1] &&
						aramatris[temp3 + 1] == matris[2] &&
						aramatris[temp + 1] == matris[5])
					{
						orgmatris[temp] = 1;
					}
				}
				else if (row == (height - 1) && column != 0 && column != (width - 1)) {
					if (aramatris[temp3 - 1] == matris[0] &&
						aramatris[temp3] == matris[1] &&
						aramatris[temp3 + 1] == matris[2] &&
						aramatris[temp - 1] == matris[3] &&
						aramatris[temp + 1] == matris[5])
					{
						orgmatris[temp] = 1;
					}
				}
				else if (row == (height - 1) && column == (width - 1)) {
					if (aramatris[temp3] == matris[1] &&
						aramatris[temp3 - 1] == matris[0] &&
						aramatris[temp - 1] == matris[3])
					{
						orgmatris[temp] = 1;
					}
				}
				else {
					if (aramatris[temp3 - 1] == matris[0] &&
						aramatris[temp3] == matris[1] &&
						aramatris[temp3 + 1] == matris[2] &&
						aramatris[temp - 1] == matris[3] &&
						aramatris[temp + 1] == matris[5] &&
						aramatris[temp2 - 1] == matris[6] &&
						aramatris[temp2] == matris[7] &&
						aramatris[temp2 + 1] == matris[8])
					{
						orgmatris[temp] = 1;
					}


				}


			}
		}
	}
	for (int i = 0; i < width*height; i++) {
		if (orgmatris[i] == 1)
		{
			orgmatris[i] = 0;
		}
		else {
			orgmatris[i] = 255;
		}
	}

	return orgmatris;



}
int* Masking(float mask[], int* goruntu, int width,int height) {

	float toplam = 0;
	int p = 0;
	int c = 0;
	int s = 0;
	int z = 0;
	int temp4;
	int* result = new int[(width - 2)*(height - 2)];
	while (c<(height)-2) {
	  p = 0;
	  toplam = 0;
	  s = 0;
	     while (p < (width)-2) {
			toplam = 0;
			s = 0;
			for (int k = 0; k < 3; k++) {
			for (int n=0; n < 3; n++) {
			temp4 = (k + c) * (width) + (n + p);
			toplam = toplam + (goruntu[temp4] * mask[s] );
			s++;
			}
			
			
		}

	result[z] = System::Math::Abs(System::Convert::ToInt32(toplam));
	z++;
	p++;
}
	c++;
}  

	return result;
	
}

int* Histogram(int width,int height,int *goruntu,int size) {
	int *hist = new int[size];
	for (int i = 0; i < size; i++) {
		hist[i] = 0;
	}


	for (int i = 0; i < width*height; i++) {
		hist[goruntu[i]]++;


	}

	return hist;





}



