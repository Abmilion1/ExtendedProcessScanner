#include <Windows.h>
#include <iostream>
#include <TlHelp32.h>
typedef enum _SECTION_INHERIT {
    ViewShare = 1,
    ViewUnmap = 2
} SECTION_INHERIT, * PSECTION_INHERIT;

typedef NTSTATUS(NTAPI* NtMapViewOfSection_)(
    HANDLE          SectionHandle,
    HANDLE          ProcessHandle,
    PVOID* BaseAddress,
    ULONG_PTR       ZeroBits,
    SIZE_T          CommitSize,
    PLARGE_INTEGER  SectionOffset,
    PSIZE_T         ViewSize,
    SECTION_INHERIT InheritDisposition,
    ULONG           AllocationType,
    ULONG           Win32Protect);
typedef NTSTATUS(NTAPI* NtUnmapViewOfSection_)(
    HANDLE ProcessHandle,
    PVOID  BaseAddress
    );

static NtMapViewOfSection_ NtMapViewOfSection = (NtMapViewOfSection_)GetProcAddress(GetModuleHandle(TEXT("ntdll.dll")), "NtMapViewOfSection");

static NtUnmapViewOfSection_ NtUnmapViewOfSection = (NtUnmapViewOfSection_)GetProcAddress(GetModuleHandle(TEXT("ntdll.dll")), "NtUnmapViewOfSection");

BOOL ScanForProcess(HANDLE hSnapshot, LPCWSTR exeName, PDWORD pdwPID);
