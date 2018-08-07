// WebBrowser2.cpp : Defines the initialization routines for the DLL.
//
//////////////////////////////////////////////////////////////////////////
#include "stdafx.h"
#include "WebBrowser2.h"

#include "ViewHtml.h"
#include "lib2.h"
#include "fnshare.h"
#include "krnllib.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

//
//	Note!
//
//		If this DLL is dynamically linked against the MFC
//		DLLs, any functions exported from this DLL which
//		call into MFC must have the AFX_MANAGE_STATE macro
//		added at the very beginning of the function.
//
//		For example:
//
//		extern "C" BOOL PASCAL EXPORT ExportedFunction()
//		{
//			AFX_MANAGE_STATE(AfxGetStaticModuleState());
//			// normal function body here
//		}
//
//		It is very important that this macro appear in each
//		function, prior to any calls into MFC.  This means that
//		it must appear as the first statement within the 
//		function, even before any object variable declarations
//		as their constructors may generate calls into the MFC
//		DLL.
//
//		Please see MFC Technical Notes 33 and 58 for additional
//		details.
//

/////////////////////////////////////////////////////////////////////////////
// CWebBrowser2App

BEGIN_MESSAGE_MAP(CWebBrowser2App, CWinApp)
	//{{AFX_MSG_MAP(CWebBrowser2App)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CWebBrowser2App construction

CWebBrowser2App::CWebBrowser2App()
{
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}

/////////////////////////////////////////////////////////////////////////////
// The one and only CWebBrowser2App object

#ifndef __E_STATIC_LIB

CWebBrowser2App theApp;

#endif
/////////////////////////////////////////////////////////////////////////////

INT g_nLastNotifyResult;
PFN_NOTIFY_SYS g_fnNotifySys = NULL;

INT WINAPI NotifySys (INT nMsg, DWORD dwParam1, DWORD dwParam2)
{
	ASSERT (g_fnNotifySys != NULL);
	if (g_fnNotifySys != NULL)
		return g_nLastNotifyResult = g_fnNotifySys (nMsg, dwParam1, dwParam2);
	else
		return g_nLastNotifyResult = 0;
}

#include "fnshare.cpp"
/////////////////////////


#ifndef __E_STATIC_LIB

LIB_DATA_TYPE_ELEMENT g_OLECMDID [] =
{
        {
        /*m_dtType*/            SDT_INT,
        /*m_pArySpec*/          NULL,
        /*m_szName*/            _T("OLECMDID_SHOWPAGEACTIONMENU"),
        /*m_szEgName*/          _T("OLECMDID_SHOWPAGEACTIONMENU"),
        /*m_szExplain*/         _T(""),
        /*m_dwState*/           LES_HAS_DEFAULT_VALUE,
        /*m_nDefault*/          59,
        }, 
        {
        /*m_dtType*/            SDT_INT,
        /*m_pArySpec*/          NULL,
        /*m_szName*/            _T("OLECMDID_FOCUSVIEWCONTROLSQUERY"),
        /*m_szEgName*/          _T("OLECMDID_FOCUSVIEWCONTROLSQUERY"),
        /*m_szExplain*/         _T(""),
        /*m_dwState*/           LES_HAS_DEFAULT_VALUE,
        /*m_nDefault*/          58,
        }, 
        {
        /*m_dtType*/            SDT_INT,
        /*m_pArySpec*/          NULL,
        /*m_szName*/            _T("OLECMDID_FOCUSVIEWCONTROLS"),
        /*m_szEgName*/          _T("OLECMDID_FOCUSVIEWCONTROLS"),
        /*m_szExplain*/         _T(""),
        /*m_dwState*/           LES_HAS_DEFAULT_VALUE,
        /*m_nDefault*/          57,
        }, 
        {
        /*m_dtType*/            SDT_INT,
        /*m_pArySpec*/          NULL,
        /*m_szName*/            _T("OLECMDID_PAGEACTIONUIQUERY"),
        /*m_szEgName*/          _T("OLECMDID_PAGEACTIONUIQUERY"),
        /*m_szExplain*/         _T(""),
        /*m_dwState*/           LES_HAS_DEFAULT_VALUE,
        /*m_nDefault*/          56,
        }, 
        {
        /*m_dtType*/            SDT_INT,
        /*m_pArySpec*/          NULL,
        /*m_szName*/            _T("OLECMDID_PAGEACTIONBLOCKED"),
        /*m_szEgName*/          _T("OLECMDID_PAGEACTIONBLOCKED"),
        /*m_szExplain*/         _T(""),
        /*m_dwState*/           LES_HAS_DEFAULT_VALUE,
        /*m_nDefault*/          55,
        }, 
        {
        /*m_dtType*/            SDT_INT,
        /*m_pArySpec*/          NULL,
        /*m_szName*/            _T("OLECMDID_GETPRINTTEMPLATE"),
        /*m_szEgName*/          _T("OLECMDID_GETPRINTTEMPLATE"),
        /*m_szExplain*/         _T(""),
        /*m_dwState*/           LES_HAS_DEFAULT_VALUE,
        /*m_nDefault*/          52,
        }, 
        {
        /*m_dtType*/            SDT_INT,
        /*m_pArySpec*/          NULL,
        /*m_szName*/            _T("OLECMDID_SETPRINTTEMPLATE"),
        /*m_szEgName*/          _T("OLECMDID_SETPRINTTEMPLATE"),
        /*m_szExplain*/         _T(""),
        /*m_dwState*/           LES_HAS_DEFAULT_VALUE,
        /*m_nDefault*/          51,
        }, 
        {
        /*m_dtType*/            SDT_INT,
        /*m_pArySpec*/          NULL,
        /*m_szName*/            _T("OLECMDID_PRINTPREVIEW2"),
        /*m_szEgName*/          _T("OLECMDID_PRINTPREVIEW2"),
        /*m_szExplain*/         _T(""),
        /*m_dwState*/           LES_HAS_DEFAULT_VALUE,
        /*m_nDefault*/          50,
        }, 
        {
        /*m_dtType*/            SDT_INT,
        /*m_pArySpec*/          NULL,
        /*m_szName*/            _T("OLECMDID_PRINT2"),
        /*m_szEgName*/          _T("OLECMDID_PRINT2"),
        /*m_szExplain*/         _T(""),
        /*m_dwState*/           LES_HAS_DEFAULT_VALUE,
        /*m_nDefault*/          49,
        }, 
        {
        /*m_dtType*/            SDT_INT,
        /*m_pArySpec*/          NULL,
        /*m_szName*/            _T("OLECMDID_UPDATEPAGESTATUS"),
        /*m_szEgName*/          _T("OLECMDID_UPDATEPAGESTATUS"),
        /*m_szExplain*/         _T(""),
        /*m_dwState*/           LES_HAS_DEFAULT_VALUE,
        /*m_nDefault*/          48,
        }, 
        {
        /*m_dtType*/            SDT_INT,
        /*m_pArySpec*/          NULL,
        /*m_szName*/            _T("OLECMDID_DONTDOWNLOADCSS"),
        /*m_szEgName*/          _T("OLECMDID_DONTDOWNLOADCSS"),
        /*m_szExplain*/         _T(""),
        /*m_dwState*/           LES_HAS_DEFAULT_VALUE,
        /*m_nDefault*/          47,
        }, 
        {
        /*m_dtType*/            SDT_INT,
        /*m_pArySpec*/          NULL,
        /*m_szName*/            _T("OLECMDID_ALLOWUILESSSAVEAS"),
        /*m_szEgName*/          _T("OLECMDID_ALLOWUILESSSAVEAS"),
        /*m_szExplain*/         _T(""),
        /*m_dwState*/           LES_HAS_DEFAULT_VALUE,
        /*m_nDefault*/          46,
        }, 
        {
        /*m_dtType*/            SDT_INT,
        /*m_pArySpec*/          NULL,
        /*m_szName*/            _T("OLECMDID_CLOSE"),
        /*m_szEgName*/          _T("OLECMDID_CLOSE"),
        /*m_szExplain*/         _T(""),
        /*m_dwState*/           LES_HAS_DEFAULT_VALUE,
        /*m_nDefault*/          45,
        }, 
        {
        /*m_dtType*/            SDT_INT,
        /*m_pArySpec*/          NULL,
        /*m_szName*/            _T("OLECMDID_SHOWPRINT"),
        /*m_szEgName*/          _T("OLECMDID_SHOWPRINT"),
        /*m_szExplain*/         _T(""),
        /*m_dwState*/           LES_HAS_DEFAULT_VALUE,
        /*m_nDefault*/          44,
        }, 
        {
        /*m_dtType*/            SDT_INT,
        /*m_pArySpec*/          NULL,
        /*m_szName*/            _T("OLECMDID_SHOWPAGESETUP"),
        /*m_szEgName*/          _T("OLECMDID_SHOWPAGESETUP"),
        /*m_szExplain*/         _T(""),
        /*m_dwState*/           LES_HAS_DEFAULT_VALUE,
        /*m_nDefault*/          43,
        }, 
        {
        /*m_dtType*/            SDT_INT,
        /*m_pArySpec*/          NULL,
        /*m_szName*/            _T("OLECMDID_SHOWFIND"),
        /*m_szEgName*/          _T("OLECMDID_SHOWFIND"),
        /*m_szExplain*/         _T(""),
        /*m_dwState*/           LES_HAS_DEFAULT_VALUE,
        /*m_nDefault*/          42,
        }, 
        {
        /*m_dtType*/            SDT_INT,
        /*m_pArySpec*/          NULL,
        /*m_szName*/            _T("OLECMDID_SHOWMESSAGE"),
        /*m_szEgName*/          _T("OLECMDID_SHOWMESSAGE"),
        /*m_szExplain*/         _T(""),
        /*m_dwState*/           LES_HAS_DEFAULT_VALUE,
        /*m_nDefault*/          41,
        }, 
        {
        /*m_dtType*/            SDT_INT,
        /*m_pArySpec*/          NULL,
        /*m_szName*/            _T("OLECMDID_SHOWSCRIPTERROR"),
        /*m_szEgName*/          _T("OLECMDID_SHOWSCRIPTERROR"),
        /*m_szExplain*/         _T(""),
        /*m_dwState*/           LES_HAS_DEFAULT_VALUE,
        /*m_nDefault*/          40,
        }, 
        {
        /*m_dtType*/            SDT_INT,
        /*m_pArySpec*/          NULL,
        /*m_szName*/            _T("OLECMDID_PREREFRESH"),
        /*m_szEgName*/          _T("OLECMDID_PREREFRESH"),
        /*m_szExplain*/         _T(""),
        /*m_dwState*/           LES_HAS_DEFAULT_VALUE,
        /*m_nDefault*/          39,
        }, 
        {
        /*m_dtType*/            SDT_INT,
        /*m_pArySpec*/          NULL,
        /*m_szName*/            _T("OLECMDID_PROPERTYBAG2"),
        /*m_szEgName*/          _T("OLECMDID_PROPERTYBAG2"),
        /*m_szExplain*/         _T(""),
        /*m_dwState*/           LES_HAS_DEFAULT_VALUE,
        /*m_nDefault*/          38,
        }, 
        {
        /*m_dtType*/            SDT_INT,
        /*m_pArySpec*/          NULL,
        /*m_szName*/            _T("OLECMDID_ONUNLOAD"),
        /*m_szEgName*/          _T("OLECMDID_ONUNLOAD"),
        /*m_szExplain*/         _T(""),
        /*m_dwState*/           LES_HAS_DEFAULT_VALUE,
        /*m_nDefault*/          37,
        }, 
        {
        /*m_dtType*/            SDT_INT,
        /*m_pArySpec*/          NULL,
        /*m_szName*/            _T("OLECMDID_ENABLE_INTERACTION"),
        /*m_szEgName*/          _T("OLECMDID_ENABLE_INTERACTION"),
        /*m_szExplain*/         _T(""),
        /*m_dwState*/           LES_HAS_DEFAULT_VALUE,
        /*m_nDefault*/          36,
        }, 
        {
        /*m_dtType*/            SDT_INT,
        /*m_pArySpec*/          NULL,
        /*m_szName*/            _T("OLECMDID_HTTPEQUIV_DONE"),
        /*m_szEgName*/          _T("OLECMDID_HTTPEQUIV_DONE"),
        /*m_szExplain*/         _T(""),
        /*m_dwState*/           LES_HAS_DEFAULT_VALUE,
        /*m_nDefault*/          35,
        }, 
        {
        /*m_dtType*/            SDT_INT,
        /*m_pArySpec*/          NULL,
        /*m_szName*/            _T("OLECMDID_HTTPEQUIV"),
        /*m_szEgName*/          _T("OLECMDID_HTTPEQUIV"),
        /*m_szExplain*/         _T(""),
        /*m_dwState*/           LES_HAS_DEFAULT_VALUE,
        /*m_nDefault*/          34,
        }, 
        {
        /*m_dtType*/            SDT_INT,
        /*m_pArySpec*/          NULL,
        /*m_szName*/            _T("OLECMDID_DELETE"),
        /*m_szEgName*/          _T("OLECMDID_DELETE"),
        /*m_szExplain*/         _T(""),
        /*m_dwState*/           LES_HAS_DEFAULT_VALUE,
        /*m_nDefault*/          33,
        }, 
        {
        /*m_dtType*/            SDT_INT,
        /*m_pArySpec*/          NULL,
        /*m_szName*/            _T("OLECMDID_FIND"),
        /*m_szEgName*/          _T("OLECMDID_FIND"),
        /*m_szExplain*/         _T(""),
        /*m_dwState*/           LES_HAS_DEFAULT_VALUE,
        /*m_nDefault*/          32,
        }, 
        {
        /*m_dtType*/            SDT_INT,
        /*m_pArySpec*/          NULL,
        /*m_szName*/            _T("OLECMDID_ONTOOLBARACTIVATED"),
        /*m_szEgName*/          _T("OLECMDID_ONTOOLBARACTIVATED"),
        /*m_szExplain*/         _T(""),
        /*m_dwState*/           LES_HAS_DEFAULT_VALUE,
        /*m_nDefault*/          31,
        }, 
        {
        /*m_dtType*/            SDT_INT,
        /*m_pArySpec*/          NULL,
        /*m_szName*/            _T("OLECMDID_STOPDOWNLOAD"),
        /*m_szEgName*/          _T("OLECMDID_STOPDOWNLOAD"),
        /*m_szExplain*/         _T(""),
        /*m_dwState*/           LES_HAS_DEFAULT_VALUE,
        /*m_nDefault*/          30,
        }, 
        {
        /*m_dtType*/            SDT_INT,
        /*m_pArySpec*/          NULL,
        /*m_szName*/            _T("OLECMDID_SETDOWNLOADSTATE"),
        /*m_szEgName*/          _T("OLECMDID_SETDOWNLOADSTATE"),
        /*m_szExplain*/         _T(""),
        /*m_dwState*/           LES_HAS_DEFAULT_VALUE,
        /*m_nDefault*/          29,
        }, 
        {
        /*m_dtType*/            SDT_INT,
        /*m_pArySpec*/          NULL,
        /*m_szName*/            _T("OLECMDID_SETTITLE"),
        /*m_szEgName*/          _T("OLECMDID_SETTITLE"),
        /*m_szExplain*/         _T(""),
        /*m_dwState*/           LES_HAS_DEFAULT_VALUE,
        /*m_nDefault*/          28,
        }, 
        {
        /*m_dtType*/            SDT_INT,
        /*m_pArySpec*/          NULL,
        /*m_szName*/            _T("OLECMDID_SETPROGRESSTEXT"),
        /*m_szEgName*/          _T("OLECMDID_SETPROGRESSTEXT"),
        /*m_szExplain*/         _T(""),
        /*m_dwState*/           LES_HAS_DEFAULT_VALUE,
        /*m_nDefault*/          27,
        }, 
        {
        /*m_dtType*/            SDT_INT,
        /*m_pArySpec*/          NULL,
        /*m_szName*/            _T("OLECMDID_SETPROGRESSPOS"),
        /*m_szEgName*/          _T("OLECMDID_SETPROGRESSPOS"),
        /*m_szExplain*/         _T(""),
        /*m_dwState*/           LES_HAS_DEFAULT_VALUE,
        /*m_nDefault*/          26,
        }, 
        {
        /*m_dtType*/            SDT_INT,
        /*m_pArySpec*/          NULL,
        /*m_szName*/            _T("OLECMDID_SETPROGRESSMAX"),
        /*m_szEgName*/          _T("OLECMDID_SETPROGRESSMAX"),
        /*m_szExplain*/         _T(""),
        /*m_dwState*/           LES_HAS_DEFAULT_VALUE,
        /*m_nDefault*/          25,
        }, 
        {
        /*m_dtType*/            SDT_INT,
        /*m_pArySpec*/          NULL,
        /*m_szName*/            _T("OLECMDID_HIDETOOLBARS"),
        /*m_szEgName*/          _T("OLECMDID_HIDETOOLBARS"),
        /*m_szExplain*/         _T(""),
        /*m_dwState*/           LES_HAS_DEFAULT_VALUE,
        /*m_nDefault*/          24,
        }, 
        {
        /*m_dtType*/            SDT_INT,
        /*m_pArySpec*/          NULL,
        /*m_szName*/            _T("OLECMDID_STOP"),
        /*m_szEgName*/          _T("OLECMDID_STOP"),
        /*m_szExplain*/         _T(""),
        /*m_dwState*/           LES_HAS_DEFAULT_VALUE,
        /*m_nDefault*/          23,
        }, 
        {
        /*m_dtType*/            SDT_INT,
        /*m_pArySpec*/          NULL,
        /*m_szName*/            _T("OLECMDID_REFRESH"),
        /*m_szEgName*/          _T("OLECMDID_REFRESH"),
        /*m_szExplain*/         _T(""),
        /*m_dwState*/           LES_HAS_DEFAULT_VALUE,
        /*m_nDefault*/          22,
        }, 
        {
        /*m_dtType*/            SDT_INT,
        /*m_pArySpec*/          NULL,
        /*m_szName*/            _T("OLECMDID_UPDATECOMMANDS"),
        /*m_szEgName*/          _T("OLECMDID_UPDATECOMMANDS"),
        /*m_szExplain*/         _T(""),
        /*m_dwState*/           LES_HAS_DEFAULT_VALUE,
        /*m_nDefault*/          21,
        }, 
        {
        /*m_dtType*/            SDT_INT,
        /*m_pArySpec*/          NULL,
        /*m_szName*/            _T("OLECMDID_GETZOOMRANGE"),
        /*m_szEgName*/          _T("OLECMDID_GETZOOMRANGE"),
        /*m_szExplain*/         _T(""),
        /*m_dwState*/           LES_HAS_DEFAULT_VALUE,
        /*m_nDefault*/          20,
        }, 
        {
        /*m_dtType*/            SDT_INT,
        /*m_pArySpec*/          NULL,
        /*m_szName*/            _T("OLECMDID_ZOOM"),
        /*m_szEgName*/          _T("OLECMDID_ZOOM"),
        /*m_szExplain*/         _T(""),
        /*m_dwState*/           LES_HAS_DEFAULT_VALUE,
        /*m_nDefault*/          19,
        }, 
        {
        /*m_dtType*/            SDT_INT,
        /*m_pArySpec*/          NULL,
        /*m_szName*/            _T("OLECMDID_CLEARSELECTION"),
        /*m_szEgName*/          _T("OLECMDID_CLEARSELECTION"),
        /*m_szExplain*/         _T(""),
        /*m_dwState*/           LES_HAS_DEFAULT_VALUE,
        /*m_nDefault*/          18,
        }, 
        {
        /*m_dtType*/            SDT_INT,
        /*m_pArySpec*/          NULL,
        /*m_szName*/            _T("OLECMDID_SELECTALL"),
        /*m_szEgName*/          _T("OLECMDID_SELECTALL"),
        /*m_szExplain*/         _T(""),
        /*m_dwState*/           LES_HAS_DEFAULT_VALUE,
        /*m_nDefault*/          17,
        }, 
        {
        /*m_dtType*/            SDT_INT,
        /*m_pArySpec*/          NULL,
        /*m_szName*/            _T("OLECMDID_REDO"),
        /*m_szEgName*/          _T("OLECMDID_REDO"),
        /*m_szExplain*/         _T(""),
        /*m_dwState*/           LES_HAS_DEFAULT_VALUE,
        /*m_nDefault*/          16,
        }, 
        {
        /*m_dtType*/            SDT_INT,
        /*m_pArySpec*/          NULL,
        /*m_szName*/            _T("OLECMDID_UNDO"),
        /*m_szEgName*/          _T("OLECMDID_UNDO"),
        /*m_szExplain*/         _T(""),
        /*m_dwState*/           LES_HAS_DEFAULT_VALUE,
        /*m_nDefault*/          15,
        }, 
        {
        /*m_dtType*/            SDT_INT,
        /*m_pArySpec*/          NULL,
        /*m_szName*/            _T("OLECMDID_PASTESPECIAL"),
        /*m_szEgName*/          _T("OLECMDID_PASTESPECIAL"),
        /*m_szExplain*/         _T(""),
        /*m_dwState*/           LES_HAS_DEFAULT_VALUE,
        /*m_nDefault*/          14,
        }, 
        {
        /*m_dtType*/            SDT_INT,
        /*m_pArySpec*/          NULL,
        /*m_szName*/            _T("OLECMDID_PASTE"),
        /*m_szEgName*/          _T("OLECMDID_PASTE"),
        /*m_szExplain*/         _T(""),
        /*m_dwState*/           LES_HAS_DEFAULT_VALUE,
        /*m_nDefault*/          13,
        }, 
        {
        /*m_dtType*/            SDT_INT,
        /*m_pArySpec*/          NULL,
        /*m_szName*/            _T("OLECMDID_COPY"),
        /*m_szEgName*/          _T("OLECMDID_COPY"),
        /*m_szExplain*/         _T(""),
        /*m_dwState*/           LES_HAS_DEFAULT_VALUE,
        /*m_nDefault*/          12,
        }, 
        {
        /*m_dtType*/            SDT_INT,
        /*m_pArySpec*/          NULL,
        /*m_szName*/            _T("OLECMDID_CUT"),
        /*m_szEgName*/          _T("OLECMDID_CUT"),
        /*m_szExplain*/         _T(""),
        /*m_dwState*/           LES_HAS_DEFAULT_VALUE,
        /*m_nDefault*/          11,
        }, 
        {
        /*m_dtType*/            SDT_INT,
        /*m_pArySpec*/          NULL,
        /*m_szName*/            _T("OLECMDID_PROPERTIES"),
        /*m_szEgName*/          _T("OLECMDID_PROPERTIES"),
        /*m_szExplain*/         _T(""),
        /*m_dwState*/           LES_HAS_DEFAULT_VALUE,
        /*m_nDefault*/          10,
        }, 
        {
        /*m_dtType*/            SDT_INT,
        /*m_pArySpec*/          NULL,
        /*m_szName*/            _T("OLECMDID_SPELL"),
        /*m_szEgName*/          _T("OLECMDID_SPELL"),
        /*m_szExplain*/         _T(""),
        /*m_dwState*/           LES_HAS_DEFAULT_VALUE,
        /*m_nDefault*/          9,
        }, 
        {
        /*m_dtType*/            SDT_INT,
        /*m_pArySpec*/          NULL,
        /*m_szName*/            _T("OLECMDID_PAGESETUP"),
        /*m_szEgName*/          _T("OLECMDID_PAGESETUP"),
        /*m_szExplain*/         _T(""),
        /*m_dwState*/           LES_HAS_DEFAULT_VALUE,
        /*m_nDefault*/          8,
        }, 
        {
        /*m_dtType*/            SDT_INT,
        /*m_pArySpec*/          NULL,
        /*m_szName*/            _T("OLECMDID_PRINTPREVIEW"),
        /*m_szEgName*/          _T("OLECMDID_PRINTPREVIEW"),
        /*m_szExplain*/         _T(""),
        /*m_dwState*/           LES_HAS_DEFAULT_VALUE,
        /*m_nDefault*/          7,
        }, 
        {
        /*m_dtType*/            SDT_INT,
        /*m_pArySpec*/          NULL,
        /*m_szName*/            _T("OLECMDID_PRINT"),
        /*m_szEgName*/          _T("OLECMDID_PRINT"),
        /*m_szExplain*/         _T(""),
        /*m_dwState*/           LES_HAS_DEFAULT_VALUE,
        /*m_nDefault*/          6,
        }, 
        {
        /*m_dtType*/            SDT_INT,
        /*m_pArySpec*/          NULL,
        /*m_szName*/            _T("OLECMDID_SAVECOPYAS"),
        /*m_szEgName*/          _T("OLECMDID_SAVECOPYAS"),
        /*m_szExplain*/         _T(""),
        /*m_dwState*/           LES_HAS_DEFAULT_VALUE,
        /*m_nDefault*/          5,
        }, 
        {
        /*m_dtType*/            SDT_INT,
        /*m_pArySpec*/          NULL,
        /*m_szName*/            _T("OLECMDID_SAVEAS"),
        /*m_szEgName*/          _T("OLECMDID_SAVEAS"),
        /*m_szExplain*/         _T(""),
        /*m_dwState*/           LES_HAS_DEFAULT_VALUE,
        /*m_nDefault*/          4,
        }, 
        {
        /*m_dtType*/            SDT_INT,
        /*m_pArySpec*/          NULL,
        /*m_szName*/            _T("OLECMDID_SAVE"),
        /*m_szEgName*/          _T("OLECMDID_SAVE"),
        /*m_szExplain*/         _T(""),
        /*m_dwState*/           LES_HAS_DEFAULT_VALUE,
        /*m_nDefault*/          3,
        }, 
        {
        /*m_dtType*/            SDT_INT,
        /*m_pArySpec*/          NULL,
        /*m_szName*/            _T("OLECMDID_NEW"),
        /*m_szEgName*/          _T("OLECMDID_NEW"),
        /*m_szExplain*/         _T(""),
        /*m_dwState*/           LES_HAS_DEFAULT_VALUE,
        /*m_nDefault*/          2,
        }, 
        {
        /*m_dtType*/            SDT_INT,
        /*m_pArySpec*/          NULL,
        /*m_szName*/            _T("OLECMDID_OPEN"),
        /*m_szEgName*/          _T("OLECMDID_OPEN"),
        /*m_szExplain*/         _T(""),
        /*m_dwState*/           LES_HAS_DEFAULT_VALUE,
        /*m_nDefault*/          1,
        }, 

};

    LIB_DATA_TYPE_ELEMENT g_OLECMDF [] =
    {
        {
        /*m_dtType*/            SDT_INT,
        /*m_pArySpec*/          NULL,
        /*m_szName*/            _T("OLECMDF_DEFHIDEONCTXTMENU"),
        /*m_szEgName*/          _T("OLECMDF_DEFHIDEONCTXTMENU"),
        /*m_szExplain*/         _T(""),
        /*m_dwState*/           LES_HAS_DEFAULT_VALUE,
        /*m_nDefault*/          32,
        }, 
        {
        /*m_dtType*/            SDT_INT,
        /*m_pArySpec*/          NULL,
        /*m_szName*/            _T("OLECMDF_INVISIBLE"),
        /*m_szEgName*/          _T("OLECMDF_INVISIBLE"),
        /*m_szExplain*/         _T(""),
        /*m_dwState*/           LES_HAS_DEFAULT_VALUE,
        /*m_nDefault*/          16,
        }, 
        {
        /*m_dtType*/            SDT_INT,
        /*m_pArySpec*/          NULL,
        /*m_szName*/            _T("OLECMDF_NINCHED"),
        /*m_szEgName*/          _T("OLECMDF_NINCHED"),
        /*m_szExplain*/         _T(""),
        /*m_dwState*/           LES_HAS_DEFAULT_VALUE,
        /*m_nDefault*/          8,
        }, 
        {
        /*m_dtType*/            SDT_INT,
        /*m_pArySpec*/          NULL,
        /*m_szName*/            _T("OLECMDF_LATCHED"),
        /*m_szEgName*/          _T("OLECMDF_LATCHED"),
        /*m_szExplain*/         _T(""),
        /*m_dwState*/           LES_HAS_DEFAULT_VALUE,
        /*m_nDefault*/          4,
        }, 
        {
        /*m_dtType*/            SDT_INT,
        /*m_pArySpec*/          NULL,
        /*m_szName*/            _T("OLECMDF_ENABLED"),
        /*m_szEgName*/          _T("OLECMDF_ENABLED"),
        /*m_szExplain*/         _T(""),
        /*m_dwState*/           LES_HAS_DEFAULT_VALUE,
        /*m_nDefault*/          2,
        }, 
        {
        /*m_dtType*/            SDT_INT,
        /*m_pArySpec*/          NULL,
        /*m_szName*/            _T("OLECMDF_SUPPORTED"),
        /*m_szEgName*/          _T("OLECMDF_SUPPORTED"),
        /*m_szExplain*/         _T(""),
        /*m_dwState*/           LES_HAS_DEFAULT_VALUE,
        /*m_nDefault*/          1,
        }, 
	};
    LIB_DATA_TYPE_ELEMENT g_OLECMDEXECOPT [] =
    {
        {
        /*m_dtType*/            SDT_INT,
        /*m_pArySpec*/          NULL,
        /*m_szName*/            _T("OLECMDEXECOPT_SHOWHELP"),
        /*m_szEgName*/          _T("OLECMDEXECOPT_SHOWHELP"),
        /*m_szExplain*/         _T(""),
        /*m_dwState*/           LES_HAS_DEFAULT_VALUE,
        /*m_nDefault*/          3,
        }, 
        {
        /*m_dtType*/            SDT_INT,
        /*m_pArySpec*/          NULL,
        /*m_szName*/            _T("OLECMDEXECOPT_DONTPROMPTUSER"),
        /*m_szEgName*/          _T("OLECMDEXECOPT_DONTPROMPTUSER"),
        /*m_szExplain*/         _T(""),
        /*m_dwState*/           LES_HAS_DEFAULT_VALUE,
        /*m_nDefault*/          2,
        }, 
        {
        /*m_dtType*/            SDT_INT,
        /*m_pArySpec*/          NULL,
        /*m_szName*/            _T("OLECMDEXECOPT_PROMPTUSER"),
        /*m_szEgName*/          _T("OLECMDEXECOPT_PROMPTUSER"),
        /*m_szExplain*/         _T(""),
        /*m_dwState*/           LES_HAS_DEFAULT_VALUE,
        /*m_nDefault*/          1,
        }, 
        {
        /*m_dtType*/            SDT_INT,
        /*m_pArySpec*/          NULL,
        /*m_szName*/            _T("OLECMDEXECOPT_DODEFAULT"),
        /*m_szEgName*/          _T("OLECMDEXECOPT_DODEFAULT"),
        /*m_szExplain*/         _T(""),
        /*m_dwState*/           LES_HAS_DEFAULT_VALUE,
        /*m_nDefault*/          0,
        }, 

	};
    LIB_DATA_TYPE_ELEMENT g_tagREADYSTATE [] =
    {
        {
        /*m_dtType*/            SDT_INT,
        /*m_pArySpec*/          NULL,
        /*m_szName*/            _T("READYSTATE_COMPLETE"),
        /*m_szEgName*/          _T("READYSTATE_COMPLETE"),
        /*m_szExplain*/         _T(""),
        /*m_dwState*/           LES_HAS_DEFAULT_VALUE,
        /*m_nDefault*/          4,
        }, 
        {
        /*m_dtType*/            SDT_INT,
        /*m_pArySpec*/          NULL,
        /*m_szName*/            _T("READYSTATE_INTERACTIVE"),
        /*m_szEgName*/          _T("READYSTATE_INTERACTIVE"),
        /*m_szExplain*/         _T(""),
        /*m_dwState*/           LES_HAS_DEFAULT_VALUE,
        /*m_nDefault*/          3,
        }, 
        {
        /*m_dtType*/            SDT_INT,
        /*m_pArySpec*/          NULL,
        /*m_szName*/            _T("READYSTATE_LOADED"),
        /*m_szEgName*/          _T("READYSTATE_LOADED"),
        /*m_szExplain*/         _T(""),
        /*m_dwState*/           LES_HAS_DEFAULT_VALUE,
        /*m_nDefault*/          2,
        }, 
        {
        /*m_dtType*/            SDT_INT,
        /*m_pArySpec*/          NULL,
        /*m_szName*/            _T("READYSTATE_LOADING"),
        /*m_szEgName*/          _T("READYSTATE_LOADING"),
        /*m_szExplain*/         _T(""),
        /*m_dwState*/           LES_HAS_DEFAULT_VALUE,
        /*m_nDefault*/          1,
        }, 
        {
        /*m_dtType*/            SDT_INT,
        /*m_pArySpec*/          NULL,
        /*m_szName*/            _T("READYSTATE_UNINITIALIZED"),
        /*m_szEgName*/          _T("READYSTATE_UNINITIALIZED"),
        /*m_szExplain*/         _T(""),
        /*m_dwState*/           LES_HAS_DEFAULT_VALUE,
        /*m_nDefault*/          0,
        }, 

	};
/////////////////////////////////////////////////////////////////////////////


INT s_nHtmlViewerElementCmdIndex [] =
{
	0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22
};

extern UNIT_PROPERTY g_HtmlViewerProperty [];
extern INT g_HtmlViewerPropertyCount;
extern EVENT_INFO2 g_HtmlViewerEvent [];
extern INT g_HtmlViewerEventCount;

// 下面的定义顺序绝对不可改动。
static LIB_DATA_TYPE_INFO s_DataType[] = 
{
	{
/*m_szName*/					_WT("互联网浏览器"),
/*m_szEgName*/					_WT("WebBrowser"),
/*m_szExplain*/					_WT("提供对HTML页面的浏览支持"),
/*m_nCmdCount*/					sizeof (s_nHtmlViewerElementCmdIndex) / sizeof (s_nHtmlViewerElementCmdIndex [0]),
/*m_pnCmdsIndex*/				s_nHtmlViewerElementCmdIndex,
/*m_dwState*/					LDT_WIN_UNIT|_LIB_OS(__OS_WIN),
/*m_dwUnitBmpID*/				IDB_BITMAP1,
/*m_nEventCount*/				g_HtmlViewerEventCount,
/*m_pEventBegin*/				g_HtmlViewerEvent,
/*m_nPropertyCount*/			g_HtmlViewerPropertyCount,
/*m_pPropertyBegin*/			g_HtmlViewerProperty,
/*m_pfnGetInterface*/			webbrowser2_GetInterface_WebBrowser,
/*m_nElementCount*/				0,
/*m_pElementBegin*/				NULL,
	},
		{
			/*m_szName*/                _T("OLECMDID"),
 			/*m_szEgName*/              _T("OLECMDID"),
			/*m_szExplain*/             _T("执行命令方法用到常数"),
 			/*m_nCmdCount*/             0,      // 没有成员方法
			/*m_pnCmdsIndex*/           NULL,
			/*m_dwState*/               (1 << 22)|_LIB_OS(__OS_WIN),
			/*m_dwUnitBmpID*/           0,
			/*m_nEventCount*/           0,      // 必须为 0 。
			/*m_pEventBegin*/           NULL,
			/*m_nPropertyCount*/        0,      // 必须为 0 。
			/*m_pPropertyBegin*/        NULL,
			/*m_pfnGetInterface*/       NULL,   // 必须为 NULL 。
			/*m_nElementCount*/         sizeof (g_OLECMDID) / sizeof (g_OLECMDID [0]),
			/*m_pElementBegin*/         g_OLECMDID,
		},
		{
			/*m_szName*/                _T("OLECMDF"),
 			/*m_szEgName*/              _T("OLECMDF"),
			/*m_szExplain*/             _T("执行命令方法用到常数"),
 			/*m_nCmdCount*/             0,      // 没有成员方法
			/*m_pnCmdsIndex*/           NULL,
			/*m_dwState*/               (1 << 22)|_LIB_OS(__OS_WIN),
			/*m_dwUnitBmpID*/           0,
			/*m_nEventCount*/           0,      // 必须为 0 。
			/*m_pEventBegin*/           NULL,
			/*m_nPropertyCount*/        0,      // 必须为 0 。
			/*m_pPropertyBegin*/        NULL,
			/*m_pfnGetInterface*/       NULL,   // 必须为 NULL 。
			/*m_nElementCount*/         sizeof (g_OLECMDF) / sizeof (g_OLECMDF [0]),
			/*m_pElementBegin*/         g_OLECMDF,
		},
		{
			/*m_szName*/                _T("OLECMDEXECOPT"),
 			/*m_szEgName*/              _T("OLECMDEXECOPT"),
			/*m_szExplain*/             _T("执行命令方法用到常数"),
 			/*m_nCmdCount*/             0,      // 没有成员方法
			/*m_pnCmdsIndex*/           NULL,
			/*m_dwState*/               (1 << 22)|_LIB_OS(__OS_WIN),
			/*m_dwUnitBmpID*/           0,
			/*m_nEventCount*/           0,      // 必须为 0 。
			/*m_pEventBegin*/           NULL,
			/*m_nPropertyCount*/        0,      // 必须为 0 。
			/*m_pPropertyBegin*/        NULL,
			/*m_pfnGetInterface*/       NULL,   // 必须为 NULL 。
			/*m_nElementCount*/         sizeof (g_OLECMDEXECOPT) / sizeof (g_OLECMDEXECOPT [0]),
			/*m_pElementBegin*/         g_OLECMDEXECOPT,
		},
		{
			/*m_szName*/                _T("tagREADYSTATE"),
 			/*m_szEgName*/              _T("tagREADYSTATE"),
			/*m_szExplain*/             _T("就绪状态所返回的常数值"),
 			/*m_nCmdCount*/             0,      // 没有成员方法
			/*m_pnCmdsIndex*/           NULL,
			/*m_dwState*/               (1 << 22)|_LIB_OS(__OS_WIN),
			/*m_dwUnitBmpID*/           0,
			/*m_nEventCount*/           0,      // 必须为 0 。
			/*m_pEventBegin*/           NULL,
			/*m_nPropertyCount*/        0,      // 必须为 0 。
			/*m_pPropertyBegin*/        NULL,
			/*m_pfnGetInterface*/       NULL,   // 必须为 NULL 。
			/*m_nElementCount*/         sizeof (g_tagREADYSTATE) / sizeof (g_tagREADYSTATE [0]),
			/*m_pElementBegin*/         g_tagREADYSTATE,
		},
};
///


///////////////////////////////////

//*** 命令定义信息:

ARG_INFO s_ArgInfo[] =
{
//****** 跳转	**	0
	{
/*name*/	_WT("网页地址"),
/*explain*/	_WT("浏览位于互联网或本机上的地址"),
/*bmp inx*/	0,
/*bmp num*/	0,
/*type*/	SDT_TEXT,
/*default*/	0,
/*state*/	NULL,
	},
//****** 标志	**	1
	{
/*name*/	_WT("标记"),
/*explain*/	_WT("浏览网页相关的标记"),
/*bmp inx*/	0,
/*bmp num*/	0,
/*type*/	SDT_INT,
/*default*/	0,
/*state*/	AS_DEFAULT_VALUE_IS_EMPTY,
	},
//****** 目标窗口名	**	2
	{
/*name*/	_WT("目标窗口名称"),
/*explain*/	_WT("为将要跳转到的目标窗口名称"),
/*bmp inx*/	0,
/*bmp num*/	0,
/*type*/	SDT_TEXT,
/*default*/	0,
/*state*/	AS_DEFAULT_VALUE_IS_EMPTY,
	},
//****** 目标窗口名	**	3
	{
/*name*/	_WT("类型说明"),
/*explain*/	_WT("为POST命令投送数据的编码类型。例：Content-Type: application/x-www-form-urlencoded"),
/*bmp inx*/	0,
/*bmp num*/	0,
/*type*/	SDT_TEXT,
/*default*/	0,
/*state*/	AS_DEFAULT_VALUE_IS_EMPTY,
	},
//****** 目标窗口名	**	4
	{
/*name*/	_WT("对象"),
/*explain*/	_WT("为将要跳转到的目标窗口名称"),
/*bmp inx*/	0,
/*bmp num*/	0,
/*type*/	DTP_COM_OBJECT,
/*default*/	0,
/*state*/	NULL,
	},
//****** 执行命令	**	5
	{
/*name*/	_WT("欲执行的命令"),
/*explain*/	_WT("指定欲执行命令的类型，为枚举常量OLECMDID的值之一"),
/*bmp inx*/	0,
/*bmp num*/	0,
/*type*/	SDT_INT,
/*default*/	0,
/*state*/	NULL,
	},
//****** 新网页接口	**	6
	{
/*name*/	_WT("命令反馈"),
/*explain*/	_WT("指定命令反馈，为以下常量值之一： "
			"0: #默认； "
			"1: #提示用户； "
			"2: #不提示用户； "
			"3: #显示帮助； "),
/*bmp inx*/	0,
/*bmp num*/	0,
/*type*/	SDT_INT,
/*default*/	0,
/*state*/	AS_DEFAULT_VALUE_IS_EMPTY,
	},
//****** 对象	**	7
	{
/*name*/	_WT("输入"),
/*explain*/	_WT("为命令的输入参数"),
/*bmp inx*/	0,
/*bmp num*/	0,
/*type*/	DTP_VARIANT,
/*default*/	0,
/*state*/	AS_DEFAULT_VALUE_IS_EMPTY,
	},
//****** 对象	**	8
	{
/*name*/	_WT("输出"),
/*explain*/	_WT("为命令的输出结果"),
/*bmp inx*/	0,
/*bmp num*/	0,
/*type*/	DTP_VARIANT,
/*default*/	0,
/*state*/	AS_DEFAULT_VALUE_IS_EMPTY,
	},
//****** 对象	**	9
	{
/*name*/	_WT("属性名称"),
/*explain*/	_WT("欲设定值的属性名称"),
/*bmp inx*/	0,
/*bmp num*/	0,
/*type*/	SDT_TEXT,
/*default*/	0,
/*state*/	NULL,
	},
//****** 对象	**	10
	{
/*name*/	_WT("属性值"),
/*explain*/	_WT("欲设定的属性值"),
/*bmp inx*/	0,
/*bmp num*/	0,
/*type*/	DTP_VARIANT,
/*default*/	0,
/*state*/	NULL,
	},
//****** 执行命令	**	11
	{
/*name*/	_WT("对齐方式"),
/*explain*/	_WT("0、无；1、左对齐；2、居中；3、右对齐；4、项目列表；5、数字列表；6、增加缩进；7、减少缩进；"),
/*bmp inx*/	0,
/*bmp num*/	0,
/*type*/	SDT_INT,
/*default*/	0,
/*state*/	NULL,
	},//****** 执行命令	**	12
	{
/*name*/	_WT("字体风格"),
/*explain*/	_WT("0、粗体；1、斜体；2、下划线；3、删除线；4、上标；5、下标；"),
/*bmp inx*/	0,
/*bmp num*/	0,
/*type*/	SDT_INT,
/*default*/	0,
/*state*/	NULL,
	},//****** 执行命令	**	13
	{
/*name*/	_WT("HTML代码"),
/*explain*/	_WT("欲加入的HTML代码。"),
/*bmp inx*/	0,
/*bmp num*/	0,
/*type*/	SDT_TEXT,
/*default*/	0,
/*state*/	NULL,
	},//****** 执行命令	**	14
	{
/*name*/	_WT("命令常数"),
/*explain*/	_WT("各种命令的常数值在VC的头文件MsHtmcid.h里定义。推荐你到微软网站下载最新文件以获得对IE6命令的支持。 "),
/*bmp inx*/	0,
/*bmp num*/	0,
/*type*/	SDT_INT,
/*default*/	0,
/*state*/	NULL,
	},
};

static CMD_INFO s_CmdInfo[] =
{
/////////////////////////////////// 超文本浏览框

//****** 跳转（成员）	** 0
	{
/*ccname*/	_WT("浏览"),
/*egname*/	_WT("Navigate"),
/*explain*/	_WT("打开互联网或者本机上指定位置处的文档"),
/*category*/-1,
/*state*/	_CMD_OS(__OS_WIN),
/*ret*/		_SDT_NULL,
/*reserved*/0,
/*level*/	LVL_SIMPLE,
/*bmp inx*/	0,
/*bmp num*/	0,
/*ArgCount*/4,
/*arg lp*/	s_ArgInfo,
	},
//****** 跳转（成员）	** 1
	{
/*ccname*/	_WT("取浏览器对象"),
/*egname*/	_WT("GetApplication"),
/*explain*/	_WT(""),
/*category*/-1,
/*state*/	_CMD_OS(__OS_WIN),
/*ret*/		NULL,
/*reserved*/0,
/*level*/	LVL_SIMPLE,
/*bmp inx*/	0,
/*bmp num*/	0,
/*ArgCount*/1,
/*arg lp*/	&s_ArgInfo[4],
	},
//****** 跳转（成员）	** 2
	{
/*ccname*/	_WT("取网页文档对象"),
/*egname*/	_WT("GetHtmlDocument"),
/*explain*/	_WT(""),
/*category*/-1,
/*state*/	_CMD_OS(__OS_WIN),
/*ret*/		NULL,
/*reserved*/0,
/*level*/	LVL_SIMPLE,
/*bmp inx*/	0,
/*bmp num*/	0,
/*ArgCount*/1,
/*arg lp*/	&s_ArgInfo[4],
	},
//****** 跳转（成员）	** 3
	{
/*ccname*/	_WT("取容器对象"),
/*egname*/	_WT("GetContainer"),
/*explain*/	_WT(""),
/*category*/-1,
/*state*/	_CMD_OS(__OS_WIN),
/*ret*/		NULL,
/*reserved*/0,
/*level*/	LVL_SIMPLE,
/*bmp inx*/	0,
/*bmp num*/	0,
/*ArgCount*/1,
/*arg lp*/	&s_ArgInfo[4],
	},
//****** 跳转（成员）	** 4
	{
/*ccname*/	_WT("前进"),
/*egname*/	_WT("GoForward"),
/*explain*/	_WT("到历史列表的下一页"),
/*category*/-1,
/*state*/	_CMD_OS(__OS_WIN),
/*ret*/		_SDT_NULL,
/*reserved*/0,
/*level*/	LVL_SIMPLE,
/*bmp inx*/	0,
/*bmp num*/	0,
/*ArgCount*/0,
/*arg lp*/	NULL,
	},
//****** 跳转（成员）	** 5
	{
/*ccname*/	_WT("后退"),
/*egname*/	_WT("GoBack"),
/*explain*/	_WT("到历史列表的前一页"),
/*category*/-1,
/*state*/	_CMD_OS(__OS_WIN),
/*ret*/		_SDT_NULL,
/*reserved*/0,
/*level*/	LVL_SIMPLE,
/*bmp inx*/	0,
/*bmp num*/	0,
/*ArgCount*/0,
/*arg lp*/	NULL,
	},
//****** 跳转（成员）	** 6
	{
/*ccname*/	_WT("到主页"),
/*egname*/	_WT("GoHome"),
/*explain*/	_WT("到IE所设置的主页"),
/*category*/-1,
/*state*/	_CMD_OS(__OS_WIN),
/*ret*/		_SDT_NULL,
/*reserved*/0,
/*level*/	LVL_SIMPLE,
/*bmp inx*/	0,
/*bmp num*/	0,
/*ArgCount*/0,
/*arg lp*/	NULL,
	},
//****** 跳转（成员）	** 7
	{
/*ccname*/	_WT("到搜索页"),
/*egname*/	_WT("GoSearch"),
/*explain*/	_WT("到当前查找页"),
/*category*/-1,
/*state*/	_CMD_OS(__OS_WIN),
/*ret*/		_SDT_NULL,
/*reserved*/0,
/*level*/	LVL_SIMPLE,
/*bmp inx*/	0,
/*bmp num*/	0,
/*ArgCount*/0,
/*arg lp*/	NULL,
	},
//****** 跳转（成员）	** 8
	{
/*ccname*/	_WT("刷新"),
/*egname*/	_WT("Refresh"),
/*explain*/	_WT("重载当前文件"),
/*category*/-1,
/*state*/	_CMD_OS(__OS_WIN),
/*ret*/		_SDT_NULL,
/*reserved*/0,
/*level*/	LVL_SIMPLE,
/*bmp inx*/	0,
/*bmp num*/	0,
/*ArgCount*/0,
/*arg lp*/	NULL,
	},
//****** 跳转（成员）	** 9
	{
/*ccname*/	_WT("停止"),
/*egname*/	_WT("Stop"),
/*explain*/	_WT("停止打开文件"),
/*category*/-1,
/*state*/	_CMD_OS(__OS_WIN),
/*ret*/		_SDT_NULL,
/*reserved*/0,
/*level*/	LVL_SIMPLE,
/*bmp inx*/	0,
/*bmp num*/	0,
/*ArgCount*/0,
/*arg lp*/	NULL,
	},
//****** 执行命令（成员）	** 10
	{
/*ccname*/	_WT("执行命令"),
/*egname*/	_WT("ExecWB"),
/*explain*/	_WT("执行指定的浏览器命令"),
/*category*/-1,
/*state*/	_CMD_OS(__OS_WIN),
/*ret*/		_SDT_NULL,
/*reserved*/0,
/*level*/	LVL_SIMPLE,
/*bmp inx*/	0,
/*bmp num*/	0,
/*ArgCount*/4,
/*arg lp*/	&s_ArgInfo[5],
	},
//****** 执行命令（成员）	** 11
	{
/*ccname*/	_WT("查询命令状态"),
/*egname*/	_WT("QueryStatusWB"),
/*explain*/	_WT("查询命令的相关信息。比如是否支持。"
		"返回值为以下各值的组合： "
			"1: #支持； "
			"2: #允许； "
			"4: #停用； "
			"8: #NINCHED； "
			"16: #不可视； "),
/*category*/-1,
/*state*/	_CMD_OS(__OS_WIN),
/*ret*/		SDT_INT,
/*reserved*/0,
/*level*/	LVL_SIMPLE,
/*bmp inx*/	0,
/*bmp num*/	0,
/*ArgCount*/1,
/*arg lp*/	&s_ArgInfo[5],
	},
//****** 跳转（成员）	** 12
	{
/*ccname*/	_WT("置属性值"),
/*egname*/	_WT("PutProperty"),
/*explain*/	_WT("设置浏览器对象的属性值"),
/*category*/-1,
/*state*/	_CMD_OS(__OS_WIN),
/*ret*/		_SDT_NULL,
/*reserved*/0,
/*level*/	LVL_SIMPLE,
/*bmp inx*/	0,
/*bmp num*/	0,
/*ArgCount*/2,
/*arg lp*/	&s_ArgInfo[9],
	},
//****** 执行命令（成员）	** 13
	{
/*ccname*/	_WT("取属性值"),
/*egname*/	_WT("GetProperty"),
/*explain*/	_WT("取浏览器对象的属性值"),
/*category*/-1,
/*state*/	_CMD_OS(__OS_WIN),
/*ret*/		DTP_VARIANT,
/*reserved*/0,
/*level*/	LVL_SIMPLE,
/*bmp inx*/	0,
/*bmp num*/	0,
/*ArgCount*/1,
/*arg lp*/	&s_ArgInfo[9],
	},
//****** 跳转（成员）	** 14
	{
/*ccname*/	_WT("置选区格式"),
/*egname*/	_WT("JustifyFormat"),
/*explain*/	_WT("在编辑模式下，设置当前选中区赤显示格式。成功返回真。"),
/*category*/-1,
/*state*/	_CMD_OS(__OS_WIN),
/*ret*/		SDT_BOOL,
/*reserved*/0,
/*level*/	LVL_SIMPLE,
/*bmp inx*/	0,
/*bmp num*/	0,
/*ArgCount*/1,
/*arg lp*/	&s_ArgInfo[11],
	},//****** 跳转（成员）	** 15
	{
/*ccname*/	_WT("取消选区"),
/*egname*/	_WT("Unselect"),
/*explain*/	_WT("在编辑模式下，清除当前选中区的选中状态。成功返回真。"),
/*category*/-1,
/*state*/	_CMD_OS(__OS_WIN),
/*ret*/		SDT_BOOL,
/*reserved*/0,
/*level*/	LVL_SIMPLE,
/*bmp inx*/	0,
/*bmp num*/	0,
/*ArgCount*/0,
/*arg lp*/	NULL,
	},//****** 跳转（成员）	** 16
	{
/*ccname*/	_WT("保存文档"),
/*egname*/	_WT("SaveAs"),
/*explain*/	_WT("将当前HTML页面保存为文件。成功返回真。"),
/*category*/-1,
/*state*/	_CMD_OS(__OS_WIN),
/*ret*/		SDT_BOOL,
/*reserved*/0,
/*level*/	LVL_SIMPLE,
/*bmp inx*/	0,
/*bmp num*/	0,
/*ArgCount*/0,
/*arg lp*/	NULL,
	},//****** 跳转（成员）	** 17
	{
/*ccname*/	_WT("插入覆盖切换"),
/*egname*/	_WT("OverWrite"),
/*explain*/	_WT("在编辑模式下，进行插入和覆盖输入状态的切换。成功返回真。"),
/*category*/-1,
/*state*/	_CMD_OS(__OS_WIN),
/*ret*/		SDT_BOOL,
/*reserved*/0,
/*level*/	LVL_SIMPLE,
/*bmp inx*/	0,
/*bmp num*/	0,
/*ArgCount*/0,
/*arg lp*/	NULL,
	},
//****** 跳转（成员）	** 18
	{
/*ccname*/	_WT("转换字体风格"),
/*egname*/	_WT("SetFontStyle"),
/*explain*/	_WT("在编辑模式下，切换指定的字体风格，和原来的相反。成功返回真。"),
/*category*/-1,
/*state*/	_CMD_OS(__OS_WIN),
/*ret*/		SDT_BOOL,
/*reserved*/0,
/*level*/	LVL_SIMPLE,
/*bmp inx*/	0,
/*bmp num*/	0,
/*ArgCount*/1,
/*arg lp*/	&s_ArgInfo[12],
	},//****** 跳转（成员）	** 19
	{
/*ccname*/	_WT("插入链接"),
/*egname*/	_WT("CreateLink"),
/*explain*/	_WT("在编辑模式下，显示一个对话框允许用户指定要为当前选中区插入的超级链接。成功返回真。"),
/*category*/-1,
/*state*/	_CMD_OS(__OS_WIN),
/*ret*/		SDT_BOOL,
/*reserved*/0,
/*level*/	LVL_SIMPLE,
/*bmp inx*/	0,
/*bmp num*/	0,
/*ArgCount*/0,
/*arg lp*/	NULL,
	},//****** 跳转（成员）	** 20
	{
/*ccname*/	_WT("删除链接"),
/*egname*/	_WT("Unlink"),
/*explain*/	_WT("在编辑模式下，从当前选中区中删除全部超级链接。成功返回真。"),
/*category*/-1,
/*state*/	_CMD_OS(__OS_WIN),
/*ret*/		SDT_BOOL,
/*reserved*/0,
/*level*/	LVL_SIMPLE,
/*bmp inx*/	0,
/*bmp num*/	0,
/*ArgCount*/0,
/*arg lp*/	NULL,
	},//****** 跳转（成员）	** 21
	{
/*ccname*/	_WT("贴入代码"),
/*egname*/	_WT("pasteHTML"),
/*explain*/	_WT("在编辑模式下，向当前选中区中贴入指定的HTML代码。成功返回真。"),
/*category*/-1,
/*state*/	_CMD_OS(__OS_WIN),
/*ret*/		SDT_BOOL,
/*reserved*/0,
/*level*/	LVL_SIMPLE,
/*bmp inx*/	0,
/*bmp num*/	0,
/*ArgCount*/1,
/*arg lp*/	&s_ArgInfo[13],
	},
//****** 执行命令（成员）	** 22
	{
/*ccname*/	_WT("执行网页命令"),
/*egname*/	_WT("ExecCommand"),
/*explain*/	_WT("执行指定的网页命令。比如执行打印、查看源文件、查找、打开“Internet选项”、“添加到收藏夹”等等操作。"),
/*category*/-1,
/*state*/	_CMD_OS(__OS_WIN),
/*ret*/		SDT_INT,
/*reserved*/0,
/*level*/	LVL_SIMPLE,
/*bmp inx*/	0,
/*bmp num*/	0,
/*ArgCount*/1,
/*arg lp*/	&s_ArgInfo[14],
	},
};

#endif

extern "C"
void webbrowser2_fnNavigate (PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf)
{
	CViewHtml* pUnit = (CViewHtml*)GetWndPtr (pArgInf);

	LPCTSTR lpszTargetFrameName=NULL;
	LPCTSTR lpszHeaders=NULL;
	if(pArgInf [3].m_dtDataType !=_SDT_NULL)
		lpszTargetFrameName=pArgInf [3].m_pText;
	if(pArgInf [4].m_dtDataType !=_SDT_NULL)
		lpszHeaders=pArgInf [4].m_pText;

	pUnit->Navigate ((LPCTSTR)pArgInf [1].m_pText,pArgInf [2].m_int,lpszTargetFrameName,lpszHeaders);
}

extern "C"
void webbrowser2_fnGetApplication (PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf)
{
	CViewHtml* pUnit = (CViewHtml*)GetWndPtr (pArgInf);
	LPDISPATCH pDis=*(LPDISPATCH*)pArgInf [1].m_ppCompoundData;
	if(pDis)
		pDis->Release();

	*(LPDISPATCH*)pArgInf [1].m_ppCompoundData=pUnit->GetApplication();

}

extern "C"
void webbrowser2_fnGetHtmlDocument (PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf)
{
	CViewHtml* pUnit = (CViewHtml*)GetWndPtr (pArgInf);
	LPDISPATCH pDis=*(LPDISPATCH*)pArgInf [1].m_ppCompoundData;
	if(pDis)
		pDis->Release();
	*(LPDISPATCH*)pArgInf [1].m_ppCompoundData=pUnit->GetHtmlDocument();

}

extern "C"
void webbrowser2_fnGetContainer (PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf)
{
	CViewHtml* pUnit = (CViewHtml*)GetWndPtr (pArgInf);
	LPDISPATCH pDis=*(LPDISPATCH*)pArgInf [1].m_ppCompoundData;
	if(pDis)
		pDis->Release();
	*(LPDISPATCH*)pArgInf [1].m_ppCompoundData=pUnit->GetContainer ();

}

extern "C"
void webbrowser2_fnGoForward (PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf)
{
	CViewHtml* pUnit = (CViewHtml*)GetWndPtr (pArgInf);


	pUnit->GoForward();
}

extern "C"
void webbrowser2_fnGoBack (PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf)
{
	CViewHtml* pUnit = (CViewHtml*)GetWndPtr (pArgInf);

	pUnit->GoBack();
}

extern "C"
void webbrowser2_fnGoHome (PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf)
{
	CViewHtml* pUnit = (CViewHtml*)GetWndPtr (pArgInf);

	pUnit->GoHome();
}

extern "C"
void webbrowser2_fnGoSearch (PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf)
{
	CViewHtml* pUnit = (CViewHtml*)GetWndPtr (pArgInf);

	pUnit->GoSearch();
}

extern "C"
void webbrowser2_fnRefresh (PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf)
{
	CViewHtml* pUnit = (CViewHtml*)GetWndPtr (pArgInf);

	pUnit->Refresh();
}

extern "C"
void webbrowser2_fnStop (PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf)
{
	CViewHtml* pUnit = (CViewHtml*)GetWndPtr (pArgInf);

	pUnit->Stop();
}

extern "C"
void webbrowser2_fnExecute (PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf)
{
	CViewHtml* pUnit = (CViewHtml*)GetWndPtr (pArgInf);


	VARIANT* pvtIn=NULL;//=(VARIANT)pArgInf [3].m_pCompoundData;

	VARIANT* pvtOut=NULL;//=(VARIANT)pArgInf [4].m_pCompoundData;

	if(pArgInf [3].m_dtDataType !=_SDT_NULL)
		pvtIn=(VARIANT*)pArgInf [3].m_pCompoundData;

	if(pArgInf [4].m_dtDataType !=_SDT_NULL)
		pvtOut=(VARIANT*)pArgInf [4].m_pCompoundData;

//		VariantClear(&pvtOut);
	//pvtOut.vt=VT_EMPTY;
/*
  	LPDISPATCH lpDisp =pUnit ->GetHtmlDocument();


	if (lpDisp != NULL) 
	{
		LPOLECOMMANDTARGET lpTarget;
 		if (SUCCEEDED(lpDisp->QueryInterface(IID_IOleCommandTarget,
                    (LPVOID*) &lpTarget))) {
  			lpTarget->Exec(NULL, (OLECMDID)pArgInf [1].m_int, (OLECMDEXECOPT)pArgInf [2].m_int, &pvtIn,&pvtOut);
  			lpTarget->Release();
 		}
 		lpDisp->Release();
 	}*/
	pUnit->ExecWB((OLECMDID)pArgInf [1].m_int,(OLECMDEXECOPT)pArgInf [2].m_int,pvtIn,pvtOut);


}

extern "C"
void webbrowser2_fnQueryStatusWB (PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf)
{
	CViewHtml* pUnit = (CViewHtml*)GetWndPtr (pArgInf);

	pRetData->m_int=pUnit->QueryStatusWB ((OLECMDID)pArgInf [1].m_int);
}

extern "C"
void webbrowser2_fnPutProperty (PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf)
{
	CViewHtml* pUnit = (CViewHtml*)GetWndPtr (pArgInf);
//	VARIANT pvtIn;
	//V_BOOL(&pvtIn)=(VARIANT_BOOL)TRUE;

	
//	pUnit->PutProperty("Silent2",pvtIn);
	pUnit->PutProperty(pArgInf [1].m_pText,*(VARIANT*)pArgInf [2].m_pCompoundData );
}

extern "C"
void webbrowser2_fnGetProperty (PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf)
{
	CViewHtml* pUnit = (CViewHtml*)GetWndPtr (pArgInf);
	pRetData->m_pCompoundData= (VARIANT*)NotifySys (NRS_MALLOC, sizeof(VARIANT), 0);
	(*((VARIANT*)pRetData->m_pCompoundData)).vt=VT_I4;

	*(VARIANT*)pRetData->m_pCompoundData=pUnit->GetProperty(pArgInf [1].m_pText);
}
//////////新增命令/////////////

extern "C"
void webbrowser2_fnJustify (PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf)
{
	CViewHtml* pUnit = (CViewHtml*)GetWndPtr (pArgInf);


		CString strURL;
	switch (pArgInf [1].m_int)
	{
	case 0:
		strURL="JustifyNone";
		break;
	case 1:
		strURL="JustifyLeft";
		break;
	case 2:
		strURL="JustifyCenter";
		break;
	case 3:
		strURL="JustifyRight";
		break;
	case 4:
		strURL="insertunorderedlist";
		break;
	case 5:
		strURL="insertorderedlist";
		break;
	case 6:
		strURL="indent";
		break;
	case 7:
		strURL="outdent";
		break;

	}
		pRetData->m_bool=pUnit->execCommand (strURL);



}

extern "C"
void webbrowser2_fnUnselect (PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf)
{
	CViewHtml* pUnit = (CViewHtml*)GetWndPtr (pArgInf);

		CString strURL("Unselect");
		pRetData->m_bool=pUnit->execCommand (strURL);

}

extern "C"
void webbrowser2_fnSaveAs (PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf)
{
	CViewHtml* pUnit = (CViewHtml*)GetWndPtr (pArgInf);

		CString strURL("SaveAs");
		pRetData->m_bool=pUnit->execCommand (strURL);

}

extern "C"
void webbrowser2_fnOverWrite (PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf)
{
	CViewHtml* pUnit = (CViewHtml*)GetWndPtr (pArgInf);

		CString strURL("OverWrite");
		pRetData->m_bool=pUnit->execCommand (strURL);

}

extern "C"
void webbrowser2_fnSetFontStyle (PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf)
{
	CViewHtml* pUnit = (CViewHtml*)GetWndPtr (pArgInf);

		CString strURL;

	switch (pArgInf [1].m_int)
	{
	case 0:
		strURL="Bold";
		break;
	case 1:
		strURL="Italic";
		break;
	case 2:
		strURL="Underline";
		break;
	case 3:
		strURL="StrikeThrough";
		break;
	case 4:
		strURL="Superscript";
		break;
	case 5:
		strURL="Subscript";
		break;

	}
		pRetData->m_bool=pUnit->execCommand (strURL);

}

extern "C"
void webbrowser2_fnCreateLink (PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf)
{
	CViewHtml* pUnit = (CViewHtml*)GetWndPtr (pArgInf);

		CString strURL("CreateLink");
		pRetData->m_bool=pUnit->execCommand (strURL);

}

extern "C"
void webbrowser2_fnUnlink (PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf)
{
	CViewHtml* pUnit = (CViewHtml*)GetWndPtr (pArgInf);

		CString strURL("Unlink");
		pRetData->m_bool=pUnit->execCommand (strURL);

}

extern "C"
void webbrowser2_fnpasteHTML (PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf)
{
	CViewHtml* pUnit = (CViewHtml*)GetWndPtr (pArgInf);


	IHTMLSelectionObject * pObject;
	IDispatch * Range;
	IHTMLTxtRange * TxtRange;
	pRetData->m_bool=FALSE;

	IHTMLDocument2* pDoc =(IHTMLDocument2*)pUnit->GetHtmlDocument();

	if(!pDoc)
		return;
	CString strURL(pArgInf [1].m_pText);
	BSTR bstr = strURL.AllocSysString();

	HRESULT hr=pDoc->get_selection(&pObject);
	if(SUCCEEDED(hr))
	{
		hr=pObject->createRange( &Range);
		if(SUCCEEDED(hr))
		{
			hr=Range->QueryInterface(&TxtRange);
			if(SUCCEEDED(hr))
			{
				hr=TxtRange->pasteHTML(bstr);
				pRetData->m_bool=SUCCEEDED(hr);
				TxtRange->Release();
			}
			Range->Release();
		}
		pObject->Release ();
	}
	pDoc->Release ();

	::SysFreeString(bstr);

}

extern "C"
void webbrowser2_fnExecCommand (PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf)
{
	CViewHtml* pUnit = (CViewHtml*)GetWndPtr (pArgInf);


	pRetData->m_int=pUnit->ExecHTMCommand (pArgInf [1].m_int);

}
	
///////////////////////////////////fnWriteCookie
//*** 命令实现信息:
#ifndef __E_STATIC_LIB

PFN_EXECUTE_CMD s_RunFunc [] =	// 索引应与s_CmdInfo中的命令定义顺序对应
{

	webbrowser2_fnNavigate,
	webbrowser2_fnGetApplication,
	webbrowser2_fnGetHtmlDocument,
	webbrowser2_fnGetContainer,
	webbrowser2_fnGoForward,
	webbrowser2_fnGoBack,
	webbrowser2_fnGoHome,
	webbrowser2_fnGoSearch,
	webbrowser2_fnRefresh,
	webbrowser2_fnStop,
	webbrowser2_fnExecute,
	webbrowser2_fnQueryStatusWB,
	webbrowser2_fnPutProperty,
	webbrowser2_fnGetProperty,
	webbrowser2_fnJustify,
	webbrowser2_fnUnselect,
	webbrowser2_fnSaveAs,
	webbrowser2_fnOverWrite,
	webbrowser2_fnSetFontStyle,
	webbrowser2_fnCreateLink,
	webbrowser2_fnUnlink,
	webbrowser2_fnpasteHTML,
	webbrowser2_fnExecCommand,
};


static const char* const g_CmdNames[] = 
{
	"webbrowser2_fnNavigate",
    "webbrowser2_fnGetApplication",
	"webbrowser2_fnGetHtmlDocument",
	"webbrowser2_fnGetContainer",
	"webbrowser2_fnGoForward",
	"webbrowser2_fnGoBack",
	"webbrowser2_fnGoHome",
	"webbrowser2_fnGoSearch",
	"webbrowser2_fnRefresh",
	"webbrowser2_fnStop",
	"webbrowser2_fnExecute",
	"webbrowser2_fnQueryStatusWB",
	"webbrowser2_fnPutProperty",
	"webbrowser2_fnGetProperty",
	"webbrowser2_fnJustify",
	"webbrowser2_fnUnselect",
	"webbrowser2_fnSaveAs",
	"webbrowser2_fnOverWrite",
	"webbrowser2_fnSetFontStyle",
	"webbrowser2_fnCreateLink",
	"webbrowser2_fnUnlink",
	"webbrowser2_fnpasteHTML",
	"webbrowser2_fnExecCommand",
};
///////////////////////////////////

//*** 常量定义信息:

// !!! 注意常量值由于已经运用到程序中，所以绝对不能改动。
// 顺序及值不能改动

LIB_CONST_INFO s_ConstInfo [] =
{
	{	_WT("前进"),	NULL,	NULL,	LVL_SIMPLE,	CT_NUM,	NULL,	1,	},
	{	_WT("后退"),	NULL,	NULL,	LVL_SIMPLE,	CT_NUM,	NULL,	2,	},
	{	_WT("更新状态"),	NULL,	NULL,	LVL_SIMPLE,	CT_NUM,	NULL,	-1,	},
};

#endif
/////////////////////////////////////////////////////////////////////////////

INT WINAPI ProcessNotifyLib (INT nMsg, DWORD dwParam1, DWORD dwParam2)
{
	INT nRet = NR_OK;
	switch (nMsg)
	{
	case NL_SYS_NOTIFY_FUNCTION:
		g_fnNotifySys = (PFN_NOTIFY_SYS)dwParam1;
		break;
	default:
		nRet = NR_ERR;
		break;
	}

	return nRet;
}

EXTERN_C INT WINAPI webbrowser2_ProcessNotifyLib (INT nMsg, DWORD dwParam1, DWORD dwParam2)
{
#ifndef __E_STATIC_LIB
	if(nMsg == NL_GET_CMD_FUNC_NAMES)
		return (INT) g_CmdNames;
	else if(nMsg == NL_GET_NOTIFY_LIB_FUNC_NAME)
		return (INT) "webbrowser2_ProcessNotifyLib";
	else if(nMsg == NL_GET_DEPENDENT_LIBS)
		return NULL;
#endif
	return ProcessNotifyLib(nMsg, dwParam1, dwParam2);
}
/////////////////////////////////////////////////////////////////////////////
#ifndef __E_STATIC_LIB
//////////// 库定义开始
static LIB_INFO s_LibInfo =
{
/*Lib Format Ver*/		LIB_FORMAT_VER,		// 保留未用。

// 本支持库的GUID串：
// guid: {5014D8FA-6DCA-40b6-8FA6-26D8183666EB}
#define		LI_LIB_GUID_STR	"F600363078DE49c5B10AF62C7A13B37E"
/*guid str*/			_T (LI_LIB_GUID_STR),

/*m_nMajorVersion*/		3,
/*m_nMinorVersion*/		0,

//!!!	注意：凡是增删或更改了命令、窗口单元、数据类型、帮助信息等，只要对帮助
//!!! 文件生成会产生影响，都必须升级版本号，而不能只修改BuildNumber。
//!!!   改动后尽量升级版本号!!!
/*m_nBuildNumber*/		3,	// 1: 2.5;  2: 2.5补遗版; 3: 3.0版
		// 构建版本号，无需对此版本号作任何处理。
		//   本版本号仅用作区分相同正式版本号的库（譬如仅仅修改了几个 BUG）。
		// 任何公布过给用户使用的版本其此版本号都应该不一样。
		//   赋值时应该顺序递增。

/*m_nRqSysMajorVer*/		3,
/*m_nRqSysMinorVer*/		6,
/*m_nRqSysKrnlLibMajorVer*/	3,
/*m_nRqSysKrnlLibMinorVer*/	7,

/*name*/				_T ("WEB浏览器"),
/*lang*/				1,
/*explain*/				_WT("本支持库封装了WEB 浏览器控件。"),
/*dwState*/				_LIB_OS(__OS_WIN),

//支持库的作者信息
/*szAuthor*/	_WT("云外归鸟"),
/*szZipCode*/	NULL,
/*szAddress*/	NULL,
/*szPhoto*/		_WT("8888888"),
/*szFax*/		_WT("8888888"),
/*szEmail*/		_WT("catboygo@163.com"),
/*szHomePage*/	_WT("http://www.ermayina.org/"),
/*szOther*/		_WT("祝您一帆风顺，心想事成！"),

/*type count*/			sizeof (s_DataType) / sizeof (s_DataType[0]),
/*PLIB_DATA_TYPE_INFO*/	s_DataType,

/*CategoryCount*/ 0,	// 加了类别需加此值。
/*category*/_WT("\0"	// 类别说明表每项为一字符串,前四位数字表示图象索引号(从1开始,0无).
				"\0"),
/*CmdCount*/				sizeof (s_CmdInfo) / sizeof (s_CmdInfo [0]),
/*BeginCmd*/				s_CmdInfo,
/*m_pCmdsFunc*/             s_RunFunc,
/*pfnRunAddInFn*/			NULL,
/*szzAddInFnInfo*/			NULL,

/*pfnNotify*/				webbrowser2_ProcessNotifyLib,

/*pfnRunSuperTemplate*/		NULL,
/*szzSuperTemplateInfo*/	NULL,

/*nLibConstCount*/			sizeof (s_ConstInfo) / sizeof (s_ConstInfo [0]),
/*pLibConst*/				s_ConstInfo,

/*szzDependFiles*/			NULL,
};

PLIB_INFO WINAPI GetNewInf ()
{
	return &s_LibInfo;
}

#endif	

