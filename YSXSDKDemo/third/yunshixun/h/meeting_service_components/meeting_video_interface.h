
#ifndef _YSX_MEETING_VIDEO_INTERFACE_H_
#define _YSX_MEETING_VIDEO_INTERFACE_H_
#include "..\ysx_sdk_def.h"

BEGIN_YSX_SDK_NAMESPACE
enum VideoStatus
{
	Video_ON,
	Video_OFF,
};

class IMeetingVideoCtrlEvent
{
public:
	/// \用户视频状态变化回调
	virtual void onUserVideoStatusChange(unsigned int userId, VideoStatus status) = 0;

	/// \焦点用户变化回调
	virtual void onSpotlightVideoChangeNotification(bool bSpotlight, unsigned int userid) = 0;
};

/// \会议视频控制器接口
///
class IMeetingVideoController
{
public:
	/// \设置事件回调对象
	virtual SDKError SetEvent(IMeetingVideoCtrlEvent* pEvent) = 0;
	
	/// \关闭自己视频
	virtual SDKError MuteVideo() = 0;

	/// \打开自己视频
	virtual SDKError UnmuteVideo() = 0;

	/// \选定或取消选定视频
	virtual SDKError PinVideo(bool bPin, bool bFirstView, unsigned int userid) = 0;

	/// \焦点视频
	virtual SDKError SpotlightVideo(bool bSpotlight, unsigned int userid) = 0;

	/// \视频墙模式下隐藏或显示无视频用户
	virtual SDKError HideOrShowNoVideoUserOnVideoWall(bool bHide) = 0;
};
END_YSX_SDK_NAMESPACE
#endif