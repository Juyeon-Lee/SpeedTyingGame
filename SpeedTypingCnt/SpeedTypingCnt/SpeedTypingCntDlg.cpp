
// SpeedTypingCntDlg.cpp: ±¸Çö ÆÄÀÏ
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


// ÀÀ¿ë ÇÁ·Î±×·¥ Á¤º¸¿¡ »ç¿ëµÇ´Â CAboutDlg ´ëÈ­ »óÀÚÀÔ´Ï´Ù.

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

	// ´ëÈ­ »óÀÚ µ¥ÀÌÅÍÀÔ´Ï´Ù.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV Áö¿øÀÔ´Ï´Ù.

// ±¸ÇöÀÔ´Ï´Ù.
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


// CSpeedTypingCntDlg ´ëÈ­ »óÀÚ



CSpeedTypingCntDlg::CSpeedTypingCntDlg(CWnd* pParent /*nullptr*/)
	: CDialogEx(IDD_SPEEDTYPINGCNT_DIALOG, pParent)
	, m_strMainID(_T("·Î±×ÀÎ ¾ÈÇÔ."))
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


// CSpeedTypingCntDlg ¸Þ½ÃÁö Ã³¸®±â

BOOL CSpeedTypingCntDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ½Ã½ºÅÛ ¸Þ´º¿¡ "Á¤º¸..." ¸Þ´º Ç×¸ñÀ» Ãß°¡ÇÕ´Ï´Ù.

	// IDM_ABOUTBOX´Â ½Ã½ºÅÛ ¸í·É ¹üÀ§¿¡ ÀÖ¾î¾ß ÇÕ´Ï´Ù.
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

	// ???€???ìž???„ì´ì½˜ì„ ?¤ì •?©ë‹ˆ??  ?‘ìš© ?„ë¡œê·¸ëž¨??ì£?ì°½ì´ ?€???ìžê°€ ?„ë‹ ê²½ìš°?ëŠ”
	//  ?„ë ˆ?„ì›Œ?¬ê? ???‘ì—…???ë™?¼ë¡œ ?˜í–‰?©ë‹ˆ??
	//SetIcon(m_hIcon, TRUE);			// ???„ì´ì½˜ì„ ?¤ì •?©ë‹ˆ??
	//SetIcon(m_hIcon, FALSE);		// ?‘ì? ?„ì´ì½˜ì„ ?¤ì •?©ë‹ˆ??

	// TODO: ?¬ê¸°??ì¶”ê? ì´ˆê¸°???‘ì—…??ì¶”ê??©ë‹ˆ??
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
	//return TRUE;  // ?¬ì»¤?¤ë? ì»¨íŠ¸ë¡¤ì— ?¤ì •?˜ì? ?Šìœ¼ë©?TRUEë¥?ë°˜í™˜?©ë‹ˆ??

	// ÀÌ ´ëÈ­ »óÀÚÀÇ ¾ÆÀÌÄÜÀ» ¼³Á¤ÇÕ´Ï´Ù.  ÀÀ¿ë ÇÁ·Î±×·¥ÀÇ ÁÖ Ã¢ÀÌ ´ëÈ­ »óÀÚ°¡ ¾Æ´Ò °æ¿ì¿¡´Â
	//  ÇÁ·¹ÀÓ¿öÅ©°¡ ÀÌ ÀÛ¾÷À» ÀÚµ¿À¸·Î ¼öÇàÇÕ´Ï´Ù.
	SetIcon(m_hIcon, TRUE);			// Å« ¾ÆÀÌÄÜÀ» ¼³Á¤ÇÕ´Ï´Ù.
	SetIcon(m_hIcon, FALSE);		// ÀÛÀº ¾ÆÀÌÄÜÀ» ¼³Á¤ÇÕ´Ï´Ù.

	// TODO: ¿©±â¿¡ Ãß°¡ ÃÊ±âÈ­ ÀÛ¾÷À» Ãß°¡ÇÕ´Ï´Ù.	
	GetDlgItem(IDC_BUTTON_MATCH)->EnableWindow(FALSE);
	GetDlgItem(IDC_BUTTON_SOLO)->EnableWindow(FALSE);
	GetDlgItem(IDC_BUTTON_SCORE)->EnableWindow(FALSE);

	m_font.CreatePointFont(130, "±¼¸²");
	m_title.SetFont(&m_font, TRUE);
		
	return TRUE;  // Æ÷Ä¿½º¸¦ ÄÁÆ®·Ñ¿¡ ¼³Á¤ÇÏÁö ¾ÊÀ¸¸é TRUE¸¦ ¹ÝÈ¯ÇÕ´Ï´Ù.

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

// ´ëÈ­ »óÀÚ¿¡ ÃÖ¼ÒÈ­ ´ÜÃß¸¦ Ãß°¡ÇÒ °æ¿ì ¾ÆÀÌÄÜÀ» ±×¸®·Á¸é
//  ¾Æ·¡ ÄÚµå°¡ ÇÊ¿äÇÕ´Ï´Ù.  ¹®¼­/ºä ¸ðµ¨À» »ç¿ëÇÏ´Â MFC ¾ÖÇÃ¸®ÄÉÀÌ¼ÇÀÇ °æ¿ì¿¡´Â
//  ÇÁ·¹ÀÓ¿öÅ©¿¡¼­ ÀÌ ÀÛ¾÷À» ÀÚµ¿À¸·Î ¼öÇàÇÕ´Ï´Ù.

void CSpeedTypingCntDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ±×¸®±â¸¦ À§ÇÑ µð¹ÙÀÌ½º ÄÁÅØ½ºÆ®ÀÔ´Ï´Ù.

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Å¬¶óÀÌ¾ðÆ® »ç°¢Çü¿¡¼­ ¾ÆÀÌÄÜÀ» °¡¿îµ¥¿¡ ¸ÂÃä´Ï´Ù.
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ¾ÆÀÌÄÜÀ» ±×¸³´Ï´Ù.¤Ã¤Ã
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// »ç¿ëÀÚ°¡ ÃÖ¼ÒÈ­µÈ Ã¢À» ²ô´Â µ¿¾È¿¡ Ä¿¼­°¡ Ç¥½ÃµÇµµ·Ï ½Ã½ºÅÛ¿¡¼­
//  ÀÌ ÇÔ¼ö¸¦ È£ÃâÇÕ´Ï´Ù.
HCURSOR CSpeedTypingCntDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

BOOL CSpeedTypingCntDlg::PreTranslateMessage(MSG* pMsg)
{
	// TODO: ¿©±â¿¡ Æ¯¼öÈ­µÈ ÄÚµå¸¦ Ãß°¡ ¹×/¶Ç´Â ±âº» Å¬·¡½º¸¦ È£ÃâÇÕ´Ï´Ù.
	if (pMsg->message == WM_KEYDOWN)
	{
		if (pMsg->wParam == VK_RETURN || pMsg->wParam == VK_ESCAPE) // enter or esc °ªÀ» ¹Þ¾ÒÀ» ¶§ Ã¢ÀÌ ²¨ÁöÁö ¾ÊÀ½
			return TRUE;
	}
	return CDialogEx::PreTranslateMessage(pMsg);
}
void CSpeedTypingCntDlg::OnBnClickedButtonSolo()
{
	// TODO: ¿©±â¿¡ ÄÁÆ®·Ñ ¾Ë¸² Ã³¸®±â ÄÚµå¸¦ Ãß°¡ÇÕ´Ï´Ù.
	SoloGame* dlg = new SoloGame;
	dlg->DoModal();
	delete dlg;
}
void CSpeedTypingCntDlg::OnBnClickedButtonMatch()
{
	// TODO: ¿©±â¿¡ ÄÁÆ®·Ñ ¾Ë¸² Ã³¸®±â ÄÚµå¸¦ Ãß°¡ÇÕ´Ï´Ù.
	MatchGame* dlg = new MatchGame;
	dlg->DoModal();
	delete dlg;
}
void CSpeedTypingCntDlg::OnBnClickedButtonScore()
{
	// TODO: ¿©±â¿¡ ÄÁÆ®·Ñ ¾Ë¸² Ã³¸®±â ÄÚµå¸¦ Ãß°¡ÇÕ´Ï´Ù.
	CScoreRef* dlg = new CScoreRef;
	dlg->DoModal();
	delete dlg;
}
void CSpeedTypingCntDlg::DoDataExchange(CDataExchange* pDX)
{
	// TODO: ¿©±â¿¡ Æ¯¼öÈ­µÈ ÄÚµå¸¦ Ãß°¡ ¹×/¶Ç´Â ±âº» Å¬·¡½º¸¦ È£ÃâÇÕ´Ï´Ù.
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
	// TODO: ¿©±â¿¡ ÄÁÆ®·Ñ ¾Ë¸² Ã³¸®±â ÄÚµå¸¦ Ãß°¡ÇÕ´Ï´Ù.
	CDlgLogin* dlg = new CDlgLogin;
	dlg->DoModal();
}


	void CSpeedTypingCntDlg::OnButtonVisible()
	{
		// TODO: ¿©±â¿¡ ±¸Çö ÄÚµå Ãß°¡.
		GetDlgItem(IDC_BUTTON_MATCH)->ShowWindow(SW_SHOWNORMAL);
		GetDlgItem(IDC_BUTTON_SOLO)->ShowWindow(SW_SHOWNORMAL);
		GetDlgItem(IDC_BUTTON_SCORE)->ShowWindow(SW_SHOWNORMAL);
	}



	HBRUSH CSpeedTypingCntDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
	{
		HBRUSH hbr = CDialogEx::OnCtlColor(pDC, pWnd, nCtlColor);

		// TODO:  ?¬ê¸°??DC???¹ì„±??ë³€ê²½í•©?ˆë‹¤.
		UINT nID = pWnd->GetDlgCtrlID();
		switch (nID)
		{
		case IDC_STATIC_TITLE:
			pDC->SetTextColor(RGB(0, 0, 255)); //?Œë???
			//hbr = ::CreateSolidBrush(RGB(255, 0, 0));
			break;
		}

		return hbr;
	}
