#pragma once


// TubeAssignmentDlg 대화 상자입니다.

class TubeAssignmentDlg : public CDialogEx
{
	DECLARE_DYNAMIC(TubeAssignmentDlg)

public:
	TubeAssignmentDlg(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~TubeAssignmentDlg();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_TUBE_ASSIGN };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

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
