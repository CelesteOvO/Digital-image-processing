#pragma once


// CDlgChangeLight 对话框

class CDlgChangeLight : public CDialogEx
{
	DECLARE_DYNAMIC(CDlgChangeLight)

public:
	CDlgChangeLight(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~CDlgChangeLight();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ChangeLight };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnChangelight();
	long Light;
	virtual BOOL OnInitDialog();
};
