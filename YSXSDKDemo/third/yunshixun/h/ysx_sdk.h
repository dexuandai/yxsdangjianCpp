#ifndef _YSX_SDK_H_
#define _YSX_SDK_H_
#include "ysx_sdk_def.h"

BEGIN_YSX_SDK_NAMESPACE
extern "C"
{
	class IMeetingService;
	class IAuthService;
	class ISettingService;	

#ifdef INCLUDE_IM
	class IMMessageService;
#endif

	class INetworkConnectionHelper;
	///初始化SDK
	SDK_API SDKError YSX_InitSDK(InitParam& initParam);
	
	///创建会议服务
	SDK_API SDKError YSX_CreateMeetingService(IMeetingService** ppMeetingService);
	///销户会议服务
	SDK_API SDKError YSX_DestroyMeetingService(IMeetingService* pMeetingService);

	///创建认证服务
	SDK_API SDKError YSX_CreateAuthService(IAuthService** ppAuthService);
	///销户认证服务
	SDK_API SDKError YSX_DestroyAuthService(IAuthService* pAuthService);

#ifdef INCLUDE_IM
	///创建IM服务
	SDK_API SDKError YSX_CreateIMMessageService(IMMessageService** ppMeetingService);
	///销毁IM服务
	SDK_API SDKError YSX_DestroyIMMessageService(IMMessageService* pMeetingService);
#endif

	///创建设置服务
	SDK_API SDKError YSX_CreateSettingService(ISettingService** ppSettingService);
	///销户设置服务
	SDK_API SDKError YSX_DestroySettingService(ISettingService* pSettingService);
	
	///创建网络服务
	SDK_API SDKError YSX_CreateNetworkConnectionHelper(INetworkConnectionHelper** ppNetworkHelper);
	///销毁网络服务
	SDK_API SDKError YSX_DestroyNetworkConnectionHelper(INetworkConnectionHelper* pNetworkHelper);

	///卸载SDK
	SDK_API SDKError YSX_CleanUPSDK();

	///获取SDK版本
	SDK_API const wchar_t* YSX_GetVersion();
	
}

END_YSX_SDK_NAMESPACE
#endif