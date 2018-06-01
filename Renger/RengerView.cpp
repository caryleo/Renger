
// RengerView.cpp : CRengerView 类的实现
//

#include "stdafx.h"
// SHARED_HANDLERS 可以在实现预览、缩略图和搜索筛选器句柄的
// ATL 项目中进行定义，并允许与该项目共享文档代码。
#ifndef SHARED_HANDLERS
#include "Renger.h"
#endif

#include "RengerDoc.h"
#include "RengerView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CRengerView

IMPLEMENT_DYNCREATE(CRengerView, CView)

BEGIN_MESSAGE_MAP(CRengerView, CView)
	// 标准打印命令
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CRengerView::OnFilePrintPreview)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
	ON_WM_SIZE()
	ON_WM_TIMER()
	ON_WM_ERASEBKGND()
	ON_WM_PAINT()
END_MESSAGE_MAP()

// CRengerView 构造/析构

CRengerView::CRengerView()
{
	// TODO: 在此处添加构造代码

}

CRengerView::~CRengerView()
{
}

BOOL CRengerView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: 在此处通过修改
	//  CREATESTRUCT cs 来修改窗口类或样式

	return CView::PreCreateWindow(cs);
}

// CRengerView 绘制

void CRengerView::OnDraw(CDC* /*pDC*/)
{
	CRengerDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: 在此处为本机数据添加绘制代码
}


// CRengerView 打印


void CRengerView::OnFilePrintPreview()
{
#ifndef SHARED_HANDLERS
	AFXPrintPreview(this);
#endif
}

BOOL CRengerView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 默认准备
	return DoPreparePrinting(pInfo);
}

void CRengerView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加额外的打印前进行的初始化过程
}

void CRengerView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加打印后进行的清理过程
}

void CRengerView::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CRengerView::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


// CRengerView 诊断

#ifdef _DEBUG
void CRengerView::AssertValid() const
{
	CView::AssertValid();
}

void CRengerView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CRengerDoc* CRengerView::GetDocument() const // 非调试版本是内联的
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CRengerDoc)));
	return (CRengerDoc*)m_pDocument;
}
#endif //_DEBUG


// CRengerView 消息处理程序


void CRengerView::OnSize(UINT nType, int cx, int cy)
{
	CView::OnSize(nType, cx, cy);
	m_gl.OnSize(cx, cy);
	// TODO: 在此处添加消息处理程序代码
}


void CRengerView::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	m_gl.OnPaint();
	CView::OnTimer(nIDEvent);
}


BOOL CRengerView::OnEraseBkgnd(CDC* pDC)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	return TRUE;
	//return CView::OnEraseBkgnd(pDC);
}


BOOL CRengerView::PreTranslateMessage(MSG* pMsg)
{
	// TODO: 在此添加专用代码和/或调用基类
	m_gl.PreTranslateMessage(pMsg->message, pMsg->wParam, pMsg->lParam);
	return CView::PreTranslateMessage(pMsg);
}


void CRengerView::OnInitialUpdate()
{
	CView::OnInitialUpdate();
	CView::OnInitialUpdate();
	if(!m_gl.Init(this->GetSafeHwnd()))
		AfxMessageBox("error!");
	CRect rect;
	GetClientRect(rect);
	m_gl.OnSize(rect.Width(), rect.Height());
	SetTimer(1, 30, nullptr);
	// TODO: 在此添加专用代码和/或调用基类
}


void CRengerView::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// TODO: 在此处添加消息处理程序代码
	// 不为绘图消息调用 CView::OnPaint()
}
