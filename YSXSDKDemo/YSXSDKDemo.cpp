// ZhumuSDKDemo.cpp : ����Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include "YSXSDKDemo.h"
#include "MainWnd.h"

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPWSTR    lpCmdLine,
	_In_ int       nCmdShow)
{


	::CoInitialize(NULL);

	CPaintManagerUI::SetInstance(hInstance);
	CPaintManagerUI::SetCurrentPath(CPaintManagerUI::GetInstancePath());
	CPaintManagerUI::SetResourcePath(L"Skin");

	MainWnd wnd;
	wnd.Create(NULL, _T("����Ѷ"), UI_WNDSTYLE_DIALOG, WS_EX_WINDOWEDGE);
	wnd.ShowModal();

	::CoUninitialize();
	return 0;
}



