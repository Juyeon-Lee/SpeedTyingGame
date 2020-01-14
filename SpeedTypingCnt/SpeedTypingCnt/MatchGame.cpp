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
	, m_word1(_T(""))
	, m_word10(_T(""))
	, m_word11(_T(""))
	, m_word12(_T(""))
	, m_word13(_T(""))
	, m_word14(_T(""))
	, m_word15(_T(""))
	, m_word2(_T(""))
	, m_word3(_T(""))
	, m_word4(_T(""))
	, m_word5(_T(""))
	, m_word6(_T(""))
	, m_word7(_T(""))
	, m_word8(_T(""))
	, m_word9(_T(""))
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
	DDX_Text(pDX, IDC_STATIC_STATUS, m_strConnect);
}


BEGIN_MESSAGE_MAP(MatchGame, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON_CONNECT, &MatchGame::OnBnClickedButtonConnect)
	ON_MESSAGE(UM_RECEIVE, &MatchGame::OnReceive)
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
			m_bConnect = TRUE;
			GetDlgItem(IDC_EDIT_TYPING)->EnableWindow(TRUE);
		}
		else
		{
			MessageBox(_T("접속 실패..."));
		}

		UpdateData(FALSE);
	}
}

afx_msg LRESULT MatchGame::OnReceive(WPARAM wParam, LPARAM lParam)
{
	char pTmp[256];
	CString str;
	memset(pTmp, '\0', 256);

	// 데이터를 pTmp에 받는다
	m_socCom.Receive(pTmp, 256);

	//일단은 헤더 없음

	str.Format("%s", pTmp);
	if (str == _T("접속성공"))
	{
		m_bConnect = TRUE;
	}
	else if (str.Find(",") != std::string::npos) // for setting m_words
	{
		scatterStrToWords(str);
	}
	else 
	{
		EraseCheck(atoi(str), FALSE);

		if (IsGameEnd()) {
			Sleep(1000);
			SetGameEnd();
		}
	}
	
	return LPARAM();
}


BOOL MatchGame::PreTranslateMessage(MSG* pMsg)
{
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.
	CString str;
	int index;

	// 엔터키 처리
	if ((pMsg->message == WM_KEYDOWN)
		&& pMsg->hwnd == GetDlgItem(IDC_EDIT_TYPING)->m_hWnd
		&& (pMsg->wParam == VK_RETURN)
		&& m_bConnect == TRUE)
	{
		// EDIT TEXT에서 문자열 획득 후, STATIC TEXT들과 비교하는 함수로 전달
		
		GetDlgItemText(IDC_EDIT_TYPING, str);

		index = staticStringToIndex(str);

		if (index) // 찾은 인덱스로 EraseCheck(인덱스)하면 단어가 삭제
		{
			EraseCheck(index, TRUE);
			UpdateData(FALSE);
			str.Format("%d", index);
			SendGame(str);
		}
			
		if (IsGameEnd())
		{
			//str.Format("%s%d%s", "게임이 종료되었습니다!\n최종 스코어 :", m_myScore, "점");
			//AfxMessageBox(str);
			Sleep(1000);
			SetGameEnd();
		}

		SetDlgItemText(IDC_EDIT_TYPING, "");
		return true;
	}

	return CDialogEx::PreTranslateMessage(pMsg);
}

BOOL MatchGame::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  여기에 추가 초기화 작업을 추가합니다.
	endGameIndex = 0;
	score = _T("");
	m_strScore.Format("%d%s", m_myScore, "점");
	m_bConnect = FALSE;

	GetDlgItem(IDC_EDIT_TYPING)->EnableWindow(FALSE);
	//UpdateData(TRUE);
	CString a;
	a.Format("%s","ab,bb,cc,dd,ee,ff,ab,bb,cc,dd,ee,ff,cc,dd,ee");
	scatterStrToWords(a);

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}

BOOL MatchGame::IsGameEnd()
{
	// TODO: 여기에 구현 코드 추가.
	if (endGameIndex >= 15)
		return TRUE;
	else
		return FALSE;

}

//str 멤버변수 중에서 일치하는 static이 몇번째인지 알려준다.
//일치하는 것이 없다면 0이 반환된다.
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

// wordIndex로 해당하는 static을 지워준다.
// itsMe : 자기 자신일 때만 m_myScore를 올려준다.
void MatchGame::EraseCheck(int wordIndex, BOOL itsMe)
{
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
	if (itsMe)//내가 맞췄을 때만 내 점수 오른다.
	{
		m_myScore++;
		m_strScore.Format("%d", m_myScore);
	}

	score.Format("%d", endGameIndex);
}

void MatchGame::SetGameEnd()
{
	// TODO: 여기에 구현 코드 추가.
	int competitorScore = 15 - m_myScore;
	if (competitorScore > m_myScore)
		MessageBox("패");
	else
		MessageBox("승");
	try
	{
		BOOL bOpen = m_db.OpenEx(_T("DRIVER={MYSQL ODBC 8.0 Unicode Driver};SERVER=127.0.0.1;PORT=3306;USER=root;PASSWORD=root;DATABASE=typing;OPTION=3;"), CDatabase::noOdbcDialog);
		if (bOpen)
			m_pRs = new CRecordset(&m_db);
	}
	catch (CException * e)
	{
		e->ReportError();

	}


	try
	{
		CString sData(_T(""));
		CString u[30][10];
		BOOL bOpen = m_pRs->Open(CRecordset::snapshot, "select member_id from user where username ='" + m_strID + "'");

		if (bOpen)
		{
			int iRow = 1;
			BOOL bIsEOF = m_pRs->IsEOF();
			DWORD dwSize = m_pRs->GetRowsetSize();
			if (!bIsEOF)
			{
				for (m_pRs->MoveFirst(); !m_pRs->IsEOF(); m_pRs->MoveNext())
				{
					int iFieldCnt = m_pRs->GetODBCFieldCount();
					for (int iCol = 0; iCol < iFieldCnt; iCol++)
					{
						CString sItem;
						m_pRs->SetAbsolutePosition(iRow);
						m_pRs->GetFieldValue(iCol, sItem);


						u[iRow - 1][iCol] = sItem;
						UpdateData(FALSE);

					}

					iRow++;
				}
			}
			m_db.BeginTrans();

			UpdateData(TRUE);

			m_db.ExecuteSQL(_T("INSERT INTO score(user_id,user_score,user_date) VALUES('" + u[0][0] + "','" + m_strScore + "',now())"));

			m_db.CommitTrans();
		}
	}

	catch (CException * e)
	{
		e->ReportError();
	}
	


	//Sleep(1000);

	try
	{
		BOOL bOpen = m_db.OpenEx(_T("DRIVER={MYSQL ODBC 8.0 Unicode Driver};SERVER=127.0.0.1;PORT=3306;USER=root;PASSWORD=root;DATABASE=typing;OPTION=3;"), CDatabase::noOdbcDialog);
		if (bOpen)
			m_pRs = new CRecordset(&m_db);
	}
	catch (CException * e)
	{
		e->ReportError();

	}


	try
	{
		CString sData(_T(""));
		CString u[30][10];
		BOOL bOpen = m_pRs->Open(CRecordset::snapshot, "select member_id from user where username ='" + m_strID + "'");

		if (bOpen)
		{
			int iRow = 1;
			BOOL bIsEOF = m_pRs->IsEOF();
			DWORD dwSize = m_pRs->GetRowsetSize();
			if (!bIsEOF)
			{
				for (m_pRs->MoveFirst(); !m_pRs->IsEOF(); m_pRs->MoveNext())
				{
					int iFieldCnt = m_pRs->GetODBCFieldCount();
					for (int iCol = 0; iCol < iFieldCnt; iCol++)
					{
						CString sItem;
						m_pRs->SetAbsolutePosition(iRow);
						m_pRs->GetFieldValue(iCol, sItem);


						u[iRow - 1][iCol] = sItem;
						UpdateData(FALSE);

					}

					iRow++;
				}
			}
			m_db.BeginTrans();

			UpdateData(TRUE);
			CString sqlStr = "INSERT INTO score(user_id,user_score,user_date) VALUES('" + u[0][0] + "','" + m_strScore + "',now())";
			m_db.ExecuteSQL(sqlStr);

			m_db.CommitTrans();
		}
	}
	catch (CException * e)
	{
		e->ReportError();
	}	
}

void MatchGame::SendGame(CString strTmp)
{
	// 데이터 전송
	UpdateData(TRUE);
	char pTmp[256];

	memset(pTmp, '\0', 256);
	sprintf_s(pTmp, 256, "%s", strTmp);

	m_socCom.Send(pTmp, 256);
}

void MatchGame::scatterStrToWords(CString sData)
{
	// TODO: 여기에 구현 코드 추가.
	AfxExtractSubString(m_word1, sData, 0, ',');
	AfxExtractSubString(m_word2, sData, 1, ',');
	AfxExtractSubString(m_word3, sData, 2, ',');
	AfxExtractSubString(m_word4, sData, 3, ',');
	AfxExtractSubString(m_word5, sData, 4, ',');
	AfxExtractSubString(m_word6, sData, 5, ',');
	AfxExtractSubString(m_word7, sData, 6, ',');
	AfxExtractSubString(m_word8, sData, 7, ',');
	AfxExtractSubString(m_word9, sData, 8, ',');
	AfxExtractSubString(m_word10, sData, 9, ',');
	AfxExtractSubString(m_word11, sData, 10, ',');
	AfxExtractSubString(m_word12, sData, 11, ',');
	AfxExtractSubString(m_word13, sData, 12, ',');
	AfxExtractSubString(m_word14, sData, 13, ',');
	AfxExtractSubString(m_word15, sData, 14, ',');

	UpdateData(false);

}
