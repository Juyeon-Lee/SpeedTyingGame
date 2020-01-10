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
	, m_strScore(_T("점수 :"))
	, m_strID(_T("회원"))
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
			MessageBox(_T("접속 성공!"));
			GetDlgItem(IDOK)->EnableWindow(TRUE);
		}
		else
		{
			MessageBox(_T("접속 실패..."));

			GetDlgItem(IDOK)->EnableWindow(FALSE);
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

	// strTmp에 헤더를 저장
	strTmp.Format("%c", pTmp[0]);

	// 받은 데이터의 헤더를 분석해 행동을 결정한다
	int iType = atoi(strTmp);
	
	return LPARAM();
}
