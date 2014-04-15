/**************************************************************************
**             Guangzhou ZHIYUAN electronics Co.,LTD
**             
**
**                   http://www.embedtools.com  
**-------------File Info---------------------------------------------------
**File Name:   SendImageThread.h
**Latest modified Data:
**Latest Version:
**Description:  
**
**-------------------------------------------------------------------------
**Create by:   魏胤
**Create date:  2013/05/03   9:07
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
#ifndef __SENDIMAGETHREAD_H__
#define __SENDIMAGETHREAD_H__

#include "../Thread/Thread.h"
#include "../Graphic/ScreenShot.h"
#include "../SocketIPv4/TcpConnection.h"
#include <queue>

class SendImageThread : public Thread
{
public:
	SendImageThread(void);
	~SendImageThread(void);

protected:
	void Run();  //线程运行函数

	/////////////////一下是截屏部分代码//////
private:
	std::queue<ByteArrayMsg*>	m_SendQueue;  //保存屏幕分块数据的队列
	ScreenShot		m_ScreenShooter; //屏幕截图对象
	int				m_Frame; //截图帧率
	TCPConnection* m_connection;
	bool Init();  
	

public:
	/**
	 * @Brief SetConnection 设置该线程所处理的连接对象
	 * @Parameter TCPConnection * _connection  连接对象指针
	 * @Returns void
	 * @Remark  
	 **/
	void SetConnection(TCPConnection* _connection);
	/**
	 * @Brief SetFrame 设置发送图片的帧率
	 * @Parameter int frame  帧率
	 * @Returns bool
	 * @Remark  
	 **/
	bool SetFrame(int frame);
	/**
	 * @Brief SetImageQuality 设置图像压缩的质量
	 * @Parameter int quality 质量值
	 * @Returns bool
	 * @Remark  
	 **/
	bool SetImageQuality(int quality);
	/**
	 * @Brief SetTileNumber  这只图像分块的数量
	 * @Parameter int Horz  横向分块数量
	 * @Parameter int Vert  纵向分块数量
	 * @Returns void
	 * @Remark  
	 **/
	void SetTileNumber(int Horz,int Vert);
};
#endif//__SENDIMAGETHREAD_H__