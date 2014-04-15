#pragma once
#include "IniFile.h"

class Config
{
public:
	Config(void);
	~Config(void);

	//是否允许远程控制相关配置
	BOOL GetIsAllowControl();
	void SetIsAllowControl(BOOL isAllowControl);

	//是否开机自动运行相关配置
	BOOL GetIsAutoRun();
	void SetIsAutoRun(BOOL isAutoRun);

	//最小化到托盘
	BOOL GetIsShowInTask();
	void SetIsShowInTask(BOOL isShowInTask);

	//加密文件
	BOOL GetIsEncryptFile();
	void SetIsEncryptFile(BOOL isEncryptFile);

	//连接端口
	int GetConnectPort();
	void SetConnectPort(int port);

	//登录密码
	CString GetAdminLoginPwd();
	void SetAdminLoginPwd(CString pwd);

	//是否使用密码保护服务器端操作
	BOOL GetIsUsePwdProtection();
	void SetIsUsePwdProtection(BOOL isUsePwdProtection);


private:
	CIniFile m_DataFile;
};
