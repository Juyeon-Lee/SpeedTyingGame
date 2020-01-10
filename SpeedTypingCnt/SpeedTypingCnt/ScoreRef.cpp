// ScoreRef.cpp: 구현 파일
//

#include "pch.h"
#include "SpeedTypingCnt.h"
#include "ScoreRef.h"
#include "afxdialogex.h"


// CScoreRef 대화 상자

IMPLEMENT_DYNAMIC(CScoreRef, CDialogEx)

CScoreRef::CScoreRef(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG1, pParent)
{

}

CScoreRef::~CScoreRef()
{
}

void CScoreRef::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CScoreRef, CDialogEx)
END_MESSAGE_MAP()


// CScoreRef 메시지 처리기
