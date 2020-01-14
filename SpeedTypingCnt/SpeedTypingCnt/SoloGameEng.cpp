// SoloGameEng.cpp: 구현 파일
//

#include "pch.h"
#include "SpeedTypingCnt.h"
#include "SoloGameEng.h"
#include "afxdialogex.h"


// SoloGameEng 대화 상자

IMPLEMENT_DYNAMIC(SoloGameEng, CDialogEx)

SoloGameEng::SoloGameEng(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_SOLO21, pParent)
	, m_strTyping1()

{
	//SetWord(1);
	//ViewWord();
	endcnt = 1;
	cnt = 1;


}

SoloGameEng::~SoloGameEng()
{
}

void SoloGameEng::DoDataExchange(CDataExchange * pDX)
{
	CDialogEx::DoDataExchange(pDX);
	//  DDX_Text(pDX, IDC_EDIT_TYPING, m_strTyping);

	//  DDX_Control(pDX, IDC_STATIC1_SOLO, m_txt1);
	
	//  DDX_Control(pDX, IDC_STATIC_STATUS, m_title);
	DDX_Control(pDX, IDC_STATIC1_SOLO1, m_txt1);
	DDX_Control(pDX, IDC_STATIC10_SOLO10, m_txt10);
	DDX_Control(pDX, IDC_EDIT_TYPING1, m_strTyping1);
	DDX_Control(pDX, IDC_STATIC11_SOLO11, m_txt11);
	DDX_Control(pDX, IDC_STATIC12_SOLO12, m_txt12);
	DDX_Control(pDX, IDC_STATIC13_SOLO13, m_txt13);
	DDX_Control(pDX, IDC_STATIC14_SOLO14, m_txt14);
	DDX_Control(pDX, IDC_STATIC15_SOLO15, m_txt15);
	DDX_Control(pDX, IDC_STATIC2_SOLO2, m_txt2);
	DDX_Control(pDX, IDC_STATIC3_SOLO3, m_txt3);
	DDX_Control(pDX, IDC_STATIC4_SOLO4, m_txt4);
	DDX_Control(pDX, IDC_STATIC5_SOLO5, m_txt5);
	DDX_Control(pDX, IDC_STATIC6_SOLO6, m_txt6);
	DDX_Control(pDX, IDC_STATIC7_SOLO7, m_txt7);
	DDX_Control(pDX, IDC_STATIC8_SOLO8, m_txt8);
	DDX_Control(pDX, IDC_STATIC9_SOLO9, m_txt9);
}


BEGIN_MESSAGE_MAP(SoloGameEng, CDialogEx)

	//ON_BN_CLICKED(IDC_BUTTON3, &SoloGameEng::OnBnClickedButton3)
END_MESSAGE_MAP()




BOOL SoloGameEng::PreTranslateMessage(MSG * pMsg)//edit control 에서 enter 로 값 비교
{

	CString strText = _T("");
	m_strTyping1.GetWindowTextA(strText);


	POSITION pos = m_string_list.GetHeadPosition();
	//POSITION remove_pos;
	cnt = 1;


	
	if (pMsg->message == WM_KEYDOWN && pMsg->hwnd == GetDlgItem(IDC_EDIT_TYPING1)->m_hWnd)
	{

		if (pMsg->wParam == VK_RETURN)
		{

			while (pos != NULL && IsGameEnd(endcnt)) {

				if (strText == m_string_list.GetAt(pos)) {
					m_strTyping1.SetWindowTextA("");
					EraseCheck(cnt);
					endcnt++;

					break;
				}
				else {
					m_string_list.GetNext(pos);
					cnt++;
				}

			}
			if (!IsGameEnd(endcnt))
				EraseCheck(cnt);

			return TRUE;
		}
	}

	return CDialogEx::PreTranslateMessage(pMsg);
}

void SoloGameEng::ViewWord()
{
	POSITION pos = m_string_list.GetHeadPosition();

	while (pos != NULL) {

		SetDlgItemText(IDC_STATIC1_SOLO1, m_string_list.GetAt(pos));
		m_string_list.GetNext(pos);
		SetDlgItemText(IDC_STATIC2_SOLO2, m_string_list.GetAt(pos));
		m_string_list.GetNext(pos);
		SetDlgItemText(IDC_STATIC3_SOLO3, m_string_list.GetAt(pos));
		m_string_list.GetNext(pos);
		SetDlgItemText(IDC_STATIC4_SOLO4, m_string_list.GetAt(pos));
		m_string_list.GetNext(pos);
		SetDlgItemText(IDC_STATIC5_SOLO5, m_string_list.GetAt(pos));
		m_string_list.GetNext(pos);
		SetDlgItemText(IDC_STATIC6_SOLO6, m_string_list.GetAt(pos));
		m_string_list.GetNext(pos);
		SetDlgItemText(IDC_STATIC7_SOLO7, m_string_list.GetAt(pos));
		m_string_list.GetNext(pos);
		SetDlgItemText(IDC_STATIC8_SOLO8, m_string_list.GetAt(pos));
		m_string_list.GetNext(pos);
		SetDlgItemText(IDC_STATIC9_SOLO9, m_string_list.GetAt(pos));
		m_string_list.GetNext(pos);
		SetDlgItemText(IDC_STATIC10_SOLO10, m_string_list.GetAt(pos));
		m_string_list.GetNext(pos);
		SetDlgItemText(IDC_STATIC11_SOLO11, m_string_list.GetAt(pos));
		m_string_list.GetNext(pos);
		SetDlgItemText(IDC_STATIC12_SOLO12, m_string_list.GetAt(pos));
		m_string_list.GetNext(pos);
		SetDlgItemText(IDC_STATIC13_SOLO13, m_string_list.GetAt(pos));
		m_string_list.GetNext(pos);
		SetDlgItemText(IDC_STATIC14_SOLO14, m_string_list.GetAt(pos));
		m_string_list.GetNext(pos);
		SetDlgItemText(IDC_STATIC15_SOLO15, m_string_list.GetAt(pos));
		m_string_list.GetNext(pos);
		break;



	}


}
void SoloGameEng::EraseCheck(int wordIndex)
{
	// (GetDlgItem(IDC_BT_EMCSTOP))->ShowWindow(FALSE);

	switch (wordIndex)
	{
	case 1:
		(GetDlgItem(IDC_STATIC1_SOLO1))->ShowWindow(FALSE);
		break;
	case 2:
		(GetDlgItem(IDC_STATIC2_SOLO2))->ShowWindow(FALSE);
		break;
	case 3:
		(GetDlgItem(IDC_STATIC3_SOLO3))->ShowWindow(FALSE);
		break;
	case 4:
		(GetDlgItem(IDC_STATIC4_SOLO4))->ShowWindow(FALSE);
		break;
	case 5:
		(GetDlgItem(IDC_STATIC5_SOLO5))->ShowWindow(FALSE);
		break;
	case 6:
		(GetDlgItem(IDC_STATIC6_SOLO6))->ShowWindow(FALSE);
		break;
	case 7:
		(GetDlgItem(IDC_STATIC7_SOLO7))->ShowWindow(FALSE);
		break;
	case 8:
		(GetDlgItem(IDC_STATIC8_SOLO8))->ShowWindow(FALSE);
		break;
	case 9:
		(GetDlgItem(IDC_STATIC9_SOLO9))->ShowWindow(FALSE);
		break;
	case 10:
		(GetDlgItem(IDC_STATIC10_SOLO10))->ShowWindow(FALSE);
		break;
	case 11:
		(GetDlgItem(IDC_STATIC11_SOLO11))->ShowWindow(FALSE);
		break;
	case 12:
		(GetDlgItem(IDC_STATIC12_SOLO12))->ShowWindow(FALSE);
		break;
	case 13:
		(GetDlgItem(IDC_STATIC13_SOLO13))->ShowWindow(FALSE);
		break;
	case 14:
		(GetDlgItem(IDC_STATIC14_SOLO14))->ShowWindow(FALSE);
		break;
	case 15:
		(GetDlgItem(IDC_STATIC15_SOLO15))->ShowWindow(FALSE);
		break;
	default:
		break;
	}
}
BOOL SoloGameEng::IsGameEnd(int endcnt)
{
	if (endcnt == 1) {
		startTime = clock();
		return TRUE;
	}
	else if (endcnt < 16)
		return TRUE;
	else if (endcnt == 16) {
		endTime = clock();
		result = ((double)(endTime - startTime)) / CLOCKS_PER_SEC;
		CString strResult;
		strResult.Format(_T("%.3f"), result);
		EraseCheck(cnt);

		MessageBox(_T("걸린 시간 :" + strResult + "초"), _T("연습결과"), MB_ICONERROR);
		return FALSE;
	}
	else
		return FALSE;
}



BOOL SoloGameEng::OnInitDialog()
{
	CDialogEx::OnInitDialog();


	//UpdateData(TRUE);
	OnReceiveWord();
	ViewWord();
	return TRUE;  // return TRUE unless you set the focus to a control
				  // 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}

void SoloGameEng::OnReceiveWord()
{
	// TODO: 여기에 구현 코드 추가.
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

	try {
		CString sData(_T(""));


		BOOL bOpen = m_pRs->Open(CRecordset::snapshot, "select context from english order by rand() limit 15;");

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
						//CString sItem;
						CDBVariant sItem;
						CString result;

						m_pRs->SetAbsolutePosition(iRow);
						m_pRs->GetFieldValue(iCol, sItem);

						result = *sItem.m_pstringW;

						/*if (iCol == 0)
							sData = sData + sItem;
							
						else {
							sData = sData + _T(",") + sItem;
							m_string_list.AddTail(sItem);*/
							
						
						
						m_string_list.AddTail(result);


						//}

					}
					//sData +=_T("\n");
					iRow++;
				}

			}

			//AfxMessageBox(sData);
		}

	}
	catch (CException * e)
	{
		e->ReportError();
	}
	m_pRs->Close();
	delete m_pRs;
}
