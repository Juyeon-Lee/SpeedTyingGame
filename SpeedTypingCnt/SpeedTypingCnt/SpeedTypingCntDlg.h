
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
	

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_SPEEDTYPINGCNT_DIALOG };
#endif

	protected:
//	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 지원입니다.


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
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	
	CString global_userID;
	
	afx_msg void OnBnClickedButtonSolo();
	afx_msg void OnBnClickedButtonMatch();
	afx_msg void OnBnClickedButtonScore();
	virtual void DoDataExchange(CDataExchange* pDX);
	afx_msg void OnBnClickedButtonInit();
	CString m_strMainID;
	void OnButtonVisible();

	CFont m_font;

	CStatic m_title;
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
};
