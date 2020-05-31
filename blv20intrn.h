#pragma once

#ifndef _BLV20INTRN_H
#define _BLV20INTRN_H

#include "framework.h"

// BL v20 DLL utility toolkit by vitawrap

namespace BL {
	extern DWORD imageBase;

	VOID init(HMODULE);

	template <typename T>
	SIZE_T write(DWORD, T const*);
}

template<typename T> SIZE_T BL::write(DWORD address, T const* data) {

	DWORD oldProtection;
	VirtualProtect((LPVOID)(imageBase + address), sizeof(T), PAGE_EXECUTE_READWRITE, &oldProtection);

	SIZE_T bwritten = 0;
	WriteProcessMemory(GetCurrentProcess(), (LPVOID)address, (LPCVOID)data, sizeof(T), &bwritten);

	VirtualProtect((LPVOID)(imageBase + address), sizeof(T), oldProtection, &oldProtection);

	return bwritten;
}

// Macros
#define BL_DECLARE_NAMESPACE(name) namespace name // Used to declare namespaced functions
#define BL_DECLARE_FUNCTION(ret, name, args) typedef ret (__cdecl *name##Proc) args; extern name##Proc name;
#define BL_DECLARE_METHOD(ret, name, args) typedef ret (__thiscall *name##Proc) args; extern name##Proc name;
#define BL_DEFINE_FUNCTION(name, addr) name##Proc name = (name##Proc)(BL::imageBase + (DWORD)(addr))
#define BL_DEFINE_NS_FUNCTION(ns, name, addr) ns::name##Proc ns::name = (ns::name##Proc)(BL::imageBase + (DWORD)(addr))

#define TypeS32			4
#define TypeBool		6
#define TypeF32			8
#define TypeString		10
#define TypeCaseString	11

// Known BL functions
BL_DECLARE_NAMESPACE(Con) {
	BL_DECLARE_FUNCTION(VOID, setVariable, (LPCSTR name, LPCSTR value));
	BL_DECLARE_FUNCTION(BOOL, addVariable, (LPCSTR name, INT32 t, LPVOID dp));
	BL_DECLARE_FUNCTION(LPCSTR, evaluate, (LPCSTR string, BOOL echo, LPCSTR fileName));
	BL_DECLARE_FUNCTION(VOID, printf, (LPCSTR fmt, ...));
	BL_DECLARE_FUNCTION(VOID, errorf, (LPCSTR fmt, ...));
}

class ConsoleConstructorProxy;

// Dummy object typedefs
typedef LPVOID LPSimObject;
// Console constructor callback typedefs
typedef LPCSTR	(*StringCallback)(LPSimObject obj,	INT32 argc, LPCSTR argv[]);
typedef INT32	(*IntCallback)(LPSimObject obj,		INT32 argc, LPCSTR argv[]);
typedef FLOAT	(*FloatCallback)(LPSimObject obj,	INT32 argc, LPCSTR argv[]);
typedef VOID    (*VoidCallback)(LPSimObject obj,	INT32 argc, LPCSTR argv[]);
typedef bool    (*BoolCallback)(LPSimObject obj,	INT32 argc, LPCSTR argv[]);

BL_DECLARE_NAMESPACE(Sim) {
	BL_DECLARE_FUNCTION(LPSimObject, findObject, (LPCSTR name));
}

// Console constructor delegate declarations
BL_DECLARE_METHOD(ConsoleConstructorProxy*, ConsoleConstructorS, (ConsoleConstructorProxy* _this, LPCSTR className, LPCSTR funcName, StringCallback		sfunc, LPCSTR usage, INT32 minArgs, INT32 maxArgs));
BL_DECLARE_METHOD(ConsoleConstructorProxy*, ConsoleConstructorI, (ConsoleConstructorProxy* _this, LPCSTR className, LPCSTR funcName, IntCallback		ifunc, LPCSTR usage, INT32 minArgs, INT32 maxArgs));
BL_DECLARE_METHOD(ConsoleConstructorProxy*, ConsoleConstructorF, (ConsoleConstructorProxy* _this, LPCSTR className, LPCSTR funcName, FloatCallback		ffunc, LPCSTR usage, INT32 minArgs, INT32 maxArgs));
BL_DECLARE_METHOD(ConsoleConstructorProxy*, ConsoleConstructorV, (ConsoleConstructorProxy* _this, LPCSTR className, LPCSTR funcName, VoidCallback		vfunc, LPCSTR usage, INT32 minArgs, INT32 maxArgs));
BL_DECLARE_METHOD(ConsoleConstructorProxy*, ConsoleConstructorB, (ConsoleConstructorProxy* _this, LPCSTR className, LPCSTR funcName, BoolCallback		bfunc, LPCSTR usage, INT32 minArgs, INT32 maxArgs));

#define SIZEOF_CCONSTRUCTOR 0x30

class /*alignas(4)*/ ConsoleConstructorProxy {
public:
	// Used by process
	CHAR dummy[SIZEOF_CCONSTRUCTOR];

	// Used by this library
	ConsoleConstructorProxy(LPCSTR className, LPCSTR funcName, StringCallback	sfunc, LPCSTR usage, INT32 minArgs, INT32 maxArgs);
	ConsoleConstructorProxy(LPCSTR className, LPCSTR funcName, IntCallback		ifunc, LPCSTR usage, INT32 minArgs, INT32 maxArgs);
	ConsoleConstructorProxy(LPCSTR className, LPCSTR funcName, FloatCallback	ffunc, LPCSTR usage, INT32 minArgs, INT32 maxArgs);
	ConsoleConstructorProxy(LPCSTR className, LPCSTR funcName, VoidCallback		vfunc, LPCSTR usage, INT32 minArgs, INT32 maxArgs);
	ConsoleConstructorProxy(LPCSTR className, LPCSTR funcName, BoolCallback		bfunc, LPCSTR usage, INT32 minArgs, INT32 maxArgs);
};

// Yes, I really went through all this just to provide you
// with the authentic TGE ConsoleFunction macro experience
#define ConsoleFunction(name, returnType, minArgs, maxArgs, usage1)							\
	static returnType c##name(LPSimObject, INT32, LPCSTR*argv);								\
	static ConsoleConstructorProxy g##name##obj(NULL,#name,c##name,usage1,minArgs,maxArgs);	\
	static returnType c##name(LPSimObject, INT32 argc, LPCSTR*argv)

#endif //_BLV20INTRN_H