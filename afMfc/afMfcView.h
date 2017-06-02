// afMfcView.h : interface of the CafMfcView class
//


#pragma once


class CafMfcView : public CView
{
protected: // create from serialization only
	CafMfcView();
	DECLARE_DYNCREATE(CafMfcView)

// Attributes
public:
	CafMfcDoc* GetDocument() const;

// Operations
public:

// Overrides
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// Implementation
public:
	virtual ~CafMfcView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in afMfcView.cpp
inline CafMfcDoc* CafMfcView::GetDocument() const
   { return reinterpret_cast<CafMfcDoc*>(m_pDocument); }
#endif
