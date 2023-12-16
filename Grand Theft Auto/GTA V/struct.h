#pragma once

#include <Windows.h>

uintptr_t WorldPTR;
uintptr_t GlobalPTR;
uintptr_t BlipPTR;
uintptr_t WaypointPTR;

class CWorld
{
public:
	struct CPed // a.k.a -> WorldPTR -> CPed Offset: 0x8
	{
		uintptr_t Health; // 0x280
		uintptr_t MaxHealth; // 0x2A0
		uintptr_t Armor; // 0x14E0
		uintptr_t GodMode; // 0x189
		uintptr_t Position; // X: 0x30 Y: 0x34 Z: 0x38
		uintptr_t Camera_Coords; // X : 0x90 Y : 0x94  Z : 0x98
		uintptr_t bInCar; // 0x1477
		uintptr_t bIsAfk;
		struct Coords
		{
			float x, y, z;
		};

		struct CPlayerinfo // Offset to access Struct -> 0x8 -> 0x10C8
		{
			uintptr_t Wanted_lvl; // 0x868
			uintptr_t Run_Speed; // 0xCD0
			uintptr_t Swim_Speed; // 0x150 
		};


		struct CVehicle // Offset to access Struct -> 0x8 -> 0xD30
		{
			uintptr_t GodMode; // 0x189
			//uintptr_t invisible_car; 0x2C0
			uintptr_t Position;
			uintptr_t Camera_Coords;
			uintptr_t CurrentVehiclePTR;
			uintptr_t Gravity;
			struct Coords
			{
				float x, y, z;
			};

			struct CVehicleHandlingData // Offset to access Struct -> 0x8 -> 0xD30 -> 0x938
			{
				uintptr_t Mass;
				uintptr_t Acceleration;
				uintptr_t Brake_Force;
				uintptr_t HandBrake_Force;
				uintptr_t Traction_Curve_Left;
				uintptr_t Traction_Curve_Right;
				uintptr_t Collision_Damage_Multiplier;
				uintptr_t Weapon_Damage_Multiplier;
				uintptr_t Deformation_Multiplier;
				uintptr_t Engine_Damage_Multiplier;
				uintptr_t Suspension_Height;
			};


			struct CVehicleDrawHandler // Offset to access Struct -> 0x8 -> 0xD30 -> 0x48
			{
				uintptr_t EMS; // Engine Management System
				uintptr_t Breaks;
				uintptr_t Suspension;
				uintptr_t Transmission;
				uintptr_t Armor;
				uintptr_t Turbo;
				uintptr_t Neon_RED;
				uintptr_t Neon_PINK;
				uintptr_t Neon_BLUE;
				uintptr_t Neon_Left_Side;
				uintptr_t Neon_Right_Side;
				uintptr_t Neon_Front_Side;
				uintptr_t Neon_Back_Side;
				uintptr_t Limo_Windows;
			};
		};

	};



	struct Map
	{
		uintptr_t Waypoint;
		struct WaypointCoords
		{
			float x, y;
		};
	};
};






CWorld::CPed Player;
CWorld::CPed::CPlayerinfo Playerinfo;
CWorld::CPed::Coords PlayerCoords;
CWorld::CPed::CVehicle Vehicle;
CWorld::CPed::CVehicle::CVehicleHandlingData VehicleHandling;
CWorld::CPed::CVehicle::CVehicleDrawHandler VehicleTunings;
CWorld::CPed::CVehicle::Coords VehicleCoords;
CWorld::Map::WaypointCoords WayPointCoords;
CWorld::Map map;
