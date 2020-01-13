// CDlgLogin.cpp: 구현 파일
//

#include "pch.h"
#include "SpeedTypingCnt.h"
#include "CDlgLogin.h"
#include "afxdialogex.h"
#include "SpeedTypingCntDlg.h";
#include "MatchGame.h"




// CDlgLogin 대화 상자

IMPLEMENT_DYNAMIC(CDlgLogin, CDialogEx)

CDlgLogin::CDlgLogin(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_LOGIN, pParent)
	, m_strID(_T(""))
	, m_strPW(_T(""))
{

}

CDlgLogin::~CDlgLogin()
{
}

void CDlgLogin::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_ID, m_strID);
	DDX_Text(pDX, IDC_EDIT_PW, m_strPW);
}


BEGIN_MESSAGE_MAP(CDlgLogin, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON_ADD, &CDlgLogin::OnClickedButtonAdd)
	ON_BN_CLICKED(IDC_BUTTON_LOGIN, &CDlgLogin::OnBnClickedButtonLogin)
END_MESSAGE_MAP()


// CDlgLogin 메시지 처리기


void CDlgLogin::OnClickedButtonAdd()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	try
	{
		BOOL bOpen = m_db.OpenEx(_T("DRIVER={MYSQL ODBC 8.0 Unicode Driver};SERVER=127.0.0.1;PORT=3306;USER=root;PASSWORD=123123;DATABASE=typing;OPTION=3;"), CDatabase::noOdbcDialog);
		if (bOpen)
			m_pRs = new CRecordset(&m_db);
	}
	catch (CException * e)
	{
		e->ReportError();

	}

	m_db.BeginTrans();
	try
	{
		UpdateData(TRUE);
		m_db.ExecuteSQL(_T("INSERT INTO user(username,password) VALUES('"+m_strID+"','"+m_strPW+"')"));


	}
	catch (CException * e)
	{
		e->ReportError();
	}
	m_db.CommitTrans();



	::SendMessage(this->m_hWnd, WM_CLOSE, NULL,NULL);
}


void CDlgLogin::OnBnClickedButtonLogin()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	UpdateData(TRUE);
	CString id_x = m_strID;

	try {
		BOOL bOpen = m_db.OpenEx(_T("DRIVER={MYSQL ODBC 8.0 Unicode Driver};SERVER=127.0.0.1;PORT=3306;USER=root;PASSWORD=123123;DATABASE=typing;OPTION=3;"), CDatabase::noOdbcDialog);
		if (bOpen)
			m_pRs = new CRecordset(&m_db);
	}
	catch (CException * e)
	{
		e->ReportError();
	}

	try {
		CString sData(_T(""));
		CString ar[10][10];
		BOOL bOpen = m_pRs->Open(CRecordset::snapshot, _T("select user.username,score.user_score,score.user_date from user join score on( score.user_id = user.member_id);"));

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

				for (m_pRs->MoveFirst(); !m_pRs->IsEOF(); m_pRs->MoveNext())
				{
					if (ar[iRow - 1][0] == m_strID)
					{
						AfxMessageBox("사용가능한 회원");
						::SendMessage(this->m_hWnd, WM_CLOSE, NULL, NULL);
						CSpeedTypingCntDlg* dlg = new CSpeedTypingCntDlg;
						if (dlg->Create(100))
						{
							dlg->global_userID = m_strID;
							dlg->m_strMainID = m_strID;
							dlg->GetDlgItem(IDC_BUTTON_SOLO)->ShowWindow(SW_SHOWNORMAL);
							UpdateData(FALSE);
						}						
						//MatchGame* dlg2 = new MatchGame;
						//dlg2->m_strID = m_strID;
						break;
					}
					else
					{
						AfxMessageBox("회원등록 필요");
						break;
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

	

		
}
