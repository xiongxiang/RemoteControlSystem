#include "StdAfx.h"
#include "ReceiveThread.h"
#include "../SocketIPv4/trace.h"
#include "../Message/MouseMsg.h"

ReceiveThread::ReceiveThread(void)
{
}

ReceiveThread::~ReceiveThread(void)
{
}

void ReceiveThread::Run()
{
	while (true)
	{
		ByteArrayMsg *msg = new ByteArrayMsg();
		m_pConnection->receive(*msg);
		switch(msg->GetType())
		{
		case RCS_MSG_KEYBOARD:
			_trace(L"收到键盘消息");
			break;
		case  RCS_MSG_MOUSE:
			_trace(L"收到鼠标消息\n");
			SetCursorPos(((MouseMsg*)msg)->GetMouseX(),((MouseMsg*)msg)->GetMouseY());

			break;
		case RCS_MSG_SETUP:
			_trace(L"收到设置消息");
			break;
		default:
			break;
		}
	}

}

void ReceiveThread::SetSendQueue( std::queue<ByteArrayMsg*> *m_pSendQueue )
{
	this->m_pSendQueue = m_pSendQueue;
}

void ReceiveThread::SetConnection( TCPConnection *_connection )
{
	m_pConnection = _connection;
}
