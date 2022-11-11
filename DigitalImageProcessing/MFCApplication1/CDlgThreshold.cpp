// CDlgThreshold.cpp: 实现文件
//

#include "pch.h"
#include "MFCApplication1.h"
#include "CDlgThreshold.h"
#include "afxdialogex.h"

#include "MainFrm.h"
#include "MFCApplication1Doc.h"
#include <iostream>
#define WIDTHBYTES(bits)    (((bits) + 31) / 32 * 4)

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

// CDlgThreshold 对话框

IMPLEMENT_DYNAMIC(CDlgThreshold, CDialogEx)

CDlgThreshold::CDlgThreshold(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_Threshold, pParent)
	, m_Type(0)
{
	m_bThre = 0;
	m_Type = 0;
}

CDlgThreshold::~CDlgThreshold()
{
}

void CDlgThreshold::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_Thre, m_bThre);
	DDV_MinMaxByte(pDX, m_bThre, 0, 255);
	DDX_Radio(pDX, IDC_RADIO1, m_Type);
}


BEGIN_MESSAGE_MAP(CDlgThreshold, CDialogEx)
	ON_BN_CLICKED(IDC_RADIO1, OnRad1)
	ON_BN_CLICKED(IDC_RADIO2, OnRad2)
	ON_BN_CLICKED(IDC_RADIO3, OnRad3)
	ON_BN_CLICKED(IDC_RADIO4, OnRad4)
	ON_BN_CLICKED(IDC_RADIO5, OnRad5)
	ON_EN_KILLFOCUS(IDC_EDIT_Thre, OnKillfocusEDITThre)
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_MOUSEMOVE()
	ON_WM_PAINT()
	ON_BN_CLICKED(IDC_Preview3, &CDlgThreshold::OnBnClickedPreview3)
	ON_BN_CLICKED(IDC_recover3, &CDlgThreshold::OnBnClickedrecover3)
	ON_BN_CLICKED(IDC_CountThreshold, &CDlgThreshold::OnBnClickedCountthreshold)
END_MESSAGE_MAP()


// CDlgThreshold 消息处理程序
BOOL CDlgThreshold::OnInitDialog()
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
	m_bIsDraging = FALSE;

	// 返回TRUE
	return TRUE;
}

void CDlgThreshold::OnRad1() 
{
	m_Type = 0;
	UpdateData(FALSE);
}

void CDlgThreshold::OnRad2()
{
	m_Type = 1;
	UpdateData(FALSE);
}

void CDlgThreshold::OnRad3()
{
	m_Type = 2;
	UpdateData(FALSE);
}

void CDlgThreshold::OnRad4()
{
	m_Type = 3;
	UpdateData(FALSE);
}

void CDlgThreshold::OnRad5()
{
	m_Type = 4;
	UpdateData(FALSE);
}

void CDlgThreshold::OnKillfocusEDITThre()
{
	// 更新
	UpdateData(TRUE);

	// 重绘
	InvalidateRect(m_MouseRect, TRUE);
}

void CDlgThreshold::OnLButtonDown(UINT nFlags, CPoint point)
{
	// 当用户单击鼠标左键开始拖动

	// 判断是否在有效区域中
	if (m_MouseRect.PtInRect(point))
	{
		if (point.x == (m_MouseRect.left + m_bThre))
		{

			// 设置拖动状态
			m_bIsDraging = TRUE;

			// 更改光标
			::SetCursor(::LoadCursor(NULL, IDC_SIZEWE));
		}
	}

	// 默认单击鼠标左键处理事件
	CDialog::OnLButtonDown(nFlags, point);
}

void CDlgThreshold::OnLButtonUp(UINT nFlags, CPoint point)
{
	// 当用户释放鼠标左键停止拖动
	if (m_bIsDraging)
	{
		// 重置拖动状态
		m_bIsDraging = FALSE;
	}

	// 默认释放鼠标左键处理事件
	CDialog::OnLButtonUp(nFlags, point);
}

void CDlgThreshold::OnMouseMove(UINT nFlags, CPoint point)
{
	// 判断当前光标是否在绘制区域
	if (m_MouseRect.PtInRect(point))
	{
		// 判断是否正在拖动
		if (m_bIsDraging)
		{
			// 更改阈值
			m_bThre = (BYTE)(point.x - m_MouseRect.left);

			// 更改光标
			::SetCursor(::LoadCursor(NULL, IDC_SIZEWE));

			// 更新
			UpdateData(FALSE);

			// 重绘
			InvalidateRect(m_MouseRect, TRUE);
		}
		else if (point.x == (m_MouseRect.left + m_bThre))
		{
			// 更改光标
			::SetCursor(::LoadCursor(NULL, IDC_SIZEWE));
		}
	}

	// 默认鼠标移动处理事件
	CDialog::OnMouseMove(nFlags, point);
}

void CDlgThreshold::OnPaint()
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
	pPenBlue->CreatePen(PS_SOLID, 2, RGB(0, 0, 255));

	// 创建画笔对象
	CPen* pPenGreen = new CPen;

	// 绿色画笔
	pPenGreen->CreatePen(PS_DOT, 1, RGB(0, 255, 0));

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

	// 更改成绿色画笔
	pDC->SelectObject(pPenGreen);

	// 绘制窗口阈值线
	pDC->MoveTo(m_bThre + 10, 25);
	pDC->LineTo(m_bThre + 10, 280);

	// 更改成蓝色画笔
	pDC->SelectObject(pPenBlue);

	// 绘制坐标值
	str.Format(L"%d", m_bThre);
	pDC->TextOut(m_bThre + 10, 281, str);

	// 绘制用户指定的窗口（注意转换坐标系）
	pDC->MoveTo(10, 280);
	pDC->LineTo(m_bThre + 10, 280);
	pDC->LineTo(m_bThre + 10, 25);
	pDC->LineTo(265, 25);

	// 恢复以前的画笔
	pDC->SelectObject(pOldPen);

	// 绘制边缘
	pDC->MoveTo(10, 25);
	pDC->LineTo(265, 25);
	pDC->LineTo(265, 280);

	// 删除新的画笔
	delete pPenRed;
	delete pPenBlue;
	delete pPenGreen;
}

//迭代法
int ThresholdDIB1(LPSTR lpDIBBits, LONG lWidth, LONG lHeight)
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
int OTSU1(LPSTR lpDIBBits, LONG lWidth, LONG lHeight)
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
int MaximumEntropy1(LPSTR lpDIBBits, LONG lWidth, LONG lHeight) {
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
int Adaptive1(LPSTR lpDIBBits, LONG lWidth, LONG lHeight) {
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

BOOL WINAPI ThresholdTrans1(LPSTR lpDIBBits, LONG lWidth, LONG lHeight, BYTE bThre)
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


void CDlgThreshold::OnBnClickedPreview3()
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
	if (m_Type == 0) {
		ThresholdDIB1(lpSrcStartBits, lSrcWidth, lSrcHeight);
	}
	else if (m_Type == 1) {
		OTSU1(lpSrcStartBits, lSrcWidth, lSrcHeight);
	}
	else if (m_Type == 2) {
		MaximumEntropy1(lpSrcStartBits, lSrcWidth, lSrcHeight);
	}
	else if (m_Type == 3) {
		Adaptive1(lpSrcStartBits, lSrcWidth, lSrcHeight);
	}
	else if (m_Type == 4) {
		ThresholdTrans1(lpSrcStartBits, lSrcWidth, lSrcHeight, m_bThre);
	}
	pDoc->UpdateAllViews(NULL);
}
void CDlgThreshold::OnBnClickedrecover3()
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
void CDlgThreshold::OnBnClickedCountthreshold()
{
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
	// TODO: 在此添加控件通知处理程序代码
	if (m_Type == 0) {
		m_bThre = ThresholdDIB1(lpSrcStartBits, lSrcWidth, lSrcHeight);
		SetDlgItemInt(IDC_EDIT_Thre, m_bThre);
		OnBnClickedrecover3();
	}
	else if (m_Type == 1) {
		m_bThre = OTSU1(lpSrcStartBits, lSrcWidth, lSrcHeight);
		SetDlgItemInt(IDC_EDIT_Thre, m_bThre);
		OnBnClickedrecover3();
	}
	else if (m_Type == 2) {
		m_bThre = MaximumEntropy1(lpSrcStartBits, lSrcWidth, lSrcHeight);
		SetDlgItemInt(IDC_EDIT_Thre, m_bThre);
		OnBnClickedrecover3();
	}
	else if (m_Type == 3) {
		m_bThre = Adaptive1(lpSrcStartBits, lSrcWidth, lSrcHeight);
		SetDlgItemInt(IDC_EDIT_Thre, m_bThre);
		OnBnClickedrecover3();
	}
}
