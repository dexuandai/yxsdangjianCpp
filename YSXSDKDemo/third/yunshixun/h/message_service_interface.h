//message_service_interface.h
#pragma once
#include "ysx_sdk_def.h"

BEGIN_YSX_SDK_NAMESPACE


class IMessageEvent
{
public:
	/// \�����յ���ͨ��Ϣ
	virtual void onReceiveMessages(const std::string& jsonMsg) = 0;

	/// \�����յ�������Ϣ
	virtual void onReceiveCmdMessages(const std::string& jsonMsg) = 0;
};

/// \IM��Ϣ����
class IMMessageService
{
public:
	/// \������Ϣ�¼��ص�����
	virtual SDKError SetEvent(IMessageEvent* pEvent) = 0;

	/// \��ʼ����IM��Ϣ
	virtual SDKError Start() = 0;
	/// \ֹͣ����IM��Ϣ
	virtual SDKError Stop() = 0;
};

END_YSX_SDK_NAMESPACE