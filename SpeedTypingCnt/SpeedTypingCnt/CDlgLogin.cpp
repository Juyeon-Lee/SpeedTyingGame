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

	//  idText = _T("");
	userID = _T("");
	userPW = _T("");
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
void CDlgLogin::OnClickedButtonAdd() // 등록
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.

	UpdateData(TRUE);

	//database connect
	try {
		BOOL bOpen = m_db.OpenEx(_T("DRIVER={MYSQL ODBC 8.0 Unicode Driver};SERVER=127.0.0.1;PORT=3306;USER=root;PASSWORD=root;DATABASE=typing;OPTION=3;")
			, CDatabase::noOdbcDialog);
		if (bOpen)
			m_pRs = new CRecordset(&m_db);
	}
	catch (CException * e)
	{
		e->ReportError();
	}

	try {
		BOOL bOpen = m_pRs->Open(CRecordset::snapshot, 
			"select member_id from user where username ='" + m_strID + "'");

		if (bOpen)
		{
			BOOL bIsEOF = m_pRs->IsEOF();

			if (!bIsEOF) // 아이디 중복
			{
				AfxMessageBox("아이디가 이미 존재합니다.");
			}
			else
			{
				m_db.BeginTrans();
				try
				{
					UpdateData(TRUE);
					// db에 입력한 아이디와 비밀번호를 저장
					m_db.ExecuteSQL(_T("INSERT INTO user(username,password) VALUES('" + m_strID + "','" + m_strPW + "')"));
					m_db.CommitTrans();
					AfxMessageBox("등록되었습니다.");
				}
				catch (CException * e)
				{
					e->ReportError();
				}
			}
			::SendMessage(this->m_hWnd, WM_CLOSE, NULL, NULL); //윈도우창 닫기
		}
		m_pRs->Close();
	}
	catch (CException * e)
	{
		e->ReportError();
	}
	
	if (m_db.IsOpen())
		m_db.Close();
}

// 로그인 버튼 클릭시
void CDlgLogin::OnBnClickedButtonLogin()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	UpdateData(TRUE);

	//database connect
	try {
		BOOL bOpen = m_db.OpenEx(_T("DRIVER={MYSQL ODBC 8.0 Unicode Driver};SERVER=127.0.0.1;PORT=3306;USER=root;PASSWORD=root;DATABASE=typing;OPTION=3;")
			, CDatabase::noOdbcDialog);
		if (bOpen)
			m_pRs = new CRecordset(&m_db);
	}
	catch (CException * e)
	{
		e->ReportError();
	}

	try {
		BOOL bOpen = m_pRs->Open(CRecordset::snapshot
				, "select member_id from user where username ='" + m_strID + "' AND password ='" + m_strPW + "'");
		if (bOpen)
		{
			BOOL bIsEOF = m_pRs->IsEOF();

			if (bIsEOF) // 일치하는 정보 없음
			{
				AfxMessageBox("아이디가 존재하지 않거나 비밀번호가 틀렸습니다.");
			}
			else // 로그인 성공
			{
				AfxMessageBox("로그인 되셨습니다");
				CString strMainDlgStatus = m_strID + "님이 로그인 중입니다";
				// 메인프레임의 포인터 획득
				CSpeedTypingCntDlg* pMainDlg = (CSpeedTypingCntDlg*)GetParent();

				// 버튼 활성화
				pMainDlg->GetDlgItem(IDC_BUTTON_MATCH)->EnableWindow(TRUE);
				pMainDlg->GetDlgItem(IDC_BUTTON_SOLO)->EnableWindow(TRUE);
				pMainDlg->GetDlgItem(IDC_BUTTON_SCORE)->EnableWindow(TRUE);
				pMainDlg->GetDlgItem(IDC_BUTTON_LOGOUT)->EnableWindow(TRUE);
				pMainDlg->GetDlgItem(IDC_BUTTON_SOLO2)->EnableWindow(TRUE);
				pMainDlg->SetDlgItemText(IDC_STATIC_MAINID, strMainDlgStatus);
				pMainDlg->global_userID = m_strID;

				UpdateData(FALSE);
				// 창 종료
				::SendMessage(this->m_hWnd, WM_CLOSE, NULL, NULL);
			}
		}
		m_pRs->Close();
	}
	catch (CException * e)
	{
		e->ReportError();
	}

	if (m_db.IsOpen())
		m_db.Close();

}