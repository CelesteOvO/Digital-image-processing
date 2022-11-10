#pragma once


// CDlgRotating 对话框

class CDlgRotating : public CDialogEx
{
	DECLARE_DYNAMIC(CDlgRotating)

public:
	CDlgRotating(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~CDlgRotating();
	int		m_iRotateAngle;

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_Rotating };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
};
