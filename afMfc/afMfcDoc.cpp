// afMfcDoc.cpp : implementation of the CafMfcDoc class
//

#include "stdafx.h"
#include "afMfc.h"

#include "afMfcDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CafMfcDoc

IMPLEMENT_DYNCREATE(CafMfcDoc, CDocument)

BEGIN_MESSAGE_MAP(CafMfcDoc, CDocument)
END_MESSAGE_MAP()


// CafMfcDoc construction/destruction

CafMfcDoc::CafMfcDoc()
{
	// TODO: add one-time construction code here

}

CafMfcDoc::~CafMfcDoc()
{
}

BOOL CafMfcDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}




// CafMfcDoc serialization

void CafMfcDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: add storing code here
	}
	else
	{
		// TODO: add loading code here
	}
}


// CafMfcDoc diagnostics

#ifdef _DEBUG
void CafMfcDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CafMfcDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// CafMfcDoc commands
