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
	/// \��ȡ��Ҫ�����������Ϣ����
	virtual RequiredInfoType GetRequiredInfoType() = 0;

	/// \��������������Ļ����
	virtual bool InputMeetingPasswordAndScreenName(const wchar_t* meetingPassword, const wchar_t* screenName) = 0;

	// \ȡ������
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

	/// \���û�������
	virtual void Reset() = 0;

	/// \���ø�����Ƶ����λ��
	virtual void SetFloatVideoPos(WndPosition pos) = 0;

	/// \���ù��������Ƿ���ʾ
	virtual void SetSharingToolbarVisibility(bool bShow) = 0;

	/// \���õײ��������Ƿ���ʾ
	virtual void SetBottomFloatToolbarWndVisibility(bool bShow) = 0;

	/// \����ֱ�ӹ���ļ�����ID
	virtual void SetDirectShareMonitorID(const wchar_t* monitorID) = 0;

	/// \���û������λ��
	virtual void SetMeetingUIPos(WndPosition pos) = 0;

	/// \���õȴ������˶Ի���
	virtual void DisableWaitingForHostDialog(bool bDisable) = 0;

	/// \���������������ػ���ʾ������Ϣ
	virtual void HideMeetingInfoFromMeetingUITitle(bool bHide) = 0;

	/// \�����û��������������û���Id
	virtual void SetMeetingIDForMeetingUITitle(UINT64 meetingNumber) = 0;

	/// \�������ʱ���ô����������Ի���
	virtual void DisablePopupMeetingWrongPSWDlg(bool bDisable) = 0;

	/// \��ʼ�»���ʱ�����Զ�������������	
	virtual void EnableAutoEndOtherMeetingWhenStartMeeting(bool bEnable) = 0;

	/// \�������ʱ��Ƶ�Զ�����������������
	virtual void EnableAutoAdjustSpeakerVolumeWhenJoinAudio(bool bEnable) = 0;

	/// \�������ʱ�Զ�������˷������
	virtual void EnableAutoAdjustMicVolumeWhenJoinAudio(bool bEnable) = 0;

	/// \�����յ�����Զ�̿�������ʱ��������׼Զ�̿��ƶԻ���
	virtual void EnableApproveRemoteControlDlg(bool bEnable) = 0;

	/// \���þܾ�Զ�̿�����Ӧ�Ի���
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

	/// \brief �������������˹���
	/// \param bEnable specify claim host feature enable or not, default is enable.
	virtual void EnableClaimHostFeature(bool bEnable) = 0;
};
END_YSX_SDK_NAMESPACE
#endif