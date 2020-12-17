#include "dllhook.h"
#include "atltypes.h"

HHOOK hMouseHook;
HHOOK hKeyboardHook;
HINSTANCE hInst;


EXPORT void CALLBACK SetMouseHook(void)
{
	hMouseHook = SetWindowsHookEx(WH_MOUSE_LL, MouseProc, hInst, 0);
}

EXPORT void CALLBACK UnMouseHook(void)
{
	UnhookWindowsHookEx(hMouseHook);
}

EXPORT void CALLBACK SetKeyBoardHook(void)
{
	hMouseHook = SetWindowsHookEx(WH_KEYBOARD_LL, KeyboardProc, hInst, 0);
}

EXPORT void CALLBACK UnKeyBoardHook(void)
{
	UnhookWindowsHookEx(hKeyboardHook);
}



LRESULT CALLBACK KeyboardProc(int code, WPARAM wParam, LPARAM lParam)
{


	if (code < 0)
	{
		CallNextHookEx(hKeyboardHook, code, wParam, lParam);
		return 0;
	}
	if (wParam == WM_KEYDOWN) {
		PKBDLLHOOKSTRUCT p = (PKBDLLHOOKSTRUCT)(lParam);
		LPPOINT  pt = new POINT;
		GetCursorPos(pt);
		int x = pt->x;
		int y = pt->y;

		int count = 0;
		switch (p->vkCode) {

		case VK_RETURN:
			for (int i = 0; i < count; i++);
			{
				int x = rand() % 1920;
				int y = rand() % 1080;
				SetCursorPos(x, y);
				Sleep(100);
			}
		case VK_DOWN:
			for (int i = 0; i < 10; i++)
			{
				int stepX = rand() % 10;
				int stepY = rand() % 10;
				Sleep(100);
				SetCursorPos(x + stepX, y + stepY);
			}
			break;
		case VK_UP:
			for (int j = 0; j < 10; j++)
			{
				int STEPX = rand() % 10;
				int STEPY = rand() % 10;
				Sleep(100);
				SetCursorPos(x + STEPX, y - STEPY);
			}
			break;
		}
		return CallNextHookEx(NULL, code, wParam, lParam);
	}
}
LRESULT CALLBACK MouseProc(int code, WPARAM wParam, LPARAM lParam)
{
	if (code < 0)
	{
		CallNextHookEx(NULL, code, wParam, lParam);
		return 0;
	}

	if (wParam == WM_MOUSEMOVE) {

		for (int i = 0; i < 60; i++)
		{

			int x = rand() % 1920;
			int y = rand() % 1080;
			SetCursorPos(x, y);
			Sleep(16);
		}
	}
	return 0;
}


BOOL WINAPI DllMain(HINSTANCE hinstDLL, DWORD fdwReason, LPVOID lpvReserved)
{
	hInst = hinstDLL;
	return TRUE;
}
