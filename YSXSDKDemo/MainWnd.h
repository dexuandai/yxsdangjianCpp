#pragma once

class MainWnd :
	public WindowImplBase,
	public IAuthServiceEvent,
	public IMeetingServiceEvent,
	public IMeetingParticipantsCtrlEvent,
    public IMeetingShareCtrlEvent,
#ifdef INCLUDE_IM
    public IMessageEvent,
#endif // INCLUDE_IM

	public IListCallbackUI
{
public:
	MainWnd();
	~MainWnd();

	LPCTSTR		GetWindowClassName() const override;
	CDuiString	GetSkinFile() override;
	void		InitWindow();

    void Notify(TNotifyUI& msg) override;

	void		OnClick(TNotifyUI& msg);
	LRESULT HandleCustomMessage(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	LRESULT OnClose(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& bHandled);


#pragma region IAuthServiceEvent
	void onAuthenticationReturn(AuthResult ret);
	void onLoginRet(LOGINSTATUS ret);
	void onLogout();
	void onConnect();
	void onDisconnect(const MsgErrorCode code);
#pragma endregion

#pragma region IMeetingServiceEvent
	void onMeetingStatusChanged(MeetingStatus status, int iResult = 0);
	void onMeetingStatisticsWarningNotification(StatisticsWarningType type);
	void onStartLeaveMeetingCountdown(int minutes = 0);	
#pragma endregion

#pragma region IMessageEvent
    void onReceiveMessages(const std::string& jsonMsg);
    void onReceiveCmdMessages(const std::string& jsonMsg);
#pragma endregion

#pragma region IMeetingParticipantsCtrlEvent
	void onUserJoin(unsigned int userId);
	void onUserLeft(unsigned int userId);
	void onHostChangeNotification(unsigned int userId);
	void onLowOrRaiseHandStatusChanged(bool bLow, unsigned int userid);
	void onUserNameChanged(unsigned int userId, const wchar_t* userName);
#pragma endregion

    virtual void onSharingStatus(SharingStatus status, unsigned int userId);

    virtual void onLockShareStatus(bool bLocked);

    virtual void onShareContentNotification(ShareInfo& shareInfo);

	LPCTSTR GetItemText(CControlUI* pList, int iItem, int iSubItem);

private:
	void Login();
	void Logout();
	void StartMeeting(UINT64 meetingNo = 0);
	void StartInstanceMeeting(const wstring& meetingTopic, const wstring& meetingParticipants);
	void JoinMeeting(const wstring& meetingId, UINT64 meetingNo = 0, int meetingType=0);
	void LockMeeting();
	void UnLockMeeting();

	void RefreshUserList();

	void SDKInit();
	void InitMeetingService();
	void ShowMsg(const std::wstring& msg);

private:

	CEditUI* m_EditUserName;
	CEditUI* m_EditPassword;
	CEditUI* m_EditMeetingId;
	CEditUI* m_EditMeetingNo;
	CEditUI* m_EditMeetingTopic;
	CEditUI* m_EditUser;
	CEditUI* m_EditToken;

	CEditUI* m_AppKey;
	CEditUI* m_AppSecret;

	CEditUI* m_ApiKey;
	CEditUI* m_ApiSecret;

	CLabelUI* m_LabelMsg;
	CLabelUI* m_LabelUName;
	CHorizontalLayoutUI* m_LayoutKeyInfo;
	CHorizontalLayoutUI* m_LayoutLogin;
	CHorizontalLayoutUI* m_LayoutMeeting;
	CHorizontalLayoutUI* m_LayoutMeetingControl;
	CListUI* m_UserList;

	std::vector<unsigned int> userList;

	wchar_t* appKey;///< APP Key string
	wchar_t* appSecret;///< APP Secret string
	wchar_t* apiKey;///< API Key string
	wchar_t* apiSecret;///< API Secret string

	YSXSDK::IAuthService* m_AuthService;
	YSXSDK::IMeetingService* m_MeetingService;
	YSXSDK::IMeetingParticipantsController* m_MeetingParticipantsController;
#ifdef INCLUDE_IM
    YSXSDK::IMMessageService* m_MessageService;
#endif // INCLUDE_IM

};

