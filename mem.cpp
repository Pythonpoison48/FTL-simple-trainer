#include <vector>
#include <Windows.h>
#include "pch.h"
#include <iostream>
#include <Psapi.h>
#include "proc.h"




namespace mem {//BYTE*    BYTE*
	void Patch(BYTE* dst, BYTE* src, unsigned int size)
	{
		DWORD oldprotect;
		VirtualProtect( dst, size, PAGE_EXECUTE_READWRITE, &oldprotect);
		memcpy( dst, src, size);
		VirtualProtect( dst, size, oldprotect, &oldprotect);
	}

	void Nop(BYTE* dst, unsigned int size)
	{
		BYTE* nopArray = new BYTE[size];
		memset(nopArray, 0x90, size);

		Patch(dst, nopArray, size);
		delete[] nopArray;
	}


	uintptr_t FindDMAaddy(uintptr_t ptr, std::vector<unsigned int>offsets) {

		uintptr_t addr = ptr;

		for (unsigned int i = 0; i < offsets.size(); ++i)
		{
			addr = *(uintptr_t*)addr;
			addr += offsets[i];

		}
		return addr;
	}
	bool Hook(void* toHook, void* ourFunct, int len) {
		if (len < 5) {
			return false;
		}

		DWORD curProtection;
		VirtualProtect(toHook, len, PAGE_EXECUTE_READWRITE, &curProtection);
		memset(toHook, 0x90, len);

		DWORD relativeAddress = ((DWORD)ourFunct - (DWORD)toHook) - 5;

		*(BYTE*)toHook = 0xE9;
		*(DWORD*)((DWORD)toHook + 1) = relativeAddress;

		DWORD temp;
		VirtualProtect(toHook, len, curProtection, &temp);

		return true;
	}

	
	
	MODULEINFO GetModuleInfo(char* szModule)
	{
		MODULEINFO modinfo = { 0 };
		HMODULE hModule = GetModuleHandle((LPCWSTR)szModule);
		if (hModule == 0)
			return modinfo;
		GetModuleInformation(GetCurrentProcess(), hModule, &modinfo, sizeof(MODULEINFO));
		return modinfo;
	}
	
	
