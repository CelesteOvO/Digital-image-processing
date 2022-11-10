// CDlgRotating.cpp: 实现文件
//

#include "pch.h"
#include "MFCApplication1.h"
#include "CDlgRotating.h"
#include "afxdialogex.h"


// CDlgRotating 对话框

IMPLEMENT_DYNAMIC(CDlgRotating, CDialogEx)

CDlgRotating::CDlgRotating(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_Rotating, pParent)
{
	m_iRotateAngle = 0;
}

CDlgRotating::~CDlgRotating()
{
}

void CDlgRotating::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_Rotate, m_iRotateAngle);
	DDV_MinMaxInt(pDX, m_iRotateAngle, 0, 360);
}


BEGIN_MESSAGE_MAP(CDlgRotating, CDialogEx)
END_MESSAGE_MAP()


// CDlgRotating 消息处理程序
