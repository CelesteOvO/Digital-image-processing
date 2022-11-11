#pragma once


// CDlgWindowTransform 对话框

class CDlgWindowTransform : public CDialogEx
{
	DECLARE_DYNAMIC(CDlgWindowTransform)

public:
	CDlgWindowTransform(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~CDlgWindowTransform();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_WindowTransform };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	int		m_iIsDraging;
	CRect	m_MouseRect;
	BYTE	m_bLow;
	BYTE	m_bUp;
protected:
	afx_msg void OnKillfocusEDITLow();
	afx_msg void OnKillfocusEDITUp();
	virtual void OnOK();
	afx_msg void OnPaint();
	virtual BOOL OnInitDialog();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
public:
	afx_msg void OnBnClickedPreview1();
	afx_msg void OnBnClickedRecover1();
};
