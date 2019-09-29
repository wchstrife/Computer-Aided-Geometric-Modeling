
// OpenGLPlatView.cpp: COpenGLPlatView 类的实现
//

#include "pch.h"
#include "framework.h"
#include "math.h"

// SHARED_HANDLERS 可以在实现预览、缩略图和搜索筛选器句柄的
// ATL 项目中进行定义，并允许与该项目共享文档代码。
#ifndef SHARED_HANDLERS
#include "OpenGLPlat.h"
#endif

#include "OpenGLPlatDoc.h"
#include "OpenGLPlatView.h"

// ////////////////////////////////////////////////////////////////
// New codes begin:

// #include “GL/GL.H” // 这不是必要的，
#include "GL/GLU.H" // 已经包含GL.h

// New codes end.
// ////////////////////////////////////////////////////////////////

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
	ON_WM_CREATE()
	ON_WM_DESTROY()
	ON_WM_SIZE()
	ON_WM_ERASEBKGND()
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

void COpenGLPlatView::OnDraw(CDC* pDC)
{
	COpenGLPlatDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: 在此处为本机数据添加绘制代码
	// ////////////////////////////////////////////////////////////////
	// New codes begin:
	wglMakeCurrent(pDC->m_hDC, m_hRC);

	glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);

	glLoadIdentity();
	/*
	int n = 9;
	double a = 4;
	double s = 0;
	double ds = 1.0 / (n - 1);
	double t = -4;
	double dt = -2 * t / (n - 1);
	double x, y;

	
	glBegin(GL_POLYGON);
	for (int i = 0; i < n; i++, s += ds, t += dt)
	{
		x = (1 - t * t) / (t * t + 1);
		y = 2 * t / (t * t + 1);
		glColor3d(1, s, 1 - s);
		glVertex3d(x * a, y * a, 0);
	} // for结构结束
	glEnd();
	*/

	// 绘制五角星
	// ////////////////////////////////////////////////////////////////
	const GLfloat Pi = 3.1415926536f;	
	const GLfloat m = 3;		// 正五角星的边长
	GLfloat a = m / sqrt(2 - 2 * cos(72 * Pi / 180));
	GLfloat bx = a * cos(18 * Pi / 180);
	GLfloat by = a * sin(18 * Pi / 180);
	GLfloat cx = a * sin(36 * Pi / 180);
	GLfloat cy = -a * cos(36 * Pi / 180);
	GLfloat
		PointA[2] = { 0, a },
		PointB[2] = { bx, by },
		PointC[2] = { cx, cy },
		PointD[2] = { -cx, cy },
		PointE[2] = { -bx, by };
	glClear(GL_COLOR_BUFFER_BIT);

	//闭合的线段
	glBegin(GL_LINE_LOOP);
	glVertex2fv(PointA);
	glVertex2fv(PointC);
	glVertex2fv(PointE);
	glVertex2fv(PointB);
	glVertex2fv(PointD);
	glColor3d(1, 0, 1);
	glEnd();
	// ////////////////////////////////////////////////////////////////

	// 绘制正六边形
	// ////////////////////////////////////////////////////////////////
	int n = 1000;
	glBegin(GL_POLYGON);
	glColor3f(1.0, 0.0, 0.0);
	for (int i = 1; i <= 6; i++)
	{
		glVertex2f(2.0f * cos(2 * (Pi / 6) * i) + 5.0f, 2.0f * sin(2 * (Pi / 6) * i));
	}
	glEnd();
	// ////////////////////////////////////////////////////////////////

	SwapBuffers(pDC->m_hDC);
	wglMakeCurrent(NULL, NULL);
	// New codes end.
	// ////////////////////////////////////////////////////////////////
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


int COpenGLPlatView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CView::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  在此添加您专用的创建代码
	// ////////////////////////////////////////////////////////////////
	// New codes begin:
		// The PIXELFORMATDESCRIPTOR structure describes
	//		the pixel format of a drawing surface.
	PIXELFORMATDESCRIPTOR pfd =
	{
		sizeof(PIXELFORMATDESCRIPTOR),  //  size of this pfd 
		1,                     			// version number 
		PFD_DRAW_TO_WINDOW |   	// support window 
		PFD_SUPPORT_OPENGL |   	// support OpenGL 
		PFD_DOUBLEBUFFER,	// double buffered
		PFD_TYPE_RGBA,
		24,                    	// 24-bit color depth 
		0, 0, 0, 0, 0, 0,      // color bits ignored 
		0,                     	// no alpha buffer 
		0,                     	// shift bit ignored 
		0,                     	// no accumulation buffer 
		0, 0, 0, 0,            	// accum bits ignored 
		32,                    	// 32-bit z-buffer (depth)
		0,                     	// no stencil buffer 
		0,                     	// no auxiliary buffer 
		PFD_MAIN_PLANE,        // main layer 
		0,                     	// reserved 
		0, 0, 0                	// layer masks ignored 
	};
	CClientDC dc(this);
	// Get the best available match of pixel format for the device context
	// In other words, if this computer doesn't support features that I
	// asked for, try to get the next best thing.  i.e. 16-bit color mode
	// instead of 24-bit color mode.
	int pixelFormat = ChoosePixelFormat(dc.m_hDC, &pfd);

	// Set the pixel format to the best pixel format I can get (see above)
	// and if that operation fails, bring up a message box that tells the
	// user the error.
	if (!SetPixelFormat(dc.m_hDC, pixelFormat, &pfd))
	{
		MessageBox(_T("Error: Unable to Set Pixel Format in CGLTemplate1View::OnCreate( )"),
			_T("Application Error"), MB_ICONERROR);
	}
	// Creates an OpenGL rendering context so that OpenGL knows how to draw
	// to this view. You can't use OpenGL in MFC without using the handle
	// that this function returns
	m_hRC = wglCreateContext(dc.m_hDC);

	// New codes end.
	// ////////////////////////////////////////////////////////////////

	return 0;
}



void COpenGLPlatView::OnDestroy()
{
	CView::OnDestroy();

	// TODO: 在此处添加消息处理程序代码
	// ////////////////////////////////////////////////////////////////
	// New codes begin:

	// Set : a specified OpenGL rendering context ==> NULL
	// Set : current rendering context ==> NULL
	wglMakeCurrent(NULL, NULL);

	// Delete the handle to an OpenGL rendering context 
	wglDeleteContext(m_hRC);
	m_hRC = NULL;
	// New codes end.
	// ////////////////////////////////////////////////////////////////
}


void COpenGLPlatView::OnSize(UINT nType, int cx, int cy)
{
	CView::OnSize(nType, cx, cy);

	// TODO: 在此处添加消息处理程序代码
	// ////////////////////////////////////////////////////////////////
	// New codes begin:

	CClientDC dc(this);
	wglMakeCurrent(dc.m_hDC, m_hRC);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	double d = 10;
	double n = 100;

	glOrtho(-cx / n, cx / n, -cy / n, cy / n, -d, d);

	glMatrixMode(GL_MODELVIEW);
	glViewport(0, 0, cx, cy);
	wglMakeCurrent(NULL, NULL);

	// New codes end.
	// ////////////////////////////////////////////////////////////////
}


BOOL COpenGLPlatView::OnEraseBkgnd(CDC* pDC)
{
	// TODO:在此添加消息处理程序代码和/或调用默认值

	// ////////////////////////////////////////////////////////////////
	// return CView::OnEraseBkgnd(pDC);
	// The above statement is commented
	//	and changed into the following statement
	//	such that the background is not repainted
	//	by the system
	// ////////////////////////////////////////////////////////////////
	return(TRUE);
}
