#pragma once
#include "utils\memory.h"
#include "utils\sigscan.h"

#define AddOffset(name, moduleName, pattern, type, retType)\
static retType Get_## name () {\
	static retType name = NULL;\
	if (Utils::Memory::IsValidPtr(name)) return name;\
	return name=reinterpret_cast<retType>(Utils::SigScan::PatternScanner::FindPattern(moduleName, {pattern, type}));\
} 

struct Offsets {
	AddOffset(VRAMCheck, "RDR2.exe", "48 89 5C 24 ?? 55 56 57 41 54 41 55 41 56 41 57 48 8D 6C 24 ?? 48 81 EC ?? ?? ?? ?? 48 8B 1D", Utils::SigScan::PatternType::Address, LPVOID)
};

#undef AddOffset