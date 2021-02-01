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

	void PlaceJMP(BYTE* Address, DWORD jumpTo, DWORD length = 5)
	{
		DWORD dwOldProtect, dwBkup, dwRelAddr;

		//give that address read and write permissions and store the old permissions at oldProtection
		VirtualProtect(Address, length, PAGE_EXECUTE_READWRITE, &dwOldProtect);

		// Calculate the "distance" we're gonna have to jump - the size of the JMP instruction
		dwRelAddr = (DWORD)(jumpTo - (DWORD)Address) - 5;

		// Write the JMP opcode @ our jump position...
		*Address = 0xE9;

		// Write the offset to where we're gonna jump
		//The instruction will then become JMP ff002123 for example
		*((DWORD*)(Address + 0x1)) = dwRelAddr;

		// Overwrite the rest of the bytes with NOPs
		//ensuring no instruction is Half overwritten(To prevent any crashes)
		for (DWORD x = 0x5; x < length; x++)
			*(Address + x) = 0x90;

		// Restore the default permissions
		VirtualProtect(Address, length, dwOldProtect, &dwBkup);
	}
	
	char* ScanBasic(char* pattern, char* mask, char* begin, intptr_t size)
	{
		intptr_t patternLen = strlen(mask);

		for (int i = 0; i < size; i++)
		{
			bool found = true;
			for (int j = 0; j < patternLen; j++)
			{
				if (mask[j] != '?' && pattern[j] != *(char*)((intptr_t)begin + i + j))
				{
					found = false;
					break;
				}
			}
			if (found)
			{
				return (begin + i);
			}
		}
		return nullptr;
	}

	char* ScanInternal(char* pattern, char* mask, char* begin, intptr_t size)
	{
	    char* match{ nullptr };
		MEMORY_BASIC_INFORMATION mbi{};

		for (char* curr = begin; curr < begin + size; curr += mbi.RegionSize)
		{
			if (!VirtualQuery(curr, &mbi, sizeof(mbi)) || mbi.State != MEM_COMMIT || mbi.Protect == PAGE_NOACCESS) continue;

			match = ScanBasic(pattern, mask, curr, mbi.RegionSize);

			if (match != nullptr)
			{
				break;
			}
		}
		return match;
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
	/*
	DWORD FindPattern(char *module, char *pattern, char  *mask)
	{
		//Get all module related information
		MODULEINFO mInfo = GetModuleInfo(module);

		//Assign our base and module size
		//Having the values right is ESSENTIAL, this makes sure
		//that we don't scan unwanted memory and leading our game to crash
		DWORD base = (DWORD)mInfo.lpBaseOfDll;
		DWORD size = (DWORD)mInfo.SizeOfImage;

		//Get length for our mask, this will allow us to loop through our array
		DWORD patternLength = (DWORD)strlen(mask);

		for (DWORD i = 0; i < size - patternLength; i++)
		{
			bool found = true;
			for (DWORD j = 0; j < patternLength; j++)
			{
				//if we have a ? in our mask then we have true by default, 
				//or if the bytes match then we keep searching until finding it or not
				found &= mask[j] == '?' || pattern[j] == *(char*)(base + i + j);
			}

			//found = true, our entire pattern was found
			//return the memory addy so we can write to it
			if (found)
			{
				return base + i;
			}
		}

		return NULL;
	}*/
	
	bool bCompare(const char* szMask, const BYTE* pPattern, const BYTE* pSource)
	{
		for (; *szMask; ++szMask, ++pPattern, ++pSource)
		{
			if (*szMask == 'x' && *pPattern != *pSource)
				return false;
		}
		return true;
	}
	
	const void* FindPattern(const void* StartAddress, DWORD RegionSize, const BYTE* pPattern, const char* szMask, UINT Alignment = 4, UINT Skip = 0)
	{
		UINT Count = 0;
		const BYTE* CurrAddress = reinterpret_cast<const BYTE*>(StartAddress);
		for (; reinterpret_cast<const BYTE*>(StartAddress) + RegionSize >= CurrAddress; CurrAddress += Alignment)
		{
			if (bCompare(szMask, pPattern, CurrAddress))
			{
				if (Count == Skip)
					return CurrAddress;
				Count++;
			}
		}
		return nullptr;
	}
	
}

