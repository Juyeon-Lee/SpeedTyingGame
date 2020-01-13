#pragma once
# include <afxdb.h>

// CDlgLogin 대화 상자

class CDlgLogin : public CDialogEx
{
	DECLARE_DYNAMIC(CDlgLogin)

public:
	CDlgLogin(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~CDlgLogin();
	
// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_LOGIN };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	CString m_strID;
	CString m_strPW;
	CDatabase m_db;
	CRecordset* m_pRs;
	afx_msg void OnClickedButtonAdd();
//	afx_msg void OnBnClickedButtonLogin();
//	CString idText;
	afx_msg void OnBnClickedButtonLogin();
	CString userID;
	CString userPW;
};
