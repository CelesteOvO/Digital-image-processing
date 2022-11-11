#pragma once


// CDlgLinerPara 对话框

class CDlgLinerPara : public CDialogEx
{
	DECLARE_DYNAMIC(CDlgLinerPara)

public:
	CDlgLinerPara(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~CDlgLinerPara();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_LinearChange };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	float m_fA;
	float m_fB;
public:

	// 标识是否已经绘制橡皮筋线
	BOOL	m_bDrawed;

	// 保存鼠标左键单击时的位置
	CPoint	m_p1;

	// 保存鼠标拖动时的位置
	CPoint	m_p2;

	// 当前鼠标拖动状态，TRUE表示正在拖动。
	BOOL	m_bIsDraging;

	// 相应鼠标事件的矩形区域
	CRect	m_MouseRect;
protected:
	afx_msg void OnPaint();
	afx_msg void OnKillfocusEditA();
	afx_msg void OnKillfocusEditB();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	virtual BOOL OnInitDialog();
};
