/**************************************************************************
**             Guangzhou ZHIYUAN electronics Co.,LTD
**
**
**                   http://www.embedtools.com  
**-------------File Info---------------------------------------------------
**File Name:
**Latest modified Data:
**Latest Version:
**Description:
**
**-------------------------------------------------------------------------
**Create by:    xiongxiang
**Create date:
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
#ifndef __TCPCLIENT_H__
#define __TCPCLIENT_H__

#include "TCPSocket.h"
#include "TCPException.h"
#include "SocketAddress.h"
#include "TcpConnection.h"
#include "TCPStringBuffer.h"

#include "../Thread/Thread.h"
#include "../Thread/GlobalMutex.h"
#include "../Thread/LocalMutex.h"
#include "../Thread/AutoLock.h"
#include "../Message/ByteArrayMsg.h"
#include "../Message/SetupMsg.h"

#include <string>
#include <process.h>
using std::string;

const int  CONNECT_ERROR  = -999;
const int  FORBIDDENIP         = -998;
const int  WRONGMSGTYPE  = -997;


class TCPClient : public TCPConnection
{
public:
    TCPClient();
    ~TCPClient(void);
    
    /**
       @brief:Connect to the server
       @Parameter:ip server ip address
       @Parameter:port server port
       @Parameter:sendMsgQueue
       @Parameter:recvMsgQueue
       @Return:    -1  wrong code or user name
                             0  Only watch authority
                             1  Watching and Operating authority
                             FORBIDDENIP     the IP is forbidden
                             WRONGMSGTYPE   message type is wrong
    */
    int Init(const string& ip, TCPSocketAddress::Port port,
        std::queue<ByteArrayMsg *> &sendMsgQueue,
        std::queue<ByteArrayMsg *> &recvMsgQueue)throw (TCPException);
	
    /**
       @brief:GetLocalAddress
       @Return:Address
    */
    virtual TCPSocketAddress GetOwnAddress() throw (TCPException);

    /**
       @brief:Start to send and receive message
       @Return:void
    */
    virtual void Start();
    /**
       @brief:Close the connection
       @Return:void
    */
    virtual void Close();

    /**
       @brief:Thread to send message in the sending message queue
       @Parameter:void * tcpclient
       @Return:void
    */

private:
    /**
       @brief:Thread to send message from the sending message queue
       @Parameter:void * tcpclient
       @Return:void
    */
    static void SendThread(void *tcpclient)
    {
        while (true)
        {
            ((TCPClient *)tcpclient)->SendMessage();
            Sleep(100);
        }
    }
    /**
       @brief:Thread to receive message from the socket ,and put
              these message to the receiving message queue.
       @Parameter:void * tcpclient
       @Return:void
    */
    static void RecvThread(void *tcpclient)
    {
        ((TCPClient *)tcpclient)->RecvMessage();
    }

    /**
       @brief:Read out message from send message 
              queue ,and send it to server
       @Return:bool
    */
    void SendMessage(void);
    /**
       @brief:Receive message from the server and push 
              it to the received message queue
       @Return:bool
    */
    void RecvMessage(void);

    /**
       @brief:Login configuration process
       @Return:    -1 wrong code or user name
                             0 Only watch authority
                             1 Watching and Operating authority
                              FORBIDDENIP the IP is forbidden
                              WRONGMSGTYPE message type is wrong
    */
    int LogInConfig(void)throw (TCPException);

private:
    /**
       @brief:The IP status of local IP on the server
       @Return:  0 IP is forbidden
                         1 IP is Authority to land
    */
    int IPconfig(void)throw (TCPException);
    /**
       @brief:User information config
       @Return:    -1 wrong code or user name
                             0 Only watch authority
                             1 Watching and Operating authority
    */
    int UserConfig(void)throw (TCPException);

private:
    std::queue<ByteArrayMsg *> *m_sendMsgQueue;
    std::queue<ByteArrayMsg *> *m_recvMsgQueue;

    LocalMutex  *m_localmutex;
};

#endif//__TCPCLIENT_H__


