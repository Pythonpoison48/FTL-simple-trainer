

#include <Windows.h>
#include <iostream>
#include <TlHelp32.h>
#include "mem.h"
#include "proc.h"
#include "classe_reclass.h"


/
DWORD jmpBackAddycrew;
DWORD jmpBackAddyWeapon;
//ORD_PTR multiplier = 0x000007D0;

void __declspec(naked) Functcrew() {
    __asm {

    
         cmp[ecx + 0x4], 0x0
         je return 
         movss[ecx + 0x28], xmm5
         jmp return
         jmp [jmpBackAddycrew] 
    return:
       jmp [jmpBackAddycrew]
    }
}



DWORD WINAPI HackThread(HMODULE hModule) {
    // Create console
    AllocConsole();
    FILE* f;
    freopen_s(&f, "CONOUT$", "w", stdout);
    std::cout << "Welcome to my cheat for FTL :" << std::endl;
    std::cout << "Press F1 for infinite health" << std::endl;
    std::cout << "Press F2 for infinite money" << std::endl;
    std::cout << "Press F3 for infinite crew health" << std::endl;
    std::cout << "Press F4 for infinite energy" << std::endl;
    std::cout << "Press F5 for infinite fuel" << std::endl;
    std::cout << "Press F6 for infinite missile" << std::endl;
    std::cout << "Press F7 for infinite Drone part" << std::endl;
    std::cout << "Press F8 to destroy enemy ship " << std::endl;
    std::cout << "Press F9 for infinite weapon energy" << std::endl;
    std::cout << "Press F10 for instantly refill ftl charge" << std::endl;
    std::cout << "press insert to kill enemy crew" << std::endl;
    std::cout << "Press F12 to exit" << std::endl;
    


    //get module base
    uintptr_t moduleBase = (uintptr_t)GetModuleHandle(L"FTLGame.exe");
    
    bool bHealth = false, bCrew = false;
    entList_class* entlistclass = *(entList_class**)(moduleBase + 0x514E4C);
    Local_Player* LocalPlayerClass = *(Local_Player**)(moduleBase + 0x51348C);
    
    //hack loop
    while (true) {
        if (GetAsyncKeyState(VK_F12) & 1) {
            break;
        }

        if (GetAsyncKeyState(VK_F1) & 1) {
            bHealth = !bHealth;
        }

        if (GetAsyncKeyState(VK_F2) & 1) {
            LocalPlayerClass->scrap = 99999;
        }

        if (GetAsyncKeyState(VK_F3) & 1) {
            bCrew = !bCrew;
            

            if (bCrew) {
                const char* pattern = "\xCC\x0F\x11\x69\x28";
                const char* mask = "xxxxx";
                const char* begin = "0x751000";
                intptr_t hooklenght = 0x5;
                MODULEINFO module_size = mem::GetModuleInfo((char*)"FTLGame.exe");
                DWORD hookAddress = moduleBase + 0x7A300;
                
                std::cout << "jmpback addy" << std::endl;
                jmpBackAddycrew = hookAddress  + 0x5;
                std::cout << jmpBackAddycrew << std::endl;

                
                std::cout << "commencement hooking" << std::endl;
                std::cout << "hookadress :  " << hookAddress << " function to hook :" << Functcrew << " hooklenght " << hooklenght << std::endl;
                
                mem::Hook((void*)hookAddress,(void*)Functcrew,hooklenght);
                



                std::cout << "invincibility enabled" << std::endl;  



            } 
        }

        if (GetAsyncKeyState(VK_F4) & 1) {
            uintptr_t energy_addr = mem::FindDMAaddy(moduleBase + 0x51AB20, { 0x04 });
            int* energy = (int*)energy_addr;
            *energy = 60;
        }

        if (GetAsyncKeyState(VK_F5) & 1) {
            LocalPlayerClass->fuel = 9999;
        }
        if (GetAsyncKeyState(VK_F6) & 1) {
            uintptr_t missile_addr = mem::FindDMAaddy(moduleBase + 0x0005134A4, { 0x0, 0x48, 0x1E8 });
            int* missile = (int*)missile_addr;
            *missile = 99999;
        }
        if (GetAsyncKeyState(VK_F7) & 1) {
            LocalPlayerClass->drones = 9999;



           
        }

        if (GetAsyncKeyState(VK_F8) & 1) {
            uintptr_t enemy_hull_life_addr = mem::FindDMAaddy(moduleBase + 0x00514E4C, { 0x0 ,0x1C8 ,0x128 ,0x118, 0xC4 , 0xD8 ,0xCC });
            int* enemy_hull = (int*)enemy_hull_life_addr;
            *enemy_hull = 0;
        }
        if (GetAsyncKeyState(VK_F9) & 1) {
            uintptr_t weapon_energy_addr = mem::FindDMAaddy(moduleBase + 0x51348C, { 0x48, 0x54 });
            int* weapon_energy = (int*)weapon_energy_addr;
            *weapon_energy = 30;
        }

        if (GetAsyncKeyState(VK_F10) & 1) {
            LocalPlayerClass->ftl_drive = LocalPlayerClass->ftl_drive_max;
            

        }

        if (GetAsyncKeyState(VK_INSERT) & 1 ){
            
            for (auto e : entlistclass->EntList) {
                if (IsBadReadPtr(e ,sizeof(e))){
                    break;
                }
                if (e->is_enemy) {
                    e->health = 0;
                }
                else {
                    std::cout << "not an enemy" << std::endl;
                }
            }
        }

        
       
        
        if (bHealth ||  bShield ) {
            if (bHealth) {
                LocalPlayerClass->health = 30;
                //std::cout << "Infinite life activated " << std::endl;
            }

            
            if (bShield) {
                uintptr_t shield_power_addr = mem::FindDMAaddy(moduleBase + 0x51348C, { 0x44 ,0x1F0 });
                int* shield_power = (int*)shield_power_addr;
                *shield_power = 5;
            }


        }
        Sleep(100);
    }
    fclose(f);
    FreeConsole();
    FreeLibraryAndExitThread(hModule, 0);

    return 0;

    //Key input 


    //continus write/freeze


    //cleanup inject
}
BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
                     )
{
    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH: {
        CloseHandle(CreateThread(nullptr, 0, (LPTHREAD_START_ROUTINE)HackThread, hModule, 0, nullptr));

    }
    case DLL_THREAD_ATTACH:
    case DLL_THREAD_DETACH:
    case DLL_PROCESS_DETACH:
        break;
    }
    return TRUE;
}

