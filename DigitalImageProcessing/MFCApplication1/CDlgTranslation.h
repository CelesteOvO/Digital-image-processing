#pragma once


// CDlgTranslation 对话框

class CDlgTranslation : public CDialogEx
{
	DECLARE_DYNAMIC(CDlgTranslation)

public:
	CDlgTranslation(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~CDlgTranslation();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_Translation };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	long	m_XOffset;
	long	m_YOffset;

};
