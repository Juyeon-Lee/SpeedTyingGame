
// SpeedTypingCntDlg.cpp: ���� ����
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


// ���� ���α׷� ������ ���Ǵ� CAboutDlg ��ȭ �����Դϴ�.

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

	// ��ȭ ���� �������Դϴ�.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

// �����Դϴ�.
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


// CSpeedTypingCntDlg ��ȭ ����



CSpeedTypingCntDlg::CSpeedTypingCntDlg(CWnd* pParent /*nullptr*/)
	: CDialogEx(IDD_SPEEDTYPINGCNT_DIALOG, pParent)
	, m_strMainID(_T("�α��� ����."))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	global_userID = _T("");
}

//void CSpeedTypingCntDlg::DoDataExchange(CDataExchange* pDX)
//{
//	CDialogEx::DoDataExchange(pDX);
//	DDX_Control(pDX, IDC_BUTTON_MATCH, m_btnMatch);
//	//  DDX_Control(pDX, IDC_BUTTON_SCORE, m_btnScore);
//	//  DDX_Control(pDX, IDC_BUTTON_SOLO, m_btnSolo);
//	//  DDX_Text(pDX, IDC_STATIC_MAINID, m_strMainID);
//	//  DDX_Control(pDX, IDC_BUTTON_INIT, m_btnLogin);
//}

BEGIN_MESSAGE_MAP(CSpeedTypingCntDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()	
	ON_BN_CLICKED(IDC_BUTTON_SOLO, &CSpeedTypingCntDlg::OnBnClickedButtonSolo)
	ON_BN_CLICKED(IDC_BUTTON_MATCH, &CSpeedTypingCntDlg::OnBnClickedButtonMatch)
	ON_BN_CLICKED(IDC_BUTTON_SCORE, &CSpeedTypingCntDlg::OnBnClickedButtonScore)
	ON_BN_CLICKED(IDC_BUTTON_INIT, &CSpeedTypingCntDlg::OnBnClickedButtonInit)
	ON_WM_CTLCOLOR()
END_MESSAGE_MAP()


// CSpeedTypingCntDlg �޽��� ó����

BOOL CSpeedTypingCntDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// �ý��� �޴��� "����..." �޴� �׸��� �߰��մϴ�.

	// IDM_ABOUTBOX�� �ý��� ��� ������ �־�� �մϴ�.
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

	// ???�???�자???�이콘을 ?�정?�니??  ?�용 ?�로그램??�?창이 ?�???�자가 ?�닐 경우?�는
	//  ?�레?�워?��? ???�업???�동?�로 ?�행?�니??
	//SetIcon(m_hIcon, TRUE);			// ???�이콘을 ?�정?�니??
	//SetIcon(m_hIcon, FALSE);		// ?��? ?�이콘을 ?�정?�니??

	// TODO: ?�기??추�? 초기???�업??추�??�니??
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
	
	

	//m_brush.CreateSolidBrush()
	//return TRUE;  // ?�커?��? 컨트롤에 ?�정?��? ?�으�?TRUE�?반환?�니??

	// �� ��ȭ ������ �������� �����մϴ�.  ���� ���α׷��� �� â�� ��ȭ ���ڰ� �ƴ� ��쿡��
	//  �����ӿ�ũ�� �� �۾��� �ڵ����� �����մϴ�.
	SetIcon(m_hIcon, TRUE);			// ū �������� �����մϴ�.
	SetIcon(m_hIcon, FALSE);		// ���� �������� �����մϴ�.

	// TODO: ���⿡ �߰� �ʱ�ȭ �۾��� �߰��մϴ�.	
	GetDlgItem(IDC_BUTTON_MATCH)->EnableWindow(FALSE);
	GetDlgItem(IDC_BUTTON_SOLO)->EnableWindow(FALSE);
	GetDlgItem(IDC_BUTTON_SCORE)->EnableWindow(FALSE);

	m_font.CreatePointFont(130, "����");
	m_title.SetFont(&m_font, TRUE);
		
	return TRUE;  // ��Ŀ���� ��Ʈ�ѿ� �������� ������ TRUE�� ��ȯ�մϴ�.

}

void CSpeedTypingCntDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
		delete dlgAbout;
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// ��ȭ ���ڿ� �ּ�ȭ ���߸� �߰��� ��� �������� �׸�����
//  �Ʒ� �ڵ尡 �ʿ��մϴ�.  ����/�� ���� ����ϴ� MFC ���ø����̼��� ��쿡��
//  �����ӿ�ũ���� �� �۾��� �ڵ����� �����մϴ�.

void CSpeedTypingCntDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // �׸��⸦ ���� ����̽� ���ؽ�Ʈ�Դϴ�.

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Ŭ���̾�Ʈ �簢������ �������� ����� ����ϴ�.
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// �������� �׸��ϴ�.�ä�
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// ����ڰ� �ּ�ȭ�� â�� ���� ���ȿ� Ŀ���� ǥ�õǵ��� �ý��ۿ���
//  �� �Լ��� ȣ���մϴ�.
HCURSOR CSpeedTypingCntDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

BOOL CSpeedTypingCntDlg::PreTranslateMessage(MSG* pMsg)
{
	// TODO: ���⿡ Ư��ȭ�� �ڵ带 �߰� ��/�Ǵ� �⺻ Ŭ������ ȣ���մϴ�.
	if (pMsg->message == WM_KEYDOWN)
	{
		if (pMsg->wParam == VK_RETURN || pMsg->wParam == VK_ESCAPE) // enter or esc ���� �޾��� �� â�� ������ ����
			return TRUE;
	}
	return CDialogEx::PreTranslateMessage(pMsg);
}
void CSpeedTypingCntDlg::OnBnClickedButtonSolo()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	SoloGame* dlg = new SoloGame;
	dlg->DoModal();
	delete dlg;
}
void CSpeedTypingCntDlg::OnBnClickedButtonMatch()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	MatchGame* dlg = new MatchGame;
	dlg->DoModal();
	delete dlg;
}
void CSpeedTypingCntDlg::OnBnClickedButtonScore()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	CScoreRef* dlg = new CScoreRef;
	dlg->DoModal();
	delete dlg;
}
void CSpeedTypingCntDlg::DoDataExchange(CDataExchange* pDX)
{
	// TODO: ���⿡ Ư��ȭ�� �ڵ带 �߰� ��/�Ǵ� �⺻ Ŭ������ ȣ���մϴ�.
	CDialogEx::DoDataExchange(pDX);
	//  DDX_Control(pDX, IDC_BUTTON_INIT, m_btnLogin);
	//  DDX_Control(pDX, IDC_BUTTON_MATCH, m_btnMatch);
	//  DDX_Control(pDX, IDC_BUTTON_SCORE, m_btnScore);
	//  DDX_Control(pDX, IDC_BUTTON_SOLO, m_btnSolo);
	DDX_Text(pDX, IDC_STATIC_MAINID, m_strMainID);
	DDX_Control(pDX, IDC_STATIC_TITLE, m_title);
	
}
void CSpeedTypingCntDlg::OnBnClickedButtonInit()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	CDlgLogin* dlg = new CDlgLogin;
	dlg->DoModal();
}


	void CSpeedTypingCntDlg::OnButtonVisible()
	{
		// TODO: ���⿡ ���� �ڵ� �߰�.
		GetDlgItem(IDC_BUTTON_MATCH)->ShowWindow(SW_SHOWNORMAL);
		GetDlgItem(IDC_BUTTON_SOLO)->ShowWindow(SW_SHOWNORMAL);
		GetDlgItem(IDC_BUTTON_SCORE)->ShowWindow(SW_SHOWNORMAL);
	}



	HBRUSH CSpeedTypingCntDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
	{
		HBRUSH hbr = CDialogEx::OnCtlColor(pDC, pWnd, nCtlColor);

		// TODO:  ?�기??DC???�성??변경합?�다.
		UINT nID = pWnd->GetDlgCtrlID();
		switch (nID)
		{
		case IDC_STATIC_TITLE:
			pDC->SetTextColor(RGB(0, 0, 255)); //?��???
			//hbr = ::CreateSolidBrush(RGB(255, 0, 0));
			break;
		}

		return hbr;
	}
