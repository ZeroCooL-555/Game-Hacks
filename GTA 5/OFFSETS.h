#pragma once


// https://www.unknowncheats.me/forum/3009463-post9648.html


#define OFFSET_PLAYER								        0x08			//playerbase
#define OFFSET_PLAYER_PED							        0x8				//playerbase
#define OFFSET_NET_PLAYER								0x1C8

#define OFFSET_ENTITY_POSBASE								0x30			//base of a structure that contains entity coords
#define	OFFSET_ENTITY_POSBASE_COS							0x20
#define	OFFSET_ENTITY_POSBASE_SIN							0x30
#define OFFSET_ENTITY_POSBASE_POS							0x50			//vector3 - PED Coords
#define OFFSET_ENTITY_POS_CAMERA							0x90			//vector3 - Camera Coords
#define OFFSET_ENTITY_HEALTH								0x0280			//entity health (except for vehicles); float cur, float max		OLD 0x280
#define OFFSET_ENTITY_HEALTH_MAX							0x2A0			//they moved this away from curHealth in 1.36 :(
#define OFFSET_ENTITY_ATTACKER								0x2A8			//base to a list of the last 3 entities that attacked the current entity
#define OFFSET_ENTITY_GOD								0x189			//godmode; on = 1, off = 0; byte


#define OFFSET_PLAYER_ARMOR								0x14E0 			//armour OLD 0x14B0
#define OFFSET_PLAYER_INFO								0x10C8			//playerInfo struct												//#define OFFSET_PLAYER_INFO								0xCD0			// OLD 0x10B8			//playerInfo struct
#define OFFSET_PED_MODEL_INFO								0x0020			// Ped model info
#define OFFSET_PLAYER_ROCKSTAR_ID							0x0070			//	ROCKSTAR ID PLAYER
#define OFFSET_PLAYER_INFO_WANTED_CAN_CHANGE				                0x71C			//fWantedCanChange
#define OFFSET_PLAYER_INFO_WANTED							0x868			//wanted level; DWORD											//#define OFFSET_PLAYER_INFO_WANTED							0x798			//wanted level; DWORD
#define	OFFSET_PLAYER_INFO_RUN_SPD							0xCD0			//run speed; def 1; float		OLD 0xE8 and 0x14C 
#define OFFSET_PLAYER_INFO_SWIM_SPD							0x150			//swim speed; def 1; float		OLD 0x148
#define OFFSET_PLAYER_INFO_FRAMEFLAGS						        0x1F9			//frame flags; DWORD			OLD 0x1F8						//#define OFFSET_PLAYER_INFO_FRAMEFLAGS						0x190			//frame flags; DWORD
#define OFFSET_PLAYER_INFO_STAMINA							0x0CD4			//fStamina, fStaminaMax			OLD 0xC00
#define OFFSET_PLAYER_MAX_STAMINA_REGEN						        0x0CD8			//	MAX STAMINA
#define OFFSET_PLAYER_VEHICLE								0xD30			//ptr to last used vehicle // OLD - 0xD28
#define OFFSET_PLAYER_NAME								0x84			//	OLD 0x7C
#define OFFSET_PLAYER_RAGDOLL								0x10B8			//byte; CPed.noRagdoll: 0x20 = off; 0x00/0x01 = on				//#define OFFSET_PLAYER_RAGDOLL								0x10A8			//byte; CPed.noRagdoll: 0x20 = off; 0x00/0x01 = on
#define OFFSET_PLAYER_SEATBELT								0xC00			//byte; CPed.seatBelt: 0xC8 = off; 0xC9 = on					//#define OFFSET_PLAYER_SEATBELT							0x13EC			//byte; CPed.seatBelt: 0xC8 = off; 0xC9 = on
#define OFFSET_PLAYER_INVEHICLE								0x1477			// 0 = in car 16 = not in car																//#define OFFSET_PLAYER_INVEHICLE								0x146B
#define OFFSET_PLAYER_INVISIBLEVEHICLE						0x2C			// 1 = Invisible 15 = Visible
#define OFFSET_PLAYER_WANTED								0x868			//	OLD 0x0848
#define OFFSET_PLAYER_STEALTH_WALK							0x016C			//	STEALTH WALK SPEED		OLD 0x168
#define OFFSET_NET_PLAYER_INFO								0xA8
#define OFFSET_PLAYER_INFO_NAME								0x84
#define OFFSET_PLAYER_INFO_NPC_IGNORE						        0x850			//npc ignore; DWORD; everyone = 0x450000;
#define OFFSET_PLAYER_WATER_PROOF							0x188			//water proof; DWORD; +0x1000000 = on
#define OFFSET_PLAYER_VEHICLE_DAMAGE_MP						        0xCFC			//super punck/kick;float;

#define OFFSET_VEHICLE_HEALTH								0x908			//vehicle health; 0.f-1000.f									//#define OFFSET_VEHICLE_HEALTH								0x84C			
#define	OFFSET_VEHICLE_HEALTH2								0x844			//vehicle health2; 0.f-1000.f
#define OFFSET_VEHICLE_HANDLING								0x938																			//#define OFFSET_VEHICLE_HANDLING								0x878
#define OFFSET_VEHICLE_HANDLING_MASS						        0xC				//fMass
#define OFFSET_VEHICLE_HANDLING_BUOYANCY					        0x40			//fBuoyancy

#define OFFSET_VEHICLE_GRAVITY								0xC5C			//fGravity														//#define OFFSET_VEHICLE_GRAVITY								0xB7C			
#define OFFSET_VEHICLE_BULLETPROOF_TIRES					        0x943			//btBulletproofTires; (btBulletproofTires & 0x20) ? true : false//#define OFFSET_VEHICLE_BULLETPROOF_TIRES					0x883			//btBulletproofTires;  (btBulletproofTires & 0x20) ? true : false
#define OFFSET_VEHICLE_HANDLING_SUSPENSION_HEIGH			                0xD0			//fSuspensionHeight
#define OFFSET_VEHICLE_HANDLING_COLISION_DAMAGE_MP			                0xF0			//fColisionDamageMult
#define OFFSET_VEHICLE_HANDLING_WEAPON_DAMAGE_MP			                0xF4			//fWeaponDamageMult
#define OFFSET_VEHICLE_HANDLING_DOWNSHIFT					        0x5C
#define OFFSET_VEHICLE_HANDLING_HANDBRAKEFORCE				                0x7C			//fHandbrakeForce
#define OFFSET_VEHICLE_HANDLING_ENGINE_DAMAGE_MP			                0xFC			//fEngineDamageMult
#define OFFSET_VEHICLE_HANDLING_ACCELERATION				                0x4C
#define OFFSET_VEHICLE_HANDLING_BRAKEFORCE					        0x6C
#define OFFSET_VEHICLE_HANDLING_TRACTION_CURVE_LEFT			                0x90			//fTractionCurveMin
#define OFFSET_VEHICLE_HANDLING_TRACTION_CURVE_RIGHT						0x88			//flTractionCurveMax
#define OFFSET_VEHICLE_HANDLING_DEFORM_MULTIPLIER			                0xF8			//fDeformationDamageMult
#define OFFSET_VEHICLE_HANDLING_UPSHIFT						        0x58
#define OFFSET_VEHICLE_HANDLING_SUSPENSION_FORCE			                0xBC			//fSuspensionForce 
#define OFFSET_VEHICLE_BOOST								0x320			//fBoost
#define OFFSET_VEHICLE_RECHARGE_SPEED						        0x324			//fRocketRechargeSpeed
#define OFFSET_VEHICLE_MISSLES								0x1280			//btVehicleMissles
#define OFFSET_VEHICLE_BOMBS								0x1294			//btAircraftBombs
#define OFFSET_VEHICLE_COUNTERMEASURES						        0x1298			//btAircraftCountermeasures
#define OFFSET_VEHICLE_MK2_MISSLES							0x1284			//btOppressorMK2Misseles
#define OFFSET_VEHICLE_TAMPA_MISSLES						        0x127C			//btTampaMissles
#define	OFFSET_VEHICLE_CUSTOM								0x48
#define	OFFSET_VEHICLE_CUSTOM_EMS							0x3D6			//btEngineManagementSystem; 0x3 = max
#define	OFFSET_VEHICLE_CUSTOM_BRAKES						        0x3D7			//btBrakes; 0x6 = max
#define	OFFSET_VEHICLE_CUSTOM_TRANSMISSION					        0x3D8			//btTransmission; 0x8 = max
#define	OFFSET_VEHICLE_CUSTOM_SUSPENSION					        0x3DA			//btSuspension; 0x1B = max
#define	OFFSET_VEHICLE_CUSTOM_ARMOR							0x3DB			//btArmor; 0x1B = max
#define	OFFSET_VEHICLE_CUSTOM_TURBO_TUNING					        0x3DD			//btTurboTuning; 0x1 = on
#define	OFFSET_VEHICLE_CUSTOM_NEON_LIGHT_BLUE					    0x3A2			//btNeonLightRed
#define	OFFSET_VEHICLE_CUSTOM_NEON_LIGHT_PINK					    0x3A1			//btNeonLightGreen
#define	OFFSET_VEHICLE_CUSTOM_NEON_LIGHT_RED					    0x3A0			//btNeonLightBlue
#define	OFFSET_VEHICLE_CUSTOM_NEON_LIGHTS_L					        0x402			//btNeonLightLeft; 0x0 = off; 0x1 = on
#define	OFFSET_VEHICLE_CUSTOM_NEON_LIGHTS_R					        0x403			//btNeonLightRight; 0x0 = off; 0x1 = on
#define	OFFSET_VEHICLE_CUSTOM_NEON_LIGHTS_F					        0x404			//btNeonLightFront; 0x0 = off; 0x1 = on
#define	OFFSET_VEHICLE_CUSTOM_NEON_LIGHTS_B					        0x405			//btNeonLightBack; 0x0 = off; 0x1 = on
#define	OFFSET_VEHICLE_CUSTOM_TYRE_SMOKE					        0x3DF			//btTyreSmoke; 0x1 = on
#define	OFFSET_VEHICLE_CUSTOM_TYRE_SMOKE_R					        0x3FC			//btTyreSmokeRed
#define	OFFSET_VEHICLE_CUSTOM_TYRE_SMOKE_G					        0x3FD			//btTyreSmokeGreen
#define	OFFSET_VEHICLE_CUSTOM_TYRE_SMOKE_B					        0x3FE			//btTyreSmokeBlue
#define	OFFSET_VEHICLE_CUSTOM_LIMO_WINDOWS					        0x3FF			//btLimoWindows; 0x1 = on


#define OFFSET_WEAPON_MANAGER								0x10D8			//from playerbase												//#define OFFSET_WEAPON_MANAGER								0x10C8			
#define OFFSET_WEAPON_CURRENT								0x20			//from weapon manager
#define OFFSET_WEAPON_AMMOINFO								0x60			//from weaponbase												//#define OFFSET_WEAPON_AMMOINFO								0x48			//from weaponbase
#define OFFSET_WEAPON_AMMOINFO_MAX							0x28			//ammoinfo
#define OFFSET_WEAPON_AMMOINFO_CUR_1						        0x08			//ptr lvl 1, ptr 1
#define OFFSET_WEAPON_AMMOINFO_CUR_2						        0x00			//ptr tr lvl 2, ptr 1
#define OFFSET_WEAPON_AMMOINFO_CURAMMO						        0x18			//offset to cur ammo
#define OFFSET_WEAPON_AMMOINFO_TYPE							0x0C			//offset to projectile type?
#define OFFSET_WEAPON_SPREAD								0x7C			//float set to 0												//#define OFFSET_WEAPON_SPREAD								0x5C			
#define OFFSET_WEAPON_BULLET_DMG							0xBC			//float times 10 (so when 0, it will stay 0)					//#define OFFSET_WEAPON_BULLET_DMG							0x98			
#define OFFSET_WEAPON_RELOAD_MULTIPLIER						        0x134			//float times 10												//#define OFFSET_WEAPON_RELOAD_MULTIPLIER						0x114			
#define OFFSET_WEAPON_RECOIL								0x2F4			//float set to 0												//#define OFFSET_WEAPON_RECOIL								0x2A4			
#define OFFSET_WEAPON_MODEL_HASH							0x14
#define OFFSET_WEAPON_NAME_HASH								0x10
#define OFFSET_WEAPON_RELOAD_VEHICLE						        0x130																			//#define OFFSET_WEAPON_RELOAD_VEHICLE						0x110
#define OFFSET_WEAPON_RANGE								0x28C																			//#define OFFSET_WEAPON_RANGE									0x25C
#define OFFSET_WEAPON_SPINUP								0x144																			//#define OFFSET_WEAPON_SPINUP								0x124
#define OFFSET_WEAPON_SPIN								0x148																			//#define OFFSET_WEAPON_SPIN									0x128
#define OFFSET_WEAPON_BULLET_BATCH							0x124			//dwBulletInBatch												//#define OFFSET_WEAPON_BULLET_BATCH							0x100			
#define OFFSET_WEAPON_MUZZLE_VELOCITY						        0x11C			//fMuzzleVelocity												//#define OFFSET_WEAPON_MUZZLE_VELOCITY						0xFC			
#define OFFSET_WEAPON_IMPACT_TYPE							0x20			//dwImpactType; 1: Fists,3; Bullets,5: Explosives
#define OFFSET_WEAPON_IMPACT_EXPLOSION						        0x24			//dwImpactExplosion
#define OFFSET_WEAPON_PENETRATION							0x110			//fPenetration
#define OFFSET_WEAPON_FORCE_ON_PED							0xDC			//fForceOnPed
#define OFFSET_WEAPON_FORCE_ON_VEHICLE						        0xE0			//fForceOnVehicle(Bullet Mass)
#define OFFSET_WEAPON_FORCE_ON_HELI							0xE4			//fForceOnHeli
#define OFFSET_WEAPON_BATCH_SPREAD							0x104			//fBatchSpread

#define OFFSET_TUNABLE_RP_MULTIPLIER						        0x10
#define OFFSET_TUNABLE_AP_MULTIPLIER						        0x30F80
#define OFFSET_TUNABLE_MIN_MISSION_PAYOUT					        0x4BC8			//fMinMissionPayout
#define OFFSET_TUNABLE_ANTI_IDLE_KICK1						        0x2C0			//AFK;DWORD;2000000000 = Anti idle kick
#define OFFSET_TUNABLE_ANTI_IDLE_KICK2						        0x2C8
#define OFFSET_TUNABLE_ANTI_IDLE_KICK3						        0x2D0
#define OFFSET_TUNABLE_ANTI_IDLE_KICK4						        0x2D8
#define OFFSET_TUNABLE_ORBITAL_CANNON_COOLDOWN				                0x2C188			//OrbitalCannonCooldown;DWORD
#define OFFSET_TUNABLE_BUNKER_RESEARCH						        0x29BB8			//UnlockAllBunkerResearch;DWORD
#define OFFSET_ATTACKER_DISTANCE							0x18			//changed to 0x18, from 0x10

#define OFFSET_REPLAY_PED_INTERFACE							0x18
#define OFFSET_REPLAY_PICKUP_INTERFACE						        0x20
#define OFFSET_INTERFACE_LIST								0x100
#define OFFSET_INTERFACE_CUR_NUMS							0x110
#define OFFSET_REPLAY_PICKUP_HASH							0x488
