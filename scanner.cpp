#include "scanner.h"
BOOL ScanForProcess(HANDLE hSnapshot, LPCWSTR exeName, PDWORD pdwPID)
{
    BOOL result = 0;
    NTSTATUS NtError;
    unsigned int index;
    char* pStruct;
    LARGE_INTEGER SectionOffset;
    SIZE_T ViewSize = 0;
    PVOID BaseAddress = 0;
    LPPROCESSENTRY32W llp;
    SectionOffset.QuadPart = 0i64;
    NtError = NtMapViewOfSection(
        hSnapshot,
        (HANDLE)-1,
        &BaseAddress,
        0,
        0,
        &SectionOffset,
        &ViewSize,
        ViewShare,
        0,
        4u);
    if (NtError < 0)
    {
        return 0;
    }
    index = *((DWORD*)BaseAddress + 9);
    while (index < *((DWORD*)BaseAddress + 1))
    {
        pStruct = (char*)BaseAddress + 556 * index + *((DWORD*)BaseAddress + 5);
        llp = reinterpret_cast<LPPROCESSENTRY32W>(pStruct);
        if (!lstrcmpW(llp->szExeFile, exeName))
        {
            result = 1;
            *pdwPID = llp->th32ProcessID;
            break;
        }
        *((DWORD*)BaseAddress + 9) = ++index;
    }


    NtUnmapViewOfSection((HANDLE)-1, BaseAddress);
    return result;
}
