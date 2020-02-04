#include "stdafx.h"
#include "MainWnd.h"
#include <iostream>
#include <time.h>
#include "json\json.h" 

#pragma region �ַ�������

//unicode תΪ ascii 
std::string WideByte2Acsi(const std::wstring wstrcode)
{
	int asciisize = ::WideCharToMultiByte(CP_OEMCP, 0, wstrcode.c_str(), -1, NULL, 0, NULL, NULL);
	if (asciisize == ERROR_NO_UNICODE_TRANSLATION)
	{
		throw std::exception("Invalid UTF-8 sequence.");
	}
	if (asciisize == 0)
	{
		throw std::exception("Error in conversion.");
	}
	std::vector<char> resultstring(asciisize);
	int convresult = ::WideCharToMultiByte(CP_OEMCP, 0, wstrcode.c_str(), -1, &resultstring[0], asciisize, NULL, NULL);
	if (convresult != asciisize)
	{
		throw std::exception("La falla!");
	}
	return std::string(&resultstring[0]);
}

//Unicode ת Utf8 
std::string Unicode2Utf8(const std::wstring widestring)
{
	int utf8size = ::WideCharToMultiByte(CP_UTF8, 0, widestring.c_str(), -1, NULL, 0, NULL, NULL);
	if (utf8size == 0)
	{
		throw std::exception("Error in conversion.");
	}
	std::vector<char> resultstring(utf8size);
	int convresult = ::WideCharToMultiByte(CP_UTF8, 0, widestring.c_str(), -1, &resultstring[0], utf8size, NULL, NULL);
	if (convresult != utf8size)
	{
		throw std::exception("La falla!");
	}
	return std::string(&resultstring[0]);
}

//ascii ת Unicode 
std::wstring ASCII2WideByte(const std::string strascii)
{
	int widesize = MultiByteToWideChar(CP_ACP, 0, (char*)strascii.c_str(), -1, NULL, 0);
	if (widesize == ERROR_NO_UNICODE_TRANSLATION)
	{
		throw std::exception("Invalid UTF-8 sequence.");
	}
	if (widesize == 0)
	{
		throw std::exception("Error in conversion.");
	}
	std::vector<wchar_t> resultstring(widesize);
	int convresult = MultiByteToWideChar(CP_ACP, 0, (char*)strascii.c_str(), -1, &resultstring[0], widesize);
	if (convresult != widesize)
	{
		throw std::exception("La falla!");
	}
	return std::wstring(&resultstring[0]);
}

//ascii ת Utf8 
std::string ASCII2UTF_8(const std::string strAsciiCode)
{
	std::string strRet("");
	//�Ȱ� ascii תΪ unicode 
	std::wstring wstr = ASCII2WideByte(strAsciiCode);
	//���� unicode תΪ utf8 
	strRet = Unicode2Utf8(wstr);
	return strRet;
}

//UTF-8תUnicode 
std::wstring Utf82Unicode(const std::string utf8string)
{
	int widesize = ::MultiByteToWideChar(CP_UTF8, 0, utf8string.c_str(), -1, NULL, 0);
	if (widesize == ERROR_NO_UNICODE_TRANSLATION)
	{
		throw std::exception("Invalid UTF-8 sequence.");
	}
	if (widesize == 0)
	{
		throw std::exception("Error in conversion.");
	}
	std::vector<wchar_t> resultstring(widesize);
	int convresult = ::MultiByteToWideChar(CP_UTF8, 0, utf8string.c_str(), -1, &resultstring[0], widesize);
	if (convresult != widesize)
	{
		throw std::exception("La falla!");
	}
	return std::wstring(&resultstring[0]);
}

//utf-8 ת ascii 
std::string UTF_82ASCII(const std::string strUtf8Code)
{
	std::string strRet("");
	//�Ȱ� utf8 תΪ unicode 
	std::wstring wstr = Utf82Unicode(strUtf8Code);
	//���� unicode תΪ ascii 
	strRet = WideByte2Acsi(wstr);
	return strRet;
}

time_t StringToDatetime(const string& str)
{
	char *cha = (char*)str.data();             // ��stringת����char*��
	tm tm_;                                    // ����tm�ṹ�塣
	int year, month, day, hour, minute, second;// ����ʱ��ĸ���int��ʱ������
	sscanf(cha, "%d-%d-%d %d:%d:%d", &year, &month, &day, &hour, &minute, &second);// ��string�洢������ʱ�䣬ת��Ϊint��ʱ������
	tm_.tm_year = year - 1900;                 // �꣬����tm�ṹ��洢���Ǵ�1900�꿪ʼ��ʱ�䣬����tm_yearΪint��ʱ������ȥ1900��
	tm_.tm_mon = month - 1;                    // �£�����tm�ṹ����·ݴ洢��ΧΪ0-11������tm_monΪint��ʱ������ȥ1��
	tm_.tm_mday = day;                         // �ա�
	tm_.tm_hour = hour;                        // ʱ��
	tm_.tm_min = minute;                       // �֡�
	tm_.tm_sec = second;                       // �롣
	tm_.tm_isdst = 0;                          // ������ʱ��
	time_t t_ = mktime(&tm_);                  // ��tm�ṹ��ת����time_t��ʽ��
	return t_;                                 // ����ֵ�� 
}

#pragma endregion

#define WM_ADDLISTITEM WM_USER + 50

MainWnd::MainWnd() :
	m_AuthService(NULL),
	m_MeetingService(NULL),
	m_MeetingParticipantsController(NULL)
{

}

MainWnd::~MainWnd()
{
}

LPCTSTR		MainWnd::GetWindowClassName() const
{
	return L"MainWnd";
}

CDuiString	MainWnd::GetSkinFile()
{
	return L"MainWnd.xml";
}

void		MainWnd::InitWindow()
{
	m_EditUserName = static_cast<CEditUI*>(m_pm.FindControl(_T("edit_UserName")));
	m_EditPassword = static_cast<CEditUI*>(m_pm.FindControl(_T("edit_Password")));
	m_EditMeetingId = static_cast<CEditUI*>(m_pm.FindControl(_T("edit_MeetingId")));
	m_EditMeetingNo = static_cast<CEditUI*>(m_pm.FindControl(_T("edit_MeetingNo")));

	m_EditMeetingTopic = static_cast<CEditUI*>(m_pm.FindControl(_T("edit_MeetingTopic")));
	m_EditUser = static_cast<CEditUI*>(m_pm.FindControl(_T("edit_Users")));
	m_EditToken = static_cast<CEditUI*>(m_pm.FindControl(_T("edit_Token")));


	m_AppKey = static_cast<CEditUI*>(m_pm.FindControl(_T("edit_AppKey")));
	m_AppSecret = static_cast<CEditUI*>(m_pm.FindControl(_T("edit_AppSecret")));
	m_ApiKey = static_cast<CEditUI*>(m_pm.FindControl(_T("edit_ApiKey")));
	m_ApiSecret = static_cast<CEditUI*>(m_pm.FindControl(_T("edit_ApiSecret")));

	m_LabelMsg = static_cast<CLabelUI*>(m_pm.FindControl(_T("lbl_Msg")));
	m_LabelUName = static_cast<CLabelUI*>(m_pm.FindControl(_T("lbl_UserName")));

	m_LayoutKeyInfo = static_cast<CHorizontalLayoutUI*>(m_pm.FindControl(_T("layout_KeyInfo")));
	m_LayoutLogin = static_cast<CHorizontalLayoutUI*>(m_pm.FindControl(_T("layout_Login")));
	m_LayoutMeeting = static_cast<CHorizontalLayoutUI*>(m_pm.FindControl(_T("layout_Meeting")));
	m_LayoutMeetingControl = static_cast<CHorizontalLayoutUI*>(m_pm.FindControl(_T("layout_MeetingControl")));


	m_UserList = static_cast<CListUI*>(m_pm.FindControl(_T("userlist")));
	if (m_UserList)
	{
		m_UserList->SetTextCallback(this);
	}

	CenterWindow();
	SDKInit();
}

void MainWnd::Notify(TNotifyUI& msg)
{
    auto senderName = msg.pSender->GetName();
    if (msg.sType == L"selectchanged")
    {
        if (senderName == L"chk_audio")
        {
            CCheckBoxUI* chk = static_cast<CCheckBoxUI*>(m_pm.FindControl(_T("chk_audio")));
            if (chk && m_MeetingService)
            {
                m_MeetingService->MuteMicWhenStartOrJoinMeeting(!chk->GetCheck());
            }
        }
    }
    else if (msg.sType == L"click")
    {
        OnClick(msg);
    }
}

/*
1:����SDK��ʼ��
*/
void MainWnd::SDKInit()
{
	auto appKeydata = m_AppKey->GetText();
	if (appKeydata.IsEmpty())
	{
		ShowMsg(L"������AppKey");
		return;
	}

	auto appSecretdata = m_AppSecret->GetText();
	if (appSecretdata.IsEmpty())
	{
		ShowMsg(L"������AppSecret");
		return;
	}

	auto apiKeydata = m_ApiKey->GetText();
	if (apiKeydata.IsEmpty())
	{
		ShowMsg(L"������ApiKey");
		return;
	}

	auto apiSecretdata = m_ApiSecret->GetText();
	if (apiSecretdata.IsEmpty())
	{
		ShowMsg(L"������ApiSecret");
		return;
	}
	TCHAR appKeyBuf[MAX_PATH] = { 0 };
	_stprintf(appKeyBuf, _T("%s"), appKeydata.GetData());
	appKey = appKeyBuf;

	TCHAR appSecretBuf[MAX_PATH] = { 0 };
	_stprintf(appSecretBuf, _T("%s"), appSecretdata.GetData());
	appSecret = appSecretBuf;

	TCHAR apiKeyBuf[MAX_PATH] = { 0 };
	_stprintf(apiKeyBuf, _T("%s"), apiKeydata.GetData());
	apiKey = apiKeyBuf;

	TCHAR apiSecretBuf[MAX_PATH] = { 0 };
	_stprintf(apiSecretBuf, _T("%s"), apiSecretdata.GetData());
	apiSecret = apiSecretBuf;

	YSXSDK::InitParam param;
	param.emLanguageID = YSXSDK::LANGUAGE_Chinese_Simplified;
	param.enableLog = true;//����ʱ�ر���־
	param.strBrandingName = L"����ѶDemo";

	//1.1SDK��ʼ��
	auto initResult = YSX_InitSDK(param);

	if (initResult == SDKError::SDKERR_SUCCESS)
	{
		//1.2��ʼ�����,������֤����
		auto createResult = YSX_CreateAuthService(&m_AuthService);
		if (createResult == SDKError::SDKERR_SUCCESS)
		{
			if (m_AuthService)
			{
				//1.3�����¼��ص�
				m_AuthService->SetEvent(this);

				//TODO:��дapikey,appkey
				AuthParam authParam;
				authParam.apiKey = apiKey;
				authParam.apiSecret = apiSecret;
				authParam.appKey = appKey;
				authParam.appSecret = appSecret;

				//1.4��SDK Key,Secret������֤
				auto errorCode = m_AuthService->SDKAuth(authParam);
				if (errorCode != SDKError::SDKERR_SUCCESS)
				{
					::MessageBox(NULL, L"SDK��֤ʧ��", L"������ʾ", MB_OK);
				}
			}
		}
		else
		{
			::MessageBox(NULL, L"SDK������֤����ʧ��", L"������ʾ", MB_OK);
		}
	}
	else
	{
		::MessageBox(NULL, L"SDK��ʼ��ʧ��", L"������ʾ", MB_OK);
	}
}

void MainWnd::OnClick(TNotifyUI& msg)
{
	auto controlName = msg.pSender->GetName();
	ShowMsg(L"����");
	if (controlName == L"btn_Login")
	{
		//SDKInit();
		Login();
	}
	else 	if (controlName == L"btn_StartMeeting")
	{
        auto txt = m_EditMeetingNo->GetText();
        auto str_Number = WideByte2Acsi(txt.GetData());
        auto meetingNo = atoll(str_Number.c_str());
        StartMeeting(meetingNo);
// 		if (!txt.IsEmpty())
// 		{
// 			auto str_Number = WideByte2Acsi(txt.GetData());
// 			auto meetingNo = atoll(str_Number.c_str());
// 			StartMeeting(meetingNo);
// 		}
// 		else
// 		{
// 			ShowMsg(L"������������");
// 		}
	}
	else 	if (controlName == L"btn_JoinMeeting")
	{
		auto meetingNum = m_EditMeetingNo->GetText();

		if (!meetingNum.IsEmpty())
		{
			auto str_Number = WideByte2Acsi(meetingNum.GetData());
			auto meetingNo = atoll(str_Number.c_str());
			JoinMeeting(L"", meetingNo);
		}
		else
		{
			ShowMsg(L"������������");
		}
    }
    else 	if (controlName == L"btn_JoinHDMeeting")
    {
        auto meetingNum = m_EditMeetingId->GetText();

        if (!meetingNum.IsEmpty())
        {
            JoinMeeting(meetingNum.GetData(), 0, 1);
        }
        else
        {
            ShowMsg(L"���������ID");
        }
    }
	else 	if (controlName == L"btn_LeaveMeeting")
	{
        m_MeetingService->Leave(LeaveMeetingCmd::LEAVE_MEETING);
	}
	else 	if (controlName == L"btn_EndMeeting")
	{
        m_MeetingService->Leave(LeaveMeetingCmd::END_MEETING);
	}
	else 	if (controlName == L"btn_close")
	{
		Logout();
	}
	else if (controlName == L"btn_min")
	{
		SendMessage(WM_SYSCOMMAND, SC_MINIMIZE, 0);
	}
	else if (controlName == L"btn_LockMeeting")
	{
		LockMeeting();
	}
	else if (controlName == L"btn_UnLockMeeting")
	{
		UnLockMeeting();
	}
	else if (controlName == L"btn_Setting")
	{
		SDKInit();
	}
	else if (controlName == L"btn_Share")
	{
		m_MeetingService->GetMeetingShareController()->StartAppShare(NULL);
	}
	else if (controlName == L"btn_StopShare")
	{
		m_MeetingService->GetMeetingShareController()->StopShare();
	}
	else if (controlName == L"btn_StartInstanceMeeting")
	{		
		StartInstanceMeeting(m_EditMeetingTopic->GetText().GetData(), m_EditUser->GetText().GetData());
	}
	//
	//SetAppKeyInfo()
}

LRESULT MainWnd::HandleCustomMessage(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	bHandled = FALSE;
	LRESULT lRes = 0;
	return lRes;
}

LRESULT MainWnd::OnClose(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& bHandled)
{
	bHandled = false;
	Logout();
	YSX_CleanUPSDK();
	return 0;
}

void MainWnd::InitMeetingService()
{
	if (m_MeetingService == NULL)
	{
		//�����������
		if (YSX_CreateMeetingService(&m_MeetingService) == SDKError::SDKERR_SUCCESS)
		{
			if (m_MeetingService)
			{
				//���û���ص��¼�
				m_MeetingService->SetEvent(this);

				//��ȡ��������˿�����
				m_MeetingParticipantsController = m_MeetingService->GetMeetingParticipantsController();

                m_MeetingService->GetMeetingAudioController()->EnableMuteOnEntry(true);
                m_MeetingService->MuteMicWhenStartOrJoinMeeting(true);

                m_MeetingService->GetMeetingShareController()->SetEvent(this);

				if (m_MeetingParticipantsController)
				{
					//���òλ��˻ص��¼�
					m_MeetingParticipantsController->SetEvent(this);
				}
			}

#ifdef INCLUDE_IM
            //����IM����
            if (YSX_CreateIMMessageService(&m_MessageService) == SDKError::SDKERR_SUCCESS)
            {
                if (m_MessageService)
                {
                    //����IM�ص��¼�
                    m_MessageService->SetEvent(this);
                    //��ʼ����IM��Ϣ
                    m_MessageService->Start();
                }
            }
            else
            {
                ::MessageBox(NULL, L"����IM����ʧ��", L"������ʾ", MB_OK);
            }
#endif // INCLUDE_IM

		}
		else
		{
			::MessageBox(NULL, L"SDK�����������ʧ��", L"������ʾ", MB_OK);
		}
	}
}

#pragma region IAuthServiceEvent
void MainWnd::onAuthenticationReturn(AuthResult ret)
{
	switch (ret)
	{
	case YSXSDK::AUTHRET_SUCCESS:
		m_LayoutKeyInfo->SetVisible(false);
		m_LayoutLogin->SetVisible(true);
		break;
	case YSXSDK::AUTHRET_KEYORSECRETEMPTY:
		::MessageBox(NULL, L"SDK��֤ʧ�� key �� secret ����Ϊ��", L"������ʾ", MB_OK);
		break;
	case YSXSDK::AUTHRET_KEYORSECRETWRONG:
		::MessageBox(NULL, L"SDK��֤ʧ�� key �� secret ����", L"������ʾ", MB_OK);
		break;
	case YSXSDK::AUTHRET_ACCOUNTNOTSUPPORT:
		::MessageBox(NULL, L"SDK��֤ʧ�� Account ��֧��", L"������ʾ", MB_OK);
		break;
	case YSXSDK::AUTHRET_ACCOUNTNOTENABLESDK:
		::MessageBox(NULL, L"SDK��֤ʧ�� Account û������SDK", L"������ʾ", MB_OK);
		break;
	case YSXSDK::AUTHRET_UNKNOWN:
		::MessageBox(NULL, L"SDK��֤ʧ��δ֪�쳣", L"������ʾ", MB_OK);
		break;
	case YSXSDK::AUTHRET_NONE:
		break;
	default:
		break;
	}
}

void MainWnd::onLoginRet(LOGINSTATUS ret)
{
	switch (ret)
	{
    case YSXSDK::LOGIN_IDLE:
        ShowMsg(L"δ��¼");
		break;
    case YSXSDK::LOGIN_PROCESSING:
        ShowMsg(L"��¼��");
		break;
	case YSXSDK::LOGIN_SUCCESS:
		m_LayoutLogin->SetVisible(false);
		m_LayoutMeeting->SetVisible(true);
		InitMeetingService();
		m_LabelUName->SetText(m_AuthService->GetCurrentUser()->UserName.c_str());
		ShowMsg(L"��¼�ɹ�");
		break;
	case YSXSDK::LOGIN_FAILED:
		ShowMsg(L"��¼ʧ��");
		break;
#ifdef INCLUDE_IM
    case YSXSDK::LOGIN_LOGINIM_FAILED:
        ShowMsg(L"��¼IMʧ��");
        break;
    case YSXSDK::LOGIN_LOGINMEETING_FAILED:
        ShowMsg(L"��¼�������ʧ��");
        break;
    case YSXSDK::LOGIN_EXCEPTION:
        break;
    case YSXSDK::LOGIN_USER_NOT_EXIST:
        break;
    case YSXSDK::LOGIN_ZHUMU_USER__NOT_EXIST:
        break;
    case YSXSDK::LOGIN_USER_ENTERPRISE_ERROR:
        break;
    case YSXSDK::LOGIN_MOBILE_NOT_EXIST:
        break;
    case YSXSDK::LOGIN_PASSWORD_ERROR:
        ShowMsg(L"�������");
        break;
    case YSXSDK::LOGIN_TICKET_NOT_EXIST:
        break;
    case YSXSDK::LOGIN_SIGN_ERROR:
        break;
    case YSXSDK::LOGIN_INVALID_TOKEN:
        break;
    case YSXSDK::LOGIN_TOKEN_EXPIRED:
        break;
    case YSXSDK::LOGIN_APIKEY_NOT_EXIST:
        break;
    case YSXSDK::LOGIN_APIKEYENTERPRISE_NO_MATCH:
        break;
    case YSXSDK::LOGIN_TICKET_EXPIRED:
        break;
    case YSXSDK::LOGIN_CONTACT_SERVICE_ERROR:
        break;
#endif // INCLUDE_IM

	default:
		break;
	}

}

void MainWnd::onLogout()
{

}

void MainWnd::onConnect()
{

}

std::wstring s2ws(const std::string& s)
{
    setlocale(LC_ALL, "chs");

    const char* _Source = s.c_str();
    size_t _Dsize = s.size() + 1;
    wchar_t *_Dest = new wchar_t[_Dsize];
    wmemset(_Dest, 0, _Dsize);
    mbstowcs(_Dest, _Source, _Dsize);
    std::wstring result = _Dest;
    delete[]_Dest;

    setlocale(LC_ALL, "C");

    return result;
}

void MainWnd::onDisconnect(const MsgErrorCode code)
{
	MessageBox(GetHWND(), L"�˺��������豸��¼", L"�˳�����", MB_OK);
	Close();
}
#pragma endregion

#pragma region IMeetingServiceEvent
void MainWnd::onMeetingStatusChanged(MeetingStatus status, int iResult)
{
//     HWND first;
//     HWND second;
//     m_MeetingService->GetUIController()->GetMeetingUIWnd(first, second);
//     if (first)
//     {
//         ::MoveWindow(first, 0, 0, 1000, 800, true);
//     }

	if (status == MeetingStatus::MEETING_STATUS_INMEETING)
	{
        char buf[1025];
        sprintf(buf, "%u", m_MeetingService->GetMeetingInfo()->GetMeetingNumber());
        ShowMsg(s2ws(buf));

//         HWND hWnd = FindWindow(L"Notepad", NULL);
//         m_MeetingService->GetMeetingShareController()->StartAppShare(hWnd);

		m_LayoutMeeting->SetVisible(false);
		m_LayoutMeetingControl->SetVisible(true);
	}
	else if (status == MeetingStatus::MEETING_STATUS_ENDED)
	{
		m_LayoutMeeting->SetVisible(true);
		m_LayoutMeetingControl->SetVisible(false);
	}
    else if (status == MeetingStatus::MEETING_STATUS_FAILED)
    {
        if (iResult == MeetingFailCode::MEETING_FAIL_MEETING_USER_FULL)
        {
            MessageBox(m_hWnd, L"�λ���Ա�������޷����룡", L"����", MB_OK);
        }
    }
}
void MainWnd::onMeetingStatisticsWarningNotification(StatisticsWarningType type)
{

}
void MainWnd::onStartLeaveMeetingCountdown(int minutes)
{
	::MessageBox(NULL, L"��ʼ����ʱ", L"�����˺�", MB_OK);
}
#pragma endregion

#ifdef INCLUDE_IM
#pragma region IMessageEvent
void MainWnd::onReceiveMessages(const std::string& jsonMsg)
{
    ::OutputDebugStringA(jsonMsg.c_str());
    //��Ϣ����JSON�ַ���
    //ʾ��:�������
    //{
    //		"UserName": "1053854278",
    //		"HeadPath" : null,
    //		"Topic" : "��2323",
    //		"StartTime" : "2018-02-09 10:05:00.000",
    //		"MeetingId" : "123589888",
    //		"MeetingNo" : 15604690822,
    //		"MeetingType" : 1,
    //		"IsMeetingEnd" : false,
    //		"Id" : "c45df9b699e44b7b8bc24c86ac2a5183",
    //		"Action" : 0,
    //		"SendTime" : "2018-02-09 10:05:24.017"
    //}

    //���ݽṹ
    /*
    public enum IMAction
    {
    /// <summary>
    /// �������
    /// </summary>
    Join = 0,
    /// <summary>
    /// ��ʼ����
    /// </summary>
    Start = 1,
    /// <summary>
    /// ���и����豸
    /// </summary>
    CallHDDevice = 3,

    /// <summary>
    /// �����ն˵�¼
    /// </summary>
    KickedOut = 4,

    /// <summary>
    /// �û������Ѹ���
    /// </summary>
    PasswordChanged = 5,

    /// <summary>
    /// �û��ѱ�����
    /// </summary>
    UserDeleted = 6,

    /// <summary>
    /// �˳�����
    /// </summary>
    QuitMeeting = 7,

    /// <summary>
    /// �����Լ�
    /// </summary>
    MuteSelf = 8,

    /// <summary>
    /// �������
    /// </summary>
    UnMuteSelf = 9,

    /// <summary>
    /// 323�豸״̬���
    /// </summary>
    HDDeviceStatusChange = 10
    }

    //0:�������
    var body = new MeetingMessage
    {
    Id = Utils.GetGuid(),
    MeetingId = instantMeeting.Id,
    MeetingNo = instantMeeting.MeetingNo,
    Topic = instantMeeting.MeetingTopic,
    UserName = instantMeeting.HostName,
    HeadPath = host.HeadPath,
    MeetingType = 0,//��������0:��ý�����,1:�������
    Action = (int)IMAction.Join,
    StartTime = instantMeeting.StartTime,
    SendTime = DateTime.Now
    };

    //1:��������
    var body = new MeetingMessage
    {
    Id = Utils.GetGuid(),
    MeetingId = meeting.Id,
    MeetingNo = meeting.MeetingNo,
    Topic = meeting.MeetingTopic,
    MeetingType = 0,//��������0:��ý�����,1:�������
    UserName = meeting.HostName,
    HeadPath = host?.HeadPath,
    Action = (int)IMAction.Start,
    StartTime = meeting.StartTime,
    SendTime = DateTime.Now
    };


    //3:����323�豸
    var callOutMsg = new CalloutMessage
    {
    Id = Utils.GetGuid(),
    MeetingNo = instantMeeting.MeetingNo,
    Action = (int)IMAction.CallHDDevice,
    Devices = new List<H323Message>(),
    SendTime = DateTime.Now
    };
    public class H323Message
    {
    /// <summary>
    /// �豸����
    /// </summary>
    public string DeviceName { get; set; }

    /// <summary>
    /// 1:H323,2:SIP
    /// </summary>
    public int DeviceType { get; set; }

    /// <summary>
    /// ��ʽ: +861053854221@111.13.137.146
    /// </summary>
    public string IP { get; set; }
    }

    //4:�˺��������豸��¼,ע����ǰ
    var body = new KickOutMessage
    {
    Action = (int)IMAction.KickedOut,
    SendTime = DateTime.Now,
    Device = data.Device,
    Ticket = data.ApiTicket
    };

    //8:�����Լ�
    var msg = new MuteMeetingMessage
    {
    Id = Utils.GetGuid(),
    MeetingId = meeting.Id,
    MeetingType = meeting.Type,//��������0:��ý�����,1:�������
    Action = (int)IMAction.MuteSelf,
    SendTime = DateTime.Now
    };

    //9:�������
    var msg = new MuteMeetingMessage
    {
    Id = Utils.GetGuid(),
    MeetingId = meeting.Id,
    MeetingType = meeting.Type,//��������0:��ý�����,1:�������
    Action = (int)IMAction.UnMuteSelf,
    SendTime = DateTime.Now
    };

    //10:323�豸״̬�ı�
    var msg = new UserStatusChangeMessage
    {
    Id = Utils.GetGuid(),
    Action = (int)IMAction.HDDeviceStatusChange,
    MeetingId = meeting.Id,
    MeetingNo = meeting.MeetingNo,
    Status =data.Status,
    UserId = user.UserId
    };
    */

    Json::Reader reader;
    Json::Value data;

    if (!reader.parse(jsonMsg, data, false))
    {
        return;
    }

    if (!data.isNull())
    {
        std::string sendTime = data["SendTime"].asString();
        //TODO:�ж���Ϣ�Ƿ����,��ʱʱ���������Լ�ҵ��

        IMAction action = (IMAction)data["Action"].asInt();
        wstring meetingId = L"";
        if (data["MeetingId"].isString())
        {
            meetingId = Utf82Unicode(data["MeetingId"].asString());
        }
        switch (action)
        {
        case YSXSDK::MEETING_JOINMEETING:
        case YSXSDK::MEETING_STARTMEETING:
            //TODO:�������崰��,���û�ѡ���Ƿ����

            if (m_MeetingService->GetMeetingStatus() != MEETING_STATUS_INMEETING)
            {
                auto meetingNo = data["MeetingNo"].asInt64();
                auto meetingType = data["MeetingType"].asInt();

                // ����demoû�п�����������������ֻ���ݽ������Ƿ�ѡ�ж����(�ӻ�)�Ƿ�����˷�(�ر���Ƶ)
                bool disableAudio = data["DisableAudio"].asBool();
                bool disableVideo = data["DisableVideo"].asBool();
                if (action == MEETING_JOINMEETING)
                {
                    JoinMeeting(meetingId, meetingNo, meetingType);
                }
                else
                {
                    StartMeeting(meetingNo);
                }
            }
            break;
        case YSXSDK::MEETING_STATUS_CHANGE:
            break;
        case YSXSDK::MEETING_CALLH323:
            break;
        case YSXSDK::LOGOFF_ACTION:
            break;
        case YSXSDK::USER_CHANGEPASSWORD:
            break;
        case YSXSDK::USER_DESTROY:
            break;
        case YSXSDK::QUIT_MEETING:
            if (m_MeetingService->GetMeetingStatus() == MEETING_STATUS_INMEETING)
            {
                if (data["MeetingType"].asInt() == 1)
                {
                    auto meetingId = data["MeetingId"].asString();
                    std::wstring currentMeetingNo = m_MeetingService->GetHDMeetingID();
                    if (meetingId == WideByte2Acsi(currentMeetingNo))
                    {
                        m_MeetingService->Leave(LeaveMeetingCmd::LEAVE_MEETING);
                    }
                }
                else
                {
                    auto meetingNo = data["MeetingNo"].asInt();
                    auto currentMeetingNo = m_MeetingService->GetMeetingInfo()->GetMeetingNumber();
                    if (meetingNo == currentMeetingNo)
                    {
                        m_MeetingService->Leave(LeaveMeetingCmd::LEAVE_MEETING);
                    }
                }
                //
            }
            break;
        case YSXSDK::MUTE_SELF:
        {
            IMeetingParticipantsController* participantsController = m_MeetingService->GetMeetingParticipantsController();
            if (participantsController)
            {
                std::vector<unsigned int > userList = participantsController->GetParticipantsList();
                for (unsigned int i = 0; i < userList.size(); ++i)
                {
                    IUserInfo* userInfo = participantsController->GetUserByUserID(userList[i]);
                    if (userInfo && userInfo->IsMySelf())
                    {
                        IMeetingAudioController* audioController = m_MeetingService->GetMeetingAudioController();
                        if (audioController)
                        {
                            audioController->MuteAudio(userList[i]);
                        }
                        break;
                    }
                }
            }
            break;
        }
        case YSXSDK::UNMUTE_SELF:
        {
            IMeetingParticipantsController* participantsController = m_MeetingService->GetMeetingParticipantsController();
            if (participantsController)
            {
                std::vector<unsigned int > userList = participantsController->GetParticipantsList();
                for (unsigned int i = 0; i < userList.size(); ++i)
                {
                    IUserInfo* userInfo = participantsController->GetUserByUserID(userList[i]);
                    if (userInfo && userInfo->IsMySelf())
                    {
                        IMeetingAudioController* audioController = m_MeetingService->GetMeetingAudioController();
                        if (audioController)
                        {
                            audioController->UnMuteAudio(userList[i]);
                        }
                        break;
                    }
                }
            }
            break;
        }
        case YSXSDK::HD_DEVICE_STATUS_CHANGE:
            break;
        default:
            break;
        }

    }

}
void MainWnd::onReceiveCmdMessages(const std::string& jsonMsg)
{
    MessageBox(NULL, ASCII2WideByte(jsonMsg).c_str(), L"IM��Ϣ", MB_OK);
}
#pragma endregion
#endif // INCLUDE_IM

#pragma region IMeetingParticipantsCtrlEvent

void MainWnd::onUserJoin(unsigned int userId)
{
	vector<unsigned int>::iterator result = find(userList.begin(), userList.end(), userId); //����3
	if (result == userList.end()) //û�ҵ�
	{
		userList.push_back(userId);
	}

	RefreshUserList();
}

void MainWnd::onUserLeft(unsigned int userId)
{
	vector<unsigned int>::iterator result = find(userList.begin(), userList.end(), userId); //����3
	if (result != userList.end()) //û�ҵ�
	{
		userList.erase(result);
	}
	RefreshUserList();
}

void MainWnd::onHostChangeNotification(unsigned int userId)
{

}

void MainWnd::onLowOrRaiseHandStatusChanged(bool bLow, unsigned int userid)
{

}

void MainWnd::onUserNameChanged(unsigned int userId, const wchar_t* userName)
{

}
#pragma endregion

void MainWnd::onSharingStatus(SharingStatus status, unsigned int userId)
{
    if (status == Sharing_Self_Send_Begin)
    {
        m_MeetingService->GetUIController()->MoveFloatVideoWnd(500, 500);
    }
}

void MainWnd::onLockShareStatus(bool bLocked)
{

}

void MainWnd::onShareContentNotification(ShareInfo& shareInfo)
{

}

LPCTSTR MainWnd::GetItemText(CControlUI* pList, int iItem, int iSubItem)
{
	auto userId = pList->GetTag();
	auto user = m_MeetingParticipantsController->GetUserByUserID(userId);
	if (user)
	{
		switch (iSubItem)
		{
		case 0:
		{
			TCHAR szBuf[MAX_PATH] = { 0 };
			wsprintf(szBuf, _T("%d"), user->GetUserID());
			pList->SetUserData(szBuf);
		}
		break;
		case 1:
			pList->SetUserData(user->GetUserNameW());
			break;
        case 2:
            pList->SetUserData(user->GetAccountID());
            break;
		}
		return pList->GetUserData();
	}
	return NULL;
}

void MainWnd::Login()
{
	auto token = m_EditToken->GetText();

	LoginParam param;

	if (token.IsEmpty())
	{
		auto mobile = m_EditUserName->GetText();
		if (mobile.IsEmpty())
		{
			ShowMsg(L"�������ֻ�����");
			return;
		}
		auto password = m_EditPassword->GetText();
		if (password.IsEmpty())
		{
			ShowMsg(L"����������");
			return;
		}
		param.loginType = LoginType::LoginType_Mobile;//�ֻ�����,�����¼
		param.userName = mobile;
		param.password = password;
	}
	else
	{
		param.loginType = LoginType::LoginType_Token;//ͨѶ¼Token��¼
		param.token = token;
	}

	//��¼�ɹ�ʧ����onLoginRet�ص��л�ȡ
	auto result = m_AuthService->Login(param);
	if (result != SDKError::SDKERR_SUCCESS)
	{
		ShowMsg(L"��¼ʧ��");
	}
}

void MainWnd::Logout()
{
	if (m_AuthService)
	{
		if (m_AuthService->GetLoginStatus() == YSXSDK::LOGINSTATUS::LOGIN_SUCCESS)
		{
			m_AuthService->Logout();
		}
	}

	Close();
}

void MainWnd::StartMeeting(UINT64 meetingNo)
{
	if (meetingNo == 0)
	{
		MessageBox(NULL, L"������������", L"��ʾ", MB_OK);
        return;
	}
	YSXSDK::StartParam param;
    CCheckBoxUI* chk = static_cast<CCheckBoxUI*>(m_pm.FindControl(L"chk_video"));
	param.isVideoOff = chk ? !chk->GetCheck() : true;			//�������ʱ�Ƿ����Ƶ
	param.meetingNumber = meetingNo;	//��ǰ�û�ԤԼ�Ļ������
	auto result = m_MeetingService->Start(param);
	if (result == SDKERR_TRIAL_USER_CAN_JOIN_TWICE_MEETING_EVERY_DAY)
	{
		MessageBox(NULL, L"ÿ��ֻ�ܼ����������", L"�����˺�", MB_OK);
	}
}

/// \brief ����һ����ʱ����
/// \param meetingTopic ��������
/// \param meetingParticipants ���������
void MainWnd::StartInstanceMeeting(const wstring& meetingTopic, const wstring& meetingParticipants)
{
    YSXSDK::InstanceMeettingParam param;
    CCheckBoxUI* chk = static_cast<CCheckBoxUI*>(m_pm.FindControl(L"chk_video"));
    param.isVideoOff = chk ? !chk->GetCheck() : true;			//�������ʱ�Ƿ����Ƶ
	param.isAudioOff = false;			//�������ʱ�Ƿ����Ƶ
	param.meetingTopic = meetingTopic.c_str();				//��������
	param.meetingParticipants = meetingParticipants.c_str();//���������,ͨѶ¼UserId,�����Ѷ��ŷָ�
	auto result = m_MeetingService->StartInstance(param);
	if (result == SDKERR_MEETING_TOPIC_EMPTY)
    {
        ::MessageBox(NULL, L"�������������", L"��ʾ", MB_OK);
	}
    else if (result == SDKERR_TRIAL_USER_CAN_JOIN_TWICE_MEETING_EVERY_DAY)
    {
        ::MessageBox(NULL, L"ÿ��ֻ�ܼ����������", L"�����˺�", MB_OK);
    }
}

/*
�������
����:IM����������,�����б��������������,����webinar����
*/
void MainWnd::JoinMeeting(const wstring& meetingId, UINT64 meetingNo, int meetingType)
{
	if (meetingNo == 0 && meetingType == 0)
	{
		MessageBox(NULL, L"������������", L"��ʾ", MB_OK);
	}

	YSXSDK::JoinParam param;
	param.userName = NULL;				//�����Զ�������
    param.psw = NULL;					//��������
    CCheckBoxUI* chk = static_cast<CCheckBoxUI*>(m_pm.FindControl(L"chk_video"));
    param.isVideoOff = chk ? !chk->GetCheck() : true;			//�������ʱ�Ƿ����Ƶ
	param.isAudioOff = false;			//����Ƶ
	param.meetingNumber = meetingNo;	//�������
	param.meetingId = meetingId.c_str();//����ID,�������Ǹ�������Ǳ�����д
	param.meetingType = meetingType;	//��������0:��ý��,1:����,REST API�ӿڷ��ػ�����Ϣ�а�����������,IM֪ͨҲ������������
	auto result = m_MeetingService->Join(param);
	if (result == SDKERR_TRIAL_USER_CAN_JOIN_TWICE_MEETING_EVERY_DAY)
	{
		::MessageBox(NULL, L"ÿ��ֻ�ܼ����������", L"�����˺�", MB_OK);
	}
}

void MainWnd::LockMeeting()
{
	auto result = m_MeetingService->LockMeeting();
	if (result == SDKError::SDKERR_SUCCESS)
	{
		ShowMsg(L"��������ɹ�");
	}
	else
	{
		ShowMsg(L"��������ʧ��");
	}
}

void MainWnd::UnLockMeeting()
{
	auto result = m_MeetingService->UnlockMeeting();
	if (result == SDKError::SDKERR_SUCCESS)
	{
		ShowMsg(L"ȡ����������ɹ�");
	}
	else
	{
		ShowMsg(L"ȡ����������ʧ��");
	}
}

void MainWnd::RefreshUserList()
{
	if (m_UserList)
	{
		m_UserList->RemoveAll();

		for (size_t i = 0; i < userList.size(); i++)
		{
			auto id = userList.at(i);
			CListTextElementUI* pListElement = new CListTextElementUI;
			pListElement->SetTag(id);
			m_UserList->Add(pListElement);
		}
	}
}

void MainWnd::ShowMsg(const std::wstring& msg)
{
	m_LabelMsg->SetText(msg.c_str());
}