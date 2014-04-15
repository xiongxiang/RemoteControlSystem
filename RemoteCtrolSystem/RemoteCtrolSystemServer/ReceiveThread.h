#pragma once
#include "../Thread/Thread.h"
#include "../SocketIPv4/TcpConnection.h"
#include <queue>

class ReceiveThread : public Thread
{
public:
	ReceiveThread(void);
	~ReceiveThread(void);

	void SetSendQueue(std::queue<ByteArrayMsg*>	*m_pSendQueue);
	void SetConnection(TCPConnection *_connection);

protected:
	void Run();

private:
	std::queue<ByteArrayMsg*>	*m_pSendQueue;
	TCPConnection *m_pConnection;
	
};
