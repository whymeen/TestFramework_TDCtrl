#pragma once


// TubeAssignmentDlg ��ȭ �����Դϴ�.

class TubeAssignmentDlg : public CDialogEx
{
	DECLARE_DYNAMIC(TubeAssignmentDlg)

public:
	TubeAssignmentDlg(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~TubeAssignmentDlg();

// ��ȭ ���� �������Դϴ�.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_TUBE_ASSIGN };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()

public:
	void setCurObjectID(int ID) { m_iCurObjectID = ID; }
	CComboBox m_cvCbxTorpedoIDList;
	CComboBox m_cvCbxTubeNum;
	CEdit m_cvEditTargetID;

	int m_iCurObjectID;
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedOk();
};
