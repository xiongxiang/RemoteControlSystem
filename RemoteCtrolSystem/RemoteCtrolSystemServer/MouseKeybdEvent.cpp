#include "StdAfx.h"
#include "MouseKeybdEvent.h"

MouseKeybdEvent::MouseKeybdEvent(void)
{
}

MouseKeybdEvent::~MouseKeybdEvent(void)
{
}


/**
 * @Brief 产生一个按键消息
 * @Parameter int 键的虚拟码
 * @Parameter BOOL 指定是否是扩展键
 * @Returns void
 * @Remark  
 **/
void MouseKeybdEvent::GenerateKey( int vk, BOOL bExtended )
{
	KEYBDINPUT kb = {0};
	INPUT input = {0};
	/* Generate a "key down" */
	if (bExtended) 
	{ 
		kb.dwFlags  = KEYEVENTF_EXTENDEDKEY; 
	}
	kb.wVk = vk;
	input.type = INPUT_KEYBOARD;
	input.ki = kb;
	SendInput(1, &input, sizeof(input));

	/* Generate a "key up" */
	ZeroMemory(&kb, sizeof(KEYBDINPUT));
	ZeroMemory(&input, sizeof(INPUT));
	kb.dwFlags  =  KEYEVENTF_KEYUP;
	if (bExtended) { kb.dwFlags |= KEYEVENTF_EXTENDEDKEY; }
	kb.wVk = vk;
	input.type = INPUT_KEYBOARD;
	input.ki = kb;
	SendInput(1, &input, sizeof(input));

}

void MouseKeybdEvent::LeftClick( const int x,const int y )
{
	SetCursorPos(x,y);

	INPUT Input[2];
	ZeroMemory(Input, sizeof(INPUT) * 2);
	Input[0].type = INPUT_MOUSE;
	Input[0].mi.dwFlags = MOUSEEVENTF_LEFTDOWN;

	Input[1].type = INPUT_MOUSE;
	Input[1].mi.dwFlags = MOUSEEVENTF_LEFTUP;
	SendInput(2, Input, sizeof(INPUT));
}

void MouseKeybdEvent::LeftClickDown( const int x,const int y )
{
	SetCursorPos(x,y);
	INPUT Input;
	ZeroMemory(&Input,sizeof(Input));
	Input.type = INPUT_MOUSE;
	Input.mi.dwFlags = MOUSEEVENTF_LEFTDOWN;

	SendInput(1,&Input,sizeof(INPUT));
}

void MouseKeybdEvent::LeftClickUp( const int x,const int y )
{
	SetCursorPos(x,y);
	INPUT Input;
	ZeroMemory(&Input,sizeof(Input));
	Input.type = INPUT_MOUSE;
	Input.mi.dwFlags = MOUSEEVENTF_LEFTUP;

	SendInput(1,&Input,sizeof(INPUT));
}

void MouseKeybdEvent::RightClickDown( const int x,const int y )
{
	SetCursorPos(x,y);
	INPUT Input;
	ZeroMemory(&Input,sizeof(Input));
	Input.type = INPUT_MOUSE;
	Input.mi.dwFlags = MOUSEEVENTF_RIGHTDOWN;

	SendInput(1,&Input,sizeof(INPUT));
}

void MouseKeybdEvent::RightClickUp( const int x,const int y )
{
	SetCursorPos(x,y);
	INPUT Input;
	ZeroMemory(&Input,sizeof(Input));
	Input.type = INPUT_MOUSE;
	Input.mi.dwFlags = MOUSEEVENTF_RIGHTUP;
	SendInput(1,&Input,sizeof(INPUT));
}

void MouseKeybdEvent::RightClick( const int x,const int y )
{
	SetCursorPos(x,y);

	INPUT Input[2];
	ZeroMemory(Input, sizeof(INPUT) * 2);
	Input[0].type = INPUT_MOUSE;
	Input[0].mi.dwFlags = MOUSEEVENTF_RIGHTDOWN;

	Input[1].type = INPUT_MOUSE;
	Input[1].mi.dwFlags = MOUSEEVENTF_RIGHTUP;
	SendInput(2, Input, sizeof(INPUT));
}

void MouseKeybdEvent::LeftDbClick( const int x,const int y )
{
	const double XSCALEFACTOR = 65535 / (GetSystemMetrics(SM_CXSCREEN) - 1);
	const double YSCALEFACTOR = 65535 / (GetSystemMetrics(SM_CYSCREEN) - 1);

	POINT cursorPos;
	GetCursorPos(&cursorPos);

	double cx = cursorPos.x * XSCALEFACTOR;
	double cy = cursorPos.y * YSCALEFACTOR;

	double nx = x * XSCALEFACTOR;
	double ny = y * YSCALEFACTOR;

	INPUT Input={0};
	Input.type = INPUT_MOUSE;

	Input.mi.dx = (LONG)nx;
	Input.mi.dy = (LONG)ny;

	Input.mi.dwFlags = MOUSEEVENTF_MOVE | MOUSEEVENTF_ABSOLUTE | MOUSEEVENTF_LEFTDOWN | MOUSEEVENTF_LEFTUP;

	SendInput(1,&Input,sizeof(INPUT));
	SendInput(1,&Input,sizeof(INPUT));

	Input.mi.dx = (LONG)cx;
	Input.mi.dy = (LONG)cy;

	Input.mi.dwFlags = MOUSEEVENTF_MOVE | MOUSEEVENTF_ABSOLUTE;

	SendInput(1,&Input,sizeof(INPUT));
}

void MouseKeybdEvent::RightDbClick( const int x,const int y )
{
	const double XSCALEFACTOR = 65535 / (GetSystemMetrics(SM_CXSCREEN) - 1);
	const double YSCALEFACTOR = 65535 / (GetSystemMetrics(SM_CYSCREEN) - 1);

	POINT cursorPos;
	GetCursorPos(&cursorPos);

	double cx = cursorPos.x * XSCALEFACTOR;
	double cy = cursorPos.y * YSCALEFACTOR;

	double nx = x * XSCALEFACTOR;
	double ny = y * YSCALEFACTOR;

	INPUT Input={0};
	Input.type = INPUT_MOUSE;

	Input.mi.dx = (LONG)nx;
	Input.mi.dy = (LONG)ny;

	Input.mi.dwFlags = MOUSEEVENTF_MOVE | MOUSEEVENTF_ABSOLUTE | MOUSEEVENTF_RIGHTDOWN | MOUSEEVENTF_RIGHTUP;

	SendInput(1,&Input,sizeof(INPUT));
	SendInput(1,&Input,sizeof(INPUT));

	Input.mi.dx = (LONG)cx;
	Input.mi.dy = (LONG)cy;

	Input.mi.dwFlags = MOUSEEVENTF_MOVE | MOUSEEVENTF_ABSOLUTE;

	SendInput(1,&Input,sizeof(INPUT));
}

void MouseKeybdEvent::MouseWheel( const int mouseData )
{
	INPUT Input;
	Input.type = INPUT_MOUSE;
	Input.mi.dwFlags = MOUSEEVENTF_WHEEL;
	Input.mi.mouseData = mouseData;
	Input.mi.dx = 0;
	Input.mi.dy = 0;
	SendInput(1,&Input,sizeof(INPUT));
}

void MouseKeybdEvent::KeyDown( int vk,BOOL bExtended )
{
	KEYBDINPUT kb = {0};
	INPUT input = {0};
	/* Generate a "key down" */
	if (bExtended) 
	{ 
		kb.dwFlags  = KEYEVENTF_EXTENDEDKEY; 
	}
	kb.wVk = vk;
	input.type = INPUT_KEYBOARD;
	input.ki = kb;
	SendInput(1, &input, sizeof(input));
}

void MouseKeybdEvent::KeyUp( int vk ,BOOL bExtended )
{
	KEYBDINPUT kb = {0};
	INPUT input = {0};
	/* Generate a "key down" */
	if (bExtended) 
	{ 
		kb.dwFlags  = KEYEVENTF_EXTENDEDKEY; 
	}
	kb.wVk = vk;
	kb.dwFlags = KEYEVENTF_KEYUP;
	input.type = INPUT_KEYBOARD;
	input.ki = kb;
	SendInput(1, &input, sizeof(input));
}
