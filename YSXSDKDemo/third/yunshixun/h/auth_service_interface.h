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
	AUTHRET_SUCCESS,				///< ��֤�ɹ� 
	AUTHRET_KEYORSECRETEMPTY,		///< Key �� Secret Ϊ��
	AUTHRET_KEYORSECRETWRONG,		///< Key �� Secret ����
	AUTHRET_ACCOUNTNOTSUPPORT,		///< ��ҵ�˺Ų�֧��
	AUTHRET_ACCOUNTNOTENABLESDK,	///< ��ҵ�˺�û�п���SDK����
	AUTHRET_UNKNOWN,				///< δ֪����
	AUTHRET_NONE,					///< ��ʼ״̬
};

/*! \enum LOGINSTATUS
	\brief Login status.
	A more detailed struct description.
*/
enum LOGINSTATUS
{
	LOGIN_IDLE,							///< δ��¼
	LOGIN_PROCESSING,					///< ��¼��
	LOGIN_SUCCESS,						///< ��¼�ɹ�
	LOGIN_FAILED,						///< ��¼ʧ��		
	LOGIN_LOGINIM_FAILED,				///< ��¼IMʧ��
	LOGIN_LOGINMEETING_FAILED,			///< ��¼�������ʧ��
	LOGIN_EXCEPTION = 500,				///< ��¼�����쳣
	LOGIN_USER_NOT_EXIST = 3001,		///< �û�������
	LOGIN_ZHUMU_USER__NOT_EXIST = 3002,	///< ��ý���û�������
	LOGIN_USER_ENTERPRISE_ERROR = 3003, ///< �û���ҵ��Ϣ����
	LOGIN_MOBILE_NOT_EXIST = 4001,		///< �ֻ����벻����
	LOGIN_PASSWORD_ERROR = 4002,		///< �������
	LOGIN_TICKET_NOT_EXIST = 4003,		///< Ticket������
	LOGIN_SIGN_ERROR = 4004,			///< ǩ������
	LOGIN_INVALID_TOKEN = 4005,			///< ��ЧToken��Ϣ
	LOGIN_TOKEN_EXPIRED = 4006,			///< Token��Ϣ�ѹ���
	LOGIN_APIKEY_NOT_EXIST = 4007,		///< APIKey������
	LOGIN_APIKEYENTERPRISE_NO_MATCH = 4008,/// <APIKey�����ڴ��û�������ҵ
	LOGIN_TICKET_EXPIRED = 4009,		///< Ticket��Ϣ�ѹ���
	LOGIN_CONTACT_SERVICE_ERROR = 7001  ///< ͨѶ¼�������

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
	LoginType_Mobile,	///< �ֻ�����,�����¼
	LoginType_Token		///< ʹ��ͨѶ¼Token��¼
};

/*! \struct tagLoginParam
	\brief Account login Parameter.
	A more detailed struct description.
*/
typedef struct tagLoginParam
{
	const wchar_t* userName;///< �ֻ�����
	const wchar_t* password;///< ����
	LoginType loginType;	///< ��¼��ʽ
	const wchar_t* token;	///< ͨѶ¼Token
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
	/// \SDK��֤����ص�
	virtual void onAuthenticationReturn(AuthResult ret) = 0;

	/// \��¼��֤����ص�
	virtual void onLoginRet(LOGINSTATUS ret) = 0;

	/// \�˳��ص�
	virtual void onLogout() = 0;

#ifdef INCLUDE_IM
	/// \IM���ӳɹ�
	virtual void onConnect() = 0;

	/// /�˺��������豸��¼
	virtual void onDisconnect(const MsgErrorCode code) = 0;
#endif
};

/// \brief ��֤����
///
class IAuthService
{
public:
	/// \������֤�ص��¼�����
	virtual SDKError SetEvent(IAuthServiceEvent* pEvent) = 0;

	/// \SDK��֤
	virtual SDKError SDKAuth(AuthParam& authParam) = 0;

	/// \��ȡ��֤���
	virtual AuthResult GetAuthResult() = 0;

	/// \��ȡSDK��ʶ
	virtual const wchar_t* GetSDKIdentity() = 0;

	// \��¼
	virtual SDKError Login(LoginParam& param) = 0;

	// \�˳�
	virtual SDKError Logout() = 0;
	
	// \��ȡ��ǰ��¼�û�
	virtual UserDetailInfo* GetCurrentUser() = 0;

	/// \��ȡ��¼״̬
	virtual LOGINSTATUS GetLoginStatus() = 0;
};
END_YSX_SDK_NAMESPACE
#endif
