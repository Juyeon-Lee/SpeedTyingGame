
// SpeedTypingCntDlg.h: 헤더 파일
//

#pragma once
# include <afxdb.h>

// CSpeedTypingCntDlg 대화 상자
class CSpeedTypingCntDlg : public CDialogEx
{
// 생성입니다.
public:
	CSpeedTypingCntDlg(CWnd* pParent = nullptr);	// 표준 생성자입니다.
	
	CDatabase m_db;
	CRecordset* m_pRs;

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_SPEEDTYPINGCNT_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 지원입니다.


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
	afx_msg void OnButtonInit();
};
