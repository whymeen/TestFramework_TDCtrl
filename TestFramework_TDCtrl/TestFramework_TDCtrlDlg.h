
// TestFramework_TDCtrlDlg.h : 헤더 파일
//

#pragma once
#include "afxwin.h"
#include "afxcmn.h"
#include "objectBase.h"
#include "ObjectMananger.h"
#include "TubeAssignmentDlg.h"


// CTestFramework_TDCtrlDlg 대화 상자
class CTestFramework_TDCtrlDlg : public CDialogEx
{
// 생성입니다.
public:
	CTestFramework_TDCtrlDlg(CWnd* pParent = NULL);	// 표준 생성자입니다.

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_TESTFRAMEWORK_TDCTRL_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 지원입니다.

public:

	int m_iCurObjectID;
	CObjectMananger m_pObjectManager;

	CComboBox m_cvCbxObjectID;
	CComboBox m_cvCbxTorpedoIDList;
	CComboBox m_cvCbxDecoyList;
	CComboBox m_cvCbxOperationMode;
	CComboBox m_cvCbxSendingMode;
	CEdit m_cvEditFrequence;
	CEdit m_cvEditSoundPressure;
	CEdit m_cvEditBeamWidth;
	CEdit m_cvEditDecoyDoppler;
	CEdit m_cvEditThrowingDistance;
	CEdit m_cvEditThrowingDirection;
	CEdit m_cvEditWorkingTime;
	CEdit m_cvEditDelayTime;
	CComboBox m_cvCbxStraightSearchMode;
	CComboBox m_cvCbxTorpedoState;
	CComboBox m_cvCbxGuidMode;
	CComboBox m_cvCbxGuidMethod;
	CComboBox m_cvCbxSpeedStep;
	CComboBox m_cvCbxTargetMode;
	CComboBox m_cvCbxTargetDetectStatus;
	CComboBox m_cvCbxTOSOMode;
	CComboBox m_cvCbxTransCtrlMode;
	CComboBox m_cvCbxTransPursMode;
	CComboBox m_cvCbxTargetSupport;
	CEdit m_cvEditCourse;
	CEdit m_cvEditProCourse;
	CEdit m_cvEditHDepth;
	CEdit m_cvEditMDepth;
	CEdit m_cvEditLDepth;

	CSliderCtrl m_cvSldHeading;
	CSliderCtrl m_cvSldDepth;
	CSliderCtrl m_cvSldVelocity;

// 구현입니다.
protected:
	HICON m_hIcon;

	// 생성된 메시지 맵 함수
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnCbnSelendcancelComboObjectid();
	afx_msg void OnBnClickedButtonFire();
	afx_msg void OnBnClickedButtonDecoyFire();
	afx_msg void OnBnClickedButtonTorpedoPreset();
	afx_msg void OnBnClickedButtonDecoyPreset();
	afx_msg void OnBnClickedButtonTubeAssignment();
	afx_msg void OnBnClickedButtonTubeStatus();

	void addObject(int objectID);
	void deleteObject(int objectID);
	afx_msg void OnNMCustomdrawSliderHorizental(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNMCustomdrawSliderDepth(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNMCustomdrawSliderVertical(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnBnClickedButtonResetH();
	afx_msg void OnBnClickedButtonResetDepth();
//	afx_msg void OnBnDropDownButtonResetV(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnBnClickedButtonResetV();
	afx_msg void OnBnClickedButtonResetAll();
};
