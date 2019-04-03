#pragma once
#include <Windows.h>
BYTE* LoadBMP(int* width, int* height, long* size, LPCTSTR bmpfile);
BYTE* ConvertBMPToIntensity(BYTE* Buffer, int width, int height);
int* Dilation(int* aramatris, int width, int heigt);
int* Erosion(int* aramatris, int width, int height);
int* Masking(float mask[], int* zoom_d,int width,int height);
int* Histogram(int width, int height, int *goruntu,int size);