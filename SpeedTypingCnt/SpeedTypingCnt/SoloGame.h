#pragma once


// SoloGame 대화 상자

class SoloGame : public CDialogEx
{
	DECLARE_DYNAMIC(SoloGame)

public:
	SoloGame(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~SoloGame();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_SOLO };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	
	CString m_strID;

	CEdit m_strTyping;
	CButton m_strSend;
	CStringList m_string_list;
	
	virtual BOOL PreTranslateMessage(MSG* pMsg); 
	void SetWord();
	void ViewWord();
	void EraseCheck(int cnt);
	BOOL IsGameEnd(int endcnt);
	int endcnt;
	int cnt;
	
	clock_t startTime;
	clock_t endTime;
	double result;
	

	CStatic m_txt1;
	CStatic m_txt10;
	CStatic m_txt11;
	CStatic m_txt12;
	CStatic m_txt13;
	CStatic m_txt14;
	CStatic m_txt15;
	CStatic m_txt2;
	CStatic m_txt3;
	CStatic m_txt5;
	CStatic m_txt4;
	CStatic m_txt6;
	CStatic m_txt7;
	CStatic m_Txt8;
	CStatic m_txt9;
	
};
