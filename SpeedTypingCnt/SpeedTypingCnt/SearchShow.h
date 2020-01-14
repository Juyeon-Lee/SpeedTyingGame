#pragma once

#include "afxdb.h"
#include "Search.h"
// SearchShow 대화 상자

class SearchShow : public CDialogEx
{
	DECLARE_DYNAMIC(SearchShow)

public:
	SearchShow(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~SearchShow();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_SEARCH_SHOW };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
//	CListCtrl m_scoreList;
	CString m_strID_score;
	SQLHANDLE mh_environment; //ODBC 기술을 사용하기 위한 환경 정보
	SQLHDBC mh_odbc; // ODBC  함수를 사용하기 위한 정보
	char m_connect_flag = 0; //서버와 연결 여부를 저장할 변수(1:연결)
	CDatabase m_db;
	CRecordset* m_pRs;

	CListCtrl m_scoreList;
	CString m_strID_search_show;
};
