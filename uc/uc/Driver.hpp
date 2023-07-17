#include <iostream>
#include <Windows.h>
#include <vector>
#include <TlHelp32.h>
#include <array>
#include <chrono>










auto get_process( LPCTSTR ProcessName ) -> uintptr_t// non-conflicting function name
{
	PROCESSENTRY32 pt;
	HANDLE hsnap = CreateToolhelp32Snapshot( TH32CS_SNAPPROCESS, 0 );
	pt.dwSize = sizeof( PROCESSENTRY32 );
	if ( Process32First( hsnap, &pt ) ) { // must call this first
		do {
			if ( !lstrcmpi( pt.szExeFile, ProcessName ) ) {
				CloseHandle( hsnap );
				return pt.th32ProcessID;
			}
		} while ( Process32Next( hsnap, &pt ) );
	}
	CloseHandle( hsnap ); // close handle on failure
	return 0;
}




