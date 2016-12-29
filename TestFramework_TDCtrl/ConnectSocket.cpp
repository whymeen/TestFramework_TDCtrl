// ConnectSocket.cpp : implementation file
//

#include "stdafx.h"
#include "TestFramework_TDCtrl.h"
#include "ConnectSocket.h"
#include "TestFramework_TDCtrlDlg.h"

// CConnectSocket

CConnectSocket::CConnectSocket()
{
}

CConnectSocket::~CConnectSocket()
{
}


// CConnectSocket member functions

void CConnectSocket::OnClose(int nErrorCode)
{
	ShutDown();
	Close();

	CSocket::OnClose(nErrorCode);

	AfxMessageBox(_T("ERROR: Disconnected from server!"));
	::PostQuitMessage(0);
}

void CConnectSocket::OnReceive(int nErrorCode)
{
	TCHAR szBuffer[1024];
	::ZeroMemory(szBuffer, sizeof(szBuffer));

	if(Receive(szBuffer, sizeof(szBuffer)) > 0)
	{
		CTestFramework_TDCtrlDlg* pMain = (CTestFramework_TDCtrlDlg*)AfxGetMainWnd();
		//pMain->m_List.AddString(szBuffer);
		//pMain->m_List.SetCurSel(pMain->m_List.GetCount() -1);
	}

	CSocket::OnReceive(nErrorCode);
}
