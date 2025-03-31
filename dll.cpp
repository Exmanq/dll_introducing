#include <windows.h>

BOOL APIENTRY DllMain(HMODULE hModule, DWORD reason, LPVOID lpReserved) {
    if (reason == DLL_PROCESS_ATTACH) {
        MessageBoxW(NULL, L"DLL внедрена by eno30100!", L"Успех", MB_OK);
    }
    return TRUE;
}
