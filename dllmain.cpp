
#include "blv20intrn.h"
#include <stdlib.h>

// HEX ADDRESS OF smShadowMask: 0077618c
#define SMSHADOWMASK_PTR (0x0077618c)
#define FXBRICKALWAYSOBJECTTYPE 67108864
#define FXBRICKOBJECTTYPE 33554432
#define SHADOWMASK 12 | FXBRICKALWAYSOBJECTTYPE | FXBRICKOBJECTTYPE

volatile static DWORD gMaskVariable = SHADOWMASK;

/*
ConsoleFunction(resetShadowMask, void, 2, 2, "(bool shadeBricks)") {
    argc;
    bool arg = !_stricmp(argv[1], "true") || atof(argv[1]);
    DWORD mask = arg ? SHADOWMASK : 12;
    BL::write(SMSHADOWMASK_PTR, &mask);
    Con::printf("Shadowmask set to %u", mask);
}
*/

void patchShadows() {
    Con::addVariable("$Pref::Client::ShadowMask", TypeS32, (LPVOID)(SMSHADOWMASK_PTR));
    BL::write(SMSHADOWMASK_PTR, &gMaskVariable);
}

BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
                     )
{
    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:
        //BL::init(hModule);
        patchShadows();
    case DLL_THREAD_ATTACH:
    case DLL_THREAD_DETACH:
    case DLL_PROCESS_DETACH:
        break;
    }
    return TRUE;
}

