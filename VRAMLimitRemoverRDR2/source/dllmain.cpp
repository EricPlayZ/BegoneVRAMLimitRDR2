#include <pch.h>

namespace Core {
    extern DWORD64 WINAPI MainThread(HMODULE hModule);
    extern void Cleanup();
}

static HANDLE hMainThread{};

BOOL APIENTRY DllMain(HMODULE hModule, DWORD64 ul_reason_for_call, LPVOID lpReserved) {
    switch (ul_reason_for_call) {
    case DLL_PROCESS_ATTACH: {
        DisableThreadLibraryCalls(hModule);
        hMainThread = CreateThread(nullptr, 0, (LPTHREAD_START_ROUTINE)Core::MainThread, hModule, 0, nullptr);

        if (!hMainThread)
            return FALSE;
        break;
    }
    case DLL_PROCESS_DETACH:
        Core::Cleanup();

        if (hMainThread)
            CloseHandle(hMainThread);
        FreeLibraryAndExitThread(hModule, 0);
        break;
    default:
        return FALSE;
    }
    return TRUE;
}