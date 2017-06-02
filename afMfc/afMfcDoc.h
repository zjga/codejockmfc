// afMfcDoc.h : interface of the CafMfcDoc class
//


#pragma once


class CafMfcDoc : public CDocument
{
protected: // create from serialization only
	CafMfcDoc();
	DECLARE_DYNCREATE(CafMfcDoc)

// Attributes
public:

// Operations
public:

// Overrides
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);

// Implementation
public:
	virtual ~CafMfcDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	DECLARE_MESSAGE_MAP()
};
