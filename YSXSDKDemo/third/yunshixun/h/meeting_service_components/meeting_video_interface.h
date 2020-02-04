
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
	/// \�û���Ƶ״̬�仯�ص�
	virtual void onUserVideoStatusChange(unsigned int userId, VideoStatus status) = 0;

	/// \�����û��仯�ص�
	virtual void onSpotlightVideoChangeNotification(bool bSpotlight, unsigned int userid) = 0;
};

/// \������Ƶ�������ӿ�
///
class IMeetingVideoController
{
public:
	/// \�����¼��ص�����
	virtual SDKError SetEvent(IMeetingVideoCtrlEvent* pEvent) = 0;
	
	/// \�ر��Լ���Ƶ
	virtual SDKError MuteVideo() = 0;

	/// \���Լ���Ƶ
	virtual SDKError UnmuteVideo() = 0;

	/// \ѡ����ȡ��ѡ����Ƶ
	virtual SDKError PinVideo(bool bPin, bool bFirstView, unsigned int userid) = 0;

	/// \������Ƶ
	virtual SDKError SpotlightVideo(bool bSpotlight, unsigned int userid) = 0;

	/// \��Ƶǽģʽ�����ػ���ʾ����Ƶ�û�
	virtual SDKError HideOrShowNoVideoUserOnVideoWall(bool bHide) = 0;
};
END_YSX_SDK_NAMESPACE
#endif