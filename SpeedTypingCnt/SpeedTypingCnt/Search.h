#pragma once


// Search 대화 상자

class Search : public CDialogEx
{
	DECLARE_DYNAMIC(Search)

public:
	Search(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~Search();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_SEARCH };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	CString m_searchID;
	//afx_msg void OnBnClickedButtonEnter();
	afx_msg void OnBnClickedOk();
};
