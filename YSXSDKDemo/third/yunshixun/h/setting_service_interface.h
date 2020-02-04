/*!
* \file setting_service_interface.h
* \brief Setting Service Interface
*
*/
#ifndef _YSX_SETTING_SERVICE_INTERFACE_H_
#define _YSX_SETTING_SERVICE_INTERFACE_H_
#include "ysx_sdk_def.h"
/// \brief YSX SDK Namespace
/// 
///
BEGIN_YSX_SDK_NAMESPACE
/// \����ͷ�豸��Ϣ
///
class ICameraInfo
{

public:
	/// \��ȡ����ͷ�豸Id
	virtual const wchar_t* GetDeviceId() = 0;

	/// \��ȡ����ͷ����
	virtual const wchar_t* GetDeviceName() = 0;

	/// \����ͷ�Ƿ�ѡ��
	virtual bool IsSelectedDevice() = 0;
};

/// \��˷��豸��Ϣ�ӿ�
///
class IMicInfo
{
public:
	/// \��ȡ��˷�Id
	virtual const wchar_t* GetDeviceId() = 0;

	/// \��ȡ��˷�����
	virtual const wchar_t* GetDeviceName() = 0;

	/// \��˷��Ƿ�ѡ��
	virtual bool IsSelectedDevice() = 0;
};

/// \��Ƶ�������豸��Ϣ�ӿ�
///
class ISpeakerInfo
{
public:
	/// \��ȡ������Id
	virtual const wchar_t* GetDeviceId() = 0;

	/// \��ȡ����������
	virtual const wchar_t* GetDeviceName() = 0;

	/// \�������Ƿ�ѡ��
	virtual bool IsSelectedDevice() = 0;
};

enum SettingTabPage
{
	SettingTabPage_General,
	SettingTabPage_Audio,
	SettingTabPage_Video
};

/*! \struct tagShowChatDlgParam
	\brief Show meeting chat dialog Parameter.
	A more detailed struct description.
*/
typedef struct tagShowSettingDlgParam
{
	HWND hParent;	///< �����ھ��
	int top;		///< ���ô���topλ��
	int left;		///< ���ô���leftλ��
	HWND hSettingWnd;///< �������ô��ھ��
	bool bShow;		///< ��ʾ������
	SettingTabPage eTabPageType;///��ʾ���ô������Ǹ�ѡ�
	tagShowSettingDlgParam()
	{
		hParent = NULL;
		top = 0;
		left = 0;
		hSettingWnd = NULL;
		bShow = true;
		eTabPageType = SettingTabPage_General;
	}
}ShowSettingDlgParam;


/// \�������ýӿ�
///
class IGeneralSettingContext
{
public:
	/// \����˫��ģʽ
	virtual SDKError EnableDualScreenMode(bool bEnable) = 0;

	/// \˫��ģʽ�Ƿ�����
	virtual bool IsDualScreenModeEnabled() = 0;

	/// \�򿪹رռ�ʻģʽ,��֧��window 7	
	virtual SDKError TurnOffAeroModeInSharing(bool bTurnoff) = 0;

	/// \�������Ƿ�رռ�ʻģʽ
	virtual bool IsAeroModeInSharingTurnOff() = 0;

	/// \�鿴��������ʱ���û�����Զ��ʺϴ���
	virtual SDKError EnableAutoFitToWindowWhenViewSharing(bool bEnable) = 0;

	/// \�Ƿ����ò鿴��������ʱ���û�����Զ��ʺϴ���
	virtual bool IsAutoFitToWindowWhenViewSharingEnabled() = 0;

	/// \�������ʱ���û�����Զ�����ȫ����Ƶģʽ
	virtual SDKError EnableAutoFullScreenVideoWhenJoinMeeting(bool bEnable) = 0;

	/// \�Ƿ������Զ�����ȫ����Ƶģʽ
	virtual bool IsAutoFullScreenVideoWhenJoinMeetingEnabled() = 0;

	/// \���û���÷���ģʽ
	virtual SDKError EnableSplitScreenMode(bool bEnable) = 0;

	/// \�Ƿ����÷���ģʽ
	virtual bool IsSplitScreenModeEnabled() = 0;
};

/// \��Ƶ���ýӿ�
///
class IVideoSettingContext
{
public:
	/// \��ȡ����ͷ�б�
	virtual std::vector<ICameraInfo* >* GetCameraList() = 0;

	/// \ѡ������ͷ
	virtual SDKError SelectCamera(const wchar_t* deviceId) = 0;

	/// \���û������Ƶ����Ч��
	virtual SDKError EnableVideoMirrorEffect(bool bEnable) = 0;

	/// \�Ƿ�������Ƶ����Ч��
	virtual bool IsVideoMirrorEffectEnabled() = 0;

	/// \���û��������Ч��
	virtual SDKError EnableFaceBeautyEffect(bool bEnable) = 0;

	/// \�Ƿ���������Ч��
	virtual bool IsFaceBeautyEffectEnabled() = 0;

	/// \���û���ø�����Ƶ
	virtual SDKError EnableHDVideo(bool bEnable) = 0;

	/// \�Ƿ����ø�����Ƶ
	virtual bool IsHDVideoEnabled() = 0;
};

/// \��Ƶ���ýӿ�
///
class IAudioSettingContext
{
public:
	/// \��ȡ��˷��б�
	virtual std::vector<IMicInfo* >* GetMicList() = 0;

	/// \ѡ����˷�
	virtual SDKError SelectMic(const wchar_t* deviceId, const wchar_t* deviceName) = 0;

	/// \��ȡ�������б�
	virtual std::vector<ISpeakerInfo* >* GetSpeakerList() = 0;

	/// \ѡ��������
	virtual SDKError SelectSpeaker(const wchar_t* deviceId, const wchar_t* deviceName) = 0;

	/// \�������ʱ���û�����Զ�������Ƶ
	virtual SDKError EnableAutoJoinAudio(bool bEnable) = 0;

	/// \�Ƿ����ü������ʱ���û�����Զ�������Ƶ	
	virtual bool IsAutoJoinAudioEnabled() = 0;

	/// \���û�����Զ�������˷�����
	virtual SDKError EnableAutoAdjustMic(bool bEnable) = 0;

	/// \�Ƿ������Զ�������˷�����
	virtual bool IsAutoAdjustMicEnabled() = 0;
};

/// \¼�����ýӿ�
///
class IRecordingSettingContext
{
public:
	/// \����¼���ļ�����·��
	virtual SDKError SetRecordingPath(const wchar_t* szPath) = 0;

	/// \��ȡ¼���ļ�����·��
	virtual const wchar_t* GetRecordingPath() = 0;
};

/// \���÷���
///
class ISettingService
{
public:
	/// \��ʾ���ô���
	virtual SDKError ShowSettingDlg(ShowSettingDlgParam& param) = 0;

	/// \�������ô���
	virtual SDKError HideSettingDlg() = 0;

	/// \��ȡ��������
	virtual IGeneralSettingContext* GetGeneralSettings() = 0;

	/// \��ȡ��Ƶ����
	virtual IAudioSettingContext* GetAudioSettings() = 0;

	/// \��ȡ��Ƶ����
	virtual IVideoSettingContext* GetVideoSettings() = 0;

	/// \��ȡ¼������
	virtual IRecordingSettingContext* GetRecordingSettings() = 0;
};
END_YSX_SDK_NAMESPACE
#endif