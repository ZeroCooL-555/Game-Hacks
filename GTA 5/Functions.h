#pragma once

uintptr_t GetPID(const wchar_t* procName);
uintptr_t GetModuleBaseAddress(DWORD procId, const wchar_t* modName);
uintptr_t FindPTR(HANDLE hproc, uintptr_t ptr, std::vector<unsigned int>offsets);
template<typename _ret_t> _ret_t ReadMemory(HANDLE phandle, uintptr_t address);
template<typename _ret_t> void WriteMemory(HANDLE phandle, uintptr_t address, _ret_t value);
void PointerResolve(bool Version);
void Readcoords();
void GetCurrentVehiclePTR();
void Max_Tune_Car();
void Perfect_Handling(bool EnableHandling);
uintptr_t _GetGlobal(int AtIndex);
void LSC_Sell_Car_Method(int Amount);
void CREATE_AMBIENT_PICKUP(float x, float y, float z);
void Anti_Kick();
