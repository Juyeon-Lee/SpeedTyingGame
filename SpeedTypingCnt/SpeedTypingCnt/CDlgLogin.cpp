// CDlgLogin.cpp: 구현 파일
//

#include "pch.h"
#include "SpeedTypingCnt.h"
#include "CDlgLogin.h"
#include "afxdialogex.h"
#include "SpeedTypingCntDlg.h";



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
END_MESSAGE_MAP()


// CDlgLogin 메시지 처리기


void CDlgLogin::OnClickedButtonAdd()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	m_db.BeginTrans();
	try
	{
		//m_db.ExecuteSQL(_T("INSERT INTO USER_INFO(USER_ID,USER_PW) VALUES('CAT',1234)"));
		
	}
	catch (CException * e)
	{
		e->ReportError();
	}
	m_db.CommitTrans();
}
