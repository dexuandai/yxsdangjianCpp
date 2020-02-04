#ifndef _YSX_MEETING_AUDIO_INTERFACE_H_
#define _YSX_MEETING_AUDIO_INTERFACE_H_
#include "..\ysx_sdk_def.h"

BEGIN_YSX_SDK_NAMESPACE

/// \�û���Ƶ״̬
struct UserAudioStatus
{
	unsigned int UserId;
	enum AudioStatus AudioStatus;
	enum AudioType   AudioType;
};

/// \������Ƶ�¼�
class IMeetingAudioCtrlEvent
{
public:
	/// \���û���Ƶ״̬�仯�ص�
	virtual void onUserAudioStatusChange(YSXSDK::UserAudioStatus& userAudioStatus) = 0;

	/// \���û���Ƶ����״̬�仯�ص�
	virtual void onUserActiveAudioChange(unsigned int userId) = 0;
};

/// \������Ƶ������
class IMeetingAudioController
{
public:
	/// \���û�����Ƶ�¼�����
	virtual SDKError SetEvent(IMeetingAudioCtrlEvent* pEvent) = 0;

	/// \����Voip��Ƶ
	virtual SDKError JoinVoip() = 0;

	/// \�뿪Voip��Ƶ
	virtual SDKError LeaveVoip() = 0;

	/// \�����˾���ָ���û�
	virtual SDKError MuteAudio(unsigned int userid, bool allowUnmuteBySelf = true) = 0;

	/// \�����˽��ָ���û�����״̬
	virtual SDKError UnMuteAudio(unsigned int userid) = 0;

	/// \�Լ��Ƿ���Խ������
	virtual bool CanUnMuteBySelf() = 0;

	/// \���û�����û�������ʽ�������
	virtual SDKError EnableMuteOnEntry(bool bEnable) = 0;

	/// \���û�����û�����ʱ������ʾ��
	virtual SDKError EnablePlayChimeWhenEnterOrExit(bool bEnable) = 0;
};
END_YSX_SDK_NAMESPACE
#endif