﻿// CDlgLogin.cpp: 구현 파일
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


void CDlgLogin::OnClickedButtonAdd()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.

	UpdateData(TRUE);
	try {
		BOOL bOpen = m_db.OpenEx(_T("DRIVER={MYSQL ODBC 8.0 Unicode Driver};SERVER=127.0.0.1;PORT=3306;USER=root;PASSWORD=????????;DATABASE=typing;OPTION=3;"), CDatabase::noOdbcDialog);
		if (bOpen)
			m_pRs = new CRecordset(&m_db);
	}
	catch (CException * e)
	{
		e->ReportError();
	}
	try {
		CString sData(_T(""));
		CString ar[30][10];	// db값을 받기위한 배열 
		BOOL bOpen = m_pRs->Open(CRecordset::snapshot, "select username from user");

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
						ar[iRow - 1][iCol] = sItem;	// 쿼리문 실행한 결과값을 ar배열에 대입
						UpdateData(FALSE);

					}

					iRow++;
				}
			}
			if (!bIsEOF)
			{
				iRow = 1;
				int flag = 1;
				for (m_pRs->MoveFirst(); !m_pRs->IsEOF(); m_pRs->MoveNext())
				{
					if (ar[iRow - 1][0] == m_strID) // 입력한 값과 username이 같다면(즉 db에 동일한 username이 존재한다면)
					{
						UpdateData(FALSE);

						AfxMessageBox("이미 존재합니다.");
						flag = 0;
						::SendMessage(this->m_hWnd, WM_CLOSE, NULL, NULL);

						break;
					}
					iRow++;

				}
				if (flag == 1) // 입력한 값과 다르다면 
				{
					m_db.BeginTrans();
					try
					{
						UpdateData(TRUE);
						AfxMessageBox("등록되었습니다.");
						// db에 입력한 아이디와 비밀번호를 저장
						m_db.ExecuteSQL(_T("INSERT INTO user(username,password) VALUES('" + m_strID + "','" + m_strPW + "')"));
						m_db.CommitTrans();
						::SendMessage(this->m_hWnd, WM_CLOSE, NULL, NULL);

					}
					catch (CException * e)
					{
						e->ReportError();
					}


					// 로그인
					//delete m_pRs;
				}
			}


		}
	}
	catch (CException * e)
	{
		e->ReportError();
	}
	//m_pRs->Close();
	//delete m_pRs;
}

// 로그인 버튼 클릭시
void CDlgLogin::OnBnClickedButtonLogin()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	UpdateData(TRUE);

	try {
		BOOL bOpen = m_db.OpenEx(_T("DRIVER={MYSQL ODBC 8.0 Unicode Driver};SERVER=127.0.0.1;PORT=3306;USER=root;PASSWORD=?????????;DATABASE=typing;OPTION=3;"), CDatabase::noOdbcDialog);
		if (bOpen)
			m_pRs = new CRecordset(&m_db);
	}
	catch (CException * e)
	{
		e->ReportError();
	}

	try {
		CString sData(_T(""));
		CString ar[40][3];	// db값을 받기위한 배열 
		BOOL bOpen = m_pRs->Open(CRecordset::snapshot, "select user.username from user");

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
						ar[iRow - 1][iCol] = sItem; // 쿼리문 실행한 결과값을 ar배열에 대입
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
					// 로그인 성공 시
					if (ar[iRow - 1][0] == m_strID)
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

						// 창 종료
						::SendMessage(this->m_hWnd, WM_CLOSE, NULL, NULL);

						UpdateData(FALSE);
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
	delete m_pRs;
}