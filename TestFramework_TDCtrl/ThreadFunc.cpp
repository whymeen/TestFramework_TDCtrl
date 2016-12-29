#include "stdafx.h"
#include "ThreadFunc.h"


ThreadFunc::ThreadFunc()
{
}


ThreadFunc::~ThreadFunc()
{
}


UINT ThreadFunc::MainThreadFunc(LPVOID pParam)
{

	ThreadFunc* pThread = (ThreadFunc*)pParam;
	int FrameLimit;
	int index = 0;

	DWORD dOldtime = 0;
	double dDelTime = 0.0;

	while (!pThread->m_bStopMainThread)
	{
		// ����ð� üũ�� ����
		//////////////////////////////////////////////////////////////////////////
		dOldtime = pThread->m_dNowtime;
		pThread->m_dNowtime = GetTickCount();
		dDelTime = dDelTime + (double)(pThread->m_dNowtime - dOldtime)*1.0 / 1000.0;

		pThread->setElapseTime(dDelTime);

		pThread->m_dElapseStepTime += pThread->getStepTime();
		//////////////////////////////////////////////////////////////////////////

		FrameLimit = 33; // FRAME_30HZ

						 // ���μ��� one step�� ���۽ð� [6/11/2010 boxface]
		QueryPerformanceCounter(&pThread->m_liST);

		// ���μ��� ó�� [6/11/2010 boxface]
		//////////////////////////////////////////////////////////////////////////

		// ������ ó�� [6/14/2010 boxface]
		pThread->process();

		// ��ü���� ���� [6/14/2010 boxface]
		///pFrame->SendObjectUpdate();

		// �޽��� ���ۿ� �ִ� ���� ���� [7/6/2010 boxface]
		// Ÿ�̸ӷ� �̵� [7/8/2010 boxface]
		//if(index%30 == 0)
		//{
		//	pFrame->SendMsgBuf();
		//}

		//////////////////////////////////////////////////////////////////////////

		// ���μ��� one step�� ���۽ð� [6/11/2010 boxface]
		QueryPerformanceCounter(&pThread->m_liED);
		QueryPerformanceFrequency(&pThread->m_liFREQ);

		// ���μ��� ó���ϴ� �ҿ�� �ð� ��� [6/11/2010 boxface]
		pThread->m_dGap = ((double)(pThread->m_liED.QuadPart - pThread->m_liST.QuadPart)) / ((double)pThread->m_liFREQ.QuadPart);
		int interval = FrameLimit - (int)(pThread->m_dGap*1000.0);

		// Ȯ���� ó���ֱ⸸ŭ ���μ��� ��� [6/11/2010 boxface]
		if (interval > 0 && interval <= FrameLimit)
		{
			if (::WaitForSingleObject(pThread->m_hMainThread, interval) == WAIT_TIMEOUT)
			{
				//dhPrint("ó���ð��� ���.. !!\n");
			}
		}

		index++;
	}


	pThread->m_hMainThread = NULL;


	AfxEndThread(0, TRUE);

	return 0;
}

void ThreadFunc::onThreadStart()
{
	if (m_bStopMainThread == TRUE)
	{
		m_bStopMainThread = FALSE;
		m_pMainThread = AfxBeginThread(MainThreadFunc, (LPVOID)this);
		m_hMainThread = m_pMainThread->m_hThread;

		m_dNowtime = GetTickCount();
		setElapseTime(0.0);
	}
	else
	{
		m_pMainThread->ResumeThread();
		m_dNowtime = GetTickCount();
	}
}

void ThreadFunc::onThreadPause()
{
	m_pMainThread->SuspendThread();
	m_bStopMainThread = FALSE;
}


void ThreadFunc::onThreadEnd()
{
	if (!m_hMainThread)
		return;

	m_bStopMainThread = TRUE;

	DWORD dwExitCode = 0;
	::GetExitCodeThread(m_hMainThread, &dwExitCode);
	if (dwExitCode != 0)
	{
		if (::WaitForSingleObject(m_hMainThread, 500) == WAIT_TIMEOUT)
		{
			if (::TerminateThread(m_hMainThread, 0))
			{
				delete m_pMainThread;
				m_pMainThread = NULL;
				m_hMainThread = NULL;
			}
		}
	}
	else
	{
		m_pMainThread = NULL;
		m_hMainThread = NULL;
	}

}

void ThreadFunc::process()
{
	CTestFramework_TDCtrlDlg* pMain = (CTestFramework_TDCtrlDlg*)AfxGetMainWnd();
	int i, count = pMain->m_pObjectManager.GetSize();

	int iObjectID;
	int iObjectType;

	double x = 0.0;
	double y = 0.0;
	double z = 0.0;
	double h = 0.0;
	double p = 0.0;
	double r = 0.0;

	double dIncreaseHeading;
	double dIncreaseDepth;
	double dVelocity;

	for (i = 0; i<count; i++)
	{
		CObjectBase *pObject = pMain->m_pObjectManager.GetObjectPointerIdx(i);

		if (pObject->getObjectStatus() != OBJECT_STATUS_ENABLE)
		{
			continue;
		}

		iObjectID = pObject->getObjectID();
		iObjectType = pObject->getObjectType();

		x = pObject->getTranslateX();
		y = pObject->getTranslateY();
		z = pObject->getTranslateZ();

		h = pObject->getRotateH();
		p = pObject->getRotateP();
		r = pObject->getRotateR();

		dIncreaseHeading = pObject->getIncreaseH();
		dVelocity = pObject->getIncreaseVel();
		dIncreaseDepth = pObject->getIncreaseDepth();

		x = x + cos(h * 3.141592 / 180.0) * dVelocity;
		y = y + sin(h * 3.141592 / 180.0) * dVelocity;
		z = z + dIncreaseDepth;

		h = h + dIncreaseHeading;
		p = 0.0;
		r = 0.0;

		pMain->m_pObjectManager.updateObject(iObjectID, x, y, z, h, p, r);
	}
}