// WebBrowser2.h : main header file for the WEBBROWSER2 DLL
//

#if !defined(AFX_WEBBROWSER2_H__B842F9B2_E7D8_4163_BAD2_F786AAD28521__INCLUDED_)
#define AFX_WEBBROWSER2_H__B842F9B2_E7D8_4163_BAD2_F786AAD28521__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CWebBrowser2App
// See WebBrowser2.cpp for the implementation of this class
//

class CWebBrowser2App : public CWinApp
{
public:
	CWebBrowser2App();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CWebBrowser2App)
	//}}AFX_VIRTUAL

	//{{AFX_MSG(CWebBrowser2App)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_WEBBROWSER2_H__B842F9B2_E7D8_4163_BAD2_F786AAD28521__INCLUDED_)
