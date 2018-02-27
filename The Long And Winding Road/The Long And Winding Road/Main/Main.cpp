#include<Windows.h>
#include"Application\Application.h"

#pragma comment(lib,"imm32.lib")

int WINAPI WinMain(HINSTANCE _hInstance, HINSTANCE _hPrevInstance, LPSTR _szStr, INT _iCmdShow)
{
	::ImmDisableIME(NULL);	// IMEÇÕêÿÇ¡ÇƒÇ®Ç≠.

	return 0;
}