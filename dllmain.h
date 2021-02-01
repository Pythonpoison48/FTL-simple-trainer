#pragma once

DWORD __stdcall HackThread(HMODULE hModule) {
    // Create console
    AllocConsole();
    FILE* f;
    freopen_s(&f, "CONOUT$", "w", stdout);


    //get module base
    uintptr_t moduleBase = (uintptr_t)GetModuleHandle(L"FTLGame.exe");

    bool bHealth = false, bMoney = false, bRecoil = false;

    //hack loop
    while (true) {
        if (GetAsyncKeyState(VK_END) & 1) {
            break;
        }

        if (GetAsyncKeyState(VK_NUMPAD1) & 1) {
            bHealth = !bHealth;
        }

        if (GetAsyncKeyState(VK_NUMPAD2) & 1) {
            bMoney = !bMoney;
        }

        if (GetAsyncKeyState(VK_NUMPAD3) & 1) {
            bRecoil = !bRecoil;
            /*
            if (bRecoil) {
            mem::Nop((BYTE*)(moduleBase + 0x63786), 10);
            }
            else {
            mem::Patch((BYTE*)(moduleBase + 0x63786), (BYTE*)"\x50\x8d\x4c\x24\x1c\x51\x8b\xce\xff\xd2",10);
            }
            */;
        }

        uintptr_t* localPlayerPtr = (uintptr_t*)(moduleBase);

        if (localPlayerPtr) {
            if (bHealth) {
                *(int*)(localPlayerPtr + 0x51348C) = 30;
            }

            if (bMoney) {
                uintptr_t ammoAddr = FindDMAAddy(moduleBase + 0x51348C, { 0x4D4 });
                int* ammo = (int*)ammoAddr;
                *ammo = 999999;

                //or 
                //*(int*) mem::FindDMAAddy(moduleBase + 0x10f4f4, { 0x374,0x14,0x0 }) = 1337;
            }

        }
        Sleep(5);
    }
    fclose(f);
    FreeConsole();
    FreeLibraryAndExitThread(hModule, 0);

    return 0;

    //Key input 


    //continus write/freeze


    //cleanup inject
}
