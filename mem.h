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
	MODULEINFO GetModuleInfo(char* szModule);	
}
