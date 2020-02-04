#ifndef _YSX_MEETING_SERVICE_INTERFACE_H_
#define _YSX_MEETING_SERVICE_INTERFACE_H_
#include "ysx_sdk_def.h"


BEGIN_YSX_SDK_NAMESPACE
/// \会议状态
enum MeetingStatus
{
	MEETING_STATUS_IDLE,			///< 空闲状态
	MEETING_STATUS_CONNECTING,		///< 连接中
	MEETING_STATUS_WAITINGFORHOST,	///< 等待主持人开始会议
	MEETING_STATUS_INMEETING,		///< 已进入会议
	MEETING_STATUS_DISCONNECTING,	///< 会议断开连接中
	MEETING_STATUS_RECONNECTING,	///< 会议重新连接
	MEETING_STATUS_FAILED,			///< 会议连接失败
	MEETING_STATUS_ENDED,			///< 会议已结束
	MEETING_STATUS_UNKNOW,			///< 未知错误
	MEETING_STATUS_LOCKED,			///< 会议已锁定
	MEETING_STATUS_UNLOCKED,		///< 会议已解除锁定
	MEETING_STATUS_IN_WAITING_ROOM,	
	MEETING_STATUS_WEBINAR_PROMOTE,
	MEETING_STATUS_WEBINAR_DEPROMOTE,
	MEETING_STATUS_JOIN_BREAKOUT_ROOM,
	MEETING_STATUS_LEAVE_BREAKOUT_ROOM,
	MEETING_STATUS_WAITING_EXTERNAL_SESSION_KEY,
    MEETING_STATUS_GET_MEETING_NUM_ERROR    ///< 加入高清会议，由高清会议ID获取会议号码失败
};

/// \会议失败原因
enum MeetingFailCode
{
	MEETING_SUCCESS = 0,
	MEETING_FAIL_NETWORK_ERR = 1,
	MEETING_FAIL_RECONNECT_ERR = 2,
	MEETING_FAIL_MMR_ERR = 3,
	MEETING_FAIL_PASSWORD_ERR = 4,
	MEETING_FAIL_SESSION_ERR = 5,
	MEETING_FAIL_MEETING_OVER = 6,
	MEETING_FAIL_MEETING_NOT_START = 7,
	MEETING_FAIL_MEETING_NOT_EXIST = 8,
	MEETING_FAIL_MEETING_USER_FULL = 9,
	MEETING_FAIL_CLIENT_INCOMPATIBLE = 10,///< RESULT_ZC_INCOMPATIBLE
	MEETING_FAIL_NO_MMR = 11,
	MEETING_FAIL_CONFLOCKED = 12,
	MEETING_FAIL_MEETING_RESTRICTED = 13,
	MEETING_FAIL_MEETING_RESTRICTED_JBH = 14,
	MEETING_FAIL_CANNOT_EMIT_WEBREQUEST = 15,
	MEETING_FAIL_CANNOT_START_TOKENEXPIRE = 16,
	SESSION_VIDEO_ERR = 17,
	SESSION_AUDIO_AUTOSTARTERR = 18,
	MEETING_FAIL_REGISTERWEBINAR_FULL = 19,
	MEETING_FAIL_REGISTERWEBINAR_HOSTREGISTER = 20,
	MEETING_FAIL_REGISTERWEBINAR_PANELISTREGISTER = 21,
	MEETING_FAIL_REGISTERWEBINAR_DENIED_EMAIL = 22,
	MEETING_FAIL_ENFORCE_LOGIN = 23,
	MEETING_FAIL_WRITE_CONFIG_FILE = 50,	///< Failed to write configure file
	MEETING_FAIL_FORBID_TO_JOIN_INTERNAL_MEETING = 60,
};

/// \会议类型
enum MeetingType
{
	MEETING_TYPE_NONE,
	MEETING_TYPE_NORMAL,
	MEETING_TYPE_WEBINAR,
	MEETING_TYPE_BREAKOUTROOM,
	MEETING_TYPE_HUAWEI_HD,
};

/// \离开会议指令
enum LeaveMeetingCmd
{
	LEAVE_MEETING,	///< 离开会议
	END_MEETING,	///< 结束会议
};


/// \加入会议,多媒体会议,高清会议
typedef struct tagJoinParam4NormalUser
{
	UINT64		   meetingNumber;		///< 会议号码
	const wchar_t* meetingId;			///< 会议Id,当meetingType=1(高清会议)是,meetingId必须填写
	const wchar_t* userName;			///< 会议显示名称
	const wchar_t* psw;					///< 会议密码
	HWND		   hDirectShareAppWnd;	///< 直接共享指定句柄窗口
	int			   meetingType;			///< 会议类型,0:多媒体,1:高清(华为),会议接口返回信息包含会议类型
	bool		   isVideoOff;			///< 是否关闭视频
	bool		   isAudioOff;			///< 是否关闭音频
	tagJoinParam4NormalUser()
	{
		userName = NULL;
		psw = NULL;
		meetingId = NULL;
		hDirectShareAppWnd = 0;
		meetingType = 0;
		isVideoOff = false;
		isAudioOff = false;
	}
}JoinParam;


/// \开始会议结构体,必须是自己预约的会议
typedef struct tagStartParam4NormalUser
{
	UINT64			meetingNumber;			///< 会议号码
	const wchar_t*	meetingId;				///< 会议Id
	HWND			hDirectShareAppWnd;		///< 直接共享指定句柄窗口
	bool			isVideoOff;				///< 是否关闭视频
	bool			isAudioOff;				///< 是否关闭音频

	tagStartParam4NormalUser()
	{		
		hDirectShareAppWnd = 0;
		meetingId = NULL;
		isVideoOff = false;
		isAudioOff = false;
	}
}StartParam;


/// \开始即时会结构体
typedef struct tagInstanceMeettingParam
{	
	const wchar_t*	meetingTopic;			///< 会议主题
	const wchar_t*	meetingParticipants;	///< 会议参与人,通讯录用户Id,以逗号分割 "1039022079703897890,1038722079703891234"
	HWND			hDirectShareAppWnd;		///< 直接共享指定句柄窗口
	bool		    isVideoOff;				///< 是否关闭视频
	bool		    isAudioOff;				///< 是否关闭音频
	tagInstanceMeettingParam()
	{
		hDirectShareAppWnd = 0;
		isVideoOff = false;
		isAudioOff = false;
	}
}InstanceMeettingParam;

/// \IM指令
enum IMAction
{
	//加入会议
	MEETING_JOINMEETING = 0,
	//开始会议
	MEETING_STARTMEETING = 1,
	//会议状态变化
	MEETING_STATUS_CHANGE = 2,
	//呼叫323设备
	MEETING_CALLH323 = 3,
	//踢出
	LOGOFF_ACTION = 4,
	//用户密码变更_重新登录
	USER_CHANGEPASSWORD = 5,
	//用户被销户,退出
	USER_DESTROY = 6,
	//退出会议
	QUIT_MEETING = 7,
	//静音自己
	MUTE_SELF = 8,
	//解除静音
	UNMUTE_SELF = 9,
	//323状态变化
	HD_DEVICE_STATUS_CHANGE = 10
};

/*! \enum ConnectionQuality
	\brief Connection quality.
	A more detailed struct description.
*/
enum ConnectionQuality
{
	Conn_Quality_Unknow,
	Conn_Quality_Very_Bad,
	Conn_Quality_Bad,
	Conn_Quality_Not_Good,
	Conn_Quality_Normal,
	Conn_Quality_Good,
	Conn_Quality_Excellent,
};

/*! \enum SDKViewType
	\brief SDK View Type, first monitor and second monitor.
	A more detailed struct description.
*/
enum SDKViewType
{
	SDK_FIRST_VIEW,
	SDK_SECOND_VIEW,
};

/// \会议信息接口
class IMeetingInfo
{
public:
	/// \获取会议号码
	virtual UINT64 GetMeetingNumber() = 0;

	/// \获取会议Id,华为会议Id自己保存
	virtual const wchar_t* GetMeetingID() = 0;

	/// \获取会议主题
	virtual const wchar_t* GetMeetingTopic() = 0;

	/// \获取会议类型
	virtual MeetingType GetMeetingType() = 0;

	/// \获取会议邀请邮件模版
	virtual const wchar_t* GetInviteEmailTeamplate() = 0;

	/// \获取会议邀请邮件标题
	virtual const wchar_t* GetInviteEmailTitle() = 0;

	/// \获取加入会议Url
	virtual const wchar_t* GetJoinMeetingUrl() = 0;

	/// \获取会议主持人标识
	virtual const wchar_t* GetMeetingHostTag() = 0;

	/// \是否是内部会议
	virtual bool IsInternalMeeting() = 0;
};

/*! \enum StatisticsWarningType
	\brief Meeting statistics warning type.
	A more detailed struct description.
*/
enum StatisticsWarningType
{
	Statistics_Warning_None,
	Statistics_Warning_Network_Quality_Bad,
};

/// \brief Meeting Service Callback Event
///
class IMeetingServiceEvent
{
public:
	/// \会议状态变化回调,
	/// \param status 会议状态值
	/// \param iResult details reason for special meeting status.
	/// 当 status=MEETING_STATUS_FAILED 时, iResult 值是 MeetingFailCode 枚举值. 
	virtual void onMeetingStatusChanged(MeetingStatus status, int iResult = 0) = 0;

	/// \会议统计警告通知回调,(网络质量差)
	virtual void onMeetingStatisticsWarningNotification(StatisticsWarningType type) = 0;


	///试用账号每次入会议限制时长为30分钟,25分钟时会触发回调,客户端自行提示客户
	virtual void onStartLeaveMeetingCountdown(int minutes = 0) = 0;
};

class IAnnotationController;
class IMeetingAudioController;
class IMeetingBreakoutRoomsController;
class IMeetingChatController;
class IMeetingConfiguration;
class IMeetingH323Helper;
class IMeetingParticipantsController;
class IMeetingPhoneHelper;
class IMeetingRecordingController;
class IMeetingRemoteController;
class IMeetingShareController;
class IMeetingUIController;
class IMeetingVideoController;
class IMeetingWaitingRoomController;
/// \会议服务
///
class IMeetingService
{
public:
	/// \设置会议事件对象
	virtual SDKError SetEvent(IMeetingServiceEvent* pEvent) = 0;

	/// \加会会议,加入多媒体或华为会议
	virtual SDKError Join(YSXSDK::JoinParam& joinParam) = 0;

	/// \启动会议,自己预约的会议
	virtual SDKError Start(YSXSDK::StartParam& startParam) = 0;

	/// \开启一个即时会议
	virtual SDKError StartInstance(YSXSDK::InstanceMeettingParam& startParam)=0;

	/// \离开会议
	virtual SDKError Leave(YSXSDK::LeaveMeetingCmd leaveCmd) = 0;

	/// \获取会议状态
	virtual MeetingStatus GetMeetingStatus() = 0;

	/// \锁定会议
	virtual SDKError LockMeeting() = 0;

	/// \解锁会议
	virtual SDKError UnlockMeeting() = 0;

	/// \会议是否被锁定
	virtual bool IsMeetingLocked() = 0;

    /// \开启会议或者加入会议时是否麦克风静音
    virtual void MuteMicWhenStartOrJoinMeeting(bool bMute) = 0;

	// \获取会议信息
	virtual IMeetingInfo* GetMeetingInfo() = 0;

	/// \获取共享连接质量
	virtual ConnectionQuality GetSharingConnQuality(bool bSending = true) = 0;

	/// \获取视频连接质量
	virtual ConnectionQuality GetVideoConnQuality(bool bSending = true) = 0;

	/// \获取音频连接质量
	virtual ConnectionQuality GetAudioConnQuality(bool bSending = true) = 0;

	/// \获取会议配置
	virtual IMeetingConfiguration* GetMeetingConfiguration() = 0;

	/// \获取UI控制器
	virtual IMeetingUIController* GetUIController() = 0;

	/// \获取注释控制器
	virtual IAnnotationController* GetAnnotationController() = 0;

	/// \获取会议视频控制
	virtual IMeetingVideoController* GetMeetingVideoController() = 0;

	/// \获取远程协助控制器
	virtual IMeetingRemoteController* GetMeetingRemoteController() = 0;

	/// \获取会议共享控制器
	virtual IMeetingShareController* GetMeetingShareController() = 0;

	/// \获取会议音频控制器
	virtual IMeetingAudioController* GetMeetingAudioController() = 0;

	/// \获取录制控制器
	virtual IMeetingRecordingController* GetMeetingRecordingController() = 0;

	/// \获取聊天控制器
	virtual IMeetingChatController* GetMeetingChatController() = 0;

	/// \获取等待室控制器
	virtual IMeetingWaitingRoomController* GetMeetingWaitingRoomController() = 0;

	/// \获取H323助手
	virtual IMeetingH323Helper* GetH323Helper() = 0;

	/// \获取电话助手
	virtual IMeetingPhoneHelper* GetMeetingPhoneHelper() = 0;

	/// \获取会议参与人控制器
	virtual IMeetingParticipantsController* GetMeetingParticipantsController() = 0;

    /// \邀请应答
    /// \meetingId 会议ID
    /// \meetingNum 会议号
    /// \action 应答操作，0：拒绝；1：接受
    virtual void InviteAnswer(const wchar_t* meetingId, UINT64 meetingNum, int action) = 0;

    /// \发送会议邀请
    /// \meetingId 会议ID
    /// \toUserIDs 被邀请人ID，以逗号分开
    virtual void SendInvite(const wchar_t* meetingId, const wchar_t* toUserIDs) = 0;

    /// \获取加入高清会议号码
    /// \meetingId 会议ID
    virtual UINT64 GetJoinMeetingNo(const wchar_t* meetingId) = 0;

    /// \获取高清会议ID
    virtual std::wstring GetHDMeetingID() = 0;
};
END_YSX_SDK_NAMESPACE
#endif