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
/// \代理设置信息回调接口
///
class IProxySettingHandler
{
public:
	virtual ~IProxySettingHandler(){};
	/// \获取代理Host
	virtual const wchar_t* GetProxyHost() = 0;
	/// \获取代理端口
	virtual unsigned int GetProxyPort() = 0;
	/// \获取代理描述
	virtual const wchar_t* GetProxyDescription() = 0;

	/// \输入用户名和密码进行连接
	virtual void InputUsernamePassword(const wchar_t* userName, const wchar_t* psw) = 0;

	/// \取消输入用户名和密码
	virtual void Cancel() = 0;

};

/// \证书验证回调接口
///
class ISSLCertVerificationHandler
{
public:
	virtual ~ISSLCertVerificationHandler(){};

	// \获取证书颁发给谁
	virtual const wchar_t* GetCertIssuedTo() = 0;
	// \获取证书颁发者
	virtual const wchar_t* GetCertIssuedBy() = 0;
	// \获取证书序列号
	virtual const wchar_t* GetCertSerialNum() = 0;
	/// \获取证书指纹
	virtual const wchar_t* GetCertFingerprint() = 0;
	// \信任此SSL证书
	virtual void Trust() = 0;
	// \不信任此SSL证书
	virtual void Cancel() = 0;

};

/// \网络连接事件回调接口
///
class INetworkConnectionHandler
{
public:
	/// \当代理信息检测完成
	virtual void onProxyDetectComplete() = 0;
	/// \收到此消息时，必须提示用户输入代理的用户名和密码
	virtual void onProxySettingNotification(IProxySettingHandler* handler) = 0;
	/// \收到此消息时，必须提示用户进行SSL证书验证
	virtual void onSSLCertVerifyNotification(ISSLCertVerificationHandler* handler) = 0;
};

class INetworkConnectionHelper
{
public:
	/// \注册网络连接消息通知的处理程序
	virtual SDKError RegisterNetworkConnectionHandler(INetworkConnectionHandler* pNetworkHandler) = 0;

	/// \卸载网络连接消息通知的处理程序
	virtual SDKError UnRegisterNetworkConnectionHandler() = 0;
};
END_YSX_SDK_NAMESPACE
#endif