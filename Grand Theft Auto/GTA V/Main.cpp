#include<Windows.h>
#include<iostream>
#include "MemoryTools.h"
#include "struct.h"
#include "Functions.h"
#include "OFFSETS.h"
// GTA ONLINE VERSION 1.52


struct Handling
{
	uintptr_t Procid = GetPID(L"GTA5.exe");
	uintptr_t ModuleBaseAddress = GetModuleBaseAddress(Procid, L"GTA5.exe");
	HANDLE handle = OpenProcess(PROCESS_ALL_ACCESS, false, Procid);
	HANDLE stdout_colour = GetStdHandle(STD_OUTPUT_HANDLE);
	HWND Window = FindWindow(0, L"Grand Theft Auto V");
}setup;

void PointerResolve(bool Version)
{
	// Resolve World,Global,Blip Pointers

	if (Version) // Social-Club
	{
		// Social-Club Pointers
		WorldPTR = setup.ModuleBaseAddress + 0x24e6d90;
		WaypointPTR = setup.ModuleBaseAddress + 0x1F94460;
		GlobalPTR = setup.ModuleBaseAddress + 0x2d9c4a0;
	}
	else
	{
		//Steam
		WorldPTR = setup.ModuleBaseAddress + 0x24E9E50;
		WaypointPTR = setup.ModuleBaseAddress + 0x1F73420;
		GlobalPTR = setup.ModuleBaseAddress + 0x2DA0A60;
	}
	

	/*

	=================================================================================================
										CWorld::CPed
	=================================================================================================

	*/

	// Resolving Health Pointer

	std::vector<unsigned int> HealthOffsets = { OFFSET_PLAYER_PED, OFFSET_ENTITY_HEALTH };
	Player.Health = FindPTR(setup.handle, WorldPTR, HealthOffsets);

	// Resolving Max Health Pointer

	std::vector<unsigned int> MaxHealthOffsets = { OFFSET_PLAYER_PED, OFFSET_ENTITY_HEALTH_MAX };
	Player.MaxHealth = FindPTR(setup.handle, WorldPTR, MaxHealthOffsets);

	// Resolving Armor Pointer

	std::vector<unsigned int> ArmorOffsets = { OFFSET_PLAYER_PED, OFFSET_PLAYER_ARMOR };
	Player.Armor = FindPTR(setup.handle, WorldPTR, ArmorOffsets);

	// Resolving Godmode Pointer

	std::vector<unsigned int> GodmodeOffsets = { OFFSET_PLAYER_PED, OFFSET_ENTITY_GOD };
	Player.GodMode = FindPTR(setup.handle, WorldPTR, GodmodeOffsets);

	// Resolving Player x,y,z Pointers

	std::vector<unsigned int> PositionOffsets = { OFFSET_PLAYER_PED, OFFSET_ENTITY_POSBASE, OFFSET_ENTITY_POSBASE_POS };
	Player.Position = FindPTR(setup.handle, WorldPTR, PositionOffsets);


	std::vector<unsigned int> CamOffsets = { OFFSET_PLAYER_PED, OFFSET_ENTITY_POS_CAMERA };
	Player.Camera_Coords = FindPTR(setup.handle, WorldPTR, CamOffsets);


	/*

	==================================================================================================
										CWorld::CPed::CPlayerinfo
	==================================================================================================

	*/

	// Resloving Player Wanted level Pointer

	std::vector<unsigned int> WantedlvlOffsets = { OFFSET_PLAYER_PED, OFFSET_PLAYER_INFO, OFFSET_PLAYER_INFO_WANTED };
	Playerinfo.Wanted_lvl = FindPTR(setup.handle, WorldPTR, WantedlvlOffsets);

	// Resolving Player Run Speed Pointer

	std::vector<unsigned int> speedOffsets = { OFFSET_PLAYER_PED, OFFSET_PLAYER_INFO, OFFSET_PLAYER_INFO_RUN_SPD };
	Playerinfo.Run_Speed = FindPTR(setup.handle, WorldPTR, speedOffsets);

	// Resolving Player Swim Speed Pointer

	std::vector<unsigned int> swimOffsets = { OFFSET_PLAYER_PED, OFFSET_PLAYER_INFO, OFFSET_PLAYER_INFO_SWIM_SPD };
	Playerinfo.Swim_Speed = FindPTR(setup.handle, WorldPTR, swimOffsets);

	// Resolving isInVehicle Pointer

	std::vector<unsigned int> bInVehicle = { OFFSET_PLAYER_PED, OFFSET_PLAYER_INVEHICLE };
	Player.bInCar = FindPTR(setup.handle, WorldPTR, bInVehicle);


	/*
	==================================================================================================
										CWorld::Map
	==================================================================================================
	*/

	// Resolving Waypoint x,y Pointer

	map.Waypoint = WaypointPTR;
};

void GetCurrentVehiclePTR()
{
	/*
	==================================================================================================
										CWorld::CPed::CVehicle
	==================================================================================================
	*/

	std::vector<unsigned int> VehGodmode = { OFFSET_PLAYER_PED, OFFSET_PLAYER_VEHICLE, OFFSET_ENTITY_GOD };
	Vehicle.GodMode = FindPTR(setup.handle, WorldPTR, VehGodmode);

	std::vector<unsigned int> VehiclePos = { OFFSET_PLAYER_PED, OFFSET_PLAYER_VEHICLE, OFFSET_ENTITY_POSBASE, OFFSET_ENTITY_POSBASE_POS };
	Vehicle.Position = FindPTR(setup.handle, WorldPTR, VehiclePos);

	std::vector<unsigned int> VehicleCamPos = { OFFSET_PLAYER_PED, OFFSET_PLAYER_VEHICLE, OFFSET_ENTITY_POS_CAMERA };
	Vehicle.Camera_Coords = FindPTR(setup.handle, WorldPTR, VehicleCamPos);


	std::vector<unsigned int> VehicleOffsets = { OFFSET_PLAYER_PED, OFFSET_PLAYER_VEHICLE };
	Vehicle.CurrentVehiclePTR = FindPTR(setup.handle, WorldPTR, VehicleOffsets);


	std::vector<unsigned int> VehGravityOffsets = { OFFSET_PLAYER_PED, OFFSET_PLAYER_VEHICLE, OFFSET_VEHICLE_GRAVITY };
	Vehicle.Gravity = FindPTR(setup.handle, WorldPTR, VehGravityOffsets);

	ReadProcessMemory(setup.handle, (LPVOID)(Vehicle.CurrentVehiclePTR), &Vehicle.CurrentVehiclePTR, sizeof(Vehicle.CurrentVehiclePTR), nullptr);
	ReadProcessMemory(setup.handle, (LPVOID)(Vehicle.Camera_Coords), &Vehicle.Camera_Coords, sizeof(Vehicle.Camera_Coords), nullptr);


	/*
	==================================================================================================
						CWorld::CPed::CVehicle::CVehicleHandlingData
	==================================================================================================
	*/

	// Resove Vehicle Mass Pointers
	std::vector<unsigned int> MassOffsets = { OFFSET_PLAYER_PED, OFFSET_PLAYER_VEHICLE, OFFSET_VEHICLE_HANDLING, OFFSET_VEHICLE_HANDLING_MASS };
	VehicleHandling.Mass = FindPTR(setup.handle, WorldPTR, MassOffsets);


	// Resolve Vehicle Acceleration Pointers
	std::vector<unsigned int> AccelerationOffsets = { OFFSET_PLAYER_PED, OFFSET_PLAYER_VEHICLE, OFFSET_VEHICLE_HANDLING, OFFSET_VEHICLE_HANDLING_ACCELERATION };
	VehicleHandling.Acceleration = FindPTR(setup.handle, WorldPTR, AccelerationOffsets);


	// Resolve Brake force Pointers
	std::vector<unsigned int> BreakForceOffsets = { OFFSET_PLAYER_PED, OFFSET_PLAYER_VEHICLE, OFFSET_VEHICLE_HANDLING, OFFSET_VEHICLE_HANDLING_BRAKEFORCE };
	VehicleHandling.Brake_Force = FindPTR(setup.handle, WorldPTR, BreakForceOffsets);

	// Resolve Handbreak force Pointers
	std::vector<unsigned int> HandbreakForceOffsets = { OFFSET_PLAYER_PED, OFFSET_PLAYER_VEHICLE, OFFSET_VEHICLE_HANDLING, OFFSET_VEHICLE_HANDLING_HANDBRAKEFORCE };
	VehicleHandling.HandBrake_Force = FindPTR(setup.handle, WorldPTR, HandbreakForceOffsets);

	// Resolve Traction Curve Min
	std::vector<unsigned int> TractionCurveMinOffsets = { OFFSET_PLAYER_PED, OFFSET_PLAYER_VEHICLE, OFFSET_VEHICLE_HANDLING, OFFSET_VEHICLE_HANDLING_TRACTION_CURVE_LEFT };
	VehicleHandling.Traction_Curve_Left = FindPTR(setup.handle, WorldPTR, TractionCurveMinOffsets);

	// Resolve Traction Curve Max
	std::vector<unsigned int> TractionCurveMaxOffsets = { OFFSET_PLAYER_PED, OFFSET_PLAYER_VEHICLE, OFFSET_VEHICLE_HANDLING, OFFSET_VEHICLE_HANDLING_TRACTION_CURVE_RIGHT };
	VehicleHandling.Traction_Curve_Right = FindPTR(setup.handle, WorldPTR, TractionCurveMaxOffsets);

	// Resolve Collision Damage Multiplier
	std::vector<unsigned int> CollisionDmgOffsets = { OFFSET_PLAYER_PED, OFFSET_PLAYER_VEHICLE, OFFSET_VEHICLE_HANDLING, OFFSET_VEHICLE_HANDLING_COLISION_DAMAGE_MP };
	VehicleHandling.Collision_Damage_Multiplier = FindPTR(setup.handle, WorldPTR, CollisionDmgOffsets);

	// Resolve Weapon Damage Multiplier
	std::vector<unsigned int> WeaponDmgOffsets = { OFFSET_PLAYER_PED, OFFSET_PLAYER_VEHICLE, OFFSET_VEHICLE_HANDLING, OFFSET_VEHICLE_HANDLING_WEAPON_DAMAGE_MP };
	VehicleHandling.Weapon_Damage_Multiplier = FindPTR(setup.handle, WorldPTR, WeaponDmgOffsets);

	// Resolve Deformation Multiplier
	std::vector<unsigned int> DeformationOffsets = { OFFSET_PLAYER_PED, OFFSET_PLAYER_VEHICLE, OFFSET_VEHICLE_HANDLING, OFFSET_VEHICLE_HANDLING_DEFORM_MULTIPLIER };
	VehicleHandling.Deformation_Multiplier = FindPTR(setup.handle, WorldPTR, DeformationOffsets);

	// Resolve Engine Damage Multiplier
	std::vector<unsigned int> EngineDmgOffsets = { OFFSET_PLAYER_PED, OFFSET_PLAYER_VEHICLE, OFFSET_VEHICLE_HANDLING, OFFSET_VEHICLE_HANDLING_ENGINE_DAMAGE_MP };
	VehicleHandling.Engine_Damage_Multiplier = FindPTR(setup.handle, WorldPTR, EngineDmgOffsets);

	// Resolve Suspension Height
	std::vector<unsigned int> SuspensionHeightOffsets = { OFFSET_PLAYER_PED, OFFSET_PLAYER_VEHICLE, OFFSET_VEHICLE_HANDLING, OFFSET_VEHICLE_HANDLING_SUSPENSION_HEIGH };
	VehicleHandling.Suspension_Height = FindPTR(setup.handle, WorldPTR, SuspensionHeightOffsets);


	/*
	==================================================================================================
						CWorld::CPed::CVehicle::CVehicleDrawHandler
	==================================================================================================
	*/



	// Resolve Engine Pointers

	std::vector<unsigned int> EMSoffsets = { OFFSET_PLAYER_PED, OFFSET_PLAYER_VEHICLE, OFFSET_VEHICLE_CUSTOM, OFFSET_VEHICLE_CUSTOM_EMS };
	VehicleTunings.EMS = FindPTR(setup.handle, WorldPTR, EMSoffsets);

	// Resolve Turbo Pointers
	std::vector<unsigned int> TurboOffsets = { OFFSET_PLAYER_PED, OFFSET_PLAYER_VEHICLE, OFFSET_VEHICLE_CUSTOM, OFFSET_VEHICLE_CUSTOM_TURBO_TUNING };
	VehicleTunings.Turbo = FindPTR(setup.handle, WorldPTR, TurboOffsets);

	// Resolve Break Pointers
	std::vector<unsigned int> BreakOffsets = { OFFSET_PLAYER_PED, OFFSET_PLAYER_VEHICLE, OFFSET_VEHICLE_CUSTOM, OFFSET_VEHICLE_CUSTOM_BRAKES };
	VehicleTunings.Breaks = FindPTR(setup.handle, WorldPTR, BreakOffsets);

	// Resolve Suspension Pointers
	std::vector<unsigned int> SuspensionLvlOffsets = { OFFSET_PLAYER_PED, OFFSET_PLAYER_VEHICLE, OFFSET_VEHICLE_CUSTOM, OFFSET_VEHICLE_CUSTOM_SUSPENSION };
	VehicleTunings.Suspension = FindPTR(setup.handle, WorldPTR, SuspensionLvlOffsets);

	// Resolve Transmission Pointers
	std::vector<unsigned int> TransmissionOffsets = { OFFSET_PLAYER_PED, OFFSET_PLAYER_VEHICLE, OFFSET_VEHICLE_CUSTOM, OFFSET_VEHICLE_CUSTOM_TRANSMISSION };
	VehicleTunings.Transmission = FindPTR(setup.handle, WorldPTR, TransmissionOffsets);

	// Resolve Vehicle Armor Pointers
	std::vector<unsigned int> ArmorOffsets_Veh = { OFFSET_PLAYER_PED, OFFSET_PLAYER_VEHICLE, OFFSET_VEHICLE_CUSTOM, OFFSET_VEHICLE_CUSTOM_ARMOR };
	VehicleTunings.Armor = FindPTR(setup.handle, WorldPTR, ArmorOffsets_Veh);

	// Resolve Limo window Pointers
	std::vector<unsigned int> limoWindowOffsets = { OFFSET_PLAYER_PED, OFFSET_PLAYER_VEHICLE, OFFSET_VEHICLE_CUSTOM, OFFSET_VEHICLE_CUSTOM_LIMO_WINDOWS };
	VehicleTunings.Limo_Windows = FindPTR(setup.handle, WorldPTR, limoWindowOffsets);

	// Resolve Vehicle Neon Colour Pointers
	std::vector<unsigned int> NeonBOffsets = { OFFSET_PLAYER_PED, OFFSET_PLAYER_VEHICLE, OFFSET_VEHICLE_CUSTOM, OFFSET_VEHICLE_CUSTOM_NEON_LIGHT_BLUE };
	VehicleTunings.Neon_BLUE = FindPTR(setup.handle, WorldPTR, NeonBOffsets);

	std::vector<unsigned int> NeonGOffsets = { OFFSET_PLAYER_PED, OFFSET_PLAYER_VEHICLE, OFFSET_VEHICLE_CUSTOM, OFFSET_VEHICLE_CUSTOM_NEON_LIGHT_PINK };
	VehicleTunings.Neon_PINK = FindPTR(setup.handle, WorldPTR, NeonGOffsets);

	std::vector<unsigned int> NeonROffsets = { OFFSET_PLAYER_PED, OFFSET_PLAYER_VEHICLE, OFFSET_VEHICLE_CUSTOM, OFFSET_VEHICLE_CUSTOM_NEON_LIGHT_RED };
	VehicleTunings.Neon_RED = FindPTR(setup.handle, WorldPTR, NeonROffsets);

	// Resolve Vehicle Neon Position Pointers
	std::vector<unsigned int> NeonRightOffsets = { OFFSET_PLAYER_PED, OFFSET_PLAYER_VEHICLE, OFFSET_VEHICLE_CUSTOM, OFFSET_VEHICLE_CUSTOM_NEON_LIGHTS_R };
	VehicleTunings.Neon_Right_Side = FindPTR(setup.handle, WorldPTR, NeonRightOffsets);

	std::vector<unsigned int> NeonLeftOffsets = { OFFSET_PLAYER_PED, OFFSET_PLAYER_VEHICLE, OFFSET_VEHICLE_CUSTOM, OFFSET_VEHICLE_CUSTOM_NEON_LIGHTS_L };
	VehicleTunings.Neon_Left_Side = FindPTR(setup.handle, WorldPTR, NeonLeftOffsets);

	std::vector<unsigned int> NeonFrontOffsets = { OFFSET_PLAYER_PED, OFFSET_PLAYER_VEHICLE, OFFSET_VEHICLE_CUSTOM, OFFSET_VEHICLE_CUSTOM_NEON_LIGHTS_F };
	VehicleTunings.Neon_Front_Side = FindPTR(setup.handle, WorldPTR, NeonFrontOffsets);

	std::vector<unsigned int> NeonBackOffsets = { OFFSET_PLAYER_PED, OFFSET_PLAYER_VEHICLE, OFFSET_VEHICLE_CUSTOM, OFFSET_VEHICLE_CUSTOM_NEON_LIGHTS_B };
	VehicleTunings.Neon_Back_Side = FindPTR(setup.handle, WorldPTR, NeonBackOffsets);

}

void Readcoords()
{
	// LocalPlayer Coords (x, y, z)
	ReadProcessMemory(setup.handle, (CWorld::CPed::Coords*)(Player.Position), &PlayerCoords, sizeof(PlayerCoords), nullptr);
	

	// Vehicle Coords (x, y, z)
	ReadProcessMemory(setup.handle, (CWorld::CPed::CVehicle::Coords*)(Vehicle.Position), &VehicleCoords, sizeof(VehicleCoords), nullptr);

	// WayPoint Coords(x, y, z)
	ReadProcessMemory(setup.handle, (CWorld::Map::WaypointCoords*)(map.Waypoint), &WayPointCoords, sizeof(WayPointCoords), nullptr);

}

void Max_Tune_Car()
{

	GetCurrentVehiclePTR();
	
	BYTE MaxEngineLvl = 3;
	BYTE Enable_Turbo = 1;
	BYTE MaxSuspension = 27;
	BYTE MaxTransmission = 9;
	BYTE MaxArmor = 14;
	BYTE MaxBreaks = 6;
	BYTE Enable_Limo_Windows = 1;
	BYTE SetNeonLeft = 1;
	BYTE SetNeonRight = 1;
	BYTE SetNeonFront = 1;
	BYTE SetNeonBack = 1;
	BYTE EnableNeon = 1;

	float NoDamage = 0;
	
	// Engine, Turbo, Suspension, Transmission, Armor, Breaks, Limo Windows
	WriteProcessMemory(setup.handle, (BYTE*)(VehicleTunings.EMS), &MaxEngineLvl, sizeof(MaxEngineLvl), nullptr);
	WriteProcessMemory(setup.handle, (BYTE*)(VehicleTunings.Turbo), &Enable_Turbo, sizeof(Enable_Turbo), nullptr);
	WriteProcessMemory(setup.handle, (BYTE*)(VehicleTunings.Suspension), &MaxSuspension, sizeof(MaxSuspension), nullptr);
	WriteProcessMemory(setup.handle, (BYTE*)(VehicleTunings.Transmission), &MaxTransmission, sizeof(MaxTransmission), nullptr);
	WriteProcessMemory(setup.handle, (BYTE*)(VehicleTunings.Armor), &MaxArmor, sizeof(MaxArmor), nullptr);
	WriteProcessMemory(setup.handle, (BYTE*)(VehicleTunings.Breaks), &MaxBreaks, sizeof(MaxBreaks), nullptr);
	WriteProcessMemory(setup.handle, (BYTE*)(VehicleTunings.Limo_Windows), &Enable_Limo_Windows, sizeof(Enable_Limo_Windows), nullptr);

	// Neon Light and all sides left,right,front,back
	WriteProcessMemory(setup.handle, (BYTE*)(VehicleTunings.Neon_Left_Side), &SetNeonLeft, sizeof(SetNeonLeft), nullptr);
	WriteProcessMemory(setup.handle, (BYTE*)(VehicleTunings.Neon_Right_Side), &SetNeonRight, sizeof(SetNeonRight), nullptr);
	WriteProcessMemory(setup.handle, (BYTE*)(VehicleTunings.Neon_Front_Side), &SetNeonFront, sizeof(SetNeonFront), nullptr);
	WriteProcessMemory(setup.handle, (BYTE*)(VehicleTunings.Neon_Back_Side), &SetNeonBack, sizeof(SetNeonBack), nullptr);

	WriteProcessMemory(setup.handle, (BYTE*)(VehicleTunings.Neon_PINK), &EnableNeon, sizeof(EnableNeon), nullptr);

	// No visual Deformation, collision damage and weapon dmg
	WriteProcessMemory(setup.handle, (PFLOAT*)(VehicleHandling.Collision_Damage_Multiplier), &NoDamage, sizeof(NoDamage), nullptr);
	WriteProcessMemory(setup.handle, (PFLOAT*)(VehicleHandling.Deformation_Multiplier), &NoDamage, sizeof(NoDamage), nullptr);
	WriteProcessMemory(setup.handle, (PFLOAT*)(VehicleHandling.Weapon_Damage_Multiplier), &NoDamage, sizeof(NoDamage), nullptr);
}

void Perfect_Handling(bool EnablePerfectHandling)
{
	
	GetCurrentVehiclePTR();

	float PerfectHandling = 50; // Increases Gravity, cars stick to ground

	if (EnablePerfectHandling)
	{
		WriteProcessMemory(setup.handle, (PFLOAT*)(Vehicle.Gravity), &PerfectHandling, sizeof(PerfectHandling), nullptr);
	}
	else
	{
		PerfectHandling = 9.8; // Default Gravity (Earths Acceleration Gravity constant 9.8 m/s^2)
		WriteProcessMemory(setup.handle, (PFLOAT*)(Vehicle.Gravity), &PerfectHandling, sizeof(PerfectHandling), nullptr);
	}
	
}

void Undead_off_Radar(bool EnableOffRadar) // This enables never wanted too because player is dead
{
	if (EnableOffRadar)
	{
		BYTE GodON = 1;
		float MaxHP = 0;
		WriteProcessMemory(setup.handle, (BYTE*)(Player.GodMode), &GodON, sizeof(GodON), nullptr);
		WriteProcessMemory(setup.handle, (PFLOAT*)(Player.MaxHealth), &MaxHP, sizeof(MaxHP), nullptr);
	}
	else
	{
		BYTE Godoff = 0;
		float MaxHP = 328;
		WriteProcessMemory(setup.handle, (BYTE*)(Player.GodMode), &Godoff, sizeof(Godoff), nullptr);
		WriteProcessMemory(setup.handle, (PFLOAT*)(Player.MaxHealth), &MaxHP, sizeof(MaxHP), nullptr);
	}
}

uintptr_t _GetGlobal(int AtIndex)
{
	/*
	Resources for info on globals
	
	Best Resource to understand what to do with globals
	https://www.unknowncheats.me/forum/grand-theft-auto-v/144028-grand-theft-auto-reversal-structs-offsets-270.html
	- Read post from Adventure Box


	1. Here the function _GetGlobal is created and used
	https://gitlab.com/ExternalMemoryakaLolBobTest/external-menu-gta-5-csgo/-/blob/master/GTA%205%20C++/1.4.1/Hack.cpp#L417
	
	2. Information on what globals are and how to find them, update them, change them etc
	https://www.unknowncheats.me/forum/grand-theft-auto-v/407535-global-info.html
	https://www.unknowncheats.me/forum/grand-theft-auto-v/413171-globals.html - Answer by Adventure Box
	*/
	return ReadMemory<uintptr_t>(setup.handle, (GlobalPTR) + (8 * (AtIndex >> 0x12 & 0x3F))) + (8 * (AtIndex & 0x3FFFF));
}

void LSC_Sell_Car_Method(int Amount)
{
	WriteMemory<int>(setup.handle, _GetGlobal(99007 + 970), Amount);
	SetConsoleTextAttribute(setup.stdout_colour, FOREGROUND_GREEN | FOREGROUND_INTENSITY);
	std::cout << "Sell Value Has Been Modified!" << std::endl << std::endl;
	SetConsoleTextAttribute(setup.stdout_colour, 15 | FOREGROUND_INTENSITY);

	std::cout << "QUIT GAME WITH (ALT + F4)" << std::endl << std::endl;
	std::cout << "Press Any Key to Close Hack....";
	getchar();
	CloseHandle(setup.handle);
	CloseHandle(setup.Window);
	CloseHandle(setup.stdout_colour);
	exit(0);

}

void CREATE_AMBIENT_PICKUP(float x, float y, float z) // Spawn Money
{
	// Found by reversing func_8717,func_1741 and func_1742 decompiled freemode.c GTA Online version 1.52

	WriteMemory<int>(setup.handle, _GetGlobal(4264051 + 1 + (ReadMemory<int>(setup.handle, _GetGlobal(2515202)) * 85) + 66 + 2), 2); // Pass if Checks?
	
	/*
	int func_1741(int iParam0)
	{
		if (iParam0 >= 0 && iParam0 < 15)
		{
		return Global_4264051[iParam0 /*85*\/].f_66.f_2;
		}
		return 0;
	}
	int func_1742(int iParam0)
	{
		if (iParam0 >= 0 && iParam0 < 15)
		{
			return Global_4264051[iParam0 /*85*\/].f_66.f_2 != 1;
		}
		return 0;
	}
	
	Returning 2 with the RPM passes these checks
	*/

	WriteMemory<int>(setup.handle, _GetGlobal(2515202 + 1), 2000); // Money Amount
	WriteMemory<float>(setup.handle, _GetGlobal(2515202 + 3 + 0), x);
	WriteMemory<float>(setup.handle, _GetGlobal(2515202 + 3 + 1), y);
	WriteMemory<float>(setup.handle, _GetGlobal(2515202 + 3 + 2), z);
	WriteMemory<int>(setup.handle, _GetGlobal(2515202), 2); // pass if checks??
	WriteMemory<int>(setup.handle, _GetGlobal(2515208), 1); // make MISC::IS_BIT_SET = true

	/*
	void func_8717()
	{
		if (MISC::IS_BIT_SET(Global_2515208, 0)) pass check with WriteMemory<int>(setup.handle, _GetGlobal(2515208), 1);
		{
			if (func_1742(Global_2515202)) pass both this and next check with WriteMemory<int>(setup.handle, _GetGlobal(2515202), 2); ??
			{
				if (func_1741(Global_2515202) == 2)
				{
					NETSHOPPING::NET_GAMESERVER_SET_TELEMETRY_NONCE_SEED(func_1739(Global_2515202));
					MONEY::NETWORK_SPENT_CASH_DROP(Global_2515202.f_1, false, false);
					func_1736(-Global_2515202.f_1, 0);
					func_8718(&(Global_2515202.f_2));
					OBJECT::CREATE_AMBIENT_PICKUP(joaat("pickup_money_variable"), Global_2515202.f_3, Global_2515202.f_2, Global_2515202.f_1, 0, false, true);
					if (MISC::IS_BIT_SET(Global_2515209, 1))
					{
						if (DECORATOR::DECOR_IS_REGISTERED_AS_TYPE("cashondeadbody", 3))
						{
							if (!DECORATOR::DECOR_EXIST_ON(PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(PLAYER::PLAYER_ID()), "cashondeadbody"))
							{
								DECORATOR::DECOR_SET_INT(PLAYER::PLAYER_PED_ID(), "cashondeadbody", Global_2515202.f_1);
							}
						}
						MISC::CLEAR_BIT(&Global_2515209, 1);
					}
					func_1731(Global_2515202);
					MISC::CLEAR_BIT(&Global_2515208, 0);
					Global_2515202.f_1 = 0;
					Global_2515202.f_2 = 0;
				}
				else if (func_1741(Global_2515202) == 3)
				{
					func_1731(Global_2515202);
					MISC::CLEAR_BIT(&Global_2515208, 0);
					Global_2515202.f_1 = 0;
					Global_2515202.f_2 = 0;
				}
			}
		}
	}

	Reversing:

	OBJECT::CREATE_AMBIENT_PICKUP(joaat("pickup_money_variable"), Global_2515202.f_3, Global_2515202.f_2, Global_2515202.f_1, 0, false, true);

	Global_2515202.f_3 = Vector3 { x, y, z}
	Global_2515202.f_2 = No Clue
	Global_2515202.f_1 = Money Amount

	*/

}

void Anti_Kick()
{
	while (true)
	{
		Sleep(120000);
		WriteMemory<int>(setup.handle, _GetGlobal(1377236 + 1149), 0);
	}
}

void RP_Multi(bool IsEnabled)
{
	if (IsEnabled)
		WriteMemory<float>(setup.handle, _GetGlobal(262145 + 1), 500); // 500x Multiplier
	else
		WriteMemory<float>(setup.handle, _GetGlobal(262145 + 1), 1); // 1x Default Multiplier
}

int main()
{
	// Set Console Name
	SetConsoleTitleA("GoldenJackPot");

	// Game versions
	bool SocialClub = true;
	bool Steam = false;
	int choose;
	std::cout << "Social Club or Steam (use 1 or 2): ";
	std::cin >> choose;
	if (choose == 1)
	{
		PointerResolve(SocialClub);
	}
	else if (choose == 2)
	{
		PointerResolve(Steam);
	}
	else
	{
		SetConsoleTextAttribute(setup.stdout_colour, FOREGROUND_RED | FOREGROUND_INTENSITY);
		std::cout << "Input not 1 or 2!" << std::endl << std::endl;
		SetConsoleTextAttribute(setup.stdout_colour, 15 | FOREGROUND_INTENSITY);
		std::cout << "Closing Hack..." << std::endl;
		CloseHandle(setup.handle);
		CloseHandle(setup.Window);
		Sleep(3000);
		exit(0);
	}
	
	// Clear Screen to enter main screen
	system("cls");

	// TOGGLES
	bool GodMode = false;
	bool VehGodMode = false;
	bool menu_one = true;
	bool InvisVeh = false;
	bool SpawnMoney = false;
	bool bOffTheRadar = false;
	bool bHandling = false;
	bool bRPMulti = false;

	// Menu Visual Values
	int Speed_Value_Show = 1;
	float Speed_Modify = 1;

	int Swim_value_show = 1;
	float Swim_modify = 1;

	// Is Player In car variable
	int isinCar;

	// Start Anti-AFK Thread
	CreateThread(0, 0, (LPTHREAD_START_ROUTINE)Anti_Kick, 0, 0, 0);

	// Main Program Logic
	while (true)
	{
		if (menu_one)
		{
			system("cls");
			SetConsoleTextAttribute(setup.stdout_colour, 6 | FOREGROUND_INTENSITY); // 6 = Yellow
			std::cout << "[ANTI-AFK]: ";
			SetConsoleTextAttribute(setup.stdout_colour, 15 | FOREGROUND_INTENSITY); // 15 = White

			SetConsoleTextAttribute(setup.stdout_colour, FOREGROUND_GREEN | FOREGROUND_INTENSITY);
			std::cout << "Running" << std::endl << std::endl;
			SetConsoleTextAttribute(setup.stdout_colour, 15 | FOREGROUND_INTENSITY);

			std::cout << "[INS] GodMode: " << (GodMode ? "ON" : "OFF") << std::endl;
			std::cout << "[PGUP] Vehicle GodMode: " << (VehGodMode ? "ON" : "OFF") << std::endl;
			std::cout << "[PGDWN] 500x RP-MultiPlier: " << (bRPMulti ? "ON" : "OFF") << std::endl;
			std::cout << "[F10] Off The Radar: " << (bOffTheRadar ? "ON" : "OFF") << std::endl;
			std::cout << "[F12] Perfect Handling: " << (bHandling ? "ON" : "OFF") << std::endl << std::endl;
			std::cout << "[F5] Run Speed " << "( Value: " << Speed_Value_Show << " )" << std::endl;
			std::cout << "[F6] Swim Speed " << "( Value: " << Swim_value_show << " )" << std::endl << std::endl;
			std::cout << "[DEL] Clear Wanted Level " << std::endl;
			std::cout << "[F3] Teleport To Waypoint" << std::endl;
			std::cout << "[F4] Max Tune Car " << std::endl;
			std::cout << "[F9] Spawn Money" << std::endl;

			std::cout << "[END] LSC Sell Method ";
			SetConsoleTextAttribute(setup.stdout_colour, FOREGROUND_RED | FOREGROUND_INTENSITY);
			std::cout << "(Will Terminate Hack)" << std::endl;
			SetConsoleTextAttribute(setup.stdout_colour, 15 | FOREGROUND_INTENSITY);
			menu_one = false;
		}
		if (GetAsyncKeyState(VK_INSERT) & 1)
		{
			GodMode = !GodMode;
			menu_one = !menu_one;
			if (GodMode)
			{
				BYTE GodmodeValue = 1;

				WriteProcessMemory(setup.handle, (LPVOID)Player.GodMode, &GodmodeValue, sizeof(GodmodeValue), nullptr);
			}
			else
			{
				!GodMode;
				!menu_one;
				BYTE GodmodeOFF = 0;
				WriteProcessMemory(setup.handle, (LPVOID)Player.GodMode, &GodmodeOFF, sizeof(GodmodeOFF), nullptr);
			}
		}
		if (GetAsyncKeyState(VK_PRIOR) & 1)
		{
			VehGodMode = !VehGodMode;
			menu_one = !menu_one;
			if (VehGodMode)
			{
				GetCurrentVehiclePTR();
				BYTE VehGodValON = 1;

				WriteProcessMemory(setup.handle, (BYTE*)Vehicle.GodMode, &VehGodValON, sizeof(VehGodValON), nullptr);
			}
			else
			{
				!VehGodMode;
				!menu_one;
				BYTE VehGodValOFF = 0;
				WriteProcessMemory(setup.handle, (BYTE*)Vehicle.GodMode, &VehGodValOFF, sizeof(VehGodValOFF), nullptr);
			}
		}
		if (GetAsyncKeyState(VK_DELETE) & 1)
		{
			menu_one = !menu_one;
			BYTE clear_wanted = 0;
			WriteProcessMemory(setup.handle, (BYTE*)Playerinfo.Wanted_lvl, &clear_wanted, sizeof(clear_wanted), nullptr);
		}
		if (GetAsyncKeyState(VK_F3) & 1)
		{
			Readcoords();
			if (WayPointCoords.x == 64000 && WayPointCoords.y == 64000)
			{
				std::cout << "WayPoint Not Set!" << std::endl;
			}
			else
			{
				ReadProcessMemory(setup.handle, (int*)(Player.bInCar), &isinCar, sizeof(isinCar), nullptr);
				if (isinCar == 16) // Not in A Vehicle
				{
					// -215 will TP the player on ground instead of under map
					float Z_Height = -215;
					WriteProcessMemory(setup.handle, (CWorld::Map::WaypointCoords*)(Player.Position), &WayPointCoords, sizeof(WayPointCoords), nullptr);
					WriteProcessMemory(setup.handle, (PFLOAT*)(Player.Position + 0x8), &Z_Height, sizeof(Z_Height), nullptr);
					WriteProcessMemory(setup.handle, (CWorld::Map::WaypointCoords*)(Player.Camera_Coords), &WayPointCoords, sizeof(WayPointCoords), nullptr);
					WriteProcessMemory(setup.handle, (PFLOAT*)(Player.Camera_Coords + 0x8), &Z_Height, sizeof(Z_Height), nullptr);
					menu_one = !menu_one;
				}
				else
				{
					// -215 will TP the player on ground instead of under map
					float Z_Height = -255;
					GetCurrentVehiclePTR();
					WriteProcessMemory(setup.handle, (CWorld::Map::WaypointCoords*)(Vehicle.Position), &WayPointCoords, sizeof(WayPointCoords), nullptr);
					WriteProcessMemory(setup.handle, (PFLOAT*)(Vehicle.Position + 0x8), &Z_Height, sizeof(Z_Height), nullptr);
					WriteProcessMemory(setup.handle, (CWorld::Map::WaypointCoords*)(Vehicle.Camera_Coords), &WayPointCoords, sizeof(WayPointCoords), nullptr);
					WriteProcessMemory(setup.handle, (PFLOAT*)(Vehicle.Camera_Coords + 0x8), &Z_Height, sizeof(Z_Height), nullptr);
					menu_one = !menu_one;
				}
			}
		}
		if (GetAsyncKeyState(VK_F4) & 1)
		{
			ReadProcessMemory(setup.handle, (int*)(Player.bInCar), &isinCar, sizeof(isinCar), nullptr);
			if (isinCar == 0)
			{
				menu_one = !menu_one;
				Max_Tune_Car();
			}
			else
			{
				std::cout << "Not In A Vehicle!" << std::endl;
			}
		}
		if (GetAsyncKeyState(VK_F5) & 1)
		{
			menu_one = !menu_one;
			Speed_Modify += 1;
			Speed_Value_Show += 1;
			WriteProcessMemory(setup.handle, (PFLOAT*)Playerinfo.Run_Speed, &Speed_Modify, sizeof(Speed_Modify), nullptr);

			if (Speed_Modify > 5)
			{
				Speed_Modify = 1;
				Speed_Value_Show = 1;
				WriteProcessMemory(setup.handle, (PFLOAT*)Playerinfo.Run_Speed, &Speed_Modify, sizeof(Speed_Modify), nullptr);
			}
		}
		if (GetAsyncKeyState(VK_F6) & 1)
		{
			menu_one = !menu_one;
			Swim_modify += 1;
			Swim_value_show += 1;
			WriteProcessMemory(setup.handle, (PFLOAT*)Playerinfo.Swim_Speed, &Swim_modify, sizeof(Swim_modify), nullptr);

			if (Swim_modify > 5)
			{
				Swim_modify = 1;
				Swim_value_show = 1;
				WriteProcessMemory(setup.handle, (PFLOAT*)Playerinfo.Swim_Speed, &Swim_modify, sizeof(Swim_modify), nullptr);
			}
		}
		if (GetAsyncKeyState(VK_F10) & 1)
		{
			menu_one = !menu_one;
			bOffTheRadar = !bOffTheRadar;
			if (bOffTheRadar)
			{
				Undead_off_Radar(bOffTheRadar); // on
			}
			else
			{
				!menu_one;
				!bOffTheRadar;
				Undead_off_Radar(bOffTheRadar); // off
			}
		}
		if (GetAsyncKeyState(VK_F12) & 1)
		{
			menu_one = !menu_one;
			bHandling = !bHandling;
			if (bHandling)
			{
				Perfect_Handling(bHandling);
			}
			else
			{
				!menu_one;
				!bHandling;
				Perfect_Handling(bHandling);
			}
		}
		if (GetAsyncKeyState(VK_F9) & 1)
		{
			menu_one = !menu_one;
			Readcoords();
			CREATE_AMBIENT_PICKUP(PlayerCoords.x+2.0, PlayerCoords.y, PlayerCoords.z+3.0);
		}
		if (GetAsyncKeyState(VK_END) & 1)
		{
			LSC_Sell_Car_Method(2147483647); // Max Money Amount
		}
		if (GetAsyncKeyState(VK_NEXT) & 1)
		{
			menu_one = !menu_one;
			bRPMulti = !bRPMulti;
			if (bRPMulti)
			{
				RP_Multi(true);
			}
			else
			{
				!menu_one;
				!bRPMulti;
				RP_Multi(false);
			}
		}
	}
	ExitThread(0); // Make Sure Thread Ends
	CloseHandle(setup.handle);
	CloseHandle(setup.Window);
	CloseHandle(setup.stdout_colour);
}
