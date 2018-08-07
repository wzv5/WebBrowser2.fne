#if !defined(AFX_HTMLFRAME_H__F4AFAD4E_5BFD_4EF5_91D9_64BECFEFFF01__INCLUDED_)
#define AFX_HTMLFRAME_H__F4AFAD4E_5BFD_4EF5_91D9_64BECFEFFF01__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// HtmlFrame.h : header file
//

#include "ViewHtml.h"
/////////////////////////////////////////////////////////////////////////////
// CHtmlFrame frame

class CHtmlFrame : public CFrameWnd
{
	DECLARE_DYNCREATE(CHtmlFrame)
protected:
	CHtmlFrame();           // protected constructor used by dynamic creation

// Attributes
public:

// Operations
public:
//	CPIHtmlViewer m_info;
//	CViewHtml* pView;
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CHtmlFrame)
	public:
	virtual BOOL LoadFrame(UINT nIDResource, DWORD dwDefaultStyle = WS_OVERLAPPEDWINDOW | FWS_ADDTOTITLE, CWnd* pParentWnd = NULL, CCreateContext* pContext = NULL);
	protected:
	virtual void PostNcDestroy();
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~CHtmlFrame();

	// Generated message map functions
	//{{AFX_MSG(CHtmlFrame)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_HTMLFRAME_H__F4AFAD4E_5BFD_4EF5_91D9_64BECFEFFF01__INCLUDED_)
