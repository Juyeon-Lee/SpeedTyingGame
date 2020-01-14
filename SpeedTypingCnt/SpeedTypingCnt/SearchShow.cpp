// SearchShow.cpp: 구현 파일
//

#include "pch.h"
#include "SpeedTypingCnt.h"
#include "SearchShow.h"
#include "afxdialogex.h"

//ODBC API를 사용하기 위한 라이브러리 추가
#pragma comment(lib,"odbc32.lib")


// SearchShow 대화 상자

IMPLEMENT_DYNAMIC(SearchShow, CDialogEx)

SearchShow::SearchShow(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_SEARCH_SHOW, pParent)
{

	m_strID_search_show = _T("");
}

SearchShow::~SearchShow()
{
}

void SearchShow::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST_SCORE, m_scoreList);
}


BEGIN_MESSAGE_MAP(SearchShow, CDialogEx)
END_MESSAGE_MAP()


// SearchShow 메시지 처리기


BOOL SearchShow::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  여기에 추가 초기화 작업을 추가합니다.

	
	try {
		BOOL bOpen = m_db.OpenEx(_T("DRIVER={MYSQL ODBC 8.0 Unicode Driver};SERVER=127.0.0.1;PORT=3306;USER=root;PASSWORD=root;DATABASE=typing;OPTION=3;"), CDatabase::noOdbcDialog);
		if (bOpen)
			m_pRs = new CRecordset(&m_db);
	}
	catch (CException * e)
	{
		e->ReportError();
	}

	m_scoreList.InsertColumn(0, _T("입력일자"), LVCFMT_LEFT, 150);
	m_scoreList.InsertColumn(0, _T("점수"), LVCFMT_RIGHT, 80);
	m_scoreList.InsertColumn(0, _T("사용자 ID"), LVCFMT_RIGHT, 80);

	

	try {
		CString br[30][3];
		CString cr[30][3];
		m_pRs->Close();
		m_pRs = new CRecordset(&m_db);


		//BOOL bOpen = m_pRs->Open(CRecordset::snapshot, "select member_id from user where username ='" + m_strID_search_show + "'");
		BOOL bOpen = m_pRs->Open(CRecordset::snapshot, "select user.username,T.user_score,T.user_date from user join (select user_id, user_score, user_date from score where user_id = (select member_id from user where username = '" + m_strID_search_show + "') ) as T on user.member_id = T.user_id;");

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
						br[iRow - 1][iCol] = sItem;
						UpdateData(FALSE);

					}
					iRow++;
				}
			}
			/*
			if (!bIsEOF)
			{

				m_pRs->Close();
				m_pRs = new CRecordset(&m_db);
				AfxMessageBox("select user.username,T.user_score,T.user_date from user join (select user_id, user_score, user_date from score where user_id = (select member_id from user where username = '" + m_strID_search_show + "') ) as T on user.member_id = T.user_id;");
				m_pRs->Open(CRecordset::snapshot, "select user_id, user_score, user_date from score where user_id = '" + br[0][0] + "';");
				iRow = 1;
				BOOL bIsEOF = m_pRs->IsEOF();
				DWORD dwSize = m_pRs->GetRowsetSize();

				for (m_pRs->MoveFirst(); !m_pRs->IsEOF(); m_pRs->MoveNext())
				{
					int iFieldCnt = m_pRs->GetODBCFieldCount();
					for (int iCol = 0; iCol < iFieldCnt; iCol++)
					{
						CString sItem;
						m_pRs->SetAbsolutePosition(iRow);
						m_pRs->GetFieldValue(iCol, sItem);
						cr[iRow - 1][iCol] = sItem;
						UpdateData(FALSE);

					}
					iRow++;
				}
			}
			*/

			if (!bIsEOF)
			{
				m_pRs->Close();
				m_pRs = new CRecordset(&m_db);
			//	AfxMessageBox("select * from score where user_id = '" + br[0][0] + "'");
			//	AfxMessageBox(br[0][0]);
		
				BOOL bOpen = m_pRs->Open(CRecordset::snapshot, "select user.username,T.user_score,T.user_date from user join (select user_id, user_score, user_date from score where user_id = (select member_id from user where username = '" + m_strID_search_show + "') ) as T on user.member_id = T.user_id;");
				iRow = 1;
				BOOL bIsEOF = m_pRs->IsEOF();
				DWORD dwSize = m_pRs->GetRowsetSize();

				for (m_pRs->MoveFirst(); !m_pRs->IsEOF(); m_pRs->MoveNext())
				{
					m_scoreList.InsertItem(iRow - 1, br[iRow - 1][0]);
					int iFieldCnt = m_pRs->GetODBCFieldCount();
					for (int iCol = 0; iCol < iFieldCnt; iCol++)
					{
						m_scoreList.SetItem(iRow - 1, iCol, LVIF_TEXT, br[iRow - 1][iCol], 0, 0, 0, NULL);


					}

					iRow++;
				}
			}


		}

	}

		catch (CException * e)
		{

			e->ReportError();
		}
		m_pRs->Close();







	










	return TRUE;  // return TRUE unless you set the focus to a control
				  // 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}
