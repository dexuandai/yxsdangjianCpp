/*!
* \file network_connection_handler_interface.h
* \brief  network connection message notification handler
* 
*/

#ifndef _YSX_NETWORK_CONNECTION_HANDLER_H_
#define _YSX_NETWORK_CONNECTION_HANDLER_H_
#include "ysx_sdk_def.h"
/// \brief YSX SDK Namespace
/// 
///
BEGIN_YSX_SDK_NAMESPACE
/// \����������Ϣ�ص��ӿ�
///
class IProxySettingHandler
{
public:
	virtual ~IProxySettingHandler(){};
	/// \��ȡ����Host
	virtual const wchar_t* GetProxyHost() = 0;
	/// \��ȡ����˿�
	virtual unsigned int GetProxyPort() = 0;
	/// \��ȡ��������
	virtual const wchar_t* GetProxyDescription() = 0;

	/// \�����û����������������
	virtual void InputUsernamePassword(const wchar_t* userName, const wchar_t* psw) = 0;

	/// \ȡ�������û���������
	virtual void Cancel() = 0;

};

/// \֤����֤�ص��ӿ�
///
class ISSLCertVerificationHandler
{
public:
	virtual ~ISSLCertVerificationHandler(){};

	// \��ȡ֤��䷢��˭
	virtual const wchar_t* GetCertIssuedTo() = 0;
	// \��ȡ֤��䷢��
	virtual const wchar_t* GetCertIssuedBy() = 0;
	// \��ȡ֤�����к�
	virtual const wchar_t* GetCertSerialNum() = 0;
	/// \��ȡ֤��ָ��
	virtual const wchar_t* GetCertFingerprint() = 0;
	// \���δ�SSL֤��
	virtual void Trust() = 0;
	// \�����δ�SSL֤��
	virtual void Cancel() = 0;

};

/// \���������¼��ص��ӿ�
///
class INetworkConnectionHandler
{
public:
	/// \��������Ϣ������
	virtual void onProxyDetectComplete() = 0;
	/// \�յ�����Ϣʱ��������ʾ�û����������û���������
	virtual void onProxySettingNotification(IProxySettingHandler* handler) = 0;
	/// \�յ�����Ϣʱ��������ʾ�û�����SSL֤����֤
	virtual void onSSLCertVerifyNotification(ISSLCertVerificationHandler* handler) = 0;
};

class INetworkConnectionHelper
{
public:
	/// \ע������������Ϣ֪ͨ�Ĵ������
	virtual SDKError RegisterNetworkConnectionHandler(INetworkConnectionHandler* pNetworkHandler) = 0;

	/// \ж������������Ϣ֪ͨ�Ĵ������
	virtual SDKError UnRegisterNetworkConnectionHandler() = 0;
};
END_YSX_SDK_NAMESPACE
#endif