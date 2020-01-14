// ScoreRef.cpp: 구현 파일
//

#include "pch.h"
#include "SpeedTypingCnt.h"
#include "ScoreRef.h"
#include "afxdialogex.h"
#include "Search.h"

//ODBC API를 사용하기 위한 라이브러리 추가
#pragma comment(lib,"odbc32.lib")

// CScoreRef 대화 상자

IMPLEMENT_DYNAMIC(CScoreRef, CDialogEx)

CScoreRef::CScoreRef(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_SCORE, pParent)
	, m_strID_score(_T("예시 ID"))
{


	m_searchID_score = _T("null");
}

CScoreRef::~CScoreRef()
{
}

void CScoreRef::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST_SCORE, m_scoreList);
	DDX_Text(pDX, IDC_STATIC_ID_SCORE, m_strID_score);
}


BEGIN_MESSAGE_MAP(CScoreRef, CDialogEx)



	ON_BN_CLICKED(IDC_BUTTON_SEARCH, &CScoreRef::OnBnClickedButtonSearch)
END_MESSAGE_MAP()


// CScoreRef 메시지 처리기


BOOL CScoreRef::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  여기에 추가 초기화 작업을 추가합니다.
	try {
		BOOL bOpen = m_db.OpenEx(_T("DRIVER={MYSQL ODBC 8.0 Unicode Driver};SERVER=127.0.0.1;PORT=3306;USER=root;PASSWORD=123123;DATABASE=typing;OPTION=3;"), CDatabase::noOdbcDialog);
		if (bOpen)
			m_pRs = new CRecordset(&m_db);
	}
	catch (CException * e)
	{
		e->ReportError();
	}



	// 점수 리스트에 컬럼 추가

	m_scoreList.InsertColumn(0, _T("입력일자"), LVCFMT_LEFT, 150);
	m_scoreList.InsertColumn(0, _T("점수"), LVCFMT_RIGHT, 80);
	m_scoreList.InsertColumn(0, _T("사용자 ID"), LVCFMT_RIGHT, 80);




	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.

	
		try {
			CString ar[30][3];
			BOOL bOpen = m_pRs->Open(CRecordset::snapshot, "select user.username,score.user_score,score.user_date from user join score on( score.user_id = user.member_id) order by id ASC;");

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
							
								ar[iRow - 1][iCol] = sItem;
							UpdateData(FALSE);
						}

						iRow++;
					}
				}
				if (!bIsEOF)
				{
					iRow = 1;
					BOOL bIsEOF = m_pRs->IsEOF();
					DWORD dwSize = m_pRs->GetRowsetSize();

					for (m_pRs->MoveFirst(); !m_pRs->IsEOF(); m_pRs->MoveNext())
					{
						m_scoreList.InsertItem(iRow - 1, ar[iRow - 1][0]);
						int iFieldCnt = m_pRs->GetODBCFieldCount();
						for (int iCol = 1; iCol < iFieldCnt; iCol++)
						{
							m_scoreList.SetItem(iRow - 1, iCol, LVIF_TEXT, ar[iRow - 1][iCol], 0, 0, 0, NULL);


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


		return TRUE;
	}





void CScoreRef::OnBnClickedButtonSearch()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
		// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.

		Search* dlg = new Search;
		//dlg->m_strID_score = global_userID;
		if (dlg->DoModal() == IDOK) {
			//UpdateData(FALSE);
			//AfxMessageBox("%d",flag);
			try {
				CString br[30][3];
				CString cr[30][3];
				m_pRs->Close();
				m_pRs = new CRecordset(&m_db);


				BOOL bOpen = m_pRs->Open(CRecordset::snapshot, "select member_id from user where username ='" + dlg->m_searchID + "'");

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
					if (!bIsEOF)
					{
						
						m_pRs->Close();
						m_pRs = new CRecordset(&m_db);
						//AfxMessageBox("select user.username,score.user_score,score.user_date from user join score on( '" + br[0][0] + "' = user.member_id)");
						m_pRs->Open(CRecordset::snapshot, "select user.username,score.user_score,score.user_date from user join score on(user.member_id = '" + br[0][0] + "');");
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

					if (!bIsEOF)
					{
						m_pRs->Close();
						m_pRs = new CRecordset(&m_db);
						//AfxMessageBox("select user.username,score.user_score,score.user_date from user join score on( '" + br[0][0] + "' = user.member_id)");
						m_pRs->Open(CRecordset::snapshot, "select user.username,score.user_score,score.user_date from user join score on(user.member_id = '" + br[0][0] + "');");
						iRow = 1;
						BOOL bIsEOF = m_pRs->IsEOF();
						DWORD dwSize = m_pRs->GetRowsetSize();

						for (m_pRs->MoveFirst(); !m_pRs->IsEOF(); m_pRs->MoveNext())
						{
							m_scoreList.InsertItem(iRow - 1, cr[iRow - 1][0]);
							int iFieldCnt = m_pRs->GetODBCFieldCount();
							for (int iCol = 1; iCol < iFieldCnt; iCol++)
							{
								m_scoreList.SetItem(iRow - 1, iCol, LVIF_TEXT, cr[iRow - 1][iCol], 0, 0, 0, NULL);


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
			delete m_pRs;
			m_searchID_score = _T("null");
		}


		delete dlg;
	
}
