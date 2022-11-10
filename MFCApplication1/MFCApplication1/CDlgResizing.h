#pragma once


// CDlgResizing 对话框

class CDlgResizing : public CDialogEx
{
	DECLARE_DYNAMIC(CDlgResizing)

public:
	CDlgResizing(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~CDlgResizing();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_Resizing };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	float	m_XZoom;
	float	m_YZoom;
};
