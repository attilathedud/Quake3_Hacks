/*!
*	A multihack for Quake 3: Arena featuring a wallhack, mist removal, and no sky. Includes 
*	header entries that make it easy to add various wireframe modes.
*
*	Originally written 2007/03/29 by attilathedud.
*/
#define WIN32_LEAN_AND_MEAN

#include <windows.h>
#include "quake3dLampsHade.h"

/*!
*	Given an address and array of bytes, set the value at that address to the bytes.
*
*	address: 	The address to modify.
*	ninfo:		Collection of bytes to write.
*	size:		Amount of bytes in ninfo.
*/
void patch(unsigned char* address, unsigned char ninfo[], int size)
{
	DWORD hold;

	VirtualProtect(address, size, PAGE_EXECUTE_READWRITE, &hold);
	for(int i = 0; i< size; i++)
		address[i] = ninfo[i];
	VirtualProtect(address, size, hold, NULL);
}

/*!
*	Thread injected inside the process. On init, removes mist, enables wallhack, and then starts
*	listening for numpad 1 to toggle the sky removal.
*/
DWORD WINAPI patchcall()
{
	// Remove mist
	patch(rclear, nop2, sizeof(nop2));

	// Invert the draw world and draw entities calls so that entities are drawn on top of walls
	patch(drawworld, switchdw, sizeof(switchdw));
	patch(basicwalls, switchbw, sizeof(switchbw));	

	// Listen for our hotkey and nop the sky render depending on toggle.
	// Note that toggling too quickly will cause Quake 3 to crash due to multiple writes to the same address.
	while(true)
	{
		while(!(GetAsyncKeyState(VK_NUMPAD1))) Sleep(1000);
			if(ssky == true)
				ssky = false;
			else
				ssky = true;

		if(ssky == true)
			patch(sky, nop2, sizeof(nop2));
		else if(ssky == false)
			patch(sky, regsky, sizeof(regsky));
	}
		
	return 0;
}

// On injection, create our thread.
BOOL APIENTRY DllMain( HANDLE hModule, 
                       DWORD  ul_reason_for_call, 
                       LPVOID lpReserved
					 )
{	
		if (ul_reason_for_call == DLL_PROCESS_ATTACH) 
		{ 
			CreateThread(
				NULL,
				NULL,
				(LPTHREAD_START_ROUTINE)patchcall,
				NULL,
				NULL,
				NULL
				); 
		}

		else
			return TRUE;
		

    return TRUE;
}


