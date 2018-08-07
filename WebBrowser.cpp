// WebBrowser.cpp : implementation file
//

#include "stdafx.h"
#include "WebBrowser2.h"
#include "WebBrowser.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CWebBrowser

IMPLEMENT_DYNCREATE(CWebBrowser, CFrameWnd)

CWebBrowser::CWebBrowser()
{
}

CWebBrowser::~CWebBrowser()
{
}


BEGIN_MESSAGE_MAP(CWebBrowser, CFrameWnd)
	//{{AFX_MSG_MAP(CWebBrowser)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CWebBrowser message handlers
