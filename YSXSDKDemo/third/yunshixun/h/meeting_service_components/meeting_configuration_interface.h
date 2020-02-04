/*!
* \file meeting_configuration_interface.h
* \brief Configuration of Meeting Service Interface
* 
*/
#ifndef _YSX_MEETING_Configuration_INTERFACE_H_
#define _YSX_MEETING_Configuration_INTERFACE_H_
#include "..\ysx_sdk_def.h"

/// \brief YSX SDK Namespace
/// 
///
BEGIN_YSX_SDK_NAMESPACE

/// \brief Meeting Password And Screen Name Handler
enum RequiredInfoType
{
	REQUIRED_INFO_TYPE_NONE,
	REQUIRED_INFO_TYPE_Password,				///< if you want to join meeting, you need input password
	REQUIRED_INFO_TYPE_Password4WrongPassword,	///< you input a wrong password, please input again
	REQUIRED_INFO_TYPE_PasswordAndScreenName,	///< if you want to join meeting, you need input password and screen name
};

class IMeetingPasswordAndScreenNameHandler
{
public:
	/// \获取需要输入的所需信息类型
	virtual RequiredInfoType GetRequiredInfoType() = 0;

	/// \输入会议密码和屏幕名称
	virtual bool InputMeetingPasswordAndScreenName(const wchar_t* meetingPassword, const wchar_t* screenName) = 0;

	// \取消输入
	virtual void Cancel() = 0;
};

/// \brief Meeting Configuration Event callback
///
class IMeetingConfigurationEvent
{
public:
	/// \brief meeting need password or screen name callback
	/// \param pHandler which will be invoked for when this message type is received.
	virtual void onInputMeetingPasswordAndScreenNameNotification(IMeetingPasswordAndScreenNameHandler* pHandler) = 0;

	/// \brief meeting need password or screen name callback
	/// \param bShow Specifies show or hide your own airplay instruction window.
	/// \param airhostName the airhost name displayed on ios device
	virtual void onAirPlayInstructionWndNotification(bool bShow, const wchar_t* airhostName) = 0;
};

/// \brief Meeting Configuration Interface
///
class IMeetingConfiguration
{
public:
	/// \brief set a handler for meeting configuration notification.
	/// \param pEvent which will be invoked for when this message type is received.
	virtual void SetEvent(IMeetingConfigurationEvent* pEvent) = 0;

	/// \重置会议设置
	virtual void Reset() = 0;

	/// \设置浮动视频窗口位置
	virtual void SetFloatVideoPos(WndPosition pos) = 0;

	/// \设置共享工具栏是否显示
	virtual void SetSharingToolbarVisibility(bool bShow) = 0;

	/// \设置底部工具栏是否显示
	virtual void SetBottomFloatToolbarWndVisibility(bool bShow) = 0;

	/// \设置直接共享的监视器ID
	virtual void SetDirectShareMonitorID(const wchar_t* monitorID) = 0;

	/// \设置会议界面位置
	virtual void SetMeetingUIPos(WndPosition pos) = 0;

	/// \禁用等待主持人对话框
	virtual void DisableWaitingForHostDialog(bool bDisable) = 0;

	/// \会议界面标题中隐藏或显示会议信息
	virtual void HideMeetingInfoFromMeetingUITitle(bool bHide) = 0;

	/// \在设置会议界面标题上设置会议Id
	virtual void SetMeetingIDForMeetingUITitle(UINT64 meetingNumber) = 0;

	/// \加入会议时禁用错误密码错误对话框
	virtual void DisablePopupMeetingWrongPSWDlg(bool bDisable) = 0;

	/// \开始新会议时启用自动结束其他会议	
	virtual void EnableAutoEndOtherMeetingWhenStartMeeting(bool bEnable) = 0;

	/// \加入会议时音频自动调节扬声器的音量
	virtual void EnableAutoAdjustSpeakerVolumeWhenJoinAudio(bool bEnable) = 0;

	/// \加入会议时自动调节麦克风的音量
	virtual void EnableAutoAdjustMicVolumeWhenJoinAudio(bool bEnable) = 0;

	/// \当您收到其他远程控制请求时，启用批准远程控制对话框。
	virtual void EnableApproveRemoteControlDlg(bool bEnable) = 0;

	/// \启用拒绝远程控制响应对话框
	virtual void EnableDeclineRemoteControlResponseDlg(bool bEnable) = 0;

	/// \brief Enable leave meeting button in leave meeting window for host
	/// \param bEnable Specifies leave meeting button show or not in host leave meeting window, default is enable,
	virtual void EnableLeaveMeetingOptionForHost(bool bEnable) = 0;

	/// \brief Enable invite button in meeting window
	/// \param bEnable Specifies invite button show or not in meeting window, default is disable,
	/// if enable this feature, you need to handle onInviteBtnClicked event callback
	virtual void EnableInviteButtonOnMeetingUI(bool bEnable) = 0;

	/// \brief config hide or show input meeting password dialog
	/// \param bEnable specify hide or show input meeting password dialog, default is enable.
	/// if disable this option, you need to handle onInputMeetingPasswordAndScreenNameNotification event callback.
	virtual void EnableInputMeetingPasswordDlg(bool bEnable) = 0;

	// \brief Enable enter and exit full screen button on meeting ui. 
	/// \param bEnable Specifies enter and exit full screen button show or not in meeting window, default is enable.
	virtual void EnableEnterAndExitFullScreenButtonOnMeetingUI(bool bEnable) = 0;

	// \brief Enable left button double click for enter and exit full screen feature. 
	/// \param bEnable Specifies Enable or disable switch full screen mode via left button double click, default is enable.
	virtual void EnableLButtonDBClick4SwitchFullScreenMode(bool bEnable) = 0;

	/// \brief Set float video windows visibility flag
	/// \param bShow Specifies float video windows show or not during sharing.
	virtual void SetFloatVideoWndVisibility(bool bShow) = 0;

	/// \brief Pre-populate registration information of webinar
	/// \param email Specifies default email.
	/// \param username Specifies default username.
	virtual void PrePopulateWebinarRegistrationInfo(const wchar_t* email, const wchar_t* username) = 0;

	/// \brief Redirect click event of start share btn to IMeetingUIControllerEvent
	/// \param bRedirect Redirect or not. if true, you will recv onStartShareBtnClicked in IMeetingUIControllerEvent
	virtual void RedirectClickShareBTNEvent(bool bRedirect) = 0;

	/// \brief Redirect click event of end meeting btn to IMeetingUIControllerEvent
	/// \param bRedirect Redirect or not. if true, you will recv onEndMeetingBtnClicked in IMeetingUIControllerEvent
	virtual void RedirectClickEndMeetingBTNEvent(bool bRedirect) = 0;

	// \brief Enable tooltips popup window on meeting ui. 
	/// \param bEnable Specifies tooltips window show or not in meeting window, default is enable.
	virtual void EnableToolTipsShow(bool bEnable) = 0;

	/// \brief config hide or show the instruction window of IOS device sharing.
	/// \param bEnable specify hide or show the instruction window of IOS device sharing, default is enable.
	/// if disable this option, you need to handle onAirPlayInstructionWndNotification event callback to show or hide your own windows.
	virtual void EnableAirplayInstructionWindow(bool bEnable) = 0;

	/// \brief 启用声明主持人功能
	/// \param bEnable specify claim host feature enable or not, default is enable.
	virtual void EnableClaimHostFeature(bool bEnable) = 0;
};
END_YSX_SDK_NAMESPACE
#endif