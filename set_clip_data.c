#include "windows.h"
#include "stdio.h"
#include "tlhelp32.h"
#include "beacon.h"

DECLSPEC_IMPORT HGLOBAL WINAPI KERNEL32$GlobalAlloc(UINT, SIZE_T);
DECLSPEC_IMPORT LPVOID WINAPI KERNEL32$GlobalLock(HGLOBAL);
DECLSPEC_IMPORT BOOL WINAPI KERNEL32$GlobalUnlock(HGLOBAL);
DECLSPEC_IMPORT BOOL WINAPI USER32$OpenClipboard(HWND);
DECLSPEC_IMPORT HANDLE WINAPI USER32$SetClipboardData(UINT, HANDLE);
DECLSPEC_IMPORT void* __cdecl  MSVCRT$memcpy(VOID*, const VOID*, size_t);
DECLSPEC_IMPORT BOOL WINAPI USER32$EmptyClipboard();
DECLSPEC_IMPORT BOOL WINAPI USER32$CloseClipboard();
DECLSPEC_IMPORT int WINAPI KERNEL32$lstrlenA(LPCSTR);

void go(char * args, int length)
{
	datap  parser;
	char * str_arg;
	BeaconDataParse(&parser, args, length);
	str_arg = BeaconDataExtract(&parser, NULL);
	DWORD size_carac = KERNEL32$lstrlenA(str_arg) + 1;
	HGLOBAL hMem = KERNEL32$GlobalAlloc(GMEM_MOVEABLE, size_carac);
	MSVCRT$memcpy(KERNEL32$GlobalLock(hMem), str_arg, size_carac);
	KERNEL32$GlobalUnlock(hMem);
	USER32$OpenClipboard(NULL);
	USER32$EmptyClipboard();
	USER32$SetClipboardData(CF_TEXT, hMem);
	USER32$CloseClipboard();
	BeaconPrintf(CALLBACK_OUTPUT, "Clipboard content edited, you can check with dumpclip command.");	
}