#if !defined(AFX_HTMLDOC_H__03F90F21_8D49_4752_BB50_751CB918D343__INCLUDED_)
#define AFX_HTMLDOC_H__03F90F21_8D49_4752_BB50_751CB918D343__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// HtmlDoc.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CHtmlDoc document

class CHtmlDoc : public CDocument
{
protected:
	CHtmlDoc();           // protected constructor used by dynamic creation
	DECLARE_DYNCREATE(CHtmlDoc)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CHtmlDoc)
	public:
	virtual void Serialize(CArchive& ar);   // overridden for document i/o
	protected:
	virtual BOOL OnNewDocument();
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CHtmlDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// Generated message map functions
protected:
	//{{AFX_MSG(CHtmlDoc)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_HTMLDOC_H__03F90F21_8D49_4752_BB50_751CB918D343__INCLUDED_)
