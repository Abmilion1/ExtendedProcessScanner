#include "scanner.h"
int main()
{
    //Создать снимок всех процессов запущенных в системе
    HANDLE hPID = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, NULL);
    PROCESSENTRY32W ProcEntry;
    ProcEntry.dwSize = sizeof(ProcEntry);
    DWORD dwPID = 0;
    if (ScanForProcess(hPID, L"csgo.exe",&dwPID))
    {
        MessageBox(NULL, L"Csgo found!", L"process scanner", MB_OK);
        std::cout << dwPID;
    }
    else
    {
        MessageBox(NULL, L"Csgo not found!", L"process scanner", MB_OK);
    }
    CloseHandle(hPID);
}
