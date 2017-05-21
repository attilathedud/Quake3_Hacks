/*!
*   An OpenGL wallhack for Quake3: Arena that works by disabling texture depth while drawing entities.
*
*   Originally written 2007/08/07 by attilathedud.
*/

#include <windows.h>
#include <detours.h>
#pragma comment(lib,"OpenGL32.lib")
#include <gl/gl.h>

// Current wallhack state
bool wallhackon = 0;

/*!
*   Our detoured function for draw entitites. The wallhack works by disabling texture depth while
*   drawing entities so all textures are drawn on the same z-level.
*/
void (*oridrawsprites)();
void detdrawsprites()
{
	if(GetAsyncKeyState(VK_NUMPAD1))
		wallhackon = 1;
	else if(GetAsyncKeyState(VK_NUMPAD2))
		wallhackon = 0;

	if(wallhackon == 1)
	{
		glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_BLEND);
		glDisable(GL_DEPTH_TEST);
	}
	else
	{
		glEnable(GL_DEPTH_TEST);
		glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
	}
		

	oridrawsprites();	
}

/*!
*   If we are attaching to a process, detour the draw entities function to our function and 
*   store the original function pointer in oridrawsprites.
*/
BOOL APIENTRY DllMain( HANDLE hModule, 
                       DWORD  ul_reason_for_call, 
                       LPVOID lpReserved
					 )
{
	if(ul_reason_for_call == DLL_PROCESS_ATTACH)
	{
			DetourFunction((unsigned char*)0x0044C4E0, (unsigned char*)detdrawsprites);
			__asm mov [oridrawsprites],eax;
	}
	else
		return true;

    return TRUE;
}