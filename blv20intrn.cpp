
#include "blv20intrn.h"

/*
DWORD BL::imageBase = 0;

void BL::init(HMODULE module) {
    //Retrieve information about the module
    MODULEINFO info;
    GetModuleInformation(GetCurrentProcess(), module, &info, sizeof(MODULEINFO));

    //Store relevant information
    imageBase = (DWORD)info.lpBaseOfDll;
}

LPVOID BL::alloc(SIZE_T size) {
    return VirtualAllocEx(GetCurrentProcess(), NULL, size, MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE);
}

bool BL::free(LPVOID ptr) {
    return VirtualFreeEx(GetCurrentProcess(), ptr, 0, MEM_RELEASE);
}
*/

// Known BL functions (defines)
// (Using fixed addresses because this version of the game allows me to...)
BL_DEFINE_NS_FUNCTION(Con, setVariable,    0x004d23a0);
BL_DEFINE_NS_FUNCTION(Con, addVariable,    0x004d25b0);
BL_DEFINE_NS_FUNCTION(Con, evaluate,       0x004d37f0);
BL_DEFINE_NS_FUNCTION(Con, printf,         0x004d35d0);
BL_DEFINE_NS_FUNCTION(Con, errorf,         0x004d3610);
BL_DEFINE_NS_FUNCTION(Sim, findObject,     0x004e13e0);

BL_DEFINE_NS_FUNCTION(Con, addCommandS, 0x004d9190);
BL_DEFINE_NS_FUNCTION(Con, addCommandI, 0x004d91e0);
BL_DEFINE_NS_FUNCTION(Con, addCommandF, 0x004d9280);
BL_DEFINE_NS_FUNCTION(Con, addCommandV, 0x004d9230);
BL_DEFINE_NS_FUNCTION(Con, addCommandB, 0x004d92d0);

// First make a fancy overload
VOID Con::addCommand(LPCSTR className, LPCSTR funcName, StringCallback	sfunc, LPCSTR usage, INT32 minArgs, INT32 maxArgs)
{
    Con::addCommandS(className, funcName, sfunc, usage, minArgs, maxArgs);
}

VOID Con::addCommand(LPCSTR className, LPCSTR funcName, IntCallback		ifunc, LPCSTR usage, INT32 minArgs, INT32 maxArgs)
{
    Con::addCommandI(className, funcName, ifunc, usage, minArgs, maxArgs);
}

VOID Con::addCommand(LPCSTR className, LPCSTR funcName, FloatCallback	ffunc, LPCSTR usage, INT32 minArgs, INT32 maxArgs)
{
    Con::addCommandF(className, funcName, ffunc, usage, minArgs, maxArgs);
}

VOID Con::addCommand(LPCSTR className, LPCSTR funcName, VoidCallback	vfunc, LPCSTR usage, INT32 minArgs, INT32 maxArgs)
{
    Con::addCommandV(className, funcName, vfunc, usage, minArgs, maxArgs);
}

VOID Con::addCommand(LPCSTR className, LPCSTR funcName, BoolCallback	bfunc, LPCSTR usage, INT32 minArgs, INT32 maxArgs)
{
    Con::addCommandB(className, funcName, bfunc, usage, minArgs, maxArgs);
}

// Make a fancy static constructor overload too
ConsoleConstructor::ConsoleConstructor(LPCSTR className, LPCSTR funcName, StringCallback	sfunc, LPCSTR usage, INT32 minArgs, INT32 maxArgs)
{
    Con::addCommandS(className, funcName, sfunc, usage, minArgs, maxArgs);
}

ConsoleConstructor::ConsoleConstructor(LPCSTR className, LPCSTR funcName, IntCallback		ifunc, LPCSTR usage, INT32 minArgs, INT32 maxArgs)
{
    Con::addCommandI(className, funcName, ifunc, usage, minArgs, maxArgs);
}

ConsoleConstructor::ConsoleConstructor(LPCSTR className, LPCSTR funcName, FloatCallback	    ffunc, LPCSTR usage, INT32 minArgs, INT32 maxArgs)
{
    Con::addCommandF(className, funcName, ffunc, usage, minArgs, maxArgs);
}

ConsoleConstructor::ConsoleConstructor(LPCSTR className, LPCSTR funcName, VoidCallback	    vfunc, LPCSTR usage, INT32 minArgs, INT32 maxArgs)
{
    Con::addCommandV(className, funcName, vfunc, usage, minArgs, maxArgs);
}

ConsoleConstructor::ConsoleConstructor(LPCSTR className, LPCSTR funcName, BoolCallback	    bfunc, LPCSTR usage, INT32 minArgs, INT32 maxArgs)
{
    Con::addCommandB(className, funcName, bfunc, usage, minArgs, maxArgs);
}