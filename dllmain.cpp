
#include "blv20intrn.h"

// HEX ADDRESS OF smShadowMask: 0077618c
#define SMSHADOWMASK_PTR (0x0077618c)
#define FXBRICKALWAYSOBJECTTYPE 67108864
#define FXBRICKOBJECTTYPE 33554432
#define SHADOWMASK 12 | FXBRICKALWAYSOBJECTTYPE | FXBRICKOBJECTTYPE

volatile DWORD gMaskVariable = SHADOWMASK;

void patchShadows() {

    Con::addVariable("$Shadow::Mask", TypeS32, (LPVOID)SMSHADOWMASK_PTR);
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
        BL::init(hModule);
        patchShadows();
    case DLL_THREAD_ATTACH:
    case DLL_THREAD_DETACH:
    case DLL_PROCESS_DETACH:
        break;
    }
    return TRUE;
}

