// CDlgImgInfo.cpp: 实现文件
//

#include "pch.h"
#include "MFCApplication1.h"
#include "CDlgImgInfo.h"
#include "afxdialogex.h"


// CDlgImgInfo 对话框

IMPLEMENT_DYNAMIC(CDlgImgInfo, CDialogEx)

CDlgImgInfo::CDlgImgInfo(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DlgImgInfo, pParent)
	, m_Height(0)
	, m_Width(0)
	, m_bitCount(0)
{

}

CDlgImgInfo::~CDlgImgInfo()
{
}

void CDlgImgInfo::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, ID_EDIT_Height, m_Height);
	DDX_Text(pDX, IDC_EDIT_Width, m_Width);
	DDX_Text(pDX, IDC_EDIT_Bit, m_bitCount);
}


BEGIN_MESSAGE_MAP(CDlgImgInfo, CDialogEx)
END_MESSAGE_MAP()


// CDlgImgInfo 消息处理程序


BOOL CDlgImgInfo::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	UpdateData(false);
	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}
