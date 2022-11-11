#pragma once


// CDlgFilter 对话框

class CDlgFilter : public CDialogEx
{
	DECLARE_DYNAMIC(CDlgFilter)

public:
	CDlgFilter(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~CDlgFilter();
	void UpdateEdit();
// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_Filter };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	FLOAT   m_Array[9];
	int		m_OperatorType;
	/*int		m_EdgeOperatorType;*/
	int     m_EdgeDirectionType;
	float   m_Coefficient;
	float   m_Constant;

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
	afx_msg void OnRad10();
	afx_msg void OnRad11();
public:
	afx_msg void OnBnClickedSaveoperator();
	afx_msg void OnBnClickedApplyoperator();
	afx_msg void OnBnClickedPreview();
	afx_msg void OnBnClickedRecover();
};
