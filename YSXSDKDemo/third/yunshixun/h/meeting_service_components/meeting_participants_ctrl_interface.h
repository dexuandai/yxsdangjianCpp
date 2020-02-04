#ifndef _YSX_MEETING_ParticipantsCtrl_INTERFACE_H_
#define _YSX_MEETING_ParticipantsCtrl_INTERFACE_H_
#include "..\ysx_sdk_def.h"
#include "meeting_audio_interface.h"

BEGIN_YSX_SDK_NAMESPACE

/// \参与人信息变化回调接口
///
class IMeetingParticipantsCtrlEvent
{
public:
	/// \当参与人进入会议回调
	virtual void onUserJoin(unsigned int userID) = 0;

	/// \当参与人离开会议回调
	virtual void onUserLeft(unsigned int userID) = 0;

	/// \当主持人变更回调
	virtual void onHostChangeNotification(unsigned int userId) = 0;

	/// \举手放下状态回调
	virtual void onLowOrRaiseHandStatusChanged(bool bLow, unsigned int userid) = 0;

	/// \当参与人名称改变回调
	virtual void onUserNameChanged(unsigned int userId, const wchar_t* userName) = 0;
};

/// \会议参与人控制器
///
class IMeetingParticipantsController
{
public:
	/// \设置事件回调对象
	virtual SDKError SetEvent(IMeetingParticipantsCtrlEvent* pEvent) = 0;

	/// \获取参数人Id列表
	virtual std::vector<unsigned int > GetParticipantsList() = 0;

	/// \获取指定id用户信息
	virtual IUserInfo* GetUserByUserID(unsigned int userid) = 0;

	/// \会中放下所有人的手
	virtual SDKError LowerAllHands() = 0;

	/// \主持人更改指定参会人名字
	virtual SDKError ChangeUserName(const unsigned int userid, const wchar_t* userName, bool bSaveUserName) = 0;
};
END_YSX_SDK_NAMESPACE
#endif