#pragma once


// CDlgVChangeReal 对话框

class CDlgVChangeReal : public CDialogEx
{
	DECLARE_DYNAMIC(CDlgVChangeReal)

public:
	CDlgVChangeReal(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~CDlgVChangeReal();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_Vchange };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	// 当前鼠标拖动状态，0表示未拖动，1表示正在拖动第一点，2表示正在拖动第二点。
	int		m_iIsDraging;

	// 相应鼠标事件的矩形区域
	CRect	m_MouseRect;

	// 标识是否已经绘制橡皮筋线
	BOOL	m_bDrawed;

	// 保存鼠标左键单击时的位置
	CPoint	m_p1;

	// 保存鼠标拖动时的位置
	CPoint	m_p2;

	BYTE	m_bX1;
	BYTE	m_bY1;

protected:
	virtual BOOL OnInitDialog();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnPaint();
};
