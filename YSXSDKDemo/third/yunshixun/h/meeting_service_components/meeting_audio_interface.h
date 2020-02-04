#ifndef _YSX_MEETING_AUDIO_INTERFACE_H_
#define _YSX_MEETING_AUDIO_INTERFACE_H_
#include "..\ysx_sdk_def.h"

BEGIN_YSX_SDK_NAMESPACE

/// \用户音频状态
struct UserAudioStatus
{
	unsigned int UserId;
	enum AudioStatus AudioStatus;
	enum AudioType   AudioType;
};

/// \会议音频事件
class IMeetingAudioCtrlEvent
{
public:
	/// \当用户音频状态变化回调
	virtual void onUserAudioStatusChange(YSXSDK::UserAudioStatus& userAudioStatus) = 0;

	/// \当用户音频激活状态变化回调
	virtual void onUserActiveAudioChange(unsigned int userId) = 0;
};

/// \会议音频控制器
class IMeetingAudioController
{
public:
	/// \设置会议音频事件对象
	virtual SDKError SetEvent(IMeetingAudioCtrlEvent* pEvent) = 0;

	/// \加入Voip音频
	virtual SDKError JoinVoip() = 0;

	/// \离开Voip音频
	virtual SDKError LeaveVoip() = 0;

	/// \主持人静音指定用户
	virtual SDKError MuteAudio(unsigned int userid, bool allowUnmuteBySelf = true) = 0;

	/// \主持人解除指定用户静音状态
	virtual SDKError UnMuteAudio(unsigned int userid) = 0;

	/// \自己是否可以解除静音
	virtual bool CanUnMuteBySelf() = 0;

	/// \启用或禁用用户静音方式加入会议
	virtual SDKError EnableMuteOnEntry(bool bEnable) = 0;

	/// \启用或禁用用户进入时播放提示音
	virtual SDKError EnablePlayChimeWhenEnterOrExit(bool bEnable) = 0;
};
END_YSX_SDK_NAMESPACE
#endif