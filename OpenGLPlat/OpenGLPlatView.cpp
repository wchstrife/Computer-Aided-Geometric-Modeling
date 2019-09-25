
// OpenGLPlatView.cpp: COpenGLPlatView 类的实现
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS 可以在实现预览、缩略图和搜索筛选器句柄的
// ATL 项目中进行定义，并允许与该项目共享文档代码。
#ifndef SHARED_HANDLERS
#include "OpenGLPlat.h"
#endif

#include "OpenGLPlatDoc.h"
#include "OpenGLPlatView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// COpenGLPlatView

IMPLEMENT_DYNCREATE(COpenGLPlatView, CView)

BEGIN_MESSAGE_MAP(COpenGLPlatView, CView)
	// 标准打印命令
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &COpenGLPlatView::OnFilePrintPreview)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
END_MESSAGE_MAP()

// COpenGLPlatView 构造/析构

COpenGLPlatView::COpenGLPlatView() noexcept
{
	// TODO: 在此处添加构造代码

}

COpenGLPlatView::~COpenGLPlatView()
{
}

BOOL COpenGLPlatView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: 在此处通过修改
	//  CREATESTRUCT cs 来修改窗口类或样式

	return CView::PreCreateWindow(cs);
}

// COpenGLPlatView 绘图

void COpenGLPlatView::OnDraw(CDC* /*pDC*/)
{
	COpenGLPlatDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: 在此处为本机数据添加绘制代码
}


// COpenGLPlatView 打印


void COpenGLPlatView::OnFilePrintPreview()
{
#ifndef SHARED_HANDLERS
	AFXPrintPreview(this);
#endif
}

BOOL COpenGLPlatView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 默认准备
	return DoPreparePrinting(pInfo);
}

void COpenGLPlatView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加额外的打印前进行的初始化过程
}

void COpenGLPlatView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加打印后进行的清理过程
}

void COpenGLPlatView::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void COpenGLPlatView::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


// COpenGLPlatView 诊断

#ifdef _DEBUG
void COpenGLPlatView::AssertValid() const
{
	CView::AssertValid();
}

void COpenGLPlatView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

COpenGLPlatDoc* COpenGLPlatView::GetDocument() const // 非调试版本是内联的
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(COpenGLPlatDoc)));
	return (COpenGLPlatDoc*)m_pDocument;
}
#endif //_DEBUG


// COpenGLPlatView 消息处理程序
