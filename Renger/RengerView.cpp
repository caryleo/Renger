
// RengerView.cpp : CRengerView ���ʵ��
//

#include "stdafx.h"
// SHARED_HANDLERS ������ʵ��Ԥ��������ͼ������ɸѡ�������
// ATL ��Ŀ�н��ж��壬�����������Ŀ�����ĵ����롣
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
	// ��׼��ӡ����
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

// CRengerView ����/����

CRengerView::CRengerView()
{
	// TODO: �ڴ˴���ӹ������

}

CRengerView::~CRengerView()
{
}

BOOL CRengerView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: �ڴ˴�ͨ���޸�
	//  CREATESTRUCT cs ���޸Ĵ��������ʽ

	return CView::PreCreateWindow(cs);
}

// CRengerView ����

void CRengerView::OnDraw(CDC* /*pDC*/)
{
	CRengerDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: �ڴ˴�Ϊ����������ӻ��ƴ���
}


// CRengerView ��ӡ


void CRengerView::OnFilePrintPreview()
{
#ifndef SHARED_HANDLERS
	AFXPrintPreview(this);
#endif
}

BOOL CRengerView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// Ĭ��׼��
	return DoPreparePrinting(pInfo);
}

void CRengerView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: ��Ӷ���Ĵ�ӡǰ���еĳ�ʼ������
}

void CRengerView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: ��Ӵ�ӡ����е��������
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


// CRengerView ���

#ifdef _DEBUG
void CRengerView::AssertValid() const
{
	CView::AssertValid();
}

void CRengerView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CRengerDoc* CRengerView::GetDocument() const // �ǵ��԰汾��������
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CRengerDoc)));
	return (CRengerDoc*)m_pDocument;
}
#endif //_DEBUG


// CRengerView ��Ϣ�������


void CRengerView::OnSize(UINT nType, int cx, int cy)
{
	CView::OnSize(nType, cx, cy);
	m_gl.OnSize(cx, cy);
	// TODO: �ڴ˴������Ϣ����������
}


void CRengerView::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	m_gl.OnPaint();
	CView::OnTimer(nIDEvent);
}


BOOL CRengerView::OnEraseBkgnd(CDC* pDC)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	return TRUE;
	//return CView::OnEraseBkgnd(pDC);
}


BOOL CRengerView::PreTranslateMessage(MSG* pMsg)
{
	// TODO: �ڴ����ר�ô����/����û���
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
	// TODO: �ڴ����ר�ô����/����û���
}


void CRengerView::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// TODO: �ڴ˴������Ϣ����������
	// ��Ϊ��ͼ��Ϣ���� CView::OnPaint()
}
