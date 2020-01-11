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
	DDX_Text(pDX, IDC_STATIC5, m_word5);
	DDX_Text(pDX, IDC_STATIC6, m_word6);
	DDX_Text(pDX, IDC_STATIC7, m_word7);
	DDX_Text(pDX, IDC_STATIC8, m_word8);
	DDX_Text(pDX, IDC_STATIC9, m_word9);
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
			// m_strConnect = "접속성공";
			MessageBox(_T("접속 성공!"));
			//m_bConnect = TRUE;
			// GetDlgItem(IDC_EDIT_TYPING)->EnableWindow(TRUE);
		}
		else
		{
			// m_strConnect = "접속실패";
			MessageBox(_T("접속 실패..."));

			// GetDlgItem(IDC_EDIT_TYPING)->EnableWindow(FALSE);
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
	/*
	EraseCheck(atoi(str));

	if (IsGameEnd()) {
		Sleep(1000);
		SetGameEnd();
	}*/

	
	return LPARAM();
}


BOOL MatchGame::PreTranslateMessage(MSG* pMsg)
{
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.

	// 엔터키 처리
	if ((pMsg->message == WM_KEYDOWN) && (pMsg->wParam == VK_RETURN))
	{
		// EDIT TEXT에서 문자열 획득 후, STATIC TEXT들과 비교하는 함수로 전달
		CString str;
		int index;
		GetDlgItemText(IDC_EDIT_TYPING, str);

		index = staticStringToIndex(str);

		// 찾은 인덱스로 EraseCheck(인덱스)하면 단어가 삭제
		if (index)
			EraseCheck(index);
		if(IsGameEnd())
			MessageBox("게임이 종료되었습니다!\n최종 스코어 : " + score + "점");

		SetDlgItemText(IDC_EDIT_TYPING, "");
		return true;
	}

	return CDialogEx::PreTranslateMessage(pMsg);
}


BOOL MatchGame::IsGameEnd()
{
	// TODO: 여기에 구현 코드 추가.
	if (endGameIndex >= 15)
		return TRUE;
	else
		return FALSE;

}


int MatchGame::staticStringToIndex(CString str)
{
	if (str == m_word1)
		return 1;
	else if (str == m_word2)
		return 2;
	else if (str == m_word3)
		return 3;
	else if (str == m_word4)
		return 4;
	else if (str == m_word5)
		return 5;
	else if (str == m_word6)
		return 6;
	else if (str == m_word7)
		return 7;
	else if (str == m_word8)
		return 8;
	else if (str == m_word9)
		return 9;
	else if (str == m_word10)
		return 10;
	else if (str == m_word11)
		return 11;
	else if (str == m_word12)
		return 12;
	else if (str == m_word13)
		return 13;
	else if (str == m_word14)
		return 14;
	else if (str == m_word15)
		return 15;
	else // 맞는 단어 없음
		return 0;
}


void MatchGame::EraseCheck(int wordIndex)
{
	// TODO: 여기에 구현 코드 추가.
	switch (wordIndex)
	{
	case 1:
		(GetDlgItem(IDC_STATIC1))->ShowWindow(FALSE);
		break;
	case 2:
		(GetDlgItem(IDC_STATIC2))->ShowWindow(FALSE);
		break;
	case 3:
		(GetDlgItem(IDC_STATIC3))->ShowWindow(FALSE);
		break;
	case 4:
		(GetDlgItem(IDC_STATIC4))->ShowWindow(FALSE);
		break;
	case 5:
		(GetDlgItem(IDC_STATIC5))->ShowWindow(FALSE);
		break;
	case 6:
		(GetDlgItem(IDC_STATIC6))->ShowWindow(FALSE);
		break;
	case 7:
		(GetDlgItem(IDC_STATIC7))->ShowWindow(FALSE);
		break;
	case 8:
		(GetDlgItem(IDC_STATIC8))->ShowWindow(FALSE);
		break;
	case 9:
		(GetDlgItem(IDC_STATIC9))->ShowWindow(FALSE);
		break;
	case 10:
		(GetDlgItem(IDC_STATIC10))->ShowWindow(FALSE);
		break;
	case 11:
		(GetDlgItem(IDC_STATIC11))->ShowWindow(FALSE);
		break;
	case 12:
		(GetDlgItem(IDC_STATIC12))->ShowWindow(FALSE);
		break;
	case 13:
		(GetDlgItem(IDC_STATIC13))->ShowWindow(FALSE);
		break;
	case 14:
		(GetDlgItem(IDC_STATIC14))->ShowWindow(FALSE);
		break;
	case 15:
		(GetDlgItem(IDC_STATIC15))->ShowWindow(FALSE);
		break;
	default:
		return;
	}

	// 일치하는 단어 찾았을 때만
	endGameIndex++;
	score.Format("%d", endGameIndex);
	SetDlgItemText(IDC_STATIC_SCORE, score);
}

void MatchGame::SetGameEnd()
{
	// TODO: 여기에 구현 코드 추가.
	int competitorScore = 15 - m_myScore;
	if (competitorScore > m_myScore)
		MessageBox("패");
	else
		MessageBox("승");

}

