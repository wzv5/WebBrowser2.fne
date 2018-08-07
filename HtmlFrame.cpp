// HtmlFrame.cpp : implementation file
//

#include "stdafx.h"
#include "WebBrowser2.h"
#include "HtmlFrame.h"
#include "HtmlDoc.h"

#include <AFXPRIV.H>
#include "krnllib.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


INT WINAPI NotifySys (INT nMsg, DWORD dwParam1, DWORD dwParam2 = 0);

#include "untshare.cpp"
#include "fnshare.h"

extern CWebBrowser2App theApp;

/////////////////////////////////////////////////////////////////////////////
// CHtmlFrame

IMPLEMENT_DYNCREATE(CHtmlFrame, CFrameWnd)

CHtmlFrame::CHtmlFrame()
{
}

CHtmlFrame::~CHtmlFrame()
{
}


BEGIN_MESSAGE_MAP(CHtmlFrame, CFrameWnd)
	//{{AFX_MSG_MAP(CHtmlFrame)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CHtmlFrame message handlers
RECT rect;
DWORD dwhStyle;
HWND hhParentWnd;
UINT uhID;
HMENU hhMenu;

BOOL CHtmlFrame::LoadFrame(UINT nIDResource, DWORD dwDefaultStyle, CWnd* pParentWnd, CCreateContext* pContext) 
{
	// TODO: Add your specialized code here and/or call the base class
	//* only do this once
//	ASSERT_VALID_IDR(nIDResource);
	ASSERT(m_nIDHelp == 0 || m_nIDHelp == nIDResource);

	m_nIDHelp = nIDResource;    // ID for help context (+HID_BASE_RESOURCE)

	CString strFullString;
	if (strFullString.LoadString(nIDResource))
		AfxExtractSubString(m_strTitle, strFullString, 0);    // first sub-string

//	VERIFY(AfxDeferRegisterClass(AFX_WNDFRAMEORVIEW_REG));

	// attempt to create the window
	LPCTSTR lpszClass = GetIconWndClass(dwDefaultStyle, nIDResource);
	LPCTSTR lpszTitle = m_strTitle;


//////////////////////

	m_strTitle = lpszTitle;    // save title for later

	
	if (!CreateEx(0L, lpszClass, lpszTitle, WS_CHILD|dwhStyle,
		rect,CWnd::FromHandle(hhParentWnd), uhID, (LPVOID)pContext))
	{
		TRACE0("Warning: failed to create CFrameWnd.\n");
		if (hhMenu != NULL)
			DestroyMenu(hhMenu);
		return FALSE;
	}

//	if (!Create(lpszClass, lpszTitle, WS_CHILD|dwCurStyle, rect,
//	  pParentCWnd, MAKEINTRESOURCE(nIDResource), 0L, pContext))
//	{
//		return FALSE;   // will self destruct on failure normally
//	}
///////////////////////
	// save the default menu handle
	ASSERT(m_hWnd != NULL);
	m_hMenuDefault = ::GetMenu(m_hWnd);

	// load accelerator resource
	LoadAccelTable(MAKEINTRESOURCE(nIDResource));

	if (pContext == NULL)   // send initial update
		SendMessageToDescendants(WM_INITIALUPDATE, 0, 0, TRUE, TRUE);

	return TRUE;		
//	return CFrameWnd::LoadFrame(nIDResource, dwDefaultStyle, pParentWnd, pContext);
}

void CHtmlFrame::PostNcDestroy() 
{
	// TODO: Add your specialized code here and/or call the base class
	
	CFrameWnd::PostNcDestroy();
//	NotifySys (NRS_UNIT_DESTROIED, pView->m_dwWinFormID, pView->m_dwUnitID);
//	delete this;
}





