/**************************************************************************
**             Guangzhou ZHIYUAN electronics Co.,LTD
**             
**
**                   http://www.embedtools.com  
**-------------File Info---------------------------------------------------
**File Name:   MouseKeybdEvent.h
**Latest modified Data:
**Latest Version:
**Description:  
**
**-------------------------------------------------------------------------
**Create by:   魏胤
**Create date:  2013/05/03   8:44
**Version:
**Description: 
**
**
**-------------------------------------------------------------------------
**Modified by:
**Modified date:
**Version:
**Description:
**-------------------------------------------------------------------------
**Modified by:
**Modified date:
**Version:
**Description:
**
**************************************************************************/
#ifndef __MOUSEKEYBDEVENT_H__
#define __MOUSEKEYBDEVENT_H__

#include <Windows.h>

class MouseKeybdEvent
{
public:
	MouseKeybdEvent(void);
	~MouseKeybdEvent(void);

public:
	//模拟键盘的一次按键，bExtended指定是否使用扩展方式
	static void GenerateKey(int vk, BOOL bExtended);

	//模拟鼠标左键点击
	static void LeftClick(const int x,const int y);

	//模拟鼠标右键点击
	static void RightClick(const int x,const int y);

	//模拟鼠标左键双击
	static void LeftDbClick(const int x,const int y);

	//模拟鼠标右键双击
	static void RightDbClick(const int x,const int y);

	//模拟鼠标左键弹起
	static void LeftClickUp(const int x,const int y);

	//模拟鼠标左键按下
	static void LeftClickDown(const int x,const int y);
	
	//模拟鼠标右键弹起
	static void RightClickUp(const int x,const int y);

	//模拟鼠标右键按下
	static void RightClickDown(const int x,const int y);

	//模拟鼠标滚轮移动
	static void MouseWheel(const int mouseData);

	//模拟键盘按键弹起
	static void KeyUp(int vk ,BOOL bExtended);

	//模拟键盘按键按下
	static void KeyDown(int vk,BOOL bExtended);
};
#endif//__MOUSEKEYBDEVENT_H__