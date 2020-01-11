// MatchGame.cpp: 구현 파일
//

#include "pch.h"
#include "SpeedTypingCnt.h"
#include "MatchGame.h"
#include "afxdialogex.h"
#include "CDlgConnect.h"
#include <iostream>
#include "ArrayList.h"


// MatchGame 대화 상자

IMPLEMENT_DYNAMIC(MatchGame, CDialogEx)

MatchGame::MatchGame(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_MATCH, pParent)
	, m_strTyping(_T(""))
	, m_strScore(_T("0"))
	, m_strID(_T("회원"))
	, m_word1(_T("함함하다"))
	, m_word10(_T("슬렉스"))
	, m_word11(_T("트리트먼트"))
	, m_word12(_T("치킨"))
	, m_word13(_T("의자"))
	, m_word14(_T("요거트"))
	, m_word15(_T("수맥"))
	, m_word2(_T("괴랄하다"))
	, m_word3(_T("신선함"))
	, m_word4(_T("고구마라떼"))
	, m_word5(_T("카푸치노"))
	, m_word6(_T("드라이기"))
	, m_word7(_T("가방"))
	, m_word8(_T("칠성"))
	, m_word9(_T("장수돌침대"))
{
	m_strList[0] = "함함하다";
	m_strList[1] = "괴랄하다";
	m_strList[2] = "신선함";
	m_strList[3] = "고구마라떼";
	m_strList[4] = "카푸치노";
	m_strList[5] = "드라이기";
	m_strList[6] = "가방";
	m_strList[7] = "칠성";
	m_strList[8] = "장수돌침대";
	m_strList[9] = "슬렉스";
	m_strList[10] = "트리트먼트";
	m_strList[11] = "치킨";
	m_strList[12] = "의자";
	m_strList[13] = "요거트";
	m_strList[14] = "수맥";
	endGameIndex = 0;
	score = _T("");
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
	DDX_Text(pDX, IDC_STATIC1, m_word1);
	DDX_Text(pDX, IDC_STATIC10, m_word10);
	DDX_Text(pDX, IDC_STATIC11, m_word11);
	DDX_Text(pDX, IDC_STATIC12, m_word12);
	DDX_Text(pDX, IDC_STATIC13, m_word13);
	DDX_Text(pDX, IDC_STATIC14, m_word14);
	DDX_Text(pDX, IDC_STATIC15, m_word15);
	DDX_Text(pDX, IDC_STATIC2, m_word2);
	DDX_Text(pDX, IDC_STATIC3, m_word3);
	DDX_Text(pDX, IDC_STATIC4, m_word4);
	//  DDX_Text(pDX, IDC_STATIC5, m_word);
	DDX_Text(pDX, IDC_STATIC5, m_word5);
	DDX_Text(pDX, IDC_STATIC6, m_word6);
	DDX_Text(pDX, IDC_STATIC7, m_word7);
	DDX_Text(pDX, IDC_STATIC8, m_word8);
	DDX_Text(pDX, IDC_STATIC9, m_word9);
	//  DDX_Text(pDX, IDC_STATIC_SCORETEXT, m_strScroreText);
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


BOOL MatchGame::PreTranslateMessage(MSG* pMsg)
{
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.

	// 엔터키 처리
	if ((pMsg->message == WM_KEYDOWN) && (pMsg->wParam == VK_RETURN))
	{
		// 여기에 원하는 동작의 코드를 삽입
		// EDIT TEXT에서 문자열 획득 후, STATIC TEXT들과 비교하는 함수로 전달
		CString str;
		GetDlgItemText(IDC_EDIT_TYPING, str);
		OnSearchWord(str);
		SetDlgItemText(IDC_EDIT_TYPING, "");
		return true;
	}

	return CDialogEx::PreTranslateMessage(pMsg);
}

// 입력한 단어를 화면에 있는 단어들과 비교 후 삭제하는 함수
void MatchGame::OnSearchWord(CString searchWord)
{
	// TODO: 여기에 구현 코드 추가.

	// 해당하는 단어 화면에서 지우기
	if (searchWord == m_word1)
	{
		SetDlgItemText(IDC_STATIC1, "");
		endGameIndex++;
		score.Format("%d", endGameIndex);
		SetDlgItemText(IDC_STATIC_SCORE, score);
	}
	else if (searchWord == m_word2)
	{
		SetDlgItemText(IDC_STATIC2, "");
		endGameIndex++;
		score.Format("%d", endGameIndex);
		SetDlgItemText(IDC_STATIC_SCORE, score);
	}
	else if (searchWord == m_word3)
	{
		SetDlgItemText(IDC_STATIC3, "");
		endGameIndex++;
		CString score;
		score.Format("%d", endGameIndex);
		SetDlgItemText(IDC_STATIC_SCORE, score);
	}
	else if (searchWord == m_word4)
	{
		SetDlgItemText(IDC_STATIC4, "");
		endGameIndex++;
		score.Format("%d", endGameIndex);
		SetDlgItemText(IDC_STATIC_SCORE, score);
	}
	else if (searchWord == m_word5)
	{
		SetDlgItemText(IDC_STATIC5, "");
		endGameIndex++;
		score.Format("%d", endGameIndex);
		SetDlgItemText(IDC_STATIC_SCORE, score);
	}
	else if (searchWord == m_word6)
	{
		SetDlgItemText(IDC_STATIC6, "");
		endGameIndex++;
		score.Format("%d", endGameIndex);
		SetDlgItemText(IDC_STATIC_SCORE, score);
	}
	else if (searchWord == m_word7)
	{
		SetDlgItemText(IDC_STATIC7, "");
		endGameIndex++;
		score.Format("%d", endGameIndex);
		SetDlgItemText(IDC_STATIC_SCORE, score);
	}
	else if (searchWord == m_word8)
	{
		SetDlgItemText(IDC_STATIC8, "");
		endGameIndex++;
		score.Format("%d", endGameIndex);
		SetDlgItemText(IDC_STATIC_SCORE, score);
	}
	else if (searchWord == m_word9)
	{
		SetDlgItemText(IDC_STATIC9, "");
		endGameIndex++;
		score.Format("%d", endGameIndex);
		SetDlgItemText(IDC_STATIC_SCORE, score);
	}
	else if (searchWord == m_word10)
	{
		SetDlgItemText(IDC_STATIC10, "");
		endGameIndex++;
		score.Format("%d", endGameIndex);
		SetDlgItemText(IDC_STATIC_SCORE, score);
	}
	else if (searchWord == m_word11)
	{
		SetDlgItemText(IDC_STATIC11, "");
		endGameIndex++;
		score.Format("%d", endGameIndex);
		SetDlgItemText(IDC_STATIC_SCORE, score);
	}
	else if (searchWord == m_word12)
	{
		SetDlgItemText(IDC_STATIC12, "");
		endGameIndex++;
		score.Format("%d", endGameIndex);
		SetDlgItemText(IDC_STATIC_SCORE, score);
	}
	else if (searchWord == m_word13)
	{
		SetDlgItemText(IDC_STATIC13, "");
		endGameIndex++;
		score.Format("%d", endGameIndex);
		SetDlgItemText(IDC_STATIC_SCORE, score);
	}
	else if (searchWord == m_word14)
	{
		SetDlgItemText(IDC_STATIC14, "");
		endGameIndex++;
		score.Format("%d", endGameIndex);
		SetDlgItemText(IDC_STATIC_SCORE, score);
	}
	else if (searchWord == m_word15)
	{
		SetDlgItemText(IDC_STATIC15, "");
		endGameIndex++;
		score.Format("%d", endGameIndex);
		SetDlgItemText(IDC_STATIC_SCORE, score);
	}

	if (endGameIndex >= 15)
	{
		MessageBox("게임이 종료되었습니다!\n최종 스코어 : " + score + "점");
	}
}
