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
	endcnt = 1;
	cnt = 1;
}

SoloGameEng::~SoloGameEng()
{
}

void SoloGameEng::DoDataExchange(CDataExchange * pDX)
{
	CDialogEx::DoDataExchange(pDX);
	
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


	// 키 이벤트가 발생할 경우 && IDC_EDIT_TYPING에 포커스가 맞춰있을 때
	if (pMsg->message == WM_KEYDOWN && pMsg->hwnd == GetDlgItem(IDC_EDIT_TYPING1)->m_hWnd)
	{
		// 엔터키 이벤트가 발생하면
		if (pMsg->wParam == VK_RETURN) 
		{
			// NULL 부분이 나올 때 까지 && ISGAMEEND가 TRUE일 때
			while (pos != NULL && IsGameEnd(endcnt)) {

				if (strText == m_string_list.GetAt(pos)) {	// STRTEXT와 리스트 안의 내용 
					m_strTyping1.SetWindowTextA("");		// 단어 바꿔주기
					EraseCheck(cnt);						// 인덱스를 보내서 단어 화면에서 삭제
					endcnt++;								// ENDCNT가 16가 넘으면(처음을 1로 설정) ISGAMEEND에서 FALSE가 보내짐

					break;
				}
				else {										// 리스트 안의 단어와 내용이 틀리다면
					m_string_list.GetNext(pos);				// 리스트 위치 다음위치로 바꾸기
					cnt++;									// ERASECHECK 인덱스 값 올리기
				}

			}
			if (!IsGameEnd(endcnt))
				EraseCheck(cnt);

			return TRUE;
		}
	}

	return CDialogEx::PreTranslateMessage(pMsg);
}

// 화면에 단어를 뿌려주는 함수
void SoloGameEng::ViewWord()
{
	POSITION pos = m_string_list.GetHeadPosition();		// 리스트 헤드 위치

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

// 인덱스 값에 맞는 STATIC TEXT 를 찾아서 화면에서 보이지 않게 하는 함수
void SoloGameEng::EraseCheck(int wordIndex)
{
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

// 게임이 끝나는 지 확인하는 함수
BOOL SoloGameEng::IsGameEnd(int endcnt)
{
	if (endcnt == 1) {												// ENTER KEY가 들어오는 첫 번 째 순간부터 타이머 작동
		startTime = clock();
		return TRUE;
	}
	else if (endcnt < 16)
		return TRUE;
	else if (endcnt == 16) {										// ENTER KEY가 들어오는 마지막 순간에 타이머 멈춤
		endTime = clock();
		result = ((double)(endTime - startTime)) / CLOCKS_PER_SEC;	// END TIME과 START TIME 값을 비교해 걸린 시간 측정
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

	OnReceiveWord();
	ViewWord();
	return TRUE;  // return TRUE unless you set the focus to a control
				  // 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}

// 데이터 베이스에서 단어를 받아서 리스트에 추가해주는 함수
void SoloGameEng::OnReceiveWord()
{
	// TODO: 여기에 구현 코드 추가.
	try
	{
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
						CDBVariant sItem;
						CString result;

						m_pRs->SetAbsolutePosition(iRow);
						m_pRs->GetFieldValue(iCol, sItem);

						result = *sItem.m_pstringW;

						m_string_list.AddTail(result);						

					}	
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
