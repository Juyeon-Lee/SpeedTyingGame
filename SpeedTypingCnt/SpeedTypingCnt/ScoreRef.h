#pragma once


#include "afxdb.h"

// CScoreRef 대화 상자

class CScoreRef : public CDialogEx
{
	DECLARE_DYNAMIC(CScoreRef)

public:
	CScoreRef(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~CScoreRef();

	// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_SCORE };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	CListCtrl m_scoreList;
	//	CString m_strIP_score;
	virtual BOOL OnInitDialog();
	CString m_strID_score;
	SQLHANDLE mh_environment; //ODBC 기술을 사용하기 위한 환경 정보
	SQLHDBC mh_odbc; // ODBC  함수를 사용하기 위한 정보
	char m_connect_flag = 0; //서버와 연결 여부를 저장할 변수(1:연결)
	CDatabase m_db;
	CRecordset* m_pRs;

	afx_msg void OnStnClickedStaticIdScore();
	afx_msg void OnBnClickedButton1();
};
