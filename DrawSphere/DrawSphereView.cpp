
// DrawSphereView.cpp: CDrawSphereView 类的实现
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS 可以在实现预览、缩略图和搜索筛选器句柄的
// ATL 项目中进行定义，并允许与该项目共享文档代码。
#ifndef SHARED_HANDLERS
#include "DrawSphere.h"
#endif

#include "DrawSphereDoc.h"
#include "DrawSphereView.h"
// ////////////////////////////////////////////////////////////////
// New codes begin:

// #include “GL/GL.H” // 这不是必要的，
#include "GL/GLU.H" // 已经包含GL.h
#include "CP_Sphere.h"

// New codes end.
// ////////////////////////////////////////////////////////////////

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CDrawSphereView

IMPLEMENT_DYNCREATE(CDrawSphereView, CView)

BEGIN_MESSAGE_MAP(CDrawSphereView, CView)
	// 标准打印命令
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
	ON_WM_CREATE()
	ON_WM_DESTROY()
	ON_WM_SIZE()
	ON_WM_ERASEBKGND()
END_MESSAGE_MAP()

// CDrawSphereView 构造/析构

CDrawSphereView::CDrawSphereView() noexcept
{
	// TODO: 在此处添加构造代码

}

CDrawSphereView::~CDrawSphereView()
{
}

BOOL CDrawSphereView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: 在此处通过修改
	//  CREATESTRUCT cs 来修改窗口类或样式

	return CView::PreCreateWindow(cs);
}

// CDrawSphereView 绘图

void CDrawSphereView::OnDraw(CDC* pDC)
{
	CDrawSphereDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: 在此处为本机数据添加绘制代码
	wglMakeCurrent(pDC->m_hDC, m_hRC);
	glClearColor(0, 1, 1, 1);
	glClearDepth(1.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	// *************************************************
// Setting lights and materials begins
// 设置光源与材料
	GLfloat material_ambient[] = { 0.2f, 0.2f, 0.2f, 0.2f };
	GLfloat material_diffuse[] = { 0.2f, 0.8f, 0.4f, 0.8f };
	GLfloat material_specular[] = { 0.2f, 0.8f, 0.4f, 0.8f };
	GLfloat material_emission[] = { 0.2f, 0.2f, 0.2f, 1.0f };
	GLfloat material_shininess[] = { 20.0f };
	glMaterialfv(GL_FRONT, GL_AMBIENT, material_ambient);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, material_diffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, material_specular);
	glMaterialfv(GL_FRONT, GL_EMISSION, material_emission);
	glMaterialfv(GL_FRONT, GL_SHININESS, material_shininess);
	GLfloat light_position[] = { 1.0f, 1.0f, 1.0f, 0.0f };
	GLfloat light_ambient[] = { 0.2f, 0.2f, 0.2f, 0.2f };
	GLfloat light_diffuse[] = { 0.5f, 0.5f, 0.5f, 0.2f };
	GLfloat light_specular[] = { 0.5f, 0.5f, 0.5f, 0.2f };
	glLightfv(GL_LIGHT0, GL_POSITION, light_position);
	glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
	glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);

	glEnable(GL_COLOR_MATERIAL);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_AUTO_NORMAL);
	glEnable(GL_NORMALIZE);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);
	// Setting lights and materials ends
	// ****************************************************
	glLoadIdentity();

	CP_Point3D p;
	CP_Sphere a(p, 2);
	glTranslated(-5.0, 0.0, 0.0);
	glColor3f(1.0, 0.0, 0.0); // 红色
	a.mb_drawSolid(false);
	glTranslated(5.0, 0.0, 0.0);
	a.mb_drawSolid(true);
	glTranslated(5.0, 0.0, 0.0);
	glColor3f(0.0, 0.0, 1.0); // 蓝色
	a.mb_drawWireframe();

	SwapBuffers(pDC->m_hDC);
	wglMakeCurrent(NULL, NULL);
	// New codes end.
	// ////////////////////////////////////
}



// CDrawSphereView 打印

BOOL CDrawSphereView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 默认准备
	return DoPreparePrinting(pInfo);
}

void CDrawSphereView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加额外的打印前进行的初始化过程
}

void CDrawSphereView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加打印后进行的清理过程
}


// CDrawSphereView 诊断

#ifdef _DEBUG
void CDrawSphereView::AssertValid() const
{
	CView::AssertValid();
}

void CDrawSphereView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CDrawSphereDoc* CDrawSphereView::GetDocument() const // 非调试版本是内联的
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CDrawSphereDoc)));
	return (CDrawSphereDoc*)m_pDocument;
}
#endif //_DEBUG


// CDrawSphereView 消息处理程序


int CDrawSphereView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CView::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  在此添加您专用的创建代码
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



void CDrawSphereView::OnDestroy()
{
	CView::OnDestroy();

	// TODO: 在此处添加消息处理程序代码
	// Set : a specified OpenGL rendering context ==> NULL
	// Set : current rendering context ==> NULL
	wglMakeCurrent(NULL, NULL);

	// Delete the handle to an OpenGL rendering context 
	wglDeleteContext(m_hRC);
	m_hRC = NULL;
	// New codes end.
	// ////////////////////////////////////////////////////////////////
}


void CDrawSphereView::OnSize(UINT nType, int cx, int cy)
{
	CView::OnSize(nType, cx, cy);

	// TODO: 在此处添加消息处理程序代码

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
}


BOOL CDrawSphereView::OnEraseBkgnd(CDC* pDC)
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
