#include "TCPClient.h"
#include "trace.h"

// Send message depend on authority of the client
// If have no authority to control, oversee the 
// control message, include mouse and keyboard message
bool CONTROL_AUTHORITY    =  false;

TCPClient::TCPClient()
{
    m_localmutex    = new LocalMutex;
}

TCPClient::~TCPClient(void)
{
    delete m_localmutex;
}

// connect to the server
int TCPClient::Init(const string& ip, TCPSocketAddress::Port port,
                     std::queue<ByteArrayMsg *> &sendMsgQueue,
                     std::queue<ByteArrayMsg *> &recvMsgQueue) throw (TCPException)
{
    // make a connection
    WSAData wsadata;
    WSAStartup(MAKEWORD(2,2),&wsadata);
    m_socket.Open(TCPSocket::TCP);
	m_socket.SetRecvBufLength(0);
//	m_socket.SetNodelay(true);
    TCPSocketAddress *addr = new TCPSocketAddress(ip, port);
    m_socket.Connect(*addr);
    SetConnected(true);
    m_recvMsgQueue = &recvMsgQueue;
    m_sendMsgQueue = &sendMsgQueue;

    // Post user information
    int logresult = LogInConfig();

    if ((logresult == 0) || (logresult == 1))
    {
        CONTROL_AUTHORITY = (logresult == 1);
    }
    return logresult;
}

TCPSocketAddress TCPClient::GetOwnAddress() throw (TCPException)
{
    return m_socket.GetSockName();
}

void TCPClient::SendMessage() throw (TCPException)
{
    ByteArrayMsg *msg;
    bool queueempty;
    queueempty = m_sendMsgQueue->empty();

    while(!queueempty)    
    {
        AutoLock l(m_localmutex);
        
        msg = m_sendMsgQueue->front(); //Get the message from queue

        if (CONTROL_AUTHORITY)
            send(*msg);    // Send all message types
        else
        {
            if ((msg->GetType() == RCS_MSG_MOUSE) || 
                (msg->GetType() == RCS_MSG_KEYBOARD))
            {
                    ; // Do not send the control message
            }
            else
            {
                send(*msg);
            }
        }
        m_sendMsgQueue->pop();         // Delete front message
        delete msg;
        queueempty = m_sendMsgQueue->empty();
        Sleep(100);
    }
}
void TCPClient::RecvMessage()throw (TCPException)
{      
   while(TRUE)
    {
		AutoLock l(m_localmutex);
		if (receive(*m_recvMsgQueue) < 0)      
		{		   
			MessageBox(NULL,L"Á´½ÓÒÑ¶Ï¿ª£¡",L"´íÎó£¡",MB_OK);		   
			return ;		      
		}       	  
		Sleep(100);
   }
}

int TCPClient::LogInConfig()throw (TCPException)
{
    int IPresult = 0;
    if ((IPresult = IPconfig()) == 0)
    {
        return FORBIDDENIP;
    }
    
    return UserConfig();
}

int TCPClient::IPconfig()throw (TCPException)
{
    ByteArrayMsg *userconfig = new ByteArrayMsg;
    if ((receive(*userconfig)) <= 0) // If the IP is forbidden
    {
        return CONNECT_ERROR;
    }
    else
    {
        if ((((SetupMsg *)userconfig)->GetStatusType() == RCS_SETUP_MSG_PERMISSION) &&
            (((SetupMsg *)userconfig)->GetValue1() == RCS_PERMISSION_IP)) 
        {
            return ((SetupMsg *)userconfig)->GetValue2();
        }
        else
        {
            return WRONGMSGTYPE;
        }
    }
}

int TCPClient::UserConfig()throw (TCPException)
{
    // Sent use config information
    SendMessage();  

    // Receive the confirm information
    ByteArrayMsg *confirmInfo = new ByteArrayMsg;
    if((receive(*confirmInfo)) <= 0)   // Receive message wrong
    {
        return CONNECT_ERROR;
    }
    else
    {
        if ((((SetupMsg *)confirmInfo)->GetStatusType() == RCS_SETUP_MSG_PERMISSION) &&
            (((SetupMsg *)confirmInfo)->GetValue1() == RCS_PERMISSION_CONTROL)) 
        {
            return ((SetupMsg *)confirmInfo)->GetValue2();        
        }
        else
        {
            return WRONGMSGTYPE;
        }
    }    
}


void TCPClient::Start()
{
    //::_beginthread(SendThread, 0, this);
    ::_beginthread(RecvThread, 0, this);
}
void TCPClient::Close()
{
    disconnect();
}

