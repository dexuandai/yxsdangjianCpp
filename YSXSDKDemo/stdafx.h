// stdafx.h : 标准系统包含文件的包含文件，
// 或是经常使用但不常更改的
// 特定于项目的包含文件
//

#pragma once

#include "targetver.h"

#define WIN32_LEAN_AND_MEAN             // 从 Windows 头中排除极少使用的资料
#define _CRT_SECURE_NO_DEPRECATE
// Windows 头文件: 
#include <windows.h>

// C 运行时头文件
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>


// TODO:  在此处引用程序需要的其他头文件
#include "duilib\h\UIlib.h"
#include "yunshixun\h\ysx_sdk_def.h"
#include "yunshixun\h\ysx_sdk.h"
#include "yunshixun\h\auth_service_interface.h"
#include "yunshixun\h\meeting_service_interface.h"
#include "yunshixun\h\setting_service_interface.h"
#include "yunshixun\h\meeting_service_components\meeting_participants_ctrl_interface.h"
#include "yunshixun\h\meeting_service_components\meeting_sharing_interface.h"
#include "yunshixun\h\meeting_service_components\meeting_configuration_interface.h"
#include "yunshixun\h\meeting_service_components\meeting_ui_ctrl_interface.h"
#include "yunshixun\h\meeting_service_components\meeting_recording_interface.h"
#ifdef INCLUDE_IM
#include "yunshixun\h\message_service_interface.h"
#endif // INCLUDE_IM


using namespace DuiLib;
using namespace YSXSDK;
using namespace std;


#ifdef _DEBUG
#pragma comment(lib, "duilib\\lib\\Dui.lib")
#pragma comment(lib,"yunshixun\\lib\\YSXSdk_d.lib")
#else
#pragma comment(lib, "duilib\\lib\\Dui.lib")
#pragma comment(lib,"yunshixun\\lib\\YSXSdk.lib")
#endif


