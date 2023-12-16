#include "Drawings.h"
#include <cmath>

void DrawString(const char* String, int x, int y, D3DCOLOR color, ID3DXFont* font)
{
	RECT FontPos;
	FontPos.left = x;
	FontPos.top = y;
	font->DrawTextA(0, String, strlen(String), &FontPos, DT_NOCLIP, color);
}

void DrawLine(int x1, int y1, int x2, int y2, int thickness, D3DCOLOR color)
{
	ID3DXLine* Linel;


	D3DXCreateLine(p_Device, &Linel);

	D3DXVECTOR2 Line[2];
	Line[0] = D3DXVECTOR2(x1, y1);
	Line[1] = D3DXVECTOR2(x2, y2);

	Linel->SetWidth(thickness);
	Linel->Draw(Line, 2, color);
	Linel->Release();
}

void DrawFilledRect(int x, int y, int w, int h, D3DCOLOR color)
{
	D3DRECT rect = { x, y, x + w, y + h };
	p_Device->Clear(1, &rect, D3DCLEAR_TARGET, color, 0, 0);
}

void DrawCornerBox(int X, int Y, int W, int H, int thickness, D3DCOLOR color)
{
	// hxxps://www.unknowncheats.me/forum/counterstrike-global-offensive/187269-corner-boxes.html
	
	
	float lineW = (W / 5);
	float lineH = (H / 6);
	float lineT = 1;

	//outline
	DrawLine(X - lineT, Y - lineT, X + lineW, Y - lineT, thickness, color); //top left
	DrawLine(X - lineT, Y - lineT, X - lineT, Y + lineH, thickness, color);
	DrawLine(X - lineT, Y + H - lineH, X - lineT, Y + H + lineT, thickness, color); //bot left
	DrawLine(X - lineT, Y + H + lineT, X + lineW, Y + H + lineT, thickness, color);
	DrawLine(X + W - lineW, Y - lineT, X + W + lineT, Y - lineT, thickness, color); // top right
	DrawLine(X + W + lineT, Y - lineT, X + W + lineT, Y + lineH, thickness, color);
	DrawLine(X + W + lineT, Y + H - lineH, X + W + lineT, Y + H + lineT, thickness, color); // bot right
	DrawLine(X + W - lineW, Y + H + lineT, X + W + lineT, Y + H + lineT, thickness, color);

	//inline
	DrawLine(X, Y, X, Y + lineH, thickness, color);//top left
	DrawLine(X, Y, X + lineW, Y, thickness, color);
	DrawLine(X + W - lineW, Y, X + W, Y, thickness, color); //top right
	DrawLine(X + W, Y, X + W, Y + lineH, thickness, color);
	DrawLine(X, Y + H - lineH, X, Y + H, thickness, color); //bot left
	DrawLine(X, Y + H, X + lineW, Y + H, thickness, color);
	DrawLine(X + W - lineW, Y + H, X + W, Y + H, thickness, color);//bot right
	DrawLine(X + W, Y + H - lineH, X + W, Y + H, thickness, color);

}


void DrawBorderBox(int x, int y, int width, int height, int thickness, D3DCOLOR color)
{
	// Draw top line
	DrawLine(x, y, x + width, y, thickness, color);

	// Draw bottom line
	DrawLine(x, y + height, x + width, y + height, thickness, color);

	// Draw left line
	DrawLine(x, y, x, y + height, thickness, color);

	// Draw right line
	DrawLine(x + width, y, x + width, y + height, thickness, color);
}
