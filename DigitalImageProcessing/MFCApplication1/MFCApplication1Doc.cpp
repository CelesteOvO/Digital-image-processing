
// MFCApplication1Doc.cpp: CMFCApplication1Doc 类的实现
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS 可以在实现预览、缩略图和搜索筛选器句柄的
// ATL 项目中进行定义，并允许与该项目共享文档代码。
#ifndef SHARED_HANDLERS
#include "MFCApplication1.h"
#endif

#include "MFCApplication1Doc.h"

#include <propkey.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CMFCApplication1Doc

IMPLEMENT_DYNCREATE(CMFCApplication1Doc, CDocument)

BEGIN_MESSAGE_MAP(CMFCApplication1Doc, CDocument)
END_MESSAGE_MAP()


// CMFCApplication1Doc 构造/析构

CMFCApplication1Doc::CMFCApplication1Doc() noexcept
{
	// TODO: 在此添加一次性构造代码
	m_hDIB = NULL;// 初始化变量
	m_palDIB = NULL;
	m_sizeDoc = CSize(1, 1);
}

CMFCApplication1Doc::~CMFCApplication1Doc()
{
	if (m_hDIB != NULL)// 判断是否有DIB对象
	{
		::GlobalFree((HGLOBAL)m_hDIB);
	}


	if (m_palDIB != NULL)// 判断调色板是否存在
	{
		delete m_palDIB;
	}
}

BOOL CMFCApplication1Doc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: 在此添加重新初始化代码
	// (SDI 文档将重用该文档)

	return TRUE;
}




// CMFCApplication1Doc 序列化

void CMFCApplication1Doc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: 在此添加存储代码
	}
	else
	{
		// TODO: 在此添加加载代码
	}
}

#ifdef SHARED_HANDLERS

// 缩略图的支持
void CMFCApplication1Doc::OnDrawThumbnail(CDC& dc, LPRECT lprcBounds)
{
	// 修改此代码以绘制文档数据
	dc.FillSolidRect(lprcBounds, RGB(255, 255, 255));

	CString strText = _T("TODO: implement thumbnail drawing here");
	LOGFONT lf;

	CFont* pDefaultGUIFont = CFont::FromHandle((HFONT) GetStockObject(DEFAULT_GUI_FONT));
	pDefaultGUIFont->GetLogFont(&lf);
	lf.lfHeight = 36;

	CFont fontDraw;
	fontDraw.CreateFontIndirect(&lf);

	CFont* pOldFont = dc.SelectObject(&fontDraw);
	dc.DrawText(strText, lprcBounds, DT_CENTER | DT_WORDBREAK);
	dc.SelectObject(pOldFont);
}

// 搜索处理程序的支持
void CMFCApplication1Doc::InitializeSearchContent()
{
	CString strSearchContent;
	// 从文档数据设置搜索内容。
	// 内容部分应由“;”分隔

	// 例如:     strSearchContent = _T("point;rectangle;circle;ole object;")；
	SetSearchContent(strSearchContent);
}

void CMFCApplication1Doc::SetSearchContent(const CString& value)
{
	if (value.IsEmpty())
	{
		RemoveChunk(PKEY_Search_Contents.fmtid, PKEY_Search_Contents.pid);
	}
	else
	{
		CMFCFilterChunkValueImpl *pChunk = nullptr;
		ATLTRY(pChunk = new CMFCFilterChunkValueImpl);
		if (pChunk != nullptr)
		{
			pChunk->SetTextValue(PKEY_Search_Contents, value, CHUNK_TEXT);
			SetChunkValue(pChunk);
		}
	}
}

#endif // SHARED_HANDLERS

// CMFCApplication1Doc 诊断

#ifdef _DEBUG
void CMFCApplication1Doc::AssertValid() const
{
	CDocument::AssertValid();
}

void CMFCApplication1Doc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// CMFCApplication1Doc 命令


BOOL CMFCApplication1Doc::OnOpenDocument(LPCTSTR lpszPathName)
{
	if (!CDocument::OnOpenDocument(lpszPathName))
		return FALSE;

	// TODO:  在此添加您专用的创建代码
	CFile file;
	if (!file.Open(lpszPathName, CFile::modeRead |
		CFile::shareDenyWrite))// 打开文件
	{
		return FALSE;// 返回FALSE
	}
	DeleteContents();
	m_hDIB = m_dib.LoadFile(file);
	if (m_hDIB == NULL)// 调用LoadFile()读取图象
	{
		return FALSE;
	}
	SetDib();// 初始化DIB
	if (m_hDIB == NULL)	// 判断读取文件是否成功
	{
		AfxMessageBox(L"读取图像时出错");// 提示出错				
		return FALSE;// 返回FALSE
	}
	SetPathName(lpszPathName);// 设置文件名称		
	SetModifiedFlag(FALSE);// 初始化修改标记为FALSE	

	//保存源图像///////////////////////////////////////////////////////////////////
	long lSrcLineBytes;  //图象每行的字节数
	long lSrcWidth;      //图象的宽度和高度
	long lSrcHeight;
	int     lpSrcBitCount;       //图像的位深
	LPSTR lpSrcDib;  //指向源图象的指针 
	LPSTR lpSrcStartBits; //指向源像素的指针
	lpSrcDib = (LPSTR) ::GlobalLock((HGLOBAL)m_hDIB);// 锁定DIB
	if (!lpSrcDib) return FALSE;

	lpSrcStartBits = m_dib.GetBits(lpSrcDib);   // 找到DIB图象像素起始位置 
	lSrcWidth = m_dib.GetWidth(lpSrcDib);     // 获取图象的宽度  
	lSrcHeight = m_dib.GetHeight(lpSrcDib);     // 获取图象的高度 
	lpSrcBitCount = m_dib.GetBitCount(lpSrcDib);                    //获取图像位深
	lSrcLineBytes = m_dib.GetReqByteWidth(lSrcWidth * lpSrcBitCount);  // 计算图象每行的字节数
	int palettesize = 0;
	if (lpSrcBitCount == 8) palettesize = 256 * sizeof(RGBQUAD);
	lpImgCpy = new BYTE[lSrcLineBytes * lSrcHeight + sizeof(BITMAPINFOHEADER) + palettesize];

	memcpy(lpImgCpy, lpSrcDib, sizeof(BITMAPINFOHEADER) + palettesize + lSrcHeight * lSrcLineBytes);

	// 解除锁定
	::GlobalUnlock((HGLOBAL)m_hDIB);
	//////////////////////////////

	return TRUE;
}


BOOL CMFCApplication1Doc::OnSaveDocument(LPCTSTR lpszPathName)
{
	// TODO: 在此添加专用代码和/或调用基类
	CFile file;
	if (!file.Open(lpszPathName, CFile::modeCreate |// 打开文件
		CFile::modeReadWrite | CFile::shareExclusive))
	{
		return FALSE;// 返回FALSE
	}
	BOOL bSuccess = FALSE;
	bSuccess = m_dib.SaveFile(m_hDIB, file);	// 保存图象	
	file.Close();// 关闭文件	
	SetModifiedFlag(FALSE);// 重置脏标记为FALSE
	if (!bSuccess)
	{
		AfxMessageBox(L"保存BMP图象时出错");// 提示出错
	}
	return bSuccess;
	//return CDocument::OnSaveDocument(lpszPathName);
}

void CMFCApplication1Doc::SetDib() //这个函数需要手动添加
{
	LPSTR lpdib = (LPSTR) ::GlobalLock((HGLOBAL)m_hDIB);

	if (m_dib.GetWidth(lpdib) > INT_MAX || m_dib.GetHeight(lpdib) > INT_MAX)// 判断图象是否过大
	{
		::GlobalUnlock((HGLOBAL)m_hDIB);
		::GlobalFree((HGLOBAL)m_hDIB);	// 释放DIB对象			
		m_hDIB = NULL;// 设置DIB为空		
		AfxMessageBox(L"初始化失败");
		return;
	}
	m_sizeDoc = CSize((int)m_dib.GetWidth(lpdib), (int)m_dib.GetHeight(lpdib));// 设置文档大小	
	::GlobalUnlock((HGLOBAL)m_hDIB);
	m_palDIB = new CPalette;// 创建新调色板		
	if (m_palDIB == NULL)// 判断是否创建成功
	{
		::GlobalFree((HGLOBAL)m_hDIB);	// 失败		
		m_hDIB = NULL;// 设置DIB对象为空
		return;
	}
	// 调用CreateDIBPalette来创建调色板
	if (m_dib.ConstructPalette(m_hDIB, m_palDIB) == NULL)
	{
		delete m_palDIB;// 删除				
		m_palDIB = NULL;// 设置为空	
		return;// 返回空
	}
}
void CMFCApplication1Doc::UpdateObject(HGLOBAL hDIB)   //这个函数需要手动添加
{
	if (m_hDIB != NULL)               // 判断DIB是否为空
	{
		::GlobalFree((HGLOBAL)m_hDIB);// 非空，则清除
	}
	m_hDIB = hDIB;                     // 替换成新的DIB对象	
}

