/**
 * @file Main.cpp
 * @author ulynaxes
 * 
 * @brief Перехватчик нажатий кнопок, который меняет их значения.
 * з -> Z
 * о -> O
 * в -> V
 * 
 * @version 1.0
 * @date 2022-08-05
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#include <stdio.h>
#include <tchar.h>
#include <wchar.h>

// CPP библиотека.
#include <iostream>

// Библиотеки нужные для работы с windows.
#include <Windows.h>
#include <winuser.h>


// https://docs.microsoft.com/en-us/windows/win32/api/winuser/nf-winuser-setwindowshookexa
HHOOK hHook {
	NULL 
};

enum Keys
{
	ShiftKey = 16,
	Capital = 20,
	ZKey = 90,
	OKey = 79,
	VKey = 86
};

int shift_active() 
{
	return GetKeyState(VK_LSHIFT) < 0 || GetKeyState(VK_RSHIFT) < 0;
}

int capital_active() 
{
	return (GetKeyState(VK_CAPITAL) & 1) == 1;
}

LRESULT CALLBACK KeyboardProc(
int nCode, WPARAM keyState, LPARAM keyInfo) {
    LRESULT reValue = 0;
    if (nCode < 0) {
        reValue = CallNextHookEx(hHook, nCode, keyState, keyInfo);
    }


    return reValue;
};

//https://docs.microsoft.com/en-us/previous-versions/windows/desktop/legacy/ms644984(v=vs.85)?redirectedfrom=MSDN
LRESULT CALLBACK keyboard_hook(const int code, const WPARAM wParam, const LPARAM lParam) 
{
	KBDLLHOOKSTRUCT *s = reinterpret_cast<KBDLLHOOKSTRUCT *>(lParam);

	switch (wParam)
	{
	case WM_KEYDOWN:
		char c = MapVirtualKey(s->vkCode, MAPVK_VK_TO_CHAR);
		if (c == 'c') {
			//sendinput
		}
		std::cout << c << std::endl;
		break;
	}
	return CallNextHookEx(hHook, code, wParam, lParam);
}

int main(int argc, char* argv[])
{
	hHook = SetWindowsHookEx(WH_KEYBOARD_LL, keyboard_hook, 0, 0);
	if (hHook == NULL) {
		std::cout << "Keyboard hook failed!" << std::endl;
	}

	MSG message;
	while (GetMessage(&message, NULL, NULL, NULL) > 0) {
		TranslateMessage(&message);
		DispatchMessage(&message);
	}

	UnhookWindowsHookEx(hHook);
	
    return 0;
}