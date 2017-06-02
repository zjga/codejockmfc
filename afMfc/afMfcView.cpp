// afMfcView.cpp : implementation of the CafMfcView class
//

#include "stdafx.h"
#include "afMfc.h"

#include "afMfcDoc.h"
#include "afMfcView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CafMfcView

IMPLEMENT_DYNCREATE(CafMfcView, CView)

BEGIN_MESSAGE_MAP(CafMfcView, CView)
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
END_MESSAGE_MAP()

// CafMfcView construction/destruction

CafMfcView::CafMfcView()
{
	// TODO: add construction code here

}

CafMfcView::~CafMfcView()
{
}

BOOL CafMfcView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

// CafMfcView drawing

void CafMfcView::OnDraw(CDC* /*pDC*/)
{
	CafMfcDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: add draw code for native data here
}


// CafMfcView printing

BOOL CafMfcView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CafMfcView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CafMfcView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}


// CafMfcView diagnostics

#ifdef _DEBUG
void CafMfcView::AssertValid() const
{
	CView::AssertValid();
}

void CafMfcView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CafMfcDoc* CafMfcView::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CafMfcDoc)));
	return (CafMfcDoc*)m_pDocument;
}
#endif //_DEBUG


// CafMfcView message handlers
