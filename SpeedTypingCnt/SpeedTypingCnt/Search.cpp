// Search.cpp: 구현 파일
//

#include "pch.h"
#include "SpeedTypingCnt.h"
#include "Search.h"
#include "afxdialogex.h"
#include "ScoreRef.h"
#include "SearchShow.h"

// Search 대화 상자

IMPLEMENT_DYNAMIC(Search, CDialogEx)

Search::Search(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_SEARCH, pParent)
	, m_searchID(_T(""))
{

}

Search::~Search()
{
}

void Search::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_ID, m_searchID);
}


BEGIN_MESSAGE_MAP(Search, CDialogEx)
	//ON_BN_CLICKED(IDC_BUTTON_ENTER, &Search::OnBnClickedButtonEnter)
	ON_BN_CLICKED(IDOK, &Search::OnBnClickedOk)
END_MESSAGE_MAP()


// Search 메시지 처리기

// 검색 버튼 클릭 시
void Search::OnBnClickedOk()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	SearchShow* dlg = new SearchShow;
	GetDlgItemText(IDC_EDIT_ID, dlg->m_strID_search_show);	// 입력값을 m_strID_search_show변수에 넣고
	dlg->DoModal();											// SearchShow 다이얼로그를 띄운다
	delete dlg;
}
