#pragma once


// CDlgAreaCount 对话框

class CDlgAreaCount : public CDialogEx
{
	DECLARE_DYNAMIC(CDlgAreaCount)

public:
	CDlgAreaCount(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~CDlgAreaCount();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_AreaCount };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	int		m_ForegroundType;
	int     m_NumberOfConnected;
	int		m_Morphology;
	int		m_NumberOfMorphology;
	int		m_count;
	double	m_maxArea;
	double	m_maxPerimeter;
	double	m_maxRoundness;
	double	m_maxLenratio;
protected:
	afx_msg void OnRad1();
	afx_msg void OnRad2();
	afx_msg void OnRad3();
	afx_msg void OnRad4();
	afx_msg void OnRad5();
	afx_msg void OnRad6();
	afx_msg void OnRad7();
	afx_msg void OnRad8();
	afx_msg void OnRad9();
public:
	afx_msg void OnBnClickedFinal();
	afx_msg void OnBnClickedDeal();
};
