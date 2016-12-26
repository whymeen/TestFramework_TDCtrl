// TubeAssignmentDlg.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "TestFramework_TDCtrl.h"
#include "TubeAssignmentDlg.h"
#include "afxdialogex.h"
#include "TestFramework_TDCtrlDlg.h"

// TubeAssignmentDlg 대화 상자입니다.

IMPLEMENT_DYNAMIC(TubeAssignmentDlg, CDialogEx)

TubeAssignmentDlg::TubeAssignmentDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_DIALOG_TUBE_ASSIGN, pParent)
{
	m_iCurObjectID = 0;
}

TubeAssignmentDlg::~TubeAssignmentDlg()
{
}

void TubeAssignmentDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO_TORPEDOIDLIST, m_cvCbxTorpedoIDList);
	DDX_Control(pDX, IDC_COMBO_TUBE_NUM, m_cvCbxTubeNum);
	DDX_Control(pDX, IDC_EDIT1, m_cvEditTargetID);
}


BEGIN_MESSAGE_MAP(TubeAssignmentDlg, CDialogEx)
	ON_BN_CLICKED(IDOK, &TubeAssignmentDlg::OnBnClickedOk)
END_MESSAGE_MAP()


// TubeAssignmentDlg 메시지 처리기입니다.


void TubeAssignmentDlg::OnBnClickedOk()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.

	// GUI에서 정보 획득 [8/21/2010 boxface]
	CString cstmp;
	int iObjectID;
	int iTubeNum;
	int iTargetID;

	// GUI에서 설정값 획득 [8/23/2010 boxface]
	m_cvCbxTorpedoIDList.GetLBText(m_cvCbxTorpedoIDList.GetCurSel(), cstmp);
	iObjectID = atoi(cstmp);
	m_cvCbxTubeNum.GetLBText(m_cvCbxTubeNum.GetCurSel(), cstmp);
	iTubeNum = atoi(cstmp);
	m_cvEditTargetID.GetWindowText(cstmp);
	iTargetID = atoi(cstmp);

	// tube 할당 정보를 네트워크로 전달 [6/15/2010 boxface]
	//////////////////////////////////////////////////////////////////////////
	_EVENT_TUBE_ASSIGNMENT_0x91 sendData;
	memset(&sendData, 0x00, sizeof(_EVENT_TUBE_ASSIGNMENT_0x91));

	sendData.type = MSG_CODE_EVENT_TUBE_ASSIGNMENT_0x91;
	sendData.length = sizeof(_EVENT_TUBE_ASSIGNMENT_0x91);

	sendData.objectID = iObjectID;
	sendData.tube_Number = iTubeNum;
	sendData.targetID = iTargetID;

	char sendBuf[NETWORK_MAXSIZE];
	memcpy(&sendBuf, (char*)&sendData, sizeof(_EVENT_TUBE_ASSIGNMENT_0x91));
	///SendEventData(sendBuf, sizeof(_EVENT_TUBE_ASSIGNMENT_0x91));
	//////////////////////////////////////////////////////////////////////////	
	
	CDialogEx::OnOK();
}


BOOL TubeAssignmentDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  여기에 추가 초기화 작업을 추가합니다.
	CString cstmp;


	// 어뢰 ID 목록 생성 [8/21/2010 boxface]
	//////////////////////////////////////////////////////////////////////////
	int i, count = ((CTestFramework_TDCtrlDlg *)GetParent())->m_pObjectManager.m_ObjectList.size();
	for (i = 0; i<count; i++)
	{
		// 플랫폼 ID에 포함된 어뢰정보 획득 [7/29/2010 boxface]
		if (((CTestFramework_TDCtrlDlg *)GetParent())->m_pObjectManager.m_ObjectList[i].getObjectID() != m_iCurObjectID)
		{
			continue;
		}

		// 탑제된 어뢰정보를 리스트에 추가 [8/3/2010 boxface]
		int j, count0 = ((CTestFramework_TDCtrlDlg *)GetParent())->m_pObjectManager.m_ObjectList[i].m_vTorpedoList.size();
		for (j = 0; j<count0; j++)
		{
			if (((CTestFramework_TDCtrlDlg *)GetParent())->m_pObjectManager.m_ObjectList[i].m_vTorpedoList[j].bFired == true)
			{
				continue;
			}

			cstmp.Format("%d", ((CTestFramework_TDCtrlDlg *)GetParent())->m_pObjectManager.m_ObjectList[i].m_vTorpedoList[j].iObjectID);
			m_cvCbxTorpedoIDList.AddString(cstmp);
		}
		m_cvCbxTorpedoIDList.SetCurSel(0);
	}


	// TUBE 넘버 목록 생성 [8/21/2010 boxface]
	for (int i = 0; i<8; i++)
	{
		cstmp.Format("%d", i + 1);
		m_cvCbxTubeNum.AddString(cstmp);
	}
	m_cvCbxTubeNum.SetCurSel(0);


	return TRUE;  // return TRUE unless you set the focus to a control
				  // 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}