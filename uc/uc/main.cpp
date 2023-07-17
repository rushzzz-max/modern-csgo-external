#include <iostream>
#include <Windows.h>
#include <vector>
#include <TlHelp32.h>


#include "Driver.hpp"
#include "Offsets.hpp"

#include "Globals.hpp"
#include "Math.hpp"

#include "C_ClientState.hpp"
#include "INetworkTable.hpp"
#include "C_BasePlayer.hpp" 
#include "C_Entity.hpp"

#include "Loop.hpp"



auto main( ) -> void {
	memory->initialize( get_process( L"csgo.exe" ) );
	globals::client_dll = memory->get_module_base_x86( "client.dll" );
	std::thread( cache_loop ).detach( );
	std::thread( esp_loop ).detach( );

	std::cin.get( );
}