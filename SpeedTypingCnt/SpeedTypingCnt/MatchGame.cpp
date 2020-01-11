// MatchGame.cpp: 구현 파일
//

#include "pch.h"
#include "SpeedTypingCnt.h"
#include "MatchGame.h"
#include "afxdialogex.h"
#include "CDlgConnect.h"

// MatchGame 대화 상자

IMPLEMENT_DYNAMIC(MatchGame, CDialogEx)

MatchGame::MatchGame(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_MATCH, pParent)
	, m_strTyping(_T(""))
	, m_strScore(_T("0점"))
	, m_strID(_T("회원"))
	, m_strConnect(_T(""))
{

}

MatchGame::~MatchGame()
{
}

void MatchGame::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_TYPING, m_strTyping);
	DDX_Text(pDX, IDC_STATIC_SCORE, m_strScore);
	DDX_Text(pDX, IDC_STATIC_ID, m_strID);
	DDX_Text(pDX, IDC_STATIC_STATUS, m_strConnect);
}


BEGIN_MESSAGE_MAP(MatchGame, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON_CONNECT, &MatchGame::OnBnClickedButtonConnect)
END_MESSAGE_MAP()


// MatchGame 메시지 처리기


void MatchGame::OnBnClickedButtonConnect()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CDlgConnect* dlg = new CDlgConnect;

	if (dlg->DoModal() == IDOK)
	{
		m_socCom.Create();

		// IP 주소와 포트 번호를 지정
		BOOL b = m_socCom.Connect(dlg->m_strIP, 5000);
		if (b)
		{
			m_socCom.Init(this->m_hWnd);
			m_strConnect = "접속성공";
			MessageBox(_T("접속 성공!"));
			//m_bConnect = TRUE;
			GetDlgItem(IDC_EDIT_TYPING)->EnableWindow(TRUE);
		}
		else
		{
			m_strConnect = "접속실패";
			MessageBox(_T("접속 실패..."));

			GetDlgItem(IDC_EDIT_TYPING)->EnableWindow(FALSE);
		}

		UpdateData(FALSE);
	}
}


LPARAM MatchGame::OnReceive(UINT wParam, LPARAM lParam)
{
	// TODO: 여기에 구현 코드 추가.
	char pTmp[256];
	CString strTmp, str;
	memset(pTmp, '\0', 256);

	// 데이터를 pTmp에 받는다
	m_socCom.Receive(pTmp, 256);

	//일단은 헤더 없음

	str.Format("%s", pTmp);
	
	EraseCheck(atoi(str));

	if (IsGameEnd()) {
		Sleep(1000);
		SetGameEnd();
	}

	
	return LPARAM();
}


BOOL MatchGame::IsGameEnd()
{
	if (m_wordNum)
		return TRUE;
	else
		return FALSE;
}


void MatchGame::EraseCheck(int wordIndex)
{
	switch (wordIndex)
	{
	case 1:
		(GetDlgItem(IDC_STATIC1))->ShowWindow(FALSE);
	case 2:
		(GetDlgItem(IDC_STATIC2))->ShowWindow(FALSE);
	case 3:
		(GetDlgItem(IDC_STATIC3))->ShowWindow(FALSE);
	case 4:
		(GetDlgItem(IDC_STATIC4))->ShowWindow(FALSE);
	case 5:
		(GetDlgItem(IDC_STATIC5))->ShowWindow(FALSE);
	case 6:
		(GetDlgItem(IDC_STATIC6))->ShowWindow(FALSE);
	case 7:
		(GetDlgItem(IDC_STATIC7))->ShowWindow(FALSE);
	case 8:
		(GetDlgItem(IDC_STATIC8))->ShowWindow(FALSE);
	case 9:
		(GetDlgItem(IDC_STATIC9))->ShowWindow(FALSE);
	case 10:
		(GetDlgItem(IDC_STATIC10))->ShowWindow(FALSE);
	case 11:
		(GetDlgItem(IDC_STATIC11))->ShowWindow(FALSE);
	case 12:
		(GetDlgItem(IDC_STATIC12))->ShowWindow(FALSE);
	case 13:
		(GetDlgItem(IDC_STATIC13))->ShowWindow(FALSE);
	case 14:
		(GetDlgItem(IDC_STATIC14))->ShowWindow(FALSE);
	case 15:
		(GetDlgItem(IDC_STATIC15))->ShowWindow(FALSE);
	default:
		break;
	}
}


void MatchGame::SetGameEnd()
{
	int competitorScore = 15 - m_myScore;
	if (competitorScore > m_myScore)
		MessageBox("패");
	else
		MessageBox("승");

}
