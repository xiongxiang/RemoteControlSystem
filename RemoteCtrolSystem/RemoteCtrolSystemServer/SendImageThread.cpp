#include "StdAfx.h"
#include "SendImageThread.h"
#include "WndClassList.h"

#include "../SocketIPv4/trace.h"
#include "../Message/SetupMsg.h"

SendImageThread::SendImageThread(void)
{
	Init();
}

SendImageThread::~SendImageThread(void)
{
}

bool SendImageThread::SetFrame( int frame )
{
	m_Frame = frame;
	return false;
}

void SendImageThread::Run()
{
	BOOL isNeedEdn = FALSE;
	while (isNeedEdn == FALSE)
	{
		
		m_ScreenShooter.ShotScreenImage(&m_SendQueue);
		//若服务端屏幕分辨率改变，则发送消息客户端
		if(m_ScreenShooter.IsPixelChange())
		{
			SetupMsg* systemMetrics = new SetupMsg;
			systemMetrics->PacketMsg(RCS_SETUP_MSG_PIXEL,GetSystemMetrics(SM_CXSCREEN),GetSystemMetrics(SM_CYSCREEN));
			m_connection->send(*systemMetrics);
			delete systemMetrics;
		}
		//图片队列不为空，则从队列中取出图片发送
		//_trace(L"frame %d\n",m_Frame);
		while (!m_SendQueue.empty())
		{
			ByteArrayMsg* curMessage = m_SendQueue.front();
			m_SendQueue.pop();
			//_trace(L"Send imag Thread::%d\n",GetThreadID());
			//_trace(L"Send size : %d\n",curMessage->GetSize());
			if (m_connection->IsConnected())
			{
				int bytes = m_connection->send(*curMessage);
				delete curMessage;
				if (bytes< 0)  //说明链接出错或者链接已断开
				{
					m_connection->disconnect();
					WndClassList::m_connectDlg->DeleteItemByConnection(m_connection);
					WndClassList::m_watcher->Stop();
					isNeedEdn = TRUE;
					break;
				}
			}
			else
			{
				delete curMessage;
				isNeedEdn = TRUE;
				break;
			}
			
			//connection.send("helloworld", 10);
		}
		Sleep(1000 / m_Frame);
	}
	//_trace(L"SendImageThread is end\n");
}

bool SendImageThread::Init()
{
	m_ScreenShooter.Init(15,15);
	m_Frame = 10;
	return SetFrame(m_Frame);
}

void SendImageThread::SetConnection( TCPConnection* _connection )
{
	m_connection = _connection;
}

bool SendImageThread::SetImageQuality( int quality )
{
	return m_ScreenShooter.SetQuality(quality);
}

void SendImageThread::SetTileNumber(int Horz,int Vert )
{
	m_ScreenShooter.Init(Horz,Vert);
}
