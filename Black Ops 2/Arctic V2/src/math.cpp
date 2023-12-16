#include "math.h"
#include <cmath>


bool WorldToScreen(Vec3 pos, Vec2& screen, float matrix[16], int windowWidth, int windowHeight) // converts 3D coords to 2D coords
{
	//Matrix-vector Product, multiplying world(eye) coordinates by projection matrix = clipCoords
	Vec4 clipCoords;
	clipCoords.x = pos.x * matrix[0] + pos.y * matrix[1] + pos.z * matrix[2] + matrix[3];
	clipCoords.y = pos.x * matrix[4] + pos.y * matrix[5] + pos.z * matrix[6] + matrix[7];
	clipCoords.z = pos.x * matrix[8] + pos.y * matrix[9] + pos.z * matrix[10] + matrix[11];
	clipCoords.w = pos.x * matrix[12] + pos.y * matrix[13] + pos.z * matrix[14] + matrix[15];

	if (clipCoords.w < 0.1f) // if the camera is behind our player don't draw
		return false;


	Vec3 NDC;
	// Normalize our coords
	NDC.x = clipCoords.x / clipCoords.w;
	NDC.y = clipCoords.y / clipCoords.w;
	NDC.z = clipCoords.z / clipCoords.w;

	// Convert to window coords (x,y)
	screen.x = (windowWidth / 2 * NDC.x) + (NDC.x + windowWidth / 2);
	screen.y = -(windowHeight / 2 * NDC.y) + (NDC.y + windowHeight / 2);
	return true;
}

float Get3Ddistance(Vec3 LocalPlayerCoords, Vec3 EnemyCoords)
{
	return (float)(sqrt(
		pow(LocalPlayerCoords.x - EnemyCoords.x, 2.0) +
		pow(LocalPlayerCoords.y - EnemyCoords.y, 2.0) +
		pow(LocalPlayerCoords.z - EnemyCoords.z, 2.0))) * 0.0254f;
}