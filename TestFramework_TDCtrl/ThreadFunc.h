#include "TestFramework_TDCtrl.h"
#include "TestFramework_TDCtrlDlg.h"

#pragma once
class ThreadFunc
{
public:
	ThreadFunc();
	~ThreadFunc();

public:
	CEvent			m_hMainEvent;
	BOOL			m_bStopMainThread;
	CWinThread*		m_pMainThread;
	HANDLE			m_hMainThread;
	LARGE_INTEGER	m_liST, m_liED, m_liFREQ;
	double			m_dGap;

public:
	void setElapseTime(double time) { m_dElapseTime = time; }
	void setElapseStepTime(double time) { m_dElapseStepTime = time; }
	void setStepTime(double delTime) { m_dStepTime = delTime; }
	double getStepTime() { return m_dStepTime; }

	static UINT	MainThreadFunc(LPVOID pParam);		// ������ ���� [6/11/2010 boxface]
	void process();
	void onThreadStart();
	void onThreadPause();
	void onThreadEnd();

	DWORD m_dNowtime;			// �ùķ��̼� ����ð��� ����� [8/14/2010 boxface]
	double m_dElapseTime;		// �ùķ��̼� ����ð� ���� ����
	double m_dElapseStepTime;	// �ùķ��̼� ����ð� ���� ����
	double m_dStepTime;			// �ùķ��̼� ����ð� ��������
};

