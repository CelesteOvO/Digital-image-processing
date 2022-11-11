#if !defined(AFX_DLGPOINTSTRE_H__45B95585_372F_4C49_8928_99D343D2DE00__INCLUDED_)
#define AFX_DLGPOINTSTRE_H__45B95585_372F_4C49_8928_99D343D2DE00__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif


// CDlgImgInverse 对话框

class CDlgImgInverse : public CDialogEx
{
	DECLARE_DYNAMIC(CDlgImgInverse)

public:
	CDlgImgInverse(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~CDlgImgInverse();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_Inverse };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	int		m_iIsDraging;

	// 相应鼠标事件的矩形区域
	CRect	m_MouseRect;

	// 标识是否已经绘制橡皮筋线
	BOOL	m_bDrawed;

	// 保存鼠标左键单击时的位置
	CPoint	m_p1;

	// 保存鼠标拖动时的位置
	CPoint	m_p2;

protected:
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
};

#endif
