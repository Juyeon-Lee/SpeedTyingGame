#pragma once

#include "afxdialogex.h"
// SoloGameEng 대화 상자

class SoloGameEng : public CDialogEx
{
	DECLARE_DYNAMIC(SoloGameEng)

public:
	SoloGameEng(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~SoloGameEng();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_SOLO21 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.
	CStringList m_string_list;

	DECLARE_MESSAGE_MAP()
public:
	//	CString m_strTyping;
		//CString m_strTime;

	//	CEdit m_strTyping;
	//	CButton m_strSend;


	virtual BOOL PreTranslateMessage(MSG* pMsg);
	void SetWord(int a, CString word);
	void ViewWord();
	void EraseCheck(int cnt);
	BOOL IsGameEnd(int cnt);
	int endcnt;
	int cnt;

	clock_t startTime;
	clock_t endTime;
	double result;
	//	CString m_strID;
//
	CString word1;
	CString word2;
	CString word3;
	CString word4;
	CString word5;
	CString word6;
	CString word7;
	CString word8;
	CString word9;
	CString word10;
	CString word11;
	CString word12;
	CString word13;
	CString word14;
	CString word15;
	CString word[10][10];

	CDatabase m_db;
	CRecordset* m_pRs;



	
	virtual BOOL OnInitDialog();
	void OnReceiveWord();
	
	CStatic m_txt1;
	CStatic m_txt10;
	CEdit m_strTyping1;
	CStatic m_txt11;
	CStatic m_txt12;
	CStatic m_txt13;
	CStatic m_txt14;
	CStatic m_txt15;
	CStatic m_txt2;
	CStatic m_txt3;
	CStatic m_txt4;
	CStatic m_txt5;
	CStatic m_txt6;
	CStatic m_txt7;
	CStatic m_txt8;
	CStatic m_txt9;
};
