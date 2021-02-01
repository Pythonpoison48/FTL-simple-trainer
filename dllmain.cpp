// dllmain.cpp : Définit le point d'entrée de l'application DLL.

#include <Windows.h>
#include <iostream>
#include <TlHelp32.h>
#include "mem.h"
#include "proc.h"


/*

                unsigned char szPatch_inverser[39] = { 0x76,0x1C,0x0F,0x2E,0xEC,0xBA,0x01,0x00,0x00,0x00,0x0F,0x9A,0xC0,0x0F,0x45,0xC2,0x84,0xC0,0x74,0x0A,0xC7,0x81,0x5c, 0x01, 0x00, 0x00, 0x00, 0x00 , 0x00,0x40, 0x0F,0x2E,0xCA,0x0F,0x87, 0xE2, 0x00, 0x00, 0x00 };
                unsigned char szPatch[39] = { 0x00, 0x00, 0x00, 0xE2, 0x87, 0x0F, 0xCA, 0x2E, 0x0F, 0x40,0x00,0x00,0x00,0x00,0x00,0x01,0x5c,0x81,0xC7,0x0A,0x74,0xC0,0x84,0xC2,0x45,0x0F,0xC0,0x9A,0x0F,0x00,0x00,0x00,0x01,0xBA,0xEC,0x2E,0x0F,0x1C,0x76 };
                char Crew_health_enable = (char)"\x00\x00\x00\xE2\x87\x0F\xCA\x2E\x0F\x40\x00\x00\x00\x00\x00\x01\x5c\x81\xC7\x0A\x74\xC0\x84\xC2\x45\x0F\xC0\x9A\x0F\x00\x00\x00\x01\xBA\xEC\x2E\x0F\x1C\x76"; // nombre = 39
                unsigned char szpatch[5] = { 0xF3, 0x0F, 0x11 ,0x69 ,0x28 };
                mem::Patch((BYTE*)(hookAddress), (BYTE*)"\x76\x1C\x0F\x2E\xEC\xBA\x01\x00\x00\x00\x0F\x9A\xC0\x0F\x45\xC2\x84\xC0\x74\x0A\xC7\x81\x5c\x01\x00\x00\x00\x00\x00\x40\x0F\x2E\xCA\x0F\x87\xE2\x00\x00\x00", 39);
                */




/*
"FTLGame.exe"+6EB4A: F3 0F 2C F0                    -  cvttss2si esi,xmm0
"FTLGame.exe"+6EB4E: F3 0F 58 C2                    -  addss xmm0,xmm2
"FTLGame.exe"+6EB52: F3 0F 10 1D 10 CB 4A 01        -  movss xmm3,[FTLGame.exe+42CB10]
"FTLGame.exe"+6EB5A: F3 0F 10 61 2C                 -  movss xmm4,[ecx+2C]
"FTLGame.exe"+6EB5F: 0F 54 DA                       -  andps xmm3,xmm2
"FTLGame.exe"+6EB62: 0F 28 EC                       -  movaps xmm5,xmm4
"FTLGame.exe"+6EB65: F3 0F 5F C1                    -  maxss xmm0,xmm1
"FTLGame.exe"+6EB69: 0F 2E D9                       -  ucomiss xmm3,xmm1
"FTLGame.exe"+6EB6C: F3 0F 5D E8                    -  minss xmm5,xmm0
"FTLGame.exe"+6EB70: 0F 28 C5  code pour enlever l'injection*/ 

DWORD jmpBackAddycrew;
DWORD jmpBackAddyWeapon;


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


void __declspec() FunctWeapon() {
   
    //penser a bien ouvrir la bonne cheat table verifier l'activation des script pour savoir si c'est la bonne
    //DWORD_PTR multiplier = 1.0f;
    // tester mov xmm5, test |
    // addss xmm0, test      | deja tester
    // mettre dword ptr sur cmp (ou pas ?)
    // retester tout depuis le début parceque un reglage avait été mal fait

    /* fonction qui ne fait pas crasher le jeu et qui n'empeche pas les armes de se charger
    cmp dword ptr[esp + 410], 0x7562656E; //Blaze it. 90775A73
    jne weapon
    addss xmm0, ss: [0x50f] ;// fonctionne pas pose vraisemblablement probleme
    weapon:
    mulss xmm0, xmm1
    addss xmm0, [esi + 0x8]
    jmp[jmpBackAddyWeapon]
    */

    /*cmp dword ptr ss:[esp+0x410], 0x7562656E //Blaze it. 90775A73
        jne weapon
        addss xmm0, ds:[0x1] //dword ptr ds:[multiplier] // fonctionne pas pose vraisemblablement probleme 
        weapon:
        mulss xmm0, xmm1
        addss xmm0, dword ptr ds:[esi+8]
        jmp[jmpBackAddyWeapon]*/
     DWORD register addressregister;
    //__asm mov registerValue , dword ptr [xmm0];
    
     
    std::cout << "addressregister : " <<  &addressregister << std::endl;
    std::cout << "addressregister2 : " << addressregister << std::endl;
    Sleep(10000);

    
    __asm {
        
        
        
        


           

       
        
       
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
    std::cout << "Press F10 for" << std::endl;
    std::cout << "Press F11 for" << std::endl;
    std::cout << "Press F12 to exit" << std::endl;
    


    //get module base
    uintptr_t moduleBase = (uintptr_t)GetModuleHandle(L"FTLGame.exe");
    
    bool bHealth = false, bMoney = false, bCrew = false, bShield = false, bWeapon = false;

    //hack loop
    while (true) {
        if (GetAsyncKeyState(VK_F12) & 1) {
            break;
        }

        if (GetAsyncKeyState(VK_F1) & 1) {
            bHealth = !bHealth;
        }

        if (GetAsyncKeyState(VK_F2) & 1) {
            bMoney = !bMoney;
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
                
                //char hookAddress = 'a';//mem::ScanInternal((char*)pattern,(char*)mask,(char*)module_size.EntryPoint,hooklenght);
                //DWORD hookAddress = mem::FindPattern("FTLGame.exe", "\xCC\x0F\x11\x69\x28","xxxxx" );
                //const void* hookAddress = mem::FindPattern((const void*)module_size.EntryPoint,module_size.SizeOfImage, (const BYTE*)pattern, mask);
                std::cout << "jmpback addy" << std::endl;
                jmpBackAddycrew = hookAddress  + 0x5;
                std::cout << jmpBackAddycrew << std::endl;

                
                std::cout << "commencement hooking" << std::endl;
                std::cout << "hookadress :  " << hookAddress << " function to hook :" << Functcrew << " hooklenght " << hooklenght << std::endl;
                
                mem::Hook((void*)hookAddress,(void*)Functcrew,hooklenght);
                //mem::Patch((BYTE*)0x00E8A300, (BYTE*)"/xE9/xFB/x5C/x1E/x01/x", 5);
                //mem::PlaceJMP((BYTE*)0x00E8A300, (DWORD)Functcrew);



                std::cout << "invincibility enabled" << std::endl;  



            } //autre facon d'ecrire : \x76\x1C\x0F\x2E\xEC\xBA\x01\x00\x00\x00\x0F\x9A\xC0\x0F\x45\xC2\x84\xC0\x74\x0A\xC7\x81\x5c\x01\x00\x00\x00\x00\x00\x40\x0F\x2E\xCA\x0F\x87\xE2\x00\x00\x00
            /*
            else {
                mem::Patch((BYTE*)(moduleBase + 0x63786), (BYTE*)"",0);
            }
            */
        }

        if (GetAsyncKeyState(VK_F4) & 1) {
            uintptr_t energy_addr = mem::FindDMAaddy(moduleBase + 0x51AB20, { 0x04 });
            int* energy = (int*)energy_addr;
            *energy = 60;
        }

        if (GetAsyncKeyState(VK_F5) & 1) {
            uintptr_t fuel_addr = mem::FindDMAaddy(moduleBase + 0x0051348C, { 0x494 });
            int* fuel = (int*)fuel_addr;
            *fuel  = 99999;
        }
        if (GetAsyncKeyState(VK_F6) & 1) {
            uintptr_t missile_addr = mem::FindDMAaddy(moduleBase + 0x0005134A4, { 0x0, 0x48, 0x1E8 });
            int* missile = (int*)missile_addr;
            *missile = 99999;
        }
        if (GetAsyncKeyState(VK_F7) & 1) {
            uintptr_t Drone_part_addr = mem::FindDMAaddy(moduleBase + 0x51348C, {0x4C,0x1CC});
            int* drone_part = (int*)Drone_part_addr;
            *drone_part = 999;
            //TODO add infinite drone part
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
            bShield = !bShield;
            
            

        }
        
        if (GetAsyncKeyState(VK_MULTIPLY) & 1) {
            bWeapon = !bWeapon;
            const char* pattern_weapon = "";
            const char* pattern_unhooking = "";
            const char* mask_weapon = "";
            intptr_t scan_size = 0x46e000;
            //intptr_t scan_size = 9; pas bon (je pense)
            MODULEINFO module_info = mem::GetModuleInfo((char*)"FTLGame.exe");

            char* address_weapon = mem::ScanInternal((char*)pattern_weapon, (char*)mask_weapon, (char*)moduleBase, scan_size);
            //char* address_unhooking = mem::ScanInternal((char*)pattern_unhooking, (char*))
            jmpBackAddyWeapon = (DWORD)address_weapon + 9;
            if (bWeapon) {
                
                std::cout << address_weapon << std::endl;
                mem::Hook((void*)address_weapon, (void*)FunctWeapon, 9);
                std::cout << "hook complete" << std::endl;


            }
            else {
                std::cout << "unhooking weapon" << std::endl;
                mem::Patch((BYTE*)address_weapon, (BYTE*)pattern_unhooking, 25);
                std::cout << "unhooking terminated " << std::endl;
            }
        }
        
        if (bHealth || bMoney || bShield) {
            if (bHealth) {
                uintptr_t localPlayerPtr = mem::FindDMAaddy(moduleBase + 0x51348C, { 0xCC });
                int* ally_hull = (int*)localPlayerPtr;
                *ally_hull = 30;
                //std::cout << "Infinite life activated " << std::endl;
            }

            if (bMoney) {
                uintptr_t ammoAddr = mem::FindDMAaddy(moduleBase + 0x51348C, { 0x4D4});
                int* ammo = (int*)ammoAddr;
                *ammo = 999999;

                //std::cout << "infinite money acctivated" << std::endl;

                //or 
               //*(int*) mem::FindDMAAddy(moduleBase + 0x10f4f4, { 0x374,0x14,0x0 }) = 1337;
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

