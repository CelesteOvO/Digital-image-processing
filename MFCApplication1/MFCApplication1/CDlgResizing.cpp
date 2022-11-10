// CDlgResizing.cpp: 实现文件
//

#include "pch.h"
#include "MFCApplication1.h"
#include "CDlgResizing.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

// CDlgResizing 对话框

IMPLEMENT_DYNAMIC(CDlgResizing, CDialogEx)

CDlgResizing::CDlgResizing(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_Resizing, pParent)
{
	m_XZoom = 0.0f;
	m_YZoom = 0.0f;
}

CDlgResizing::~CDlgResizing()
{
}

void CDlgResizing::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_XZoom, m_XZoom);
	DDV_MinMaxFloat(pDX, m_XZoom, 0.25f, 4.f);
	DDX_Text(pDX, IDC_EDIT_YZoom, m_YZoom);
	DDV_MinMaxFloat(pDX, m_YZoom, 0.25f, 4.f);
}


BEGIN_MESSAGE_MAP(CDlgResizing, CDialogEx)
END_MESSAGE_MAP()


// CDlgResizing 消息处理程序
