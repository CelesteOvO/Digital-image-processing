#pragma once


// CDlgCorrosion 对话框

class CDlgCorrosion : public CDialogEx
{
	DECLARE_DYNAMIC(CDlgCorrosion)

public:
	CDlgCorrosion(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~CDlgCorrosion();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_corrosion };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CButton	m_Control9;
	CButton	m_Control8;
	CButton	m_Control7;
	CButton	m_Control6;
	CButton	m_Control5;
	CButton	m_Control4;
	CButton	m_Control3;
	CButton	m_Control2;
	CButton	m_Control1;
	int		m_nMode;
	int		m_nStructure1;
	int		m_nStructure2;
	int		m_nStructure3;
	int		m_nStructure4;
	int		m_nStructure5;
	int		m_nStructure6;
	int		m_nStructure7;
	int		m_nStructure8;
	int		m_nStructure9;
protected:
	afx_msg void OnHori();
	afx_msg void OnVert();
	afx_msg void Oncustom();
};
