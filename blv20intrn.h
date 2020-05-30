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
#define BL_DEFINE_FUNCTION(name, addr) name##Proc name = (name##Proc)(BL::imageBase + (DWORD)(addr))
#define BL_DEFINE_FUNCTION(ns, name, addr) ns::name##Proc ns::name = (ns::name##Proc)(BL::imageBase + (DWORD)(addr))

#define TypeS32		4
#define TypeBool	6
#define TypeF32		8

// Known BL functions
BL_DECLARE_NAMESPACE(Con) {
	BL_DECLARE_FUNCTION(VOID, setVariable, (LPCSTR name, LPCSTR value));
	BL_DECLARE_FUNCTION(BOOL, addVariable, (LPCSTR name, INT32 t, LPVOID dp));
	BL_DECLARE_FUNCTION(VOID, printf, (LPCSTR fmt, ...));
	BL_DECLARE_FUNCTION(VOID, errorf, (LPCSTR fmt, ...));
}

#endif //_BLV20INTRN_H