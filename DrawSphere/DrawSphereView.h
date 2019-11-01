
// DrawSphereView.h: CDrawSphereView 类的接口
//

#pragma once


class CDrawSphereView : public CView
{
protected: // 仅从序列化创建
	CDrawSphereView() noexcept;
	DECLARE_DYNCREATE(CDrawSphereView)

// 特性
public:
	CDrawSphereDoc* GetDocument() const;

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
	virtual ~CDrawSphereView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 生成的消息映射函数
protected:
	DECLARE_MESSAGE_MAP()
	// OpenGL渲染句柄(a handle to an OpenGL rendering context)
	HGLRC m_hRC;
public:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnDestroy();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
};

#ifndef _DEBUG  // DrawSphereView.cpp 中的调试版本
inline CDrawSphereDoc* CDrawSphereView::GetDocument() const
   { return reinterpret_cast<CDrawSphereDoc*>(m_pDocument); }
#endif

