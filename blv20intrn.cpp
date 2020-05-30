
#include "blv20intrn.h"

DWORD BL::imageBase = 0;

void BL::init(HMODULE process) {
    //Retrieve information about the module
    MODULEINFO info;
    GetModuleInformation(GetCurrentProcess(), process, &info, sizeof(MODULEINFO));

    //Store relevant information
    imageBase = (DWORD)info.lpBaseOfDll;
}

// Known BL functions (defines)
BL_DEFINE_FUNCTION(Con, setVariable,    0x004d23a0);
BL_DEFINE_FUNCTION(Con, addVariable,    0x004d25b0);
BL_DEFINE_FUNCTION(Con, evaluate,       0x004d37f0);
BL_DEFINE_FUNCTION(Con, printf,         0x004d35d0);
BL_DEFINE_FUNCTION(Con, errorf,         0x004d3610);

BL_DEFINE_FUNCTION(Sim, findObject,     0x004e13e0);