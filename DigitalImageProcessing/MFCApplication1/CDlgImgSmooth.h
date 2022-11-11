#if !defined(AFX_DLGSMOOTH_H__DA1CA811_9B09_49C3_9598_E62B2757D073__INCLUDED_)
#define AFX_DLGSMOOTH_H__DA1CA811_9B09_49C3_9598_E62B2757D073__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif

// CDlgImgSmooth 对话框

class CDlgImgSmooth : public CDialogEx
{
	DECLARE_DYNAMIC(CDlgImgSmooth)

public:
	CDlgImgSmooth(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~CDlgImgSmooth();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_imgSmooth };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	void UpdateEdit();
	FLOAT* m_fpArray;
	// 模板类型
	int		m_intType;
	// 模板高度	
	int		m_iTempH;
	// 模板宽度	
	int		m_iTempW;
	// 模板中心元素X坐标	
	int		m_iTempMX;
	// 模板中心元素Y坐标	
	int		m_iTempMY;
	// 模板系数	
	float	m_fTempC;
protected:
	afx_msg void OnRad1();
	afx_msg void OnRad2();
	afx_msg void OnRad3();
	virtual void OnOK();
	afx_msg void OnKillfocusEditTemph();
	afx_msg void OnKillfocusEditTempw();
};

#endif