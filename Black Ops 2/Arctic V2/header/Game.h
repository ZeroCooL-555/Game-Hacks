#pragma once
#include <Windows.h>
#include "math.h"
#include "DirectX.h"


// Custom Games only
// ===============================================
#define MAX_CLIENTS 18
#define MAX_ENTITIES 64
#define VSAT_ADDR 0x012A0CA4
#define LOCAL_POS_OFF 0x2C
#define PLAYERBASE 0x2E496518
#define PLAYER_HEALTH 0x21EF968
#define PLAYER_ITEAMNUM 0x011497D0

#define ENTITY_LIST 0x01DEFC38
#define ENTITY_HEALTH_OFF 0x1A8
#define ENTITY_LOOP 0x8C
#define ENTITY_HEADPOS 0x128 // 128 12c 130
#define ENTITY_POS 0x134 // 134 138 13c
#define VIEW_MATRIX 0x01065F40
#define FOV_ADDR 0x2A430C0
// ================================================



struct EntityINFO
{
	DWORD EntityHealth;
	DWORD entlist;
	DWORD CurrentEnemy;
	Vec3 Position;
	Vec3 HeadPosition;
	void ReadEnemiesData(int enemy);
};

struct Local
{
	Vec3 local_pos;
	int Health;
	float Matrix[16];
	int Team;
	void ReadLP();
};

class Color
{
public:
	const static D3DCOLOR red = D3DCOLOR_RGBA(255, 0, 0, 255);
	const static D3DCOLOR green = D3DCOLOR_RGBA(0, 255, 0, 255);
	const static D3DCOLOR cyan = D3DCOLOR_RGBA(0, 255, 255, 255);
	const static D3DCOLOR yellow = D3DCOLOR_RGBA(255, 255, 0, 255);
	const static D3DCOLOR tangerine = D3DCOLOR_RGBA(255, 179, 25, 255);
	const static D3DCOLOR gray = D3DCOLOR_RGBA(211, 211, 211, 255);
	const static D3DCOLOR black = D3DCOLOR_RGBA(32, 32, 32, 255);
};

extern Local LocalPlayer;
extern EntityINFO Enemies[MAX_ENTITIES];
