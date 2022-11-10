#pragma once


// CDlgThreshold 对话框

class CDlgThreshold : public CDialogEx
{
	DECLARE_DYNAMIC(CDlgThreshold)

public:
	CDlgThreshold(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~CDlgThreshold();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_Threshold };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	BOOL	m_bIsDraging;
	CRect	m_MouseRect;
	BYTE	m_bThre;
protected:
	afx_msg void OnRad1();
	afx_msg void OnRad2();
	afx_msg void OnRad3();
	afx_msg void OnRad4();
	afx_msg void OnRad5();
	afx_msg void OnKillfocusEDITThre();
	virtual BOOL OnInitDialog();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnPaint();
public:
	int m_Type;
	afx_msg void OnBnClickedPreview3();
	afx_msg void OnBnClickedrecover3();
	afx_msg void OnBnClickedCountthreshold();
};
