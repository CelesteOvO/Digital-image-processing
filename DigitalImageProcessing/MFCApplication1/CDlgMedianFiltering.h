#if !defined(AFX_DLGMIDFILTER_H__3844F7C0_0F6D_488D_97CE_1DF381742683__INCLUDED_)
#define AFX_DLGMIDFILTER_H__3844F7C0_0F6D_488D_97CE_1DF381742683__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif


// CDlgMedianFiltering 对话框

class CDlgMedianFiltering : public CDialogEx
{
	DECLARE_DYNAMIC(CDlgMedianFiltering)

public:
	CDlgMedianFiltering(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~CDlgMedianFiltering();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MedianFiltering };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	// 滤波器类型
	int		m_iFilterType;

	// 滤波器高度
	int		m_iFilterH;

	// 滤波器宽度
	int		m_iFilterW;

	// 滤波器中心元素X坐标
	int		m_iFilterMX;

	// 滤波器中心元素Y坐标
	int		m_iFilterMY;
protected:
	afx_msg void OnRad1();
	afx_msg void OnRad2();
	afx_msg void OnRad3();
	afx_msg void OnRad4();
	virtual void OnOK();
};

#endif
