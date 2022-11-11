// CDlgTranslation.cpp: 实现文件
//

#include "pch.h"
#include "MFCApplication1.h"
#include "CDlgTranslation.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

// CDlgTranslation 对话框

IMPLEMENT_DYNAMIC(CDlgTranslation, CDialogEx)

CDlgTranslation::CDlgTranslation(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_Translation, pParent)
{
	m_XOffset = 0;
	m_YOffset = 0;
}

CDlgTranslation::~CDlgTranslation()
{
}

void CDlgTranslation::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_XOffset, m_XOffset);
	DDX_Text(pDX, IDC_EDIT_YOffset, m_YOffset);
}


BEGIN_MESSAGE_MAP(CDlgTranslation, CDialogEx)
END_MESSAGE_MAP()


// CDlgTranslation 消息处理程序
