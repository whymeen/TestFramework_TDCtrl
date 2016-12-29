
// TestFramework_TDCtrlDlg.cpp : ���� ����
//

#include "stdafx.h"
#include "TestFramework_TDCtrl.h"
#include "TestFramework_TDCtrlDlg.h"
#include "afxdialogex.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// ���� ���α׷� ������ ���Ǵ� CAboutDlg ��ȭ �����Դϴ�.

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// ��ȭ ���� �������Դϴ�.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

// �����Դϴ�.
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CTestFramework_TDCtrlDlg ��ȭ ����



CTestFramework_TDCtrlDlg::CTestFramework_TDCtrlDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_TESTFRAMEWORK_TDCTRL_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CTestFramework_TDCtrlDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO_OBJECTID, m_cvCbxObjectID);
	DDX_Control(pDX, IDC_COMBO_TORPEDOID, m_cvCbxTorpedoIDList);
	DDX_Control(pDX, IDC_COMBO_DECOYID, m_cvCbxDecoyList);
	DDX_Control(pDX, IDC_COMBO_OPERATIONMODE, m_cvCbxOperationMode);
	DDX_Control(pDX, IDC_COMBO_SENDINGMODE, m_cvCbxSendingMode);
	DDX_Control(pDX, IDC_EDIT_FREQUENCE, m_cvEditFrequence);
	DDX_Control(pDX, IDC_EDIT_SOUNDPRESSURE, m_cvEditSoundPressure);
	DDX_Control(pDX, IDC_EDIT_BEAMWIDTH, m_cvEditBeamWidth);
	DDX_Control(pDX, IDC_EDIT_DECOY_DOPPLER, m_cvEditDecoyDoppler);
	DDX_Control(pDX, IDC_EDIT_THROWING_DISTANCE, m_cvEditThrowingDistance);
	DDX_Control(pDX, IDC_EDIT_THROWING_DIRECTION, m_cvEditThrowingDirection);
	DDX_Control(pDX, IDC_EDIT_WORKINGTIME, m_cvEditWorkingTime);
	DDX_Control(pDX, IDC_EDIT_DELAYTIME, m_cvEditDelayTime);
	DDX_Control(pDX, IDC_COMBO_TORPEDOSTATE, m_cvCbxTorpedoState);
	DDX_Control(pDX, IDC_COMBO_TORPEDO_GUIDMODE, m_cvCbxGuidMode);
	DDX_Control(pDX, IDC_COMBO_TORPEDO_GUIDMETHOD, m_cvCbxGuidMethod);
	DDX_Control(pDX, IDC_COMBO_TORPEDO_SPEEDSTEP, m_cvCbxSpeedStep);
	DDX_Control(pDX, IDC_COMBO_TARGET_MODE, m_cvCbxTargetMode);
	DDX_Control(pDX, IDC_COMBO_TARGET_DETECT, m_cvCbxTargetDetectStatus);
	DDX_Control(pDX, IDC_COMBO_TOSO_MODE, m_cvCbxTOSOMode);
	DDX_Control(pDX, IDC_COMBO_TRANS_CTRL_MODE, m_cvCbxTransCtrlMode);
	DDX_Control(pDX, IDC_COMBO_TRANS_PURS_MODE, m_cvCbxTransPursMode);
	DDX_Control(pDX, IDC_COMBO_TARGET_SUPPORT, m_cvCbxTargetSupport);
	DDX_Control(pDX, IDC_EDIT_COURSE, m_cvEditCourse);
	DDX_Control(pDX, IDC_EDIT_PRO_COURSE, m_cvEditProCourse);
	DDX_Control(pDX, IDC_EDIT_H_DEPTH, m_cvEditHDepth);
	DDX_Control(pDX, IDC_EDIT_M_DEPTH, m_cvEditMDepth);
	DDX_Control(pDX, IDC_EDIT_L_DEPTH, m_cvEditLDepth);
	DDX_Control(pDX, IDC_SLIDER_HORIZENTAL, m_cvSldHeading);
	DDX_Control(pDX, IDC_SLIDER_DEPTH, m_cvSldDepth);
	DDX_Control(pDX, IDC_SLIDER_VERTICAL, m_cvSldVelocity);
}

BEGIN_MESSAGE_MAP(CTestFramework_TDCtrlDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_CBN_SELENDCANCEL(IDC_COMBO_OBJECTID, &CTestFramework_TDCtrlDlg::OnCbnSelendcancelComboObjectid)
	ON_BN_CLICKED(IDC_BUTTON_FIRE, &CTestFramework_TDCtrlDlg::OnBnClickedButtonFire)
	ON_BN_CLICKED(IDC_BUTTON_DECOY_FIRE, &CTestFramework_TDCtrlDlg::OnBnClickedButtonDecoyFire)
	ON_BN_CLICKED(IDC_BUTTON_TORPEDO_PRESET, &CTestFramework_TDCtrlDlg::OnBnClickedButtonTorpedoPreset)
	ON_BN_CLICKED(IDC_BUTTON_DECOY_PRESET, &CTestFramework_TDCtrlDlg::OnBnClickedButtonDecoyPreset)
	ON_BN_CLICKED(IDC_BUTTON_TUBE_ASSIGNMENT, &CTestFramework_TDCtrlDlg::OnBnClickedButtonTubeAssignment)
	ON_BN_CLICKED(IDC_BUTTON_TUBE_STATUS, &CTestFramework_TDCtrlDlg::OnBnClickedButtonTubeStatus)
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_SLIDER_HORIZENTAL, &CTestFramework_TDCtrlDlg::OnNMCustomdrawSliderHorizental)
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_SLIDER_DEPTH, &CTestFramework_TDCtrlDlg::OnNMCustomdrawSliderDepth)
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_SLIDER_VERTICAL, &CTestFramework_TDCtrlDlg::OnNMCustomdrawSliderVertical)
	ON_BN_CLICKED(IDC_BUTTON_RESET_H, &CTestFramework_TDCtrlDlg::OnBnClickedButtonResetH)
	ON_BN_CLICKED(IDC_BUTTON_RESET_DEPTH, &CTestFramework_TDCtrlDlg::OnBnClickedButtonResetDepth)
	ON_BN_CLICKED(IDC_BUTTON_RESET_V, &CTestFramework_TDCtrlDlg::OnBnClickedButtonResetV)
	ON_BN_CLICKED(IDC_BUTTON_RESET_ALL, &CTestFramework_TDCtrlDlg::OnBnClickedButtonResetAll)
	END_MESSAGE_MAP()


// CTestFramework_TDCtrlDlg �޽��� ó����

BOOL CTestFramework_TDCtrlDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// �ý��� �޴��� "����..." �޴� �׸��� �߰��մϴ�.

	// IDM_ABOUTBOX�� �ý��� ��� ������ �־�� �մϴ�.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// �� ��ȭ ������ �������� �����մϴ�.  ���� ���α׷��� �� â�� ��ȭ ���ڰ� �ƴ� ��쿡��
	//  �����ӿ�ũ�� �� �۾��� �ڵ����� �����մϴ�.
	SetIcon(m_hIcon, TRUE);			// ū �������� �����մϴ�.
	SetIcon(m_hIcon, FALSE);		// ���� �������� �����մϴ�.

	//���Ͽ���
	
	m_Socket.Create();
	if (m_Socket.Connect(_T("127.0.0.1"), 21000) == FALSE)
	{
		AfxMessageBox(_T("ERROR: Failed to connect server"));
		PostQuitMessage(0);

		return FALSE;
	}

	// �ʱ� �� ����

	m_iCurObjectID = 0;

	m_cvCbxTorpedoState.InsertString(0, "off");
	m_cvCbxTorpedoState.InsertString(1, "auto off");
	m_cvCbxTorpedoState.InsertString(2, "Checking");
	m_cvCbxTorpedoState.InsertString(3, "Power on Check");
	m_cvCbxTorpedoState.InsertString(4, "On");
	m_cvCbxTorpedoState.InsertString(5, "Extended Check");
	m_cvCbxTorpedoState.InsertString(6, "Ready to Launch");
	m_cvCbxTorpedoState.InsertString(7, "Fire");
	m_cvCbxTorpedoState.InsertString(8, "Aborted");
	m_cvCbxTorpedoState.InsertString(9, "Post Launch");
	m_cvCbxTorpedoState.SetCurSel(0);


	m_cvCbxGuidMode.InsertString(0, "Computer Guidance");
	m_cvCbxGuidMode.InsertString(1, "Internal Guidance");
	m_cvCbxGuidMode.InsertString(2, "Manual Guidance");
	m_cvCbxGuidMode.SetCurSel(0);


	m_cvCbxGuidMethod.InsertString(0, "CCM");
	m_cvCbxGuidMethod.InsertString(1, "CCM-A");
	m_cvCbxGuidMethod.InsertString(2, "BRM");
	m_cvCbxGuidMethod.InsertString(3, "BRM-C");
	m_cvCbxGuidMethod.SetCurSel(0);


	m_cvCbxSpeedStep.InsertString(0, "off");
	m_cvCbxSpeedStep.InsertString(1, "S1");
	m_cvCbxSpeedStep.InsertString(2, "S2");
	m_cvCbxSpeedStep.InsertString(3, "S3");
	m_cvCbxSpeedStep.SetCurSel(0);


	m_cvCbxTargetMode.InsertString(0, "������(Srf)");
	m_cvCbxTargetMode.InsertString(1, "ǥ����(Sub)");
	m_cvCbxTargetMode.SetCurSel(0);


	m_cvCbxTargetDetectStatus.InsertString(0, "-");
	m_cvCbxTargetDetectStatus.InsertString(1, "Target Contact 1");
	m_cvCbxTargetDetectStatus.InsertString(2, "Target Contact 2");
	m_cvCbxTargetDetectStatus.InsertString(3, "Target Detected");
	m_cvCbxTargetDetectStatus.InsertString(4, "Turn Around");
	m_cvCbxTargetDetectStatus.SetCurSel(0);


	m_cvCbxTOSOMode.InsertString(0, "Passive");
	m_cvCbxTOSOMode.InsertString(1, "Active");
	m_cvCbxTOSOMode.SetCurSel(0);

	m_cvCbxTransCtrlMode.InsertString(0, "Internal");
	m_cvCbxTransCtrlMode.InsertString(1, "Auto");
	m_cvCbxTransCtrlMode.InsertString(2, "Auto Dir");
	m_cvCbxTransCtrlMode.InsertString(3, "Ahead");
	m_cvCbxTransCtrlMode.InsertString(4, "Manual");
	m_cvCbxTransCtrlMode.SetCurSel(0);


	m_cvCbxTransPursMode.InsertString(0, "Follow up");
	m_cvCbxTransPursMode.InsertString(1, "Earth fixed");
	m_cvCbxTransPursMode.SetCurSel(0);


	m_cvCbxTargetSupport.InsertString(0, "�ý���ǥ���� ����");
	m_cvCbxTargetSupport.InsertString(1, "�ý���ǥ���� ��������");
	m_cvCbxTargetSupport.InsertString(2, "���ο� �ý���ǥ�� �߰�");
	m_cvCbxTargetSupport.SetCurSel(0);

	m_cvCbxOperationMode.InsertString(0, "Jammer");
	m_cvCbxOperationMode.InsertString(1, "Decoy");
	m_cvCbxOperationMode.SetCurSel(0);


	m_cvCbxSendingMode.InsertString(0, "�ɵ�");
	m_cvCbxSendingMode.InsertString(1, "����");
	m_cvCbxSendingMode.InsertString(2, "ȥ��");
	m_cvCbxSendingMode.SetCurSel(0);


	m_cvSldHeading.SetRange(0, 100);
	m_cvSldVelocity.SetRange(0, 100);
	m_cvSldDepth.SetRange(0, 100);

	m_cvSldHeading.SetPos(50);
	m_cvSldVelocity.SetPos(50);
	m_cvSldDepth.SetPos(50);

	return TRUE;  // ��Ŀ���� ��Ʈ�ѿ� �������� ������ TRUE�� ��ȯ�մϴ�.
}

void CTestFramework_TDCtrlDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// ��ȭ ���ڿ� �ּ�ȭ ���߸� �߰��� ��� �������� �׸�����
//  �Ʒ� �ڵ尡 �ʿ��մϴ�.  ����/�� ���� ����ϴ� MFC ���� ���α׷��� ��쿡��
//  �����ӿ�ũ���� �� �۾��� �ڵ����� �����մϴ�.

void CTestFramework_TDCtrlDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // �׸��⸦ ���� ����̽� ���ؽ�Ʈ�Դϴ�.

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Ŭ���̾�Ʈ �簢������ �������� ����� ����ϴ�.
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// �������� �׸��ϴ�.
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// ����ڰ� �ּ�ȭ�� â�� ���� ���ȿ� Ŀ���� ǥ�õǵ��� �ý��ۿ���
//  �� �Լ��� ȣ���մϴ�.
HCURSOR CTestFramework_TDCtrlDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CTestFramework_TDCtrlDlg::OnCbnSelendcancelComboObjectid()
{
	// �ʱ�ȭ [7/29/2010 boxface]
	m_cvCbxTorpedoIDList.ResetContent();
	m_cvCbxDecoyList.ResetContent();

	// �÷��� ID ���� [7/29/2010 boxface]
	CString cstmp;
	m_cvCbxObjectID.GetLBText(m_cvCbxObjectID.GetCurSel(), cstmp);
	m_iCurObjectID = atoi(cstmp);


	int i, count = m_pObjectManager.m_ObjectList.size();
	for (i = 0; i<count; i++)
	{
		// �÷��� ID�� ���Ե� ������� ȹ�� [7/29/2010 boxface]
		if (m_pObjectManager.m_ObjectList[i].getObjectID() != m_iCurObjectID)
		{
			continue;
		}

		// ž���� ��������� ����Ʈ�� �߰� [8/3/2010 boxface]
		int j, count0 = m_pObjectManager.m_ObjectList[i].m_vTorpedoList.size();
		for (j = 0; j<count0; j++)
		{
			if (m_pObjectManager.m_ObjectList[i].m_vTorpedoList[j].bFired == true)
			{
				continue;
			}

			cstmp.Format("%d", m_pObjectManager.m_ObjectList[i].m_vTorpedoList[j].iObjectID);
			m_cvCbxTorpedoIDList.AddString(cstmp);
		}
		m_cvCbxTorpedoIDList.SetCurSel(0);

		// ž���� �⸸�� ������ ����Ʈ�� �߰� [8/3/2010 boxface]
		int count1 = m_pObjectManager.m_ObjectList[i].m_vDecoyList.size();
		for (j = 0; j<count1; j++)
		{
			if (m_pObjectManager.m_ObjectList[i].m_vDecoyList[j].bFired == true)
			{
				continue;
			}

			cstmp.Format("%d", m_pObjectManager.m_ObjectList[i].m_vDecoyList[j].iObjectID);
			m_cvCbxDecoyList.AddString(cstmp);
		}
		m_cvCbxDecoyList.SetCurSel(0);

		if (m_pObjectManager.m_ObjectList[i].getObjectType() == OBJECT_TYPE_TORPEDO ||
			m_pObjectManager.m_ObjectList[i].getObjectType() == OBJECT_TYPE_DECOY)
		{
			m_cvCbxTorpedoIDList.EnableWindow(false);
			m_cvCbxDecoyList.EnableWindow(false);
		}
		else
		{
			m_cvCbxTorpedoIDList.EnableWindow(true);
			m_cvCbxDecoyList.EnableWindow(true);
		}
	}
}


void CTestFramework_TDCtrlDlg::OnBnClickedButtonFire()
{

	int iIFF;
	int curTorpedoObjectID;
	int curOwnshipObjectID;
	int curTorpedoImageType = 0;
	CString cstmp;
	m_cvCbxObjectID.GetLBText(m_cvCbxObjectID.GetCurSel(), cstmp);
	curOwnshipObjectID = atoi(cstmp);

	m_cvCbxTorpedoIDList.GetLBText(m_cvCbxTorpedoIDList.GetCurSel(), cstmp);
	curTorpedoObjectID = atoi(cstmp);

	// �߻������� ���� ��ü ���� [7/29/2010 boxface]
	//////////////////////////////////////////////////////////////////////////
	int i, count = m_pObjectManager.GetSize();

	// torpedo�� �ʱ���ġ�� ���� [7/26/2010 boxface]
	//////////////////////////////////////////////////////////////////////////
	double x, y, z, h, p, r;
	int objectType = OBJECT_TYPE_TORPEDO;

	x = 0.0;
	y = 0.0;
	z = 0.0;
	h = 0.0;
	p = 0.0;
	r = 0.0;

	//1.  �߻����� ��ġ�� ���� [7/26/2010 boxface]
	for (i = 0; i<count; i++)
	{
		if (curOwnshipObjectID == m_pObjectManager.m_ObjectList[i].getObjectID())
		{
			m_pObjectManager.m_ObjectList[i].getTranslate(x, y, z);
			m_pObjectManager.m_ObjectList[i].getRotate(h, p, r);
			iIFF = m_pObjectManager.m_ObjectList[i].getIFF();

			// �߻��� ����� �߻���°� ���� [7/29/2010 boxface]
			int j, count0 = m_pObjectManager.m_ObjectList[i].m_vTorpedoList.size();
			for (j = 0; j<count0; j++)
			{
				if (m_pObjectManager.m_ObjectList[i].m_vTorpedoList[j].iObjectID != curTorpedoObjectID)
				{
					continue;
				}

				m_pObjectManager.m_ObjectList[i].m_vTorpedoList[j].bFired = true;
				objectType = m_pObjectManager.m_ObjectList[i].m_vTorpedoList[j].iObjectType;
				curTorpedoImageType = m_pObjectManager.m_ObjectList[i].m_vTorpedoList[j].iImageType;

			}
		}
	}

	x = x;
	y = y;

	//2. ����� ��ġ�� ����
	//////////////////////////////////////////////////////////////////////////
	// ���� �޸𸮿� torpedo ����  [7/26/2010 boxface]
	CObjectBase pTorpedo;

	pTorpedo.setObjectID(curTorpedoObjectID);
	pTorpedo.setObjectType(objectType);
	pTorpedo.setObjectStatus(OBJECT_STATUS_ENABLE);
	pTorpedo.setIFF(iIFF);
	pTorpedo.setObjectImageType(curTorpedoImageType);
	pTorpedo.setParentID(curOwnshipObjectID);

	pTorpedo.setTranslate(x, y, z);
	pTorpedo.setRotate(h, p, r);

	m_pObjectManager.m_ObjectList.push_back(pTorpedo);

	// GUI�� ������Ʈ [7/29/2010 boxface]
	cstmp.Format("%d", curTorpedoObjectID);
	m_cvCbxTorpedoIDList.DeleteString(m_cvCbxTorpedoIDList.GetCurSel());

	// �ٸ� Dlg�� ID ���� ������Ʈ [6/15/2010 boxface]
	//m_pBaseView->addObject(curTorpedoObjectID);

	// ��ڻ��������� ��Ʈ��ũ�� ���� [6/15/2010 boxface]
	//////////////////////////////////////////////////////////////////////////
	EVENT_OBJECT_CONTROL sendData;
	memset(&sendData, 0x00, sizeof(EVENT_OBJECT_CONTROL));

	sendData.type = MSG_CODE_EVENT_OBJECT_CONTROL_0x13;
	sendData.length = sizeof(EVENT_OBJECT_CONTROL);

	sendData.mode = OBJECT_CTRL_CREATE;
	sendData.objectID = curTorpedoObjectID;
	sendData.objectType = objectType;
	sendData.status = OBJECT_STATUS_ENABLE;
	sendData.IFF = iIFF;
	sendData.imageType = curTorpedoImageType;

	//sendData.x = x;
	//sendData.y = y;
	//sendData.z = z;
	//sendData.h = (Sflt32)h;
	//sendData.p = (Sflt32)p;
	//sendData.r = (Sflt32)r;

	sendData.speed = 20;
	sendData.course = h;
	sendData.latitude = x;
	sendData.longitude = y;
	sendData.depth = -z;


	char sendBuf[NETWORK_MAXSIZE];
	memcpy(&sendBuf, (char*)&sendData, sizeof(EVENT_OBJECT_CONTROL));
	//SendEventData(sendBuf, sizeof(EVENT_OBJECT_CONTROL));
	//////////////////////////////////////////////////////////////////////////		

	Sleep(1000);

}


void CTestFramework_TDCtrlDlg::OnBnClickedButtonDecoyFire()
{

	int curDecoyObjectID;
	int curOwnshipObjectID;
	int curDecoyImageType = 0;
	CString cstmp;
	m_cvCbxObjectID.GetLBText(m_cvCbxObjectID.GetCurSel(), cstmp);
	curOwnshipObjectID = atoi(cstmp);

	m_cvCbxDecoyList.GetLBText(m_cvCbxDecoyList.GetCurSel(), cstmp);
	curDecoyObjectID = atoi(cstmp);

	// �߻������� ���� ��ü ���� [7/29/2010 boxface]
	//////////////////////////////////////////////////////////////////////////
	int i, count = m_pObjectManager.GetSize();

	// torpedo�� �ʱ���ġ�� ���� [7/26/2010 boxface]
	//////////////////////////////////////////////////////////////////////////
	double x, y, z, h, p, r;
	int objectType = OBJECT_TYPE_DECOY;

	x = 0.0;
	y = 0.0;
	z = 0.0;
	h = 0.0;
	p = 0.0;
	r = 0.0;

	//1.  �߻����� ��ġ�� ���� [7/26/2010 boxface]
	for (i = 0; i<count; i++)
	{
		if (curOwnshipObjectID == m_pObjectManager.m_ObjectList[i].getObjectID())
		{
			m_pObjectManager.m_ObjectList[i].getTranslate(x, y, z);
			m_pObjectManager.m_ObjectList[i].getRotate(h, p, r);

			// �߻��� ����� �߻���°� ���� [7/29/2010 boxface]
			int j, count0 = m_pObjectManager.m_ObjectList[i].m_vDecoyList.size();
			for (j = 0; j<count0; j++)
			{
				if (m_pObjectManager.m_ObjectList[i].m_vDecoyList[j].iObjectID != curDecoyObjectID)
				{
					continue;
				}

				m_pObjectManager.m_ObjectList[i].m_vDecoyList[j].bFired = true;
				objectType = m_pObjectManager.m_ObjectList[i].m_vDecoyList[j].iObjectType;
				curDecoyImageType = m_pObjectManager.m_ObjectList[i].m_vDecoyList[j].iImageType;
			}
		}
	}

	x = x;
	y = y;

	//2. �⸸���� ��ġ�� ����
	//////////////////////////////////////////////////////////////////////////
	// ���� �޸𸮿� decoy ����  [7/26/2010 boxface]
	CObjectBase pDecoy;

	pDecoy.setObjectID(curDecoyObjectID);
	pDecoy.setObjectType(objectType);
	pDecoy.setObjectStatus(OBJECT_STATUS_ENABLE);
	pDecoy.setIFF(IFF_FRIEND);
	pDecoy.setObjectImageType(curDecoyImageType);
	pDecoy.setParentID(curOwnshipObjectID);

	pDecoy.setTranslate(x, y, z);
	pDecoy.setRotate(h, p, r);

	m_pObjectManager.m_ObjectList.push_back(pDecoy);

	// GUI�� ������Ʈ [7/29/2010 boxface]
	cstmp.Format("%d", curDecoyObjectID);
	m_cvCbxDecoyList.DeleteString(m_cvCbxDecoyList.GetCurSel());

	// �ٸ� Dlg�� ID ���� ������Ʈ [6/15/2010 boxface]
	//m_pBaseView->addObject(curDecoyObjectID);

	// Decoy ���������� ��Ʈ��ũ�� ���� [6/15/2010 boxface]
	//////////////////////////////////////////////////////////////////////////
	EVENT_OBJECT_CONTROL sendData;
	memset(&sendData, 0x00, sizeof(EVENT_OBJECT_CONTROL));

	sendData.type = MSG_CODE_EVENT_OBJECT_CONTROL_0x13;
	sendData.length = sizeof(EVENT_OBJECT_CONTROL);

	sendData.mode = OBJECT_CTRL_CREATE;
	sendData.objectID = curDecoyObjectID;
	sendData.objectType = objectType;
	sendData.status = OBJECT_STATUS_ENABLE;
	sendData.IFF = IFF_FRIEND;
	sendData.imageType = curDecoyImageType;

	//sendData.x = x;
	//sendData.y = y;
	//sendData.z = z;
	//sendData.h = (Sflt32)h;
	//sendData.p = (Sflt32)p;
	//sendData.r = (Sflt32)r;

	sendData.speed = 20;
	sendData.course = h;
	sendData.latitude = x;
	sendData.longitude = y;
	sendData.depth = -z;

	char sendBuf[NETWORK_MAXSIZE];
	memcpy(&sendBuf, (char*)&sendData, sizeof(EVENT_OBJECT_CONTROL));
	//SendEventData(sendBuf, sizeof(EVENT_OBJECT_CONTROL));
	//////////////////////////////////////////////////////////////////////////		

	Sleep(1000);

	// �߻������� ��Ʈ��ũ�� ���� [6/15/2010 boxface]
	//////////////////////////////////////////////////////////////////////////
	EVENT_DECOY_FIRE sendData0;
	memset(&sendData0, 0x00, sizeof(EVENT_DECOY_FIRE));

	sendData0.type = MSG_CODE_EVENT_DECOY_FIRE_0x72;
	sendData0.length = sizeof(EVENT_DECOY_FIRE);

	sendData0.objectID = curDecoyObjectID;
	sendData0.firing_objectID = curOwnshipObjectID;
	sendData0.target_objectID = 0;

	char sendBuf0[NETWORK_MAXSIZE];
	memcpy(&sendBuf0, (char*)&sendData0, sizeof(EVENT_DECOY_FIRE));
	//SendEventData(sendBuf0, sizeof(EVENT_DECOY_FIRE));
	//////////////////////////////////////////////////////////////////////////
}


void CTestFramework_TDCtrlDlg::OnBnClickedButtonTorpedoPreset()
{
	

	CString cstmp;
	int iObjectID = 0;
	float fCourse = 0.0f;
	float fprogramCourse = 0.0f;
	float fhDepth = 0.0f;
	float fmDepth = 0.0f;
	float flDepth = 0.0f;


	// GUI���� ���� ȹ�� [8/13/2010 boxface]

	m_cvCbxTorpedoIDList.GetLBText(m_cvCbxTorpedoIDList.GetCurSel(), cstmp);
	iObjectID = atoi(cstmp);

	m_cvEditCourse.GetWindowText(cstmp);
	fCourse = (float)atof(cstmp);

	m_cvEditProCourse.GetWindowText(cstmp);
	fprogramCourse = (float)atof(cstmp);

	m_cvEditHDepth.GetWindowText(cstmp);
	fhDepth = (float)atof(cstmp);
	m_cvEditMDepth.GetWindowText(cstmp);
	fmDepth = (float)atof(cstmp);
	m_cvEditLDepth.GetWindowText(cstmp);
	flDepth = (float)atof(cstmp);

	// ��� preset ������ ��Ʈ��ũ�� ���� [6/15/2010 boxface]
	//////////////////////////////////////////////////////////////////////////
	EVENT_TORPEDO_PRESET sendData;
	memset(&sendData, 0x00, sizeof(EVENT_TORPEDO_PRESET));

	sendData.type = MSG_CODE_EVENT_TORPEDO_PRESET_0x51;
	sendData.length = sizeof(EVENT_TORPEDO_PRESET);
	sendData.objectID = iObjectID;

	sendData.torpedoState = m_cvCbxTorpedoState.GetCurSel();
	sendData.guidanceMode = m_cvCbxGuidMode.GetCurSel();
	sendData.guidanceMethod = m_cvCbxGuidMethod.GetCurSel();
	sendData.speedStep = m_cvCbxSpeedStep.GetCurSel();
	sendData.targetMode = m_cvCbxTargetMode.GetCurSel();
	sendData.targetDetectionState = m_cvCbxTargetDetectStatus.GetCurSel();
	sendData.TOSOMode = m_cvCbxTOSOMode.GetCurSel();
	sendData.tansducerControlMode = m_cvCbxTransCtrlMode.GetCurSel();
	sendData.tansducerPursuitMode = m_cvCbxTransPursMode.GetCurSel();
	sendData.targetSupport = m_cvCbxTargetSupport.GetCurSel();


	sendData.torpedo_course = fCourse;
	sendData.torpedo_program_course = fprogramCourse;
	sendData.hDepth = fhDepth;
	sendData.mDepth = fmDepth;
	sendData.lDepth = flDepth;

	char sendBuf[NETWORK_MAXSIZE];
	memcpy(&sendBuf, (char*)&sendData, sizeof(EVENT_TORPEDO_PRESET));
	//SendEventData(sendBuf, sizeof(EVENT_TORPEDO_PRESET));
	//////////////////////////////////////////////////////////////////////////	
}


void CTestFramework_TDCtrlDlg::OnBnClickedButtonDecoyPreset()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.

	CString cstmp;
	int iObjectID = 0;
	int iOperationMode = 0;
	int iSendingMode = 0;
	double dFrequence = 0.0;
	double dSoundPressure = 0.0;
	double dBeamWidth = 0.0;
	double dDecoyDoppler = 0.0;
	double dThrowingDistance = 0.0;
	double dThrowingDirection = 0.0;
	double dWorkingTime = 0.0;
	double dDelayTime = 0.0;
	double dSpeed1 = 0.0;
	double dSpeed2 = 0.0;
	double dSpeed3 = 0.0;
//	double H1, P1, R1;
//	double H2, P2, R2;
//	double H3, P3, R3;
	double dDepth1 = 0.0;
	double dDepth2 = 0.0;
	double dDepth3 = 0.0;

	// GUI���� ���� ȹ�� [8/13/2010 boxface]
	iOperationMode = m_cvCbxOperationMode.GetCurSel();
	iSendingMode = m_cvCbxSendingMode.GetCurSel();
	m_cvEditFrequence.GetWindowText(cstmp);
	dFrequence = atof(cstmp);
	m_cvEditSoundPressure.GetWindowText(cstmp);
	dSoundPressure = atof(cstmp);
	m_cvEditBeamWidth.GetWindowText(cstmp);
	dBeamWidth = atof(cstmp);
	m_cvEditDecoyDoppler.GetWindowText(cstmp);
	dDecoyDoppler = atof(cstmp);
	m_cvEditThrowingDistance.GetWindowText(cstmp);
	dThrowingDistance = atof(cstmp);
	m_cvEditThrowingDirection.GetWindowText(cstmp);
	dThrowingDirection = atof(cstmp);
	m_cvEditWorkingTime.GetWindowText(cstmp);
	dWorkingTime = atof(cstmp);
	m_cvEditDelayTime.GetWindowText(cstmp);
	dDelayTime = atof(cstmp);

	// ��� preset ������ ��Ʈ��ũ�� ���� [6/15/2010 boxface]
	//////////////////////////////////////////////////////////////////////////
	EVENT_DECOY_PRESET sendData;
	memset(&sendData, 0x00, sizeof(EVENT_DECOY_PRESET));

	sendData.type = MSG_CODE_EVENT_DECOY_FIRE_0x72;
	sendData.length = sizeof(EVENT_DECOY_PRESET);

	sendData.oprationMode = iOperationMode;
	sendData.sendingMode = iSendingMode;
	sendData.frequence = (float)dFrequence;
	sendData.soundPressure = (float)dSoundPressure;
	sendData.beamWidth = (float)dSoundPressure;
	sendData.decoyDoppler = (float)dDecoyDoppler;
	sendData.throwingDistance = (float)dThrowingDistance;
	sendData.throwingDirection = (float)dThrowingDirection;
	sendData.workingTime = (float)dWorkingTime;
	sendData.delayTime = (float)dDelayTime;

	char sendBuf[NETWORK_MAXSIZE];
	memcpy(&sendBuf, (char*)&sendData, sizeof(EVENT_DECOY_PRESET));
	//SendEventData(sendBuf, sizeof(EVENT_DECOY_PRESET));
	//////////////////////////////////////////////////////////////////////////
}


void CTestFramework_TDCtrlDlg::OnBnClickedButtonTubeAssignment()
{
	TubeAssignmentDlg tubeAssignmentDlg;

	tubeAssignmentDlg.setCurObjectID(m_iCurObjectID);

	if (tubeAssignmentDlg.DoModal() == IDOK)
	{
		AfxMessageBox("�Ҵ������� ��Ʈ��ũ�� �����ߴ� !!");
	}
	else
	{
		AfxMessageBox("�Ҵ����� ������ ����ߴ� !!");
	}


}


void CTestFramework_TDCtrlDlg::OnBnClickedButtonTubeStatus()
{

	// ��� preset ������ ��Ʈ��ũ�� ���� [6/15/2010 boxface]
	//////////////////////////////////////////////////////////////////////////
	UPDATE_TUBE_STATUS sendData;
	memset(&sendData, 0x00, sizeof(UPDATE_TUBE_STATUS));

	sendData.type = MSG_CODE_UPDATE_TUBE_STATUS_0xA2;
	sendData.length = sizeof(UPDATE_TUBE_STATUS);

	sendData.objectID = 3001;
	sendData.tube_Number = 1;
	sendData.target_ObjectID = 2;
	sendData.tube_status = 1;
	sendData.weaponType = 1;
	sendData.weaponCharacter = 1;
	sendData.emergencyMode = 1;
	sendData.firingStatus = 1;

	sendData.wireLength = 323.4f;

	char sendBuf[NETWORK_MAXSIZE];
	memcpy(&sendBuf, (char*)&sendData, sizeof(UPDATE_TUBE_STATUS));
	//SendEventData(sendBuf, sizeof(UPDATE_TUBE_STATUS));
	//////////////////////////////////////////////////////////////////////////	
}


void CTestFramework_TDCtrlDlg::addObject(int objectID)
{
	CString cstmp;
	cstmp.Format("%d", objectID);
	m_cvCbxObjectID.AddString(cstmp);
}

void CTestFramework_TDCtrlDlg::deleteObject(int objectID)
{
	int curObjectID;
	CString cstmp;

	int i, count = m_cvCbxObjectID.GetCount();
	for (i = 0; i< count; i++)
	{
		m_cvCbxObjectID.GetLBText(i, cstmp);
		curObjectID = atoi(cstmp);
		if (objectID == curObjectID)
		{
			m_cvCbxObjectID.DeleteString(i);
			m_cvCbxObjectID.SetCurSel(0);
			break;
		}
	}

	count = m_cvCbxTorpedoIDList.GetCount();
	for (i = 0; i< count; i++)
	{
		m_cvCbxTorpedoIDList.GetLBText(i, cstmp);
		curObjectID = atoi(cstmp);
		if (objectID == curObjectID)
		{
			m_cvCbxTorpedoIDList.DeleteString(i);
			m_cvCbxTorpedoIDList.SetCurSel(0);
			break;
		}
	}
}

void CTestFramework_TDCtrlDlg::OnNMCustomdrawSliderHorizental(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMCUSTOMDRAW pNMCD = reinterpret_cast<LPNMCUSTOMDRAW>(pNMHDR);
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	int iIncreaseHeading = 50 - m_cvSldHeading.GetPos();
	m_pObjectManager.updateObjectAVel(m_iCurObjectID, (double)iIncreaseHeading*0.01);
	*pResult = 0;
}


void CTestFramework_TDCtrlDlg::OnNMCustomdrawSliderDepth(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMCUSTOMDRAW pNMCD = reinterpret_cast<LPNMCUSTOMDRAW>(pNMHDR);
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	int iIncreaseDepth = 50 - m_cvSldDepth.GetPos();
	m_pObjectManager.updateObjectDVel(m_iCurObjectID, (double)iIncreaseDepth*0.01);
	*pResult = 0;
}


void CTestFramework_TDCtrlDlg::OnNMCustomdrawSliderVertical(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMCUSTOMDRAW pNMCD = reinterpret_cast<LPNMCUSTOMDRAW>(pNMHDR);
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	int iVelcity = 50 - m_cvSldVelocity.GetPos();
	m_pObjectManager.updateObjectVel(m_iCurObjectID, (double)iVelcity*0.01);
	*pResult = 0;
}


void CTestFramework_TDCtrlDlg::OnBnClickedButtonResetH()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	m_cvSldHeading.SetPos(50);
}


void CTestFramework_TDCtrlDlg::OnBnClickedButtonResetDepth()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	m_cvSldDepth.SetPos(50);
}



void CTestFramework_TDCtrlDlg::OnBnClickedButtonResetV()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	m_cvSldVelocity.SetPos(50);
}


void CTestFramework_TDCtrlDlg::OnBnClickedButtonResetAll()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	m_cvSldHeading.SetPos(50);
	m_cvSldVelocity.SetPos(50);
	m_cvSldDepth.SetPos(50);
}
