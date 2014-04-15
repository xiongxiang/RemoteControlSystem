#include "StdAfx.h"
#include "DealConnection.h"
#include "IpRuleFile.h"
#include "SendImageThread.h"
#include "MouseKeybdEvent.h"
#include "TabConnectionDlg.h"
#include "UserFile.h"
#include "WndClassList.h"

#include "../Message/SetupMsg.h"
#include "../Message/ByteArrayMsg.h"
#include "../Message/UserMsg.h"
#include "../Message/KeyboardMsg.h"
#include "../Message/MouseMsg.h"

#include <queue>
#include <atlconv.h>


DealConnection::~DealConnection(void)
{
}

void DealConnection::Run()
{
	USES_CONVERSION;
	//TODO::这里进行单个客户端链接的消息处理

	//获取连接的客户端ip地址等信息
	TCPSocketAddress clientAddress =  this->connection.getConnectedAddress();
	string address = clientAddress.GetIPString(0);
	CString strAddress(address.c_str());
	CIpRuleFile rule;
	
	//返回对客户端ip地址验证的结果
	if (rule.GetPowerByIp(strAddress) == 0)
	{
		SetupMsg* ipPower = new SetupMsg();
		//返回0表示禁止链接
		ipPower->PacketMsg(RCS_SETUP_MSG_PERMISSION,RCS_PERMISSION_IP,0);
		connection.send(*ipPower);
		delete ipPower;
		return ;
	}
	else
	{
		SetupMsg* ipPower = new SetupMsg;
		//返回1表示允许链接
		ipPower->PacketMsg(RCS_SETUP_MSG_PERMISSION,RCS_PERMISSION_IP,1);
		//_trace(L"send ip correct\n");
		connection.send(*ipPower);
		delete ipPower;
	}

	//接收客户端的用户账号信息
	ConnectionData data;
	ByteArrayMsg *receive = new ByteArrayMsg();
	connection.receive(*receive);
	char username[20],userpwd [20];
	if(receive->GetType() ==RCS_MSG_USER )
	{
	//}
	//switch(receive->GetType())
	//{
	//case RCS_MSG_USER:
		((UserMsg*)receive)->GetUsername(username);
		((UserMsg*)receive)->GetPassword(userpwd);
		CUserFile userfile;
		SetupMsg* acount = new SetupMsg();
		int power;
		if (WndClassList::m_connectDlg->IsUserLogined(A2T(username)))
		{
			//发送2表示用户已经登录
			acount->PacketMsg(RCS_SETUP_MSG_PERMISSION,RCS_PERMISSION_CONTROL,2);
			connection.send(*acount);
			return ;
		}		
		if ( (power =userfile.GetUserPower(A2T(username),A2T(userpwd)))== -1)
		{
			//-1表示用户名密码错误
			acount->PacketMsg(RCS_SETUP_MSG_PERMISSION,RCS_PERMISSION_CONTROL,-1);
			connection.send(*acount);
			return ;
		}
		else
		{
			//否则把账号权限发送过去
			acount->PacketMsg(RCS_SETUP_MSG_PERMISSION,RCS_PERMISSION_CONTROL,power);
			//_trace(L"send account infomation\n");
			connection.send(*acount);
			data.status = power;
			//若有监控权限，则开启操作记录
			if (power == 1)
			{
				//WndClassList::m_watcher = new SystemMonitor;
				WndClassList::m_watcher->SetName(username);
				WndClassList::m_watcher->SetIp(address.c_str());
				WndClassList::m_watcher->SetFilePath("monitor.log");
				WndClassList::m_watcher->Start();
			}
		}
		
	}
	else
	{
		//_trace(L"未进行用户验证\n");
		return ;
	}

	//更新服务端连接管理界面的表格
	data.username = username;
	data.ip = strAddress;
	data.connection = &connection;
	WndClassList::m_connectDlg->AddConnection(data);
	WndClassList::m_connectDlg->UpdateList();

	//发送屏幕分辨率大小给客户端
	SetupMsg* systemMetrics = new SetupMsg;
	systemMetrics->PacketMsg(RCS_SETUP_MSG_PIXEL,GetSystemMetrics(SM_CXSCREEN),GetSystemMetrics(SM_CYSCREEN));
	connection.send(*systemMetrics);
	delete systemMetrics;

	//发送屏幕的线程
	SendImageThread sendThread;
	sendThread.SetConnection(&connection);
	sendThread.Start();

	//循环接收客户端的命令，包括鼠标、键盘、改变帧率、质量、分块等信息
	char *receiveData = new char[4096];
	ByteArrayMsg *msg = new ByteArrayMsg;
	while (connection.IsConnected())
	{
		/*std::queue<ByteArrayMsg*> msgs;
		int bytes = connection.receive(msgs);
		while (!msgs.empty())
		{
			ByteArrayMsg *msg = msgs.front();*/
		int bytes = connection.receive(receiveData,4096);
		if (bytes <=0)  //接收数据为0，表示链接出错或者已经断开
		{
			connection.disconnect();
			WndClassList::m_connectDlg->DeleteItemByConnection(&connection);
			WndClassList::m_watcher->Stop();
			break;
		}
		int iter = 0;
		while (iter<bytes)
		{
			msg->SetBuffer(receiveData+iter);
			iter+=ByteArrayMsg::GetSize(receiveData+iter,bytes-iter);
			switch(msg->GetType())
			{
			case RCS_MSG_KEYBOARD:  //键盘消息
				{
					//_trace(L"收到键盘消息\n");
					int stats = ((KeyboardMsg*)msg)->GetKeyStatus();
					int vk = ((KeyboardMsg*)msg)->GetKey();
					if (vk == RCS_KEY_TASKMGR)
					{
						WinExec("taskmgr.exe",SW_SHOW);
						break;
					}
					if (RCS_KEY_DOWN == stats)
					{
						MouseKeybdEvent::KeyDown(vk,FALSE);
					}
					else 
					{
						MouseKeybdEvent::KeyUp(vk,FALSE);
					}
				}
				break;
			case  RCS_MSG_MOUSE:  //鼠标消息
				{		
					//_trace(L"收到鼠标消息");
					int xPos =((MouseMsg*)msg)->GetMouseX();
					int yPos = ((MouseMsg*)msg)->GetMouseY();
					//SetCursorPos(xPos,yPos);
					//_trace(L"Position:%d , %d",xPos,yPos);
					int status = ((MouseMsg*)msg)->GetMouseStatus();
					switch(status)
					{
					case RCS_MOUSE_LEFT_DOWN:
						{
							//_trace(L"--->左键按下\n");
							MouseKeybdEvent::LeftClickDown(xPos,yPos);
							///mouse_event(MOUSEEVENTF_LEFTDOWN|MOUSEEVENTF_ABSOLUTE,xPos,yPos,0,0);
						}
						break;
					case  RCS_MOUSE_LEFT_UP:
						{
							//_trace(L"--->左键弹起\n");
							MouseKeybdEvent::LeftClickUp(xPos,yPos);
						}
						break;
					case RCS_MOUSE_RIGHT_DOWN:
						{
							//_trace(L"--->右键按下\n");
							MouseKeybdEvent::RightClickDown(xPos,yPos);
							
						}
						break;
					case  RCS_MOUSE_RIGHT_UP:
						{
							//_trace(L"--->右键弹起\n");
							MouseKeybdEvent::RightClickUp(xPos,yPos);
						}
						break;
					case RCS_MOUSE_RIGHT_DBLCLK:
						{
							//_trace(L"--->右键双击\n");
							MouseKeybdEvent::RightDbClick(xPos,yPos);
						}
						break;
					case  RCS_MOUSE_LEFT_DBLCLK:
						{
							//_trace(L"--->左键双击\n");
							MouseKeybdEvent::LeftDbClick(xPos,yPos);
						}
						break;
					case  RCS_MOUSE_MINDLE_DOWN:
						{
							//_trace(L"--->滚轮按下\n");
						}
						break;
					case  RCS_MOUSE_MINDLE_UP:
						{
							//_trace(L"--->滚轮弹起\n");
						}
						break;
					case RCS_MOUSE_MINDLE_DBLCLK:
						{
							//_trace(L"--->滚轮双击\n");
						}
						break;
					case 0:
						{
							//_trace(L"--->鼠标移动\n");
							SetCursorPos(xPos,yPos);
						}
					case RCS_MOUSE_WHEEL:
						{
							//_trace(L"--->鼠标滚动\n");
							int wheels = ((MouseMsg*)msg)->GetMouseStatus();
							//MouseKeybdEvent::MouseWheel(wheels);
						}
					default:
						break;
					}
				}
				break;
			case RCS_MSG_SETUP: //设置消息
				{			
					//_trace(L"收到设置消息");
					int type = ((SetupMsg*)msg)->GetStatusType();
					switch(type)
					{
					case RCS_SETUP_MSG_IMAGE_QUALITY:
						{						
							//_trace(L"--->图像质量\n");
							int quality = ((SetupMsg*)msg)->GetValue1();
							sendThread.SetImageQuality(quality);
						}
						break;
					case RCS_SETUP_MSG_TILE:
						{						
							//_trace(L"--->分块信息\n");
							int xbox = ((SetupMsg*)msg)->GetValue1();
							int ybox = ((SetupMsg*)msg)->GetValue2();
							sendThread.SetTileNumber(xbox,ybox);
						}
						break;
					case RCS_SETUP_MSG_FRAME:
						{
							//_trace(L"--->帧率\n");
							int frame = ((SetupMsg*)msg)->GetValue1();
							sendThread.SetFrame(frame);
						}
						
						break;
					}
				}
				break;
			case RCS_MSG_USER:
				//_trace(L"收到用户消息\n");
				break;
			default:
				break;
			}		
		}		
		
	}
	sendThread.WaitForEnd();
	Sleep(2000);
	//_trace(L"DealConnectionThread is end\n");
}