#if !defined(AFX_WEBBROWSER_H__9B9FD7F5_FD3B_4ED6_98C2_393D0318A999__INCLUDED_)
#define AFX_WEBBROWSER_H__9B9FD7F5_FD3B_4ED6_98C2_393D0318A999__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// WebBrowser.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CWebBrowser frame

class CWebBrowser : public CFrameWnd
{
	DECLARE_DYNCREATE(CWebBrowser)
protected:
	CWebBrowser();           // protected constructor used by dynamic creation

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CWebBrowser)
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~CWebBrowser();

	// Generated message map functions
	//{{AFX_MSG(CWebBrowser)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_WEBBROWSER_H__9B9FD7F5_FD3B_4ED6_98C2_393D0318A999__INCLUDED_)
