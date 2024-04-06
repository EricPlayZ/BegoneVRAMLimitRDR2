#include <pch.h>
#include "..\offsets.h"

namespace Hooks {
#pragma region VRAMCheck
	static DWORD* pVRAMUsed = nullptr;
	static DWORD* pVRAMUsed2 = nullptr;
	static DWORD* pVRAMUsedApps = nullptr;

	static bool detourVRAMCheck(LPVOID pInstance);
	static Utils::Hook::MHook<LPVOID, bool(*)(LPVOID)> VRAMCheckHook{ "VRAMCheck", &Offsets::Get_VRAMCheck, &detourVRAMCheck };

	static bool detourVRAMCheck(LPVOID pInstance) {
		const DWORD VRAMUsedOffset = *Offsets::Get_VRAMUsedOffset();
		pVRAMUsed = reinterpret_cast<DWORD*>((reinterpret_cast<DWORD64>(pInstance) + VRAMUsedOffset));
		*pVRAMUsed = 0;

		const DWORD VRAMUsed2Offset = *Offsets::Get_VRAMUsed2Offset();
		pVRAMUsed2 = reinterpret_cast<DWORD*>((reinterpret_cast<DWORD64>(pInstance) + VRAMUsed2Offset));
		*pVRAMUsed2 = 0;

		const DWORD VRAMUsedAppsOffset = *Offsets::Get_VRAMUsedAppsOffset();
		pVRAMUsedApps = reinterpret_cast<DWORD*>((reinterpret_cast<DWORD64>(pInstance) + VRAMUsedAppsOffset));
		*pVRAMUsedApps = 0;

		return VRAMCheckHook.pOriginal(pInstance);
	}
#pragma endregion

#pragma region VRAMWriteFunc
	static bool detourVRAMWriteFunc(DWORD* a1, DWORD64 a2, int a3, DWORD* a4, DWORD* a5);
	static Utils::Hook::MHook<LPVOID, bool(*)(DWORD*, DWORD64, int, DWORD*, DWORD*)> VRAMWriteFuncHook{ "VRAMWriteFunc", &Offsets::Get_VRAMWriteFunc, &detourVRAMWriteFunc };

	static bool detourVRAMWriteFunc(DWORD* a1, DWORD64 a2, int a3, DWORD* a4, DWORD* a5) {
		if (a4 == pVRAMUsed || a4 == pVRAMUsed2 || a4 == pVRAMUsedApps)
			return true;

		return VRAMWriteFuncHook.pOriginal(a1, a2, a3, a4, a5);;
	}
#pragma endregion
}