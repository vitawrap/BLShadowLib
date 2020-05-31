
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
// (Using fixed addresses because this version of the game allows me to...)
BL_DEFINE_NS_FUNCTION(Con, setVariable,    0x004d23a0);
BL_DEFINE_NS_FUNCTION(Con, addVariable,    0x004d25b0);
BL_DEFINE_NS_FUNCTION(Con, evaluate,       0x004d37f0);
BL_DEFINE_NS_FUNCTION(Con, printf,         0x004d35d0);
BL_DEFINE_NS_FUNCTION(Con, errorf,         0x004d3610);
BL_DEFINE_NS_FUNCTION(Sim, findObject,     0x004e13e0);

BL_DEFINE_FUNCTION(ConsoleConstructorS, 0x004d2140);
BL_DEFINE_FUNCTION(ConsoleConstructorI, 0x004d2190);
BL_DEFINE_FUNCTION(ConsoleConstructorF, 0x004d21e0);
BL_DEFINE_FUNCTION(ConsoleConstructorV, 0x004d2230);
BL_DEFINE_FUNCTION(ConsoleConstructorB, 0x004d2280);

ConsoleConstructorProxy::ConsoleConstructorProxy(LPCSTR className, LPCSTR funcName, StringCallback	sfunc, LPCSTR usage, INT32 minArgs, INT32 maxArgs)
{ConsoleConstructorS(this, className, funcName, sfunc, usage, minArgs, maxArgs);}

ConsoleConstructorProxy::ConsoleConstructorProxy(LPCSTR className, LPCSTR funcName, IntCallback		ifunc, LPCSTR usage, INT32 minArgs, INT32 maxArgs)
{ConsoleConstructorI(this, className, funcName, ifunc, usage, minArgs, maxArgs);}

ConsoleConstructorProxy::ConsoleConstructorProxy(LPCSTR className, LPCSTR funcName, FloatCallback	ffunc, LPCSTR usage, INT32 minArgs, INT32 maxArgs)
{ConsoleConstructorF(this, className, funcName, ffunc, usage, minArgs, maxArgs);}

ConsoleConstructorProxy::ConsoleConstructorProxy(LPCSTR className, LPCSTR funcName, VoidCallback	vfunc, LPCSTR usage, INT32 minArgs, INT32 maxArgs)
{ConsoleConstructorV(this, className, funcName, vfunc, usage, minArgs, maxArgs);}

ConsoleConstructorProxy::ConsoleConstructorProxy(LPCSTR className, LPCSTR funcName, BoolCallback	bfunc, LPCSTR usage, INT32 minArgs, INT32 maxArgs)
{ConsoleConstructorB(this, className, funcName, bfunc, usage, minArgs, maxArgs);}