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
/// \摄像头设备信息
///
class ICameraInfo
{

public:
	/// \获取摄像头设备Id
	virtual const wchar_t* GetDeviceId() = 0;

	/// \获取摄像头名称
	virtual const wchar_t* GetDeviceName() = 0;

	/// \摄像头是否被选择
	virtual bool IsSelectedDevice() = 0;
};

/// \麦克风设备信息接口
///
class IMicInfo
{
public:
	/// \获取麦克风Id
	virtual const wchar_t* GetDeviceId() = 0;

	/// \获取麦克风名称
	virtual const wchar_t* GetDeviceName() = 0;

	/// \麦克风是否被选择
	virtual bool IsSelectedDevice() = 0;
};

/// \音频扬声器设备信息接口
///
class ISpeakerInfo
{
public:
	/// \获取扬声器Id
	virtual const wchar_t* GetDeviceId() = 0;

	/// \获取扬声器名称
	virtual const wchar_t* GetDeviceName() = 0;

	/// \扬声器是否被选择
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
	HWND hParent;	///< 父窗口句柄
	int top;		///< 设置窗口top位置
	int left;		///< 设置窗口left位置
	HWND hSettingWnd;///< 返回设置窗口句柄
	bool bShow;		///< 显示或隐藏
	SettingTabPage eTabPageType;///显示设置窗口中那个选项卡
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


/// \常规设置接口
///
class IGeneralSettingContext
{
public:
	/// \启用双屏模式
	virtual SDKError EnableDualScreenMode(bool bEnable) = 0;

	/// \双屏模式是否启用
	virtual bool IsDualScreenModeEnabled() = 0;

	/// \打开关闭驾驶模式,仅支持window 7	
	virtual SDKError TurnOffAeroModeInSharing(bool bTurnoff) = 0;

	/// \共享中是否关闭驾驶模式
	virtual bool IsAeroModeInSharingTurnOff() = 0;

	/// \查看共享内容时启用或禁用自动适合窗口
	virtual SDKError EnableAutoFitToWindowWhenViewSharing(bool bEnable) = 0;

	/// \是否启用查看共享内容时启用或禁用自动适合窗口
	virtual bool IsAutoFitToWindowWhenViewSharingEnabled() = 0;

	/// \加入会议时启用或禁用自动进入全屏视频模式
	virtual SDKError EnableAutoFullScreenVideoWhenJoinMeeting(bool bEnable) = 0;

	/// \是否启用自动进入全屏视频模式
	virtual bool IsAutoFullScreenVideoWhenJoinMeetingEnabled() = 0;

	/// \启用或禁用分屏模式
	virtual SDKError EnableSplitScreenMode(bool bEnable) = 0;

	/// \是否启用分屏模式
	virtual bool IsSplitScreenModeEnabled() = 0;
};

/// \视频设置接口
///
class IVideoSettingContext
{
public:
	/// \获取摄像头列表
	virtual std::vector<ICameraInfo* >* GetCameraList() = 0;

	/// \选择摄像头
	virtual SDKError SelectCamera(const wchar_t* deviceId) = 0;

	/// \启用或禁用视频镜像效果
	virtual SDKError EnableVideoMirrorEffect(bool bEnable) = 0;

	/// \是否启用视频镜像效果
	virtual bool IsVideoMirrorEffectEnabled() = 0;

	/// \启用或禁用美颜效果
	virtual SDKError EnableFaceBeautyEffect(bool bEnable) = 0;

	/// \是否启用美颜效果
	virtual bool IsFaceBeautyEffectEnabled() = 0;

	/// \启用或禁用高清视频
	virtual SDKError EnableHDVideo(bool bEnable) = 0;

	/// \是否启用高清视频
	virtual bool IsHDVideoEnabled() = 0;
};

/// \音频设置接口
///
class IAudioSettingContext
{
public:
	/// \获取麦克风列表
	virtual std::vector<IMicInfo* >* GetMicList() = 0;

	/// \选择麦克风
	virtual SDKError SelectMic(const wchar_t* deviceId, const wchar_t* deviceName) = 0;

	/// \获取扬声器列表
	virtual std::vector<ISpeakerInfo* >* GetSpeakerList() = 0;

	/// \选择扬声器
	virtual SDKError SelectSpeaker(const wchar_t* deviceId, const wchar_t* deviceName) = 0;

	/// \加入会议时启用或禁用自动加入音频
	virtual SDKError EnableAutoJoinAudio(bool bEnable) = 0;

	/// \是否启用加入会议时启用或禁用自动加入音频	
	virtual bool IsAutoJoinAudioEnabled() = 0;

	/// \启用或禁用自动调整麦克风音量
	virtual SDKError EnableAutoAdjustMic(bool bEnable) = 0;

	/// \是否启用自动调整麦克风音量
	virtual bool IsAutoAdjustMicEnabled() = 0;
};

/// \录制设置接口
///
class IRecordingSettingContext
{
public:
	/// \设置录制文件保存路径
	virtual SDKError SetRecordingPath(const wchar_t* szPath) = 0;

	/// \获取录制文件保存路径
	virtual const wchar_t* GetRecordingPath() = 0;
};

/// \设置服务
///
class ISettingService
{
public:
	/// \显示设置窗口
	virtual SDKError ShowSettingDlg(ShowSettingDlgParam& param) = 0;

	/// \隐藏设置窗口
	virtual SDKError HideSettingDlg() = 0;

	/// \获取常规设置
	virtual IGeneralSettingContext* GetGeneralSettings() = 0;

	/// \获取音频设置
	virtual IAudioSettingContext* GetAudioSettings() = 0;

	/// \获取视频设置
	virtual IVideoSettingContext* GetVideoSettings() = 0;

	/// \获取录制设置
	virtual IRecordingSettingContext* GetRecordingSettings() = 0;
};
END_YSX_SDK_NAMESPACE
#endif