/*!
* \file auth_service_interface.h
* \brief Authentication Service Interface
*
*/
#ifndef _YSX_AUTH_SERVICE_INTERFACE_H_
#define _YSX_AUTH_SERVICE_INTERFACE_H_
#include "ysx_sdk_def.h"
#include <string>
/// \brief YSX SDK Namespace
/// 
///
BEGIN_YSX_SDK_NAMESPACE

/*! \enum AuthResult
	\brief SDK Authentication result.
	A more detailed struct description.
*/
enum AuthResult
{
	AUTHRET_SUCCESS,				///< 认证成功 
	AUTHRET_KEYORSECRETEMPTY,		///< Key 或 Secret 为空
	AUTHRET_KEYORSECRETWRONG,		///< Key 或 Secret 错误
	AUTHRET_ACCOUNTNOTSUPPORT,		///< 企业账号不支持
	AUTHRET_ACCOUNTNOTENABLESDK,	///< 企业账号没有开启SDK集成
	AUTHRET_UNKNOWN,				///< 未知错误
	AUTHRET_NONE,					///< 初始状态
};

/*! \enum LOGINSTATUS
	\brief Login status.
	A more detailed struct description.
*/
enum LOGINSTATUS
{
	LOGIN_IDLE,							///< 未登录
	LOGIN_PROCESSING,					///< 登录中
	LOGIN_SUCCESS,						///< 登录成功
	LOGIN_FAILED,						///< 登录失败		
	LOGIN_LOGINIM_FAILED,				///< 登录IM失败
	LOGIN_LOGINMEETING_FAILED,			///< 登录会议服务失败
	LOGIN_EXCEPTION = 500,				///< 登录发生异常
	LOGIN_USER_NOT_EXIST = 3001,		///< 用户不存在
	LOGIN_ZHUMU_USER__NOT_EXIST = 3002,	///< 多媒体用户不存在
	LOGIN_USER_ENTERPRISE_ERROR = 3003, ///< 用户企业信息错误
	LOGIN_MOBILE_NOT_EXIST = 4001,		///< 手机号码不存在
	LOGIN_PASSWORD_ERROR = 4002,		///< 密码错误
	LOGIN_TICKET_NOT_EXIST = 4003,		///< Ticket不存在
	LOGIN_SIGN_ERROR = 4004,			///< 签名错误
	LOGIN_INVALID_TOKEN = 4005,			///< 无效Token信息
	LOGIN_TOKEN_EXPIRED = 4006,			///< Token信息已过期
	LOGIN_APIKEY_NOT_EXIST = 4007,		///< APIKey不存在
	LOGIN_APIKEYENTERPRISE_NO_MATCH = 4008,/// <APIKey不属于此用户所在企业
	LOGIN_TICKET_EXPIRED = 4009,		///< Ticket信息已过期
	LOGIN_CONTACT_SERVICE_ERROR = 7001  ///< 通讯录服务错误

};

/*! \struct tagAuthParam
	\brief SDK Authentication Parameter.
	A more detailed struct description.
*/
typedef struct tagAuthParam
{
	const wchar_t* appKey;		///< APP Key
	const wchar_t* appSecret;	///< APP Secret
	const wchar_t* apiKey;		///< API Key
	const wchar_t* apiSecret;	///< API Secret
	tagAuthParam()
	{
		appKey = NULL;
		appSecret = NULL;
		apiKey = NULL;
		apiSecret = NULL;
	}
}AuthParam;

/*! \enum LoginType
\brief type of user login.
A more detailed struct description.
*/
enum LoginType
{
	LoginType_Mobile,	///< 手机号码,密码登录
	LoginType_Token		///< 使用通讯录Token登录
};

/*! \struct tagLoginParam
	\brief Account login Parameter.
	A more detailed struct description.
*/
typedef struct tagLoginParam
{
	const wchar_t* userName;///< 手机号码
	const wchar_t* password;///< 密码
	LoginType loginType;	///< 登录方式
	const wchar_t* token;	///< 通讯录Token
	tagLoginParam()
	{
		userName = NULL;
		password = NULL;
		token = NULL;
		loginType = LoginType::LoginType_Mobile;
	}
}LoginParam;

typedef struct  tagUserDetailInfo
{
	std::wstring UserId;
	std::wstring Email;
	std::wstring IMId;
	std::wstring EnterpriseId;
	std::wstring UserName;
	std::wstring Ticket;
	std::wstring Token;
	bool IsTrial;
} UserDetailInfo;


/// \brief Authentication Service Callback Event
///
class IAuthServiceEvent
{
public:
	/// \SDK认证结果回调
	virtual void onAuthenticationReturn(AuthResult ret) = 0;

	/// \登录认证结果回调
	virtual void onLoginRet(LOGINSTATUS ret) = 0;

	/// \退出回调
	virtual void onLogout() = 0;

#ifdef INCLUDE_IM
	/// \IM连接成功
	virtual void onConnect() = 0;

	/// /账号在其他设备登录
	virtual void onDisconnect(const MsgErrorCode code) = 0;
#endif
};

/// \brief 认证服务
///
class IAuthService
{
public:
	/// \设置认证回调事件对象
	virtual SDKError SetEvent(IAuthServiceEvent* pEvent) = 0;

	/// \SDK认证
	virtual SDKError SDKAuth(AuthParam& authParam) = 0;

	/// \获取认证结果
	virtual AuthResult GetAuthResult() = 0;

	/// \获取SDK标识
	virtual const wchar_t* GetSDKIdentity() = 0;

	// \登录
	virtual SDKError Login(LoginParam& param) = 0;

	// \退出
	virtual SDKError Logout() = 0;
	
	// \获取当前登录用户
	virtual UserDetailInfo* GetCurrentUser() = 0;

	/// \获取登录状态
	virtual LOGINSTATUS GetLoginStatus() = 0;
};
END_YSX_SDK_NAMESPACE
#endif
