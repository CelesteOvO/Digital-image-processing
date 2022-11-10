
// MFCApplication1View.cpp: CMFCApplication1View 类的实现
//
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS 可以在实现预览、缩略图和搜索筛选器句柄的
// ATL 项目中进行定义，并允许与该项目共享文档代码。
#ifndef SHARED_HANDLERS
#include "MFCApplication1.h"
#endif

#include <iostream>
#include <vector>
#include <cmath>
#include "stdafx.h"
#include "DIBAPI.H"
#include "MFCApplication1Doc.h"
#include "MFCApplication1View.h"
#include "CDlgImgInfo.h"
#include "CDlgChangeLight.h"
#include "CDlgHistogram.h"
#include "CDlgImgInverse.h"
#include "CDlgVChange.h"
#include "CDlgVChangeReal.h"
#include "CDlgInverseLchange.h"
#include "CDlgLChange.h"
#include "CDlgLinerPara.h"
#include "CDlgImgSmooth.h"
#include "CDlgMedianFiltering.h"
#include "CDlgExpansion.h"
#include "CDlgCorrosion.h"
#include "CDlgOpen.h"
#include "CDlgClose.h"
#include "CDlgThreshold.h"
#include "CDlgWindowTransform.h"
#include "CDlgGrayStretch.h"
#include "CDlgTranslation.h"
#include "CDlgResizing.h"
#include "CDlgRotating.h"
#include "CDlgFilter.h"
#include "CDlgAreaCount.h"
#include "resource.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#define WIDTHBYTES(bits)    (((bits) + 31) / 32 * 4)
#define PI 3.1415926535
#define RADIAN(angle) ((angle)*PI/180.0)
#define SWAP(a,b) tempr=(a);(a)=(b);(b)=tempr

// CMFCApplication1View

IMPLEMENT_DYNCREATE(CMFCApplication1View, CView)

BEGIN_MESSAGE_MAP(CMFCApplication1View, CView)
	// 标准打印命令
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
	ON_COMMAND(ID_DispImgInfo, &CMFCApplication1View::OnDispimginfo)
	ON_COMMAND(ID_ChangeLight, &CMFCApplication1View::OnChangelight)
	ON_COMMAND(ID_ShowHistogram, &CMFCApplication1View::OnShowhistogram)
	ON_COMMAND(ID_ChangePicture, &CMFCApplication1View::OnChangepicture)
	ON_COMMAND(ID_8to8GRAY, &CMFCApplication1View::On8to8gray)
	ON_COMMAND(ID_HalfTone, &CMFCApplication1View::OnHalftone)
	ON_COMMAND(ID_Binarization, &CMFCApplication1View::OnBinarization)
	ON_COMMAND(ID_24to8COLOR, &CMFCApplication1View::On24to8color)
	ON_COMMAND(ID_Vchange, &CMFCApplication1View::OnVchange)
	ON_COMMAND(ID_PointInvert, &CMFCApplication1View::OnPointinvert)
	ON_COMMAND(ID_InverseVchange, &CMFCApplication1View::OnInversevchange)
	ON_COMMAND(ID_InverseLchange, &CMFCApplication1View::OnInverselchange)
	ON_COMMAND(ID_Lchange, &CMFCApplication1View::OnLchange)
	ON_COMMAND(ID_LinearChange, &CMFCApplication1View::OnLinearchange)
	ON_COMMAND(ID_imgSmooth, &CMFCApplication1View::Onimgsmooth)
	ON_COMMAND(ID_MedianFiltering, &CMFCApplication1View::OnMedianfiltering)
	ON_COMMAND(ID_RandomNoise, &CMFCApplication1View::OnRandomnoise)
	ON_COMMAND(ID_SaltNoise, &CMFCApplication1View::OnSaltnoise)
	ON_COMMAND(ID_LaplaceSharp4, &CMFCApplication1View::OnLaplacesharp4)
	ON_COMMAND(ID_LaplaceSharp8, &CMFCApplication1View::OnLaplacesharp8)
	ON_COMMAND(ID_Robert, &CMFCApplication1View::OnRobert)
	ON_COMMAND(ID_Sobel, &CMFCApplication1View::OnSobel)
	ON_COMMAND(ID_GaussLaplace, &CMFCApplication1View::OnGausslaplace)
	ON_COMMAND(ID_Prewitt, &CMFCApplication1View::OnPrewitt)
	ON_COMMAND(ID_Kirsch, &CMFCApplication1View::OnKirsch)
	ON_COMMAND(ID_Expansion, &CMFCApplication1View::OnExpansion)
	ON_COMMAND(ID_corrosion, &CMFCApplication1View::Oncorrosion)
	ON_COMMAND(ID_Open, &CMFCApplication1View::OnOpen)
	ON_COMMAND(ID_Close, &CMFCApplication1View::OnClose)
	ON_COMMAND(ID_Threshold, &CMFCApplication1View::OnThreshold)
	ON_COMMAND(ID_ThresholdChange, &CMFCApplication1View::OnThresholdchange)
	ON_COMMAND(ID_WindowTransform, &CMFCApplication1View::OnWindowtransform)
	ON_COMMAND(ID_GrayStretch, &CMFCApplication1View::OnGraystretch)
	ON_COMMAND(ID_Equalization, &CMFCApplication1View::OnEqualization)
	ON_COMMAND(ID_Translation, &CMFCApplication1View::OnTranslation)
	ON_COMMAND(ID_HorizontalMirror, &CMFCApplication1View::OnHorizontalmirror)
	ON_COMMAND(ID_VerticalMirror, &CMFCApplication1View::OnVerticalmirror)
	ON_COMMAND(ID_Resizing, &CMFCApplication1View::OnResizing)
	ON_COMMAND(ID_Transpose, &CMFCApplication1View::OnTranspose)
	ON_COMMAND(ID_Rotating, &CMFCApplication1View::OnRotating)
	ON_COMMAND(ID_Canny, &CMFCApplication1View::OnCanny)
	ON_COMMAND(ID_Sketch, &CMFCApplication1View::OnSketch)
	ON_COMMAND(ID_Cartoon, &CMFCApplication1View::OnCartoon)
	ON_COMMAND(ID_Ancient, &CMFCApplication1View::OnAncient)
	ON_COMMAND(ID_Mosaic, &CMFCApplication1View::OnMosaic)
	ON_COMMAND(ID_relief, &CMFCApplication1View::Onrelief)
	ON_COMMAND(ID_Filter, &CMFCApplication1View::OnFilter)
	ON_COMMAND(ID_AreaCount, &CMFCApplication1View::OnAreacount)
	ON_COMMAND(ID_USM, &CMFCApplication1View::OnUsm)
	ON_COMMAND(ID_Log, &CMFCApplication1View::OnLog)
	ON_COMMAND(ID_Gamma, &CMFCApplication1View::OnGamma)
END_MESSAGE_MAP()

// CMFCApplication1View 构造/析构

CMFCApplication1View::CMFCApplication1View() noexcept
{
	// TODO: 在此处添加构造代码

}

CMFCApplication1View::~CMFCApplication1View()
{
}

BOOL CMFCApplication1View::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: 在此处通过修改
	//  CREATESTRUCT cs 来修改窗口类或样式

	return CView::PreCreateWindow(cs);
}

// CMFCApplication1View 绘图

void CMFCApplication1View::OnDraw(CDC* pDC)
{
	CMFCApplication1Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: 在此处为本机数据添加绘制代码
	HGLOBAL hDIB = pDoc->GetHObject();

	// 判断DIB是否为空
	if (hDIB != NULL)
	{
		LPSTR lpDibSection = (LPSTR) ::GlobalLock((HGLOBAL)hDIB);

		// 获取DIB宽度
		int cxDIB = (int)pDoc->m_dib.GetWidth(lpDibSection);

		// 获取DIB高度
		int cyDIB = (int)pDoc->m_dib.GetHeight(lpDibSection);
		::GlobalUnlock((HGLOBAL)hDIB);
		CRect rcDIB;
		rcDIB.top = rcDIB.left = 0;
		rcDIB.right = cxDIB;
		rcDIB.bottom = cyDIB;
		CRect rcDest = rcDIB;
		// 输出DIB
		pDoc->m_dib.DrawDib(pDC->m_hDC, &rcDest, pDoc->GetHObject(),
			&rcDIB, pDoc->GetDocPal());
	}

}


// CMFCApplication1View 打印

BOOL CMFCApplication1View::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 默认准备
	return DoPreparePrinting(pInfo);
}

void CMFCApplication1View::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加额外的打印前进行的初始化过程
}

void CMFCApplication1View::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加打印后进行的清理过程
}


// CMFCApplication1View 诊断

#ifdef _DEBUG
void CMFCApplication1View::AssertValid() const
{
	CView::AssertValid();
}

void CMFCApplication1View::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CMFCApplication1Doc* CMFCApplication1View::GetDocument() const // 非调试版本是内联的
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMFCApplication1Doc)));
	return (CMFCApplication1Doc*)m_pDocument;
}
#endif //_DEBUG


// CMFCApplication1View 消息处理程序

void CMFCApplication1View::OnDispimginfo()
{
	// TODO: 在此添加命令处理程序代码
	CMFCApplication1Doc* pDoc = GetDocument();// 获取文档	
	////////////////////////////////////////////////////////////////////////////////////////////////	
	long	lSrcLineBytes;		//图象每行的字节数
	long	lSrcWidth;      //图象的宽度和高度
	long	lSrcHeight;
	int     lpSrcBitCount;       //图像的位深
	LPSTR	lpSrcDib;		//指向源图象的指针	
	LPSTR	lpSrcStartBits;	//指向源像素的指针
	lpSrcDib = (LPSTR) ::GlobalLock((HGLOBAL)pDoc->GetHObject());// 锁定DIB
	if (!lpSrcDib) return;
	/*
	if (pDoc->m_dib.GetColorNum(lpSrcDib) != 256)// 判断是否是8-bpp位图
	{
		   AfxMessageBox(L"对不起，不是256色位图！");// 警告
		   ::GlobalUnlock((HGLOBAL) pDoc->GetHObject());// 解除锁定
		   return;									//返回
	 }										//判断是否是8-bpp位图,不是则返回
	 */
	lpSrcStartBits = pDoc->m_dib.GetBits(lpSrcDib);			// 找到DIB图象像素起始位置	
	lSrcWidth = pDoc->m_dib.GetWidth(lpSrcDib);					// 获取图象的宽度		
	lSrcHeight = pDoc->m_dib.GetHeight(lpSrcDib);					// 获取图象的高度	
	lpSrcBitCount = pDoc->m_dib.GetBitCount(lpSrcDib);                    //获取图像位深
	lSrcLineBytes = pDoc->m_dib.GetReqByteWidth(lSrcWidth * lpSrcBitCount);		// 计算图象每行的字节数
/////////////////////////////////////////////////////////////////////////////////////////////////	
	CDlgImgInfo dlgPara;// 创建对话框		
	dlgPara.m_Width = lSrcWidth;
	dlgPara.m_Height = lSrcHeight;
	dlgPara.m_bitCount = lpSrcBitCount;

	if (dlgPara.DoModal() != IDOK)// 显示对话框， 
	{
		return;
	}
	::GlobalUnlock((HGLOBAL)pDoc->GetHObject());// 解除锁定
}


void CMFCApplication1View::OnChangelight()
{
	// TODO: 在此添加命令处理程序代码
	CMFCApplication1Doc* pDoc = GetDocument();// 获取文档
	////////////////////////////////////////////////////////////////////////////////////////////////	
	long	lSrcLineBytes;		//图象每行的字节数
	long	lSrcWidth;      //图象的宽度和高度
	long	lSrcHeight;
	int     lpSrcBitCount;       //图像的位深
	LPSTR	lpSrcDib;		//指向源图象的指针	
	LPSTR	lpSrcStartBits;	//指向源像素的指针
	lpSrcDib = (LPSTR) ::GlobalLock((HGLOBAL)pDoc->GetHObject());// 锁定DIB
	if (!lpSrcDib) return;
	/*
	if (pDoc->m_dib.GetColorNum(lpSrcDib) != 256)// 判断是否是8-bpp位图
	{
		   AfxMessageBox(L"对不起，不是256色位图！");// 警告
		   ::GlobalUnlock((HGLOBAL) pDoc->GetHObject());// 解除锁定
		   return;									//返回
	 }										//判断是否是8-bpp位图,不是则返回
	 */
	lpSrcStartBits = pDoc->m_dib.GetBits(lpSrcDib);			// 找到DIB图象像素起始位置	
	lSrcWidth = pDoc->m_dib.GetWidth(lpSrcDib);					// 获取图象的宽度		
	lSrcHeight = pDoc->m_dib.GetHeight(lpSrcDib);					// 获取图象的高度	
	lpSrcBitCount = pDoc->m_dib.GetBitCount(lpSrcDib);                    //获取图像位深
	lSrcLineBytes = pDoc->m_dib.GetReqByteWidth(lSrcWidth * lpSrcBitCount);		// 计算图象每行的字节数
/////////////////////////////////////////////////////////////////////////////////////////////////	
	
	CDlgChangeLight dig;// 创建对话框
	if (dig.DoModal() != IDOK)// 显示对话框， 
	{
		return;
	}

	unsigned char* lpSrc;
	LONG i;
	LONG j;

	LONG fTemp;

	for (i = 0; i < lSrcHeight; i++)
		for (j = 0; j < lSrcWidth; j++)
		{
			lpSrc = (unsigned char*)lpSrcStartBits + (lSrcLineBytes) * (lSrcHeight - 1 - i) + j;
			fTemp = *lpSrc + dig.Light;
			if (fTemp >= 255)
			{
				*lpSrc = 255;
			}
			else if (fTemp <= 0)  
			{
				*lpSrc = 0;
			}
			else 
			{ 
				*lpSrc = (unsigned char)(fTemp + 0.5);
			}
		}
	pDoc->SetModifiedFlag(true);
	pDoc->UpdateAllViews(NULL);
	::GlobalUnlock((HGLOBAL)pDoc->GetHObject());// 解除锁定
}

//void CMFCApplication1View::OnOK()
//{
//	// TODO: Add extra validation here
//
//	CDialog::OnOK();
//}

void CMFCApplication1View::OnShowhistogram()
{
	// TODO: 在此添加命令处理程序代码
	CMFCApplication1Doc* pDoc = GetDocument();// 获取文档
	////////////////////////////////////////////////////////////////////////////////////////////////	
	long	lSrcLineBytes;		//图象每行的字节数
	long	lSrcWidth;      //图象的宽度和高度
	long	lSrcHeight;
	int     lpSrcBitCount;       //图像的位深
	LPSTR	lpSrcDib;		//指向源图象的指针	
	LPSTR	lpSrcStartBits;	//指向源像素的指针
	lpSrcDib = (LPSTR) ::GlobalLock((HGLOBAL)pDoc->GetHObject());// 锁定DIB
	if (!lpSrcDib) return;
	
	if (pDoc->m_dib.GetColorNum(lpSrcDib) != 256)// 判断是否是8-bpp位图
	{
		   AfxMessageBox(L"对不起，不是256色位图！");// 警告
		   ::GlobalUnlock((HGLOBAL) pDoc->GetHObject());// 解除锁定
		   return;									//返回
	 }										//判断是否是8-bpp位图,不是则返回
	 
	lpSrcStartBits = pDoc->m_dib.GetBits(lpSrcDib);			// 找到DIB图象像素起始位置	
	lSrcWidth = pDoc->m_dib.GetWidth(lpSrcDib);					// 获取图象的宽度		
	lSrcHeight = pDoc->m_dib.GetHeight(lpSrcDib);					// 获取图象的高度	
	lpSrcBitCount = pDoc->m_dib.GetBitCount(lpSrcDib);                    //获取图像位深
	lSrcLineBytes = pDoc->m_dib.GetReqByteWidth(lSrcWidth * lpSrcBitCount);		// 计算图象每行的字节数
/////////////////////////////////////////////////////////////////////////////////////////////////
	CDlgHistogram dlgPara;
	dlgPara.m_lpDIBBits = lpSrcStartBits;
	dlgPara.m_lWidth = lSrcWidth;
	dlgPara.m_lHeight = lSrcHeight;
	dlgPara.m_iLowGray = 0;
	dlgPara.m_iUpGray = 255;
	if (dlgPara.DoModal() != IDOK)// 显示对话框， 
	{
		return;
	}
	delete dlgPara;
	EndWaitCursor();
	pDoc->SetModifiedFlag(true);
	pDoc->UpdateAllViews(NULL);
	::GlobalUnlock((HGLOBAL)pDoc->GetHObject());// 解除锁定
}

void CMFCApplication1View::OnChangepicture()
{
	// TODO: 在此添加命令处理程序代码
	CMFCApplication1Doc* pDoc = GetDocument();// 获取文档
	////////////////////////////////////////////////////////////////////////////////////////////////	
	long	lSrcLineBytes;		//图象每行的字节数
	long	lSrcWidth;      //图象的宽度和高度
	long	lSrcHeight;
	int     lpSrcBitCount;       //图像的位深
	LPSTR	lpSrcDib;		//指向源图象的指针	
	LPSTR	lpSrcStartBits;	//指向源像素的指针
	lpSrcDib = (LPSTR) ::GlobalLock((HGLOBAL)pDoc->GetHObject());// 锁定DIB
	if (!lpSrcDib) return;
	/*
	if (pDoc->m_dib.GetColorNum(lpSrcDib) != 256)// 判断是否是8-bpp位图
	{
		   AfxMessageBox(L"对不起，不是256色位图！");// 警告
		   ::GlobalUnlock((HGLOBAL) pDoc->GetHObject());// 解除锁定
		   return;									//返回
	 }										//判断是否是8-bpp位图,不是则返回
	 */
	lpSrcStartBits = pDoc->m_dib.GetBits(lpSrcDib);			// 找到DIB图象像素起始位置	
	lSrcWidth = pDoc->m_dib.GetWidth(lpSrcDib);					// 获取图象的宽度		
	lSrcHeight = pDoc->m_dib.GetHeight(lpSrcDib);					// 获取图象的高度	
	lpSrcBitCount = pDoc->m_dib.GetBitCount(lpSrcDib);                    //获取图像位深
	lSrcLineBytes = pDoc->m_dib.GetReqByteWidth(lSrcWidth * lpSrcBitCount);		// 计算图象每行的字节数
/////////////////////////////////////////////////////////////////////////////////////////////////	
	int lBitCountNew = lpSrcBitCount;
	long lLineBytesNew = pDoc->m_dib.GetReqByteWidth(lSrcWidth * lBitCountNew);
	int PaletteSize = 0;
	if (lpSrcBitCount == 8) PaletteSize = 1024;
	memcpy(lpSrcDib, pDoc->lpImgCpy, sizeof(BITMAPINFOHEADER) + PaletteSize + lSrcHeight * lLineBytesNew);


	//设置文档修改标志
	pDoc->SetModifiedFlag(true);
	//更新视图
	pDoc->UpdateAllViews(NULL);
	// 解除锁定
	::GlobalUnlock((HGLOBAL)pDoc->GetHObject());
}

void CMFCApplication1View::On8to8gray()
{
	// TODO: 在此添加命令处理程序代码
	CMFCApplication1Doc* pDoc = GetDocument();// 获取文档
	////////////////////////////////////////////////////////////////////////////////////////////////	
	long	lSrcLineBytes;		//图象每行的字节数
	long	lSrcWidth;      //图象的宽度和高度
	long	lSrcHeight;
	int     lpSrcBitCount;       //图像的位深
	LPSTR	lpSrcDib;		//指向源图象的指针	
	LPSTR	lpSrcStartBits;	//指向源像素的指针
	lpSrcDib = (LPSTR) ::GlobalLock((HGLOBAL)pDoc->GetHObject());// 锁定DIB
	if (!lpSrcDib) return;
	/*
	if (pDoc->m_dib.GetColorNum(lpSrcDib) != 256)// 判断是否是8-bpp位图
	{
		   AfxMessageBox(L"对不起，不是256色位图！");// 警告
		   ::GlobalUnlock((HGLOBAL) pDoc->GetHObject());// 解除锁定
		   return;									//返回
	 }										//判断是否是8-bpp位图,不是则返回
	 */
	lpSrcStartBits = pDoc->m_dib.GetBits(lpSrcDib);			// 找到DIB图象像素起始位置	
	lSrcWidth = pDoc->m_dib.GetWidth(lpSrcDib);					// 获取图象的宽度		
	lSrcHeight = pDoc->m_dib.GetHeight(lpSrcDib);					// 获取图象的高度	
	lpSrcBitCount = pDoc->m_dib.GetBitCount(lpSrcDib);                    //获取图像位深
	lSrcLineBytes = pDoc->m_dib.GetReqByteWidth(lSrcWidth * lpSrcBitCount);		// 计算图象每行的字节数
/////////////////////////////////////////////////////////////////////////////////////////////////	

	unsigned char* lpSrc;

	LONG i;
	LONG j;

	// 灰度映射表
	BYTE bMap[256];
	RGBQUAD* pTable, * pTable1;//颜色表指针

	pTable = (RGBQUAD*)(lpSrcDib + sizeof(BITMAPINFOHEADER));

	for (i = 0; i < 256; i++)//生成新的调色板,并转换灰度
	{
		// 计算该颜色对应的灰度值g=0.299*r+0.587*g+0.114*b 
		bMap[i] = (BYTE)(0.299 * pTable->rgbRed + 0.587 * pTable->rgbGreen + 0.114 * pTable->rgbBlue + 0.5);
		pTable->rgbRed = (BYTE)i;
		pTable->rgbGreen = (BYTE)i;
		pTable->rgbBlue = (BYTE)i;
		pTable->rgbReserved = (BYTE)0;
		pTable++;
	}

	for (i = 0; i < lSrcHeight; i++)
	{
		//逐列扫描
		for (j = 0; j < lSrcWidth; j++)
		{
			// 指向DIB第i行，第j个象素的指针
			lpSrc = (unsigned char*)lpSrcStartBits + lSrcLineBytes * (lSrcHeight - 1 - i) + j;
			// 变换
			*lpSrc = bMap[*lpSrc];
		}
	}
	pDoc->SetModifiedFlag(true);
	pDoc->UpdateAllViews(NULL);
	::GlobalUnlock((HGLOBAL)pDoc->GetHObject());// 解除锁定
}

BYTE BayerPattern[8][8] = { 0,32,8,40,2,34,10,42,
							48,16,56,24,50,18,58,26,
							12,44,4,36,14,46,6,38,
							60,28,52,20,62,30,54,22,
							3,35,11,43,1 ,33,9,41,
							51,19,59,27,49,17,57,25,
							15,47,7,39,13,45,5,37,
							63,31,55,23,61,29,53,21 };

void CMFCApplication1View::OnHalftone()
{
	// TODO: 在此添加命令处理程序代码
	CMFCApplication1Doc* pDoc = GetDocument();// 获取文档
	////////////////////////////////////////////////////////////////////////////////////////////////	
	long	lSrcLineBytes;		//图象每行的字节数
	long	lSrcWidth;      //图象的宽度和高度
	long	lSrcHeight;
	int     lpSrcBitCount;       //图像的位深
	LPSTR	lpSrcDib;		//指向源图象的指针	
	LPSTR	lpSrcStartBits;	//指向源像素的指针
	lpSrcDib = (LPSTR) ::GlobalLock((HGLOBAL)pDoc->GetHObject());// 锁定DIB
	if (!lpSrcDib) return;
	/*
	if (pDoc->m_dib.GetColorNum(lpSrcDib) != 256)// 判断是否是8-bpp位图
	{
		   AfxMessageBox(L"对不起，不是256色位图！");// 警告
		   ::GlobalUnlock((HGLOBAL) pDoc->GetHObject());// 解除锁定
		   return;									//返回
	 }										//判断是否是8-bpp位图,不是则返回
	 */
	lpSrcStartBits = pDoc->m_dib.GetBits(lpSrcDib);			// 找到DIB图象像素起始位置	
	lSrcWidth = pDoc->m_dib.GetWidth(lpSrcDib);					// 获取图象的宽度		
	lSrcHeight = pDoc->m_dib.GetHeight(lpSrcDib);					// 获取图象的高度	
	lpSrcBitCount = pDoc->m_dib.GetBitCount(lpSrcDib);                    //获取图像位深
	lSrcLineBytes = pDoc->m_dib.GetReqByteWidth(lSrcWidth * lpSrcBitCount);		// 计算图象每行的字节数
/////////////////////////////////////////////////////////////////////////////////////////////////

	char* lpSrc;
	lpSrc = lpSrcStartBits;
	unsigned char fTemp;
	LONG i;
	LONG j;
	for (i = 1; i <= lSrcWidth; i++) {
		for (j = 1; j <= lSrcHeight; j++)
		{
			fTemp = *lpSrc;
			if (lpSrcBitCount == 8) {
				if ((fTemp >> 2) > BayerPattern[i & 7][j & 7])
					*lpSrc = 255;
				else
					*lpSrc = 0;
				lpSrc++;
			}
			if (lpSrcBitCount == 24) {
				if ((fTemp >> 2) > BayerPattern[i & 7][j & 7])
					*lpSrc = 255;
				else
					*lpSrc = 0;
				*(lpSrc + 2) = *(lpSrc + 1) = *lpSrc;
				lpSrc = lpSrc + 3;
			}

		}
	}

	pDoc->SetModifiedFlag(true);
	pDoc->UpdateAllViews(NULL);
	::GlobalUnlock((HGLOBAL)pDoc->GetHObject());// 解除锁定
}

void CMFCApplication1View::OnBinarization()
{
	// TODO: 在此添加命令处理程序代码
	CMFCApplication1Doc* pDoc = GetDocument();// 获取文档
	////////////////////////////////////////////////////////////////////////////////////////////////	
	long	lSrcLineBytes;		//图象每行的字节数
	long	lSrcWidth;      //图象的宽度和高度
	long	lSrcHeight;
	int     lpSrcBitCount;       //图像的位深
	LPSTR	lpSrcDib;		//指向源图象的指针	
	LPSTR	lpSrcStartBits;	//指向源像素的指针
	lpSrcDib = (LPSTR) ::GlobalLock((HGLOBAL)pDoc->GetHObject());// 锁定DIB
	if (!lpSrcDib) return;
	/*
	if (pDoc->m_dib.GetColorNum(lpSrcDib) != 256)// 判断是否是8-bpp位图
	{
		   AfxMessageBox(L"对不起，不是256色位图！");// 警告
		   ::GlobalUnlock((HGLOBAL) pDoc->GetHObject());// 解除锁定
		   return;									//返回
	 }										//判断是否是8-bpp位图,不是则返回
	 */
	lpSrcStartBits = pDoc->m_dib.GetBits(lpSrcDib);			// 找到DIB图象像素起始位置	
	lSrcWidth = pDoc->m_dib.GetWidth(lpSrcDib);					// 获取图象的宽度		
	lSrcHeight = pDoc->m_dib.GetHeight(lpSrcDib);					// 获取图象的高度	
	lpSrcBitCount = pDoc->m_dib.GetBitCount(lpSrcDib);                    //获取图像位深
	lSrcLineBytes = pDoc->m_dib.GetReqByteWidth(lSrcWidth * lpSrcBitCount);		// 计算图象每行的字节数
/////////////////////////////////////////////////////////////////////////////////////////////////
	char * lpSrc;
	lpSrc = lpSrcStartBits;
	unsigned char fTemp;
	LONG i;
	LONG j;
	for (i = 1; i <= lSrcWidth; i++) {
		for (j = 1; j <= lSrcHeight; j++)
		{
			fTemp = *lpSrc;
			if (lpSrcBitCount == 8) {
				if (fTemp >= 128) {
					*lpSrc = 255;
				}
				else {
					*lpSrc = 0;
				}
				lpSrc++;
			}
			if (lpSrcBitCount == 24) {
				if (fTemp >= 128) {
					*lpSrc = 255;
				}
				else {
					*lpSrc = 0;
				}
				*(lpSrc+2) = *(lpSrc + 1) = *lpSrc;
				lpSrc = lpSrc + 3;
			}

		}
	}
	pDoc->SetModifiedFlag(true);
	pDoc->UpdateAllViews(NULL);
	::GlobalUnlock((HGLOBAL)pDoc->GetHObject());// 解除锁定
}

int PFC(int color1, int color2)
{
	int x, y, z;
	x = (color1 & 0xf) - (color2 & 0xf);
	y = ((color1 >> 4) & 0xf) - ((color2 >> 4) & 0xf);
	z = ((color1 >> 8) & 0xf) - ((color2 >> 8) & 0xf);
	return (x * x + y * y + z * z);
}

//直接插入排序  
int Sort1(int* src, int* attach, int n)
{
	int cur, cur1;
	int i, j, k = 0;
	for (i = 1; i < n; i++)
	{
		cur = src[i];
		cur1 = attach[i];
		for (j = i - 1; j >= 0; j--)
		{
			if (cur > src[j])
			{
				src[j + 1] = src[j];
				attach[j + 1] = attach[j];
			}
			else
				break;
		}
		src[j + 1] = cur;
		attach[j + 1] = cur1;
	}
	return 0;
}

//快速排序  
int Sort2(int* src, int* attach, int n)
{
	if (n <= 12)
		return Sort1(src, attach, n);
	int low = 1, high = n - 1;
	int tmp;
	while (low <= high)
	{
		while (src[low] >= src[0])
		{
			if (++low > n - 1)
				break;
		}
		while (src[high] < src[0])
		{
			if (--high < 1)
				break;
		}
		if (low > high)
			break;
		{
			tmp = src[low];
			src[low] = src[high];
			src[high] = tmp;
			tmp = attach[low];
			attach[low] = attach[high];
			attach[high] = tmp;
		}
		low++;
		high--;
	}


	{
		tmp = src[low - 1];
		src[low - 1] = src[0];
		src[0] = tmp;
		tmp = attach[low - 1];
		attach[low - 1] = attach[0];
		attach[0] = tmp;
	}
	if (low > 1)
		Sort2(src, attach, low - 1);
	if (low < n)
		Sort2(&src[low], &attach[low], n - low);
	return 0;
}

int Transfer(WORD* color24bit, int len, BYTE* Index, RGBQUAD* mainColor)
{
	int usedTimes[4096] = { 0 };
	int miniColor[4096];
	int i;
	for (i = 0; i < 4096; i++)
		miniColor[i] = i;
	i = 0;
	for (i = 0; i < len; i++)
	{
		assert(color24bit[i] < 4096);
		usedTimes[color24bit[i]]++;
	}

	int numberOfColors = 0;
	for (i = 0; i < 4096; i++)
	{
		if (usedTimes[i] > 0)
			numberOfColors++;
	}

	//对usedTimes进行排序，排序过程中minColor数组(保存了颜色值)也作与useTimes  
	//数组相似的交换  
	Sort2(usedTimes, miniColor, 4096);

	//usedTimes数组中是各颜色使用频率，从高到低排列，显然第numberOfColor个之后的都为0  
	//miniColor数组中是相应的颜色数据  
	//将前256个颜色数据保存到256色位图的调色盘中  
	for (i = 0; i < 256; i++)
	{
		mainColor[i].rgbBlue = (BYTE)((miniColor[i] >> 8) << 4);
		mainColor[i].rgbGreen = (BYTE)(((miniColor[i] >> 4) & 0xf) << 4);
		mainColor[i].rgbRed = (BYTE)((miniColor[i] & 0xf) << 4);
		mainColor[i].rgbReserved = 0;
	}

	int* colorIndex = usedTimes;//用原来的useTimes数组来保存索引值  
	memset(colorIndex, 0, sizeof(int) * 4096);

	if (numberOfColors <= 256)
	{
		for (i = 0; i < numberOfColors; i++)
			colorIndex[miniColor[i]] = i;
	}
	else//为第256之后的颜色在前256种颜色中找一个最接近的  
	{
		for (i = 0; i < 256; i++)
			colorIndex[miniColor[i]] = i;

		int index, tmp, tmp1;
		for (i = 256; i < numberOfColors; i++)
		{
			tmp = PFC(miniColor[0], miniColor[i]);
			index = 0;
			for (int j = 1; j < 256; j++)
			{
				tmp1 = PFC(miniColor[j], miniColor[i]);
				if (tmp > tmp1)
				{
					tmp = tmp1;
					index = j;
				}
			}
			colorIndex[miniColor[i]] = index;
		}
	}
	//记录各点颜色数据的索引值，即256色位图的颜色数据  
	for (i = 0; i < len; i++)
	{
		assert(colorIndex[color24bit[i]] < 256);
		Index[i] = colorIndex[color24bit[i]];
	}

	return 1;
}

void CMFCApplication1View::On24to8color()
{
	// TODO: 在此添加命令处理程序代码
	CMFCApplication1Doc* pDoc = GetDocument();// 获取文档
	////////////////////////////////////////////////////////////////////////////////////////////////	
	long	lSrcLineBytes;		//图象每行的字节数
	long	lSrcWidth;      //图象的宽度和高度
	long	lSrcHeight;
	int     lpSrcBitCount;       //图像的位深
	LPSTR	lpSrcDib;		//指向源图象的指针	
	LPSTR	lpSrcStartBits;	//指向源像素的指针
	lpSrcDib = (LPSTR) ::GlobalLock((HGLOBAL)pDoc->GetHObject());// 锁定DIB
	if (!lpSrcDib) return;
	/*
	if (pDoc->m_dib.GetColorNum(lpSrcDib) != 256)// 判断是否是8-bpp位图
	{
		   AfxMessageBox(L"对不起，不是256色位图！");// 警告
		   ::GlobalUnlock((HGLOBAL) pDoc->GetHObject());// 解除锁定
		   return;									//返回
	 }										//判断是否是8-bpp位图,不是则返回
	 */
	lpSrcStartBits = pDoc->m_dib.GetBits(lpSrcDib);			// 找到DIB图象像素起始位置	
	lSrcWidth = pDoc->m_dib.GetWidth(lpSrcDib);					// 获取图象的宽度		
	lSrcHeight = pDoc->m_dib.GetHeight(lpSrcDib);					// 获取图象的高度	
	lpSrcBitCount = pDoc->m_dib.GetBitCount(lpSrcDib);                    //获取图像位深
	lSrcLineBytes = pDoc->m_dib.GetReqByteWidth(lSrcWidth * lpSrcBitCount);		// 计算图象每行的字节数
/////////////////////////////////////////////////////////////////////////////////////////////////
	unsigned char* lpSrc;
	// 循环变量
	LONG    i;
	LONG    j;
	// 图像每行的字节数
	LONG    lLineBytes;
	// 计算图像每行的字节数
	lLineBytes = WIDTHBYTES(lSrcWidth * 24);
	BITMAPINFOHEADER* pHead;
	RGBQUAD* pColorTable = NULL;
	int lineByteNew;
	int biBitCount = 8;
	lineByteNew = (lSrcWidth * biBitCount / 8 + 3) / 4 * 4;
	//灰度图像有颜色表，且颜色表表项为
	if (biBitCount == 8) {
		//申请颜色表所需要的空间，给颜色表赋值
		pColorTable = new RGBQUAD[256];
		memset(pColorTable, 0, sizeof(RGBQUAD) * 256);
	}
	BYTE* Index = new BYTE[lineByteNew * lSrcHeight]; //图像数据区的数据(保存在Index中)
	WORD* shortColor = new WORD[lineByteNew * lSrcHeight]; //颜色的高4位
	int iRed, iGreen, iBlue;
	for (int i = 0; i < lSrcHeight; i++)
	{//取RGB颜色的高4位  
		for (int j = 0; j < lSrcWidth; j++)
		{
			lpSrc = (unsigned char*)lpSrcStartBits + lLineBytes * (lSrcHeight - 1 - i) + j * 3;
			iBlue = (*lpSrc) >> 4;
			iGreen = (*(++lpSrc)) >> 4;
			iRed = (*(++lpSrc)) >> 4;
			shortColor[lineByteNew * (lSrcHeight - 1 - i) + j] = (iBlue << 8) + (iGreen << 4) + iRed;
		}
	}


	//调用转换函数  24color To->8color
	Transfer(shortColor, lineByteNew * lSrcHeight, Index, pColorTable);
	/* Transfer(shortColor, nData/3, Index, mainColor);  */




//申请位图数据所需要的空间，读位图数据进内存
	unsigned char* pBmpBufNew;
	pBmpBufNew = new unsigned char[sizeof(BITMAPINFOHEADER) + 256 * 4];//申请新图像的空间
	memcpy(pBmpBufNew, (unsigned char*)lpSrcDib, sizeof(BITMAPINFOHEADER));//信息头拷贝
	pHead = (BITMAPINFOHEADER*)pBmpBufNew;
	pHead->biBitCount = 8;//改变位数,
	pHead->biHeight = lSrcHeight;
	pHead->biWidth = lSrcWidth;
	pHead->biClrUsed = 256;
	pHead->biClrImportant = 0;
	pHead->biCompression = 0;
	pHead->biPlanes = 1;
	pHead->biSize = 40;
	pHead->biSizeImage = lineByteNew * lSrcHeight;
	pHead->biXPelsPerMeter = 0;
	pHead->biYPelsPerMeter = 0;

	//拷贝
	memcpy(lpSrcDib, pBmpBufNew, sizeof(BITMAPINFOHEADER));
	memcpy(lpSrcDib + sizeof(BITMAPINFOHEADER), pColorTable, sizeof(RGBQUAD) * 256);
	memcpy(lpSrcDib + sizeof(BITMAPINFOHEADER) + sizeof(RGBQUAD) * 256, Index, lineByteNew * lSrcHeight);

	delete[]Index;
	delete[]shortColor;

	//设置文档修改标志
	pDoc->SetModifiedFlag(true);
	//更新视图
	pDoc->UpdateAllViews(NULL);
	//解除锁定
	::GlobalUnlock((HGLOBAL)pDoc->GetHObject());
}

void CMFCApplication1View::OnPointinvert()
{
	// TODO: 在此添加命令处理程序代码
	CMFCApplication1Doc* pDoc = GetDocument();// 获取文档
	////////////////////////////////////////////////////////////////////////////////////////////////	
	long	lSrcLineBytes;		//图象每行的字节数
	long	lSrcWidth;      //图象的宽度和高度
	long	lSrcHeight;
	int     lpSrcBitCount;       //图像的位深
	LPSTR	lpSrcDib;		//指向源图象的指针	
	LPSTR	lpSrcStartBits;	//指向源像素的指针
	lpSrcDib = (LPSTR) ::GlobalLock((HGLOBAL)pDoc->GetHObject());// 锁定DIB
	if (!lpSrcDib) return;
	/*
	if (pDoc->m_dib.GetColorNum(lpSrcDib) != 256)// 判断是否是8-bpp位图
	{
		   AfxMessageBox(L"对不起，不是256色位图！");// 警告
		   ::GlobalUnlock((HGLOBAL) pDoc->GetHObject());// 解除锁定
		   return;									//返回
	 }										//判断是否是8-bpp位图,不是则返回
	 */
	lpSrcStartBits = pDoc->m_dib.GetBits(lpSrcDib);			// 找到DIB图象像素起始位置	
	lSrcWidth = pDoc->m_dib.GetWidth(lpSrcDib);					// 获取图象的宽度		
	lSrcHeight = pDoc->m_dib.GetHeight(lpSrcDib);					// 获取图象的高度	
	lpSrcBitCount = pDoc->m_dib.GetBitCount(lpSrcDib);                    //获取图像位深
	lSrcLineBytes = pDoc->m_dib.GetReqByteWidth(lSrcWidth * lpSrcBitCount);		// 计算图象每行的字节数
/////////////////////////////////////////////////////////////////////////////////////////////////
	CDlgImgInverse digInverse;// 创建对话框
	FLOAT fA = -1.0;
	FLOAT fB = 255;
	unsigned char* lpSrc;
	LONG i;
	LONG j;

	LONG fTemp;

	for (i = 0; i < lSrcHeight; i++)
		for (j = 0; j < lSrcWidth; j++)
		{
			lpSrc = (unsigned char*)lpSrcStartBits + lSrcLineBytes * (lSrcHeight - 1 - i) + j;
			fTemp = fA*(*lpSrc) + fB;
			if (fTemp >= 255)
			{
				*lpSrc = 255;
			}
			else if (fTemp <= 0)
			{
				*lpSrc = 0;
			}
			else
			{
				*lpSrc = (unsigned char)(fTemp + 0.5);
			}
		}
	//if (digInverse.DoModal() != IDOK)// 显示对话框， 
	//{
	//	return;
	//}
	pDoc->SetModifiedFlag(true);
	pDoc->UpdateAllViews(NULL);
	::GlobalUnlock((HGLOBAL)pDoc->GetHObject());// 解除锁定
}

BOOL WINAPI GrayStretch(LPSTR lpDIBBits, LONG lWidth, LONG lHeight, BYTE bX1, BYTE bY1, BYTE bX2, BYTE bY2)
{

	// 指向源图像的指针
	unsigned char* lpSrc;

	// 循环变量
	LONG	i;
	LONG	j;

	// 灰度映射表
	BYTE	bMap[256];

	// 图像每行的字节数
	LONG	lLineBytes;

	// 计算图像每行的字节数
	lLineBytes = WIDTHBYTES(lWidth * 8);

	// 计算灰度映射表
	for (i = 0; i <= bX1; i++)
	{
		// 判断bX1是否大于0（防止分母为0）
		if (bX1 > 0)
		{
			// 线性变换
			bMap[i] = (BYTE)bY1 * i / bX1;
		}
		else
		{
			// 直接赋值为0
			bMap[i] = 0;
		}
	}
	for (; i <= bX2; i++)
	{
		// 判断bX1是否等于bX2（防止分母为0）
		if (bX2 != bX1)
		{
			// 线性变换
			bMap[i] = bY1 + (BYTE)((bY2 - bY1) * (i - bX1) / (bX2 - bX1));
		}
		else
		{
			// 直接赋值为bY1
			bMap[i] = bY1;
		}
	}
	for (; i < 256; i++)
	{
		// 判断bX2是否等于255（防止分母为0）
		if (bX2 != 255)
		{
			// 线性变换
			bMap[i] = bY2 + (BYTE)((255 - bY2) * (i - bX2) / (255 - bX2));
		}
		else
		{
			// 直接赋值为255
			bMap[i] = 255;
		}
	}

	// 每行
	for (i = 0; i < lHeight; i++)
	{
		// 每列
		for (j = 0; j < lWidth; j++)
		{
			// 指向DIB第i行，第j个象素的指针
			lpSrc = (unsigned char*)lpDIBBits + lLineBytes * (lHeight - 1 - i) + j;

			// 计算新的灰度值
			*lpSrc = bMap[*lpSrc];
		}
	}

	// 返回
	return TRUE;
}

void CMFCApplication1View::OnInversevchange()
{
	// TODO: 在此添加命令处理程序代码
	CMFCApplication1Doc* pDoc = GetDocument();// 获取文档
	////////////////////////////////////////////////////////////////////////////////////////////////	
	long	lSrcLineBytes;		//图象每行的字节数
	long	lSrcWidth;      //图象的宽度和高度
	long	lSrcHeight;
	int     lpSrcBitCount;       //图像的位深
	LPSTR	lpSrcDib;		//指向源图象的指针	
	LPSTR	lpSrcStartBits;	//指向源像素的指针
	lpSrcDib = (LPSTR) ::GlobalLock((HGLOBAL)pDoc->GetHObject());// 锁定DIB
	if (!lpSrcDib) return;
	/*
	if (pDoc->m_dib.GetColorNum(lpSrcDib) != 256)// 判断是否是8-bpp位图
	{
		   AfxMessageBox(L"对不起，不是256色位图！");// 警告
		   ::GlobalUnlock((HGLOBAL) pDoc->GetHObject());// 解除锁定
		   return;									//返回
	 }										//判断是否是8-bpp位图,不是则返回
	 */
	lpSrcStartBits = pDoc->m_dib.GetBits(lpSrcDib);			// 找到DIB图象像素起始位置	
	lSrcWidth = pDoc->m_dib.GetWidth(lpSrcDib);					// 获取图象的宽度		
	lSrcHeight = pDoc->m_dib.GetHeight(lpSrcDib);					// 获取图象的高度	
	lpSrcBitCount = pDoc->m_dib.GetBitCount(lpSrcDib);                    //获取图像位深
	lSrcLineBytes = pDoc->m_dib.GetReqByteWidth(lSrcWidth * lpSrcBitCount);		// 计算图象每行的字节数
/////////////////////////////////////////////////////////////////////////////////////////////////	
	CDlgVChange dlg;
	BYTE	bX1=0;
	BYTE	bY1=0;
	dlg.m_bX1 = 127;
	dlg.m_bY1 = 0;
	unsigned char* lpSrc;
	LONG i;
	LONG j;

	LONG fTemp;
	if (dlg.DoModal() != IDOK)// 显示对话框
	{
		return;
	}
	bX1 = dlg.m_bX1;
	GrayStretch(lpSrcStartBits, lSrcWidth, lSrcHeight, bX1, bY1, 255, 255);
	pDoc->SetModifiedFlag(true);
	pDoc->UpdateAllViews(NULL);
	::GlobalUnlock((HGLOBAL)pDoc->GetHObject());// 解除锁定
}

void CMFCApplication1View::OnVchange()
{
	// TODO: 在此添加命令处理程序代码
	// TODO: 在此添加命令处理程序代码
	CMFCApplication1Doc* pDoc = GetDocument();// 获取文档
	////////////////////////////////////////////////////////////////////////////////////////////////	
	long	lSrcLineBytes;		//图象每行的字节数
	long	lSrcWidth;      //图象的宽度和高度
	long	lSrcHeight;
	int     lpSrcBitCount;       //图像的位深
	LPSTR	lpSrcDib;		//指向源图象的指针	
	LPSTR	lpSrcStartBits;	//指向源像素的指针
	lpSrcDib = (LPSTR) ::GlobalLock((HGLOBAL)pDoc->GetHObject());// 锁定DIB
	if (!lpSrcDib) return;
	/*
	if (pDoc->m_dib.GetColorNum(lpSrcDib) != 256)// 判断是否是8-bpp位图
	{
		   AfxMessageBox(L"对不起，不是256色位图！");// 警告
		   ::GlobalUnlock((HGLOBAL) pDoc->GetHObject());// 解除锁定
		   return;									//返回
	 }										//判断是否是8-bpp位图,不是则返回
	 */
	lpSrcStartBits = pDoc->m_dib.GetBits(lpSrcDib);			// 找到DIB图象像素起始位置	
	lSrcWidth = pDoc->m_dib.GetWidth(lpSrcDib);					// 获取图象的宽度		
	lSrcHeight = pDoc->m_dib.GetHeight(lpSrcDib);					// 获取图象的高度	
	lpSrcBitCount = pDoc->m_dib.GetBitCount(lpSrcDib);                    //获取图像位深
	lSrcLineBytes = pDoc->m_dib.GetReqByteWidth(lSrcWidth * lpSrcBitCount);		// 计算图象每行的字节数
/////////////////////////////////////////////////////////////////////////////////////////////////
	CDlgVChangeReal dlg;
	BYTE	bX1 = 0;
	BYTE	bY1 = 0;
	dlg.m_bX1 = 127;
	dlg.m_bY1 = 255;
	unsigned char* lpSrc;
	LONG i;
	LONG j;

	LONG fTemp;
	if (dlg.DoModal() != IDOK)// 显示对话框
	{
		return;
	}
	bX1 = dlg.m_bX1;
	GrayStretch(lpSrcStartBits, lSrcWidth, lSrcHeight, bX1, bY1, 255, 255);
	pDoc->SetModifiedFlag(true);
	pDoc->UpdateAllViews(NULL);
	::GlobalUnlock((HGLOBAL)pDoc->GetHObject());// 解除锁定
}

void CMFCApplication1View::OnInverselchange()
{
	// TODO: 在此添加命令处理程序代码
	CMFCApplication1Doc* pDoc = GetDocument();// 获取文档
	////////////////////////////////////////////////////////////////////////////////////////////////	
	long	lSrcLineBytes;		//图象每行的字节数
	long	lSrcWidth;      //图象的宽度和高度
	long	lSrcHeight;
	int     lpSrcBitCount;       //图像的位深
	LPSTR	lpSrcDib;		//指向源图象的指针	
	LPSTR	lpSrcStartBits;	//指向源像素的指针
	lpSrcDib = (LPSTR) ::GlobalLock((HGLOBAL)pDoc->GetHObject());// 锁定DIB
	if (!lpSrcDib) return;
	/*
	if (pDoc->m_dib.GetColorNum(lpSrcDib) != 256)// 判断是否是8-bpp位图
	{
		   AfxMessageBox(L"对不起，不是256色位图！");// 警告
		   ::GlobalUnlock((HGLOBAL) pDoc->GetHObject());// 解除锁定
		   return;									//返回
	 }										//判断是否是8-bpp位图,不是则返回
	 */
	lpSrcStartBits = pDoc->m_dib.GetBits(lpSrcDib);			// 找到DIB图象像素起始位置	
	lSrcWidth = pDoc->m_dib.GetWidth(lpSrcDib);					// 获取图象的宽度		
	lSrcHeight = pDoc->m_dib.GetHeight(lpSrcDib);					// 获取图象的高度	
	lpSrcBitCount = pDoc->m_dib.GetBitCount(lpSrcDib);                    //获取图像位深
	lSrcLineBytes = pDoc->m_dib.GetReqByteWidth(lSrcWidth * lpSrcBitCount);		// 计算图象每行的字节数
/////////////////////////////////////////////////////////////////////////////////////////////////
	CDlgInverseLchange dlg;
	BYTE	bX1 = 0;
	BYTE	bY1 = 0;
	dlg.m_bX1 = 127;
	dlg.m_bY1 = 255;
	unsigned char* lpSrc;
	LONG i;
	LONG j;

	LONG fTemp;
	if (dlg.DoModal() != IDOK)// 显示对话框
	{
		return;
	}
	bX1 = dlg.m_bX1;
	GrayStretch(lpSrcStartBits, lSrcWidth, lSrcHeight, bX1, bY1, 255, 255);
	pDoc->SetModifiedFlag(true);
	pDoc->UpdateAllViews(NULL);
	::GlobalUnlock((HGLOBAL)pDoc->GetHObject());// 解除锁定
}

void CMFCApplication1View::OnLchange()
{
	// TODO: 在此添加命令处理程序代码
	CMFCApplication1Doc* pDoc = GetDocument();// 获取文档
////////////////////////////////////////////////////////////////////////////////////////////////	
	long	lSrcLineBytes;		//图象每行的字节数
	long	lSrcWidth;      //图象的宽度和高度
	long	lSrcHeight;
	int     lpSrcBitCount;       //图像的位深
	LPSTR	lpSrcDib;		//指向源图象的指针	
	LPSTR	lpSrcStartBits;	//指向源像素的指针
	lpSrcDib = (LPSTR) ::GlobalLock((HGLOBAL)pDoc->GetHObject());// 锁定DIB
	if (!lpSrcDib) return;
	/*
	if (pDoc->m_dib.GetColorNum(lpSrcDib) != 256)// 判断是否是8-bpp位图
	{
		   AfxMessageBox(L"对不起，不是256色位图！");// 警告
		   ::GlobalUnlock((HGLOBAL) pDoc->GetHObject());// 解除锁定
		   return;									//返回
	 }										//判断是否是8-bpp位图,不是则返回
	 */
	lpSrcStartBits = pDoc->m_dib.GetBits(lpSrcDib);			// 找到DIB图象像素起始位置	
	lSrcWidth = pDoc->m_dib.GetWidth(lpSrcDib);					// 获取图象的宽度		
	lSrcHeight = pDoc->m_dib.GetHeight(lpSrcDib);					// 获取图象的高度	
	lpSrcBitCount = pDoc->m_dib.GetBitCount(lpSrcDib);                    //获取图像位深
	lSrcLineBytes = pDoc->m_dib.GetReqByteWidth(lSrcWidth * lpSrcBitCount);		// 计算图象每行的字节数
/////////////////////////////////////////////////////////////////////////////////////////////////
	CDlgLChange Ldlg;
	BYTE	bX1 = 0;
	BYTE	bY1 = 0;
	Ldlg.m_bX1 = 127;
	Ldlg.m_bY1 = 255;
	unsigned char* lpSrc;
	LONG i;
	LONG j;

	LONG fTemp;
	if (Ldlg.DoModal() != IDOK)// 显示对话框
	{
		return;
	}
	bX1 = Ldlg.m_bX1;
	GrayStretch(lpSrcStartBits, lSrcWidth, lSrcHeight, bX1, bY1, 255, 255);
	pDoc->SetModifiedFlag(true);
	pDoc->UpdateAllViews(NULL);
	::GlobalUnlock((HGLOBAL)pDoc->GetHObject());// 解除锁定
}

BOOL WINAPI LinerTrans(LPSTR lpDIBBits, LONG lWidth, LONG lHeight, FLOAT fA, FLOAT fB)
{

	// 指向源图像的指针
	unsigned char* lpSrc;

	// 循环变量
	LONG	i;
	LONG	j;

	// 图像每行的字节数
	LONG	lLineBytes;

	// 中间变量
	FLOAT	fTemp;

	// 计算图像每行的字节数
	lLineBytes = WIDTHBYTES(lWidth * 8);

	// 每行
	for (i = 0; i < lHeight; i++)
	{
		// 每列
		for (j = 0; j < lWidth; j++)
		{
			// 指向DIB第i行，第j个象素的指针
			lpSrc = (unsigned char*)lpDIBBits + lLineBytes * (lHeight - 1 - i) + j;

			// 线性变换
			fTemp = fA * (*lpSrc) + fB;

			// 判断是否超出范围
			if (fTemp > 255)
			{
				// 直接赋值为255
				*lpSrc = 255;
			}
			else if (fTemp < 0)
			{
				// 直接赋值为0
				*lpSrc = 0;
			}
			else
			{
				// 四舍五入
				*lpSrc = (unsigned char)(fTemp + 0.5);
			}
		}
	}

	// 返回
	return TRUE;

}

void CMFCApplication1View::OnLinearchange()
{
	// TODO: 在此添加命令处理程序代码
	CMFCApplication1Doc* pDoc = GetDocument();// 获取文档
////////////////////////////////////////////////////////////////////////////////////////////////	
	long	lSrcLineBytes;		//图象每行的字节数
	long	lSrcWidth;      //图象的宽度和高度
	long	lSrcHeight;
	int     lpSrcBitCount;       //图像的位深
	LPSTR	lpSrcDib;		//指向源图象的指针	
	LPSTR	lpSrcStartBits;	//指向源像素的指针
	lpSrcDib = (LPSTR) ::GlobalLock((HGLOBAL)pDoc->GetHObject());// 锁定DIB
	if (!lpSrcDib) return;
	/*
	if (pDoc->m_dib.GetColorNum(lpSrcDib) != 256)// 判断是否是8-bpp位图
	{
		   AfxMessageBox(L"对不起，不是256色位图！");// 警告
		   ::GlobalUnlock((HGLOBAL) pDoc->GetHObject());// 解除锁定
		   return;									//返回
	 }										//判断是否是8-bpp位图,不是则返回
	 */
	lpSrcStartBits = pDoc->m_dib.GetBits(lpSrcDib);			// 找到DIB图象像素起始位置	
	lSrcWidth = pDoc->m_dib.GetWidth(lpSrcDib);					// 获取图象的宽度		
	lSrcHeight = pDoc->m_dib.GetHeight(lpSrcDib);					// 获取图象的高度	
	lpSrcBitCount = pDoc->m_dib.GetBitCount(lpSrcDib);                    //获取图像位深
	lSrcLineBytes = pDoc->m_dib.GetReqByteWidth(lSrcWidth * lpSrcBitCount);		// 计算图象每行的字节数
/////////////////////////////////////////////////////////////////////////////////////////////////
	CDlgLinerPara dlgPara;
	dlgPara.m_fA = 2.0;
	dlgPara.m_fB = -128.0;

	if (dlgPara.DoModal() != IDOK)
	{
		// 返回
		return;
	}
	FLOAT fA;
	FLOAT fB;
	fA = dlgPara.m_fA;
	fB = dlgPara.m_fB;
	LinerTrans(lpSrcStartBits, lSrcWidth, lSrcHeight, fA, fB);
	pDoc->SetModifiedFlag(true);
	pDoc->UpdateAllViews(NULL);
	::GlobalUnlock((HGLOBAL)pDoc->GetHObject());// 解除锁定
}

BOOL Template(LPSTR lpDIBBits, LONG lWidth, LONG lHeight,
	int iTempH, int iTempW,
	int iTempMX, int iTempMY,
	FLOAT* fpArray, FLOAT fCoef)
{
	// 指向复制图像的指针
	LPSTR	lpNewDIBBits;
	HLOCAL	hNewDIBBits;

	// 指向源图像的指针
	unsigned char* lpSrc;

	// 指向要复制区域的指针
	unsigned char* lpDst;

	// 循环变量
	LONG	i;
	LONG	j;
	LONG	k;
	LONG	l;

	// 计算结果
	FLOAT	fResult;

	// 图像每行的字节数
	LONG lLineBytes;

	// 计算图像每行的字节数
	lLineBytes = WIDTHBYTES(lWidth * 8);

	// 暂时分配内存，以保存新图像
	hNewDIBBits = LocalAlloc(LHND, lLineBytes * lHeight);

	// 判断是否内存分配失败
	if (hNewDIBBits == NULL)
	{
		// 分配内存失败
		return FALSE;
	}

	// 锁定内存
	lpNewDIBBits = (char*)LocalLock(hNewDIBBits);

	// 初始化图像为原始图像
	memcpy(lpNewDIBBits, lpDIBBits, lLineBytes * lHeight);

	// 行(除去边缘几行)
	for (i = iTempMY; i < lHeight - iTempH + iTempMY + 1; i++)
	{
		// 列(除去边缘几列)
		for (j = iTempMX; j < lWidth - iTempW + iTempMX + 1; j++)
		{
			// 指向新DIB第i行，第j个象素的指针
			lpDst = (unsigned char*)lpNewDIBBits + lLineBytes * (lHeight - 1 - i) + j;

			fResult = 0;

			// 计算
			for (k = 0; k < iTempH; k++)
			{
				for (l = 0; l < iTempW; l++)
				{
					// 指向DIB第i - iTempMY + k行，第j - iTempMX + l个象素的指针
					lpSrc = (unsigned char*)lpDIBBits + lLineBytes * (lHeight - 1 - i + iTempMY - k)
						+ j - iTempMX + l;

					// 保存象素值
					fResult += (*lpSrc) * fpArray[k * iTempW + l];
				}
			}

			// 乘上系数
			fResult *= fCoef;

			// 取绝对值
			fResult = (FLOAT)fabs(fResult);

			// 判断是否超过255
			if (fResult > 255)
			{
				// 直接赋值为255
				*lpDst = 255;
			}
			else
			{
				// 赋值
				*lpDst = (unsigned char)(fResult + 0.5);
			}

		}
	}

	// 复制变换后的图像
	memcpy(lpDIBBits, lpNewDIBBits, lLineBytes * lHeight);

	// 释放内存
	LocalUnlock(hNewDIBBits);
	LocalFree(hNewDIBBits);

	// 返回
	return TRUE;

}

void CMFCApplication1View::Onimgsmooth()
{
	// TODO: 在此添加命令处理程序代码
	CMFCApplication1Doc* pDoc = GetDocument();// 获取文档
////////////////////////////////////////////////////////////////////////////////////////////////	
	long	lSrcLineBytes;		//图象每行的字节数
	long	lSrcWidth;      //图象的宽度和高度
	long	lSrcHeight;
	int     lpSrcBitCount;       //图像的位深
	LPSTR	lpSrcDib;		//指向源图象的指针	
	LPSTR	lpSrcStartBits;	//指向源像素的指针
	lpSrcDib = (LPSTR) ::GlobalLock((HGLOBAL)pDoc->GetHObject());// 锁定DIB
	if (!lpSrcDib) return;
	/*
	if (pDoc->m_dib.GetColorNum(lpSrcDib) != 256)// 判断是否是8-bpp位图
	{
		   AfxMessageBox(L"对不起，不是256色位图！");// 警告
		   ::GlobalUnlock((HGLOBAL) pDoc->GetHObject());// 解除锁定
		   return;									//返回
	 }										//判断是否是8-bpp位图,不是则返回
	 */
	lpSrcStartBits = pDoc->m_dib.GetBits(lpSrcDib);			// 找到DIB图象像素起始位置	
	lSrcWidth = pDoc->m_dib.GetWidth(lpSrcDib);					// 获取图象的宽度		
	lSrcHeight = pDoc->m_dib.GetHeight(lpSrcDib);					// 获取图象的高度	
	lpSrcBitCount = pDoc->m_dib.GetBitCount(lpSrcDib);                    //获取图像位深
	lSrcLineBytes = pDoc->m_dib.GetReqByteWidth(lSrcWidth * lpSrcBitCount);		// 计算图象每行的字节数
/////////////////////////////////////////////////////////////////////////////////////////////////
	int		iTempH;
	// 模板宽度
	int		iTempW;
	// 模板系数
	FLOAT	fTempC;
	// 模板中心元素X坐标
	int		iTempMX;
	// 模板中心元素Y坐标
	int		iTempMY;
	// 模板元素数组
	FLOAT	aValue[25];
	CDlgImgSmooth dlgPara;
	// 给模板数组赋初值（为平均模板）
	aValue[0] = 1.0;
	aValue[1] = 1.0;
	aValue[2] = 1.0;
	aValue[3] = 0.0;
	aValue[4] = 0.0;
	aValue[5] = 1.0;
	aValue[6] = 1.0;
	aValue[7] = 1.0;
	aValue[8] = 0.0;
	aValue[9] = 0.0;
	aValue[10] = 1.0;
	aValue[11] = 1.0;
	aValue[12] = 1.0;
	aValue[13] = 0.0;
	aValue[14] = 0.0;
	aValue[15] = 0.0;
	aValue[16] = 0.0;
	aValue[17] = 0.0;
	aValue[18] = 0.0;
	aValue[19] = 0.0;
	aValue[20] = 0.0;
	aValue[21] = 0.0;
	aValue[22] = 0.0;
	aValue[23] = 0.0;
	aValue[24] = 0.0;

	// 初始化对话框变量值
	dlgPara.m_intType = 0;
	dlgPara.m_iTempH = 3;
	dlgPara.m_iTempW = 3;
	dlgPara.m_iTempMX = 1;
	dlgPara.m_iTempMY = 1;
	dlgPara.m_fTempC = (FLOAT)(1.0 / 9.0);
	dlgPara.m_fpArray = aValue;
	
	if (dlgPara.DoModal() != IDOK)
	{
		// 返回
		return;
	}
	// 获取用户设定的平移量
	iTempH = dlgPara.m_iTempH;
	iTempW = dlgPara.m_iTempW;
	iTempMX = dlgPara.m_iTempMX;
	iTempMY = dlgPara.m_iTempMY;
	fTempC = dlgPara.m_fTempC; 

	delete dlgPara;
	BeginWaitCursor();
	if (Template(lpSrcStartBits, lSrcWidth, lSrcHeight,
		iTempH, iTempW, iTempMX, iTempMY, aValue, fTempC))
	{

		// 设置脏标记
		pDoc->SetModifiedFlag(TRUE);

		// 更新视图
		pDoc->UpdateAllViews(NULL);
	}
	else
	{
		// 提示用户
		MessageBox(L"分配内存失败！", L"系统提示", MB_ICONINFORMATION | MB_OK);
	}
	::GlobalUnlock((HGLOBAL)pDoc->GetHObject());// 解除锁定
}

unsigned char GetMedianNum(unsigned char* bArray, int iFilterLen)
{
	// 循环变量
	int		i;
	int		j;

	// 中间变量
	unsigned char bTemp;

	// 用冒泡法对数组进行排序
	for (j = 0; j < iFilterLen - 1; j++)
	{
		for (i = 0; i < iFilterLen - j - 1; i++)
		{
			if (bArray[i] > bArray[i + 1])
			{
				// 互换
				bTemp = bArray[i];
				bArray[i] = bArray[i + 1];
				bArray[i + 1] = bTemp;
			}
		}
	}

	// 计算中值
	if ((iFilterLen & 1) > 0)
	{
		// 数组有奇数个元素，返回中间一个元素
		bTemp = bArray[(iFilterLen + 1) / 2];
	}
	else
	{
		// 数组有偶数个元素，返回中间两个元素平均值
		bTemp = (bArray[iFilterLen / 2] + bArray[iFilterLen / 2 + 1]) / 2;
	}

	// 返回中值
	return bTemp;
}

BOOL MedianFilter(LPSTR lpDIBBits, LONG lWidth, LONG lHeight,
	int iFilterH, int iFilterW,
	int iFilterMX, int iFilterMY)
{

	// 指向源图像的指针
	unsigned char* lpSrc;

	// 指向要复制区域的指针
	unsigned char* lpDst;

	// 指向复制图像的指针
	LPSTR			lpNewDIBBits;
	HLOCAL			hNewDIBBits;

	// 指向滤波器数组的指针
	unsigned char* aValue;
	HLOCAL			hArray;

	// 循环变量
	LONG			i;
	LONG			j;
	LONG			k;
	LONG			l;

	// 图像每行的字节数
	LONG			lLineBytes;

	// 计算图像每行的字节数
	lLineBytes = WIDTHBYTES(lWidth * 8);

	// 暂时分配内存，以保存新图像
	hNewDIBBits = LocalAlloc(LHND, lLineBytes * lHeight);

	// 判断是否内存分配失败
	if (hNewDIBBits == NULL)
	{
		// 分配内存失败
		return FALSE;
	}

	// 锁定内存
	lpNewDIBBits = (char*)LocalLock(hNewDIBBits);

	// 初始化图像为原始图像
	memcpy(lpNewDIBBits, lpDIBBits, lLineBytes * lHeight);

	// 暂时分配内存，以保存滤波器数组
	hArray = LocalAlloc(LHND, iFilterH * iFilterW);

	// 判断是否内存分配失败
	if (hArray == NULL)
	{
		// 释放内存
		LocalUnlock(hNewDIBBits);
		LocalFree(hNewDIBBits);

		// 分配内存失败
		return FALSE;
	}

	// 锁定内存
	aValue = (unsigned char*)LocalLock(hArray);

	// 开始中值滤波
	// 行(除去边缘几行)
	for (i = iFilterMY; i < lHeight - iFilterH + iFilterMY + 1; i++)
	{
		// 列(除去边缘几列)
		for (j = iFilterMX; j < lWidth - iFilterW + iFilterMX + 1; j++)
		{
			// 指向新DIB第i行，第j个象素的指针
			lpDst = (unsigned char*)lpNewDIBBits + lLineBytes * (lHeight - 1 - i) + j;

			// 读取滤波器数组
			for (k = 0; k < iFilterH; k++)
			{
				for (l = 0; l < iFilterW; l++)
				{
					// 指向DIB第i - iFilterMY + k行，第j - iFilterMX + l个象素的指针
					lpSrc = (unsigned char*)lpDIBBits + lLineBytes * (lHeight - 1 - i + iFilterMY - k) + j - iFilterMX + l;

					// 保存象素值
					aValue[k * iFilterW + l] = *lpSrc;
				}
			}

			// 获取中值
			*lpDst = GetMedianNum(aValue, iFilterH * iFilterW);
		}
	}

	// 复制变换后的图像
	memcpy(lpDIBBits, lpNewDIBBits, lLineBytes * lHeight);

	// 释放内存
	LocalUnlock(hNewDIBBits);
	LocalFree(hNewDIBBits);
	LocalUnlock(hArray);
	LocalFree(hArray);

	// 返回
	return TRUE;
}

void CMFCApplication1View::OnMedianfiltering()
{
	// TODO: 在此添加命令处理程序代码
	CMFCApplication1Doc* pDoc = GetDocument();// 获取文档
////////////////////////////////////////////////////////////////////////////////////////////////	
	long	lSrcLineBytes;		//图象每行的字节数
	long	lSrcWidth;      //图象的宽度和高度
	long	lSrcHeight;
	int     lpSrcBitCount;       //图像的位深
	LPSTR	lpSrcDib;		//指向源图象的指针	
	LPSTR	lpSrcStartBits;	//指向源像素的指针
	lpSrcDib = (LPSTR) ::GlobalLock((HGLOBAL)pDoc->GetHObject());// 锁定DIB
	if (!lpSrcDib) return;
	/*
	if (pDoc->m_dib.GetColorNum(lpSrcDib) != 256)// 判断是否是8-bpp位图
	{
		   AfxMessageBox(L"对不起，不是256色位图！");// 警告
		   ::GlobalUnlock((HGLOBAL) pDoc->GetHObject());// 解除锁定
		   return;									//返回
	 }										//判断是否是8-bpp位图,不是则返回
	 */
	lpSrcStartBits = pDoc->m_dib.GetBits(lpSrcDib);			// 找到DIB图象像素起始位置	
	lSrcWidth = pDoc->m_dib.GetWidth(lpSrcDib);					// 获取图象的宽度		
	lSrcHeight = pDoc->m_dib.GetHeight(lpSrcDib);					// 获取图象的高度	
	lpSrcBitCount = pDoc->m_dib.GetBitCount(lpSrcDib);                    //获取图像位深
	lSrcLineBytes = pDoc->m_dib.GetReqByteWidth(lSrcWidth * lpSrcBitCount);		// 计算图象每行的字节数
/////////////////////////////////////////////////////////////////////////////////////////////////
	// 滤波器的高度
	int iFilterH;
	// 滤波器的宽度
	int iFilterW;
	// 中心元素的X坐标
	int iFilterMX;
	// 中心元素的Y坐标
	int iFilterMY;
	CDlgMedianFiltering dlgPara;
	dlgPara.m_iFilterType = 0;
	dlgPara.m_iFilterH = 3;
	dlgPara.m_iFilterW = 1;
	dlgPara.m_iFilterMX = 0;
	dlgPara.m_iFilterMY = 1;

	if (dlgPara.DoModal() != IDOK)
	{
		// 返回
		return;
	}
	// 获取用户的设定
	iFilterH = dlgPara.m_iFilterH;
	iFilterW = dlgPara.m_iFilterW;
	iFilterMX = dlgPara.m_iFilterMX;
	iFilterMY = dlgPara.m_iFilterMY;
	// 删除对话框
	delete dlgPara;
	// 更改光标形状
	BeginWaitCursor();
	// 调用MedianFilter()函数中值滤波
	if (MedianFilter(lpSrcStartBits, lSrcWidth, lSrcHeight,
		iFilterH, iFilterW, iFilterMX, iFilterMY))
	{
		// 设置脏标记
		pDoc->SetModifiedFlag(TRUE);
		// 更新视图
		pDoc->UpdateAllViews(NULL);
	}
	else
	{
		// 提示用户
		MessageBox(L"分配内存失败！", L"系统提示", MB_ICONINFORMATION | MB_OK);
	}
	// 解除锁定
	::GlobalUnlock((HGLOBAL)pDoc->GetHObject());// 解除锁定
	// 恢复光标
	EndWaitCursor();
}

BOOL RandomNoiseDIB(LPSTR lpDIBBits, LONG lWidth, LONG lHeight)
{
	// 指向源图像的指针
	LPSTR	lpSrc;

	//循环变量
	long i;
	long j;

	// 图像每行的字节数
	LONG lLineBytes;

	//像素值
	unsigned char pixel;

	//噪声
	BYTE NoisePoint;

	// 计算图像每行的字节数
	lLineBytes = WIDTHBYTES(lWidth * 8);

	//生成伪随机种子
	srand((unsigned)time(NULL));

	//在图像中加噪
	for (j = 0; j < lHeight; j++)
	{
		for (i = 0; i < lLineBytes; i++)
		{
			NoisePoint = rand() / 1024;

			// 指向源图像倒数第j行，第i个象素的指针			
			lpSrc = (char*)lpDIBBits + lLineBytes * j + i;

			//取得像素值
			pixel = (unsigned char)*lpSrc;

			*lpSrc = (unsigned char)(pixel * 224 / 256 + NoisePoint);
		}
	}
	// 返回
	return true;
}

void CMFCApplication1View::OnRandomnoise()
{
	// TODO: 在此添加命令处理程序代码
	CMFCApplication1Doc* pDoc = GetDocument();// 获取文档
////////////////////////////////////////////////////////////////////////////////////////////////	
	long	lSrcLineBytes;		//图象每行的字节数
	long	lSrcWidth;      //图象的宽度和高度
	long	lSrcHeight;
	int     lpSrcBitCount;       //图像的位深
	LPSTR	lpSrcDib;		//指向源图象的指针	
	LPSTR	lpSrcStartBits;	//指向源像素的指针
	lpSrcDib = (LPSTR) ::GlobalLock((HGLOBAL)pDoc->GetHObject());// 锁定DIB
	if (!lpSrcDib) return;
	/*
	if (pDoc->m_dib.GetColorNum(lpSrcDib) != 256)// 判断是否是8-bpp位图
	{
		   AfxMessageBox(L"对不起，不是256色位图！");// 警告
		   ::GlobalUnlock((HGLOBAL) pDoc->GetHObject());// 解除锁定
		   return;									//返回
	 }										//判断是否是8-bpp位图,不是则返回
	 */
	lpSrcStartBits = pDoc->m_dib.GetBits(lpSrcDib);			// 找到DIB图象像素起始位置	
	lSrcWidth = pDoc->m_dib.GetWidth(lpSrcDib);					// 获取图象的宽度		
	lSrcHeight = pDoc->m_dib.GetHeight(lpSrcDib);					// 获取图象的高度	
	lpSrcBitCount = pDoc->m_dib.GetBitCount(lpSrcDib);                    //获取图像位深
	lSrcLineBytes = pDoc->m_dib.GetReqByteWidth(lSrcWidth * lpSrcBitCount);		// 计算图象每行的字节数
/////////////////////////////////////////////////////////////////////////////////////////////////
	if (RandomNoiseDIB(lpSrcStartBits, lSrcWidth, lSrcHeight))
	{

		// 设置脏标记
		pDoc->SetModifiedFlag(TRUE);

		// 更新视图
		pDoc->UpdateAllViews(NULL);
	}
	else
	{
		// 提示用户
		MessageBox(L"分配内存失败！", L"系统提示", MB_ICONINFORMATION | MB_OK);
	}
	// 解除锁定
	::GlobalUnlock((HGLOBAL)pDoc->GetHObject());// 解除锁定
	// 恢复光标
	EndWaitCursor();
}

BOOL SaltNoiseDIB(LPSTR lpDIBBits, LONG lWidth, LONG lHeight)
{
	// 指向源图像的指针
	LPSTR	lpSrc;

	//循环变量
	long i;
	long j;

	// 图像每行的字节数
	LONG lLineBytes;

	// 计算图像每行的字节数
	lLineBytes = WIDTHBYTES(lWidth * 8);

	//生成伪随机种子
	srand((unsigned)time(NULL));

	//在图像中加噪
	for (j = 0; j < lHeight; j++)
	{
		for (i = 0; i < lLineBytes; i++)
		{
			if (rand() > 31500)
			{
				// 指向源图像倒数第j行，第i个象素的指针			
				lpSrc = (char*)lpDIBBits + lLineBytes * j + i;

				//图像中当前点置为黑
				*lpSrc = 0;
			}
		}
	}
	// 返回
	return true;
}

void CMFCApplication1View::OnSaltnoise()
{
	// TODO: 在此添加命令处理程序代码
	CMFCApplication1Doc* pDoc = GetDocument();// 获取文档
////////////////////////////////////////////////////////////////////////////////////////////////	
	long	lSrcLineBytes;		//图象每行的字节数
	long	lSrcWidth;      //图象的宽度和高度
	long	lSrcHeight;
	int     lpSrcBitCount;       //图像的位深
	LPSTR	lpSrcDib;		//指向源图象的指针	
	LPSTR	lpSrcStartBits;	//指向源像素的指针
	lpSrcDib = (LPSTR) ::GlobalLock((HGLOBAL)pDoc->GetHObject());// 锁定DIB
	if (!lpSrcDib) return;
	/*
	if (pDoc->m_dib.GetColorNum(lpSrcDib) != 256)// 判断是否是8-bpp位图
	{
		   AfxMessageBox(L"对不起，不是256色位图！");// 警告
		   ::GlobalUnlock((HGLOBAL) pDoc->GetHObject());// 解除锁定
		   return;									//返回
	 }										//判断是否是8-bpp位图,不是则返回
	 */
	lpSrcStartBits = pDoc->m_dib.GetBits(lpSrcDib);			// 找到DIB图象像素起始位置	
	lSrcWidth = pDoc->m_dib.GetWidth(lpSrcDib);					// 获取图象的宽度		
	lSrcHeight = pDoc->m_dib.GetHeight(lpSrcDib);					// 获取图象的高度	
	lpSrcBitCount = pDoc->m_dib.GetBitCount(lpSrcDib);                    //获取图像位深
	lSrcLineBytes = pDoc->m_dib.GetReqByteWidth(lSrcWidth * lpSrcBitCount);		// 计算图象每行的字节数
/////////////////////////////////////////////////////////////////////////////////////////////////
	if (SaltNoiseDIB(lpSrcStartBits, lSrcWidth, lSrcHeight))
	{

		// 设置脏标记
		pDoc->SetModifiedFlag(TRUE);

		// 更新视图
		pDoc->UpdateAllViews(NULL);
	}
	else
	{
		// 提示用户
		MessageBox(L"分配内存失败！", L"系统提示", MB_ICONINFORMATION | MB_OK);
	}
	// 解除锁定
	::GlobalUnlock((HGLOBAL)pDoc->GetHObject());// 解除锁定
	// 恢复光标
	EndWaitCursor();
}

void CMFCApplication1View::OnLaplacesharp4()
{
	// TODO: 在此添加命令处理程序代码
	CMFCApplication1Doc* pDoc = GetDocument();// 获取文档
////////////////////////////////////////////////////////////////////////////////////////////////	
	long	lSrcLineBytes;		//图象每行的字节数
	long	lSrcWidth;      //图象的宽度和高度
	long	lSrcHeight;
	int     lpSrcBitCount;       //图像的位深
	LPSTR	lpSrcDib;		//指向源图象的指针	
	LPSTR	lpSrcStartBits;	//指向源像素的指针
	lpSrcDib = (LPSTR) ::GlobalLock((HGLOBAL)pDoc->GetHObject());// 锁定DIB
	if (!lpSrcDib) return;
	
	if (pDoc->m_dib.GetColorNum(lpSrcDib) != 256)// 判断是否是8-bpp位图
	{
		   AfxMessageBox(L"对不起，不是256色位图！");// 警告
		   ::GlobalUnlock((HGLOBAL) pDoc->GetHObject());// 解除锁定
		   return;									//返回
	 }										//判断是否是8-bpp位图,不是则返回
	 
	lpSrcStartBits = pDoc->m_dib.GetBits(lpSrcDib);			// 找到DIB图象像素起始位置	
	lSrcWidth = pDoc->m_dib.GetWidth(lpSrcDib);					// 获取图象的宽度		
	lSrcHeight = pDoc->m_dib.GetHeight(lpSrcDib);					// 获取图象的高度	
	lpSrcBitCount = pDoc->m_dib.GetBitCount(lpSrcDib);                    //获取图像位深
	lSrcLineBytes = pDoc->m_dib.GetReqByteWidth(lSrcWidth * lpSrcBitCount);		// 计算图象每行的字节数
/////////////////////////////////////////////////////////////////////////////////////////////////
	// 模板高度
	int		iTempH;
	// 模板宽度
	int		iTempW;
	// 模板系数
	FLOAT	fTempC;
	// 模板中心元素X坐标
	int		iTempMX;
	// 模板中心元素Y坐标
	int		iTempMY;
	// 模板元素数组
	FLOAT	aValue[9];
	iTempW = 3;
	iTempH = 3;
	fTempC = 1.0;
	iTempMX = 1;
	iTempMY = 1;
	aValue[0] = 0;
	aValue[1] = 1;
	aValue[2] = 0;
	aValue[3] = 1;
	aValue[4] = -4.0;
	aValue[5] = 1;
	aValue[6] = 0;
	aValue[7] = 1;
	aValue[8] = 0;
	// 调用Template()函数用拉普拉斯模板锐化DIB
	if (Template(lpSrcStartBits, lSrcWidth, lSrcHeight,
		iTempH, iTempW, iTempMX, iTempMY, aValue, fTempC))
	{

		// 设置脏标记
		pDoc->SetModifiedFlag(TRUE);

		// 更新视图
		pDoc->UpdateAllViews(NULL);
	}
	else
	{
		// 提示用户
		MessageBox(L"分配内存失败！", L"系统提示", MB_ICONINFORMATION | MB_OK);
	}
	// 解除锁定
	::GlobalUnlock((HGLOBAL)pDoc->GetHObject());// 解除锁定
	// 恢复光标
	EndWaitCursor();
}

void CMFCApplication1View::OnLaplacesharp8()
{
	// TODO: 在此添加命令处理程序代码
	CMFCApplication1Doc* pDoc = GetDocument();// 获取文档
////////////////////////////////////////////////////////////////////////////////////////////////	
	long	lSrcLineBytes;		//图象每行的字节数
	long	lSrcWidth;      //图象的宽度和高度
	long	lSrcHeight;
	int     lpSrcBitCount;       //图像的位深
	LPSTR	lpSrcDib;		//指向源图象的指针	
	LPSTR	lpSrcStartBits;	//指向源像素的指针
	lpSrcDib = (LPSTR) ::GlobalLock((HGLOBAL)pDoc->GetHObject());// 锁定DIB
	if (!lpSrcDib) return;

	if (pDoc->m_dib.GetColorNum(lpSrcDib) != 256)// 判断是否是8-bpp位图
	{
		AfxMessageBox(L"对不起，不是256色位图！");// 警告
		::GlobalUnlock((HGLOBAL)pDoc->GetHObject());// 解除锁定
		return;									//返回
	}										//判断是否是8-bpp位图,不是则返回

	lpSrcStartBits = pDoc->m_dib.GetBits(lpSrcDib);			// 找到DIB图象像素起始位置	
	lSrcWidth = pDoc->m_dib.GetWidth(lpSrcDib);					// 获取图象的宽度		
	lSrcHeight = pDoc->m_dib.GetHeight(lpSrcDib);					// 获取图象的高度	
	lpSrcBitCount = pDoc->m_dib.GetBitCount(lpSrcDib);                    //获取图像位深
	lSrcLineBytes = pDoc->m_dib.GetReqByteWidth(lSrcWidth * lpSrcBitCount);		// 计算图象每行的字节数
/////////////////////////////////////////////////////////////////////////////////////////////////
	// 模板高度
	int		iTempH;
	// 模板宽度
	int		iTempW;
	// 模板系数
	FLOAT	fTempC;
	// 模板中心元素X坐标
	int		iTempMX;
	// 模板中心元素Y坐标
	int		iTempMY;
	// 模板元素数组
	FLOAT	aValue[9];
	iTempW = 3;
	iTempH = 3;
	fTempC = 1.0;
	iTempMX = 1;
	iTempMY = 1;
	aValue[0] = -1.0;
	aValue[1] = -1.0;
	aValue[2] = -1.0;
	aValue[3] = -1.0;
	aValue[4] = 8.0;
	aValue[5] = -1.0;
	aValue[6] = -1.0;
	aValue[7] = -1.0;
	aValue[8] = -1.0;
	// 调用Template()函数用拉普拉斯模板锐化DIB
	if (Template(lpSrcStartBits, lSrcWidth, lSrcHeight,
		iTempH, iTempW, iTempMX, iTempMY, aValue, fTempC))
	{

		// 设置脏标记
		pDoc->SetModifiedFlag(TRUE);

		// 更新视图
		pDoc->UpdateAllViews(NULL);
	}
	else
	{
		// 提示用户
		MessageBox(L"分配内存失败！", L"系统提示", MB_ICONINFORMATION | MB_OK);
	}
	// 解除锁定
	::GlobalUnlock((HGLOBAL)pDoc->GetHObject());// 解除锁定
	// 恢复光标
	EndWaitCursor();
}

BOOL RobertDIB(LPSTR lpDIBBits, LONG lWidth, LONG lHeight)
{

	// 指向源图像的指针
	LPSTR	lpSrc;
	// 指向缓存图像的指针
	LPSTR	lpDst;
	// 指向缓存DIB图像的指针
	LPSTR	lpNewDIBBits;
	HLOCAL	hNewDIBBits;
	//循环变量
	long i;
	long j;
	//像素值
	double result;
	unsigned char pixel[4];
	// 暂时分配内存，以保存新图像
	hNewDIBBits = LocalAlloc(LHND, lWidth * lHeight);

	if (hNewDIBBits == NULL)
	{
		// 分配内存失败
		return FALSE;
	}

	// 锁定内存
	lpNewDIBBits = (char*)LocalLock(hNewDIBBits);

	// 初始化新分配的内存，设定初始值为255
	lpDst = (char*)lpNewDIBBits;
	memset(lpDst, (BYTE)255, lWidth * lHeight);


	//使用水平方向的结构元素进行腐蚀
	for (j = lHeight - 1; j > 0; j--)
	{
		for (i = 0; i < lWidth - 1; i++)
		{
			//由于使用2×2的模板，为防止越界，所以不处理最下边和最右边的两列像素

			// 指向源图像第j行，第i个象素的指针			
			lpSrc = (char*)lpDIBBits + lWidth * j + i;

			// 指向目标图像第j行，第i个象素的指针			
			lpDst = (char*)lpNewDIBBits + lWidth * j + i;

			//取得当前指针处2*2区域的像素值，注意要转换为unsigned char型
			pixel[0] = (unsigned char)*lpSrc;
			pixel[1] = (unsigned char)*(lpSrc + 1);
			pixel[2] = (unsigned char)*(lpSrc - lWidth);
			pixel[3] = (unsigned char)*(lpSrc - lWidth + 1);

			//计算目标图像中的当前点
			result = sqrt((pixel[0] - pixel[3]) * (pixel[0] - pixel[3]) + \
				(pixel[1] - pixel[2]) * (pixel[1] - pixel[2]));
			*lpDst = (unsigned char)result;

		}
	}

	// 复制腐蚀后的图像
	memcpy(lpDIBBits, lpNewDIBBits, lWidth * lHeight);

	// 释放内存
	LocalUnlock(hNewDIBBits);
	LocalFree(hNewDIBBits);

	// 返回
	return TRUE;
}

void CMFCApplication1View::OnRobert()
{
	// TODO: 在此添加命令处理程序代码
	CMFCApplication1Doc* pDoc = GetDocument();// 获取文档
////////////////////////////////////////////////////////////////////////////////////////////////	
	long	lSrcLineBytes;		//图象每行的字节数
	long	lSrcWidth;      //图象的宽度和高度
	long	lSrcHeight;
	int     lpSrcBitCount;       //图像的位深
	LPSTR	lpSrcDib;		//指向源图象的指针	
	LPSTR	lpSrcStartBits;	//指向源像素的指针
	lpSrcDib = (LPSTR) ::GlobalLock((HGLOBAL)pDoc->GetHObject());// 锁定DIB
	if (!lpSrcDib) return;

	//if (pDoc->m_dib.GetColorNum(lpSrcDib) != 256)// 判断是否是8-bpp位图
	//{
	//	AfxMessageBox(L"对不起，不是256色位图！");// 警告
	//	::GlobalUnlock((HGLOBAL)pDoc->GetHObject());// 解除锁定
	//	return;									//返回
	//}										//判断是否是8-bpp位图,不是则返回

	lpSrcStartBits = pDoc->m_dib.GetBits(lpSrcDib);			// 找到DIB图象像素起始位置	
	lSrcWidth = pDoc->m_dib.GetWidth(lpSrcDib);					// 获取图象的宽度		
	lSrcHeight = pDoc->m_dib.GetHeight(lpSrcDib);					// 获取图象的高度	
	lpSrcBitCount = pDoc->m_dib.GetBitCount(lpSrcDib);                    //获取图像位深
	lSrcLineBytes = pDoc->m_dib.GetReqByteWidth(lSrcWidth * lpSrcBitCount);		// 计算图象每行的字节数
/////////////////////////////////////////////////////////////////////////////////////////////////
	if (RobertDIB(lpSrcStartBits, WIDTHBYTES(lSrcWidth * 8), lSrcHeight))
	{
		// 设置脏标记
		pDoc->SetModifiedFlag(TRUE);
		// 更新视图
		pDoc->UpdateAllViews(NULL);
	}
	else
	{
		// 提示用户
		MessageBox(L"分配内存失败！", L"系统提示", MB_ICONINFORMATION | MB_OK);
	}
	// 解除锁定
	::GlobalUnlock((HGLOBAL)pDoc->GetHObject());// 解除锁定
	// 恢复光标
	EndWaitCursor();
}

BOOL SobelDIB(LPSTR lpDIBBits, LONG lWidth, LONG lHeight)
{
	// 指向缓存图像的指针
	LPSTR	lpDst1;
	LPSTR	lpDst2;
	// 指向缓存DIB图像的指针
	LPSTR	lpNewDIBBits1;
	HLOCAL	hNewDIBBits1;
	LPSTR	lpNewDIBBits2;
	HLOCAL	hNewDIBBits2;
	//循环变量
	long i;
	long j;
	// 模板高度
	int		iTempH;
	// 模板宽度
	int		iTempW;
	// 模板系数
	FLOAT	fTempC;
	// 模板中心元素X坐标
	int		iTempMX;
	// 模板中心元素Y坐标
	int		iTempMY;
	//模板数组
	FLOAT aTemplate[9];
	// 暂时分配内存，以保存新图像
	hNewDIBBits1 = LocalAlloc(LHND, lWidth * lHeight);
	if (hNewDIBBits1 == NULL)
	{
		// 分配内存失败
		return FALSE;
	}
	// 锁定内存
	lpNewDIBBits1 = (char*)LocalLock(hNewDIBBits1);

	// 暂时分配内存，以保存新图像
	hNewDIBBits2 = LocalAlloc(LHND, lWidth * lHeight);

	if (hNewDIBBits2 == NULL)
	{
		// 分配内存失败
		return FALSE;
	}

	// 锁定内存
	lpNewDIBBits2 = (char*)LocalLock(hNewDIBBits2);

	// 拷贝源图像到缓存图像中
	lpDst1 = (char*)lpNewDIBBits1;
	memcpy(lpNewDIBBits1, lpDIBBits, lWidth * lHeight);
	lpDst2 = (char*)lpNewDIBBits2;
	memcpy(lpNewDIBBits2, lpDIBBits, lWidth * lHeight);

	// 设置Sobel模板参数
	iTempW = 3;
	iTempH = 3;
	fTempC = 1.0;
	iTempMX = 1;
	iTempMY = 1;
	aTemplate[0] = -1.0;
	aTemplate[1] = -2.0;
	aTemplate[2] = -1.0;
	aTemplate[3] = 0.0;
	aTemplate[4] = 0.0;
	aTemplate[5] = 0.0;
	aTemplate[6] = 1.0;
	aTemplate[7] = 2.0;
	aTemplate[8] = 1.0;

	// 调用Template()函数
	if (!Template(lpNewDIBBits1, lWidth, lHeight,
		iTempH, iTempW, iTempMX, iTempMY, aTemplate, fTempC))
	{
		return FALSE;
	}

	// 设置Sobel模板参数
	aTemplate[0] = -1.0;
	aTemplate[1] = 0.0;
	aTemplate[2] = 1.0;
	aTemplate[3] = -2.0;
	aTemplate[4] = 0.0;
	aTemplate[5] = 2.0;
	aTemplate[6] = -1.0;
	aTemplate[7] = 0.0;
	aTemplate[8] = 1.0;

	// 调用Template()函数
	if (!Template(lpNewDIBBits2, lWidth, lHeight,
		iTempH, iTempW, iTempMX, iTempMY, aTemplate, fTempC))
	{
		return FALSE;
	}

	//求两幅缓存图像的最大值
	for (j = 0; j < lHeight; j++)
	{
		for (i = 0; i < lWidth - 1; i++)
		{

			// 指向缓存图像1倒数第j行，第i个象素的指针			
			lpDst1 = (char*)lpNewDIBBits1 + lWidth * j + i;

			// 指向缓存图像2倒数第j行，第i个象素的指针			
			lpDst2 = (char*)lpNewDIBBits2 + lWidth * j + i;

			if (*lpDst2 > *lpDst1)
				*lpDst1 = *lpDst2;

		}
	}

	// 复制经过模板运算后的图像到源图像
	memcpy(lpDIBBits, lpNewDIBBits1, lWidth * lHeight);

	// 释放内存
	LocalUnlock(hNewDIBBits1);
	LocalFree(hNewDIBBits1);

	LocalUnlock(hNewDIBBits2);
	LocalFree(hNewDIBBits2);
	// 返回
	return TRUE;
}

void CMFCApplication1View::OnSobel()
{
	// TODO: 在此添加命令处理程序代码
	CMFCApplication1Doc* pDoc = GetDocument();// 获取文档
////////////////////////////////////////////////////////////////////////////////////////////////	
	long	lSrcLineBytes;		//图象每行的字节数
	long	lSrcWidth;      //图象的宽度和高度
	long	lSrcHeight;
	int     lpSrcBitCount;       //图像的位深
	LPSTR	lpSrcDib;		//指向源图象的指针	
	LPSTR	lpSrcStartBits;	//指向源像素的指针
	lpSrcDib = (LPSTR) ::GlobalLock((HGLOBAL)pDoc->GetHObject());// 锁定DIB
	if (!lpSrcDib) return;

	if (pDoc->m_dib.GetColorNum(lpSrcDib) != 256)// 判断是否是8-bpp位图
	{
		AfxMessageBox(L"对不起，不是256色位图！");// 警告
		::GlobalUnlock((HGLOBAL)pDoc->GetHObject());// 解除锁定
		return;									//返回
	}										//判断是否是8-bpp位图,不是则返回

	lpSrcStartBits = pDoc->m_dib.GetBits(lpSrcDib);			// 找到DIB图象像素起始位置	
	lSrcWidth = pDoc->m_dib.GetWidth(lpSrcDib);					// 获取图象的宽度		
	lSrcHeight = pDoc->m_dib.GetHeight(lpSrcDib);					// 获取图象的高度	
	lpSrcBitCount = pDoc->m_dib.GetBitCount(lpSrcDib);                    //获取图像位深
	lSrcLineBytes = pDoc->m_dib.GetReqByteWidth(lSrcWidth * lpSrcBitCount);		// 计算图象每行的字节数
/////////////////////////////////////////////////////////////////////////////////////////////////
	if (SobelDIB(lpSrcStartBits, WIDTHBYTES(lSrcWidth * 8), lSrcHeight))
	{
		// 设置脏标记
		pDoc->SetModifiedFlag(TRUE);
		// 更新视图
		pDoc->UpdateAllViews(NULL);
	}
	else
	{
		// 提示用户
		MessageBox(L"分配内存失败！", L"系统提示", MB_ICONINFORMATION | MB_OK);
	}
	// 解除锁定
	::GlobalUnlock((HGLOBAL)pDoc->GetHObject());// 解除锁定
	// 恢复光标
	EndWaitCursor();
}

BOOL WINAPI GaussDIB(LPSTR lpDIBBits, LONG lWidth, LONG lHeight)
{

	// 指向缓存图像的指针
	LPSTR	lpDst1;
	LPSTR	lpDst2;

	// 指向缓存DIB图像的指针
	LPSTR	lpNewDIBBits1;
	HLOCAL	hNewDIBBits1;
	LPSTR	lpNewDIBBits2;
	HLOCAL	hNewDIBBits2;

	// 模板高度
	int		iTempH;

	// 模板宽度
	int		iTempW;

	// 模板系数
	FLOAT	fTempC;

	// 模板中心元素X坐标
	int		iTempMX;

	// 模板中心元素Y坐标
	int		iTempMY;

	//模板数组
	FLOAT aTemplate[25];

	// 暂时分配内存，以保存新图像
	hNewDIBBits1 = LocalAlloc(LHND, lWidth * lHeight);

	if (hNewDIBBits1 == NULL)
	{
		// 分配内存失败
		return FALSE;
	}

	// 锁定内存
	lpNewDIBBits1 = (char*)LocalLock(hNewDIBBits1);

	// 暂时分配内存，以保存新图像
	hNewDIBBits2 = LocalAlloc(LHND, lWidth * lHeight);

	if (hNewDIBBits2 == NULL)
	{
		// 分配内存失败
		return FALSE;
	}

	// 锁定内存
	lpNewDIBBits2 = (char*)LocalLock(hNewDIBBits2);

	// 拷贝源图像到缓存图像中
	lpDst1 = (char*)lpNewDIBBits1;
	memcpy(lpNewDIBBits1, lpDIBBits, lWidth * lHeight);
	lpDst2 = (char*)lpNewDIBBits2;
	memcpy(lpNewDIBBits2, lpDIBBits, lWidth * lHeight);


	// 设置Gauss模板参数
	iTempW = 5;
	iTempH = 5;
	fTempC = 1.0;
	iTempMX = 3;
	iTempMY = 3;
	aTemplate[0] = -2.0;
	aTemplate[1] = -4.0;
	aTemplate[2] = -4.0;
	aTemplate[3] = -4.0;
	aTemplate[4] = -2.0;
	aTemplate[5] = -4.0;
	aTemplate[6] = 0.0;
	aTemplate[7] = 8.0;
	aTemplate[8] = 0.0;
	aTemplate[9] = -4.0;
	aTemplate[10] = -4.0;
	aTemplate[11] = 8.0;
	aTemplate[12] = 24.0;
	aTemplate[13] = 8.0;
	aTemplate[14] = -4.0;
	aTemplate[15] = -4.0;
	aTemplate[16] = 0.0;
	aTemplate[17] = 8.0;
	aTemplate[18] = 0.0;
	aTemplate[19] = -4.0;
	aTemplate[20] = -2.0;
	aTemplate[21] = -4.0;
	aTemplate[22] = -4.0;
	aTemplate[23] = -4.0;
	aTemplate[24] = -2.0;

	// 调用Template()函数
	if (!Template(lpNewDIBBits1, lWidth, lHeight,
		iTempH, iTempW, iTempMX, iTempMY, aTemplate, fTempC))
	{
		return FALSE;
	}

	// 复制经过模板运算后的图像到源图像
	memcpy(lpDIBBits, lpNewDIBBits1, lWidth * lHeight);

	// 释放内存
	LocalUnlock(hNewDIBBits1);
	LocalFree(hNewDIBBits1);

	LocalUnlock(hNewDIBBits2);
	LocalFree(hNewDIBBits2);
	// 返回
	return TRUE;
}

void CMFCApplication1View::OnGausslaplace()
{
	// TODO: 在此添加命令处理程序代码
	CMFCApplication1Doc* pDoc = GetDocument();// 获取文档
////////////////////////////////////////////////////////////////////////////////////////////////	
	long	lSrcLineBytes;		//图象每行的字节数
	long	lSrcWidth;      //图象的宽度和高度
	long	lSrcHeight;
	int     lpSrcBitCount;       //图像的位深
	LPSTR	lpSrcDib;		//指向源图象的指针	
	LPSTR	lpSrcStartBits;	//指向源像素的指针
	lpSrcDib = (LPSTR) ::GlobalLock((HGLOBAL)pDoc->GetHObject());// 锁定DIB
	if (!lpSrcDib) return;

	if (pDoc->m_dib.GetColorNum(lpSrcDib) != 256)// 判断是否是8-bpp位图
	{
		AfxMessageBox(L"对不起，不是256色位图！");// 警告
		::GlobalUnlock((HGLOBAL)pDoc->GetHObject());// 解除锁定
		return;									//返回
	}										//判断是否是8-bpp位图,不是则返回

	lpSrcStartBits = pDoc->m_dib.GetBits(lpSrcDib);			// 找到DIB图象像素起始位置	
	lSrcWidth = pDoc->m_dib.GetWidth(lpSrcDib);					// 获取图象的宽度		
	lSrcHeight = pDoc->m_dib.GetHeight(lpSrcDib);					// 获取图象的高度	
	lpSrcBitCount = pDoc->m_dib.GetBitCount(lpSrcDib);                    //获取图像位深
	lSrcLineBytes = pDoc->m_dib.GetReqByteWidth(lSrcWidth * lpSrcBitCount);		// 计算图象每行的字节数
/////////////////////////////////////////////////////////////////////////////////////////////////
	if (GaussDIB(lpSrcStartBits, WIDTHBYTES(lSrcWidth * 8), lSrcHeight))
	{
		// 设置脏标记
		pDoc->SetModifiedFlag(TRUE);
		// 更新视图
		pDoc->UpdateAllViews(NULL);
	}
	else
	{
		// 提示用户
		MessageBox(L"分配内存失败！", L"系统提示", MB_ICONINFORMATION | MB_OK);
	}
	// 解除锁定
	::GlobalUnlock((HGLOBAL)pDoc->GetHObject());// 解除锁定
	// 恢复光标
	EndWaitCursor();

}

BOOL PrewittDIB(LPSTR lpDIBBits, LONG lWidth, LONG lHeight)
{

	// 指向缓存图像的指针
	LPSTR	lpDst1;
	LPSTR	lpDst2;

	// 指向缓存DIB图像的指针
	LPSTR	lpNewDIBBits1;
	HLOCAL	hNewDIBBits1;
	LPSTR	lpNewDIBBits2;
	HLOCAL	hNewDIBBits2;

	//循环变量
	long i;
	long j;

	// 模板高度
	int		iTempH;

	// 模板宽度
	int		iTempW;

	// 模板系数
	FLOAT	fTempC;

	// 模板中心元素X坐标
	int		iTempMX;

	// 模板中心元素Y坐标
	int		iTempMY;

	//模板数组
	FLOAT aTemplate[9];

	// 暂时分配内存，以保存新图像
	hNewDIBBits1 = LocalAlloc(LHND, lWidth * lHeight);

	if (hNewDIBBits1 == NULL)
	{
		// 分配内存失败
		return FALSE;
	}

	// 锁定内存
	lpNewDIBBits1 = (char*)LocalLock(hNewDIBBits1);

	// 暂时分配内存，以保存新图像
	hNewDIBBits2 = LocalAlloc(LHND, lWidth * lHeight);

	if (hNewDIBBits2 == NULL)
	{
		// 分配内存失败
		return FALSE;
	}

	// 锁定内存
	lpNewDIBBits2 = (char*)LocalLock(hNewDIBBits2);

	// 拷贝源图像到缓存图像中
	lpDst1 = (char*)lpNewDIBBits1;
	memcpy(lpNewDIBBits1, lpDIBBits, lWidth * lHeight);
	lpDst2 = (char*)lpNewDIBBits2;
	memcpy(lpNewDIBBits2, lpDIBBits, lWidth * lHeight);


	// 设置Prewitt模板参数
	iTempW = 3;
	iTempH = 3;
	fTempC = 1.0;
	iTempMX = 1;
	iTempMY = 1;
	aTemplate[0] = -1.0;
	aTemplate[1] = -1.0;
	aTemplate[2] = -1.0;
	aTemplate[3] = 0.0;
	aTemplate[4] = 0.0;
	aTemplate[5] = 0.0;
	aTemplate[6] = 1.0;
	aTemplate[7] = 1.0;
	aTemplate[8] = 1.0;

	// 调用Template()函数
	if (!Template(lpNewDIBBits1, lWidth, lHeight,
		iTempH, iTempW, iTempMX, iTempMY, aTemplate, fTempC))
	{
		return FALSE;
	}

	// 设置Prewitt模板参数
	aTemplate[0] = 1.0;
	aTemplate[1] = 0.0;
	aTemplate[2] = -1.0;
	aTemplate[3] = 1.0;
	aTemplate[4] = 0.0;
	aTemplate[5] = -1.0;
	aTemplate[6] = 1.0;
	aTemplate[7] = 0.0;
	aTemplate[8] = -1.0;

	// 调用Template()函数
	if (!Template(lpNewDIBBits2, lWidth, lHeight,
		iTempH, iTempW, iTempMX, iTempMY, aTemplate, fTempC))
	{
		return FALSE;
	}

	//求两幅缓存图像的最大值
	for (j = 0; j < lHeight; j++)
	{
		for (i = 0; i < lWidth - 1; i++)
		{

			// 指向缓存图像1倒数第j行，第i个象素的指针			
			lpDst1 = (char*)lpNewDIBBits1 + lWidth * j + i;

			// 指向缓存图像2倒数第j行，第i个象素的指针			
			lpDst2 = (char*)lpNewDIBBits2 + lWidth * j + i;

			if (*lpDst2 > *lpDst1)
				*lpDst1 = *lpDst2;

		}
	}

	// 复制经过模板运算后的图像到源图像
	memcpy(lpDIBBits, lpNewDIBBits1, lWidth * lHeight);

	// 释放内存
	LocalUnlock(hNewDIBBits1);
	LocalFree(hNewDIBBits1);

	LocalUnlock(hNewDIBBits2);
	LocalFree(hNewDIBBits2);
	// 返回
	return TRUE;
}

void CMFCApplication1View::OnPrewitt()
{
	// TODO: 在此添加命令处理程序代码
	CMFCApplication1Doc* pDoc = GetDocument();// 获取文档
////////////////////////////////////////////////////////////////////////////////////////////////	
	long	lSrcLineBytes;		//图象每行的字节数
	long	lSrcWidth;      //图象的宽度和高度
	long	lSrcHeight;
	int     lpSrcBitCount;       //图像的位深
	LPSTR	lpSrcDib;		//指向源图象的指针	
	LPSTR	lpSrcStartBits;	//指向源像素的指针
	lpSrcDib = (LPSTR) ::GlobalLock((HGLOBAL)pDoc->GetHObject());// 锁定DIB
	if (!lpSrcDib) return;

	if (pDoc->m_dib.GetColorNum(lpSrcDib) != 256)// 判断是否是8-bpp位图
	{
		AfxMessageBox(L"对不起，不是256色位图！");// 警告
		::GlobalUnlock((HGLOBAL)pDoc->GetHObject());// 解除锁定
		return;									//返回
	}										//判断是否是8-bpp位图,不是则返回

	lpSrcStartBits = pDoc->m_dib.GetBits(lpSrcDib);			// 找到DIB图象像素起始位置	
	lSrcWidth = pDoc->m_dib.GetWidth(lpSrcDib);					// 获取图象的宽度		
	lSrcHeight = pDoc->m_dib.GetHeight(lpSrcDib);					// 获取图象的高度	
	lpSrcBitCount = pDoc->m_dib.GetBitCount(lpSrcDib);                    //获取图像位深
	lSrcLineBytes = pDoc->m_dib.GetReqByteWidth(lSrcWidth * lpSrcBitCount);		// 计算图象每行的字节数
/////////////////////////////////////////////////////////////////////////////////////////////////
	if (PrewittDIB(lpSrcStartBits, WIDTHBYTES(lSrcWidth * 8), lSrcHeight))
	{
		// 设置脏标记
		pDoc->SetModifiedFlag(TRUE);
		// 更新视图
		pDoc->UpdateAllViews(NULL);
	}
	else
	{
		// 提示用户
		MessageBox(L"分配内存失败！", L"系统提示", MB_ICONINFORMATION | MB_OK);
	}
	// 解除锁定
	::GlobalUnlock((HGLOBAL)pDoc->GetHObject());// 解除锁定
	// 恢复光标
	EndWaitCursor();
}

BOOL KirschDIB(LPSTR lpDIBBits, LONG lWidth, LONG lHeight)
{

	// 指向缓存图像的指针
	LPSTR	lpDst1;
	LPSTR	lpDst2;

	// 指向缓存DIB图像的指针
	LPSTR	lpNewDIBBits1;
	HLOCAL	hNewDIBBits1;
	LPSTR	lpNewDIBBits2;
	HLOCAL	hNewDIBBits2;

	//循环变量
	long i;
	long j;

	// 模板高度
	int		iTempH;

	// 模板宽度
	int		iTempW;

	// 模板系数
	FLOAT	fTempC;

	// 模板中心元素X坐标
	int		iTempMX;

	// 模板中心元素Y坐标
	int		iTempMY;

	//模板数组
	FLOAT aTemplate[9];

	// 暂时分配内存，以保存新图像
	hNewDIBBits1 = LocalAlloc(LHND, lWidth * lHeight);

	if (hNewDIBBits1 == NULL)
	{
		// 分配内存失败
		return FALSE;
	}

	// 锁定内存
	lpNewDIBBits1 = (char*)LocalLock(hNewDIBBits1);

	// 暂时分配内存，以保存新图像
	hNewDIBBits2 = LocalAlloc(LHND, lWidth * lHeight);

	if (hNewDIBBits2 == NULL)
	{
		// 分配内存失败
		return FALSE;
	}

	// 锁定内存
	lpNewDIBBits2 = (char*)LocalLock(hNewDIBBits2);

	// 拷贝源图像到缓存图像中
	lpDst1 = (char*)lpNewDIBBits1;
	memcpy(lpNewDIBBits1, lpDIBBits, lWidth * lHeight);
	lpDst2 = (char*)lpNewDIBBits2;
	memcpy(lpNewDIBBits2, lpDIBBits, lWidth * lHeight);


	// 设置Kirsch模板1参数
	iTempW = 3;
	iTempH = 3;
	fTempC = 1.0;
	iTempMX = 1;
	iTempMY = 1;
	aTemplate[0] = 5.0;
	aTemplate[1] = 5.0;
	aTemplate[2] = 5.0;
	aTemplate[3] = -3.0;
	aTemplate[4] = 0.0;
	aTemplate[5] = -3.0;
	aTemplate[6] = -3.0;
	aTemplate[7] = -3.0;
	aTemplate[8] = -3.0;

	// 调用Template()函数
	if (!Template(lpNewDIBBits1, lWidth, lHeight,
		iTempH, iTempW, iTempMX, iTempMY, aTemplate, fTempC))
	{
		return FALSE;
	}

	// 设置Kirsch模板2参数
	aTemplate[0] = -3.0;
	aTemplate[1] = 5.0;
	aTemplate[2] = 5.0;
	aTemplate[3] = -3.0;
	aTemplate[4] = 0.0;
	aTemplate[5] = 5.0;
	aTemplate[6] = -3.0;
	aTemplate[7] = -3.0;
	aTemplate[8] = -3.0;

	// 调用Template()函数
	if (!Template(lpNewDIBBits2, lWidth, lHeight,
		iTempH, iTempW, iTempMX, iTempMY, aTemplate, fTempC))
	{
		return FALSE;
	}

	//求两幅缓存图像的最大值
	for (j = 0; j < lHeight; j++)
	{
		for (i = 0; i < lWidth - 1; i++)
		{

			// 指向缓存图像1倒数第j行，第i个象素的指针			
			lpDst1 = (char*)lpNewDIBBits1 + lWidth * j + i;

			// 指向缓存图像2倒数第j行，第i个象素的指针			
			lpDst2 = (char*)lpNewDIBBits2 + lWidth * j + i;

			if (*lpDst2 > *lpDst1)
				*lpDst1 = *lpDst2;

		}
	}

	// 拷贝源图像到缓存图像中
	memcpy(lpNewDIBBits2, lpDIBBits, lWidth * lHeight);

	// 设置Kirsch模板3参数
	aTemplate[0] = -3.0;
	aTemplate[1] = -3.0;
	aTemplate[2] = 5.0;
	aTemplate[3] = -3.0;
	aTemplate[4] = 0.0;
	aTemplate[5] = 5.0;
	aTemplate[6] = -3.0;
	aTemplate[7] = -3.0;
	aTemplate[8] = 5.0;

	// 调用Template()函数
	if (!Template(lpNewDIBBits2, lWidth, lHeight,
		iTempH, iTempW, iTempMX, iTempMY, aTemplate, fTempC))
	{
		return FALSE;
	}

	//求两幅缓存图像的最大值
	for (j = 0; j < lHeight; j++)
	{
		for (i = 0; i < lWidth - 1; i++)
		{

			// 指向缓存图像1倒数第j行，第i个象素的指针			
			lpDst1 = (char*)lpNewDIBBits1 + lWidth * j + i;

			// 指向缓存图像2倒数第j行，第i个象素的指针			
			lpDst2 = (char*)lpNewDIBBits2 + lWidth * j + i;

			if (*lpDst2 > *lpDst1)
				*lpDst1 = *lpDst2;

		}
	}

	// 拷贝源图像到缓存图像中
	memcpy(lpNewDIBBits2, lpDIBBits, lWidth * lHeight);

	// 设置Kirsch模板4参数
	aTemplate[0] = -3.0;
	aTemplate[1] = -3.0;
	aTemplate[2] = -3.0;
	aTemplate[3] = -3.0;
	aTemplate[4] = 0.0;
	aTemplate[5] = 5.0;
	aTemplate[6] = -3.0;
	aTemplate[7] = 5.0;
	aTemplate[8] = 5.0;

	// 调用Template()函数
	if (!Template(lpNewDIBBits2, lWidth, lHeight,
		iTempH, iTempW, iTempMX, iTempMY, aTemplate, fTempC))
	{
		return FALSE;
	}

	//求两幅缓存图像的最大值
	for (j = 0; j < lHeight; j++)
	{
		for (i = 0; i < lWidth - 1; i++)
		{

			// 指向缓存图像1倒数第j行，第i个象素的指针			
			lpDst1 = (char*)lpNewDIBBits1 + lWidth * j + i;

			// 指向缓存图像2倒数第j行，第i个象素的指针			
			lpDst2 = (char*)lpNewDIBBits2 + lWidth * j + i;

			if (*lpDst2 > *lpDst1)
				*lpDst1 = *lpDst2;

		}
	}

	// 拷贝源图像到缓存图像中
	memcpy(lpNewDIBBits2, lpDIBBits, lWidth * lHeight);

	// 设置Kirsch模板5参数
	aTemplate[0] = -3.0;
	aTemplate[1] = -3.0;
	aTemplate[2] = -3.0;
	aTemplate[3] = -3.0;
	aTemplate[4] = 0.0;
	aTemplate[5] = -3.0;
	aTemplate[6] = 5.0;
	aTemplate[7] = 5.0;
	aTemplate[8] = 5.0;

	// 调用Template()函数
	if (!Template(lpNewDIBBits2, lWidth, lHeight,
		iTempH, iTempW, iTempMX, iTempMY, aTemplate, fTempC))
	{
		return FALSE;
	}

	// 拷贝源图像到缓存图像中
	memcpy(lpNewDIBBits2, lpDIBBits, lWidth * lHeight);
	//求两幅缓存图像的最大值
	for (j = 0; j < lHeight; j++)
	{
		for (i = 0; i < lWidth - 1; i++)
		{

			// 指向缓存图像1倒数第j行，第i个象素的指针			
			lpDst1 = (char*)lpNewDIBBits1 + lWidth * j + i;

			// 指向缓存图像2倒数第j行，第i个象素的指针			
			lpDst2 = (char*)lpNewDIBBits2 + lWidth * j + i;

			if (*lpDst2 > *lpDst1)
				*lpDst1 = *lpDst2;

		}
	}

	// 拷贝源图像到缓存图像中
	memcpy(lpNewDIBBits2, lpDIBBits, lWidth * lHeight);

	// 设置Kirsch模板6参数
	aTemplate[0] = -3.0;
	aTemplate[1] = -3.0;
	aTemplate[2] = -3.0;
	aTemplate[3] = 5.0;
	aTemplate[4] = 0.0;
	aTemplate[5] = -3.0;
	aTemplate[6] = 5.0;
	aTemplate[7] = 5.0;
	aTemplate[8] = -3.0;

	// 调用Template()函数
	if (!Template(lpNewDIBBits2, lWidth, lHeight,
		iTempH, iTempW, iTempMX, iTempMY, aTemplate, fTempC))
	{
		return FALSE;
	}

	//求两幅缓存图像的最大值
	for (j = 0; j < lHeight; j++)
	{
		for (i = 0; i < lWidth - 1; i++)
		{

			// 指向缓存图像1倒数第j行，第i个象素的指针			
			lpDst1 = (char*)lpNewDIBBits1 + lWidth * j + i;

			// 指向缓存图像2倒数第j行，第i个象素的指针			
			lpDst2 = (char*)lpNewDIBBits2 + lWidth * j + i;

			if (*lpDst2 > *lpDst1)
				*lpDst1 = *lpDst2;

		}
	}

	// 拷贝源图像到缓存图像中
	memcpy(lpNewDIBBits2, lpDIBBits, lWidth * lHeight);

	// 设置Kirsch模板7参数
	aTemplate[0] = 5.0;
	aTemplate[1] = -3.0;
	aTemplate[2] = -3.0;
	aTemplate[3] = 5.0;
	aTemplate[4] = 0.0;
	aTemplate[5] = -3.0;
	aTemplate[6] = 5.0;
	aTemplate[7] = -3.0;
	aTemplate[8] = -3.0;

	// 调用Template()函数
	if (!Template(lpNewDIBBits2, lWidth, lHeight,
		iTempH, iTempW, iTempMX, iTempMY, aTemplate, fTempC))
	{
		return FALSE;
	}

	//求两幅缓存图像的最大值
	for (j = 0; j < lHeight; j++)
	{
		for (i = 0; i < lWidth - 1; i++)
		{

			// 指向缓存图像1倒数第j行，第i个象素的指针			
			lpDst1 = (char*)lpNewDIBBits1 + lWidth * j + i;

			// 指向缓存图像2倒数第j行，第i个象素的指针			
			lpDst2 = (char*)lpNewDIBBits2 + lWidth * j + i;

			if (*lpDst2 > *lpDst1)
				*lpDst1 = *lpDst2;

		}
	}

	// 拷贝源图像到缓存图像中
	memcpy(lpNewDIBBits2, lpDIBBits, lWidth * lHeight);

	// 设置Kirsch模板8参数
	aTemplate[0] = 5.0;
	aTemplate[1] = 5.0;
	aTemplate[2] = -3.0;
	aTemplate[3] = 5.0;
	aTemplate[4] = 0.0;
	aTemplate[5] = -3.0;
	aTemplate[6] = -3.0;
	aTemplate[7] = -3.0;
	aTemplate[8] = -3.0;

	// 调用Template()函数
	if (!Template(lpNewDIBBits2, lWidth, lHeight,
		iTempH, iTempW, iTempMX, iTempMY, aTemplate, fTempC))
	{
		return FALSE;
	}

	//求两幅缓存图像的最大值
	for (j = 0; j < lHeight; j++)
	{
		for (i = 0; i < lWidth - 1; i++)
		{

			// 指向缓存图像1倒数第j行，第i个象素的指针			
			lpDst1 = (char*)lpNewDIBBits1 + lWidth * j + i;

			// 指向缓存图像2倒数第j行，第i个象素的指针			
			lpDst2 = (char*)lpNewDIBBits2 + lWidth * j + i;

			if (*lpDst2 > *lpDst1)
				*lpDst1 = *lpDst2;

		}
	}

	// 复制经过模板运算后的图像到源图像
	memcpy(lpDIBBits, lpNewDIBBits1, lWidth * lHeight);

	// 释放内存
	LocalUnlock(hNewDIBBits1);
	LocalFree(hNewDIBBits1);

	LocalUnlock(hNewDIBBits2);
	LocalFree(hNewDIBBits2);
	// 返回
	return TRUE;
}

void CMFCApplication1View::OnKirsch()
{
	// TODO: 在此添加命令处理程序代码
	CMFCApplication1Doc* pDoc = GetDocument();// 获取文档
////////////////////////////////////////////////////////////////////////////////////////////////	
	long	lSrcLineBytes;		//图象每行的字节数
	long	lSrcWidth;      //图象的宽度和高度
	long	lSrcHeight;
	int     lpSrcBitCount;       //图像的位深
	LPSTR	lpSrcDib;		//指向源图象的指针	
	LPSTR	lpSrcStartBits;	//指向源像素的指针
	lpSrcDib = (LPSTR) ::GlobalLock((HGLOBAL)pDoc->GetHObject());// 锁定DIB
	if (!lpSrcDib) return;

	if (pDoc->m_dib.GetColorNum(lpSrcDib) != 256)// 判断是否是8-bpp位图
	{
		AfxMessageBox(L"对不起，不是256色位图！");// 警告
		::GlobalUnlock((HGLOBAL)pDoc->GetHObject());// 解除锁定
		return;									//返回
	}										//判断是否是8-bpp位图,不是则返回

	lpSrcStartBits = pDoc->m_dib.GetBits(lpSrcDib);			// 找到DIB图象像素起始位置	
	lSrcWidth = pDoc->m_dib.GetWidth(lpSrcDib);					// 获取图象的宽度		
	lSrcHeight = pDoc->m_dib.GetHeight(lpSrcDib);					// 获取图象的高度	
	lpSrcBitCount = pDoc->m_dib.GetBitCount(lpSrcDib);                    //获取图像位深
	lSrcLineBytes = pDoc->m_dib.GetReqByteWidth(lSrcWidth * lpSrcBitCount);		// 计算图象每行的字节数
/////////////////////////////////////////////////////////////////////////////////////////////////
	if (KirschDIB(lpSrcStartBits, WIDTHBYTES(lSrcWidth) * 8, lSrcHeight))
	{
		// 设置脏标记
		pDoc->SetModifiedFlag(TRUE);
		// 更新视图
		pDoc->UpdateAllViews(NULL);
	}
	else
	{
		// 提示用户
		MessageBox(L"分配内存失败！", L"系统提示", MB_ICONINFORMATION | MB_OK);
	}
	// 解除锁定
	::GlobalUnlock((HGLOBAL)pDoc->GetHObject());// 解除锁定
	// 恢复光标
	EndWaitCursor();
}

BOOL DilationDIB(LPSTR lpDIBBits, LONG lWidth, LONG lHeight, int nMode, int structure[3][3])
{

	// 指向源图像的指针
	LPSTR	lpSrc;

	// 指向缓存图像的指针
	LPSTR	lpDst;

	// 指向缓存DIB图像的指针
	LPSTR	lpNewDIBBits;
	HLOCAL	hNewDIBBits;

	//循环变量
	long i;
	long j;
	int  n;
	int  m;

	//像素值
	unsigned char pixel;

	// 暂时分配内存，以保存新图像
	hNewDIBBits = LocalAlloc(LHND, lWidth * lHeight);

	if (hNewDIBBits == NULL)
	{
		// 分配内存失败
		return FALSE;
	}

	// 锁定内存
	lpNewDIBBits = (char*)LocalLock(hNewDIBBits);

	// 初始化新分配的内存，设定初始值为255
	lpDst = (char*)lpNewDIBBits;
	memset(lpDst, (BYTE)255, lWidth * lHeight);


	if (nMode == 0)
	{
		//使用水平方向的结构元素进行膨胀
		for (j = 0; j < lHeight; j++)
		{
			for (i = 1; i < lWidth - 1; i++)
			{
				//由于使用1×3的结构元素，为防止越界，所以不处理最左边和最右边的两列像素

				// 指向源图像倒数第j行，第i个象素的指针			
				lpSrc = (char*)lpDIBBits + lWidth * j + i;

				// 指向目标图像倒数第j行，第i个象素的指针			
				lpDst = (char*)lpNewDIBBits + lWidth * j + i;

				//取得当前指针处的像素值，注意要转换为unsigned char型
				pixel = (unsigned char)*lpSrc;

				//目标图像中含有0和255外的其它灰度值
				if (pixel != 255 && pixel != 0)
					return FALSE;

				//目标图像中的当前点先赋成白色
				*lpDst = (unsigned char)255;

				//源图像中当前点自身或者左右只要有一个点是黑色，
				//则将目标图像中的当前点赋成黑色
				for (n = 0; n < 3; n++)
				{
					pixel = *(lpSrc + n - 1);
					if (pixel == 0)
					{
						*lpDst = (unsigned char)0;
						break;
					}
				}

			}
		}

	}
	else if (nMode == 1)
	{
		//使用垂直方向的结构元素进行膨胀
		for (j = 1; j < lHeight - 1; j++)
		{
			for (i = 0; i < lWidth; i++)
			{
				//由于使用1×3的结构元素，为防止越界，所以不处理最上边和最下边的两列像素

				// 指向源图像倒数第j行，第i个象素的指针			
				lpSrc = (char*)lpDIBBits + lWidth * j + i;

				// 指向目标图像倒数第j行，第i个象素的指针			
				lpDst = (char*)lpNewDIBBits + lWidth * j + i;

				//取得当前指针处的像素值，注意要转换为unsigned char型
				pixel = (unsigned char)*lpSrc;

				//目标图像中含有0和255外的其它灰度值
				if (pixel != 255 && *lpSrc != 0)
					return FALSE;

				//目标图像中的当前点先赋成白色
				*lpDst = (unsigned char)255;

				//源图像中当前点自身或者上下只要有一个点是黑色，
				//则将目标图像中的当前点赋成黑色
				for (n = 0; n < 3; n++)
				{
					pixel = *(lpSrc + (n - 1) * lWidth);
					if (pixel == 0)
					{
						*lpDst = (unsigned char)0;
						break;
					}
				}

			}
		}

	}
	else
	{
		//使用自定义的结构元素进行膨胀
		for (j = 1; j < lHeight - 1; j++)
		{
			for (i = 0; i < lWidth; i++)
			{
				//由于使用3×3的结构元素，为防止越界，所以不处理最左边和最右边的两列像素
				//和最上边和最下边的两列像素
				// 指向源图像倒数第j行，第i个象素的指针			
				lpSrc = (char*)lpDIBBits + lWidth * j + i;

				// 指向目标图像倒数第j行，第i个象素的指针			
				lpDst = (char*)lpNewDIBBits + lWidth * j + i;

				//取得当前指针处的像素值，注意要转换为unsigned char型
				pixel = (unsigned char)*lpSrc;

				//目标图像中含有0和255外的其它灰度值
				if (pixel != 255 && *lpSrc != 0)
					return FALSE;

				//目标图像中的当前点先赋成白色
				*lpDst = (unsigned char)255;

				//原图像中对应结构元素中为黑色的那些点中只要有一个是黑色，
				//则将目标图像中的当前点赋成黑色
				//注意在DIB图像中内容是上下倒置的
				for (m = 0; m < 3; m++)
				{
					for (n = 0; n < 3; n++)
					{
						if (structure[m][n] == -1)
							continue;
						pixel = *(lpSrc + ((2 - m) - 1) * lWidth + (n - 1));
						if (pixel == 0)
						{
							*lpDst = (unsigned char)0;
							break;
						}
					}
				}

			}
		}

	}
	// 复制膨胀后的图像
	memcpy(lpDIBBits, lpNewDIBBits, lWidth * lHeight);

	// 释放内存
	LocalUnlock(hNewDIBBits);
	LocalFree(hNewDIBBits);

	// 返回
	return TRUE;
}

void CMFCApplication1View::OnExpansion()
{
	// TODO: 在此添加命令处理程序代码
	CMFCApplication1Doc* pDoc = GetDocument();// 获取文档
////////////////////////////////////////////////////////////////////////////////////////////////	
	long	lSrcLineBytes;		//图象每行的字节数
	long	lSrcWidth;      //图象的宽度和高度
	long	lSrcHeight;
	int     lpSrcBitCount;       //图像的位深
	LPSTR	lpSrcDib;		//指向源图象的指针	
	LPSTR	lpSrcStartBits;	//指向源像素的指针
	lpSrcDib = (LPSTR) ::GlobalLock((HGLOBAL)pDoc->GetHObject());// 锁定DIB
	if (!lpSrcDib) return;

	if (pDoc->m_dib.GetColorNum(lpSrcDib) != 256)// 判断是否是8-bpp位图
	{
		AfxMessageBox(L"对不起，不是256色位图！");// 警告
		::GlobalUnlock((HGLOBAL)pDoc->GetHObject());// 解除锁定
		return;									//返回
	}										//判断是否是8-bpp位图,不是则返回

	lpSrcStartBits = pDoc->m_dib.GetBits(lpSrcDib);			// 找到DIB图象像素起始位置	
	lSrcWidth = pDoc->m_dib.GetWidth(lpSrcDib);					// 获取图象的宽度		
	lSrcHeight = pDoc->m_dib.GetHeight(lpSrcDib);					// 获取图象的高度	
	lpSrcBitCount = pDoc->m_dib.GetBitCount(lpSrcDib);                    //获取图像位深
	lSrcLineBytes = pDoc->m_dib.GetReqByteWidth(lSrcWidth * lpSrcBitCount);		// 计算图象每行的字节数
/////////////////////////////////////////////////////////////////////////////////////////////////
	CDlgExpansion dlgPara;
	int nMode;
	dlgPara.m_nMode = 0;
	// 显示对话框，提示用户设定腐蚀方向
	if (dlgPara.DoModal() != IDOK)
	{
		// 返回
		return;
	}
		// 获取用户设定的腐蚀方向
	nMode = dlgPara.m_nMode;

	int structure[3][3];
	if (nMode == 2)
	{
		structure[0][0] = dlgPara.m_nStructure1;
		structure[0][1] = dlgPara.m_nStructure2;
		structure[0][2] = dlgPara.m_nStructure3;
		structure[1][0] = dlgPara.m_nStructure4;
		structure[1][1] = dlgPara.m_nStructure5;
		structure[1][2] = dlgPara.m_nStructure6;
		structure[2][0] = dlgPara.m_nStructure7;
		structure[2][1] = dlgPara.m_nStructure8;
		structure[2][2] = dlgPara.m_nStructure9;
	}
	// 删除对话框
	delete dlgPara;
	// 更改光标形状
	BeginWaitCursor();
	if (DilationDIB(lpSrcStartBits, WIDTHBYTES(lSrcWidth * 8), lSrcHeight, nMode, structure))
	{
		// 设置脏标记
		pDoc->SetModifiedFlag(TRUE);
		// 更新视图
		pDoc->UpdateAllViews(NULL);
	}
	::GlobalUnlock((HGLOBAL)pDoc->GetHObject());// 解除锁定
}

BOOL ErosionDIB(LPSTR lpDIBBits, LONG lWidth, LONG lHeight, int nMode, int structure[3][3])
{

	// 指向源图像的指针
	LPSTR	lpSrc;

	// 指向缓存图像的指针
	LPSTR	lpDst;

	// 指向缓存DIB图像的指针
	LPSTR	lpNewDIBBits;
	HLOCAL	hNewDIBBits;

	//循环变量
	long i;
	long j;
	int  n;
	int  m;

	//像素值
	unsigned char pixel;

	// 暂时分配内存，以保存新图像
	hNewDIBBits = LocalAlloc(LHND, lWidth * lHeight);

	if (hNewDIBBits == NULL)
	{
		// 分配内存失败
		return FALSE;
	}

	// 锁定内存
	lpNewDIBBits = (char*)LocalLock(hNewDIBBits);

	// 初始化新分配的内存，设定初始值为255
	lpDst = (char*)lpNewDIBBits;
	memset(lpDst, (BYTE)255, lWidth * lHeight);


	if (nMode == 0)
	{
		//使用水平方向的结构元素进行腐蚀
		for (j = 0; j < lHeight; j++)
		{
			for (i = 1; i < lWidth - 1; i++)
			{
				//由于使用1×3的结构元素，为防止越界，所以不处理最左边和最右边的两列像素

				// 指向源图像倒数第j行，第i个象素的指针			
				lpSrc = (char*)lpDIBBits + lWidth * j + i;

				// 指向目标图像倒数第j行，第i个象素的指针			
				lpDst = (char*)lpNewDIBBits + lWidth * j + i;

				//取得当前指针处的像素值，注意要转换为unsigned char型
				pixel = (unsigned char)*lpSrc;

				//目标图像中含有0和255外的其它灰度值
				if (pixel != 255 && *lpSrc != 0)
					return FALSE;

				//目标图像中的当前点先赋成黑色
				*lpDst = (unsigned char)0;

				//如果源图像中当前点自身或者左右有一个点不是黑色，
				//则将目标图像中的当前点赋成白色
				for (n = 0; n < 3; n++)
				{
					pixel = *(lpSrc + n - 1);
					if (pixel == 255)
					{
						*lpDst = (unsigned char)255;
						break;
					}
				}

			}
		}

	}
	else if (nMode == 1)
	{
		//使用垂直方向的结构元素进行腐蚀
		for (j = 1; j < lHeight - 1; j++)
		{
			for (i = 0; i < lWidth; i++)
			{
				//由于使用1×3的结构元素，为防止越界，所以不处理最上边和最下边的两列像素

				// 指向源图像倒数第j行，第i个象素的指针			
				lpSrc = (char*)lpDIBBits + lWidth * j + i;

				// 指向目标图像倒数第j行，第i个象素的指针			
				lpDst = (char*)lpNewDIBBits + lWidth * j + i;

				//取得当前指针处的像素值，注意要转换为unsigned char型
				pixel = (unsigned char)*lpSrc;

				//目标图像中含有0和255外的其它灰度值
				if (pixel != 255 && *lpSrc != 0)
					return FALSE;

				//目标图像中的当前点先赋成黑色
				*lpDst = (unsigned char)0;

				//如果源图像中当前点自身或者上下有一个点不是黑色，
				//则将目标图像中的当前点赋成白色
				for (n = 0; n < 3; n++)
				{
					pixel = *(lpSrc + (n - 1) * lWidth);
					if (pixel == 255)
					{
						*lpDst = (unsigned char)255;
						break;
					}
				}

			}
		}

	}
	else
	{
		//使用自定义的结构元素进行腐蚀
		for (j = 1; j < lHeight - 1; j++)
		{
			for (i = 0; i < lWidth; i++)
			{
				//由于使用3×3的结构元素，为防止越界，所以不处理最左边和最右边的两列像素
				//和最上边和最下边的两列像素
				// 指向源图像倒数第j行，第i个象素的指针			
				lpSrc = (char*)lpDIBBits + lWidth * j + i;

				// 指向目标图像倒数第j行，第i个象素的指针			
				lpDst = (char*)lpNewDIBBits + lWidth * j + i;

				//取得当前指针处的像素值，注意要转换为unsigned char型
				pixel = (unsigned char)*lpSrc;

				//目标图像中含有0和255外的其它灰度值
				if (pixel != 255 && *lpSrc != 0)
					return FALSE;

				//目标图像中的当前点先赋成黑色
				*lpDst = (unsigned char)0;

				//如果原图像中对应结构元素中为黑色的那些点中有一个不是黑色，
				//则将目标图像中的当前点赋成白色
				//注意在DIB图像中内容是上下倒置的
				for (m = 0; m < 3; m++)
				{
					for (n = 0; n < 3; n++)
					{
						if (structure[m][n] == -1)
							continue;
						pixel = *(lpSrc + ((2 - m) - 1) * lWidth + (n - 1));
						if (pixel == 255)
						{
							*lpDst = (unsigned char)255;
							break;
						}
					}
				}

			}
		}

	}
	// 复制腐蚀后的图像
	memcpy(lpDIBBits, lpNewDIBBits, lWidth * lHeight);

	// 释放内存
	LocalUnlock(hNewDIBBits);
	LocalFree(hNewDIBBits);

	// 返回
	return TRUE;
}

void CMFCApplication1View::Oncorrosion()
{
	// TODO: 在此添加命令处理程序代码
	CMFCApplication1Doc* pDoc = GetDocument();// 获取文档
////////////////////////////////////////////////////////////////////////////////////////////////	
	long	lSrcLineBytes;		//图象每行的字节数
	long	lSrcWidth;      //图象的宽度和高度
	long	lSrcHeight;
	int     lpSrcBitCount;       //图像的位深
	LPSTR	lpSrcDib;		//指向源图象的指针	
	LPSTR	lpSrcStartBits;	//指向源像素的指针
	lpSrcDib = (LPSTR) ::GlobalLock((HGLOBAL)pDoc->GetHObject());// 锁定DIB
	if (!lpSrcDib) return;

	if (pDoc->m_dib.GetColorNum(lpSrcDib) != 256)// 判断是否是8-bpp位图
	{
		AfxMessageBox(L"对不起，不是256色位图！");// 警告
		::GlobalUnlock((HGLOBAL)pDoc->GetHObject());// 解除锁定
		return;									//返回
	}										//判断是否是8-bpp位图,不是则返回

	lpSrcStartBits = pDoc->m_dib.GetBits(lpSrcDib);			// 找到DIB图象像素起始位置	
	lSrcWidth = pDoc->m_dib.GetWidth(lpSrcDib);					// 获取图象的宽度		
	lSrcHeight = pDoc->m_dib.GetHeight(lpSrcDib);					// 获取图象的高度	
	lpSrcBitCount = pDoc->m_dib.GetBitCount(lpSrcDib);                    //获取图像位深
	lSrcLineBytes = pDoc->m_dib.GetReqByteWidth(lSrcWidth * lpSrcBitCount);		// 计算图象每行的字节数
/////////////////////////////////////////////////////////////////////////////////////////////////
	CDlgCorrosion dlgPara;
	int nMode;
	dlgPara.m_nMode = 0;
	// 显示对话框，提示用户设定腐蚀方向
	if (dlgPara.DoModal() != IDOK)
	{
		// 返回
		return;
	}
	// 获取用户设定的腐蚀方向
	nMode = dlgPara.m_nMode;
	int structure[3][3];
	if (nMode == 2)
	{
		structure[0][0] = dlgPara.m_nStructure1;
		structure[0][1] = dlgPara.m_nStructure2;
		structure[0][2] = dlgPara.m_nStructure3;
		structure[1][0] = dlgPara.m_nStructure4;
		structure[1][1] = dlgPara.m_nStructure5;
		structure[1][2] = dlgPara.m_nStructure6;
		structure[2][0] = dlgPara.m_nStructure7;
		structure[2][1] = dlgPara.m_nStructure8;
		structure[2][2] = dlgPara.m_nStructure9;
	}
	// 删除对话框
	delete dlgPara;
	// 更改光标形状
	BeginWaitCursor();
	if (ErosionDIB(lpSrcStartBits, WIDTHBYTES(lSrcWidth * 8), lSrcHeight, nMode, structure))
	{
		// 设置脏标记
		pDoc->SetModifiedFlag(TRUE);
		// 更新视图
		pDoc->UpdateAllViews(NULL);
	}
	::GlobalUnlock((HGLOBAL)pDoc->GetHObject());// 解除锁定
}

BOOL OpenDIB(LPSTR lpDIBBits, LONG lWidth, LONG lHeight, int nMode, int structure[3][3])
{

	// 指向源图像的指针
	LPSTR	lpSrc;

	// 指向缓存图像的指针
	LPSTR	lpDst;

	// 指向缓存DIB图像的指针
	LPSTR	lpNewDIBBits;
	HLOCAL	hNewDIBBits;

	//循环变量
	long i;
	long j;
	int  n;
	int  m;

	//像素值
	unsigned char pixel;

	// 暂时分配内存，以保存新图像
	hNewDIBBits = LocalAlloc(LHND, lWidth * lHeight);

	if (hNewDIBBits == NULL)
	{
		// 分配内存失败
		return FALSE;
	}

	// 锁定内存
	lpNewDIBBits = (char*)LocalLock(hNewDIBBits);

	// 初始化新分配的内存，设定初始值为255
	lpDst = (char*)lpNewDIBBits;
	memset(lpDst, (BYTE)255, lWidth * lHeight);


	if (nMode == 0)
	{
		//使用水平方向的结构元素进行腐蚀
		for (j = 0; j < lHeight; j++)
		{
			for (i = 1; i < lWidth - 1; i++)
			{
				//由于使用1×3的结构元素，为防止越界，所以不处理最左边和最右边的两列像素

				// 指向源图像倒数第j行，第i个象素的指针			
				lpSrc = (char*)lpDIBBits + lWidth * j + i;

				// 指向目标图像倒数第j行，第i个象素的指针			
				lpDst = (char*)lpNewDIBBits + lWidth * j + i;

				//取得当前指针处的像素值，注意要转换为unsigned char型
				pixel = (unsigned char)*lpSrc;

				//目标图像中含有0和255外的其它灰度值
				if (pixel != 255 && *lpSrc != 0)
					return FALSE;

				//目标图像中的当前点先赋成黑色
				*lpDst = (unsigned char)0;

				//如果源图像中当前点自身或者左右有一个点不是黑色，
				//则将目标图像中的当前点赋成白色
				for (n = 0; n < 3; n++)
				{
					pixel = *(lpSrc + n - 1);
					if (pixel == 255)
					{
						*lpDst = (unsigned char)255;
						break;
					}
				}

			}
		}

	}
	else if (nMode == 1)
	{
		//使用垂直方向的结构元素进行腐蚀
		for (j = 1; j < lHeight - 1; j++)
		{
			for (i = 0; i < lWidth; i++)
			{
				//由于使用1×3的结构元素，为防止越界，所以不处理最上边和最下边的两列像素

				// 指向源图像倒数第j行，第i个象素的指针			
				lpSrc = (char*)lpDIBBits + lWidth * j + i;

				// 指向目标图像倒数第j行，第i个象素的指针			
				lpDst = (char*)lpNewDIBBits + lWidth * j + i;

				//取得当前指针处的像素值，注意要转换为unsigned char型
				pixel = (unsigned char)*lpSrc;

				//目标图像中含有0和255外的其它灰度值
				if (pixel != 255 && *lpSrc != 0)
					return FALSE;

				//目标图像中的当前点先赋成黑色
				*lpDst = (unsigned char)0;

				//如果源图像中当前点自身或者上下有一个点不是黑色，
				//则将目标图像中的当前点赋成白色
				for (n = 0; n < 3; n++)
				{
					pixel = *(lpSrc + (n - 1) * lWidth);
					if (pixel == 255)
					{
						*lpDst = (unsigned char)255;
						break;
					}
				}

			}
		}

	}
	else
	{
		//使用自定义的结构元素进行腐蚀
		for (j = 1; j < lHeight - 1; j++)
		{
			for (i = 0; i < lWidth; i++)
			{
				//由于使用3×3的结构元素，为防止越界，所以不处理最左边和最右边的两列像素
				//和最上边和最下边的两列像素
				// 指向源图像倒数第j行，第i个象素的指针			
				lpSrc = (char*)lpDIBBits + lWidth * j + i;

				// 指向目标图像倒数第j行，第i个象素的指针			
				lpDst = (char*)lpNewDIBBits + lWidth * j + i;

				//取得当前指针处的像素值，注意要转换为unsigned char型
				pixel = (unsigned char)*lpSrc;

				//目标图像中含有0和255外的其它灰度值
				if (pixel != 255 && *lpSrc != 0)
					return FALSE;

				//目标图像中的当前点先赋成黑色
				*lpDst = (unsigned char)0;

				//如果原图像中对应结构元素中为黑色的那些点中有一个不是黑色，
				//则将目标图像中的当前点赋成白色
				//注意在DIB图像中内容是上下倒置的
				for (m = 0; m < 3; m++)
				{
					for (n = 0; n < 3; n++)
					{
						if (structure[m][n] == -1)
							continue;
						pixel = *(lpSrc + ((2 - m) - 1) * lWidth + (n - 1));
						if (pixel == 255)
						{
							*lpDst = (unsigned char)255;
							break;
						}
					}
				}

			}
		}

	}
	// 复制腐蚀后的图像
	memcpy(lpDIBBits, lpNewDIBBits, lWidth * lHeight);

	// 重新初始化新分配的内存，设定初始值为255
	//lpDst = (char *)lpNewDIBBits;
	//memset(lpDst, (BYTE)255, lWidth * lHeight);


	if (nMode == 0)
	{
		//使用水平方向的结构元素进行膨胀
		for (j = 0; j < lHeight; j++)
		{
			for (i = 1; i < lWidth - 1; i++)
			{
				//由于使用1×3的结构元素，为防止越界，所以不处理最左边和最右边的两列像素

				// 指向源图像倒数第j行，第i个象素的指针			
				lpSrc = (char*)lpDIBBits + lWidth * j + i;

				// 指向目标图像倒数第j行，第i个象素的指针			
				lpDst = (char*)lpNewDIBBits + lWidth * j + i;

				//取得当前指针处的像素值，注意要转换为unsigned char型
				pixel = (unsigned char)*lpSrc;

				//目标图像中含有0和255外的其它灰度值
				if (pixel != 255 && *lpSrc != 0)
					return FALSE;

				//目标图像中的当前点先赋成白色
				*lpDst = (unsigned char)255;

				//源图像中当前点自身或者左右只要有一个点是黑色，
				//则将目标图像中的当前点赋成黑色
				for (n = 0; n < 3; n++)
				{
					pixel = *(lpSrc + n - 1);
					if (pixel == 0)
					{
						*lpDst = (unsigned char)0;
						break;
					}
				}

			}
		}

	}
	else if (nMode == 1)
	{
		//使用垂直方向的结构元素进行膨胀
		for (j = 1; j < lHeight - 1; j++)
		{
			for (i = 0; i < lWidth; i++)
			{
				//由于使用1×3的结构元素，为防止越界，所以不处理最上边和最下边的两列像素

				// 指向源图像倒数第j行，第i个象素的指针			
				lpSrc = (char*)lpDIBBits + lWidth * j + i;

				// 指向目标图像倒数第j行，第i个象素的指针			
				lpDst = (char*)lpNewDIBBits + lWidth * j + i;

				//取得当前指针处的像素值，注意要转换为unsigned char型
				pixel = (unsigned char)*lpSrc;

				//目标图像中含有0和255外的其它灰度值
				if (pixel != 255 && *lpSrc != 0)
					return FALSE;

				//目标图像中的当前点先赋成白色
				*lpDst = (unsigned char)255;

				//源图像中当前点自身或者上下只要有一个点是黑色，
				//则将目标图像中的当前点赋成黑色
				for (n = 0; n < 3; n++)
				{
					pixel = *(lpSrc + (n - 1) * lWidth);
					if (pixel == 0)
					{
						*lpDst = (unsigned char)0;
						break;
					}
				}

			}
		}

	}
	else
	{
		//使用自定义的结构元素进行膨胀
		for (j = 1; j < lHeight - 1; j++)
		{
			for (i = 0; i < lWidth; i++)
			{
				//由于使用3×3的结构元素，为防止越界，所以不处理最左边和最右边的两列像素
				//和最上边和最下边的两列像素
				// 指向源图像倒数第j行，第i个象素的指针			
				lpSrc = (char*)lpDIBBits + lWidth * j + i;

				// 指向目标图像倒数第j行，第i个象素的指针			
				lpDst = (char*)lpNewDIBBits + lWidth * j + i;

				//取得当前指针处的像素值，注意要转换为unsigned char型
				pixel = (unsigned char)*lpSrc;

				//目标图像中含有0和255外的其它灰度值
				if (pixel != 255 && *lpSrc != 0)
					return FALSE;

				//目标图像中的当前点先赋成白色
				*lpDst = (unsigned char)255;

				//原图像中对应结构元素中为黑色的那些点中只要有一个是黑色，
				//则将目标图像中的当前点赋成黑色
				//注意在DIB图像中内容是上下倒置的
				for (m = 0; m < 3; m++)
				{
					for (n = 0; n < 3; n++)
					{
						if (structure[m][n] == -1)
							continue;
						pixel = *(lpSrc + ((2 - m) - 1) * lWidth + (n - 1));
						if (pixel == 0)
						{
							*lpDst = (unsigned char)0;
							break;
						}
					}
				}

			}
		}

	}
	// 复制膨胀后的图像
	memcpy(lpDIBBits, lpNewDIBBits, lWidth * lHeight);

	// 释放内存
	LocalUnlock(hNewDIBBits);
	LocalFree(hNewDIBBits);


	return TRUE;
}

void CMFCApplication1View::OnOpen()
{
	// TODO: 在此添加命令处理程序代码
	CMFCApplication1Doc* pDoc = GetDocument();// 获取文档
////////////////////////////////////////////////////////////////////////////////////////////////	
	long	lSrcLineBytes;		//图象每行的字节数
	long	lSrcWidth;      //图象的宽度和高度
	long	lSrcHeight;
	int     lpSrcBitCount;       //图像的位深
	LPSTR	lpSrcDib;		//指向源图象的指针	
	LPSTR	lpSrcStartBits;	//指向源像素的指针
	lpSrcDib = (LPSTR) ::GlobalLock((HGLOBAL)pDoc->GetHObject());// 锁定DIB
	if (!lpSrcDib) return;

	if (pDoc->m_dib.GetColorNum(lpSrcDib) != 256)// 判断是否是8-bpp位图
	{
		AfxMessageBox(L"对不起，不是256色位图！");// 警告
		::GlobalUnlock((HGLOBAL)pDoc->GetHObject());// 解除锁定
		return;									//返回
	}										//判断是否是8-bpp位图,不是则返回

	lpSrcStartBits = pDoc->m_dib.GetBits(lpSrcDib);			// 找到DIB图象像素起始位置	
	lSrcWidth = pDoc->m_dib.GetWidth(lpSrcDib);					// 获取图象的宽度		
	lSrcHeight = pDoc->m_dib.GetHeight(lpSrcDib);					// 获取图象的高度	
	lpSrcBitCount = pDoc->m_dib.GetBitCount(lpSrcDib);                    //获取图像位深
	lSrcLineBytes = pDoc->m_dib.GetReqByteWidth(lSrcWidth * lpSrcBitCount);		// 计算图象每行的字节数
/////////////////////////////////////////////////////////////////////////////////////////////////
	CDlgOpen dlgPara;
	int nMode;
	dlgPara.m_nMode = 0;
	// 显示对话框，提示用户设定腐蚀方向
	if (dlgPara.DoModal() != IDOK)
	{
		// 返回
		return;
	}
	// 获取用户设定的腐蚀方向
	nMode = dlgPara.m_nMode;
	int structure[3][3];
	if (nMode == 2)
	{
		structure[0][0] = dlgPara.m_nStructure1;
		structure[0][1] = dlgPara.m_nStructure2;
		structure[0][2] = dlgPara.m_nStructure3;
		structure[1][0] = dlgPara.m_nStructure4;
		structure[1][1] = dlgPara.m_nStructure5;
		structure[1][2] = dlgPara.m_nStructure6;
		structure[2][0] = dlgPara.m_nStructure7;
		structure[2][1] = dlgPara.m_nStructure8;
		structure[2][2] = dlgPara.m_nStructure9;
	}
	// 删除对话框
	delete dlgPara;
	// 更改光标形状
	BeginWaitCursor();
	if (OpenDIB(lpSrcStartBits, WIDTHBYTES(lSrcWidth * 8), lSrcHeight, nMode, structure))
	{
		// 设置脏标记
		pDoc->SetModifiedFlag(TRUE);
		// 更新视图
		pDoc->UpdateAllViews(NULL);
	}
	::GlobalUnlock((HGLOBAL)pDoc->GetHObject());// 解除锁定
}

BOOL CloseDIB(LPSTR lpDIBBits, LONG lWidth, LONG lHeight, int nMode, int structure[3][3])
{
	if (DilationDIB(lpDIBBits, lWidth, lHeight, nMode, structure))
	{

		if (ErosionDIB(lpDIBBits, lWidth, lHeight, nMode, structure))
		{
			// 返回
			return TRUE;

		}
	}
	return FALSE;

	// 返回
	return TRUE;
}

void CMFCApplication1View::OnClose()
{
	// TODO: 在此添加命令处理程序代码
	CMFCApplication1Doc* pDoc = GetDocument();// 获取文档
////////////////////////////////////////////////////////////////////////////////////////////////	
	long	lSrcLineBytes;		//图象每行的字节数
	long	lSrcWidth;      //图象的宽度和高度
	long	lSrcHeight;
	int     lpSrcBitCount;       //图像的位深
	LPSTR	lpSrcDib;		//指向源图象的指针	
	LPSTR	lpSrcStartBits;	//指向源像素的指针
	lpSrcDib = (LPSTR) ::GlobalLock((HGLOBAL)pDoc->GetHObject());// 锁定DIB
	if (!lpSrcDib) return;

	if (pDoc->m_dib.GetColorNum(lpSrcDib) != 256)// 判断是否是8-bpp位图
	{
		AfxMessageBox(L"对不起，不是256色位图！");// 警告
		::GlobalUnlock((HGLOBAL)pDoc->GetHObject());// 解除锁定
		return;									//返回
	}										//判断是否是8-bpp位图,不是则返回

	lpSrcStartBits = pDoc->m_dib.GetBits(lpSrcDib);			// 找到DIB图象像素起始位置	
	lSrcWidth = pDoc->m_dib.GetWidth(lpSrcDib);					// 获取图象的宽度		
	lSrcHeight = pDoc->m_dib.GetHeight(lpSrcDib);					// 获取图象的高度	
	lpSrcBitCount = pDoc->m_dib.GetBitCount(lpSrcDib);                    //获取图像位深
	lSrcLineBytes = pDoc->m_dib.GetReqByteWidth(lSrcWidth * lpSrcBitCount);		// 计算图象每行的字节数
/////////////////////////////////////////////////////////////////////////////////////////////////
	CDlgClose dlgPara;
	int nMode;
	dlgPara.m_nMode = 0;
	// 显示对话框，提示用户设定腐蚀方向
	if (dlgPara.DoModal() != IDOK)
	{
		// 返回
		return;
	}
	// 获取用户设定的腐蚀方向
	nMode = dlgPara.m_nMode;
	int structure[3][3];
	if (nMode == 2)
	{
		structure[0][0] = dlgPara.m_nStructure1;
		structure[0][1] = dlgPara.m_nStructure2;
		structure[0][2] = dlgPara.m_nStructure3;
		structure[1][0] = dlgPara.m_nStructure4;
		structure[1][1] = dlgPara.m_nStructure5;
		structure[1][2] = dlgPara.m_nStructure6;
		structure[2][0] = dlgPara.m_nStructure7;
		structure[2][1] = dlgPara.m_nStructure8;
		structure[2][2] = dlgPara.m_nStructure9;
	}
	// 删除对话框
	delete dlgPara;
	// 更改光标形状
	BeginWaitCursor();
	if (CloseDIB(lpSrcStartBits, WIDTHBYTES(lSrcWidth * 8), lSrcHeight, nMode, structure))
	{
		// 设置脏标记
		pDoc->SetModifiedFlag(TRUE);
		// 更新视图
		pDoc->UpdateAllViews(NULL);
	}
	::GlobalUnlock((HGLOBAL)pDoc->GetHObject());// 解除锁定
}

BOOL WINAPI ThresholdTrans(LPSTR lpDIBBits, LONG lWidth, LONG lHeight, BYTE bThre)
{

	// 指向源图像的指针
	unsigned char* lpSrc;

	// 循环变量
	LONG	i;
	LONG	j;

	// 图像每行的字节数
	LONG	lLineBytes;

	// 计算图像每行的字节数
	lLineBytes = WIDTHBYTES(lWidth * 8);

	// 每行
	for (i = 0; i < lHeight; i++)
	{
		// 每列
		for (j = 0; j < lWidth; j++)
		{
			// 指向DIB第i行，第j个象素的指针
			lpSrc = (unsigned char*)lpDIBBits + lLineBytes * (lHeight - 1 - i) + j;

			// 判断是否小于阈值
			if ((*lpSrc) < bThre)
			{
				// 直接赋值为0
				*lpSrc = 0;
			}
			else
			{
				// 直接赋值为255
				*lpSrc = 255;
			}
		}
	}

	// 返回
	return TRUE;
}

void CMFCApplication1View::OnThreshold()
{
	// TODO: 在此添加命令处理程序代码
	CMFCApplication1Doc* pDoc = GetDocument();// 获取文档
////////////////////////////////////////////////////////////////////////////////////////////////	
	long	lSrcLineBytes;		//图象每行的字节数
	long	lSrcWidth;      //图象的宽度和高度
	long	lSrcHeight;
	int     lpSrcBitCount;       //图像的位深
	LPSTR	lpSrcDib;		//指向源图象的指针	
	LPSTR	lpSrcStartBits;	//指向源像素的指针
	lpSrcDib = (LPSTR) ::GlobalLock((HGLOBAL)pDoc->GetHObject());// 锁定DIB
	if (!lpSrcDib) return;

	if (pDoc->m_dib.GetColorNum(lpSrcDib) != 256)// 判断是否是8-bpp位图
	{
		AfxMessageBox(L"对不起，不是256色位图！");// 警告
		::GlobalUnlock((HGLOBAL)pDoc->GetHObject());// 解除锁定
		return;									//返回
	}										//判断是否是8-bpp位图,不是则返回

	lpSrcStartBits = pDoc->m_dib.GetBits(lpSrcDib);			// 找到DIB图象像素起始位置	
	lSrcWidth = pDoc->m_dib.GetWidth(lpSrcDib);					// 获取图象的宽度		
	lSrcHeight = pDoc->m_dib.GetHeight(lpSrcDib);					// 获取图象的高度	
	lpSrcBitCount = pDoc->m_dib.GetBitCount(lpSrcDib);                    //获取图像位深
	lSrcLineBytes = pDoc->m_dib.GetReqByteWidth(lSrcWidth * lpSrcBitCount);		// 计算图象每行的字节数
/////////////////////////////////////////////////////////////////////////////////////////////////
	CDlgThreshold dlgPara;
	BYTE	bThre;
	dlgPara.m_bThre = 128;
	if (dlgPara.DoModal() != IDOK)
	{
		// 返回
		return;
	}
	bThre = dlgPara.m_bThre;
	ThresholdTrans(lpSrcStartBits, lSrcWidth, lSrcHeight, bThre);
	// 设置脏标记
	pDoc->SetModifiedFlag(TRUE);
	// 更新视图
	pDoc->UpdateAllViews(NULL);
	::GlobalUnlock((HGLOBAL)pDoc->GetHObject());// 解除锁定
}

//迭代法
int ThresholdDIB(LPSTR lpDIBBits, LONG lWidth, LONG lHeight)
{

	// 指向源图像的指针
	LPSTR	lpSrc;

	// 指向缓存图像的指针
	LPSTR	lpDst;

	// 指向缓存DIB图像的指针
	LPSTR	lpNewDIBBits;
	HLOCAL	hNewDIBBits;

	//循环变量
	long i;
	long j;

	//像素值
	unsigned char pixel;

	//直方图数组
	long lHistogram[256];

	//阈值，最大灰度值与最小灰度值，两个区域的平均灰度值
	unsigned char iThreshold, iNewThreshold, iMaxGrayValue, iMinGrayValue, iMean1GrayValue, iMean2GrayValue;

	//用于计算区域灰度平均值的中间变量
	long lP1, lP2, lS1, lS2;

	//迭代次数
	int iIterationTimes;

	// 图像每行的字节数
	LONG lLineBytes;

	// 暂时分配内存，以保存新图像
	hNewDIBBits = LocalAlloc(LHND, lWidth * lHeight);

	if (hNewDIBBits == NULL)
	{
		// 分配内存失败
		return FALSE;
	}

	// 锁定内存
	lpNewDIBBits = (char*)LocalLock(hNewDIBBits);

	// 初始化新分配的内存，设定初始值为255
	lpDst = (char*)lpNewDIBBits;
	memset(lpDst, (BYTE)255, lWidth * lHeight);

	// 计算图像每行的字节数
	lLineBytes = WIDTHBYTES(lWidth * 8);

	for (i = 0; i < 256; i++)
	{
		lHistogram[i] = 0;
	}

	//获得直方图
	iMaxGrayValue = 0;
	iMinGrayValue = 255;
	for (i = 0; i < lWidth; i++)
	{
		for (j = 0; j < lHeight; j++)
		{
			// 指向源图像倒数第j行，第i个象素的指针			
			lpSrc = (char*)lpDIBBits + lLineBytes * j + i;

			pixel = (unsigned char)*lpSrc;

			lHistogram[pixel]++;
			//修改最大，最小灰度值
			if (iMinGrayValue > pixel)
			{
				iMinGrayValue = pixel;
			}
			if (iMaxGrayValue < pixel)
			{
				iMaxGrayValue = pixel;
			}
		}
	}

	//迭代求最佳阈值
	iNewThreshold = (iMinGrayValue + iMaxGrayValue) / 2;
	iThreshold = 0;

	for (iIterationTimes = 0; iThreshold != iNewThreshold && iIterationTimes < 100; iIterationTimes++)
	{
		iThreshold = iNewThreshold;
		lP1 = 0;
		lP2 = 0;
		lS1 = 0;
		lS2 = 0;
		//求两个区域的灰度平均值
		for (i = iMinGrayValue; i < iThreshold; i++)
		{
			lP1 += lHistogram[i] * i;
			lS1 += lHistogram[i];
		}
		iMean1GrayValue = (unsigned char)(lP1 / lS1);
		for (i = iThreshold + 1; i < iMaxGrayValue; i++)
		{
			lP2 += lHistogram[i] * i;
			lS2 += lHistogram[i];
		}
		iMean2GrayValue = (unsigned char)(lP2 / lS2);
		iNewThreshold = (iMean1GrayValue + iMean2GrayValue) / 2;
	}

	//根据阈值将图像二值化
	for (i = 0; i < lWidth; i++)
	{
		for (j = 0; j < lHeight; j++)
		{
			// 指向源图像倒数第j行，第i个象素的指针			
			lpSrc = (char*)lpDIBBits + lLineBytes * j + i;

			// 指向目标图像倒数第j行，第i个象素的指针			
			lpDst = (char*)lpNewDIBBits + lLineBytes * j + i;

			pixel = (unsigned char)*lpSrc;

			if (pixel <= iThreshold)
			{
				*lpDst = (unsigned char)0;
			}
			else
			{
				*lpDst = (unsigned char)255;
			}
		}
	}

	std::cout << iThreshold << std::endl;
	std::cout << iNewThreshold << std::endl;

	// 复制图像
	memcpy(lpDIBBits, lpNewDIBBits, lWidth * lHeight);

	// 释放内存
	LocalUnlock(hNewDIBBits);
	LocalFree(hNewDIBBits);

	// 返回
	return iNewThreshold;
}
//OTSU
int OTSU(LPSTR lpDIBBits, LONG lWidth, LONG lHeight)
{
	// 指向源图像的指针
	LPSTR	lpSrc;

	// 指向缓存图像的指针
	LPSTR	lpDst;

	// 指向缓存DIB图像的指针
	LPSTR	lpNewDIBBits;
	HLOCAL	hNewDIBBits;

	//循环变量
	long i;
	long j;

	//像素值
	unsigned char pixel;

	//直方图数组
	long lHistogram[256];

	//阈值，最大灰度值与最小灰度值，两个区域的平均灰度值
	unsigned char iThreshold, iNewThreshold, iMaxGrayValue, iMinGrayValue, iMean1GrayValue, iMean2GrayValue;

	// 图像每行的字节数
	LONG lLineBytes;

	// 暂时分配内存，以保存新图像
	hNewDIBBits = LocalAlloc(LHND, lWidth * lHeight);

	if (hNewDIBBits == NULL)
	{
		// 分配内存失败
		return FALSE;
	}

	// 锁定内存
	lpNewDIBBits = (char*)LocalLock(hNewDIBBits);

	// 初始化新分配的内存，设定初始值为255
	lpDst = (char*)lpNewDIBBits;
	memset(lpDst, (BYTE)255, lWidth * lHeight);

	// 计算图像每行的字节数
	lLineBytes = WIDTHBYTES(lWidth * 8);

	for (i = 0; i < 256; i++)
	{
		lHistogram[i] = 0;
	}

	//获得直方图
	iMaxGrayValue = 0;
	iMinGrayValue = 255;
	for (i = 0; i < lWidth; i++)
	{
		for (j = 0; j < lHeight; j++)
		{
			// 指向源图像倒数第j行，第i个象素的指针			
			lpSrc = (char*)lpDIBBits + lLineBytes * j + i;

			pixel = (unsigned char)*lpSrc;

			lHistogram[pixel]++;
			//修改最大，最小灰度值
			if (iMinGrayValue > pixel)
			{
				iMinGrayValue = pixel;
			}
			if (iMaxGrayValue < pixel)
			{
				iMaxGrayValue = pixel;
			}
		}
	}

	double sumIntensity = 0.0;
	for (int k = iMinGrayValue; k <= iMaxGrayValue; k++)
	{
		sumIntensity += (double)k * (double)lHistogram[k];
	}

	int thrIntensity = 1;
	double otsu = -1.0;
	int w0 = 0;//小于等于当前阈值的点数（前景点数）
	double sumFore = 0.0;//前景质量矩
	for (int k = iMinGrayValue; k <= iMaxGrayValue; k++)
	{
		w0 += lHistogram[k];
		int w1 = lWidth * lHeight - w0;//（后景点数）
		if (w0 == 0)
			continue;
		if (w1 == 0)
			break;

		sumFore += (double)k * lHistogram[k];

		double u0 = sumFore / w0; //前景的平均灰度
		double u1 = (sumIntensity - sumFore) / w1; //背景的平均灰度
		double g = (double)w0 * (double)w1 * (u0 - u1) * (u0 - u1); //类间方差

		if (g > otsu)
		{
			otsu = g;
			thrIntensity = k;
		}
	}

	//根据阈值将图像二值化
	for (i = 0; i < lWidth; i++)
	{
		for (j = 0; j < lHeight; j++)
		{
			// 指向源图像倒数第j行，第i个象素的指针			
			lpSrc = (char*)lpDIBBits + lLineBytes * j + i;

			// 指向目标图像倒数第j行，第i个象素的指针			
			lpDst = (char*)lpNewDIBBits + lLineBytes * j + i;

			pixel = (unsigned char)*lpSrc;

			if (pixel <= thrIntensity)
			{
				*lpDst = (unsigned char)0;
			}
			else
			{
				*lpDst = (unsigned char)255;
			}
		}
	}
	std::cout << thrIntensity << std::endl;
	// 复制图像
	memcpy(lpDIBBits, lpNewDIBBits, lWidth * lHeight);

	// 释放内存
	LocalUnlock(hNewDIBBits);
	LocalFree(hNewDIBBits);

	// 返回
	return thrIntensity;
}
//最大最小
int MaximumEntropy(LPSTR lpDIBBits, LONG lWidth, LONG lHeight) {
	// 指向源图像的指针
	LPSTR	lpSrc;

	// 指向缓存图像的指针
	LPSTR	lpDst;

	// 指向缓存DIB图像的指针
	LPSTR	lpNewDIBBits;
	HLOCAL	hNewDIBBits;

	//循环变量
	long i;
	long j;

	//像素值
	unsigned char pixel;

	//直方图数组
	long lHistogram[256];

	//阈值，最大灰度值与最小灰度值，两个区域的平均灰度值
	unsigned char iThreshold, iNewThreshold, iMean1GrayValue, iMean2GrayValue;

	// 图像每行的字节数
	LONG lLineBytes;

	// 暂时分配内存，以保存新图像
	hNewDIBBits = LocalAlloc(LHND, lWidth * lHeight);

	if (hNewDIBBits == NULL)
	{
		// 分配内存失败
		return FALSE;
	}

	// 锁定内存
	lpNewDIBBits = (char*)LocalLock(hNewDIBBits);

	// 初始化新分配的内存，设定初始值为255
	lpDst = (char*)lpNewDIBBits;
	memset(lpDst, (BYTE)255, lWidth * lHeight);

	// 计算图像每行的字节数
	lLineBytes = WIDTHBYTES(lWidth * 8);

	for (i = 0; i < 256; i++)
	{
		lHistogram[i] = 0;
	}

	int tbHist[256] = { 0 };

	for (i = 0; i < lWidth; i++)
	{
		for (j = 0; j < lHeight; j++)
		{
			// 指向源图像倒数第j行，第i个象素的指针			
			lpSrc = (char*)lpDIBBits + lLineBytes * j + i;

			pixel = (unsigned char)*lpSrc;

			lHistogram[pixel]++;
			//修改最大，最小灰度值
		}
	}
	double probability = 0.0; //概率
	double maxEntropy = DBL_MIN; //最大熵
	int totalpix = lWidth * lHeight;
	int thresh = 0;
	for (int i = 0; i < 256; ++i)
	{
		//计算背景像素数
		double backgroundpix = 0;
		for (int j = 0; j <= i; ++j)
			backgroundpix += lHistogram[j];
		//计算背景熵
		double H0 = 0.0; //背景熵
		if (backgroundpix > 0)
		{
			for (int j = 0; j <= i; ++j)
			{
				probability = lHistogram[j] / backgroundpix;
				if (probability > 0.00001)
					H0 += -probability * log(probability);
			}
		}

		//计算前景像素数
		double frontpix = totalpix - backgroundpix;
		//计算前景熵
		double H1 = 0.0; //前景熵
		if (frontpix > 0)
		{
			for (int k = i + 1; k < 256; ++k)
			{
				probability = lHistogram[k] / frontpix;
				if (probability > 0.00001)
					H1 += -probability * log(probability);
			}
		}

		//计算最大熵
		if (H0 + H1 > maxEntropy)
		{
			maxEntropy = H0 + H1;
			thresh = i;
		}
	}

	std::cout << thresh << std::endl;
	//根据阈值将图像二值化
	for (i = 0; i < lWidth; i++)
	{
		for (j = 0; j < lHeight; j++)
		{
			// 指向源图像倒数第j行，第i个象素的指针			
			lpSrc = (char*)lpDIBBits + lLineBytes * j + i;

			// 指向目标图像倒数第j行，第i个象素的指针			
			lpDst = (char*)lpNewDIBBits + lLineBytes * j + i;

			pixel = (unsigned char)*lpSrc;

			if (pixel <= thresh)
			{
				*lpDst = (unsigned char)0;
			}
			else
			{
				*lpDst = (unsigned char)255;
			}
		}
	}

	// 复制图像
	memcpy(lpDIBBits, lpNewDIBBits, lWidth * lHeight);

	// 释放内存
	LocalUnlock(hNewDIBBits);
	LocalFree(hNewDIBBits);

	// 返回
	return thresh;
}
//自适应
int Adaptive(LPSTR lpDIBBits, LONG lWidth, LONG lHeight) {
	// 指向源图像的指针
	LPSTR	lpSrc;

	// 指向缓存图像的指针
	LPSTR	lpDst;

	// 指向缓存DIB图像的指针
	LPSTR	lpNewDIBBits;
	HLOCAL	hNewDIBBits;

	//循环变量
	long i;
	long j;

	//像素值
	unsigned char pixel;

	//直方图数组
	long lHistogram[256];

	//阈值，最大灰度值与最小灰度值，两个区域的平均灰度值
	unsigned char iMean1GrayValue, iMean2GrayValue;

	//用于计算区域灰度平均值的中间变量
	long lP1, lP2, lS1, lS2;

	//迭代次数
	int iIterationTimes;

	// 图像每行的字节数
	LONG lLineBytes;

	// 暂时分配内存，以保存新图像
	hNewDIBBits = LocalAlloc(LHND, lWidth * lHeight);

	if (hNewDIBBits == NULL)
	{
		// 分配内存失败
		return FALSE;
	}

	// 锁定内存
	lpNewDIBBits = (char*)LocalLock(hNewDIBBits);

	// 初始化新分配的内存，设定初始值为255
	lpDst = (char*)lpNewDIBBits;
	memset(lpDst, (BYTE)255, lWidth * lHeight);

	// 计算图像每行的字节数
	lLineBytes = WIDTHBYTES(lWidth * 8);

	for (i = 0; i < 256; i++)
	{
		lHistogram[i] = 0;
	}

	unsigned char iThreshold1;
	unsigned char iNewThreshold1;
	unsigned char iMaxGrayValue1 = 0;
	unsigned char iMinGrayValue1 = 255;

	for (i = 0; i < lWidth / 2; i++)
	{
		for (j = 0; j < lHeight / 2; j++)
		{
			// 指向源图像倒数第j行，第i个象素的指针			
			lpSrc = (char*)lpDIBBits + lLineBytes * j + i;

			pixel = (unsigned char)*lpSrc;

			lHistogram[pixel]++;
			//修改最大，最小灰度值
			if (iMinGrayValue1 > pixel)
			{
				iMinGrayValue1 = pixel;
			}
			if (iMaxGrayValue1 < pixel)
			{
				iMaxGrayValue1 = pixel;
			}
		}
	}

	//迭代求最佳阈值
	iNewThreshold1 = (iMinGrayValue1 + iMaxGrayValue1) / 2;
	iThreshold1 = 0;

	for (iIterationTimes = 0; iThreshold1 != iNewThreshold1 && iIterationTimes < 100; iIterationTimes++)
	{
		iThreshold1 = iNewThreshold1;
		lP1 = 0;
		lP2 = 0;
		lS1 = 0;
		lS2 = 0;
		//求两个区域的灰度平均值
		for (i = iMinGrayValue1; i < iThreshold1; i++)
		{
			lP1 += lHistogram[i] * i;
			lS1 += lHistogram[i];
		}
		iMean1GrayValue = (unsigned char)(lP1 / lS1);
		for (i = iThreshold1 + 1; i < iMaxGrayValue1; i++)
		{
			lP2 += lHistogram[i] * i;
			lS2 += lHistogram[i];
		}
		iMean2GrayValue = (unsigned char)(lP2 / lS2);
		iNewThreshold1 = (iMean1GrayValue + iMean2GrayValue) / 2;
	}

	unsigned char iThreshold2;
	unsigned char iNewThreshold2;
	unsigned char iMaxGrayValue2 = 0;
	unsigned char iMinGrayValue2 = 255;

	for (i = lWidth / 2; i < lWidth; i++)
	{
		for (j = 0; j < lHeight / 2; j++)
		{
			// 指向源图像倒数第j行，第i个象素的指针			
			lpSrc = (char*)lpDIBBits + lLineBytes * j + i;

			pixel = (unsigned char)*lpSrc;

			lHistogram[pixel]++;
			//修改最大，最小灰度值
			if (iMinGrayValue2 > pixel)
			{
				iMinGrayValue2 = pixel;
			}
			if (iMaxGrayValue2 < pixel)
			{
				iMaxGrayValue2 = pixel;
			}
		}
	}

	//迭代求最佳阈值
	iNewThreshold2 = (iMinGrayValue2 + iMaxGrayValue2) / 2;
	iThreshold2 = 0;

	for (iIterationTimes = 0; iThreshold2 != iNewThreshold2 && iIterationTimes < 100; iIterationTimes++)
	{
		iThreshold2 = iNewThreshold2;
		lP1 = 0;
		lP2 = 0;
		lS1 = 0;
		lS2 = 0;
		//求两个区域的灰度平均值
		for (i = iMinGrayValue2; i < iThreshold2; i++)
		{
			lP1 += lHistogram[i] * i;
			lS1 += lHistogram[i];
		}
		iMean1GrayValue = (unsigned char)(lP1 / lS1);
		for (i = iThreshold2 + 1; i < iMaxGrayValue2; i++)
		{
			lP2 += lHistogram[i] * i;
			lS2 += lHistogram[i];
		}
		iMean2GrayValue = (unsigned char)(lP2 / lS2);
		iNewThreshold2 = (iMean1GrayValue + iMean2GrayValue) / 2;
	}

	unsigned char iThreshold3;
	unsigned char iNewThreshold3;
	unsigned char iMaxGrayValue3 = 0;
	unsigned char iMinGrayValue3 = 255;

	for (i = 0; i < lWidth / 2; i++)
	{
		for (j = lHeight / 2; j < lHeight; j++)
		{
			// 指向源图像倒数第j行，第i个象素的指针			
			lpSrc = (char*)lpDIBBits + lLineBytes * j + i;

			pixel = (unsigned char)*lpSrc;

			lHistogram[pixel]++;
			//修改最大，最小灰度值
			if (iMinGrayValue3 > pixel)
			{
				iMinGrayValue3 = pixel;
			}
			if (iMaxGrayValue3 < pixel)
			{
				iMaxGrayValue3 = pixel;
			}
		}
	}

	//迭代求最佳阈值
	iNewThreshold3 = (iMinGrayValue3 + iMaxGrayValue3) / 2;
	iThreshold3 = 0;

	for (iIterationTimes = 0; iThreshold3 != iNewThreshold3 && iIterationTimes < 100; iIterationTimes++)
	{
		iThreshold3 = iNewThreshold3;
		lP1 = 0;
		lP2 = 0;
		lS1 = 0;
		lS2 = 0;
		//求两个区域的灰度平均值
		for (i = iMinGrayValue3; i < iThreshold3; i++)
		{
			lP1 += lHistogram[i] * i;
			lS1 += lHistogram[i];
		}
		iMean1GrayValue = (unsigned char)(lP1 / lS1);
		for (i = iThreshold3 + 1; i < iMaxGrayValue3; i++)
		{
			lP2 += lHistogram[i] * i;
			lS2 += lHistogram[i];
		}
		iMean2GrayValue = (unsigned char)(lP2 / lS2);
		iNewThreshold3 = (iMean1GrayValue + iMean2GrayValue) / 2;
	}

	unsigned char iThreshold4;
	unsigned char iNewThreshold4;
	unsigned char iMaxGrayValue4 = 0;
	unsigned char iMinGrayValue4 = 255;

	for (i = lWidth / 2; i < lWidth; i++)
	{
		for (j = lHeight / 2; j < lHeight; j++)
		{
			// 指向源图像倒数第j行，第i个象素的指针			
			lpSrc = (char*)lpDIBBits + lLineBytes * j + i;

			pixel = (unsigned char)*lpSrc;

			lHistogram[pixel]++;
			//修改最大，最小灰度值
			if (iMinGrayValue4 > pixel)
			{
				iMinGrayValue4 = pixel;
			}
			if (iMaxGrayValue4 < pixel)
			{
				iMaxGrayValue4 = pixel;
			}
		}
	}

	//迭代求最佳阈值
	iNewThreshold4 = (iMinGrayValue4 + iMaxGrayValue4) / 2;
	iThreshold4 = 0;

	for (iIterationTimes = 0; iThreshold4 != iNewThreshold4 && iIterationTimes < 100; iIterationTimes++)
	{
		iThreshold4 = iNewThreshold4;
		lP1 = 0;
		lP2 = 0;
		lS1 = 0;
		lS2 = 0;
		//求两个区域的灰度平均值
		for (i = iMinGrayValue4; i < iThreshold4; i++)
		{
			lP1 += lHistogram[i] * i;
			lS1 += lHistogram[i];
		}
		iMean1GrayValue = (unsigned char)(lP1 / lS1);
		for (i = iThreshold4 + 1; i < iMaxGrayValue4; i++)
		{
			lP2 += lHistogram[i] * i;
			lS2 += lHistogram[i];
		}
		iMean2GrayValue = (unsigned char)(lP2 / lS2);
		iNewThreshold4 = (iMean1GrayValue + iMean2GrayValue) / 2;
	}
	unsigned char iNewThreshold_up, iNewThreshold_down, iNewThreshold_final;
	iNewThreshold_up = (iNewThreshold1 + iNewThreshold2) / 2;
	iNewThreshold_down = (iNewThreshold3 + iNewThreshold4) / 2;
	iNewThreshold_final = (iNewThreshold_up + iNewThreshold_down) / 2;

	for (i = 0; i < lWidth; i++)
	{
		for (j = 0; j < lHeight; j++)
		{
			// 指向源图像倒数第j行，第i个象素的指针			
			lpSrc = (char*)lpDIBBits + lLineBytes * j + i;

			// 指向目标图像倒数第j行，第i个象素的指针			
			lpDst = (char*)lpNewDIBBits + lLineBytes * j + i;

			pixel = (unsigned char)*lpSrc;

			if (pixel <= iNewThreshold_final)
			{
				*lpDst = (unsigned char)0;
			}
			else
			{
				*lpDst = (unsigned char)255;
			}
		}
	}
	// 复制图像
	memcpy(lpDIBBits, lpNewDIBBits, lWidth * lHeight);

	// 释放内存
	LocalUnlock(hNewDIBBits);
	LocalFree(hNewDIBBits);
	return iNewThreshold_final;
}

void CMFCApplication1View::OnThresholdchange()
{
	// TODO: 在此添加命令处理程序代码
	CMFCApplication1Doc* pDoc = GetDocument();// 获取文档
////////////////////////////////////////////////////////////////////////////////////////////////	
	long	lSrcLineBytes;		//图象每行的字节数
	long	lSrcWidth;      //图象的宽度和高度
	long	lSrcHeight;
	int     lpSrcBitCount;       //图像的位深
	LPSTR	lpSrcDib;		//指向源图象的指针	
	LPSTR	lpSrcStartBits;	//指向源像素的指针
	lpSrcDib = (LPSTR) ::GlobalLock((HGLOBAL)pDoc->GetHObject());// 锁定DIB
	if (!lpSrcDib) return;

	//if (pDoc->m_dib.GetColorNum(lpSrcDib) != 256)// 判断是否是8-bpp位图
	//{
	//	AfxMessageBox(L"对不起，不是256色位图！");// 警告
	//	::GlobalUnlock((HGLOBAL)pDoc->GetHObject());// 解除锁定
	//	return;									//返回
	//}										//判断是否是8-bpp位图,不是则返回

	lpSrcStartBits = pDoc->m_dib.GetBits(lpSrcDib);			// 找到DIB图象像素起始位置	
	lSrcWidth = pDoc->m_dib.GetWidth(lpSrcDib);					// 获取图象的宽度		
	lSrcHeight = pDoc->m_dib.GetHeight(lpSrcDib);					// 获取图象的高度	
	lpSrcBitCount = pDoc->m_dib.GetBitCount(lpSrcDib);                    //获取图像位深
	lSrcLineBytes = pDoc->m_dib.GetReqByteWidth(lSrcWidth * lpSrcBitCount);		// 计算图象每行的字节数
/////////////////////////////////////////////////////////////////////////////////////////////////
	int type;
	CDlgThreshold dlgPara;
	BYTE	bThre;
	dlgPara.m_bThre = 128;
	if (dlgPara.DoModal() != IDOK)
	{
		// 返回
		return;
	}
	bThre = dlgPara.m_bThre;
	if (dlgPara.m_Type == 0) {
		bThre = ThresholdDIB(lpSrcStartBits, lSrcWidth, lSrcHeight);
	}
	else if (dlgPara.m_Type == 1) {
		bThre = OTSU(lpSrcStartBits, lSrcWidth, lSrcHeight);
		ThresholdTrans(lpSrcStartBits, lSrcWidth, lSrcHeight, bThre);
	}	
	else if (dlgPara.m_Type == 2) {
		bThre = MaximumEntropy(lpSrcStartBits, lSrcWidth, lSrcHeight);
		ThresholdTrans(lpSrcStartBits, lSrcWidth, lSrcHeight, bThre);
	}
	else if (dlgPara.m_Type == 3) { 
		bThre = Adaptive(lpSrcStartBits, lSrcWidth, lSrcHeight);
		ThresholdTrans(lpSrcStartBits, lSrcWidth, lSrcHeight, bThre);
	}
	else if (dlgPara.m_Type == 4) {
		bThre = dlgPara.m_bThre;
		ThresholdTrans(lpSrcStartBits, lSrcWidth, lSrcHeight, bThre);
	}
	pDoc->SetModifiedFlag(TRUE);
	// 更新视图
	pDoc->UpdateAllViews(NULL);
	::GlobalUnlock((HGLOBAL)pDoc->GetHObject());// 解除锁定
}

BOOL WindowTrans(LPSTR lpDIBBits, LONG lWidth, LONG lHeight, BYTE bLow, BYTE bUp)
{

	// 指向源图像的指针
	unsigned char* lpSrc;

	// 循环变量
	LONG	i;
	LONG	j;

	// 图像每行的字节数
	LONG	lLineBytes;

	// 计算图像每行的字节数
	lLineBytes = WIDTHBYTES(lWidth * 8);

	// 每行
	for (i = 0; i < lHeight; i++)
	{
		// 每列
		for (j = 0; j < lWidth; j++)
		{
			// 指向DIB第i行，第j个象素的指针
			lpSrc = (unsigned char*)lpDIBBits + lLineBytes * (lHeight - 1 - i) + j;

			// 判断是否超出范围
			if ((*lpSrc) < bLow)
			{
				// 直接赋值为0
				*lpSrc = 0;
			}
			else if ((*lpSrc) > bUp)
			{
				// 直接赋值为255
				*lpSrc = 255;
			}
		}
	}

	// 返回
	return TRUE;
}

void CMFCApplication1View::OnWindowtransform()
{
	// TODO: 在此添加命令处理程序代码
	CMFCApplication1Doc* pDoc = GetDocument();// 获取文档
////////////////////////////////////////////////////////////////////////////////////////////////	
	long	lSrcLineBytes;		//图象每行的字节数
	long	lSrcWidth;      //图象的宽度和高度
	long	lSrcHeight;
	int     lpSrcBitCount;       //图像的位深
	LPSTR	lpSrcDib;		//指向源图象的指针	
	LPSTR	lpSrcStartBits;	//指向源像素的指针
	lpSrcDib = (LPSTR) ::GlobalLock((HGLOBAL)pDoc->GetHObject());// 锁定DIB
	if (!lpSrcDib) return;

	if (pDoc->m_dib.GetColorNum(lpSrcDib) != 256)// 判断是否是8-bpp位图
	{
		AfxMessageBox(L"对不起，不是256色位图！");// 警告
		::GlobalUnlock((HGLOBAL)pDoc->GetHObject());// 解除锁定
		return;									//返回
	}										//判断是否是8-bpp位图,不是则返回

	lpSrcStartBits = pDoc->m_dib.GetBits(lpSrcDib);			// 找到DIB图象像素起始位置	
	lSrcWidth = pDoc->m_dib.GetWidth(lpSrcDib);					// 获取图象的宽度		
	lSrcHeight = pDoc->m_dib.GetHeight(lpSrcDib);					// 获取图象的高度	
	lpSrcBitCount = pDoc->m_dib.GetBitCount(lpSrcDib);                    //获取图像位深
	lSrcLineBytes = pDoc->m_dib.GetReqByteWidth(lSrcWidth * lpSrcBitCount);		// 计算图象每行的字节数
/////////////////////////////////////////////////////////////////////////////////////////////////
	CDlgWindowTransform dlgPara;
	// 窗口下限
	BYTE	bLow;
	// 窗口上限
	BYTE	bUp;
	// 初始化变量值
	dlgPara.m_bLow = 0;
	dlgPara.m_bUp = 255;
	// 显示对话框，提示用户设定窗口上下限
	if (dlgPara.DoModal() != IDOK)
	{
		// 返回
		return;
	}
	// 获取用户设定的窗口上下限
	bLow = dlgPara.m_bLow;
	bUp = dlgPara.m_bUp;
	WindowTrans(lpSrcStartBits, lSrcWidth, lSrcHeight, bLow, bUp);
	pDoc->SetModifiedFlag(TRUE);
	// 更新视图
	pDoc->UpdateAllViews(NULL);
	::GlobalUnlock((HGLOBAL)pDoc->GetHObject());// 解除锁定
}

BOOL GrayStretch1(LPSTR lpDIBBits, LONG lWidth, LONG lHeight, BYTE bX1, BYTE bY1, BYTE bX2, BYTE bY2)
{

	// 指向源图像的指针
	unsigned char* lpSrc;

	// 循环变量
	LONG	i;
	LONG	j;

	// 灰度映射表
	BYTE	bMap[256];

	// 图像每行的字节数
	LONG	lLineBytes;

	// 计算图像每行的字节数
	lLineBytes = WIDTHBYTES(lWidth * 8);

	// 计算灰度映射表
	for (i = 0; i <= bX1; i++)
	{
		// 判断bX1是否大于0（防止分母为0）
		if (bX1 > 0)
		{
			// 线性变换
			bMap[i] = (BYTE)bY1 * i / bX1;
		}
		else
		{
			// 直接赋值为0
			bMap[i] = 0;
		}
	}
	for (; i <= bX2; i++)
	{
		// 判断bX1是否等于bX2（防止分母为0）
		if (bX2 != bX1)
		{
			// 线性变换
			bMap[i] = bY1 + (BYTE)((bY2 - bY1) * (i - bX1) / (bX2 - bX1));
		}
		else
		{
			// 直接赋值为bY1
			bMap[i] = bY1;
		}
	}
	for (; i < 256; i++)
	{
		// 判断bX2是否等于255（防止分母为0）
		if (bX2 != 255)
		{
			// 线性变换
			bMap[i] = bY2 + (BYTE)((255 - bY2) * (i - bX2) / (255 - bX2));
		}
		else
		{
			// 直接赋值为255
			bMap[i] = 255;
		}
	}

	// 每行
	for (i = 0; i < lHeight; i++)
	{
		// 每列
		for (j = 0; j < lWidth; j++)
		{
			// 指向DIB第i行，第j个象素的指针
			lpSrc = (unsigned char*)lpDIBBits + lLineBytes * (lHeight - 1 - i) + j;

			// 计算新的灰度值
			*lpSrc = bMap[*lpSrc];
		}
	}

	// 返回
	return TRUE;
}

void CMFCApplication1View::OnGraystretch()
{
	// TODO: 在此添加命令处理程序代码
	CMFCApplication1Doc* pDoc = GetDocument();// 获取文档
////////////////////////////////////////////////////////////////////////////////////////////////	
	long	lSrcLineBytes;		//图象每行的字节数
	long	lSrcWidth;      //图象的宽度和高度
	long	lSrcHeight;
	int     lpSrcBitCount;       //图像的位深
	LPSTR	lpSrcDib;		//指向源图象的指针	
	LPSTR	lpSrcStartBits;	//指向源像素的指针
	lpSrcDib = (LPSTR) ::GlobalLock((HGLOBAL)pDoc->GetHObject());// 锁定DIB
	if (!lpSrcDib) return;

	if (pDoc->m_dib.GetColorNum(lpSrcDib) != 256)// 判断是否是8-bpp位图
	{
		AfxMessageBox(L"对不起，不是256色位图！");// 警告
		::GlobalUnlock((HGLOBAL)pDoc->GetHObject());// 解除锁定
		return;									//返回
	}										//判断是否是8-bpp位图,不是则返回

	lpSrcStartBits = pDoc->m_dib.GetBits(lpSrcDib);			// 找到DIB图象像素起始位置	
	lSrcWidth = pDoc->m_dib.GetWidth(lpSrcDib);					// 获取图象的宽度		
	lSrcHeight = pDoc->m_dib.GetHeight(lpSrcDib);					// 获取图象的高度	
	lpSrcBitCount = pDoc->m_dib.GetBitCount(lpSrcDib);                    //获取图像位深
	lSrcLineBytes = pDoc->m_dib.GetReqByteWidth(lSrcWidth * lpSrcBitCount);		// 计算图象每行的字节数
/////////////////////////////////////////////////////////////////////////////////////////////////
	CDlgGrayStretch dlgPara;
	// 点1坐标
	BYTE	bX1;
	BYTE	bY1;
	// 点2坐标
	BYTE	bX2;
	BYTE	bY2;
	// 初始化变量值
	dlgPara.m_bX1 = 50;
	dlgPara.m_bY1 = 30;
	dlgPara.m_bX2 = 200;
	dlgPara.m_bY2 = 220;
	// 显示对话框，提示用户设定拉伸位置
	if (dlgPara.DoModal() != IDOK)
	{
		// 返回
		return;
	}
	// 获取用户的设定
	bX1 = dlgPara.m_bX1;
	bY1 = dlgPara.m_bY1;
	bX2 = dlgPara.m_bX2;
	bY2 = dlgPara.m_bY2;
	GrayStretch1(lpSrcStartBits, lSrcWidth, lSrcHeight, bX1, bY1, bX2, bY2);
	pDoc->SetModifiedFlag(TRUE);
	// 更新视图
	pDoc->UpdateAllViews(NULL);
	::GlobalUnlock((HGLOBAL)pDoc->GetHObject());// 解除锁定
}

BOOL WINAPI InteEqualize(LPSTR lpDIBBits, LONG lWidth, LONG lHeight)
{

	// 指向源图像的指针
	unsigned char* lpSrc;

	// 临时变量
	LONG	lTemp;

	// 循环变量
	LONG	i;
	LONG	j;

	// 灰度映射表
	BYTE	bMap[256];

	// 灰度映射表
	LONG	lCount[256];

	// 图像每行的字节数
	LONG	lLineBytes;

	// 计算图像每行的字节数
	lLineBytes = WIDTHBYTES(lWidth * 8);

	// 重置计数为0
	for (i = 0; i < 256; i++)
	{
		// 清零
		lCount[i] = 0;
	}

	// 计算各个灰度值的计数
	for (i = 0; i < lHeight; i++)
	{
		for (j = 0; j < lWidth; j++)
		{
			lpSrc = (unsigned char*)lpDIBBits + lLineBytes * i + j;

			// 计数加1
			lCount[*(lpSrc)]++;
		}
	}

	// 计算灰度映射表
	for (i = 0; i < 256; i++)
	{
		// 初始为0
		lTemp = 0;

		for (j = 0; j <= i; j++)
		{
			lTemp += lCount[j];
		}

		// 计算对应的新灰度值
		bMap[i] = (BYTE)(lTemp * 255 / lHeight / lWidth);
	}

	// 每行
	for (i = 0; i < lHeight; i++)
	{
		// 每列
		for (j = 0; j < lWidth; j++)
		{
			// 指向DIB第i行，第j个象素的指针
			lpSrc = (unsigned char*)lpDIBBits + lLineBytes * (lHeight - 1 - i) + j;

			// 计算新的灰度值
			*lpSrc = bMap[*lpSrc];
		}
	}

	// 返回
	return TRUE;
}

void CMFCApplication1View::OnEqualization()
{
	// TODO: 在此添加命令处理程序代码
	CMFCApplication1Doc* pDoc = GetDocument();// 获取文档
////////////////////////////////////////////////////////////////////////////////////////////////	
	long	lSrcLineBytes;		//图象每行的字节数
	long	lSrcWidth;      //图象的宽度和高度
	long	lSrcHeight;
	int     lpSrcBitCount;       //图像的位深
	LPSTR	lpSrcDib;		//指向源图象的指针	
	LPSTR	lpSrcStartBits;	//指向源像素的指针
	lpSrcDib = (LPSTR) ::GlobalLock((HGLOBAL)pDoc->GetHObject());// 锁定DIB
	if (!lpSrcDib) return;

	if (pDoc->m_dib.GetColorNum(lpSrcDib) != 256)// 判断是否是8-bpp位图
	{
		AfxMessageBox(L"对不起，不是256色位图！");// 警告
		::GlobalUnlock((HGLOBAL)pDoc->GetHObject());// 解除锁定
		return;									//返回
	}										//判断是否是8-bpp位图,不是则返回

	lpSrcStartBits = pDoc->m_dib.GetBits(lpSrcDib);			// 找到DIB图象像素起始位置	
	lSrcWidth = pDoc->m_dib.GetWidth(lpSrcDib);					// 获取图象的宽度		
	lSrcHeight = pDoc->m_dib.GetHeight(lpSrcDib);					// 获取图象的高度	
	lpSrcBitCount = pDoc->m_dib.GetBitCount(lpSrcDib);                    //获取图像位深
	lSrcLineBytes = pDoc->m_dib.GetReqByteWidth(lSrcWidth * lpSrcBitCount);		// 计算图象每行的字节数
/////////////////////////////////////////////////////////////////////////////////////////////////
	InteEqualize(lpSrcStartBits, lSrcWidth, lSrcHeight);
	pDoc->SetModifiedFlag(TRUE);
	// 更新视图
	pDoc->UpdateAllViews(NULL);
	::GlobalUnlock((HGLOBAL)pDoc->GetHObject());// 解除锁定
}

BOOL TranslationDIB1(LPSTR lpDIBBits, LONG lWidth, LONG lHeight, LONG lXOffset, LONG lYOffset)
{
	// 指向源图像的指针
	LPSTR	lpSrc;

	// 指向要复制区域的指针
	LPSTR	lpDst;

	// 指向复制图像的指针
	LPSTR	lpNewDIBBits;
	HLOCAL	hNewDIBBits;

	// 象素在新DIB中的坐标
	LONG	i;
	LONG	j;

	// 象素在源DIB中的坐标
	LONG	i0;
	LONG	j0;

	// 图像每行的字节数
	LONG lLineBytes;

	// 计算图像每行的字节数
	lLineBytes = WIDTHBYTES(lWidth * 8);

	// 暂时分配内存，以保存新图像
	hNewDIBBits = LocalAlloc(LHND, lLineBytes * lHeight);
	if (hNewDIBBits == NULL)
	{
		// 分配内存失败
		return FALSE;
	}

	// 锁定内存
	lpNewDIBBits = (char*)LocalLock(hNewDIBBits);

	// 每行
	for (i = 0; i < lHeight; i++)
	{
		// 每列
		for (j = 0; j < lWidth; j++)
		{
			// 指向新DIB第i行，第j个象素的指针
			// 注意由于DIB中图像第一行其实保存在最后一行的位置，因此lpDst
			// 值不是(char *)lpNewDIBBits + lLineBytes * i + j，而是
			// (char *)lpNewDIBBits + lLineBytes * (lHeight - 1 - i) + j
			lpDst = (char*)lpNewDIBBits + lLineBytes * (lHeight - 1 - i) + j;

			// 计算该象素在源DIB中的坐标
			i0 = i - lXOffset;
			j0 = j - lYOffset;

			// 判断是否在源图范围内
			if ((j0 >= 0) && (j0 < lWidth) && (i0 >= 0) && (i0 < lHeight))
			{
				// 指向源DIB第i0行，第j0个象素的指针
				// 同样要注意DIB上下倒置的问题
				lpSrc = (char*)lpDIBBits + lLineBytes * (lHeight - 1 - i0) + j0;

				// 复制象素
				*lpDst = *lpSrc;
			}
			else
			{
				// 对于源图中没有的象素，直接赋值为255
				*((unsigned char*)lpDst) = 255;
			}

		}
	}

	// 复制平移后的图像
	memcpy(lpDIBBits, lpNewDIBBits, lLineBytes * lHeight);

	// 释放内存
	LocalUnlock(hNewDIBBits);
	LocalFree(hNewDIBBits);

	// 返回
	return TRUE;
}

void CMFCApplication1View::OnTranslation()
{
	// TODO: 在此添加命令处理程序代码
	CMFCApplication1Doc* pDoc = GetDocument();// 获取文档
////////////////////////////////////////////////////////////////////////////////////////////////	
	long	lSrcLineBytes;		//图象每行的字节数
	long	lSrcWidth;      //图象的宽度和高度
	long	lSrcHeight;
	int     lpSrcBitCount;       //图像的位深
	LPSTR	lpSrcDib;		//指向源图象的指针	
	LPSTR	lpSrcStartBits;	//指向源像素的指针
	lpSrcDib = (LPSTR) ::GlobalLock((HGLOBAL)pDoc->GetHObject());// 锁定DIB
	if (!lpSrcDib) return;

	if (pDoc->m_dib.GetColorNum(lpSrcDib) != 256)// 判断是否是8-bpp位图
	{
		AfxMessageBox(L"对不起，不是256色位图！");// 警告
		::GlobalUnlock((HGLOBAL)pDoc->GetHObject());// 解除锁定
		return;									//返回
	}										//判断是否是8-bpp位图,不是则返回

	lpSrcStartBits = pDoc->m_dib.GetBits(lpSrcDib);			// 找到DIB图象像素起始位置	
	lSrcWidth = pDoc->m_dib.GetWidth(lpSrcDib);					// 获取图象的宽度		
	lSrcHeight = pDoc->m_dib.GetHeight(lpSrcDib);					// 获取图象的高度	
	lpSrcBitCount = pDoc->m_dib.GetBitCount(lpSrcDib);                    //获取图像位深
	lSrcLineBytes = pDoc->m_dib.GetReqByteWidth(lSrcWidth * lpSrcBitCount);		// 计算图象每行的字节数
/////////////////////////////////////////////////////////////////////////////////////////////////
	CDlgTranslation dlgPara;
	dlgPara.m_XOffset = 100;
	dlgPara.m_YOffset = 100;
	LONG lXOffset;
	LONG lYOffset;
	if (dlgPara.DoModal() != IDOK)
	{
		// 返回
		return;
	}
	lXOffset = dlgPara.m_XOffset;
	lYOffset = dlgPara.m_YOffset;
	if (TranslationDIB1(lpSrcStartBits, lSrcWidth, lSrcHeight, lXOffset, lYOffset))
	{

		// 设置脏标记
		pDoc->SetModifiedFlag(TRUE);

		// 更新视图
		pDoc->UpdateAllViews(NULL);
	}
	else
	{
		// 提示用户
		MessageBox(L"分配内存失败！", L"系统提示", MB_ICONINFORMATION | MB_OK);
	}
	::GlobalUnlock((HGLOBAL)pDoc->GetHObject());// 解除锁定
}

BOOL MirrorDIB(LPSTR lpDIBBits, LONG lWidth, LONG lHeight, BOOL bDirection)
{

	// 指向源图像的指针
	LPSTR	lpSrc;

	// 指向要复制区域的指针
	LPSTR	lpDst;

	// 指向复制图像的指针
	LPSTR	lpBits;
	HLOCAL	hBits;

	// 循环变量
	LONG	i;
	LONG	j;

	// 图像每行的字节数
	LONG lLineBytes;

	// 计算图像每行的字节数
	lLineBytes = WIDTHBYTES(lWidth * 8);

	// 暂时分配内存，以保存一行图像
	hBits = LocalAlloc(LHND, lLineBytes);
	if (hBits == NULL)
	{
		// 分配内存失败
		return FALSE;
	}

	// 锁定内存
	lpBits = (char*)LocalLock(hBits);

	// 判断镜像方式
	if (bDirection)
	{
		// 水平镜像

		// 针对图像每行进行操作
		for (i = 0; i < lHeight; i++)
		{
			// 针对每行图像左半部分进行操作
			for (j = 0; j < lWidth / 2; j++)
			{

				// 指向倒数第i行，第j个象素的指针
				lpSrc = (char*)lpDIBBits + lLineBytes * i + j;

				// 指向倒数第i行，倒数第j个象素的指针
				lpDst = (char*)lpDIBBits + lLineBytes * (i + 1) - j;

				// 备份一个象素
				*lpBits = *lpDst;

				// 将倒数第i行，第j个象素复制到倒数第i行，倒数第j个象素
				*lpDst = *lpSrc;

				// 将倒数第i行，倒数第j个象素复制到倒数第i行，第j个象素
				*lpSrc = *lpBits;
			}

		}
	}
	else
	{
		// 垂直镜像

		// 针对上半图像进行操作
		for (i = 0; i < lHeight / 2; i++)
		{

			// 指向倒数第i行象素起点的指针
			lpSrc = (char*)lpDIBBits + lLineBytes * i;

			// 指向第i行象素起点的指针
			lpDst = (char*)lpDIBBits + lLineBytes * (lHeight - i - 1);

			// 备份一行，宽度为lWidth
			memcpy(lpBits, lpDst, lLineBytes);

			// 将倒数第i行象素复制到第i行
			memcpy(lpDst, lpSrc, lLineBytes);

			// 将第i行象素复制到倒数第i行
			memcpy(lpSrc, lpBits, lLineBytes);

		}
	}

	// 释放内存
	LocalUnlock(hBits);
	LocalFree(hBits);

	// 返回
	return TRUE;
}

void CMFCApplication1View::OnHorizontalmirror()
{
	// TODO: 在此添加命令处理程序代码
	CMFCApplication1Doc* pDoc = GetDocument();// 获取文档
////////////////////////////////////////////////////////////////////////////////////////////////	
	long	lSrcLineBytes;		//图象每行的字节数
	long	lSrcWidth;      //图象的宽度和高度
	long	lSrcHeight;
	int     lpSrcBitCount;       //图像的位深
	LPSTR	lpSrcDib;		//指向源图象的指针	
	LPSTR	lpSrcStartBits;	//指向源像素的指针
	lpSrcDib = (LPSTR) ::GlobalLock((HGLOBAL)pDoc->GetHObject());// 锁定DIB
	if (!lpSrcDib) return;

	if (pDoc->m_dib.GetColorNum(lpSrcDib) != 256)// 判断是否是8-bpp位图
	{
		AfxMessageBox(L"对不起，不是256色位图！");// 警告
		::GlobalUnlock((HGLOBAL)pDoc->GetHObject());// 解除锁定
		return;									//返回
	}										//判断是否是8-bpp位图,不是则返回

	lpSrcStartBits = pDoc->m_dib.GetBits(lpSrcDib);			// 找到DIB图象像素起始位置	
	lSrcWidth = pDoc->m_dib.GetWidth(lpSrcDib);					// 获取图象的宽度		
	lSrcHeight = pDoc->m_dib.GetHeight(lpSrcDib);					// 获取图象的高度	
	lpSrcBitCount = pDoc->m_dib.GetBitCount(lpSrcDib);                    //获取图像位深
	lSrcLineBytes = pDoc->m_dib.GetReqByteWidth(lSrcWidth * lpSrcBitCount);		// 计算图象每行的字节数
/////////////////////////////////////////////////////////////////////////////////////////////////
	MirrorDIB(lpSrcStartBits, lSrcWidth, lSrcHeight, FALSE);
	pDoc->SetModifiedFlag(TRUE);
	// 更新视图
	pDoc->UpdateAllViews(NULL);
	::GlobalUnlock((HGLOBAL)pDoc->GetHObject());// 解除锁定
}

void CMFCApplication1View::OnVerticalmirror()
{
	// TODO: 在此添加命令处理程序代码
	CMFCApplication1Doc* pDoc = GetDocument();// 获取文档
////////////////////////////////////////////////////////////////////////////////////////////////	
	long	lSrcLineBytes;		//图象每行的字节数
	long	lSrcWidth;      //图象的宽度和高度
	long	lSrcHeight;
	int     lpSrcBitCount;       //图像的位深
	LPSTR	lpSrcDib;		//指向源图象的指针	
	LPSTR	lpSrcStartBits;	//指向源像素的指针
	lpSrcDib = (LPSTR) ::GlobalLock((HGLOBAL)pDoc->GetHObject());// 锁定DIB
	if (!lpSrcDib) return;

	if (pDoc->m_dib.GetColorNum(lpSrcDib) != 256)// 判断是否是8-bpp位图
	{
		AfxMessageBox(L"对不起，不是256色位图！");// 警告
		::GlobalUnlock((HGLOBAL)pDoc->GetHObject());// 解除锁定
		return;									//返回
	}										//判断是否是8-bpp位图,不是则返回

	lpSrcStartBits = pDoc->m_dib.GetBits(lpSrcDib);			// 找到DIB图象像素起始位置	
	lSrcWidth = pDoc->m_dib.GetWidth(lpSrcDib);					// 获取图象的宽度		
	lSrcHeight = pDoc->m_dib.GetHeight(lpSrcDib);					// 获取图象的高度	
	lpSrcBitCount = pDoc->m_dib.GetBitCount(lpSrcDib);                    //获取图像位深
	lSrcLineBytes = pDoc->m_dib.GetReqByteWidth(lSrcWidth * lpSrcBitCount);		// 计算图象每行的字节数
/////////////////////////////////////////////////////////////////////////////////////////////////
	MirrorDIB(lpSrcStartBits, lSrcWidth, lSrcHeight, TRUE);
	pDoc->SetModifiedFlag(TRUE);
	// 更新视图
	pDoc->UpdateAllViews(NULL);
	::GlobalUnlock((HGLOBAL)pDoc->GetHObject());// 解除锁定
}

HGLOBAL WINAPI ZoomDIB(LPSTR lpDIB, float fXZoomRatio, float fYZoomRatio)
{

	// 源图像的宽度和高度
	LONG	lWidth;
	LONG	lHeight;

	// 缩放后图像的宽度和高度
	LONG	lNewWidth;
	LONG	lNewHeight;

	// 缩放后图像的宽度（lNewWidth'，必须是4的倍数）
	LONG	lNewLineBytes;

	// 指向源图像的指针
	LPSTR	lpDIBBits;

	// 指向源象素的指针
	LPSTR	lpSrc;

	// 缩放后新DIB句柄
	HDIB	hDIB;

	// 指向缩放图像对应象素的指针
	LPSTR	lpDst;

	// 指向缩放图像的指针
	LPSTR	lpNewDIB;
	LPSTR	lpNewDIBBits;

	// 指向BITMAPINFO结构的指针（Win3.0）
	LPBITMAPINFOHEADER lpbmi;

	// 指向BITMAPCOREINFO结构的指针
	LPBITMAPCOREHEADER lpbmc;

	// 循环变量（象素在新DIB中的坐标）
	LONG	i;
	LONG	j;

	// 象素在源DIB中的坐标
	LONG	i0;
	LONG	j0;

	// 图像每行的字节数
	LONG lLineBytes;

	// 找到源DIB图像象素起始位置
	lpDIBBits = ::FindDIBBits(lpDIB);

	// 获取图像的宽度
	lWidth = ::DIBWidth(lpDIB);

	// 计算图像每行的字节数
	lLineBytes = WIDTHBYTES(lWidth * 8);

	// 获取图像的高度
	lHeight = ::DIBHeight(lpDIB);

	// 计算缩放后的图像实际宽度
	// 此处直接加0.5是由于强制类型转换时不四舍五入，而是直接截去小数部分
	lNewWidth = (LONG)(::DIBWidth(lpDIB) * fXZoomRatio + 0.5);

	// 计算新图像每行的字节数
	lNewLineBytes = WIDTHBYTES(lNewWidth * 8);

	// 计算缩放后的图像高度
	lNewHeight = (LONG)(lHeight * fYZoomRatio + 0.5);

	// 分配内存，以保存新DIB
	hDIB = (HDIB) ::GlobalAlloc(GHND, lNewLineBytes * lNewHeight + *(LPDWORD)lpDIB + ::PaletteSize(lpDIB));

	// 判断是否内存分配失败
	if (hDIB == NULL)
	{
		// 分配内存失败
		return NULL;
	}

	// 锁定内存
	lpNewDIB = (char*)::GlobalLock((HGLOBAL)hDIB);

	// 复制DIB信息头和调色板
	memcpy(lpNewDIB, lpDIB, *(LPDWORD)lpDIB + ::PaletteSize(lpDIB));

	// 找到新DIB象素起始位置
	lpNewDIBBits = ::FindDIBBits(lpNewDIB);

	// 获取指针
	lpbmi = (LPBITMAPINFOHEADER)lpNewDIB;
	lpbmc = (LPBITMAPCOREHEADER)lpNewDIB;

	// 更新DIB中图像的高度和宽度
	if (IS_WIN30_DIB(lpNewDIB))
	{
		// 对于Windows 3.0 DIB
		lpbmi->biWidth = lNewWidth;
		lpbmi->biHeight = lNewHeight;
	}
	else
	{
		// 对于其它格式的DIB
		lpbmc->bcWidth = (unsigned short)lNewWidth;
		lpbmc->bcHeight = (unsigned short)lNewHeight;
	}

	// 针对图像每行进行操作
	for (i = 0; i < lNewHeight; i++)
	{
		// 针对图像每列进行操作
		for (j = 0; j < lNewWidth; j++)
		{

			// 指向新DIB第i行，第j个象素的指针
			// 注意此处宽度和高度是新DIB的宽度和高度
			lpDst = (char*)lpNewDIBBits + lNewLineBytes * (lNewHeight - 1 - i) + j;

			// 计算该象素在源DIB中的坐标
			i0 = (LONG)(i / fYZoomRatio + 0.5);
			j0 = (LONG)(j / fXZoomRatio + 0.5);

			// 判断是否在源图范围内
			if ((j0 >= 0) && (j0 < lWidth) && (i0 >= 0) && (i0 < lHeight))
			{

				// 指向源DIB第i0行，第j0个象素的指针
				lpSrc = (char*)lpDIBBits + lLineBytes * (lHeight - 1 - i0) + j0;

				// 复制象素
				*lpDst = *lpSrc;
			}
			else
			{
				// 对于源图中没有的象素，直接赋值为255
				*((unsigned char*)lpDst) = 255;
			}

		}

	}

	// 返回
	return hDIB;
}

void CMFCApplication1View::OnResizing()
{
	// TODO: 在此添加命令处理程序代码
	CMFCApplication1Doc* pDoc = GetDocument();// 获取文档
////////////////////////////////////////////////////////////////////////////////////////////////	
	long	lSrcLineBytes;		//图象每行的字节数
	long	lSrcWidth;      //图象的宽度和高度
	long	lSrcHeight;
	int     lpSrcBitCount;       //图像的位深
	LPSTR	lpSrcDib;		//指向源图象的指针	
	LPSTR	lpSrcStartBits;	//指向源像素的指针
	lpSrcDib = (LPSTR) ::GlobalLock((HGLOBAL)pDoc->GetHObject());// 锁定DIB
	if (!lpSrcDib) return;

	if (pDoc->m_dib.GetColorNum(lpSrcDib) != 256)// 判断是否是8-bpp位图
	{
		AfxMessageBox(L"对不起，不是256色位图！");// 警告
		::GlobalUnlock((HGLOBAL)pDoc->GetHObject());// 解除锁定
		return;									//返回
	}										//判断是否是8-bpp位图,不是则返回

	lpSrcStartBits = pDoc->m_dib.GetBits(lpSrcDib);			// 找到DIB图象像素起始位置	
	lSrcWidth = pDoc->m_dib.GetWidth(lpSrcDib);					// 获取图象的宽度		
	lSrcHeight = pDoc->m_dib.GetHeight(lpSrcDib);					// 获取图象的高度	
	lpSrcBitCount = pDoc->m_dib.GetBitCount(lpSrcDib);                    //获取图像位深
	lSrcLineBytes = pDoc->m_dib.GetReqByteWidth(lSrcWidth * lpSrcBitCount);		// 计算图象每行的字节数
/////////////////////////////////////////////////////////////////////////////////////////////////
	float fXZoomRatio;
	float fYZoomRatio;
	CDlgResizing dlgPara;
	dlgPara.m_XZoom = 0.5;
	dlgPara.m_YZoom = 0.5;
	if (dlgPara.DoModal() != IDOK)
	{
		// 返回
		return;
	}
	fXZoomRatio = dlgPara.m_XZoom;
	fYZoomRatio = dlgPara.m_YZoom;
	HDIB hNewDIB = NULL;
	hNewDIB = (HDIB)ZoomDIB(lpSrcDib, fXZoomRatio, fYZoomRatio);
	pDoc->UpdateObject(hNewDIB);
	pDoc->SetDib();
	pDoc->SetModifiedFlag(TRUE);
	pDoc->UpdateAllViews(NULL);
	::GlobalUnlock((HGLOBAL)pDoc->GetHObject());// 解除锁定
}

BOOL TransposeDIB(LPSTR lpDIB)
{

	// 图像的宽度和高度
	LONG	lWidth;
	LONG	lHeight;

	// 指向源图像的指针
	LPSTR	lpDIBBits;

	// 指向源象素的指针
	LPSTR	lpSrc;

	// 指向转置图像对应象素的指针
	LPSTR	lpDst;

	// 指向转置图像的指针
	LPSTR	lpNewDIBBits;
	HLOCAL	hNewDIBBits;

	// 指向BITMAPINFO结构的指针（Win3.0）
	LPBITMAPINFOHEADER lpbmi;

	// 指向BITMAPCOREINFO结构的指针
	LPBITMAPCOREHEADER lpbmc;

	// 循环变量
	LONG	i;
	LONG	j;

	// 图像每行的字节数
	LONG lLineBytes;

	// 新图像每行的字节数
	LONG lNewLineBytes;

	// 获取指针
	lpbmi = (LPBITMAPINFOHEADER)lpDIB;
	lpbmc = (LPBITMAPCOREHEADER)lpDIB;

	// 找到源DIB图像象素起始位置
	lpDIBBits = ::FindDIBBits(lpDIB);

	// 获取图像的"宽度"（4的倍数）
	lWidth = ::DIBWidth(lpDIB);

	// 获取图像的高度
	lHeight = ::DIBHeight(lpDIB);

	// 计算图像每行的字节数
	lLineBytes = WIDTHBYTES(lWidth * 8);

	// 计算新图像每行的字节数
	lNewLineBytes = WIDTHBYTES(lHeight * 8);

	// 暂时分配内存，以保存新图像
	hNewDIBBits = LocalAlloc(LHND, lWidth * lNewLineBytes);

	// 判断是否内存分配失败
	if (hNewDIBBits == NULL)
	{
		// 分配内存失败
		return FALSE;
	}

	// 锁定内存
	lpNewDIBBits = (char*)LocalLock(hNewDIBBits);

	// 针对图像每行进行操作
	for (i = 0; i < lHeight; i++)
	{
		// 针对每行图像每列进行操作
		for (j = 0; j < lWidth; j++)
		{

			// 指向源DIB第i行，第j个象素的指针
			lpSrc = (char*)lpDIBBits + lLineBytes * (lHeight - 1 - i) + j;

			// 指向转置DIB第j行，第i个象素的指针
			// 注意此处lWidth和lHeight是源DIB的宽度和高度，应该互换
			lpDst = (char*)lpNewDIBBits + lNewLineBytes * (lWidth - 1 - j) + i;

			// 复制象素
			*lpDst = *lpSrc;

		}

	}

	// 复制转置后的图像
	memcpy(lpDIBBits, lpNewDIBBits, lWidth * lNewLineBytes);

	// 互换DIB中图像的高宽
	if (IS_WIN30_DIB(lpDIB))
	{
		// 对于Windows 3.0 DIB
		lpbmi->biWidth = lHeight;

		lpbmi->biHeight = lWidth;
	}
	else
	{
		// 对于其它格式的DIB
		lpbmc->bcWidth = (unsigned short)lHeight;
		lpbmc->bcHeight = (unsigned short)lWidth;
	}

	// 释放内存
	LocalUnlock(hNewDIBBits);
	LocalFree(hNewDIBBits);

	// 返回
	return TRUE;
}

void CMFCApplication1View::OnTranspose()
{
	// TODO: 在此添加命令处理程序代码
	CMFCApplication1Doc* pDoc = GetDocument();// 获取文档
////////////////////////////////////////////////////////////////////////////////////////////////	
	long	lSrcLineBytes;		//图象每行的字节数
	long	lSrcWidth;      //图象的宽度和高度
	long	lSrcHeight;
	int     lpSrcBitCount;       //图像的位深
	LPSTR	lpSrcDib;		//指向源图象的指针	
	LPSTR	lpSrcStartBits;	//指向源像素的指针
	lpSrcDib = (LPSTR) ::GlobalLock((HGLOBAL)pDoc->GetHObject());// 锁定DIB
	if (!lpSrcDib) return;

	if (pDoc->m_dib.GetColorNum(lpSrcDib) != 256)// 判断是否是8-bpp位图
	{
		AfxMessageBox(L"对不起，不是256色位图！");// 警告
		::GlobalUnlock((HGLOBAL)pDoc->GetHObject());// 解除锁定
		return;									//返回
	}										//判断是否是8-bpp位图,不是则返回

	lpSrcStartBits = pDoc->m_dib.GetBits(lpSrcDib);			// 找到DIB图象像素起始位置	
	lSrcWidth = pDoc->m_dib.GetWidth(lpSrcDib);					// 获取图象的宽度		
	lSrcHeight = pDoc->m_dib.GetHeight(lpSrcDib);					// 获取图象的高度	
	lpSrcBitCount = pDoc->m_dib.GetBitCount(lpSrcDib);                    //获取图像位深
	lSrcLineBytes = pDoc->m_dib.GetReqByteWidth(lSrcWidth * lpSrcBitCount);		// 计算图象每行的字节数
/////////////////////////////////////////////////////////////////////////////////////////////////
	TransposeDIB(lpSrcDib);
	pDoc->SetModifiedFlag(TRUE);
	pDoc->SetDib();
	pDoc->UpdateAllViews(NULL);
	::GlobalUnlock((HGLOBAL)pDoc->GetHObject());// 解除锁定
}

HGLOBAL WINAPI RotateDIB(LPSTR lpDIB, int iRotateAngle)
{

	// 源图像的宽度和高度
	LONG	lWidth;
	LONG	lHeight;

	// 旋转后图像的宽度和高度
	LONG	lNewWidth;
	LONG	lNewHeight;

	// 图像每行的字节数
	LONG	lLineBytes;

	// 旋转后图像的宽度（lNewWidth'，必须是4的倍数）
	LONG	lNewLineBytes;

	// 指向源图像的指针
	LPSTR	lpDIBBits;

	// 指向源象素的指针
	LPSTR	lpSrc;

	// 旋转后新DIB句柄
	HDIB	hDIB;

	// 指向旋转图像对应象素的指针
	LPSTR	lpDst;

	// 指向旋转图像的指针
	LPSTR	lpNewDIB;
	LPSTR	lpNewDIBBits;

	// 指向BITMAPINFO结构的指针（Win3.0）
	LPBITMAPINFOHEADER lpbmi;

	// 指向BITMAPCOREINFO结构的指针
	LPBITMAPCOREHEADER lpbmc;

	// 循环变量（象素在新DIB中的坐标）
	LONG	i;
	LONG	j;

	// 象素在源DIB中的坐标
	LONG	i0;
	LONG	j0;

	// 旋转角度（弧度）
	float	fRotateAngle;

	// 旋转角度的正弦和余弦
	float	fSina, fCosa;

	// 源图四个角的坐标（以图像中心为坐标系原点）
	float	fSrcX1, fSrcY1, fSrcX2, fSrcY2, fSrcX3, fSrcY3, fSrcX4, fSrcY4;

	// 旋转后四个角的坐标（以图像中心为坐标系原点）
	float	fDstX1, fDstY1, fDstX2, fDstY2, fDstX3, fDstY3, fDstX4, fDstY4;

	// 两个中间常量
	float	f1, f2;

	// 找到源DIB图像象素起始位置
	lpDIBBits = ::FindDIBBits(lpDIB);

	// 获取图像的"宽度"（4的倍数）
	lWidth = ::DIBWidth(lpDIB);

	// 计算图像每行的字节数
	lLineBytes = WIDTHBYTES(lWidth * 8);

	// 获取图像的高度
	lHeight = ::DIBHeight(lpDIB);

	// 将旋转角度从度转换到弧度
	fRotateAngle = (float)RADIAN(iRotateAngle);

	// 计算旋转角度的正弦
	fSina = (float)sin((double)fRotateAngle);

	// 计算旋转角度的余弦
	fCosa = (float)cos((double)fRotateAngle);

	// 计算原图的四个角的坐标（以图像中心为坐标系原点）
	fSrcX1 = (float)(-(lWidth - 1) / 2);
	fSrcY1 = (float)((lHeight - 1) / 2);
	fSrcX2 = (float)((lWidth - 1) / 2);
	fSrcY2 = (float)((lHeight - 1) / 2);
	fSrcX3 = (float)(-(lWidth - 1) / 2);
	fSrcY3 = (float)(-(lHeight - 1) / 2);
	fSrcX4 = (float)((lWidth - 1) / 2);
	fSrcY4 = (float)(-(lHeight - 1) / 2);

	// 计算新图四个角的坐标（以图像中心为坐标系原点）
	fDstX1 = fCosa * fSrcX1 + fSina * fSrcY1;
	fDstY1 = -fSina * fSrcX1 + fCosa * fSrcY1;
	fDstX2 = fCosa * fSrcX2 + fSina * fSrcY2;
	fDstY2 = -fSina * fSrcX2 + fCosa * fSrcY2;
	fDstX3 = fCosa * fSrcX3 + fSina * fSrcY3;
	fDstY3 = -fSina * fSrcX3 + fCosa * fSrcY3;
	fDstX4 = fCosa * fSrcX4 + fSina * fSrcY4;
	fDstY4 = -fSina * fSrcX4 + fCosa * fSrcY4;

	// 计算旋转后的图像实际宽度
	lNewWidth = (LONG)(max(fabs(fDstX4 - fDstX1), fabs(fDstX3 - fDstX2)) + 0.5);

	// 计算新图像每行的字节数
	lNewLineBytes = WIDTHBYTES(lNewWidth * 8);

	// 计算旋转后的图像高度
	lNewHeight = (LONG)(max(fabs(fDstY4 - fDstY1), fabs(fDstY3 - fDstY2)) + 0.5);

	// 两个常数，这样不用以后每次都计算了
	f1 = (float)(-0.5 * (lNewWidth - 1) * fCosa - 0.5 * (lNewHeight - 1) * fSina
		+ 0.5 * (lWidth - 1));
	f2 = (float)(0.5 * (lNewWidth - 1) * fSina - 0.5 * (lNewHeight - 1) * fCosa
		+ 0.5 * (lHeight - 1));

	// 分配内存，以保存新DIB
	hDIB = (HDIB) ::GlobalAlloc(GHND, lNewLineBytes * lNewHeight + *(LPDWORD)lpDIB + ::PaletteSize(lpDIB));

	// 判断是否内存分配失败
	if (hDIB == NULL)
	{
		// 分配内存失败
		return NULL;
	}

	// 锁定内存
	lpNewDIB = (char*)::GlobalLock((HGLOBAL)hDIB);

	// 复制DIB信息头和调色板
	memcpy(lpNewDIB, lpDIB, *(LPDWORD)lpDIB + ::PaletteSize(lpDIB));

	// 找到新DIB象素起始位置
	lpNewDIBBits = ::FindDIBBits(lpNewDIB);

	// 获取指针
	lpbmi = (LPBITMAPINFOHEADER)lpNewDIB;
	lpbmc = (LPBITMAPCOREHEADER)lpNewDIB;

	// 更新DIB中图像的高度和宽度
	if (IS_WIN30_DIB(lpNewDIB))
	{
		// 对于Windows 3.0 DIB
		lpbmi->biWidth = lNewWidth;
		lpbmi->biHeight = lNewHeight;
	}
	else
	{
		// 对于其它格式的DIB
		lpbmc->bcWidth = (unsigned short)lNewWidth;
		lpbmc->bcHeight = (unsigned short)lNewHeight;
	}

	// 针对图像每行进行操作
	for (i = 0; i < lNewHeight; i++)
	{
		// 针对图像每列进行操作
		for (j = 0; j < lNewWidth; j++)
		{
			// 指向新DIB第i行，第j个象素的指针
			// 注意此处宽度和高度是新DIB的宽度和高度
			lpDst = (char*)lpNewDIBBits + lNewLineBytes * (lNewHeight - 1 - i) + j;

			// 计算该象素在源DIB中的坐标
			i0 = (LONG)(-((float)j) * fSina + ((float)i) * fCosa + f2 + 0.5);
			j0 = (LONG)(((float)j) * fCosa + ((float)i) * fSina + f1 + 0.5);

			// 判断是否在源图范围内
			if ((j0 >= 0) && (j0 < lWidth) && (i0 >= 0) && (i0 < lHeight))
			{
				// 指向源DIB第i0行，第j0个象素的指针
				lpSrc = (char*)lpDIBBits + lLineBytes * (lHeight - 1 - i0) + j0;

				// 复制象素
				*lpDst = *lpSrc;
			}
			else
			{
				// 对于源图中没有的象素，直接赋值为255
				*((unsigned char*)lpDst) = 255;
			}

		}

	}

	// 返回
	return hDIB;
}

void CMFCApplication1View::OnRotating()
{
	// TODO: 在此添加命令处理程序代码
	CMFCApplication1Doc* pDoc = GetDocument();// 获取文档
////////////////////////////////////////////////////////////////////////////////////////////////	
	long	lSrcLineBytes;		//图象每行的字节数
	long	lSrcWidth;      //图象的宽度和高度
	long	lSrcHeight;
	int     lpSrcBitCount;       //图像的位深
	LPSTR	lpSrcDib;		//指向源图象的指针	
	LPSTR	lpSrcStartBits;	//指向源像素的指针
	lpSrcDib = (LPSTR) ::GlobalLock((HGLOBAL)pDoc->GetHObject());// 锁定DIB
	if (!lpSrcDib) return;

	if (pDoc->m_dib.GetColorNum(lpSrcDib) != 256)// 判断是否是8-bpp位图
	{
		AfxMessageBox(L"对不起，不是256色位图！");// 警告
		::GlobalUnlock((HGLOBAL)pDoc->GetHObject());// 解除锁定
		return;									//返回
	}										//判断是否是8-bpp位图,不是则返回

	lpSrcStartBits = pDoc->m_dib.GetBits(lpSrcDib);			// 找到DIB图象像素起始位置	
	lSrcWidth = pDoc->m_dib.GetWidth(lpSrcDib);					// 获取图象的宽度		
	lSrcHeight = pDoc->m_dib.GetHeight(lpSrcDib);					// 获取图象的高度	
	lpSrcBitCount = pDoc->m_dib.GetBitCount(lpSrcDib);                    //获取图像位深
	lSrcLineBytes = pDoc->m_dib.GetReqByteWidth(lSrcWidth * lpSrcBitCount);		// 计算图象每行的字节数
/////////////////////////////////////////////////////////////////////////////////////////////////
	CDlgRotating dlgPara;
	int iRotateAngle;
	dlgPara.m_iRotateAngle = 90;
	// 显示对话框，提示用户设定旋转角度
	if (dlgPara.DoModal() != IDOK)
	{
		// 返回
		return;
	}

	// 获取用户设定的平移量
	iRotateAngle = dlgPara.m_iRotateAngle;
	HDIB hNewDIB = NULL;
	hNewDIB = (HDIB)RotateDIB(lpSrcDib, iRotateAngle);
	pDoc->UpdateObject(hNewDIB);
	pDoc->SetDib();
	pDoc->SetModifiedFlag(TRUE);
	pDoc->UpdateAllViews(NULL);
	::GlobalUnlock((HGLOBAL)pDoc->GetHObject());// 解除锁定
}

void CMFCApplication1View::OnCanny()
{
	// TODO: 在此添加命令处理程序代码
	CMFCApplication1Doc* pDoc = GetDocument();// 获取文档
	USES_CONVERSION;
	cv::String cvStr = W2A(pDoc->GetPathName());
	cv::Mat img = cv::imread(cvStr, cv::IMREAD_COLOR);
	cv::Mat imgSmooth, imgGray, imgThre, imgdst;
	cvtColor(img, imgGray, cv::COLOR_BGR2GRAY);
	GaussianBlur(imgGray, imgSmooth, cv::Size(5, 5), 0, 0);
	Canny(imgSmooth, imgdst, 25, 75);
	cv::imshow("Image", imgdst);
}

void CMFCApplication1View::OnSketch()
{
	// TODO: 在此添加命令处理程序代码
	OnRobert();
	OnPointinvert();
}

BOOL WINAPI AddMinusDIB(LPSTR lpDIBBits, LPSTR lpDIBBitsBK, LONG lWidth, LONG lHeight, bool bAddMinus)
{

	// 指向源图像的指针
	LPSTR	lpSrc, lpSrcBK;

	// 指向缓存图像的指针
	LPSTR	lpDst;

	// 指向缓存DIB图像的指针
	LPSTR	lpNewDIBBits;
	HLOCAL	hNewDIBBits;

	//循环变量
	long i;
	long j;

	//像素值
	unsigned char pixel, pixelBK;

	// 图像每行的字节数
	LONG lLineBytes;

	// 暂时分配内存，以保存新图像
	hNewDIBBits = LocalAlloc(LHND, lWidth * lHeight);

	if (hNewDIBBits == NULL)
	{
		// 分配内存失败
		return FALSE;
	}

	// 锁定内存
	lpNewDIBBits = (char*)LocalLock(hNewDIBBits);

	// 初始化新分配的内存，设定初始值为255
	lpDst = (char*)lpNewDIBBits;
	memset(lpDst, (BYTE)255, lWidth * lHeight);

	// 计算图像每行的字节数
	lLineBytes = WIDTHBYTES(lWidth * 8);

	for (j = 0; j < lHeight; j++)
	{
		for (i = 0; i < lWidth; i++)
		{
			// 指向源图像倒数第j行，第i个象素的指针			
			lpSrc = (char*)lpDIBBits + lLineBytes * j + i;
			lpSrcBK = (char*)lpDIBBitsBK + lLineBytes * j + i;

			// 指向目标图像倒数第j行，第i个象素的指针			
			lpDst = (char*)lpNewDIBBits + lLineBytes * j + i;

			pixel = (unsigned char)*lpSrc;
			pixelBK = (unsigned char)*lpSrcBK;
			if (bAddMinus)
				*lpDst = pixel + pixelBK > 255 ? 255 : pixel + pixelBK;
			else
				*lpDst = pixel - pixelBK < 0 ? 0 : pixel - pixelBK;


		}
	}


	// 复制腐蚀后的图像
	memcpy(lpDIBBits, lpNewDIBBits, lWidth * lHeight);

	// 释放内存
	LocalUnlock(hNewDIBBits);
	LocalFree(hNewDIBBits);

	// 返回
	return TRUE;
}
BOOL fourn(double* data, unsigned long nn[], int ndim, int isign)
{
	int idim;
	unsigned long i1, i2, i3, i2rev, i3rev, ip1, ip2, ip3, ifp1, ifp2;
	unsigned long ibit, k1, k2, n, nprev, nrem, ntot;
	double tempi, tempr;
	double theta, wi, wpi, wpr, wr, wtemp;

	for (ntot = 1, idim = 1; idim <= ndim; idim++)
		ntot *= nn[idim];
	nprev = 1;
	for (idim = ndim; idim >= 1; idim--) {
		n = nn[idim];
		nrem = ntot / (n * nprev);
		ip1 = nprev << 1;
		ip2 = ip1 * n;
		ip3 = ip2 * nrem;
		i2rev = 1;
		for (i2 = 1; i2 <= ip2; i2 += ip1) {
			if (i2 < i2rev) {
				for (i1 = i2; i1 <= i2 + ip1 - 2; i1 += 2) {
					for (i3 = i1; i3 <= ip3; i3 += ip2) {
						i3rev = i2rev + i3 - i2;
						SWAP(data[i3], data[i3rev]);
						SWAP(data[i3 + 1], data[i3rev + 1]);
					}
				}
			}
			ibit = ip2 >> 1;
			while (ibit >= ip1 && i2rev > ibit) {
				i2rev -= ibit;
				ibit >>= 1;
			}
			i2rev += ibit;
		}
		ifp1 = ip1;
		while (ifp1 < ip2) {
			ifp2 = ifp1 << 1;
			theta = isign * 6.28318530717959 / (ifp2 / ip1);
			wtemp = sin(0.5 * theta);
			wpr = -2.0 * wtemp * wtemp;
			wpi = sin(theta);
			wr = 1.0;
			wi = 0.0;
			for (i3 = 1; i3 <= ifp1; i3 += ip1) {
				for (i1 = i3; i1 <= i3 + ip1 - 2; i1 += 2) {
					for (i2 = i1; i2 <= ip3; i2 += ifp2) {
						k1 = i2;
						k2 = k1 + ifp1;
						tempr = wr * data[k2] - wi * data[k2 + 1];
						tempi = wr * data[k2 + 1] + wi * data[k2];
						data[k2] = data[k1] - tempr;
						data[k2 + 1] = data[k1 + 1] - tempi;
						data[k1] += tempr;
						data[k1 + 1] += tempi;
					}
				}
				wr = (wtemp = wr) * wpr - wi * wpi + wr;
				wi = wi * wpr + wtemp * wpi + wi;
			}
			ifp1 = ifp2;
		}
		nprev *= n;
	}
	return true;
}
BOOL WINAPI BlurDIB(LPSTR lpDIBBits, LONG lWidth, LONG lHeight)
{
	// 指向源图像的指针
	LPSTR	lpSrc;

	//循环变量
	long i;
	long j;

	//像素值
	unsigned char pixel;

	// 图像每行的字节数
	LONG lLineBytes;

	//用于做FFT的数组
	double* fftSrc, * fftKernel;
	//二维FFT的长度和宽度
	unsigned long nn[3];
	//图像归一化因子
	double MaxNum;

	// 计算图像每行的字节数
	lLineBytes = WIDTHBYTES(lWidth * 8);

	double dPower = log((double)lLineBytes) / log(2.0);
	if (dPower != (int)dPower)
	{
		return false;
	}
	dPower = log((double)lHeight) / log(2.0);
	if (dPower != (int)dPower)
	{
		return false;
	}

	fftSrc = new double[lHeight * lLineBytes * 2 + 1];
	fftKernel = new double[lHeight * lLineBytes * 2 + 1];

	nn[1] = lHeight;
	nn[2] = lLineBytes;

	for (j = 0; j < lHeight; j++)
	{
		for (i = 0; i < lLineBytes; i++)
		{
			// 指向源图像倒数第j行，第i个象素的指针			
			lpSrc = (char*)lpDIBBits + lLineBytes * j + i;

			pixel = (unsigned char)*lpSrc;

			fftSrc[(2 * lLineBytes) * j + 2 * i + 1] = (double)pixel;
			fftSrc[(2 * lLineBytes) * j + 2 * i + 2] = 0.0;

			if (i < 5 && j < 5)
			{
				fftKernel[(2 * lLineBytes) * j + 2 * i + 1] = 1 / 25.0;
			}
			else
			{
				fftKernel[(2 * lLineBytes) * j + 2 * i + 1] = 0.0;
			}
			fftKernel[(2 * lLineBytes) * j + 2 * i + 2] = 0.0;
		}
	}

	//对源图像进行FFT
	fourn(fftSrc, nn, 2, 1);
	//对卷积核图像进行FFT
	fourn(fftKernel, nn, 2, 1);

	//频域相乘
	for (i = 1; i < lHeight * lLineBytes * 2; i += 2)
	{
		fftSrc[i] = fftSrc[i] * fftKernel[i] - fftSrc[i + 1] * fftKernel[i + 1];
		fftSrc[i + 1] = fftSrc[i] * fftKernel[i + 1] + fftSrc[i + 1] * fftKernel[i];
	}

	//对结果图像进行反FFT
	fourn(fftSrc, nn, 2, -1);

	//确定归一化因子
	MaxNum = 0.0;
	for (j = 0; j < lHeight; j++)
	{
		for (i = 0; i < lLineBytes; i++)
		{
			fftSrc[(2 * lLineBytes) * j + 2 * i + 1] =
				sqrt(fftSrc[(2 * lLineBytes) * j + 2 * i + 1] * fftSrc[(2 * lLineBytes) * j + 2 * i + 1]\
					+ fftSrc[(2 * lLineBytes) * j + 2 * i + 2] * fftSrc[(2 * lLineBytes) * j + 2 * i + 2]);
			if (MaxNum < fftSrc[(2 * lLineBytes) * j + 2 * i + 1])
				MaxNum = fftSrc[(2 * lLineBytes) * j + 2 * i + 1];
		}
	}

	//转换为图像
	for (j = 0; j < lHeight; j++)
	{
		for (i = 0; i < lLineBytes; i++)
		{
			// 指向源图像倒数第j行，第i个象素的指针			
			lpSrc = (char*)lpDIBBits + lLineBytes * j + i;

			*lpSrc = (unsigned char)(fftSrc[(2 * lLineBytes) * j + 2 * i + 1] * 255.0 / MaxNum);
		}
	}
	delete fftSrc;
	delete fftKernel;
	// 返回
	return true;
}

void CMFCApplication1View::OnCartoon()
{
	// TODO: 在此添加命令处理程序代码
	CMFCApplication1Doc* pDoc = GetDocument();// 获取文档
////////////////////////////////////////////////////////////////////////////////////////////////	
	long	lSrcLineBytes;		//图象每行的字节数
	long	lSrcWidth;      //图象的宽度和高度
	long	lSrcHeight;
	int     lpSrcBitCount;       //图像的位深
	LPSTR	lpSrcDib;		//指向源图象的指针
	LPSTR	lpSrcDibBK;
	LPSTR	lpSrcStartBits;	//指向源像素的指针
	LPSTR	lpSrcStartBitsBK;
	lpSrcDib = (LPSTR) ::GlobalLock((HGLOBAL)pDoc->GetHObject());// 锁定DIB
	lpSrcDibBK = lpSrcDib;
	if (!lpSrcDib) return;

	if (pDoc->m_dib.GetColorNum(lpSrcDib) != 256)// 判断是否是8-bpp位图
	{
		AfxMessageBox(L"对不起，不是256色位图！");// 警告
		::GlobalUnlock((HGLOBAL)pDoc->GetHObject());// 解除锁定
		return;									//返回
	}										//判断是否是8-bpp位图,不是则返回

	lpSrcStartBits = pDoc->m_dib.GetBits(lpSrcDib);			// 找到DIB图象像素起始位置
	lpSrcStartBitsBK = pDoc->m_dib.GetBits(lpSrcDibBK);
	lSrcWidth = pDoc->m_dib.GetWidth(lpSrcDib);					// 获取图象的宽度		
	lSrcHeight = pDoc->m_dib.GetHeight(lpSrcDib);					// 获取图象的高度	
	lpSrcBitCount = pDoc->m_dib.GetBitCount(lpSrcDib);                    //获取图像位深
	lSrcLineBytes = pDoc->m_dib.GetReqByteWidth(lSrcWidth * lpSrcBitCount);		// 计算图象每行的字节数
/////////////////////////////////////////////////////////////////////////////////////////////////
	RobertDIB(lpSrcStartBits, WIDTHBYTES(lSrcWidth * 8), lSrcHeight);
	FLOAT fA = -1.0;
	FLOAT fB = 255;
	unsigned char* lpSrc;
	LONG i;
	LONG j;
	LONG fTemp;
	for (i = 0; i < lSrcHeight; i++)
		for (j = 0; j < lSrcWidth; j++)
		{
			lpSrc = (unsigned char*)lpSrcStartBits + lSrcLineBytes * (lSrcHeight - 1 - i) + j;
			fTemp = fA * (*lpSrc) + fB;
			if (fTemp >= 255)
			{
				*lpSrc = 255;
			}
			else if (fTemp <= 0)
			{
				*lpSrc = 0;
			}
			else
			{
				*lpSrc = (unsigned char)(fTemp + 0.5);
			}
		}
	////////////////
	BlurDIB(lpSrcStartBits, lSrcWidth, lSrcHeight);
	/////////////////
	//AddMinusDIB(lpSrcStartBits, lpSrcStartBitsBK, lSrcWidth, lSrcHeight, true);
	pDoc->SetModifiedFlag(TRUE);
	pDoc->UpdateAllViews(NULL);
	::GlobalUnlock((HGLOBAL)pDoc->GetHObject());// 解除锁定
}

void CMFCApplication1View::OnAncient()
{
	// TODO: 在此添加命令处理程序代码
	CMFCApplication1Doc* pDoc = GetDocument();// 获取文档
////////////////////////////////////////////////////////////////////////////////////////////////	
	long	lSrcLineBytes;		//图象每行的字节数
	long	lSrcWidth;      //图象的宽度和高度
	long	lSrcHeight;
	int     lpSrcBitCount;       //图像的位深
	LPSTR	lpSrcDib;		//指向源图象的指针
	LPSTR	lpSrcStartBits;	//指向源像素的指针
	lpSrcDib = (LPSTR) ::GlobalLock((HGLOBAL)pDoc->GetHObject());// 锁定DIB
	if (!lpSrcDib) return;

	if (pDoc->m_dib.GetColorNum(lpSrcDib) != 256)// 判断是否是8-bpp位图
	{
		AfxMessageBox(L"对不起，不是256色位图！");// 警告
		::GlobalUnlock((HGLOBAL)pDoc->GetHObject());// 解除锁定
		return;									//返回
	}										//判断是否是8-bpp位图,不是则返回
	lpSrcStartBits = pDoc->m_dib.GetBits(lpSrcDib);			// 找到DIB图象像素起始位置
	lSrcWidth = pDoc->m_dib.GetWidth(lpSrcDib);					// 获取图象的宽度		
	lSrcHeight = pDoc->m_dib.GetHeight(lpSrcDib);					// 获取图象的高度	
	lpSrcBitCount = pDoc->m_dib.GetBitCount(lpSrcDib);                    //获取图像位深
	lSrcLineBytes = pDoc->m_dib.GetReqByteWidth(lSrcWidth * lpSrcBitCount);		// 计算图象每行的字节数
/////////////////////////////////////////////////////////////////////////////////////////////////
	unsigned char* lpSrc;

	LONG i;
	LONG j;

	// 灰度映射表
	BYTE bMapR[256];
	BYTE bMapG[256];
	BYTE bMapB[256];
	RGBQUAD* pTable, * pTable1;//颜色表指针

	pTable = (RGBQUAD*)(lpSrcDib + sizeof(BITMAPINFOHEADER));

	for (i = 0; i < 256; i++)//生成新的调色板
	{	
		pTable->rgbRed = (BYTE)i;
		pTable->rgbGreen = (BYTE)i;
		pTable->rgbBlue = (BYTE)i;
		pTable->rgbReserved = (BYTE)0;
		bMapR[i] = (BYTE)min((0.393 * pTable->rgbRed + 0.769 * pTable->rgbGreen + 0.189 * pTable->rgbBlue + 0.5),255);
		bMapG[i] = (BYTE)min((0.349 * pTable->rgbRed + 0.686 * pTable->rgbGreen + 0.168 * pTable->rgbBlue + 0.5),255);
		bMapB[i] = (BYTE)min((0.272 * pTable->rgbRed + 0.534 * pTable->rgbGreen + 0.131 * pTable->rgbBlue + 0.5),255);
		pTable++;
	}
	LPBITMAPINFO lpbmi;
	BOOL bWinStyleDIB;
	LPBITMAPCOREINFO lpbmc;
	lpbmi = (LPBITMAPINFO)lpSrcDib;
	lpbmc = (LPBITMAPCOREINFO)lpSrcDib;
	for (i = 0; i < 256; i++) {
		lpbmi->bmiColors[i].rgbRed = bMapR[i];
		lpbmi->bmiColors[i].rgbGreen = bMapG[i];
		lpbmi->bmiColors[i].rgbBlue = bMapB[i];
		lpbmi->bmiColors[i].rgbReserved = 0;
	}
	pDoc->SetModifiedFlag(true);
	pDoc->UpdateAllViews(NULL);
	::GlobalUnlock((HGLOBAL)pDoc->GetHObject());// 解除锁定
}

void CMFCApplication1View::OnMosaic()
{
	// TODO: 在此添加命令处理程序代码
	CMFCApplication1Doc* pDoc = GetDocument();// 获取文档
////////////////////////////////////////////////////////////////////////////////////////////////	
	long	lSrcLineBytes;		//图象每行的字节数
	long	lSrcWidth;      //图象的宽度和高度
	long	lSrcHeight;
	int     lpSrcBitCount;       //图像的位深
	LPSTR	lpSrcDib;		//指向源图象的指针
	LPSTR	lpSrcStartBits;	//指向源像素的指针
	lpSrcDib = (LPSTR) ::GlobalLock((HGLOBAL)pDoc->GetHObject());// 锁定DIB
	if (!lpSrcDib) return;

	//if (pDoc->m_dib.GetColorNum(lpSrcDib) != 256)// 判断是否是8-bpp位图
	//{
	//	AfxMessageBox(L"对不起，不是256色位图！");// 警告
	//	::GlobalUnlock((HGLOBAL)pDoc->GetHObject());// 解除锁定
	//	return;									//返回
	//}										//判断是否是8-bpp位图,不是则返回
	lpSrcStartBits = pDoc->m_dib.GetBits(lpSrcDib);			// 找到DIB图象像素起始位置
	lSrcWidth = pDoc->m_dib.GetWidth(lpSrcDib);					// 获取图象的宽度		
	lSrcHeight = pDoc->m_dib.GetHeight(lpSrcDib);					// 获取图象的高度	
	lpSrcBitCount = pDoc->m_dib.GetBitCount(lpSrcDib);                    //获取图像位深
	lSrcLineBytes = pDoc->m_dib.GetReqByteWidth(lSrcWidth * lpSrcBitCount);		// 计算图象每行的字节数
/////////////////////////////////////////////////////////////////////////////////////////////////
	int x = 8;
	unsigned char* lpSrc1,* lpSrc2;
	for (int i = 0; i + x < lSrcWidth; i += x)
	{
		for (int j = 0; j + x < lSrcHeight; j += x)
		{
			lpSrc1 = (unsigned char*)lpSrcStartBits + lSrcLineBytes * (lSrcHeight - 1 - i) + j;
			for (int newi = i; newi < i + x; newi++)
			{
				for (int newj = j; newj < j + x; newj++)
				{//取每个块的最下角的像素点 作为该马赛克块的所有的像素点 	
					lpSrc2 = (unsigned char*)lpSrcStartBits + lSrcLineBytes * (lSrcHeight - 1 - newi) + newj;
					*lpSrc2 = *lpSrc1;
				}
			}
		}
	}
	pDoc->SetModifiedFlag(true);
	pDoc->UpdateAllViews(NULL);
	::GlobalUnlock((HGLOBAL)pDoc->GetHObject());// 解除锁定
}

void CMFCApplication1View::Onrelief()
{
	// TODO: 在此添加命令处理程序代码
	CMFCApplication1Doc* pDoc = GetDocument();// 获取文档
////////////////////////////////////////////////////////////////////////////////////////////////	
	long	lSrcLineBytes;		//图象每行的字节数
	long	lSrcWidth;      //图象的宽度和高度
	long	lSrcHeight;
	int     lpSrcBitCount;       //图像的位深
	LPSTR	lpSrcDib;		//指向源图象的指针
	LPSTR	lpSrcStartBits;	//指向源像素的指针
	lpSrcDib = (LPSTR) ::GlobalLock((HGLOBAL)pDoc->GetHObject());// 锁定DIB
	if (!lpSrcDib) return;

	//if (pDoc->m_dib.GetColorNum(lpSrcDib) != 256)// 判断是否是8-bpp位图
	//{
	//	AfxMessageBox(L"对不起，不是256色位图！");// 警告
	//	::GlobalUnlock((HGLOBAL)pDoc->GetHObject());// 解除锁定
	//	return;									//返回
	//}										//判断是否是8-bpp位图,不是则返回
	lpSrcStartBits = pDoc->m_dib.GetBits(lpSrcDib);			// 找到DIB图象像素起始位置
	lSrcWidth = pDoc->m_dib.GetWidth(lpSrcDib);					// 获取图象的宽度		
	lSrcHeight = pDoc->m_dib.GetHeight(lpSrcDib);					// 获取图象的高度	
	lpSrcBitCount = pDoc->m_dib.GetBitCount(lpSrcDib);                    //获取图像位深
	lSrcLineBytes = pDoc->m_dib.GetReqByteWidth(lSrcWidth * lpSrcBitCount);		// 计算图象每行的字节数
/////////////////////////////////////////////////////////////////////////////////////////////////
	unsigned char* lpSrc1, * lpSrc2;
	LONG fTemp;
	for (int i = 0; i < lSrcWidth; i ++)
	{
		for (int j = 0; j < lSrcHeight; j ++)
		{
			lpSrc1 = (unsigned char*)lpSrcStartBits + lSrcLineBytes * (lSrcHeight - 1 - i) + j;
			lpSrc2 = (unsigned char*)lpSrcStartBits + lSrcLineBytes * (lSrcHeight - 1 - i) + j + 1;
			fTemp = *lpSrc1 - *lpSrc2 + 150;
			if (fTemp > 255)
				fTemp = 255;
			else if (fTemp < 0)
				fTemp = 0;
			*lpSrc1 = fTemp;
		}
	}
	pDoc->SetModifiedFlag(true);
	pDoc->UpdateAllViews(NULL);
	::GlobalUnlock((HGLOBAL)pDoc->GetHObject());// 解除锁定
}

BOOL SobelDIBLevel(LPSTR lpDIBBits, LONG lWidth, LONG lHeight)
{
	// 指向缓存图像的指针
	LPSTR	lpDst1;
	LPSTR	lpDst2;
	// 指向缓存DIB图像的指针
	LPSTR	lpNewDIBBits1;
	HLOCAL	hNewDIBBits1;
	LPSTR	lpNewDIBBits2;
	HLOCAL	hNewDIBBits2;
	//循环变量
	long i;
	long j;
	// 模板高度
	int		iTempH;
	// 模板宽度
	int		iTempW;
	// 模板系数
	FLOAT	fTempC;
	// 模板中心元素X坐标
	int		iTempMX;
	// 模板中心元素Y坐标
	int		iTempMY;
	//模板数组
	FLOAT aTemplate[9];
	// 暂时分配内存，以保存新图像
	hNewDIBBits1 = LocalAlloc(LHND, lWidth * lHeight);
	if (hNewDIBBits1 == NULL)
	{
		// 分配内存失败
		return FALSE;
	}
	// 锁定内存
	lpNewDIBBits1 = (char*)LocalLock(hNewDIBBits1);

	// 暂时分配内存，以保存新图像
	hNewDIBBits2 = LocalAlloc(LHND, lWidth * lHeight);

	if (hNewDIBBits2 == NULL)
	{
		// 分配内存失败
		return FALSE;
	}

	// 锁定内存
	lpNewDIBBits2 = (char*)LocalLock(hNewDIBBits2);

	// 拷贝源图像到缓存图像中
	lpDst1 = (char*)lpNewDIBBits1;
	memcpy(lpNewDIBBits1, lpDIBBits, lWidth * lHeight);
	lpDst2 = (char*)lpNewDIBBits2;
	memcpy(lpNewDIBBits2, lpDIBBits, lWidth * lHeight);

	// 设置Sobel模板参数
	iTempW = 3;
	iTempH = 3;
	fTempC = 1.0;
	iTempMX = 1;
	iTempMY = 1;
	aTemplate[0] = -1.0;
	aTemplate[1] = 0;
	aTemplate[2] = 1.0;
	aTemplate[3] = -2.0;
	aTemplate[4] = 0.0;
	aTemplate[5] = 2.0;
	aTemplate[6] = -1.0;
	aTemplate[7] = 0.0;
	aTemplate[8] = 1.0;

	// 调用Template()函数
	if (!Template(lpNewDIBBits1, lWidth, lHeight,
		iTempH, iTempW, iTempMX, iTempMY, aTemplate, fTempC))
	{
		return FALSE;
	}

	// 设置Sobel模板参数
	aTemplate[0] = -1.0;
	aTemplate[1] = 0.0;
	aTemplate[2] = 1.0;
	aTemplate[3] = -2.0;
	aTemplate[4] = 0.0;
	aTemplate[5] = 2.0;
	aTemplate[6] = -1.0;
	aTemplate[7] = 0.0;
	aTemplate[8] = 1.0;

	// 调用Template()函数
	if (!Template(lpNewDIBBits2, lWidth, lHeight,
		iTempH, iTempW, iTempMX, iTempMY, aTemplate, fTempC))
	{
		return FALSE;
	}

	//求两幅缓存图像的最大值
	for (j = 0; j < lHeight; j++)
	{
		for (i = 0; i < lWidth - 1; i++)
		{

			// 指向缓存图像1倒数第j行，第i个象素的指针			
			lpDst1 = (char*)lpNewDIBBits1 + lWidth * j + i;

			// 指向缓存图像2倒数第j行，第i个象素的指针			
			lpDst2 = (char*)lpNewDIBBits2 + lWidth * j + i;

			if (*lpDst2 > *lpDst1)
				*lpDst1 = *lpDst2;

		}
	}

	// 复制经过模板运算后的图像到源图像
	memcpy(lpDIBBits, lpNewDIBBits1, lWidth * lHeight);

	// 释放内存
	LocalUnlock(hNewDIBBits1);
	LocalFree(hNewDIBBits1);

	LocalUnlock(hNewDIBBits2);
	LocalFree(hNewDIBBits2);
	// 返回
	return TRUE;
}
BOOL PrewittDIBLevel(LPSTR lpDIBBits, LONG lWidth, LONG lHeight)
{

	// 指向缓存图像的指针
	LPSTR	lpDst1;
	LPSTR	lpDst2;

	// 指向缓存DIB图像的指针
	LPSTR	lpNewDIBBits1;
	HLOCAL	hNewDIBBits1;
	LPSTR	lpNewDIBBits2;
	HLOCAL	hNewDIBBits2;

	//循环变量
	long i;
	long j;

	// 模板高度
	int		iTempH;

	// 模板宽度
	int		iTempW;

	// 模板系数
	FLOAT	fTempC;

	// 模板中心元素X坐标
	int		iTempMX;

	// 模板中心元素Y坐标
	int		iTempMY;

	//模板数组
	FLOAT aTemplate[9];

	// 暂时分配内存，以保存新图像
	hNewDIBBits1 = LocalAlloc(LHND, lWidth * lHeight);

	if (hNewDIBBits1 == NULL)
	{
		// 分配内存失败
		return FALSE;
	}

	// 锁定内存
	lpNewDIBBits1 = (char*)LocalLock(hNewDIBBits1);

	// 暂时分配内存，以保存新图像
	hNewDIBBits2 = LocalAlloc(LHND, lWidth * lHeight);

	if (hNewDIBBits2 == NULL)
	{
		// 分配内存失败
		return FALSE;
	}

	// 锁定内存
	lpNewDIBBits2 = (char*)LocalLock(hNewDIBBits2);

	// 拷贝源图像到缓存图像中
	lpDst1 = (char*)lpNewDIBBits1;
	memcpy(lpNewDIBBits1, lpDIBBits, lWidth * lHeight);
	lpDst2 = (char*)lpNewDIBBits2;
	memcpy(lpNewDIBBits2, lpDIBBits, lWidth * lHeight);


	// 设置Prewitt模板参数
	iTempW = 3;
	iTempH = 3;
	fTempC = 1.0;
	iTempMX = 1;
	iTempMY = 1;
	aTemplate[0] = -1.0;
	aTemplate[1] = 0.0;
	aTemplate[2] = 1.0;
	aTemplate[3] = -1.0;
	aTemplate[4] = 0.0;
	aTemplate[5] = 1.0;
	aTemplate[6] = -1.0;
	aTemplate[7] = 0.0;
	aTemplate[8] = 1.0;

	// 调用Template()函数
	if (!Template(lpNewDIBBits1, lWidth, lHeight,
		iTempH, iTempW, iTempMX, iTempMY, aTemplate, fTempC))
	{
		return FALSE;
	}

	// 设置Prewitt模板参数
	aTemplate[0] = 1.0;
	aTemplate[1] = 0.0;
	aTemplate[2] = -1.0;
	aTemplate[3] = 1.0;
	aTemplate[4] = 0.0;
	aTemplate[5] = -1.0;
	aTemplate[6] = 1.0;
	aTemplate[7] = 0.0;
	aTemplate[8] = -1.0;

	// 调用Template()函数
	if (!Template(lpNewDIBBits2, lWidth, lHeight,
		iTempH, iTempW, iTempMX, iTempMY, aTemplate, fTempC))
	{
		return FALSE;
	}

	//求两幅缓存图像的最大值
	for (j = 0; j < lHeight; j++)
	{
		for (i = 0; i < lWidth - 1; i++)
		{

			// 指向缓存图像1倒数第j行，第i个象素的指针			
			lpDst1 = (char*)lpNewDIBBits1 + lWidth * j + i;

			// 指向缓存图像2倒数第j行，第i个象素的指针			
			lpDst2 = (char*)lpNewDIBBits2 + lWidth * j + i;

			if (*lpDst2 > *lpDst1)
				*lpDst1 = *lpDst2;

		}
	}

	// 复制经过模板运算后的图像到源图像
	memcpy(lpDIBBits, lpNewDIBBits1, lWidth * lHeight);

	// 释放内存
	LocalUnlock(hNewDIBBits1);
	LocalFree(hNewDIBBits1);

	LocalUnlock(hNewDIBBits2);
	LocalFree(hNewDIBBits2);
	// 返回
	return TRUE;
}

void CMFCApplication1View::OnFilter()
{
	// TODO: 在此添加命令处理程序代码
	CMFCApplication1Doc* pDoc = GetDocument();// 获取文档
////////////////////////////////////////////////////////////////////////////////////////////////	
	long	lSrcLineBytes;		//图象每行的字节数
	long	lSrcWidth;      //图象的宽度和高度
	long	lSrcHeight;
	int     lpSrcBitCount;       //图像的位深
	LPSTR	lpSrcDib;		//指向源图象的指针
	LPSTR	lpSrcStartBits;	//指向源像素的指针
	lpSrcDib = (LPSTR) ::GlobalLock((HGLOBAL)pDoc->GetHObject());// 锁定DIB
	if (!lpSrcDib) return;

	//if (pDoc->m_dib.GetColorNum(lpSrcDib) != 256)// 判断是否是8-bpp位图
	//{
	//	AfxMessageBox(L"对不起，不是256色位图！");// 警告
	//	::GlobalUnlock((HGLOBAL)pDoc->GetHObject());// 解除锁定
	//	return;									//返回
	//}										//判断是否是8-bpp位图,不是则返回
	lpSrcStartBits = pDoc->m_dib.GetBits(lpSrcDib);			// 找到DIB图象像素起始位置
	lSrcWidth = pDoc->m_dib.GetWidth(lpSrcDib);					// 获取图象的宽度		
	lSrcHeight = pDoc->m_dib.GetHeight(lpSrcDib);					// 获取图象的高度	
	lpSrcBitCount = pDoc->m_dib.GetBitCount(lpSrcDib);                    //获取图像位深
	lSrcLineBytes = pDoc->m_dib.GetReqByteWidth(lSrcWidth * lpSrcBitCount);		// 计算图象每行的字节数
/////////////////////////////////////////////////////////////////////////////////////////////////
	CDlgFilter dlgPara;
	FLOAT	aValue[9];
	if (dlgPara.DoModal() != IDOK)
	{
		// 返回
		return;
	}
	if (dlgPara.m_OperatorType == 0) {
		FLOAT fA = -1.0;
		FLOAT fB = 255;
		unsigned char* lpSrc;
		LONG i;
		LONG j;

		LONG fTemp;

		for (i = 0; i < lSrcHeight; i++)
			for (j = 0; j < lSrcWidth; j++)
			{
				lpSrc = (unsigned char*)lpSrcStartBits + lSrcLineBytes * (lSrcHeight - 1 - i) + j;
				fTemp = fA * (*lpSrc) + fB;
				if (fTemp >= 255)
				{
					*lpSrc = 255;
				}
				else if (fTemp <= 0)
				{
					*lpSrc = 0;
				}
				else
				{
					*lpSrc = (unsigned char)(fTemp + 0.5);
				}
			}
	}
	else if (dlgPara.m_OperatorType == 1) {
		aValue[0] = 1.0;
		aValue[1] = 1.0;
		aValue[2] = 1.0;
		aValue[3] = 1.0;
		aValue[4] = 1.0;
		aValue[5] = 1.0;
		aValue[6] = 1.0;
		aValue[7] = 1.0;
		aValue[8] = 1.0;
		Template(lpSrcStartBits, lSrcWidth, lSrcHeight, 3, 3, 1, 1, aValue, (FLOAT)(1.0 / 9.0));
	}
	else if (dlgPara.m_OperatorType == 2) {
		aValue[0] = 1.0;
		aValue[1] = 2.0;
		aValue[2] = 1.0;
		aValue[3] = 2.0;
		aValue[4] = 4.0;
		aValue[5] = 2.0;
		aValue[6] = 1.0;
		aValue[7] = 2.0;
		aValue[8] = 1.0;
		Template(lpSrcStartBits, lSrcWidth, lSrcHeight, 3, 3, 1, 1, aValue, (FLOAT)(1.0 / 16.0));
		dlgPara.m_Coefficient = (FLOAT)(1.0 / 16.0);
	}
	else if (dlgPara.m_OperatorType == 3) {
		aValue[0] = -1.0;
		aValue[1] = -1.0;
		aValue[2] = -1.0;
		aValue[3] = -1.0;
		aValue[4] = 9.0;
		aValue[5] = -1.0;
		aValue[6] = -1.0;
		aValue[7] = -1.0;
		aValue[8] = -1.0;
		Template(lpSrcStartBits, lSrcWidth, lSrcHeight, 3, 3, 1, 1, aValue, 1.0);
	}
	else if (dlgPara.m_OperatorType == 4) {
		Onrelief();
	}
	else if (dlgPara.m_OperatorType == 5) {
		unsigned char* lpSrc;
		LONG i;
		LONG j;

		LONG fTemp;

		for (i = 0; i < lSrcHeight; i++)
			for (j = 0; j < lSrcWidth; j++)
			{
				lpSrc = (unsigned char*)lpSrcStartBits + (lSrcLineBytes) * (lSrcHeight - 1 - i) + j;
				fTemp = *lpSrc + dlgPara.m_Constant;
				if (fTemp >= 255)
				{
					*lpSrc = 255;
				}
				else if (fTemp <= 0)
				{
					*lpSrc = 0;
				}
				else
				{
					*lpSrc = (unsigned char)(fTemp + 0.5);
				}
			}
	}
	else if (dlgPara.m_OperatorType == 6) {
		aValue[0] = dlgPara.m_Array[0];
		aValue[1] = dlgPara.m_Array[1];
		aValue[2] = dlgPara.m_Array[2];
		aValue[3] = dlgPara.m_Array[3];
		aValue[4] = dlgPara.m_Array[4];
		aValue[5] = dlgPara.m_Array[5];
		aValue[6] = dlgPara.m_Array[6];
		aValue[7] = dlgPara.m_Array[7];
		aValue[8] = dlgPara.m_Array[8]; 
		float Coefficient = dlgPara.m_Coefficient;
		Template(lpSrcStartBits, lSrcWidth, lSrcHeight, 3, 3, 1, 1, aValue, Coefficient);
	}
	else if (dlgPara.m_OperatorType == 7) {
		if (dlgPara.m_EdgeDirectionType == 0) {
			SobelDIB(lpSrcStartBits, WIDTHBYTES(lSrcWidth * 8), lSrcHeight);
		}
		else if (dlgPara.m_EdgeDirectionType == 1) {
			SobelDIBLevel(lpSrcStartBits, WIDTHBYTES(lSrcWidth * 8), lSrcHeight);
		}
	}
	else if (dlgPara.m_OperatorType == 8) {
		if (dlgPara.m_EdgeDirectionType == 0) {
			PrewittDIB(lpSrcStartBits, WIDTHBYTES(lSrcWidth * 8), lSrcHeight);
		}
		else if (dlgPara.m_EdgeDirectionType == 1) {
			PrewittDIBLevel(lpSrcStartBits, WIDTHBYTES(lSrcWidth * 8), lSrcHeight);
		}
	}
	pDoc->SetModifiedFlag(true);
	pDoc->UpdateAllViews(NULL);
	::GlobalUnlock((HGLOBAL)pDoc->GetHObject());// 解除锁定
}

int PixelCounter(cv::Mat src, int nflag)
{

	int nCount_White = 0;//白
	int nCount_Black = 0;//黑

	//通过迭代器访问图像的像素点
	cv::Mat_<uchar>::iterator itor = src.begin<uchar>();
	cv::Mat_<uchar>::iterator itorEnd = src.end<uchar>();
	for (; itor != itorEnd; ++itor)
	{
		if ((*itor) > 0)
		{
			//白：像素值 ptr:255
			nCount_White += 1;
		}
		else
		{
			//黑：像素值 ptr:0
			nCount_Black += 1;
		}

	}

	//根据nflag返回黑或白像素个数
	if (nflag == 1)
	{
		//白
		return nCount_White;
	}
	else
	{
		//黑
		return nCount_Black;
	}

}

void CMFCApplication1View::OnAreacount()
{
	// TODO: 在此添加命令处理程序代码
	CMFCApplication1Doc* pDoc = GetDocument();// 获取文档
	USES_CONVERSION;
	cv::String cvStr = W2A(pDoc->GetPathName());
	cv::Mat img = cv::imread(cvStr, cv::IMREAD_COLOR);
	cv::Mat imgSmooth, imgGray,imgThre,imgdst;
	cvtColor(img, imgGray, cv::COLOR_BGR2GRAY);
	GaussianBlur(imgGray, imgSmooth, cv::Size(5, 5), 0, 0);
	threshold(imgSmooth, imgThre, 0, 255, cv::THRESH_OTSU);
	int nWhiteCount = PixelCounter(imgThre, 1);
	int nBlackCount = PixelCounter(imgThre, 2);
	CDlgAreaCount dlgPara;
	if (dlgPara.DoModal() != IDOK)
	{
		// 返回
		return;
	}
	cv::Mat imgMor;
	cv::Mat element;
	if (dlgPara.m_NumberOfConnected == 0) {
		element = cv::getStructuringElement(cv::MORPH_RECT, cv::Size(4, 4));
	}
	else if (dlgPara.m_NumberOfConnected == 1) {
		element = cv::getStructuringElement(cv::MORPH_RECT, cv::Size(8, 8));
	}
	morphologyEx(imgThre, imgMor, cv::MORPH_OPEN, element);

	if (dlgPara.m_ForegroundType == 0) {
		/*threshold(imgSmooth, imgThre, 0, 255, cv::THRESH_BINARY_INV);*/
		int height = imgMor.rows;
		int width = imgMor.cols;
		for (int row = 0; row < height; row++)
		{
			for (int col = 0; col < width; col++)
			{
				int gray = imgMor.at<uchar>(row, col);
				imgMor.at<uchar>(row, col) = 255 - gray;
			}
		}
		imgdst = imgMor;
	}
	else if (dlgPara.m_ForegroundType == 1) {
		imgdst = imgMor;
	}
	else if (dlgPara.m_ForegroundType == 2) {
		if (nWhiteCount > nBlackCount) {
			int height = imgMor.rows;
			int width = imgMor.cols;
			for (int row = 0; row < height; row++)
			{
				for (int col = 0; col < width; col++)
				{
					int gray = imgMor.at<uchar>(row, col);
					imgMor.at<uchar>(row, col) = 255 - gray;
				}
			}
			imgdst = imgMor;
		}
		else {
			imgdst = imgMor;
		}
	}
	cv::imshow("Image", imgdst);
	cv::Mat imgfinal;
	std::vector<std::vector<cv::Point>> contours;
	std::vector<cv::Vec4i> hierarchy;
	findContours(imgMor, contours, hierarchy, cv::RETR_EXTERNAL, cv::CHAIN_APPROX_SIMPLE);
	//cv::imshow("Image", imgMor);
	/*drawContours(imgMor, contours, -1, cv::Scalar(255, 0, 255), 2);*/
	std::vector<std::vector<cv::Point>> conPoly(contours.size());
	std::vector<cv::Rect> boundRect(contours.size());
	double maxArea = 0;
	double maxPerimeter = 0;
	double maxRoundness = 0;
	double maxLenratio = 0;
	int count = 0;
 	for (int i = 0; i < contours.size(); i++)
	{
		int area = contourArea(contours[i]);
		if (area < 10)
			continue;
		count++;
		if (maxArea < area) {
			maxArea = area;
		}
		int perimeter = arcLength(contours[i],true);
		if (maxPerimeter < perimeter) {
			maxPerimeter = perimeter;
		}
		double roundness = (4 * CV_PI * area) / (perimeter * perimeter);
		if (maxRoundness < roundness) {
			maxRoundness = roundness;
		}
		cv::RotatedRect minrect = cv::minAreaRect(contours[i]);
		double lenratio = perimeter / (minrect.size.height > minrect.size.width ? minrect.size.height : minrect.size.width);
		if (maxLenratio < lenratio) {
			maxLenratio = lenratio;
		}
	}
	dlgPara.m_maxArea = maxArea;
	dlgPara.m_maxPerimeter = maxPerimeter;
	dlgPara.m_maxRoundness = maxRoundness;
	dlgPara.m_maxLenratio = maxLenratio;
	dlgPara.m_count = count;
	pDoc->SetModifiedFlag(true);
	pDoc->UpdateAllViews(NULL);
	::GlobalUnlock((HGLOBAL)pDoc->GetHObject());// 解除锁定
}

void CMFCApplication1View::OnUsm()
{
	// TODO: 在此添加命令处理程序代码
	CMFCApplication1Doc* pDoc = GetDocument();// 获取文档
	USES_CONVERSION;
	cv::String cvStr = W2A(pDoc->GetPathName());
	cv::Mat img = cv::imread(cvStr, cv::IMREAD_COLOR);
	cv::Mat blur_usm, dst_usm;
	cv::GaussianBlur(img, blur_usm, cv::Size(0, 0), 25);
	cv::addWeighted(img, 1.5, blur_usm, -0.5, 0, dst_usm);
	imshow("USM", dst_usm);
}


void CMFCApplication1View::OnLog()
{
	// TODO: 在此添加命令处理程序代码
	CMFCApplication1Doc* pDoc = GetDocument();// 获取文档
////////////////////////////////////////////////////////////////////////////////////////////////	
	long	lSrcLineBytes;		//图象每行的字节数
	long	lSrcWidth;      //图象的宽度和高度
	long	lSrcHeight;
	int     lpSrcBitCount;       //图像的位深
	LPSTR	lpSrcDib;		//指向源图象的指针
	LPSTR	lpSrcStartBits;	//指向源像素的指针
	lpSrcDib = (LPSTR) ::GlobalLock((HGLOBAL)pDoc->GetHObject());// 锁定DIB
	if (!lpSrcDib) return;

	//if (pDoc->m_dib.GetColorNum(lpSrcDib) != 256)// 判断是否是8-bpp位图
	//{
	//	AfxMessageBox(L"对不起，不是256色位图！");// 警告
	//	::GlobalUnlock((HGLOBAL)pDoc->GetHObject());// 解除锁定
	//	return;									//返回
	//}										//判断是否是8-bpp位图,不是则返回
	lpSrcStartBits = pDoc->m_dib.GetBits(lpSrcDib);			// 找到DIB图象像素起始位置
	lSrcWidth = pDoc->m_dib.GetWidth(lpSrcDib);					// 获取图象的宽度		
	lSrcHeight = pDoc->m_dib.GetHeight(lpSrcDib);					// 获取图象的高度	
	lpSrcBitCount = pDoc->m_dib.GetBitCount(lpSrcDib);                    //获取图像位深
	lSrcLineBytes = pDoc->m_dib.GetReqByteWidth(lSrcWidth * lpSrcBitCount);		// 计算图象每行的字节数
/////////////////////////////////////////////////////////////////////////////////////////////////
	unsigned char* lpSrc;
	LONG i;
	LONG j;
	LONG fTemp;
	for (i = 0; i < lSrcHeight; i++)
		for (j = 0; j < lSrcWidth; j++)
		{
			lpSrc = (unsigned char*)lpSrcStartBits + lSrcLineBytes * (lSrcHeight - 1 - i) + j;
			fTemp = 10 * log(double(*lpSrc + 1));
			if (fTemp >= 255)
			{
				*lpSrc = 255;
			}
			else if (fTemp <= 0)
			{
				*lpSrc = 0;
			}
			else
			{
				*lpSrc = (unsigned char)(fTemp + 0.5);
			}
		}
	OnEqualization();
	pDoc->SetModifiedFlag(true);
	pDoc->UpdateAllViews(NULL);
	::GlobalUnlock((HGLOBAL)pDoc->GetHObject());// 解除锁定
}


void CMFCApplication1View::OnGamma()
{
	// TODO: 在此添加命令处理程序代码
	CMFCApplication1Doc* pDoc = GetDocument();// 获取文档
////////////////////////////////////////////////////////////////////////////////////////////////	
	long	lSrcLineBytes;		//图象每行的字节数
	long	lSrcWidth;      //图象的宽度和高度
	long	lSrcHeight;
	int     lpSrcBitCount;       //图像的位深
	LPSTR	lpSrcDib;		//指向源图象的指针
	LPSTR	lpSrcStartBits;	//指向源像素的指针
	lpSrcDib = (LPSTR) ::GlobalLock((HGLOBAL)pDoc->GetHObject());// 锁定DIB
	if (!lpSrcDib) return;

	//if (pDoc->m_dib.GetColorNum(lpSrcDib) != 256)// 判断是否是8-bpp位图
	//{
	//	AfxMessageBox(L"对不起，不是256色位图！");// 警告
	//	::GlobalUnlock((HGLOBAL)pDoc->GetHObject());// 解除锁定
	//	return;									//返回
	//}										//判断是否是8-bpp位图,不是则返回
	lpSrcStartBits = pDoc->m_dib.GetBits(lpSrcDib);			// 找到DIB图象像素起始位置
	lSrcWidth = pDoc->m_dib.GetWidth(lpSrcDib);					// 获取图象的宽度		
	lSrcHeight = pDoc->m_dib.GetHeight(lpSrcDib);					// 获取图象的高度	
	lpSrcBitCount = pDoc->m_dib.GetBitCount(lpSrcDib);                    //获取图像位深
	lSrcLineBytes = pDoc->m_dib.GetReqByteWidth(lSrcWidth * lpSrcBitCount);		// 计算图象每行的字节数
/////////////////////////////////////////////////////////////////////////////////////////////////
	unsigned char* lpSrc;
	LONG i;
	LONG j;
	LONG fTemp;
	float fNormalFactor = 1.0f / 255.0f;
	float fGamma = 1.0f / 2.2f; 
	for (i = 0; i < lSrcHeight; i++)
		for (j = 0; j < lSrcWidth; j++)
		{
			lpSrc = (unsigned char*)lpSrcStartBits + lSrcLineBytes * (lSrcHeight - 1 - i) + j;
			fTemp = std::pow((*lpSrc) * fNormalFactor, fGamma)*255;
			if (fTemp >= 255)
			{
				*lpSrc = 255;
			}
			else if (fTemp <= 0)
			{
				*lpSrc = 0;
			}
			else
			{
				*lpSrc = (unsigned char)(fTemp + 0.5);
			}
		}
	pDoc->SetModifiedFlag(true);
	pDoc->UpdateAllViews(NULL);
	::GlobalUnlock((HGLOBAL)pDoc->GetHObject());// 解除锁定
}
