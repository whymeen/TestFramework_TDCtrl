// dhTCPLib.h : dhTCPLib DLL�� �⺻ ��� �����Դϴ�.
//

#pragma once

#ifndef __AFXWIN_H__
	#error "PCH�� ���� �� ������ �����ϱ� ���� 'stdafx.h'�� �����մϴ�."
#endif

#include "resource.h"		// �� ��ȣ�Դϴ�.


// CdhTCPLibApp
// �� Ŭ������ ������ ������ dhTCPLib.cpp�� �����Ͻʽÿ�.
//

class CdhTCPLibApp : public CWinApp
{
public:
	CdhTCPLibApp();

// �������Դϴ�.
public:
	virtual BOOL InitInstance();

	DECLARE_MESSAGE_MAP()
};
