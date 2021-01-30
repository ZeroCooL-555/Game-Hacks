#include "Drawings.h"
#include <cmath>

void DrawString(char* String, int x, int y, D3DCOLOR color, ID3DXFont* font)
{
	RECT FontPos;
	FontPos.left = x;
	FontPos.top = y;
	//SetRect(&FontPos, x + 1, y + 1, x + 1, y + 1);
	font->DrawTextA(0, String, strlen(String), &FontPos, DT_NOCLIP, color);
}

void DrawFilledRectangle(int x, int y, int w, int h, D3DCOLOR color)
{
	D3DRECT rect = { x, y,x + w,y + h };
	p_Device->Clear(1, &rect, D3DCLEAR_TARGET, color, 0, 0);
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

void DrawEsp2D(int topx, int topy, int bottomx, int bottomy, int thickness, D3DCOLOR color)
{
	int height = std::abs(topy - bottomy);

	int tl_x, tl_y, tr_x, tr_y; // topleft and topright...Cant use Vec2 so using a int
	int bl_x, bl_y, br_x, br_y; // bottomleft and bottomright...Cant use Vec2 so using int

	tl_x = topx - height / 4;
	tr_x = topx + height / 4;
	tl_y = tr_y = topy;

	bl_x = bottomx - height / 4;
	br_x = bottomx + height / 4;
	bl_y = br_y = bottomy;


	DrawLine(tl_x, tl_y, tr_x, tr_y, thickness, color);
	DrawLine(bl_x, bl_y, br_x, br_y, thickness, color);
	DrawLine(tl_x, tl_y, bl_x, bl_y, thickness, color);
	DrawLine(tr_x, tr_y, br_x, br_y, thickness, color);

}
