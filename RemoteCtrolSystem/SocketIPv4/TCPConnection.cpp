#include "TCPConnection.h"
#include "TCPStringBuffer.h"
#include "trace.h"

TCPConnection::~TCPConnection(void)
{
}

TCPConnection::TCPConnection( TCPSocket::Descriptor descriptor )
:m_socket(descriptor) ,m_iFlags(0),m_bConnected(true)
{

}

TCPConnection::TCPConnection():m_iFlags(0),m_bConnected(true)
{

}

void TCPConnection::disconnect() throw(TCPException)
{
	//_trace(L"TCPConnection::disconnect\n");
	m_socket.Close();
	m_bConnected = false;
}

bool TCPConnection::IsConnected() throw()
{
	return m_bConnected;
}

void TCPConnection::SetConnected( bool _connected ) throw()
{
	m_bConnected = _connected;
}

int TCPConnection::send( const TCPBuffer& data ) throw (TCPException)
{
	return m_socket.Send(data,m_iFlags);
}

int TCPConnection::send (ByteArrayMsg &data)throw (TCPException)
{
	//_trace(L"TCPConnection::send\n");
    return m_socket.Send(data.GetBufferPtr(), data.GetSize(), m_iFlags);
}
int TCPConnection::send (char *data, int size)throw (TCPException)
{
    return m_socket.Send(data, size);
}




int TCPConnection::receive( TCPBuffer& buffer ) throw (TCPException)
{
	return m_socket.Recv(buffer,m_iFlags);
}
int TCPConnection::receive(ByteArrayMsg& buffer) throw (TCPException)
{
    return m_socket.Recv(buffer, m_iFlags);
}
int TCPConnection::receive(char *data, int size) throw (TCPException)
{
    return m_socket.Recv(data, size, m_iFlags);
}


static int leavelenth = 0;         // remain message  buffet length
static char leavemsg[DEFAULTBUFSIZE*2]; // contain the remain buffer, that not push into the queue
int TCPConnection::receive(std::queue<ByteArrayMsg *> &msgQueue) 
{
	int  receivebyte = receive(leavemsg+leavelenth, DEFAULTBUFSIZE);

    // broke up receivebuffer onto one by one message, and push it into the message queue
    leavelenth = DealRecvbuffer(leavemsg, receivebyte, msgQueue) ; 

    return receivebyte;
}
int TCPConnection::DealRecvbuffer(char *tmpbuffer, int byte, std::queue<ByteArrayMsg *> &MsgQueue)
{
    int tmplen = byte + leavelenth;

    int msglen;
	int i = 0;
    while ((msglen = ByteArrayMsg::GetSize(tmpbuffer, tmplen)) > 0) // get the first message length
    {
        if (msglen <= tmplen)
        {
            ByteArrayMsg *msg = new ByteArrayMsg;
			msglen =  msg->SetBuffer(tmpbuffer);
			AutoLock l(&m_mLocaMutex);
            MsgQueue.push(msg);
			 ++i;
            tmplen   -= msglen;    //the left message length in buffer
            tmpbuffer += msglen;   // the left message pointer
            continue;
        }
        else
        {
            memcpy(leavemsg,tmpbuffer, tmplen );     // Save the left message data into the leavemsg
            return (tmplen);
        }
    }
	//_trace(L"接收到了一共 %d 个消息\n", i);
    return (tmplen = 0);
}

TCPConnection& TCPConnection::operator<<( const string& text ) throw(TCPException)
{
	TCPStringBuffer buffer = text;send(buffer);
	return *this;
}

void TCPConnection::operator>>( string& text ) throw(TCPException)
{
	TCPStringBuffer buffer;
	receive(buffer);
	text = buffer;
}

TCPSocketAddress TCPConnection::getConnectedAddress() throw (TCPException)
{
	return m_socket.GetPeerName();
}

void TCPConnection::SetFlags( int flags ) throw()
{
	this->m_iFlags = flags;
}
