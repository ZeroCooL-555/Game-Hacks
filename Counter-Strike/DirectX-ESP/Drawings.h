#ifndef DRAWINGS_H
#define DRAWINGS_H


#include "DirectX.h"

#pragma warning( disable : 4244 )
#pragma warning( disable : 4996 )


#include <d3dx9.h>
#include <d3d9.h>
#pragma comment(lib, "d3d9.lib")
#pragma comment(lib, "d3dx9.lib")



void DrawString(char* String, int x, int y, D3DCOLOR color, ID3DXFont* font);
void DrawFilledRectangle(int x, int y, int w, int h, D3DCOLOR color);
void DrawLine(int x1, int y1, int x2, int y2, int thickness, D3DCOLOR color);
void DrawEsp2D(int topx, int topy, int bottomx, int bottomy, int thickness, D3DCOLOR color);
#endif
