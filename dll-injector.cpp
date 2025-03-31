#include <stdio.h>
#include <windows.h>

int main(int argc, char *argv[]) {
    if (argc < 3) {
        printf("Usage: %s <PID> <DLL_PATH>\n", argv[0]);
        return 1;
    }

    DWORD pid = atoi(argv[1]);
    wchar_t dllPath[MAX_PATH];
    mbstowcs(dllPath, argv[2], MAX_PATH);

    HANDLE process = OpenProcess(PROCESS_ALL_ACCESS, FALSE, pid);
    if (!process) {
        printf("OpenProcess failed: %lu\n", GetLastError());
        return 1;
    }

    LPVOID remoteMem = VirtualAllocEx(process, NULL, sizeof(dllPath), MEM_COMMIT, PAGE_READWRITE);
    WriteProcessMemory(process, remoteMem, dllPath, sizeof(dllPath), NULL);

    HMODULE kernel32 = GetModuleHandleW(L"Kernel32");
    PTHREAD_START_ROUTINE loadLib = (PTHREAD_START_ROUTINE)GetProcAddress(kernel32, "LoadLibraryW");
    HANDLE thread = CreateRemoteThread(process, NULL, 0, loadLib, remoteMem, 0, NULL);

    WaitForSingleObject(thread, INFINITE);
    VirtualFreeEx(process, remoteMem, 0, MEM_RELEASE);
    CloseHandle(thread);
    CloseHandle(process);

    printf("DLL внедрена! by eno30100\n");
    return 0;
}
