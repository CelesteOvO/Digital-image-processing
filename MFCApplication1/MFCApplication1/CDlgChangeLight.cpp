// CDlgChangeLight.cpp: 实现文件
//

#include "pch.h"
#include "MFCApplication1.h"
#include "CDlgChangeLight.h"
#include "afxdialogex.h"


// CDlgChangeLight 对话框

IMPLEMENT_DYNAMIC(CDlgChangeLight, CDialogEx)

CDlgChangeLight::CDlgChangeLight(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_ChangeLight, pParent)
	, Light(0)
{

}

CDlgChangeLight::~CDlgChangeLight()
{
}

void CDlgChangeLight::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDIDC_Light, Light);
	DDV_MinMaxLong(pDX, Light, -255, 255);
}


BEGIN_MESSAGE_MAP(CDlgChangeLight, CDialogEx)
	ON_COMMAND(ID_ChangeLight, &CDlgChangeLight::OnChangelight)
END_MESSAGE_MAP()


// CDlgChangeLight 消息处理程序


void CDlgChangeLight::OnChangelight()
{
	// TODO: 在此添加命令处理程序代码
}


BOOL CDlgChangeLight::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	UpdateData(false);
	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}
