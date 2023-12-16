#pragma once

struct Vec4
{
	float x, y, z, w;
};

struct Vec3
{
	float x, y, z;
};

struct Vec2
{
	float x, y;
};

struct Monitor
{
	int x, y;
};


float Get3Ddistance(Vec3 LocalPlayerCoords, Vec3 EnemyCoords);
bool WorldToScreen(Vec3 pos, Vec2& screen, float matrix[16], int windowWidth, int windowHeight);
extern Monitor monitor;