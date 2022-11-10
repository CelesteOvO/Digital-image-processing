#pragma once


// CDlgHistogram 对话框

class CDlgHistogram : public CDialogEx
{
	DECLARE_DYNAMIC(CDlgHistogram)

public:
	CDlgHistogram(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~CDlgHistogram();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ShowHistogram };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
protected:	
	afx_msg void OnPaint();
	afx_msg void OnkillfocusEDITLowGray(); 
	afx_msg void OnKillfocusEDITUpGray (); 
	virtual void OnOK();
	afx_msg void OnMouseMove(UINT nFlags, CPoint point); 
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point); 
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
public:
	int m_iIsDraging;
	CRect m_MouseRect;
	LONG m_lHeight;
	LONG m_lWidth;
	char* m_lpDIBBits;
	int m_iLowGray, m_iUpGray;
	LONG m_lCount[256];
	afx_msg void OnEnChangeEdit2();
	afx_msg void OnEnChangeEditLowgray();
	afx_msg void OnEnChangeEditUpgray();
};
