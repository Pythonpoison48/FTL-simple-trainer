#pragma once

#include <vector>
#include <iostream>
#include <windows.h>
#include <Psapi.h>
using namespace std;
namespace mem
{	
	void Patch(BYTE* dst, BYTE* src, unsigned int size);
	void Nop(BYTE* dst, unsigned int size);
	uintptr_t FindDMAaddy(uintptr_t ptr, vector<unsigned int> offsets);
	bool Hook(void* toHook, void* ourFunct, int len);
	char* ScanBasic(char* pattern, char* mask, char* begin, intptr_t size);
	char* ScanInternal(char* pattern, char* mask, char* begin, intptr_t size);
	MODULEINFO GetModuleInfo(char* szModule);
	void PlaceJMP(BYTE* Address, DWORD jumpTo, DWORD length = 5);
	//DWORD FindPattern(char *module, char *pattern, char *mask);

	const void* FindPattern(const void* StartAddress, DWORD RegionSize, const BYTE* pPattern, const char* szMask, UINT Alignment = 4, UINT Skip = 0);
	bool bCompare(const char* szMask, const BYTE* pPattern, const BYTE* pSource);
	
}