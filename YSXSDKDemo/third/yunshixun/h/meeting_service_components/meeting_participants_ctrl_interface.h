#ifndef _YSX_MEETING_ParticipantsCtrl_INTERFACE_H_
#define _YSX_MEETING_ParticipantsCtrl_INTERFACE_H_
#include "..\ysx_sdk_def.h"
#include "meeting_audio_interface.h"

BEGIN_YSX_SDK_NAMESPACE

/// \��������Ϣ�仯�ص��ӿ�
///
class IMeetingParticipantsCtrlEvent
{
public:
	/// \�������˽������ص�
	virtual void onUserJoin(unsigned int userID) = 0;

	/// \���������뿪����ص�
	virtual void onUserLeft(unsigned int userID) = 0;

	/// \�������˱���ص�
	virtual void onHostChangeNotification(unsigned int userId) = 0;

	/// \���ַ���״̬�ص�
	virtual void onLowOrRaiseHandStatusChanged(bool bLow, unsigned int userid) = 0;

	/// \�����������Ƹı�ص�
	virtual void onUserNameChanged(unsigned int userId, const wchar_t* userName) = 0;
};

/// \��������˿�����
///
class IMeetingParticipantsController
{
public:
	/// \�����¼��ص�����
	virtual SDKError SetEvent(IMeetingParticipantsCtrlEvent* pEvent) = 0;

	/// \��ȡ������Id�б�
	virtual std::vector<unsigned int > GetParticipantsList() = 0;

	/// \��ȡָ��id�û���Ϣ
	virtual IUserInfo* GetUserByUserID(unsigned int userid) = 0;

	/// \���з��������˵���
	virtual SDKError LowerAllHands() = 0;

	/// \�����˸���ָ���λ�������
	virtual SDKError ChangeUserName(const unsigned int userid, const wchar_t* userName, bool bSaveUserName) = 0;
};
END_YSX_SDK_NAMESPACE
#endif