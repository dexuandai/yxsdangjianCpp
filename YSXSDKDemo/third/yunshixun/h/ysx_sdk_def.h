/*!
* \file ysx_sdk_def.h
* \brief  YSX Windows SDK Common Defines File
*
*/
#ifndef _YSX_SDK_DEF_H_
#define _YSX_SDK_DEF_H_
#include <tchar.h>
#include <windows.h>
#include <vector>
#define PLATFORM_IMPORT	__declspec(dllimport)  
#define PLATFORM_EXPORT	__declspec(dllexport)
#ifdef YSX_SDK_DLL_EXPORT
#define SDK_API PLATFORM_EXPORT
#elif defined YSX_SDK_DLL_IMPORT
#define SDK_API PLATFORM_IMPORT
#else
#define SDK_API
#endif

#define YSX_SDK_NAMESPACE YSXSDK
#define BEGIN_YSX_SDK_NAMESPACE namespace YSX_SDK_NAMESPACE {
#define END_YSX_SDK_NAMESPACE };
#define USING_YSX_SDK_NAMESPACE using namespace YSX_SDK_NAMESPACE;

/// \brief YSX SDK Namespace
/// 
///
BEGIN_YSX_SDK_NAMESPACE

/*! \enum SDKError
	\brief Init SDK Parameter.
	A more detailed struct description.
*/
enum SDKError
{
	SDKERR_SUCCESS = 0,///< Success Result
	SDKERR_NO_IMPL,///< Not support this feature now 
	SDKERR_WRONG_USEAGE,///< Wrong useage about this feature 
	SDKERR_INVALID_PARAMETER,///< Wrong parameter 
	SDKERR_MODULE_LOAD_FAILED,///< Load module failed 
	SDKERR_MEMORY_FAILED,///< No memory allocated 
	SDKERR_SERVICE_FAILED,///< Internal service error 
	SDKERR_UNINITIALIZE,///< Not initialize before use 
	SDKERR_UNAUTHENTICATION,///< Not Authentication before use
	SDKERR_NORECORDINGINPROCESS,///< No recording in process
	SDKERR_TRANSCODER_NOFOUND,///< can't find transcoder module
	SDKERR_VIDEO_NOTREADY,///< Video service not ready
	SDKERR_NO_PERMISSION,///< No premission to do this
    SDKERR_UNKNOWN,///< Unknown error 
	SDKERR_OTHER_SDK_INSTANCE_RUNNING,
	SDKERR_TRIAL_USER_CAN_JOIN_TWICE_MEETING_EVERY_DAY,///< 试用账号每天最多加入两次会议
    SDKERR_MEETING_TOPIC_EMPTY,///< 会议主题为空
};


enum MsgErrorCode
{
	EM_NO_ERROR = 0,                    //No error

	USER_ALREADY_LOGIN = 200,           //User has already login
	USER_NOT_LOGIN,                     //User has not login
	USER_AUTHENTICATION_FAILED,         //User name or password is wrong
	USER_ALREADY_EXIST,                 //User has already exist
	USER_NOT_FOUND,                     //User dosn't exist
	USER_ILLEGAL_ARGUMENT,              //Illegal argument
	USER_LOGIN_ANOTHER_DEVICE,          //User login on another device
	USER_REMOVED,                       //User was removed from server
	USER_REG_FAILED,                    //User register failed
	PUSH_UPDATECONFIGS_FAILED,          //Update push configs failed
	USER_PERMISSION_DENIED,             //User has no right for this operation
	USER_BINDDEVICETOKEN_FAILED,        //Bind device token failed
	USER_UNBIND_DEVICETOKEN_FAILED,     //Unbind device token failed
	USER_BIND_ANOTHER_DEVICE,           //Bind another device and do not allow auto login
	USER_LOGIN_TOO_MANY_DEVICES,        //User login on too many devices
	USER_MUTED,                         //User mutes in groups or chatrooms
	USER_KICKED_BY_CHANGE_PASSWORD,     //User has changed the password
	USER_KICKED_BY_OTHER_DEVICE,        //User was kicked by other device or console backend

	SERVER_NOT_REACHABLE = 300,         //Server is not reachable
	SERVER_TIMEOUT,                     //Wait server response timeout
	SERVER_BUSY,                        //Server is busy
	SERVER_UNKNOWN_ERROR,               //Unknown server error
	SERVER_GET_DNSLIST_FAILED,          //Can't get dns list
	SERVER_SERVING_DISABLED,            //Serving is disabled
	SERVER_DECRYPTION_FAILED,           //Server transfer decryption failure.
	
	MESSAGE_INVALID = 500,              //Message is invalid
	MESSAGE_INCLUDE_ILLEGAL_CONTENT,    //Message include illegal content
	MESSAGE_SEND_TRAFFIC_LIMIT,
	MESSAGE_ENCRYPTION_ERROR,
	MESSAGE_RECALL_TIME_LIMIT,          //Message recall exceed time limit
	SERVICE_NOT_ENABLED		

};

enum SDK_LANGUAGE_ID
{
	LANGUAGE_Unknow = 0,
	LANGUAGE_English,
	LANGUAGE_Chinese_Simplified,
	LANGUAGE_Chinese_Traditional,
	LANGUAGE_Japanese,
	LANGUAGE_Spanish,
	LANGUAGE_German,
	LANGUAGE_French,
};

typedef struct tagWndPosition
{
	int left;
	int top;
	HWND hSelfWnd;
	HWND hParent;
	tagWndPosition()
	{
		left = 0;
		top = 0;
		hSelfWnd = NULL;
		hParent = NULL;
	}
}WndPosition;

enum CustomizedLanguageType
{
	CustomizedLanguage_None,
	CustomizedLanguage_FilePath,
	CustomizedLanguage_Content,
};
typedef struct tagCustomizedLanguageInfo
{
	const char* langName;
	const char* langInfo;
	CustomizedLanguageType langType;
	tagCustomizedLanguageInfo()
	{
		langName = NULL;
		langInfo = NULL;
		langType = CustomizedLanguage_None;
	}

}CustomizedLanguageInfo;

typedef struct tagConfigurableOptions
{
	CustomizedLanguageInfo customizedLang;
}ConfigurableOptions;

/*! \struct tagInitParam
	\brief Init SDK Parameter.
	A more detailed struct description.
*/
typedef struct tagInitParam
{
	const wchar_t* strBrandingName;		///< 应用名称
	const wchar_t* strSupportUrl;		///< 支持URL
	unsigned int uiWindowIconSmallID;	///< 小图标
	unsigned int uiWindowIconBigID;		///< 大图标
	SDK_LANGUAGE_ID emLanguageID;		///< 语言ID
	bool enableLog;						///< 启用日志
	tagInitParam()
	{
		strBrandingName = NULL;
		strSupportUrl = NULL;
		uiWindowIconSmallID = 0;
		uiWindowIconBigID = 0;
		emLanguageID = LANGUAGE_Unknow;
		enableLog = false;
	}
}InitParam;


//=================从meeting_audio_interface.h和meeting_participants_ctrl_interface.h迁移过来============
/*! \enum AudioStatus
\brief Audio status.
A more detailed struct description.
*/
enum AudioStatus
{
	Audio_None,
	Audio_Muted,
	Audio_UnMuted,
	Audio_Muted_ByHost,
	Audio_UnMuted_ByHost,
	Audio_MutedAll_ByHost,
	Audio_UnMutedAll_ByHost,
};

enum AudioType
{
	AUDIOTYPE_NONE,
	AUDIOTYPE_VOIP,
	AUDIOTYPE_PHONE,
	AUDIOTYPE_UNKNOW,
};

enum UserRole
{
	USERROLE_NONE,
	USERROLE_HOST,
	USERROLE_COHOST,
	USERROLE_PANELIST,
	USERROLE_BREAKOUTROOM_MODERATOR,
	USERROLE_ATTENDEE,
};


/// \brief User information Interface
///
class IUserInfo
{
public:
	/// \brief Get user name
	/// \return If the function succeeds, the return value is user name.
	///If the function fails, the return value is NULL.
	virtual const wchar_t* GetUserName() = 0;

	/// \brief Get user email
	/// \return If the function succeeds, the return value is user email.
	///If the function fails, the return value is NULL.
	virtual const wchar_t* GetEmail() = 0;

	/// \brief Is host or not
	/// \return host or not
	virtual bool IsHost() = 0;

	/// \brief Get user ID
	/// \return If the function succeeds, the return value is user ID.
	///If the function fails, the return value is 0.
	virtual unsigned int GetUserID() = 0;

	/// \brief Is video on or off 
	/// \return video on or off
	virtual bool IsVideoOn() = 0;

	/// \brief Is audio Muted or UnMuted 
	/// \return audio Muted or UnMuted 
	virtual bool IsAudioMuted() = 0;

	/// \brief Audio type
	/// \return Audio join type
	virtual AudioType GetAudioJoinType() = 0;

	/// \brief Is me or not
	/// \return me or not
	virtual bool IsMySelf() = 0;

	/// \brief Is in waiting room or not
	/// \return in waiting room or not 
	virtual bool IsInWaitingRoom() = 0;

	/// \brief Is raise hand or not
	/// \return Is raise hand or not
	virtual bool IsRaiseHand() = 0;

	/// \brief User Role
	/// \return User Role
	virtual UserRole GetUserRole() = 0;

	/// \brief Is pure phone user or not
	/// \return Is pure phone user or not
	virtual bool IsPurePhoneUser() = 0;

    virtual const wchar_t* GetAccountID() = 0;
};

typedef struct  tagLoginUserInfo
{
	const wchar_t* UserId;
	const wchar_t* Email;
	const wchar_t* IMId;
	const wchar_t* EnterpriseId;
	const wchar_t* UserName;
	const wchar_t* Token;
	tagLoginUserInfo()
	{
		UserId = NULL;
		Email = NULL;
		IMId = NULL;
		EnterpriseId = NULL;
		UserName = NULL;
		Token = NULL;
	}
} LoginUserInfo;

END_YSX_SDK_NAMESPACE

#endif