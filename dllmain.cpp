
#include "pch.h"

// HEX ADDRESS OF smShadowMask: 0077618c
#define SMSHADOWMASK_PTR (0x0077618c)
#define FXBRICKALWAYSOBJECTTYPE 67108864
#define FXBRICKOBJECTTYPE 33554432
#define SHADOWMASK 12 | FXBRICKALWAYSOBJECTTYPE | FXBRICKOBJECTTYPE

void patchShadows(HMODULE blockland) {

    //Retrieve information about the module
    MODULEINFO info;
    GetModuleInformation(GetCurrentProcess(), blockland, &info, sizeof(MODULEINFO));

    //Store relevant information
    DWORD imageBase = (DWORD)info.lpBaseOfDll;

    // Patch the dword
    DWORD oldProtection;
    VirtualProtect((LPVOID)(imageBase + SMSHADOWMASK_PTR), 4, PAGE_EXECUTE_READWRITE, &oldProtection);

    DWORD mask = SHADOWMASK;
    DWORD bwritten = 0;
    WriteProcessMemory(GetCurrentProcess(), (LPVOID)SMSHADOWMASK_PTR, &mask, 4, &bwritten);

    VirtualProtect((LPVOID)(imageBase + SMSHADOWMASK_PTR), 4, oldProtection, &oldProtection);
}

BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
                     )
{
    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:
        patchShadows(hModule);
    case DLL_THREAD_ATTACH:
    case DLL_THREAD_DETACH:
    case DLL_PROCESS_DETACH:
        break;
    }
    return TRUE;
}

