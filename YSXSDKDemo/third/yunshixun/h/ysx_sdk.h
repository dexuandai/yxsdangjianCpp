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
	///��ʼ��SDK
	SDK_API SDKError YSX_InitSDK(InitParam& initParam);
	
	///�����������
	SDK_API SDKError YSX_CreateMeetingService(IMeetingService** ppMeetingService);
	///�����������
	SDK_API SDKError YSX_DestroyMeetingService(IMeetingService* pMeetingService);

	///������֤����
	SDK_API SDKError YSX_CreateAuthService(IAuthService** ppAuthService);
	///������֤����
	SDK_API SDKError YSX_DestroyAuthService(IAuthService* pAuthService);

#ifdef INCLUDE_IM
	///����IM����
	SDK_API SDKError YSX_CreateIMMessageService(IMMessageService** ppMeetingService);
	///����IM����
	SDK_API SDKError YSX_DestroyIMMessageService(IMMessageService* pMeetingService);
#endif

	///�������÷���
	SDK_API SDKError YSX_CreateSettingService(ISettingService** ppSettingService);
	///�������÷���
	SDK_API SDKError YSX_DestroySettingService(ISettingService* pSettingService);
	
	///�����������
	SDK_API SDKError YSX_CreateNetworkConnectionHelper(INetworkConnectionHelper** ppNetworkHelper);
	///�����������
	SDK_API SDKError YSX_DestroyNetworkConnectionHelper(INetworkConnectionHelper* pNetworkHelper);

	///ж��SDK
	SDK_API SDKError YSX_CleanUPSDK();

	///��ȡSDK�汾
	SDK_API const wchar_t* YSX_GetVersion();
	
}

END_YSX_SDK_NAMESPACE
#endif