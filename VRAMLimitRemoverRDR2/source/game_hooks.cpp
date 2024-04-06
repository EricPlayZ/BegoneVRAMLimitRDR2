#include <pch.h>
#include "..\offsets.h"

namespace Hooks {
#pragma region VRAMCheck
	static bool detourVRAMCheck(LPVOID pInstance);
	static Utils::Hook::MHook<LPVOID, bool(*)(LPVOID)> VRAMCheckHook{ "VRAMCheck", &Offsets::Get_VRAMCheck, &detourVRAMCheck };

	static bool detourVRAMCheck(LPVOID pInstance) {
		return false;
	}
#pragma endregion
}