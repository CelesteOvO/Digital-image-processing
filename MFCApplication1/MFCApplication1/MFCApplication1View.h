
// MFCApplication1View.h: CMFCApplication1View 类的接口
//

#pragma once


class CMFCApplication1View : public CView
{
protected: // 仅从序列化创建
	CMFCApplication1View() noexcept;
	DECLARE_DYNCREATE(CMFCApplication1View)

// 特性
public:
	CMFCApplication1Doc* GetDocument() const;

// 操作
public:

// 重写
public:
	virtual void OnDraw(CDC* pDC);  // 重写以绘制该视图
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// 实现
public:
	virtual ~CMFCApplication1View();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 生成的消息映射函数
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnDispimginfo();
	afx_msg void OnChangelight();
public:
	unsigned char* pBmpBuf; //读入图像数据的指针
	int bmpWidth;                //图像的宽
	int bmpHeight;              //图像的高
	RGBQUAD* pColorTable;//颜色表指针
	int biBitCount;             //图像类型，每像素位数
	unsigned int OffSet = 0;	//从标题到数据的偏移
	//afx_msg void OnOK();
	afx_msg void OnShowhistogram();
	afx_msg void OnChangepicture();
	afx_msg void On8to8gray();
	afx_msg void OnHalftone();
	afx_msg void OnBinarization();
	afx_msg void On24to8gray();
	afx_msg void On24to8color();
	afx_msg void OnVchange();
	afx_msg void OnPointinvert();
	afx_msg void OnInversevchange();
	afx_msg void OnInverselchange();
	afx_msg void OnLchange();
	afx_msg void OnLinearchange();
	afx_msg void Onimgsmooth();
	afx_msg void OnMedianfiltering();
	afx_msg void OnRandomnoise();
	afx_msg void OnSaltnoise();
	afx_msg void OnLaplacesharp4();
	afx_msg void OnLaplacesharp8();
	afx_msg void OnRobert();
	afx_msg void OnSobel();
	afx_msg void OnGausslaplace();
	afx_msg void OnPrewitt();
	afx_msg void OnKirsch();
	afx_msg void OnExpansion();
	afx_msg void Oncorrosion();
	afx_msg void OnOpen();
	afx_msg void OnClose();
	afx_msg void OnThreshold();
	afx_msg void OnThresholdchange();
	afx_msg void OnWindowtransform();
	afx_msg void OnGraystretch();
	afx_msg void OnEqualization();
	afx_msg void OnTranslation();
	afx_msg void OnHorizontalmirror();
	afx_msg void OnVerticalmirror();
	afx_msg void OnResizing();
	afx_msg void OnTranspose();
	afx_msg void OnRotating();
	afx_msg void OnCanny();
	afx_msg void OnSketch();
	afx_msg void OnCartoon();
	afx_msg void OnAncient();
	afx_msg void OnMosaic();
	afx_msg void Onrelief();
	afx_msg void OnFilter();
	afx_msg void OnAreacount();
	afx_msg void OnUsm();
	afx_msg void OnLog();
	afx_msg void OnGamma();
};

#ifndef _DEBUG  // MFCApplication1View.cpp 中的调试版本
inline CMFCApplication1Doc* CMFCApplication1View::GetDocument() const
   { return reinterpret_cast<CMFCApplication1Doc*>(m_pDocument); }
#endif

