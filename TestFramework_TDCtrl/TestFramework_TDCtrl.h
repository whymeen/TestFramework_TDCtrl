
// TestFramework_TDCtrl.h : PROJECT_NAME ���� ���α׷��� ���� �� ��� �����Դϴ�.
//

#pragma once

#ifndef __AFXWIN_H__
	#error "PCH�� ���� �� ������ �����ϱ� ���� 'stdafx.h'�� �����մϴ�."
#endif

#include "resource.h"		// �� ��ȣ�Դϴ�.


// CTestFramework_TDCtrlApp:
// �� Ŭ������ ������ ���ؼ��� TestFramework_TDCtrl.cpp�� �����Ͻʽÿ�.
//

class CTestFramework_TDCtrlApp : public CWinApp
{
public:
	CTestFramework_TDCtrlApp();

// �������Դϴ�.
public:
	virtual BOOL InitInstance();

// �����Դϴ�.

	DECLARE_MESSAGE_MAP()
};

extern CTestFramework_TDCtrlApp theApp;