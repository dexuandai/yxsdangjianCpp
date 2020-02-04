//message_service_interface.h
#pragma once
#include "ysx_sdk_def.h"

BEGIN_YSX_SDK_NAMESPACE


class IMessageEvent
{
public:
	/// \当接收到普通消息
	virtual void onReceiveMessages(const std::string& jsonMsg) = 0;

	/// \当接收到命令消息
	virtual void onReceiveCmdMessages(const std::string& jsonMsg) = 0;
};

/// \IM消息服务
class IMMessageService
{
public:
	/// \设置消息事件回调对象
	virtual SDKError SetEvent(IMessageEvent* pEvent) = 0;

	/// \开始接收IM消息
	virtual SDKError Start() = 0;
	/// \停止接收IM消息
	virtual SDKError Stop() = 0;
};

END_YSX_SDK_NAMESPACE