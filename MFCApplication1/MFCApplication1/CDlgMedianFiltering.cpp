// CDlgMedianFiltering.cpp: 实现文件
//

#include "pch.h"
#include "MFCApplication1.h"
#include "CDlgMedianFiltering.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

// CDlgMedianFiltering 对话框

IMPLEMENT_DYNAMIC(CDlgMedianFiltering, CDialogEx)

CDlgMedianFiltering::CDlgMedianFiltering(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_MedianFiltering, pParent)
{
	m_iFilterType = -1;
	m_iFilterH = 0;
	m_iFilterMX = 0;
	m_iFilterMY = 0;
	m_iFilterW = 0;
}

CDlgMedianFiltering::~CDlgMedianFiltering()
{
}

void CDlgMedianFiltering::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Radio(pDX, IDC_RAD1, m_iFilterType);
	DDX_Text(pDX, IDC_EDIT_FH, m_iFilterH);
	DDV_MinMaxInt(pDX, m_iFilterH, 1, 8);
	DDX_Text(pDX, IDC_EDIT_FMX, m_iFilterMX);
	DDX_Text(pDX, IDC_EDIT_FMY, m_iFilterMY);
	DDX_Text(pDX, IDC_EDIT_FW, m_iFilterW);
	DDV_MinMaxInt(pDX, m_iFilterW, 1, 8);
}


BEGIN_MESSAGE_MAP(CDlgMedianFiltering, CDialogEx)
	ON_BN_CLICKED(IDC_RAD1, OnRad1)
	ON_BN_CLICKED(IDC_RAD2, OnRad2)
	ON_BN_CLICKED(IDC_RAD3, OnRad3)
	ON_BN_CLICKED(IDC_RAD4, OnRad4)
END_MESSAGE_MAP()


// CDlgMedianFiltering 消息处理程序
void CDlgMedianFiltering::OnRad1()
{
	// 3×1模板
	m_iFilterType = 0;
	m_iFilterH = 3;
	m_iFilterW = 1;
	m_iFilterMX = 0;
	m_iFilterMY = 1;

	// 设置文本框不可用
	(CEdit*)GetDlgItem(IDC_EDIT_FH)->EnableWindow(FALSE);
	(CEdit*)GetDlgItem(IDC_EDIT_FW)->EnableWindow(FALSE);
	(CEdit*)GetDlgItem(IDC_EDIT_FMX)->EnableWindow(FALSE);
	(CEdit*)GetDlgItem(IDC_EDIT_FMY)->EnableWindow(FALSE);

	// 更新
	UpdateData(FALSE);
}

void CDlgMedianFiltering::OnRad2()
{
	// 1×3模板
	m_iFilterType = 1;
	m_iFilterH = 1;
	m_iFilterW = 3;
	m_iFilterMX = 1;
	m_iFilterMY = 0;

	// 设置文本框不可用
	(CEdit*)GetDlgItem(IDC_EDIT_FH)->EnableWindow(FALSE);
	(CEdit*)GetDlgItem(IDC_EDIT_FW)->EnableWindow(FALSE);
	(CEdit*)GetDlgItem(IDC_EDIT_FMX)->EnableWindow(FALSE);
	(CEdit*)GetDlgItem(IDC_EDIT_FMY)->EnableWindow(FALSE);

	// 更新
	UpdateData(FALSE);
}

void CDlgMedianFiltering::OnRad3()
{
	// 3×3模板
	m_iFilterType = 2;
	m_iFilterH = 3;
	m_iFilterW = 3;
	m_iFilterMX = 1;
	m_iFilterMY = 1;

	// 设置文本框不可用
	(CEdit*)GetDlgItem(IDC_EDIT_FH)->EnableWindow(FALSE);
	(CEdit*)GetDlgItem(IDC_EDIT_FW)->EnableWindow(FALSE);
	(CEdit*)GetDlgItem(IDC_EDIT_FMX)->EnableWindow(FALSE);
	(CEdit*)GetDlgItem(IDC_EDIT_FMY)->EnableWindow(FALSE);

	// 更新
	UpdateData(FALSE);
}

void CDlgMedianFiltering::OnRad4()
{
	// 自定义模板
	(CEdit*)GetDlgItem(IDC_EDIT_FH)->EnableWindow(TRUE);
	(CEdit*)GetDlgItem(IDC_EDIT_FW)->EnableWindow(TRUE);
	(CEdit*)GetDlgItem(IDC_EDIT_FMX)->EnableWindow(TRUE);
	(CEdit*)GetDlgItem(IDC_EDIT_FMY)->EnableWindow(TRUE);
}

void CDlgMedianFiltering::OnOK()
{
	// 获取用户设置（更新）
	UpdateData(TRUE);

	// 判断设置是否有效
	if ((m_iFilterMX < 0) || (m_iFilterMX > m_iFilterW - 1) ||
		(m_iFilterMY < 0) || (m_iFilterMY > m_iFilterH - 1))
	{
		// 提示用户参数设置错误
		MessageBox(L"参数设置错误！", L"系统提示", MB_ICONINFORMATION | MB_OK);

		// 返回
		return;
	}

	// 退出
	CDialog::OnOK();
}
