#ifndef _YSX_MEETING_SERVICE_INTERFACE_H_
#define _YSX_MEETING_SERVICE_INTERFACE_H_
#include "ysx_sdk_def.h"


BEGIN_YSX_SDK_NAMESPACE
/// \����״̬
enum MeetingStatus
{
	MEETING_STATUS_IDLE,			///< ����״̬
	MEETING_STATUS_CONNECTING,		///< ������
	MEETING_STATUS_WAITINGFORHOST,	///< �ȴ������˿�ʼ����
	MEETING_STATUS_INMEETING,		///< �ѽ������
	MEETING_STATUS_DISCONNECTING,	///< ����Ͽ�������
	MEETING_STATUS_RECONNECTING,	///< ������������
	MEETING_STATUS_FAILED,			///< ��������ʧ��
	MEETING_STATUS_ENDED,			///< �����ѽ���
	MEETING_STATUS_UNKNOW,			///< δ֪����
	MEETING_STATUS_LOCKED,			///< ����������
	MEETING_STATUS_UNLOCKED,		///< �����ѽ������
	MEETING_STATUS_IN_WAITING_ROOM,	
	MEETING_STATUS_WEBINAR_PROMOTE,
	MEETING_STATUS_WEBINAR_DEPROMOTE,
	MEETING_STATUS_JOIN_BREAKOUT_ROOM,
	MEETING_STATUS_LEAVE_BREAKOUT_ROOM,
	MEETING_STATUS_WAITING_EXTERNAL_SESSION_KEY,
    MEETING_STATUS_GET_MEETING_NUM_ERROR    ///< ���������飬�ɸ������ID��ȡ�������ʧ��
};

/// \����ʧ��ԭ��
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

/// \��������
enum MeetingType
{
	MEETING_TYPE_NONE,
	MEETING_TYPE_NORMAL,
	MEETING_TYPE_WEBINAR,
	MEETING_TYPE_BREAKOUTROOM,
	MEETING_TYPE_HUAWEI_HD,
};

/// \�뿪����ָ��
enum LeaveMeetingCmd
{
	LEAVE_MEETING,	///< �뿪����
	END_MEETING,	///< ��������
};


/// \�������,��ý�����,�������
typedef struct tagJoinParam4NormalUser
{
	UINT64		   meetingNumber;		///< �������
	const wchar_t* meetingId;			///< ����Id,��meetingType=1(�������)��,meetingId������д
	const wchar_t* userName;			///< ������ʾ����
	const wchar_t* psw;					///< ��������
	HWND		   hDirectShareAppWnd;	///< ֱ�ӹ���ָ���������
	int			   meetingType;			///< ��������,0:��ý��,1:����(��Ϊ),����ӿڷ�����Ϣ������������
	bool		   isVideoOff;			///< �Ƿ�ر���Ƶ
	bool		   isAudioOff;			///< �Ƿ�ر���Ƶ
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


/// \��ʼ����ṹ��,�������Լ�ԤԼ�Ļ���
typedef struct tagStartParam4NormalUser
{
	UINT64			meetingNumber;			///< �������
	const wchar_t*	meetingId;				///< ����Id
	HWND			hDirectShareAppWnd;		///< ֱ�ӹ���ָ���������
	bool			isVideoOff;				///< �Ƿ�ر���Ƶ
	bool			isAudioOff;				///< �Ƿ�ر���Ƶ

	tagStartParam4NormalUser()
	{		
		hDirectShareAppWnd = 0;
		meetingId = NULL;
		isVideoOff = false;
		isAudioOff = false;
	}
}StartParam;


/// \��ʼ��ʱ��ṹ��
typedef struct tagInstanceMeettingParam
{	
	const wchar_t*	meetingTopic;			///< ��������
	const wchar_t*	meetingParticipants;	///< ���������,ͨѶ¼�û�Id,�Զ��ŷָ� "1039022079703897890,1038722079703891234"
	HWND			hDirectShareAppWnd;		///< ֱ�ӹ���ָ���������
	bool		    isVideoOff;				///< �Ƿ�ر���Ƶ
	bool		    isAudioOff;				///< �Ƿ�ر���Ƶ
	tagInstanceMeettingParam()
	{
		hDirectShareAppWnd = 0;
		isVideoOff = false;
		isAudioOff = false;
	}
}InstanceMeettingParam;

/// \IMָ��
enum IMAction
{
	//�������
	MEETING_JOINMEETING = 0,
	//��ʼ����
	MEETING_STARTMEETING = 1,
	//����״̬�仯
	MEETING_STATUS_CHANGE = 2,
	//����323�豸
	MEETING_CALLH323 = 3,
	//�߳�
	LOGOFF_ACTION = 4,
	//�û�������_���µ�¼
	USER_CHANGEPASSWORD = 5,
	//�û�������,�˳�
	USER_DESTROY = 6,
	//�˳�����
	QUIT_MEETING = 7,
	//�����Լ�
	MUTE_SELF = 8,
	//�������
	UNMUTE_SELF = 9,
	//323״̬�仯
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

/// \������Ϣ�ӿ�
class IMeetingInfo
{
public:
	/// \��ȡ�������
	virtual UINT64 GetMeetingNumber() = 0;

	/// \��ȡ����Id,��Ϊ����Id�Լ�����
	virtual const wchar_t* GetMeetingID() = 0;

	/// \��ȡ��������
	virtual const wchar_t* GetMeetingTopic() = 0;

	/// \��ȡ��������
	virtual MeetingType GetMeetingType() = 0;

	/// \��ȡ���������ʼ�ģ��
	virtual const wchar_t* GetInviteEmailTeamplate() = 0;

	/// \��ȡ���������ʼ�����
	virtual const wchar_t* GetInviteEmailTitle() = 0;

	/// \��ȡ�������Url
	virtual const wchar_t* GetJoinMeetingUrl() = 0;

	/// \��ȡ���������˱�ʶ
	virtual const wchar_t* GetMeetingHostTag() = 0;

	/// \�Ƿ����ڲ�����
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
	/// \����״̬�仯�ص�,
	/// \param status ����״ֵ̬
	/// \param iResult details reason for special meeting status.
	/// �� status=MEETING_STATUS_FAILED ʱ, iResult ֵ�� MeetingFailCode ö��ֵ. 
	virtual void onMeetingStatusChanged(MeetingStatus status, int iResult = 0) = 0;

	/// \����ͳ�ƾ���֪ͨ�ص�,(����������)
	virtual void onMeetingStatisticsWarningNotification(StatisticsWarningType type) = 0;


	///�����˺�ÿ�����������ʱ��Ϊ30����,25����ʱ�ᴥ���ص�,�ͻ���������ʾ�ͻ�
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
/// \�������
///
class IMeetingService
{
public:
	/// \���û����¼�����
	virtual SDKError SetEvent(IMeetingServiceEvent* pEvent) = 0;

	/// \�ӻ����,�����ý���Ϊ����
	virtual SDKError Join(YSXSDK::JoinParam& joinParam) = 0;

	/// \��������,�Լ�ԤԼ�Ļ���
	virtual SDKError Start(YSXSDK::StartParam& startParam) = 0;

	/// \����һ����ʱ����
	virtual SDKError StartInstance(YSXSDK::InstanceMeettingParam& startParam)=0;

	/// \�뿪����
	virtual SDKError Leave(YSXSDK::LeaveMeetingCmd leaveCmd) = 0;

	/// \��ȡ����״̬
	virtual MeetingStatus GetMeetingStatus() = 0;

	/// \��������
	virtual SDKError LockMeeting() = 0;

	/// \��������
	virtual SDKError UnlockMeeting() = 0;

	/// \�����Ƿ�����
	virtual bool IsMeetingLocked() = 0;

    /// \����������߼������ʱ�Ƿ���˷羲��
    virtual void MuteMicWhenStartOrJoinMeeting(bool bMute) = 0;

	// \��ȡ������Ϣ
	virtual IMeetingInfo* GetMeetingInfo() = 0;

	/// \��ȡ������������
	virtual ConnectionQuality GetSharingConnQuality(bool bSending = true) = 0;

	/// \��ȡ��Ƶ��������
	virtual ConnectionQuality GetVideoConnQuality(bool bSending = true) = 0;

	/// \��ȡ��Ƶ��������
	virtual ConnectionQuality GetAudioConnQuality(bool bSending = true) = 0;

	/// \��ȡ��������
	virtual IMeetingConfiguration* GetMeetingConfiguration() = 0;

	/// \��ȡUI������
	virtual IMeetingUIController* GetUIController() = 0;

	/// \��ȡע�Ϳ�����
	virtual IAnnotationController* GetAnnotationController() = 0;

	/// \��ȡ������Ƶ����
	virtual IMeetingVideoController* GetMeetingVideoController() = 0;

	/// \��ȡԶ��Э��������
	virtual IMeetingRemoteController* GetMeetingRemoteController() = 0;

	/// \��ȡ���鹲�������
	virtual IMeetingShareController* GetMeetingShareController() = 0;

	/// \��ȡ������Ƶ������
	virtual IMeetingAudioController* GetMeetingAudioController() = 0;

	/// \��ȡ¼�ƿ�����
	virtual IMeetingRecordingController* GetMeetingRecordingController() = 0;

	/// \��ȡ���������
	virtual IMeetingChatController* GetMeetingChatController() = 0;

	/// \��ȡ�ȴ��ҿ�����
	virtual IMeetingWaitingRoomController* GetMeetingWaitingRoomController() = 0;

	/// \��ȡH323����
	virtual IMeetingH323Helper* GetH323Helper() = 0;

	/// \��ȡ�绰����
	virtual IMeetingPhoneHelper* GetMeetingPhoneHelper() = 0;

	/// \��ȡ��������˿�����
	virtual IMeetingParticipantsController* GetMeetingParticipantsController() = 0;

    /// \����Ӧ��
    /// \meetingId ����ID
    /// \meetingNum �����
    /// \action Ӧ�������0���ܾ���1������
    virtual void InviteAnswer(const wchar_t* meetingId, UINT64 meetingNum, int action) = 0;

    /// \���ͻ�������
    /// \meetingId ����ID
    /// \toUserIDs ��������ID���Զ��ŷֿ�
    virtual void SendInvite(const wchar_t* meetingId, const wchar_t* toUserIDs) = 0;

    /// \��ȡ�������������
    /// \meetingId ����ID
    virtual UINT64 GetJoinMeetingNo(const wchar_t* meetingId) = 0;

    /// \��ȡ�������ID
    virtual std::wstring GetHDMeetingID() = 0;
};
END_YSX_SDK_NAMESPACE
#endif