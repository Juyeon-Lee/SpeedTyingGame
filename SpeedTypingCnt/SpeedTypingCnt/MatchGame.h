#pragma once

#include "CSocCom.h"

// MatchGame 대화 상자

class MatchGame : public CDialogEx
{
	DECLARE_DYNAMIC(MatchGame)

public:
	MatchGame(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~MatchGame();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_MATCH };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	const CString statics = "IDC_STATIC";
	int m_wordNum = 15;
	int m_myScore = 0;
	CString m_strTyping;
	CString m_strScore;
	CString m_strID;
	CSocCom m_socCom;
	afx_msg void OnBnClickedButtonConnect();
	LPARAM OnReceive(UINT wParam, LPARAM lParam);
	CString m_strConnect;
	BOOL IsGameEnd();
	void EraseCheck(int wordIndex);
	void SetGameEnd();
};
