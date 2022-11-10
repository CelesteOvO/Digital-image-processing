// CDlgAreaCount.cpp: 实现文件
//

#include "pch.h"
#include "MFCApplication1.h"
#include "CDlgAreaCount.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#include "MainFrm.h"
#include "MFCApplication1Doc.h"
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>

// CDlgAreaCount 对话框

IMPLEMENT_DYNAMIC(CDlgAreaCount, CDialogEx)

CDlgAreaCount::CDlgAreaCount(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_AreaCount, pParent)
{
	m_ForegroundType = 0;
	m_NumberOfConnected = 0;
	m_NumberOfMorphology = 0;
	m_Morphology = 0;
	m_maxArea = 0;
	m_maxPerimeter = 0;
	m_maxRoundness = 0;
	m_maxLenratio = 0;
	m_count = 0;
}

CDlgAreaCount::~CDlgAreaCount()
{
}

void CDlgAreaCount::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Radio(pDX, IDC_RADIO1, m_ForegroundType);
	DDX_Radio(pDX, IDC_RADIO4, m_NumberOfConnected);
	DDX_Text(pDX, IDC_Area, m_maxArea);
	DDX_Text(pDX, IDC_Perimeter, m_maxPerimeter);
	DDX_Text(pDX, IDC_Roundness, m_maxRoundness);
	DDX_Text(pDX, IDC_Lenratio, m_maxLenratio);
	DDX_Text(pDX, IDC_Count, m_count);
}


BEGIN_MESSAGE_MAP(CDlgAreaCount, CDialogEx)
	ON_BN_CLICKED(IDC_RADIO1, OnRad1)
	ON_BN_CLICKED(IDC_RADIO2, OnRad2)
	ON_BN_CLICKED(IDC_RADIO3, OnRad3)
	ON_BN_CLICKED(IDC_RADIO4, OnRad4)
	ON_BN_CLICKED(IDC_RADIO5, OnRad5)
	ON_BN_CLICKED(IDC_Final, &CDlgAreaCount::OnBnClickedFinal)
END_MESSAGE_MAP()


// CDlgAreaCount 消息处理程序
void CDlgAreaCount::OnRad1() {
	m_ForegroundType = 0;
}
void CDlgAreaCount::OnRad2() {
	m_ForegroundType = 1;
}
void CDlgAreaCount::OnRad3() {
	m_ForegroundType = 2;
}
void CDlgAreaCount::OnRad4() {
	m_NumberOfConnected = 0;
}
void CDlgAreaCount::OnRad5() {
	m_NumberOfConnected = 1;
}
void CDlgAreaCount::OnRad6() {
	m_Morphology = 0;
}
void CDlgAreaCount::OnRad7() {
	m_Morphology = 1;
}
void CDlgAreaCount::OnRad8() {
	m_Morphology = 2;
}
void CDlgAreaCount::OnRad9() {
	m_Morphology = 3;
}

int PixelCounter1(cv::Mat src, int nflag)
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
void CDlgAreaCount::OnBnClickedFinal()
{
	// TODO: 在此添加控件通知处理程序代码
	CMainFrame* pMainFrame = (CMainFrame*)AfxGetMainWnd();//调用主框架类，获得句柄
	CMFCApplication1Doc* pDoc = (CMFCApplication1Doc*)pMainFrame->GetActiveDocument();//从主框架类里面获得当前
	USES_CONVERSION;
	cv::String cvStr = W2A(pDoc->GetPathName());
	cv::Mat img = cv::imread(cvStr, cv::IMREAD_COLOR);
	cv::Mat imgSmooth, imgGray,imgCanny, imgThre, imgdst, imgDil;
	cvtColor(img, imgGray, cv::COLOR_BGR2GRAY);
	GaussianBlur(imgGray, imgSmooth, cv::Size(5, 5), 0, 0);
	threshold(imgSmooth, imgThre, 0, 255, cv::THRESH_OTSU);
	Canny(imgThre, imgCanny, 25, 50);
	int nWhiteCount = PixelCounter1(imgThre, 1);
	int nBlackCount = PixelCounter1(imgThre, 2);
	cv::Mat imgMor;
	cv::Mat element;
	if (m_NumberOfConnected == 0) {
		element = cv::getStructuringElement(cv::MORPH_RECT, cv::Size(4, 4));
	}
	else if (m_NumberOfConnected == 1) {
		element = cv::getStructuringElement(cv::MORPH_RECT, cv::Size(8, 8));
	}
	dilate(imgCanny, imgDil, element);
	morphologyEx(imgDil, imgMor, cv::MORPH_OPEN, element);
	cv::Mat imgNext;
	imgMor = imgDil;
	imgNext = imgMor;
	if (m_ForegroundType == 0) {
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
	else if (m_ForegroundType == 1) {
		imgdst = imgMor;
	}
	else if (m_ForegroundType == 2) {
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
	std::vector<std::vector<cv::Point>> contours;
	std::vector<cv::Vec4i> hierarchy;
	findContours(imgNext, contours, hierarchy, cv::RETR_EXTERNAL, cv::CHAIN_APPROX_SIMPLE);
	//cv::imshow("Image", imgMor);  
	//drawContours(imgMor, contours, -1, cv::Scalar(255, 0, 255), 2);
	std::vector<std::vector<cv::Point>> conPoly(contours.size());
	std::vector<cv::Rect> boundRect(contours.size());
	double maxArea = 0;
	double maxPerimeter = 0;
	double maxRoundness = 0;
	double maxLenratio = 0;
	int count = 0;
	for (int i = 0; i < contours.size(); i++)
	{
		double area = contourArea(contours[i]);
		if (area < 10)
			continue;
		count++;
		if (maxArea < area) {
			maxArea = area;
		}
		double perimeter = arcLength(contours[i], true);
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
	m_maxArea = maxArea;
	m_maxPerimeter = maxPerimeter;
	m_maxRoundness = maxRoundness;
	m_maxLenratio = maxLenratio;
	m_count = count;
	CString str1,str2,str3,str4;
	str1.Format(_T("%f"), maxArea);
	str2.Format(_T("%f"), maxPerimeter);
	str3.Format(_T("%f"), maxRoundness);
	str4.Format(_T("%f"), maxLenratio);
	SetDlgItemText(IDC_Area, str1);
	SetDlgItemText(IDC_Perimeter, str2);
	SetDlgItemText(IDC_Roundness, str3);
	SetDlgItemText(IDC_Lenratio, str4);
	SetDlgItemInt(IDC_Count, m_count);
	pDoc->SetModifiedFlag(true);
	pDoc->UpdateAllViews(NULL);
	::GlobalUnlock((HGLOBAL)pDoc->GetHObject());// 解除锁定
}

