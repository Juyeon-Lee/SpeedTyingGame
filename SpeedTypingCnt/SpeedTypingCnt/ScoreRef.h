#pragma once


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
};
