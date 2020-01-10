// ScoreRef.cpp: 구현 파일
//

#include "pch.h"
#include "SpeedTypingCnt.h"
#include "ScoreRef.h"
#include "afxdialogex.h"


// CScoreRef 대화 상자

IMPLEMENT_DYNAMIC(CScoreRef, CDialogEx)

CScoreRef::CScoreRef(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_SCORE, pParent)	
	, m_strID_score(_T("예시 ID"))
{

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
END_MESSAGE_MAP()


// CScoreRef 메시지 처리기


BOOL CScoreRef::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  여기에 추가 초기화 작업을 추가합니다.

	// 점수 리스트에 컬럼 추가
	m_scoreList.InsertColumn(0, _T("최근 점수"), LVCFMT_LEFT, 150);
	m_scoreList.InsertColumn(0, _T("최고 점수"), LVCFMT_LEFT, 150);
	m_scoreList.InsertColumn(0, _T("게임 횟수"), LVCFMT_RIGHT, 80);
	m_scoreList.InsertColumn(0, _T("사용자 ID"), LVCFMT_RIGHT, 80);

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}
