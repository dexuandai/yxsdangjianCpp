// stdafx.h : ��׼ϵͳ�����ļ��İ����ļ���
// ���Ǿ���ʹ�õ��������ĵ�
// �ض�����Ŀ�İ����ļ�
//

#pragma once

#include "targetver.h"

#define WIN32_LEAN_AND_MEAN             // �� Windows ͷ���ų�����ʹ�õ�����
#define _CRT_SECURE_NO_DEPRECATE
// Windows ͷ�ļ�: 
#include <windows.h>

// C ����ʱͷ�ļ�
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>


// TODO:  �ڴ˴����ó�����Ҫ������ͷ�ļ�
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


