﻿// CDlgGrayStretch.cpp: 实现文件
//

#include "pch.h"
#include "MFCApplication1.h"
#include "CDlgGrayStretch.h"
#include "afxdialogex.h"

#include "MainFrm.h"
#include "MFCApplication1Doc.h"
#define WIDTHBYTES(bits)    (((bits) + 31) / 32 * 4)

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

// CDlgGrayStretch 对话框

IMPLEMENT_DYNAMIC(CDlgGrayStretch, CDialogEx)

CDlgGrayStretch::CDlgGrayStretch(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_GrayStretch, pParent)
{
	m_bX1 = 0;
	m_bY1 = 0;
	m_bX2 = 0;
	m_bY2 = 0;
}

CDlgGrayStretch::~CDlgGrayStretch()
{
}

void CDlgGrayStretch::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_X1, m_bX1);
	DDV_MinMaxByte(pDX, m_bX1, 0, 255);
	DDX_Text(pDX, IDC_EDIT_X2, m_bX2);
	DDV_MinMaxByte(pDX, m_bY1, 0, 255);
	DDX_Text(pDX, IDC_EDIT_Y1, m_bY1);
	DDV_MinMaxByte(pDX, m_bX2, 0, 255);
	DDX_Text(pDX, IDC_EDIT_Y2, m_bY2);
	DDV_MinMaxByte(pDX, m_bY2, 0, 255);
}


BEGIN_MESSAGE_MAP(CDlgGrayStretch, CDialogEx)
	ON_WM_LBUTTONDOWN()
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONUP()
	ON_WM_PAINT()
	ON_EN_KILLFOCUS(IDC_EDIT_X1, OnKillfocusEditX1)
	ON_EN_KILLFOCUS(IDC_EDIT_X2, OnKillfocusEditX2)
	ON_EN_KILLFOCUS(IDC_EDIT_Y1, OnKillfocusEditY1)
	ON_EN_KILLFOCUS(IDC_EDIT_Y2, OnKillfocusEditY2)
	ON_BN_CLICKED(IDC_preview2, &CDlgGrayStretch::OnBnClickedpreview2)
	ON_BN_CLICKED(IDC_recover2, &CDlgGrayStretch::OnBnClickedrecover2)
END_MESSAGE_MAP()


// CDlgGrayStretch 消息处理程序
BOOL CDlgGrayStretch::OnInitDialog()
{

	// 调用默认OnInitDialog函数
	CDialog::OnInitDialog();

	// 获取绘制直方图的标签
	CWnd* pWnd = GetDlgItem(IDC_COOR);

	// 计算接受鼠标事件的有效区域
	pWnd->GetClientRect(m_MouseRect);
	pWnd->ClientToScreen(&m_MouseRect);

	CRect rect;
	GetClientRect(rect);
	ClientToScreen(&rect);

	m_MouseRect.top -= rect.top;
	m_MouseRect.left -= rect.left;

	// 设置接受鼠标事件的有效区域
	m_MouseRect.top += 25;
	m_MouseRect.left += 10;
	m_MouseRect.bottom = m_MouseRect.top + 255;
	m_MouseRect.right = m_MouseRect.left + 256;

	// 初始化拖动状态
	m_iIsDraging = 0;

	return TRUE;  // return TRUE unless you set the focus to a control
				  // EXCEPTION: OCX Property Pages should return FALSE
}

void CDlgGrayStretch::OnKillfocusEditX1()
{
	// 更新
	UpdateData(TRUE);

	// 判断是否下限超过上限
	if (m_bX1 > m_bX2)
	{
		// 互换
		BYTE bTemp = m_bX1;
		m_bX1 = m_bX2;
		m_bX2 = bTemp;
		bTemp = m_bY1;
		m_bY1 = m_bY2;
		m_bY2 = bTemp;

		// 更新
		UpdateData(FALSE);
	}

	// 重绘
	InvalidateRect(m_MouseRect, TRUE);
}

void CDlgGrayStretch::OnKillfocusEditX2()
{
	// 更新
	UpdateData(TRUE);

	// 判断是否下限超过上限
	if (m_bX1 > m_bX2)
	{
		// 互换
		BYTE bTemp = m_bX1;
		m_bX1 = m_bX2;
		m_bX2 = bTemp;
		bTemp = m_bY1;
		m_bY1 = m_bY2;
		m_bY2 = bTemp;

		// 更新
		UpdateData(FALSE);
	}

	// 重绘
	InvalidateRect(m_MouseRect, TRUE);
}

void CDlgGrayStretch::OnKillfocusEditY1()
{
	// 更新
	UpdateData(TRUE);

	// 重绘
	InvalidateRect(m_MouseRect, TRUE);
}

void CDlgGrayStretch::OnKillfocusEditY2()
{
	// 更新
	UpdateData(TRUE);

	// 重绘
	InvalidateRect(m_MouseRect, TRUE);
}

void CDlgGrayStretch::OnOK()
{
	// 判断是否下限超过上限
	if (m_bX1 > m_bX2)
	{
		// 互换
		BYTE bTemp = m_bX1;
		m_bX1 = m_bX2;
		m_bX2 = bTemp;
		bTemp = m_bY1;
		m_bY1 = m_bY2;
		m_bY2 = bTemp;

		// 更新
		UpdateData(FALSE);
	}

	// 默认处理事件
	CDialog::OnOK();
}

void CDlgGrayStretch::OnLButtonDown(UINT nFlags, CPoint point)
{
	// 当用户单击鼠标左键开始拖动
	if (m_MouseRect.PtInRect(point))
	{
		CRect	rectTemp;

		// 计算点1临近区域
		rectTemp.left = m_MouseRect.left + m_bX1 - 2;
		rectTemp.right = m_MouseRect.left + m_bX1 + 2;
		rectTemp.top = 255 + m_MouseRect.top - m_bY1 - 2;
		rectTemp.bottom = 255 + m_MouseRect.top - m_bY1 + 2;

		// 判断用户是不是想拖动点1
		if (rectTemp.PtInRect(point))
		{

			// 设置拖动状态1，拖动点1
			m_iIsDraging = 1;

			// 更改光标
			::SetCursor(::LoadCursor(NULL, IDC_SIZEALL));
		}
		else
		{
			// 计算点2临近区域
			rectTemp.left = m_MouseRect.left + m_bX2 - 2;
			rectTemp.right = m_MouseRect.left + m_bX2 + 2;
			rectTemp.top = 255 + m_MouseRect.top - m_bY2 - 2;
			rectTemp.bottom = 255 + m_MouseRect.top - m_bY2 + 2;

			// 判断用户是不是想拖动点2
			if (rectTemp.PtInRect(point))
			{

				// 设置拖动状态为2，拖动点2
				m_iIsDraging = 2;

				// 更改光标
				::SetCursor(::LoadCursor(NULL, IDC_SIZEALL));
			}
		}
	}

	// 默认单击鼠标左键处理事件
	CDialog::OnLButtonDown(nFlags, point);
}

void CDlgGrayStretch::OnMouseMove(UINT nFlags, CPoint point)
{
	// 判断当前光标是否在绘制区域
	if (m_MouseRect.PtInRect(point))
	{
		// 判断是否正在拖动
		if (m_iIsDraging != 0)
		{
			// 判断正在拖动点1还是点2
			if (m_iIsDraging == 1)
			{
				// 判断是否下限<上限
				if (point.x - m_MouseRect.left < m_bX2)
				{
					// 更改下限
					m_bX1 = (BYTE)(point.x - m_MouseRect.left);
				}
				else
				{
					// 下限拖过上限，设置为上限-1
					m_bX1 = m_bX2 - 1;

					// 重设鼠标位置
					point.x = m_MouseRect.left + m_bX2 - 1;
				}

				// 更改Y坐标
				m_bY1 = (BYTE)(255 + m_MouseRect.top - point.y);
			}
			else
			{
				// 正在拖动点2

				// 判断是否上限>下限
				if (point.x - m_MouseRect.left > m_bX1)
				{
					// 更改下限
					m_bX2 = (BYTE)(point.x - m_MouseRect.left);
				}
				else
				{
					// 下限拖过上限，设置为下限＋1
					m_bX2 = m_bX1 + 1;

					// 重设鼠标位置
					point.x = m_MouseRect.left + m_bX1 + 1;
				}

				// 更改Y坐标
				m_bY2 = (BYTE)(255 + m_MouseRect.top - point.y);
			}

			// 更改光标
			::SetCursor(::LoadCursor(NULL, IDC_SIZEALL));

			// 更新
			UpdateData(FALSE);

			// 重绘
			InvalidateRect(m_MouseRect, TRUE);
		}
		else
		{
			CRect	rectTemp1;
			CRect	rectTemp2;

			// 计算点1临近区域
			rectTemp1.left = m_MouseRect.left + m_bX1 - 2;
			rectTemp1.right = m_MouseRect.left + m_bX1 + 2;
			rectTemp1.top = 255 + m_MouseRect.top - m_bY1 - 2;
			rectTemp1.bottom = 255 + m_MouseRect.top - m_bY1 + 2;

			// 计算点2临近区域
			rectTemp2.left = m_MouseRect.left + m_bX2 - 2;
			rectTemp2.right = m_MouseRect.left + m_bX2 + 2;
			rectTemp2.top = 255 + m_MouseRect.top - m_bY2 - 2;
			rectTemp2.bottom = 255 + m_MouseRect.top - m_bY2 + 2;

			// 判断用户在点1或点2旁边
			if ((rectTemp1.PtInRect(point)) || (rectTemp2.PtInRect(point)))
			{
				// 更改光标
				::SetCursor(::LoadCursor(NULL, IDC_SIZEALL));
			}
		}
	}

	// 默认鼠标移动处理事件
	CDialog::OnMouseMove(nFlags, point);
}

void CDlgGrayStretch::OnLButtonUp(UINT nFlags, CPoint point)
{
	// 当用户释放鼠标左键停止拖动
	if (m_iIsDraging != 0)
	{
		// 重置拖动状态
		m_iIsDraging = 0;
	}

	// 默认释放鼠标左键处理事件
	CDialog::OnLButtonUp(nFlags, point);
}

void CDlgGrayStretch::OnPaint()
{
	// 字符串
	CString str;

	// 设备上下文
	CPaintDC dc(this);

	// 获取绘制坐标的文本框
	CWnd* pWnd = GetDlgItem(IDC_COOR);

	// 指针
	CDC* pDC = pWnd->GetDC();
	pWnd->Invalidate();
	pWnd->UpdateWindow();

	pDC->Rectangle(0, 0, 330, 300);

	// 创建画笔对象
	CPen* pPenRed = new CPen;

	// 红色画笔
	pPenRed->CreatePen(PS_SOLID, 2, RGB(255, 0, 0));

	// 创建画笔对象
	CPen* pPenBlue = new CPen;

	// 蓝色画笔
	pPenBlue->CreatePen(PS_SOLID, 1, RGB(0, 0, 255));

	// 选中当前红色画笔，并保存以前的画笔
	CGdiObject* pOldPen = pDC->SelectObject(pPenRed);

	// 绘制坐标轴
	pDC->MoveTo(10, 10);

	// 垂直轴
	pDC->LineTo(10, 280);

	// 水平轴
	pDC->LineTo(320, 280);

	// 写坐标
	str.Format(L"0");
	pDC->TextOut(10, 281, str);

	str.Format(L"255");
	pDC->TextOut(265, 281, str);
	pDC->TextOut(11, 25, str);

	// 绘制X轴箭头
	pDC->LineTo(315, 275);
	pDC->MoveTo(320, 280);
	pDC->LineTo(315, 285);

	// 绘制X轴箭头
	pDC->MoveTo(10, 10);
	pDC->LineTo(5, 15);
	pDC->MoveTo(10, 10);
	pDC->LineTo(15, 15);

	// 更改成蓝色画笔
	pDC->SelectObject(pPenBlue);

	// 绘制坐标值
	str.Format(L"(%d, %d)", m_bX1, m_bY1);
	pDC->TextOut(m_bX1 + 10, 281 - m_bY1, str);
	str.Format(L"(%d, %d)", m_bX2, m_bY2);
	pDC->TextOut(m_bX2 + 10, 281 - m_bY2, str);

	// 绘制用户指定的变换直线
	pDC->MoveTo(10, 280);
	pDC->LineTo(m_bX1 + 10, 280 - m_bY1);
	pDC->LineTo(m_bX2 + 10, 280 - m_bY2);
	pDC->LineTo(265, 25);

	// 绘制点边缘的小矩形
	CBrush  brush;
	brush.CreateSolidBrush(RGB(0, 255, 0));

	// 选中刷子
	CGdiObject* pOldBrush = pDC->SelectObject(&brush);

	// 绘制小矩形
	pDC->Rectangle(m_bX1 + 10 - 2, 280 - m_bY1 - 2, m_bX1 + 12, 280 - m_bY1 + 2);
	pDC->Rectangle(m_bX2 + 10 - 2, 280 - m_bY2 - 2, m_bX2 + 12, 280 - m_bY2 + 2);

	// 恢复以前的画笔
	pDC->SelectObject(pOldPen);

	// 绘制边缘
	pDC->MoveTo(10, 25);
	pDC->LineTo(265, 25);
	pDC->LineTo(265, 280);

	// 删除新的画笔
	delete pPenRed;
	delete pPenBlue;

}

BOOL GrayStretch2(LPSTR lpDIBBits, LONG lWidth, LONG lHeight, BYTE bX1, BYTE bY1, BYTE bX2, BYTE bY2)
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

void CDlgGrayStretch::OnBnClickedpreview2()
{
	// TODO: 在此添加控件通知处理程序代码
	CMainFrame* pMainFrame = (CMainFrame*)AfxGetMainWnd();//调用主框架类，获得句柄
	CMFCApplication1Doc* pDoc = (CMFCApplication1Doc*)pMainFrame->GetActiveDocument();//从主框架类里面获得当前
	long	lSrcLineBytes;		//图象每行的字节数
	long	lSrcWidth;      //图象的宽度和高度
	long	lSrcHeight;
	int     lpSrcBitCount;       //图像的位深
	LPSTR	lpSrcDib;		//指向源图象的指针
	LPSTR	lpSrcStartBits;	//指向源像素的指针
	lpSrcDib = (LPSTR) ::GlobalLock((HGLOBAL)pDoc->GetHObject());// 锁定DIB
	lpSrcStartBits = pDoc->m_dib.GetBits(lpSrcDib);			// 找到DIB图象像素起始位置
	lSrcWidth = pDoc->m_dib.GetWidth(lpSrcDib);					// 获取图象的宽度		
	lSrcHeight = pDoc->m_dib.GetHeight(lpSrcDib);					// 获取图象的高度	
	lpSrcBitCount = pDoc->m_dib.GetBitCount(lpSrcDib);                    //获取图像位深
	lSrcLineBytes = pDoc->m_dib.GetReqByteWidth(lSrcWidth * lpSrcBitCount);
	UpdateData(TRUE);
	GrayStretch2(lpSrcStartBits, lSrcWidth, lSrcHeight, m_bX1, m_bY1, m_bX2, m_bY2);
	pDoc->UpdateAllViews(NULL);
}


void CDlgGrayStretch::OnBnClickedrecover2()
{
	// TODO: 在此添加控件通知处理程序代码
	CMainFrame* pMainFrame = (CMainFrame*)AfxGetMainWnd();//调用主框架类，获得句柄
	CMFCApplication1Doc* pDoc = (CMFCApplication1Doc*)pMainFrame->GetActiveDocument();//从主框架类里面获得当前
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
