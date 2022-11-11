// CDlgFilter.cpp: 实现文件
//

#include "pch.h"
#include "MFCApplication1.h"
#include "CDlgFilter.h"
#include "afxdialogex.h"

#include "MainFrm.h"
#include "MFCApplication1Doc.h"
#define WIDTHBYTES(bits)    (((bits) + 31) / 32 * 4)

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif
// CDlgFilter 对话框

IMPLEMENT_DYNAMIC(CDlgFilter, CDialogEx)

CDlgFilter::CDlgFilter(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_Filter, pParent)
{
	m_OperatorType = 0;
	m_EdgeDirectionType = 0;
	m_Coefficient = 0;
	m_Constant = 0;
}

CDlgFilter::~CDlgFilter()
{
}

void CDlgFilter::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Radio(pDX, IDC_RADIO1, m_OperatorType);
	//DDX_Radio(pDX, IDC_RAD6, m_EdgeOperatorType);
	DDX_Radio(pDX, IDC_RADIO10, m_EdgeDirectionType);
	DDX_Text(pDX, IDC_Coefficient, m_Coefficient);
	DDX_Text(pDX, IDC_Constant, m_Constant);
	DDX_Text(pDX, IDC_EDIT1, m_Array[0]);
	DDX_Text(pDX, IDC_EDIT2, m_Array[1]);
	DDX_Text(pDX, IDC_EDIT3, m_Array[2]);
	DDX_Text(pDX, IDC_EDIT4, m_Array[3]);
	DDX_Text(pDX, IDC_EDIT5, m_Array[4]);
	DDX_Text(pDX, IDC_EDIT6, m_Array[5]);
	DDX_Text(pDX, IDC_EDIT7, m_Array[6]);
	DDX_Text(pDX, IDC_EDIT8, m_Array[7]);
	DDX_Text(pDX, IDC_EDIT9, m_Array[8]);
}


BEGIN_MESSAGE_MAP(CDlgFilter, CDialogEx)
	ON_BN_CLICKED(IDC_RADIO1, OnRad1)
	ON_BN_CLICKED(IDC_RADIO2, OnRad2)
	ON_BN_CLICKED(IDC_RADIO3, OnRad3)
	ON_BN_CLICKED(IDC_RADIO4, OnRad4)
	ON_BN_CLICKED(IDC_RADIO5, OnRad5)
	ON_BN_CLICKED(IDC_RADIO6, OnRad6)
	ON_BN_CLICKED(IDC_RADIO7, OnRad7)
	ON_BN_CLICKED(IDC_RADIO8, OnRad8)
	ON_BN_CLICKED(IDC_RADIO9, OnRad9)
	ON_BN_CLICKED(IDC_RADIO10, OnRad10)
	ON_BN_CLICKED(IDC_RADIO11, OnRad11)
	ON_BN_CLICKED(IDC_SaveOperator, &CDlgFilter::OnBnClickedSaveoperator)
	ON_BN_CLICKED(IDC_ApplyOperator, &CDlgFilter::OnBnClickedApplyoperator)
	ON_BN_CLICKED(IDC_Preview, &CDlgFilter::OnBnClickedPreview)
	ON_BN_CLICKED(IDC_Recover, &CDlgFilter::OnBnClickedRecover)
END_MESSAGE_MAP()


// CDlgFilter 消息处理程序
void CDlgFilter::OnRad1() {
	m_OperatorType = 0;
	m_Array[0] = 0;
	m_Array[1] = 0;
	m_Array[2] = 0;
	m_Array[3] = 0;
	m_Array[4] = 1;
	m_Array[5] = 0;
	m_Array[6] = 0;
	m_Array[7] = 0;
	m_Array[8] = 0;
	m_Coefficient = -1;
	m_Constant = 255;
	UpdateEdit();
	UpdateData(FALSE);
}
void CDlgFilter::OnRad2() {
	m_OperatorType = 1;
	m_Array[0] = 1.0;
	m_Array[1] = 1.0;
	m_Array[2] = 1.0;
	m_Array[3] = 1.0;
	m_Array[4] = 1.0;
	m_Array[5] = 1.0;
	m_Array[6] = 1.0;
	m_Array[7] = 1.0;
	m_Array[8] = 1.0;
	m_Coefficient = (FLOAT)(1.0 / 9.0);
	m_Constant = 0;
	UpdateEdit();
	UpdateData(FALSE);
}
void CDlgFilter::OnRad3() {
	m_OperatorType = 2;
	m_Array[0] = 1.0;
	m_Array[1] = 2.0;
	m_Array[2] = 1.0;
	m_Array[3] = 2.0;
	m_Array[4] = 4.0;
	m_Array[5] = 2.0;
	m_Array[6] = 1.0;
	m_Array[7] = 2.0;
	m_Array[8] = 1.0;
	m_Coefficient = (FLOAT)(1.0 / 16.0);
	m_Constant = 0;
	UpdateEdit();
	UpdateData(FALSE);
}
void CDlgFilter::OnRad4() {
	m_OperatorType = 3;
	m_Array[0] = -1.0;
	m_Array[1] = -1.0;
	m_Array[2] = -1.0;
	m_Array[3] = -1.0;
	m_Array[4] = 9.0;
	m_Array[5] = -1.0;
	m_Array[6] = -1.0;
	m_Array[7] = -1.0;
	m_Array[8] = -1.0;
	m_Coefficient = 1.0;
	m_Constant = 0;
	UpdateEdit();
	UpdateData(FALSE);
}
void CDlgFilter::OnRad5() {
	m_OperatorType = 4;
	m_Array[0] = -1.0;
	m_Array[1] = -1.0;
	m_Array[2] = 0;
	m_Array[3] = -1.0;
	m_Array[4] = 0;
	m_Array[5] = 1;
	m_Array[6] = 0;
	m_Array[7] = 1;
	m_Array[8] = 1;
	m_Coefficient = 1.0;
	m_Constant = 100;
	UpdateEdit();
	UpdateData(FALSE);
}
void CDlgFilter::OnRad6() {
	m_OperatorType = 5;
	m_Array[0] = 0;
	m_Array[1] = 0;
	m_Array[2] = 0;
	m_Array[3] = 0;
	m_Array[4] = 1;
	m_Array[5] = 0;
	m_Array[6] = 0;
	m_Array[7] = 0;
	m_Array[8] = 0;
	m_Coefficient = 1.0;
	m_Constant = 0;
	UpdateEdit();
	UpdateData(FALSE);
}
void CDlgFilter::OnRad7() {
	m_OperatorType = 6;
	UpdateEdit();
	UpdateData(FALSE);
}
void CDlgFilter::OnRad8() {
	m_OperatorType = 7;
	UpdateEdit();
	UpdateData(FALSE);
}
void CDlgFilter::OnRad9() {
	m_OperatorType = 8;
	UpdateEdit();
	UpdateData(FALSE);
}
void CDlgFilter::OnRad10() {	
	m_EdgeDirectionType = 0;
	if (m_OperatorType == 7) {
		m_Array[0] = -1;
		m_Array[1] = 0;
		m_Array[2] = 1;
		m_Array[3] = -2;
		m_Array[4] = 0;
		m_Array[5] = 2;
		m_Array[6] = -1;
		m_Array[7] = 0;
		m_Array[8] = 1;
	}
	else if (m_OperatorType == 8) {
		m_Array[0] = -1;
		m_Array[1] = 0;
		m_Array[2] = 1;
		m_Array[3] = -1;
		m_Array[4] = 0;
		m_Array[5] = 1;
		m_Array[6] = -1;
		m_Array[7] = 0;
		m_Array[8] = 1;
	}
	UpdateEdit();
	UpdateData(FALSE);
}
void CDlgFilter::OnRad11() {
	m_EdgeDirectionType = 1;
	if (m_OperatorType == 7) {
		m_Array[0] = -1;
		m_Array[1] = -2;
		m_Array[2] = -1;
		m_Array[3] = 0;
		m_Array[4] = 0;
		m_Array[5] = 0;
		m_Array[6] = 1;
		m_Array[7] = 2;
		m_Array[8] = 1;
	}
	else if (m_OperatorType == 8) {
		m_Array[0] = -1;
		m_Array[1] = -1;
		m_Array[2] = -1;
		m_Array[3] = 0;
		m_Array[4] = 0;
		m_Array[5] = 0;
		m_Array[6] = 1;
		m_Array[7] = 1;
		m_Array[8] = 1;
	}
	UpdateEdit();
	UpdateData(FALSE);
}

void CDlgFilter::UpdateEdit()
{
	BOOL	bEnable;

	// 循环变量
	int		i;
	int		j;

	if (m_OperatorType == 0||m_OperatorType == 1|| m_OperatorType == 2||m_OperatorType == 3 || m_OperatorType == 4 || m_OperatorType == 5 || m_OperatorType == 7 || m_OperatorType == 8)
	{
		bEnable = FALSE;
	}
	else
	{
		bEnable = TRUE;
	}

	for (i = IDC_EDIT1; i <= IDC_EDIT9; i++)
	{
		// 设置文本框不可编辑
		(CEdit*)GetDlgItem(i)->EnableWindow(bEnable);
	}

	(CEdit*)GetDlgItem(IDC_Coefficient)->EnableWindow(bEnable);
	if (m_OperatorType == 5) {
		bEnable = TRUE;
	}
	(CEdit*)GetDlgItem(IDC_Constant)->EnableWindow(bEnable);
	UpdateData(FALSE);
}
void CDlgFilter::OnBnClickedSaveoperator()
{
	TCHAR szFilter[] = _T("文本文件(*.txt)|*.txt|| ");    //在下面实例fileDlg中作为参数使用
	// 构造保存文件对话框
	CFileDialog fileDlg(FALSE, _T("txt"), _T("operator"), OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, szFilter, this);
	/*TRUE为打开文件对话框，FALSE为保存，此处是保存
	 _T("txt")，默认文件格式，也可以是_T("doc")或者是_T("xls")
	  _T("my"),默认文件名为“my.txt”
	 OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT，打开文件的方式隐藏文件对话框上的“Read Only”复选框
	 以及弹出覆盖文件对话框，可以固定
	 szFilter，文件过滤器
	 this，文件对话框的父窗口的指针，可以固定*/
	if (IDOK == fileDlg.DoModal())    // 调用DoModal()显示保存文件对话框，如果确认按下执行以下
	{
		CStdioFile  MyFile; //打开文件，上面是打开保存文件对话框，不同
		MyFile.Open(fileDlg.GetPathName(), CFile::modeWrite | CFile::modeRead | CFile::modeCreate);
		/*fileDlg.GetPathName(),获取文件路径；后面的是打开方式*/
		CString string1;
		MyFile.Seek(0, CFile::end);
		string1.Format(_T("%f"), m_Array[0]);
		MyFile.Seek(0, CFile::end); //找到文件结尾
		MyFile.Write(string1,string1.GetLength()); //列表中读取数据，调用WriteString方法写入文件
		MyFile.WriteString(L"\n");
		string1.Format(_T("%f"), m_Array[1]);
		MyFile.Seek(0, CFile::end); //找到文件结尾
		MyFile.Write(string1, string1.GetLength()); //列表中读取数据，调用WriteString方法写入文件
		MyFile.WriteString(L"\n");
		string1.Format(_T("%f"), m_Array[2]);
		MyFile.Seek(0, CFile::end); //找到文件结尾
		MyFile.Write(string1, string1.GetLength()); //列表中读取数据，调用WriteString方法写入文件
		MyFile.WriteString(L"\n");
		string1.Format(_T("%f"), m_Array[3]);
		MyFile.Seek(0, CFile::end); //找到文件结尾
		MyFile.Write(string1, string1.GetLength()); //列表中读取数据，调用WriteString方法写入文件
		MyFile.WriteString(L"\n");
		string1.Format(_T("%f"), m_Array[4]);
		MyFile.Seek(0, CFile::end); //找到文件结尾
		MyFile.Write(string1, string1.GetLength()); //列表中读取数据，调用WriteString方法写入文件
		MyFile.WriteString(L"\n");
		string1.Format(_T("%f"), m_Array[5]);
		MyFile.Seek(0, CFile::end); //找到文件结尾
		MyFile.Write(string1, string1.GetLength()); //列表中读取数据，调用WriteString方法写入文件
		MyFile.WriteString(L"\n");
		string1.Format(_T("%f"), m_Array[6]);
		MyFile.Seek(0, CFile::end); //找到文件结尾
		MyFile.Write(string1, string1.GetLength()); //列表中读取数据，调用WriteString方法写入文件
		MyFile.WriteString(L"\n");
		string1.Format(_T("%f"), m_Array[7]);
		MyFile.Seek(0, CFile::end); //找到文件结尾
		MyFile.Write(string1, string1.GetLength()); //列表中读取数据，调用WriteString方法写入文件
		MyFile.WriteString(L"\n");
		string1.Format(_T("%f"), m_Array[8]);
		MyFile.Seek(0, CFile::end); //找到文件结尾
		MyFile.Write(string1, string1.GetLength()); //列表中读取数据，调用WriteString方法写入文件
		MyFile.WriteString(L"\n");
		string1.Format(_T("%.4f"), m_Coefficient);
		MyFile.Seek(0, CFile::end); //找到文件结尾
		MyFile.Write(string1, 15); //列表中读取数据，调用WriteString方法写入文件
		MyFile.WriteString(L"\n");
		string1.Format(_T("%f"), m_Constant);
		MyFile.Seek(0, CFile::end); //找到文件结尾
		MyFile.Write(string1, string1.GetLength()); //列表中读取数据，调用WriteString方法写入文件
		MyFile.WriteString(L"\n");
		MyFile.Close();
	}
}
void CDlgFilter::OnBnClickedApplyoperator()
{
	// TODO: 在此添加控件通知处理程序代码
	TCHAR szFilter[] = _T("文本文件(*.txt)|*.txt|| ");    //在下面实例fileDlg中作为参数使用
	// 构造保存文件对话框
	CFileDialog fileDlg(TRUE, _T("txt"), _T("operator"));
	if ( fileDlg.DoModal() == IDOK ) {
		CStdioFile MyFile;
		CFileException fe;
		CString strPathName;
		strPathName = fileDlg.GetPathName();
		// 打开文件
		VERIFY(MyFile.Open(strPathName, CFile::modeRead | CFile::shareDenyWrite, &fe));
		MyFile.SeekToBegin();
		CString v0, v1, v2, v3, v4, v5, v6, v7, v8;
		CString Coefficient, Constant;
		MyFile.ReadString(v0);
		MyFile.ReadString(v1);
		MyFile.ReadString(v2);
		MyFile.ReadString(v3);
		MyFile.ReadString(v4);
		MyFile.ReadString(v5);
		MyFile.ReadString(v6);
		MyFile.ReadString(v7);
		MyFile.ReadString(v8);
		MyFile.ReadString(Coefficient);
		MyFile.ReadString(Constant);
		SetDlgItemText(IDC_EDIT1, v0);
		SetDlgItemText(IDC_EDIT2, v1);
		SetDlgItemText(IDC_EDIT3, v2);
		SetDlgItemText(IDC_EDIT4, v3);
		SetDlgItemText(IDC_EDIT5, v4);
		SetDlgItemText(IDC_EDIT6, v5);
		SetDlgItemText(IDC_EDIT7, v6);
		SetDlgItemText(IDC_EDIT8, v7);
		SetDlgItemText(IDC_EDIT9, v8);
		CString str1,str2;
		str1.Format(_T("%.4f"), 0.1);
		SetDlgItemText(IDC_Coefficient, str1);
		str2.Format(_T("%.4f"), Constant);
		SetDlgItemText(IDC_Constant, str2);
		MyFile.Close();
	}
}

BOOL Template1(LPSTR lpDIBBits, LONG lWidth, LONG lHeight,
	int iTempH, int iTempW,
	int iTempMX, int iTempMY,
	FLOAT* fpArray, FLOAT fCoef, FLOAT Cons)
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
					fResult += (*lpSrc) * fpArray[k * iTempW + l] ;
				}
			}

			// 乘上系数
			/*fResult = fResult * fCoef + Cons;*/
			if(Cons != 0)
				fResult = fCoef * (*lpDst) + Cons;
			else
				fResult = fResult * fCoef + Cons;

			// 取绝对值
			fResult = (FLOAT)fabs(fResult);

			// 判断是否超过255
			if (fResult > 255)
			{
				// 直接赋值为255
				*lpDst = 255;
			}
			else if (fResult <= 0) {
				*lpDst = 0;
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

void CDlgFilter::OnBnClickedPreview()
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
	FLOAT	aValue[9];
	if (m_OperatorType == 0) {
		aValue[0] = 0;
		aValue[1] = 0;
		aValue[2] = 0;
		aValue[3] = 0;
		aValue[4] = 1;
		aValue[5] = 0;
		aValue[6] = 0;
		aValue[7] = 0;
		aValue[8] = 0;
		Template1(lpSrcStartBits, lSrcWidth, lSrcHeight, 3, 3, 1, 1, aValue, -1.0, 255);
	}
	else if (m_OperatorType == 1) {
		aValue[0] = 1.0;
		aValue[1] = 1.0;
		aValue[2] = 1.0;
		aValue[3] = 1.0;
		aValue[4] = 1.0;
		aValue[5] = 1.0;
		aValue[6] = 1.0;
		aValue[7] = 1.0;
		aValue[8] = 1.0;
		Template1(lpSrcStartBits, lSrcWidth, lSrcHeight, 3, 3, 1, 1, aValue, (FLOAT)(1.0 / 9.0),0);
	}
	else if (m_OperatorType == 2) {
		aValue[0] = 1.0;
		aValue[1] = 2.0;
		aValue[2] = 1.0;
		aValue[3] = 2.0;
		aValue[4] = 4.0;
		aValue[5] = 2.0;
		aValue[6] = 1.0;
		aValue[7] = 2.0;
		aValue[8] = 1.0;
		Template1(lpSrcStartBits, lSrcWidth, lSrcHeight, 3, 3, 1, 1, aValue, (FLOAT)(1.0 / 16.0),0);
		m_Coefficient = (FLOAT)(1.0 / 16.0);
	}
	else if (m_OperatorType == 3) {
		aValue[0] = -1.0;
		aValue[1] = -1.0;
		aValue[2] = -1.0;
		aValue[3] = -1.0;
		aValue[4] = 9.0;
		aValue[5] = -1.0;
		aValue[6] = -1.0;
		aValue[7] = -1.0;
		aValue[8] = -1.0;
		Template1(lpSrcStartBits, lSrcWidth, lSrcHeight, 3, 3, 1, 1, aValue, 1.0,0);
	}
	else if (m_OperatorType == 4) {
		aValue[0] = -1.0;
		aValue[1] = -1.0;
		aValue[2] = 0;
		aValue[3] = -1.0;
		aValue[4] = 0;
		aValue[5] = 1.0;
		aValue[6] = 0;
		aValue[7] = 1.0;
		aValue[8] = 1.0;
		Template1(lpSrcStartBits, lSrcWidth, lSrcHeight, 3, 3, 1, 1, aValue, 1.0, 0);
		aValue[0] = 0;
		aValue[1] = 0;
		aValue[2] = 0;
		aValue[3] = 0;
		aValue[4] = 1;
		aValue[5] = 0;
		aValue[6] = 0;
		aValue[7] = 0;
		aValue[8] = 0;
		Template1(lpSrcStartBits, lSrcWidth, lSrcHeight, 3, 3, 1, 1, aValue, 1.0, 100);
	}
	else if (m_OperatorType == 5) {
		aValue[0] = 0;
		aValue[1] = 0;
		aValue[2] = 0;
		aValue[3] = 0;
		aValue[4] = 1;
		aValue[5] = 0;
		aValue[6] = 0;
		aValue[7] = 0;
		aValue[8] = 0;
		Template1(lpSrcStartBits, lSrcWidth, lSrcHeight, 3, 3, 1, 1, aValue, 1.0, m_Constant);
	}
	else if (m_OperatorType == 6) {
		aValue[0] = m_Array[0];
		aValue[1] = m_Array[1];
		aValue[2] = m_Array[2];
		aValue[3] = m_Array[3];
		aValue[4] = m_Array[4];
		aValue[5] = m_Array[5];
		aValue[6] = m_Array[6];
		aValue[7] = m_Array[7];
		aValue[8] = m_Array[8];
		float Coefficient = m_Coefficient;
		Template1(lpSrcStartBits, lSrcWidth, lSrcHeight, 3, 3, 1, 1, aValue, Coefficient,0);
	}
	else if (m_OperatorType == 7) {
		if (m_EdgeDirectionType == 0) {
			aValue[0] = -1;
			aValue[1] = 0;
			aValue[2] = 1;
			aValue[3] = -2;
			aValue[4] = 0;
			aValue[5] = 2;
			aValue[6] = -1;
			aValue[7] = 0;
			aValue[8] = 1;
			Template1(lpSrcStartBits, lSrcWidth, lSrcHeight, 3, 3, 1, 1, aValue, 1.0, 0);
			
		}
		else if (m_EdgeDirectionType == 1) {
			aValue[0] = -1;
			aValue[1] = -2;
			aValue[2] = -1;
			aValue[3] = 0;
			aValue[4] = 0;
			aValue[5] = 0;
			aValue[6] = 1;
			aValue[7] = 2;
			aValue[8] = 1;
			Template1(lpSrcStartBits, lSrcWidth, lSrcHeight, 3, 3, 1, 1, aValue, 1.0, 0);
		}
	}
	else if (m_OperatorType == 8) {
		if (m_EdgeDirectionType == 0) {
			aValue[0] = -1;
			aValue[1] = 0;
			aValue[2] = 1;
			aValue[3] = -1;
			aValue[4] = 0;
			aValue[5] = 1;
			aValue[6] = -1;
			aValue[7] = 0;
			aValue[8] = 1;
			Template1(lpSrcStartBits, lSrcWidth, lSrcHeight, 3, 3, 1, 1, aValue, 1.0, 0);
		}
		else if (m_EdgeDirectionType == 1) {
			aValue[0] = -1;
			aValue[1] = -1;
			aValue[2] = -1;
			aValue[3] = 0;
			aValue[4] = 0;
			aValue[5] = 0;
			aValue[6] = 1;
			aValue[7] = 1;
			aValue[8] = 1;
			Template1(lpSrcStartBits, lSrcWidth, lSrcHeight, 3, 3, 1, 1, aValue, 1.0, 0);
		}
	}
	pDoc->UpdateAllViews(NULL);
}

void CDlgFilter::OnBnClickedRecover()
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
