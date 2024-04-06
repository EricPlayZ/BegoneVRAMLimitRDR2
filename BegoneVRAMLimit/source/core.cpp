#include <pch.h>

namespace Core {
	DWORD64 WINAPI MainThread(HMODULE hModule) {
		MH_Initialize();

		for (auto& hook : *Utils::Hook::HookBase::GetInstances()) {
			std::thread([&hook]() {
				hook->HookLoop();
			}).detach();
		}

		const HANDLE proc = GetCurrentProcess();
		WaitForSingleObject(proc, INFINITE);

		return TRUE;
	}

	void Cleanup() {
		MH_DisableHook(MH_ALL_HOOKS);
		MH_Uninitialize();
	}
}