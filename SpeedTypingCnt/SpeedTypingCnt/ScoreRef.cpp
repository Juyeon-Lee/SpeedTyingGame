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

// 이 초기화 함수를 통해서 db의값들이 출력된다.
BOOL CScoreRef::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  여기에 추가 초기화 작업을 추가합니다.
	// DB 연결
	try {
		BOOL bOpen = m_db.OpenEx(_T("DRIVER={MYSQL ODBC 8.0 Unicode Driver};SERVER=127.0.0.1;PORT=3306;USER=root;PASSWORD=root;DATABASE=typing;OPTION=3;"), CDatabase::noOdbcDialog);
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
		CString ar[30][3];	// db값을 받기위한 배열 
		// 쿼리문 실행
		BOOL bOpen = m_pRs->Open(CRecordset::snapshot, "select user.username,score.user_score,score.user_date from user join score on( score.user_id = user.member_id) order by id ASC;");

		// 쿼리문이 정상 작동한 경우
		if (bOpen)
		{
			int iRow = 1;	// 쿼리문에서 SELECT된 값의 행을 받는 변수 
			BOOL bIsEOF = m_pRs->IsEOF(); // 데이터베이스의 마지막임을 알려주는 변수
			DWORD dwSize = m_pRs->GetRowsetSize();
			if (!bIsEOF)
			{
				// SELECT된 값의 행을 for문을 통해 돈다
				for (m_pRs->MoveFirst(); !m_pRs->IsEOF(); m_pRs->MoveNext())
				{
					int iFieldCnt = m_pRs->GetODBCFieldCount();	// 열에 대한 정보를 받는 변수
					for (int iCol = 0; iCol < iFieldCnt; iCol++) // SELECT된 값의 열을 for문을 통해 돈다
					{
						CString sItem;						// SELECT 된 값들을 담기위한 변수
						m_pRs->SetAbsolutePosition(iRow);	// 각각의 행과열에 해당되는 변수의 값을 얻는다
						m_pRs->GetFieldValue(iCol, sItem);

						ar[iRow - 1][iCol] = sItem; // 쿼리문 실행한 결과값을 ar배열에 대입
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
					m_scoreList.InsertItem(iRow - 1, ar[iRow - 1][0]);	// 리스트 각 행의 첫번쨰 열은 InsertItem으로 추가
					int iFieldCnt = m_pRs->GetODBCFieldCount();
					for (int iCol = 1; iCol < iFieldCnt; iCol++)
					{
						// 그 이외의 열은 SetItem으로 추가
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

// 점수조회 화면에서 검색버튼 클릭시
void CScoreRef::OnBnClickedButtonSearch()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	Search* dlg = new Search;
	dlg->DoModal(); //search 화면을 띄운다
	delete dlg;
}
