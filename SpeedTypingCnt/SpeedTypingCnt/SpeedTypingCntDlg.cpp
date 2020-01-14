
// SpeedTypingCntDlg.cpp: 구현 파일
//

#include "pch.h"
#include "framework.h"
#include "SpeedTypingCnt.h"
#include "SpeedTypingCntDlg.h"
#include "afxdialogex.h"
#include "ScoreRef.h"
#include "SoloGame.h"
#include "CDlgLogin.h"
#include "MatchGame.h"
#include "ScoreRef.h"
#include "afxdb.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 응용 프로그램 정보에 사용되는 CAboutDlg 대화 상자입니다.

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

	// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

// 구현입니다.
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CSpeedTypingCntDlg 대화 상자



CSpeedTypingCntDlg::CSpeedTypingCntDlg(CWnd* pParent /*nullptr*/)
	: CDialogEx(IDD_SPEEDTYPINGCNT_DIALOG, pParent)
	, m_strMainID(_T("로그아웃 되어있음"))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	global_userID = _T("");
}

void CSpeedTypingCntDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);

	//DDX_Control(pDX, IDC_STATIC_TEXTEX, m_title);
	//DDX_Control(pDX, IDC_STATIC_TEXTEX, m_title);
	DDX_Control(pDX, IDC_STATIC_TITLE, m_title);
	DDX_Text(pDX, IDC_STATIC_MAINID, m_strMainID);
	DDX_Control(pDX, IDC_BUTTON_MATCH, m_btnMatch);
	DDX_Control(pDX, IDC_BUTTON_SCORE, m_btnScore);
	DDX_Control(pDX, IDC_BUTTON_SOLO, m_btnSolo);
}

BEGIN_MESSAGE_MAP(CSpeedTypingCntDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON_SCORE, &CSpeedTypingCntDlg::OnBnClickedButtonScore)
	//	ON_BN_CLICKED(IDC_BUTTON_SOLO, &CSpeedTypingCntDlg::OnBnClickedButtonSolo)
	ON_BN_CLICKED(IDC_BUTTON_MATCH, &CSpeedTypingCntDlg::OnBnClickedButtonMatch)
	ON_BN_CLICKED(IDC_BUTTON_INIT, &CSpeedTypingCntDlg::OnButtonInit)
	ON_BN_CLICKED(IDC_BUTTON_SOLO, &CSpeedTypingCntDlg::OnClickedButtonSolo)
	ON_WM_CTLCOLOR()
END_MESSAGE_MAP()


// CSpeedTypingCntDlg 메시지 처리기

BOOL CSpeedTypingCntDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 시스템 메뉴에 "정보..." 메뉴 항목을 추가합니다.

	// IDM_ABOUTBOX는 시스템 명령 범위에 있어야 합니다.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// ???�???곸옄???꾩씠肄섏쓣 ?ㅼ젙?⑸땲??  ?묒슜 ?꾨줈洹몃옩??二?李쎌씠 ?�???곸옄媛� ?꾨땺 寃쎌슦?먮뒗
	//  ?꾨젅?꾩썙?ш? ???묒뾽???먮룞?쇰줈 ?섑뻾?⑸땲??
	SetIcon(m_hIcon, TRUE);			// ???꾩씠肄섏쓣 ?ㅼ젙?⑸땲??
	SetIcon(m_hIcon, FALSE);		// ?묒? ?꾩씠肄섏쓣 ?ㅼ젙?⑸땲??

	// TODO: ?ш린??異붽? 珥덇린???묒뾽??異붽??⑸땲??
	/*try
	{
		BOOL bOpen = m_db.OpenEx(_T("DSN=test_odbc;SERVER=127.0.0.1;PORT=3306;UID=root;PWD=root;DATABASE=test_db;"), CDatabase::noOdbcDialog);
		if (bOpen)
			m_pRs = new CRecordset(&m_db);
	}
	catch(CException *e)
	{
		e->ReportError();

	}*/
	
	m_font.CreatePointFont(120, "굴림");
	m_title.SetFont(&m_font, TRUE);
	//m_brush.CreateSolidBrush()
	return TRUE;  // ?ъ빱?ㅻ? 而⑦듃濡ㅼ뿉 ?ㅼ젙?섏? ?딆쑝硫?TRUE瑜?諛섑솚?⑸땲??

	// 이 대화 상자의 아이콘을 설정합니다.  응용 프로그램의 주 창이 대화 상자가 아닐 경우에는
	//  프레임워크가 이 작업을 자동으로 수행합니다.
	SetIcon(m_hIcon, TRUE);			// 큰 아이콘을 설정합니다.
	SetIcon(m_hIcon, FALSE);		// 작은 아이콘을 설정합니다.

	// TODO: 여기에 추가 초기화 작업을 추가합니다.
	/*GetDlgItem(IDC_BUTTON_MATCH)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_BUTTON_SOLO)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_BUTTON_SCORE)->ShowWindow(SW_HIDE);*/
	
	return TRUE;  // 포커스를 컨트롤에 설정하지 않으면 TRUE를 반환합니다.

}

void CSpeedTypingCntDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 대화 상자에 최소화 단추를 추가할 경우 아이콘을 그리려면
//  아래 코드가 필요합니다.  문서/뷰 모델을 사용하는 MFC 애플리케이션의 경우에는
//  프레임워크에서 이 작업을 자동으로 수행합니다.

void CSpeedTypingCntDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 그리기를 위한 디바이스 컨텍스트입니다.

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 클라이언트 사각형에서 아이콘을 가운데에 맞춥니다.
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 아이콘을 그립니다.ㅓㅓ
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// 사용자가 최소화된 창을 끄는 동안에 커서가 표시되도록 시스템에서
//  이 함수를 호출합니다.
HCURSOR CSpeedTypingCntDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CSpeedTypingCntDlg::OnBnClickedButtonScore()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	// 점수 조회 버튼을 누르면 해당 다이얼로그 보이기
	CScoreRef dlg;
	dlg.DoModal();
}


//void CSpeedTypingCntDlg::OnBnClickedButtonSolo()
//{
//	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
//	SoloGame* dlg = new SoloGame;
//	dlg->DoModal();
//}


void CSpeedTypingCntDlg::OnBnClickedButtonMatch()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	MatchGame* dlg = new MatchGame;
	dlg->DoModal();
}


void CSpeedTypingCntDlg::OnButtonInit()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CDlgLogin* dlg = new CDlgLogin;

	dlg->DoModal();

	//if(d)
}
BOOL CSpeedTypingCntDlg::PreTranslateMessage(MSG* pMsg)
{
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.
	if (pMsg->message == WM_KEYDOWN)
	{
		if (pMsg->wParam == VK_RETURN || pMsg->wParam == VK_ESCAPE) // enter or esc 값을 받았을 때 창이 꺼지지 않음
			return TRUE;
	}
	return CDialogEx::PreTranslateMessage(pMsg);
}


void CSpeedTypingCntDlg::OnClickedButtonSolo()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	SoloGame* dlg = new SoloGame;
	dlg->DoModal();

}


HBRUSH CSpeedTypingCntDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialogEx::OnCtlColor(pDC, pWnd, nCtlColor);

	// TODO:  ?ш린??DC???뱀꽦??蹂�寃쏀빀?덈떎.
	UINT nID = pWnd->GetDlgCtrlID();
	switch (nID)
	{
	case IDC_STATIC_TITLE:
		pDC->SetTextColor(RGB(0, 0, 255)); //?뚮???
		//hbr = ::CreateSolidBrush(RGB(255, 0, 0));
		break;
	}

	return hbr;
}

	void CSpeedTypingCntDlg::OnButtonVisible()
	{
		// TODO: 여기에 구현 코드 추가.
		GetDlgItem(IDC_BUTTON_MATCH)->ShowWindow(SW_SHOWNORMAL);
		GetDlgItem(IDC_BUTTON_SOLO)->ShowWindow(SW_SHOWNORMAL);
		GetDlgItem(IDC_BUTTON_SCORE)->ShowWindow(SW_SHOWNORMAL);
	}

