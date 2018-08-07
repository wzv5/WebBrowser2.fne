// ViewHtml.cpp : implementation file
//

#include "stdafx.h"
#include "WebBrowser2.h"
#include "ViewHtml.h"
#include <MsHtmcid.h> 

#include <AFXPRIV.H>
#include "krnllib.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#define	WU_GET_WND_PTR			(WM_APP + 2)

INT WINAPI NotifySys (INT nMsg, DWORD dwParam1, DWORD dwParam2 = 0);

#include "untshare.cpp"
#include "fnshare.h"
static const IID DIID_HTMLDocumentEvents2=
{ 0x3050F613, 0x98B5, 0x11cf, { 0xbb, 0x82, 0x00, 0xaa, 0x00, 0xbd, 0xce, 0x0b } };

/////////////////////////////////////////////////////////////////////////////
// CViewHtml

IMPLEMENT_DYNCREATE(CViewHtml, CHtmlView)

CViewHtml::CViewHtml()
{
	//{{AFX_DATA_INIT(CViewHtml)
		// NOTE: the ClassWizard will add member initialization here
	m_dwCookie=0;
	m_bIsEvenConn=FALSE;
	pDoc2=NULL;
	m_bEditMode=FALSE;
	//}}AFX_DATA_INIT
	 EnableAutomation();
}

CViewHtml::~CViewHtml()
{

	
	if(pDoc2)
	{
		if(m_bIsEvenConn)
		{
			AfxConnectionUnadvise(pDoc2, 
  				DIID_HTMLDocumentEvents2 , 
  				GetIDispatch(FALSE),  
  				FALSE, 
 				m_dwCookie );
		}
		pDoc2->Release ();
	}


}

void CViewHtml::DoDataExchange(CDataExchange* pDX)
{
	CHtmlView::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CViewHtml)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CViewHtml, CHtmlView)
	//{{AFX_MSG_MAP(CViewHtml)
		ON_MESSAGE(WU_GET_WND_PTR, OnGetWndPtr)
	ON_WM_ERASEBKGND()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

BEGIN_EVENTSINK_MAP(CViewHtml, CHtmlView)
    //{{AFX_EVENTSINK_MAP(CViewHtml)
	ON_EVENT(CViewHtml, 59648, 270 /* FileDownload */, OnFileDownload, VTS_PBOOL)
	ON_EVENT(CViewHtml, 59648, 265 /* WindowSetTop */, OnWindowSetTop, VTS_I4)
	ON_EVENT(CViewHtml, 59648, 267 /* WindowSetHeight */, OnWindowSetHeight, VTS_I4)
	ON_EVENT(CViewHtml, 59648, 264 /* WindowSetLeft */, OnWindowSetLeft, VTS_I4)
	ON_EVENT(CViewHtml, 59648, 266 /* WindowSetWidth */, OnWindowSetWidth, VTS_I4)
	ON_EVENT(CViewHtml, 59648, 262 /* WindowSetResizable */, OnWindowSetResizable, VTS_BOOL)
	ON_EVENT(CViewHtml, 59648, 263 /* WindowClosing */, OnWindowClosing, VTS_BOOL VTS_PBOOL)

	//}}AFX_EVENTSINK_MAP
END_EVENTSINK_MAP()

BEGIN_DISPATCH_MAP(CViewHtml, CHtmlView)
	DISP_FUNCTION_ID(CViewHtml, "oncontextmenu", 0x000003ff, OnHtmlContextMenu, VT_BOOL, VTS_DISPATCH)
	DISP_FUNCTION_ID(CViewHtml, "onclick", DISPID_HTMLDOCUMENTEVENTS_ONCLICK, OnHtmlOnclick, VT_BOOL, VTS_DISPATCH)
	DISP_FUNCTION_ID(CViewHtml, "oncontrolselect", 0x0000040c, OnHtmlOnclick, VT_BOOL, VTS_DISPATCH)
END_DISPATCH_MAP()
/////////////////////////////////////////////////////////////////////////////
// CViewHtml diagnostics

#ifdef _DEBUG
void CViewHtml::AssertValid() const
{
	CHtmlView::AssertValid();
}

void CViewHtml::Dump(CDumpContext& dc) const
{
	CHtmlView::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CViewHtml message handlers

LRESULT CViewHtml::OnGetWndPtr(WPARAM wparam, LPARAM lparam)
{
	return (LRESULT)this;//这样才能收TAB等按键消息
}



void CViewHtml::PostNcDestroy() 
{
	// TODO: Add your specialized code here and/or call the base class
	
	CHtmlView::PostNcDestroy();
	NotifySys (NRS_UNIT_DESTROIED, m_dwWinFormID, m_dwUnitID);
//	delete this;
}

void CViewHtml::OnBeforeNavigate2(LPCTSTR lpszURL, DWORD nFlags, LPCTSTR lpszTargetFrameName, CByteArray& baPostedData, LPCTSTR lpszHeaders, BOOL* pbCancel) 
{
	// TODO: Add your specialized code here and/or call the base class

	EVENT_NOTIFY2 event (m_dwWinFormID, m_dwUnitID, 0);
		event.m_nArgCount = 7;


		event.m_arg[0].m_inf.m_ppText =(char **)(&lpszURL);
		event.m_arg[0].m_dwState=EAV_IS_POINTER;

		event.m_arg[1].m_inf.m_int= nFlags;
		//event.m_arg[1].m_dwState=EAV_IS_POINTER;

		event.m_arg[2].m_inf.m_ppText = (char **)(&lpszTargetFrameName);
		event.m_arg[2].m_dwState=EAV_IS_POINTER;


		event.m_arg[3].m_inf.m_int= (int)baPostedData.GetData();
		//event.m_arg[3].m_dwState=EAV_IS_POINTER;
		event.m_arg[4].m_inf.m_int= baPostedData.GetSize();
		//event.m_arg[3].m_dwState=EAV_IS_POINTER;


		event.m_arg[5].m_inf.m_ppText = (char **)&lpszHeaders;
		event.m_arg[5].m_dwState=EAV_IS_POINTER;

		event.m_arg[6].m_inf.m_pBool = pbCancel;
	//	event.m_arg[6].m_dwState=EAV_IS_POINTER;

	
		NotifySys (NRS_EVENT_NOTIFY2, (DWORD)&event);
/*		nDataSize=*(LPINT)((*pp)+sizeof (INT));
		if(nDataSize>0)
		{
			baPostedData.RemoveAll();
			CMemFile file;
			file.Attach ((*pp)+sizeof (INT) * 2,nDataSize);
			CArchive ar (&file, CArchive::load);
			baPostedData.Serialize(ar);
			AfxMessageBox((LPTSTR)baPostedData.GetData());
		}*/
	//	NotifySys (NRS_MFREE, (DWORD)*event.m_arg[5].m_inf.m_ppText);

		
	CHtmlView::OnBeforeNavigate2(lpszURL, nFlags,	lpszTargetFrameName, baPostedData, lpszHeaders, pbCancel);
}

void CViewHtml::OnCommandStateChange(long nCommand, BOOL bEnable) 
{
	// TODO: Add your specialized code here and/or call the base class
	EVENT_NOTIFY2 event (m_dwWinFormID, m_dwUnitID, 9);
		event.m_nArgCount = 2;
		event.m_arg[0].m_inf.m_int =nCommand;
		event.m_arg[1].m_inf.m_bool =bEnable !=0;
		NotifySys (NRS_EVENT_NOTIFY2, (DWORD)&event);	

	CHtmlView::OnCommandStateChange(nCommand, bEnable);
}

void CViewHtml::OnDocumentComplete(LPCTSTR lpszURL) 
{
	// TODO: Add your specialized code here and/or call the base class

	if(!m_bIsEvenConn)
	{
		pDoc2 =(IHTMLDocument2*)this->GetHtmlDocument();
		if(pDoc2)
		{

			m_bIsEvenConn = AfxConnectionAdvise( 
				pDoc2,  //可连接对象的接口指针		
				DIID_HTMLDocumentEvents2, //连接接口ID
				GetIDispatch(FALSE), //把内嵌的IDispatch实现类的一个对象实例m_xDispatch传了出去
				FALSE,   //donod addref
				&m_dwCookie );  //cookie to break connection later...
		}
		if(m_bEditMode)
			ExecHTMCommand(IDM_EDITMODE);
	}
	
	EVENT_NOTIFY2 event (m_dwWinFormID, m_dwUnitID, 6);
		event.m_nArgCount = 1;
		event.m_arg[0].m_inf.m_ppText =(char **)(&lpszURL);
		event.m_arg[0].m_dwState=EAV_IS_POINTER;
		NotifySys (NRS_EVENT_NOTIFY2, (DWORD)&event);	

	CHtmlView::OnDocumentComplete(lpszURL);

//	if(this->GetLeft()!=0)
//		this->SetLeft (0);
//	if(this->GetTop()!=0)
//		this->SetTop (0);

/*	CWnd* p=GetWindow (GW_CHILD);
	if(p)	
	{
		CRect rect;
		GetClientRect(rect);
		p->MoveWindow(&rect);
		p=p->GetWindow (GW_CHILD);
		if(p)
		{
			p->MoveWindow(&rect);
			p=p->GetWindow (GW_CHILD);
			if(p)
			{
				p->MoveWindow(&rect);
				//p->InvalidateRect(&rect);
				//p->UpdateWindow();
			}
		}
	
	}*/
	//this->UpdateWindow();
}

void CViewHtml::OnDownloadBegin() 
{
	// TODO: Add your specialized code here and/or call the base class
	NotifySys (NRS_EVENT_NOTIFY2, (DWORD)&EVENT_NOTIFY2 (m_dwWinFormID, m_dwUnitID, 3));

	CHtmlView::OnDownloadBegin();
}

void CViewHtml::OnDownloadComplete() 
{
	// TODO: Add your specialized code here and/or call the base class
	NotifySys (NRS_EVENT_NOTIFY2, (DWORD)&EVENT_NOTIFY2 (m_dwWinFormID, m_dwUnitID, 5));	
	CHtmlView::OnDownloadComplete();

}

void CViewHtml::OnProgressChange(long nProgress, long nProgressMax) 
{
	// TODO: Add your specialized code here and/or call the base class
	EVENT_NOTIFY2 event (m_dwWinFormID, m_dwUnitID, 4);
		event.m_nArgCount = 2;
		event.m_arg[0].m_inf.m_int =nProgress;
		event.m_arg[1].m_inf.m_int =nProgressMax;
		NotifySys (NRS_EVENT_NOTIFY2, (DWORD)&event);	
		
	CHtmlView::OnProgressChange(nProgress, nProgressMax);
}

void CViewHtml::OnStatusTextChange(LPCTSTR lpszText) 
{
	// TODO: Add your specialized code here and/or call the base class
	EVENT_NOTIFY2 event (m_dwWinFormID, m_dwUnitID, 7);
		event.m_nArgCount = 1;
		event.m_arg[0].m_inf.m_ppText =(char **)(&lpszText);
		event.m_arg[0].m_dwState=EAV_IS_POINTER;
		NotifySys (NRS_EVENT_NOTIFY2, (DWORD)&event);	

	CHtmlView::OnStatusTextChange(lpszText);
}

void CViewHtml::OnTitleChange(LPCTSTR lpszText) 
{
	// TODO: Add your specialized code here and/or call the base class
	EVENT_NOTIFY2 event (m_dwWinFormID, m_dwUnitID, 8);
		event.m_nArgCount = 1;
		event.m_arg[0].m_inf.m_ppText =(char **)(&lpszText);
		event.m_arg[0].m_dwState=EAV_IS_POINTER;
		NotifySys (NRS_EVENT_NOTIFY2, (DWORD)&event);	
		
	CHtmlView::OnTitleChange(lpszText);
}

void CViewHtml::OnNavigateComplete2(LPCTSTR strURL) 
{
	// TODO: Add your specialized code here and/or call the base class
	EVENT_NOTIFY2 event (m_dwWinFormID, m_dwUnitID, 2);
		event.m_nArgCount = 1;
		event.m_arg[0].m_inf.m_ppText =(char **)(&strURL);
		event.m_arg[0].m_dwState=EAV_IS_POINTER;
		NotifySys (NRS_EVENT_NOTIFY2, (DWORD)&event);	

	CHtmlView::OnNavigateComplete2(strURL);
}

void CViewHtml::OnNewWindow2(LPDISPATCH* ppDisp, BOOL* Cancel) 
{
	// TODO: Add your specialized code here and/or call the base class
	EVENT_NOTIFY2 event (m_dwWinFormID, m_dwUnitID, 1);
		event.m_nArgCount = 2;


		event.m_arg[0].m_inf.m_ppCompoundData = (void **)&ppDisp;
		event.m_arg[0].m_dwState=EAV_IS_POINTER;

		event.m_arg[1].m_inf.m_pBool = Cancel;

		NotifySys (NRS_EVENT_NOTIFY2, (DWORD)&event);

			
	CHtmlView::OnNewWindow2(ppDisp, Cancel);
}



void CViewHtml::OnQuit() 
{
	// TODO: Add your specialized code here and/or call the base class
	
	CHtmlView::OnQuit();
}

void CViewHtml::OnFileDownload(BOOL FAR* Cancel) 
{
	// TODO: Add your specialized code here and/or call the base class
	//AfxMessageBox("FileDownload");

}
void CViewHtml::OnWindowSetTop(long Top) 
{
	// TODO: Add your specialized code here and/or call the base class
	EVENT_NOTIFY2 event (m_dwWinFormID, m_dwUnitID, 10);
		event.m_nArgCount = 1;
		event.m_arg[0].m_inf.m_int =Top;

		NotifySys (NRS_EVENT_NOTIFY2, (DWORD)&event);

}
void CViewHtml::OnWindowSetLeft(long Left) 
{
	// TODO: Add your control notification handler code here
	this->RedrawWindow ();
	EVENT_NOTIFY2 event (m_dwWinFormID, m_dwUnitID, 11);
		event.m_nArgCount = 1;
		event.m_arg[0].m_inf.m_int =Left;


		NotifySys (NRS_EVENT_NOTIFY2, (DWORD)&event);
}

void CViewHtml::OnWindowSetHeight(long Height) 
{
	// TODO: Add your control notification handler code here
	EVENT_NOTIFY2 event (m_dwWinFormID, m_dwUnitID, 12);
		event.m_nArgCount = 1;
		event.m_arg[0].m_inf.m_int =Height;

		NotifySys (NRS_EVENT_NOTIFY2, (DWORD)&event);
}


void CViewHtml::OnWindowSetWidth(long Width) 
{
	// TODO: Add your control notification handler code here
	EVENT_NOTIFY2 event (m_dwWinFormID, m_dwUnitID, 13);
		event.m_nArgCount = 1;
		event.m_arg[0].m_inf.m_int =Width;

		NotifySys (NRS_EVENT_NOTIFY2, (DWORD)&event);

}
void CViewHtml::OnWindowSetResizable(BOOL Resizable) 
{
	// TODO: Add your control notification handler code here
	EVENT_NOTIFY2 event (m_dwWinFormID, m_dwUnitID, 14);
		event.m_nArgCount = 1;
		event.m_arg[0].m_inf.m_bool=Resizable!=0;

		NotifySys (NRS_EVENT_NOTIFY2, (DWORD)&event);

}
void CViewHtml::OnWindowClosing(BOOL IsChildWindow, BOOL FAR* Cancel) 
{
	// TODO: Add your control notification handler code here
	EVENT_NOTIFY2 event (m_dwWinFormID, m_dwUnitID, 15);
		event.m_nArgCount = 2;
		event.m_arg[0].m_inf.m_bool=IsChildWindow!=0;
		event.m_arg[1].m_inf.m_pBool = Cancel;
		if(*event.m_arg[1].m_inf.m_pBool)
			*Cancel=-1;

		NotifySys (NRS_EVENT_NOTIFY2, (DWORD)&event);
}
BOOL CViewHtml::OnHtmlContextMenu(IHTMLEventObj *pEvtObj)
{
	EVENT_NOTIFY2 event (m_dwWinFormID, m_dwUnitID, 17);
		event.m_nArgCount = 1;

		LPDISPATCH** ppDisp=(LPDISPATCH**)&pEvtObj;
		event.m_arg[0].m_inf.m_ppCompoundData = (void **)&ppDisp;
		event.m_arg[0].m_dwState=EAV_IS_POINTER;


	if (NotifySys (NRS_EVENT_NOTIFY2, (DWORD)&event) != 0 &&
			event.m_blHasRetVal == TRUE &&
			event.m_infRetData.m_bool== 0)

			return FALSE;
	
	return TRUE;
}

BOOL CViewHtml::OnHtmlOnclick(IHTMLEventObj *pEvtObj)
{
	EVENT_NOTIFY2 event (m_dwWinFormID, m_dwUnitID, 16);
		event.m_nArgCount = 1;

		LPDISPATCH** ppDisp=(LPDISPATCH**)&pEvtObj;
		event.m_arg[0].m_inf.m_ppCompoundData = (void **)&ppDisp;
		event.m_arg[0].m_dwState=EAV_IS_POINTER;

	if (NotifySys (NRS_EVENT_NOTIFY2, (DWORD)&event) != 0 &&
			event.m_blHasRetVal == TRUE &&
			event.m_infRetData.m_bool== 0)

			return FALSE;
	
	return TRUE;
}

//////////////////////////////////

CString CViewHtml::GetFontName()
{
    ASSERT(m_pBrowserApp != NULL);

	CString retVal;
    VARIANT result;
	CString strURL("FontName");
	BSTR bstr = strURL.AllocSysString();

	VariantInit(&result);

	IHTMLDocument2* pDoc =(IHTMLDocument2*)this->GetHtmlDocument();

	if(pDoc)
	{
		pDoc->queryCommandValue(bstr, &result);

		if(result.vt == VT_BSTR)
		{
			retVal=result.bstrVal;
		}
		else
			retVal.Empty ();
		pDoc->Release ();
	}
	else
		retVal.Empty ();

	VariantClear(&result);
	::SysFreeString(bstr);
    return retVal;
}

BOOL CViewHtml::GetEditMode()
{
    VARIANT result;
	CString strURL("EditMode");
	BSTR bstr = strURL.AllocSysString();

	VariantInit(&result);
	IHTMLDocument2* pDoc =(IHTMLDocument2*)this->GetHtmlDocument();
	if(pDoc)
	{
		pDoc->queryCommandValue(bstr, &result);
	
		if(result.vt == VT_BOOL)
		{
			return (result.boolVal !=NULL);
		}
		else
			return FALSE;
		pDoc->Release ();

	}
	VariantClear(&result);
	::SysFreeString(bstr);
    return FALSE;
}

void CViewHtml::SetFontName(LPCTSTR lpszfn)//execCommand
{
    VARIANT_BOOL result,v_bshowUI;
    VARIANT v_Value;
	CString strURL("FontName");
	BSTR bstr = strURL.AllocSysString();
	strURL=lpszfn;
	v_Value.vt=VT_BSTR;
	v_Value.bstrVal= strURL.AllocSysString();
	v_bshowUI=FALSE;
	IHTMLDocument2* pDoc =(IHTMLDocument2*)this->GetHtmlDocument();
	if(pDoc)
	{
		pDoc->execCommand (bstr,v_bshowUI,v_Value,&result);
		pDoc->Release ();
	}
	VariantClear(&v_Value);
	::SysFreeString(bstr);
}

INT CViewHtml::GetFontValue(UINT nCode)
{
    ASSERT(m_pBrowserApp != NULL);

	INT retVal=0;
    VARIANT result;
	CString strURL;
	switch (nCode)
	{
	case 0:
		strURL="FontSize";
		break;
	case 1:
		strURL="ForeColor";
		break;
	case 2:
		strURL="BackColor";
		break;

	}

	BSTR bstr = strURL.AllocSysString();

	VariantInit(&result);

	IHTMLDocument2* pDoc =(IHTMLDocument2*)this->GetHtmlDocument();
	if(pDoc)
	{
		pDoc->queryCommandValue(bstr, &result);

		if(result.vt == VT_I4)
		{
			retVal=result.lVal;
		}
		pDoc->Release ();

	}
	VariantClear(&result);
	::SysFreeString(bstr);

    return retVal;
}

void CViewHtml::SetFontValue(UINT nCode, INT nValue)
{

    VARIANT_BOOL result,v_bshowUI;
    VARIANT v_Value;

	CString strURL;
	switch (nCode)
	{
	case 0:
		strURL="FontSize";
		break;
	case 1:
		strURL="ForeColor";
		break;
	case 2:
		strURL="BackColor";
		break;

	}

	BSTR bstr = strURL.AllocSysString();

	v_Value.vt=VT_I4;
	v_Value.lVal= nValue;
	v_bshowUI=FALSE;
	IHTMLDocument2* pDoc =(IHTMLDocument2*)this->GetHtmlDocument();
	if(pDoc)
	{
		pDoc->execCommand (bstr,v_bshowUI,v_Value,&result);
		pDoc->Release ();
	}
	VariantClear(&v_Value);
	::SysFreeString(bstr);
}

BOOL CViewHtml::GetFontStyle(UINT nCode)
{
    VARIANT result;
	CString strURL;
	switch (nCode)
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
	case 6:
		strURL="OverWrite";
		break;

	}

	BSTR bstr = strURL.AllocSysString();
	VariantInit(&result);
	IHTMLDocument2* pDoc =(IHTMLDocument2*)this->GetHtmlDocument();
	if(pDoc)
	{
		pDoc->queryCommandValue(bstr, &result);
	
		if(result.vt == VT_BOOL)
		{
			return (result.boolVal != NULL);
		}
		else
			return FALSE;
		pDoc->Release ();
	}
	VariantClear(&result);
	::SysFreeString(bstr);
    return FALSE;
}

BOOL CViewHtml::TheCommandIsEnabled(UINT nCode)
{
    VARIANT_BOOL result;
	CString strURL;
	switch (nCode)
	{
	case 0:
		strURL="Paste";
		break;
	case 1:
		strURL="Copy";
		break;
	case 2:
		strURL="Cut";
		break;
	case 3:
		strURL="Redo";
		break;
	case 4:
		strURL="Undo";
		break;

	}

	BSTR bstr = strURL.AllocSysString();
	IHTMLDocument2* pDoc =(IHTMLDocument2*)this->GetHtmlDocument();

	if(pDoc)
	{
		pDoc->queryCommandEnabled(bstr, &result);
		pDoc->Release ();
		::SysFreeString(bstr);
		return (result !=NULL);
	}

	::SysFreeString(bstr);
    return FALSE;
}

BOOL CViewHtml::execCommand(CString sCmd)
{
    VARIANT_BOOL result,v_bshowUI;
    VARIANT v_Value;

	BSTR bstr = sCmd.AllocSysString();
	v_bshowUI=FALSE;
	VariantInit(&v_Value);
	IHTMLDocument2* pDoc =(IHTMLDocument2*)this->GetHtmlDocument();
	if(pDoc)
	{
		pDoc->execCommand (bstr,v_bshowUI,v_Value,&result);
		pDoc->Release ();
		VariantClear(&v_Value);
		::SysFreeString(bstr);
		return (result !=NULL);
	}
	VariantClear(&v_Value);
	::SysFreeString(bstr);
	return FALSE;
}

INT CViewHtml::ExecHTMCommand(INT nCID)
{
	CWnd* pChildWind=GetWindow (GW_CHILD);
	if(pChildWind)	
	{
		pChildWind=pChildWind->GetWindow (GW_CHILD);
		if(pChildWind)
		{
			pChildWind=pChildWind->GetWindow (GW_CHILD);
			if(pChildWind)
			{

				WPARAM wParam = MAKELONG(nCID, 1);//WM_COMMAND, wParam, (LPARAM)
				return pChildWind->SendMessage(WM_COMMAND, wParam, (LPARAM)pChildWind->GetSafeHwnd ());

			}
		}
	
	}

	return NULL;
}


#ifndef __E_STATIC_LIB
//////////////////////////////////////////////////////////////////////////////////////
// !!! 此处的定义顺序绝对不可改变
static EVENT_ARG_INFO2 s_HtmlViewerArgInfo [] =
{

//****** 跳转地址0
	{
/*name*/	_WT("地址"),
/*explain*/	_WT("为事件发生的URL地址名称。"),
/*state*/	EAS_BY_REF,
/*m_dtDataType*/ SDT_TEXT,
	},
//****** 标志1
	{
/*name*/	_WT("标记"),
/*explain*/	_WT("浏览网页相关的标记"),
/*state*/	(1<<0),//EAS_BY_REF,
/*m_dtDataType*/ SDT_INT,
	},
//****** 目标窗口名2
	{
/*name*/	_WT("目标窗口名称"),
/*explain*/	_WT("为将要跳转到的目标窗口名称。"),
/*state*/	EAS_BY_REF,
/*m_dtDataType*/ SDT_TEXT,
	},
//****** 投送的数据3
	{
/*name*/	_WT("投送的数据指针"),
/*explain*/	_WT("为POST命令投送的数据，用“指针到字节集（）”取出。"),
/*state*/	 (1<<0),//EAS_BY_REF,,
/*m_dtDataType*/ SDT_INT,
	},
//****** 投送的数据4
	{
/*name*/	_WT("投送的数据长度"),
/*explain*/	_WT("为POST命令投送的数据长度，用“指针到字节集（）”取出。"),
/*state*/	 (1<<0),//EAS_BY_REF,,
/*m_dtDataType*/ SDT_INT,
	},
//****** 头文本5
	{
/*name*/	_WT("类型说明"),
/*explain*/	_WT("为POST命令投送数据的编码类型。"),
/*state*/	EAS_BY_REF,
/*m_dtDataType*/ SDT_TEXT,
	},
//****** 当前网址6
	{
/*name*/	_WT("取消跳转"),
/*explain*/	_WT("赋值真不允许跳转，赋值假或不赋值值允许跳转。"),
/*state*/	EAS_BY_REF,
/*m_dtDataType*/ SDT_BOOL,
	},
//****** 当前网址7
	{
/*name*/	_WT("浏览器对象"),
/*explain*/	_WT("为该对象赋值将要打开的新浏览器窗口对象。"),
/*state*/	EAS_BY_REF,
/*m_dtDataType*/ DTP_COM_OBJECT,
	},
//****** 当前网址8
	{
/*name*/	_WT("取消打开"),
/*explain*/	_WT("赋值真不允许打开，赋值假或不赋值值允许打开。"),
/*state*/	EAS_BY_REF,
/*m_dtDataType*/ SDT_BOOL,
	},
//****** 载入进度改变9
	{
/*name*/	_WT("进度值"),
/*explain*/	_WT("参数值指示当前文档已经被载入的进度值"),
/*state*/	(1<<0),
/*m_dtDataType*/ SDT_INT,
	},
//****** 载入进度改变10
	{
/*name*/	_WT("最大进度值"),
/*explain*/	_WT("参数值指示当前文档已经被载入的最大进度值"),
/*state*/	(1<<0),
/*m_dtDataType*/ SDT_INT,
	},
//****** 头文本11
	{
/*name*/	_WT("状态文本"),
/*explain*/	_WT(""),
/*state*/	EAS_BY_REF,
/*m_dtDataType*/ SDT_TEXT,
	},
//****** 头文本12
	{
/*name*/	_WT("标题文本"),
/*explain*/	_WT(""),
/*state*/	EAS_BY_REF,
/*m_dtDataType*/ SDT_TEXT,
	},
//****** 命令状态被改变13
	{
/*name*/	_WT("命令"),
/*explain*/	_WT("参数值指示允许状态被改变的命令类型，为以下常量值之一："
		"0: #前进； 1: #后退"),
/*state*/	(1<<0),
/*state*/	SDT_INT,
	}, {
/*name*/	_WT("是否被允许"),
/*explain*/	_WT("参数值指示该命令当前是否被允许"),
/*state*/	(1<<0),
/*m_dtDataType*/ SDT_BOOL,
	},//****** 命令状态被改变15
	{
/*name*/	_WT("窗口顶边"),
/*explain*/	_WT(""),
/*state*/	(1<<0),
/*state*/	SDT_INT,
	},//****** 命令状态被改变16
	{
/*name*/	_WT("窗口左边"),
/*explain*/	_WT(""),
/*state*/	(1<<0),
/*state*/	SDT_INT,
	},//****** 命令状态被改变17
	{
/*name*/	_WT("窗口高度"),
/*explain*/	_WT(""),
/*state*/	(1<<0),
/*state*/	SDT_INT,
	},//****** 命令状态被改变18
	{
/*name*/	_WT("窗口宽度"),
/*explain*/	_WT(""),
/*state*/	(1<<0),
/*state*/	SDT_INT,
	},//****** 命令状态被改变19
	{
/*name*/	_WT("是否可调"),
/*explain*/	_WT("参数值指示边框是否可调"),
/*state*/	(1<<0),
/*m_dtDataType*/ SDT_BOOL,
	},//****** 命令状态被改变20
	{
/*name*/	_WT("是否子窗口"),
/*explain*/	_WT(""),
/*state*/	(1<<0),
/*state*/	SDT_BOOL,
	},//****** 命令状态被改变21
	{
/*name*/	_WT("取消关闭"),
/*explain*/	_WT(""),
/*state*/	EAS_BY_REF,
/*m_dtDataType*/ SDT_BOOL,
	},//****** 命令状态被改变22
	{
/*name*/	_WT("事件对象"),
/*explain*/	_WT("该对象包含有相关事件的参数，比如菜单的弹出位置和发生事件的对象"),
/*state*/	EAS_BY_REF,
/*m_dtDataType*/ DTP_COM_OBJECT,
	}
};

// !!! 此处的定义顺序绝对不可改变，主默认信息放在首位。
EVENT_INFO2 g_HtmlViewerEvent [] =
{
	{
	_WT("即将跳转"),
	_WT("在浏览器即将跳转到另一个页面之前产生此事件，"
		"在参数一中读取“跳转地址”即可得知即将跳转到的地址"),
/*m_dwState*/			EV_IS_VER2|_EVENT_OS(__OS_WIN),
/*m_nArgCount*/			7,
/*m_pBeginArgInfo*/		s_HtmlViewerArgInfo,
/*m_dtRetDataType*/		 _SDT_NULL,
	}, 
	{
	_WT("即将打开新窗口"),
	_WT("在浏览器即将打开新窗口浏览另一个页面之前产生此事件，第一个参数对象型代入“取浏览器对象（）”方法里，即可打开新窗口，参数二决定是否打开"),
/*m_dwState*/			EV_IS_VER2|_EVENT_OS(__OS_WIN),
/*m_nArgCount*/			2,
/*m_pBeginArgInfo*/		&s_HtmlViewerArgInfo[7],
/*m_dtRetDataType*/		 _SDT_NULL,
	}, {
	_WT("跳转完毕"),//2
	_WT("当浏览器已跳转到另一个页面之后产生此事件，在事件处理子程序参数一中读取“地址”参数即可得知已就绪文档的地址"),
/*m_dwState*/			EV_IS_VER2|_EVENT_OS(__OS_WIN),
/*m_nArgCount*/			1,
/*m_pBeginArgInfo*/		s_HtmlViewerArgInfo,
/*m_dtRetDataType*/		 _SDT_NULL,
	}, {
	_WT("载入开始"),//3
	_WT("本事件在“即将跳转”事件之后触发，表示浏览器已开始载入将要显示的文档"),
/*m_dwState*/			EV_IS_VER2|_EVENT_OS(__OS_WIN),
/*m_nArgCount*/			0,
/*m_pBeginArgInfo*/		NULL,
/*m_dtRetDataType*/		 _SDT_NULL,
	}, {
	_WT("载入进度改变"),//4
	_WT("在浏览器载入文档的过程中，每当文档被载入一部分即触发本事件，用作通知载入进度"),
/*m_dwState*/			EV_IS_VER2|_EVENT_OS(__OS_WIN),
/*m_nArgCount*/			2,
/*m_pBeginArgInfo*/		&s_HtmlViewerArgInfo [9],
/*m_dtRetDataType*/		 _SDT_NULL,
	}, {
	_WT("载入完毕"),//5
	_WT("当将要显示在浏览器内的文档被载入完毕后触发本事件"),
/*m_dwState*/			EV_IS_VER2|_EVENT_OS(__OS_WIN),
/*m_nArgCount*/			0,
/*m_pBeginArgInfo*/		NULL,
/*m_dtRetDataType*/		 _SDT_NULL,
	}, {
	_WT("已就绪"),//6
	_WT("当浏览器已经将所需显示的文档处理完毕后发送本事件，在事件处理子程序参数一中读取“地址”参数即可得知已就绪文档的地址"),
/*m_dwState*/			EV_IS_VER2|_EVENT_OS(__OS_WIN),
/*m_nArgCount*/			1,
/*m_pBeginArgInfo*/		s_HtmlViewerArgInfo,
/*m_dtRetDataType*/		 _SDT_NULL,
	}, {
	_WT("状态文本被改变"),//7
	_WT("当浏览器的状态条文本被改变后发送本事件，在事件处理子程序参数一中读取“状态文本”参数即可得知内容"),
/*m_dwState*/			EV_IS_VER2|_EVENT_OS(__OS_WIN),
/*m_nArgCount*/			1,
/*m_pBeginArgInfo*/		&s_HtmlViewerArgInfo [11],
/*m_dtRetDataType*/		 _SDT_NULL,
	}, {
	_WT("标题被改变"),//8
	_WT("当浏览器的标题文本被改变后发送本事件，在事件处理子程序参数一中读取“标题文本”参数即可得知内容"),
/*m_dwState*/			EV_IS_VER2|_EVENT_OS(__OS_WIN),
/*m_nArgCount*/			1,
/*m_pBeginArgInfo*/		&s_HtmlViewerArgInfo [12],
/*m_dtRetDataType*/		 _SDT_NULL,
	}, {
	_WT("命令状态被改变"),//9
	_WT("当“前进”、“后退”等命令的允许状态被改变后发送此事件，"
		"用户程序应该根据状态值允许或禁止对应的按钮或菜单项。"),
/*m_dwState*/			EV_IS_VER2|_EVENT_OS(__OS_WIN),
/*m_nArgCount*/			2,
/*m_pBeginArgInfo*/		&s_HtmlViewerArgInfo [13],
/*m_dtRetDataType*/		 _SDT_NULL,
	},{
	_WT("置窗口顶边"),//10
	_WT("被网页脚本改变窗口顶边"),
/*m_dwState*/			EV_IS_VER2|_EVENT_OS(__OS_WIN),
/*m_nArgCount*/			1,
/*m_pBeginArgInfo*/		&s_HtmlViewerArgInfo [15],
/*m_dtRetDataType*/		 _SDT_NULL,
	},{
	_WT("置窗口左边"),//11
	_WT("被网页脚本改变窗口左边"),
/*m_dwState*/			EV_IS_VER2|_EVENT_OS(__OS_WIN),
/*m_nArgCount*/			1,
/*m_pBeginArgInfo*/		&s_HtmlViewerArgInfo [16],
/*m_dtRetDataType*/		 _SDT_NULL,
	},{
	_WT("置窗口高度"),//12
	_WT("被网页脚本改变窗口高度"),
/*m_dwState*/			EV_IS_VER2|_EVENT_OS(__OS_WIN),
/*m_nArgCount*/			1,
/*m_pBeginArgInfo*/		&s_HtmlViewerArgInfo [17],
/*m_dtRetDataType*/		 _SDT_NULL,
	},{
	_WT("置窗口宽度"),//13
	_WT("被网页脚本改变窗口宽度"),
/*m_dwState*/			EV_IS_VER2|_EVENT_OS(__OS_WIN),
/*m_nArgCount*/			1,
/*m_pBeginArgInfo*/		&s_HtmlViewerArgInfo [18],
/*m_dtRetDataType*/		 _SDT_NULL,
	},{
	_WT("置窗口边框可调"),//14
	_WT("被网页脚本改变窗口风格"),
/*m_dwState*/			EV_IS_VER2|_EVENT_OS(__OS_WIN),
/*m_nArgCount*/			1,
/*m_pBeginArgInfo*/		&s_HtmlViewerArgInfo [19],
/*m_dtRetDataType*/		 _SDT_NULL,
	},{
	_WT("窗口被关闭"),//15
	_WT("窗口被网页脚本关闭"),
/*m_dwState*/			EV_IS_VER2|_EVENT_OS(__OS_WIN),
/*m_nArgCount*/			2,
/*m_pBeginArgInfo*/		&s_HtmlViewerArgInfo [20],
/*m_dtRetDataType*/		 _SDT_NULL,
	},{
	_WT("网页被单击"),//16
	_WT("当网页被单击时发生本事件。处理本事件的子程序如果返回假，则取消本事件。本事件需要IE 5.5以上版本才会产生"),
/*m_dwState*/			EV_IS_VER2|_EVENT_OS(__OS_WIN),
/*m_nArgCount*/			1,
/*m_pBeginArgInfo*/		&s_HtmlViewerArgInfo [22],
/*m_dtRetDataType*/		SDT_BOOL,
	},{
	_WT("弹出右键菜单"),//17
	_WT("弹出网页的右键菜单。处理本事件的子程序如果返回假，则取消本事件。本事件需要IE 5.5以上版本才会产生"),
/*m_dwState*/			EV_RETURN_BOOL|EV_IS_VER2|_EVENT_OS(__OS_WIN),
/*m_nArgCount*/			1,
/*m_pBeginArgInfo*/		&s_HtmlViewerArgInfo [22],
/*m_dtRetDataType*/		SDT_BOOL,
	},
};
INT g_HtmlViewerEventCount = sizeof (g_HtmlViewerEvent) / sizeof (g_HtmlViewerEvent [0]);

// 注意顺序不可改变!!!
UNIT_PROPERTY g_HtmlViewerProperty [] =
{
	FIXED_WIN_UNIT_PROPERTY,
	{
	/*m_szName*/			_WT("边框"),
	/*m_szEgName*/			_WT("Style"),
	/*m_szExplain*/			_WT(""),
	/*m_shtType*/			UD_PICK_INT,
	/*m_wState*/			_PROP_OS(__OS_WIN),
	/*m_szzPickStr*/		_WT("无边框\0凹入式\0凸出式\0浅凹入式\0镜框式\0单线边框式\0\0"),
	},
	{
	/*m_szName*/			_WT("静默"),
	/*m_szEgName*/			_WT("Silent"),
	/*m_szExplain*/			_WT("则浏览过程中不允许浏览器显示自己的对话框。包括脚本错误提示"),
	/*m_shtType*/			UD_BOOL,
	/*m_wState*/			_PROP_OS(__OS_WIN),
	/*m_szzPickStr*/		NULL,
	}, 	
	{
	/*m_szName*/			_WT("离线浏览"),
	/*m_szEgName*/			_WT("Offline"),
	/*m_szExplain*/			_WT("指定浏览器是否从缓存里面读取超文本页面数据"),
	/*m_shtType*/			UD_BOOL,
	/*m_wState*/			_PROP_OS(__OS_WIN),
	/*m_szzPickStr*/		NULL,
	}, 	
	{
	/*m_szName*/			_WT("可拖放"),
	/*m_szEgName*/			_WT("RegisterAsDropTarget"),
	/*m_szExplain*/			_WT("浏览器注册为可以拖放的对象，可以拖入网址直接打开。"),
	/*m_shtType*/			UD_BOOL,
	/*m_wState*/			_PROP_OS(__OS_WIN),
	/*m_szzPickStr*/		NULL,
	}, 	
	{
	/*m_szName*/			_WT("顶层浏览器"),
	/*m_szEgName*/			_WT("RegisterAsBrowser"),
	/*m_szExplain*/			_WT("指浏览器注册为顶层浏览器"),
	/*m_shtType*/			UD_BOOL,
	/*m_wState*/			_PROP_OS(__OS_WIN),
	/*m_szzPickStr*/		NULL,
	}, 	
	{
	/*m_szName*/			_WT("地址栏"),
	/*m_szEgName*/			_WT("AddressBar"),
	/*m_szExplain*/			_WT("浏览器是否有地址栏"),
	/*m_shtType*/			UD_BOOL,
	/*m_wState*/			_PROP_OS(__OS_WIN)|UW_ONLY_READ,
	/*m_szzPickStr*/		NULL,
	}, 	
	{
	/*m_szName*/			_WT("全屏幕"),
	/*m_szEgName*/			_WT("FullScreen"),
	/*m_szExplain*/			_WT("浏览器是否全屏幕"),
	/*m_shtType*/			UD_BOOL,
	/*m_wState*/			_PROP_OS(__OS_WIN)|UW_ONLY_READ,
	/*m_szzPickStr*/		NULL,
	}, 	
	{
	/*m_szName*/			_WT("菜单栏"),
	/*m_szEgName*/			_WT("MenuBar"),
	/*m_szExplain*/			_WT("浏览器是否有菜单栏"),
	/*m_shtType*/			UD_BOOL,
	/*m_wState*/			_PROP_OS(__OS_WIN)|UW_ONLY_READ,
	/*m_szzPickStr*/		NULL,
	}, 	
	{
	/*m_szName*/			_WT("可调边框"),
	/*m_szEgName*/			_WT("Resizble"),
	/*m_szExplain*/			_WT("浏览器为可调边框窗口"),
	/*m_shtType*/			UD_BOOL,
	/*m_wState*/			_PROP_OS(__OS_WIN)|UW_ONLY_READ|UW_IS_HIDED,
	/*m_szzPickStr*/		NULL,
	}, 	
	{
	/*m_szName*/			_WT("状态栏"),
	/*m_szEgName*/			_WT("StatusBar"),
	/*m_szExplain*/			_WT("浏览器是否有状态栏"),
	/*m_shtType*/			UD_BOOL,
	/*m_wState*/			_PROP_OS(__OS_WIN)|UW_ONLY_READ,
	/*m_szzPickStr*/		NULL,
	}, 	
	{
	/*m_szName*/			_WT("影院模式"),
	/*m_szEgName*/			_WT("TheaterMode"),
	/*m_szExplain*/			_WT("浏览器为影院模式"),
	/*m_shtType*/			UD_BOOL,
	/*m_wState*/			_PROP_OS(__OS_WIN)|UW_ONLY_READ,
	/*m_szzPickStr*/		NULL,
	}, 	
	{
	/*m_szName*/			_WT("工具栏"),
	/*m_szEgName*/			_WT("ToolBar"),
	/*m_szExplain*/			_WT("浏览器是否有工具栏"),
	/*m_shtType*/			UD_BOOL,
	/*m_wState*/			_PROP_OS(__OS_WIN)|UW_ONLY_READ,
	/*m_szzPickStr*/		NULL,
	}, 	
	{
	/*m_szName*/			_WT("是否可视"),
	/*m_szEgName*/			_WT("Visible"),
	/*m_szExplain*/			_WT("浏览器是否可视"),
	/*m_shtType*/			UD_BOOL,
	/*m_wState*/			_PROP_OS(__OS_WIN)|UW_ONLY_READ,
	/*m_szzPickStr*/		NULL,
	}, 	
	{
	/*m_szName*/			_WT("繁忙"),
	/*m_szEgName*/			_WT("Busy"),
	/*m_szExplain*/			_WT("浏览器是否繁忙状态中"),
	/*m_shtType*/			UD_BOOL,
	/*m_wState*/			_PROP_OS(__OS_WIN)|UW_ONLY_READ,
	/*m_szzPickStr*/		NULL,
	}, 	
	{
	/*m_szName*/			_WT("是否顶层容器"),
	/*m_szEgName*/			_WT("TopLevelContainer"),
	/*m_szExplain*/			_WT("浏览器是否为顶层容器"),
	/*m_shtType*/			UD_BOOL,
	/*m_wState*/			_PROP_OS(__OS_WIN)|UW_ONLY_READ,
	/*m_szzPickStr*/		NULL,
	}, 	
	{
	/*m_szName*/			_WT("就绪状态"),
	/*m_szEgName*/			_WT("ReadyState"),
	/*m_szExplain*/			_WT("获取浏览器就绪状态："
		"0. 未初始化、1.  正在下载、2.  已下载、3.  通信中、4.  完成"),
	/*m_shtType*/			UD_INT,
	/*m_wState*/			_PROP_OS(__OS_WIN)|UW_ONLY_READ,
	/*m_szzPickStr*/		NULL,
	}, {
	/*m_szName*/			_WT("程序全路径"),
	/*m_szEgName*/			_WT("FullName"),
	/*m_szExplain*/			_WT("返回应用程序的全路径"),
	/*m_shtType*/			UD_TEXT,
	/*m_wState*/			_PROP_OS(__OS_WIN)|UW_ONLY_READ,
	/*m_szzPickStr*/		NULL,
	}, {
	/*m_szName*/			_WT("地址"),
	/*m_szEgName*/			_WT("LocationURL"),
	/*m_szExplain*/			_WT("返回当前浏览器的网页地址"),
	/*m_shtType*/			UD_TEXT,
	/*m_wState*/			_PROP_OS(__OS_WIN)|UW_ONLY_READ,
	/*m_szzPickStr*/		NULL,
	}, {
	/*m_szName*/			_WT("标题"),
	/*m_szEgName*/			_WT("Caption"),
	/*m_szExplain*/			_WT("用作在运行时提供浏览器的当前标题文本"),
	/*m_shtType*/			UD_TEXT,
	/*m_wState*/			_PROP_OS(__OS_WIN)|UW_ONLY_READ,
	/*m_szzPickStr*/		NULL,
	}, {
	/*m_szName*/			_WT("文档类型"),/////19
	/*m_szEgName*/			_WT("Type"),
	/*m_szExplain*/			_WT("返回浏览器中现行文档的类型文本"),
	/*m_shtType*/			UD_TEXT,
	/*m_wState*/			_PROP_OS(__OS_WIN)|UW_ONLY_READ,
	/*m_szzPickStr*/		NULL,
	}, {
	/*m_szName*/			_WT("编辑模式"),//20
	/*m_szEgName*/			_WT("EditMode"),
	/*m_szExplain*/			_WT("设置和获取浏览框是否为编辑模式。"),
	/*m_shtType*/			UD_BOOL,
	/*m_wState*/			_PROP_OS(__OS_WIN)|UW_CANNOT_INIT,
	/*m_szzPickStr*/		NULL,
	},{
	/*m_szName*/			_WT("字体名称"),//21
	/*m_szEgName*/			_WT("FontName"),
	/*m_szExplain*/			_WT("在编辑模式下，设置和取得被选择文本的字体名称。如果字体混合选中,则取得空文本。"),
	/*m_shtType*/			UD_TEXT,
	/*m_wState*/			_PROP_OS(__OS_WIN)|UW_CANNOT_INIT |UW_HAS_INDENT,
	/*m_szzPickStr*/		NULL,
	},{
	/*m_szName*/			_WT("字体大小"),//22
	/*m_szEgName*/			_WT("FontSize"),
	/*m_szExplain*/			_WT("在编辑模式下，设置和取得被选择文本的字体大小。为网页字号。如果字体混合选中，则取得零。"),
	/*m_shtType*/			UD_INT,
	/*m_wState*/			_PROP_OS(__OS_WIN)|UW_CANNOT_INIT |UW_HAS_INDENT,
	/*m_szzPickStr*/		NULL,
	},{
	/*m_szName*/			_WT("文本颜色"),//23
	/*m_szEgName*/			_WT("ForeColor"),
	/*m_szExplain*/			_WT("在编辑模式下，设置和取得被选择文本的颜色值。如果字体混合选中,则取得零。"),
	/*m_shtType*/			UD_INT,
	/*m_wState*/			_PROP_OS(__OS_WIN)|UW_CANNOT_INIT |UW_HAS_INDENT,
	/*m_szzPickStr*/		NULL,
	},{
	/*m_szName*/			_WT("背景颜色"),//24
	/*m_szEgName*/			_WT("BackColor"),
	/*m_szExplain*/			_WT("在编辑模式下，设置和取得被选择文本的背景颜色值。如果字体混合选中,则取得零。"),
	/*m_shtType*/			UD_INT,
	/*m_wState*/			_PROP_OS(__OS_WIN)|UW_CANNOT_INIT |UW_HAS_INDENT,
	/*m_szzPickStr*/		NULL,
	},{
	/*m_szName*/			_WT("粗体"),//25
	/*m_szEgName*/			_WT("Bold"),
	/*m_szExplain*/			_WT("在编辑模式下，被选择文本是否为粗体。如果字体混合选中,则以第一个字符为准。"),
	/*m_shtType*/			UD_BOOL,
	/*m_wState*/			_PROP_OS(__OS_WIN)|UW_ONLY_READ |UW_CANNOT_INIT |UW_HAS_INDENT,
	/*m_szzPickStr*/		NULL,
	},{
	/*m_szName*/			_WT("斜体"),//26
	/*m_szEgName*/			_WT("Italic"),
	/*m_szExplain*/			_WT("在编辑模式下，被选择文本是否为斜体。如果字体混合选中,则以第一个字符为准。"),
	/*m_shtType*/			UD_BOOL,
	/*m_wState*/			_PROP_OS(__OS_WIN)|UW_ONLY_READ |UW_CANNOT_INIT |UW_HAS_INDENT,
	/*m_szzPickStr*/		NULL,
	},{
	/*m_szName*/			_WT("下划线"),//27
	/*m_szEgName*/			_WT("Underline"),
	/*m_szExplain*/			_WT("在编辑模式下，被选择文本是否为下划线。如果字体混合选中,则以第一个字符为准。"),
	/*m_shtType*/			UD_BOOL,
	/*m_wState*/			_PROP_OS(__OS_WIN)|UW_ONLY_READ |UW_CANNOT_INIT |UW_HAS_INDENT,
	/*m_szzPickStr*/		NULL,
	},{
	/*m_szName*/			_WT("删除线"),//28
	/*m_szEgName*/			_WT("StrikeThrough"),
	/*m_szExplain*/			_WT("在编辑模式下，被选择文本是否为删除线。如果字体混合选中,则以第一个字符为准。"),
	/*m_shtType*/			UD_BOOL,
	/*m_wState*/			_PROP_OS(__OS_WIN)|UW_ONLY_READ |UW_CANNOT_INIT |UW_HAS_INDENT,
	/*m_szzPickStr*/		NULL,
	},{
	/*m_szName*/			_WT("上标"),//29
	/*m_szEgName*/			_WT("Superscript"),
	/*m_szExplain*/			_WT("在编辑模式下，被选择文本是否为上标。如果字体混合选中,则以第一个字符为准。"),
	/*m_shtType*/			UD_BOOL,
	/*m_wState*/			_PROP_OS(__OS_WIN)|UW_ONLY_READ |UW_CANNOT_INIT |UW_HAS_INDENT,
	/*m_szzPickStr*/		NULL,
	},{
	/*m_szName*/			_WT("下标"),//30
	/*m_szEgName*/			_WT("Subscript"),
	/*m_szExplain*/			_WT("在编辑模式下，被选择文本是否为下标。如果字体混合选中,则以第一个字符为准。"),
	/*m_shtType*/			UD_BOOL,
	/*m_wState*/			_PROP_OS(__OS_WIN)|UW_ONLY_READ |UW_CANNOT_INIT |UW_HAS_INDENT,
	/*m_szzPickStr*/		NULL,
	},{
	/*m_szName*/			_WT("覆盖状态"),//31
	/*m_szEgName*/			_WT("OverWrite"),
	/*m_szExplain*/			_WT("在编辑模式下，网页编辑框是否为输入覆盖状态。"),
	/*m_shtType*/			UD_BOOL,
	/*m_wState*/			_PROP_OS(__OS_WIN)|UW_ONLY_READ |UW_CANNOT_INIT |UW_HAS_INDENT,
	/*m_szzPickStr*/		NULL,
	},{
	/*m_szName*/			_WT("可否粘贴"),//32
	/*m_szEgName*/			_WT("Paste"),
	/*m_szExplain*/			_WT("指示该命令是否可用。"),
	/*m_shtType*/			UD_BOOL,
	/*m_wState*/			_PROP_OS(__OS_WIN)|UW_ONLY_READ |UW_CANNOT_INIT |UW_HAS_INDENT,
	/*m_szzPickStr*/		NULL,
	},{
	/*m_szName*/			_WT("可否复制"),//33
	/*m_szEgName*/			_WT("Copy"),
	/*m_szExplain*/			_WT("指示该命令是否可用。"),
	/*m_shtType*/			UD_BOOL,
	/*m_wState*/			_PROP_OS(__OS_WIN)|UW_ONLY_READ |UW_CANNOT_INIT |UW_HAS_INDENT,
	/*m_szzPickStr*/		NULL,
	},{
	/*m_szName*/			_WT("可否剪切"),//34
	/*m_szEgName*/			_WT("Cut"),
	/*m_szExplain*/			_WT("指示该命令是否可用。"),
	/*m_shtType*/			UD_BOOL,
	/*m_wState*/			_PROP_OS(__OS_WIN)|UW_ONLY_READ |UW_CANNOT_INIT |UW_HAS_INDENT,
	/*m_szzPickStr*/		NULL,
	},{
	/*m_szName*/			_WT("可否重做"),//35
	/*m_szEgName*/			_WT("Redo"),
	/*m_szExplain*/			_WT("指示该命令是否可用。"),
	/*m_shtType*/			UD_BOOL,
	/*m_wState*/			_PROP_OS(__OS_WIN)|UW_ONLY_READ |UW_CANNOT_INIT |UW_HAS_INDENT,
	/*m_szzPickStr*/		NULL,
	},{
	/*m_szName*/			_WT("可否撤消"),//36
	/*m_szEgName*/			_WT("Undo"),
	/*m_szExplain*/			_WT("指示该命令是否可用。"),
	/*m_shtType*/			UD_BOOL,
	/*m_wState*/			_PROP_OS(__OS_WIN)|UW_ONLY_READ |UW_CANNOT_INIT |UW_HAS_INDENT,
	/*m_szzPickStr*/		NULL,
	},

 		

};

INT g_HtmlViewerPropertyCount = sizeof (g_HtmlViewerProperty) / sizeof (g_HtmlViewerProperty [0]);


#endif


void CPIHtmlViewer::init ()
{
	CPropertyInfo::init ();

    m_blOffline = FALSE;
    m_blSilent = FALSE;
    m_blRegisterAsDropTarget = TRUE;
    m_blRegisterAsBrowser = FALSE;

}

BOOL CPIHtmlViewer::Serialize (CArchive& ar)
{
	if (CPropertyInfo::Serialize (ar) == FALSE)
		return FALSE;

	TRY
	{
		if (ar.IsLoading () == TRUE)
		{
			DWORD dwUnitDataVer;
			ar >> dwUnitDataVer;
			if (dwUnitDataVer > CUR_UNIT_VER)
				return FALSE;
			ar >>  m_Style >> m_blSilent >> m_blOffline >> m_blRegisterAsDropTarget >>m_blRegisterAsBrowser ;
		}
		else
		{
			ar << (DWORD)CUR_UNIT_VER;
			ar <<  m_Style << m_blSilent << m_blOffline << m_blRegisterAsDropTarget << m_blRegisterAsBrowser ;
		}

		
		return TRUE;
	}
	END_TRY

	return FALSE;
}

/////////////////////////////////////////////////////////////////////////////

HUNIT WINAPI Create_HtmlViewer (LPBYTE pAllData, INT nAllDataSize,
		DWORD dwStyle, HWND hParentWnd, UINT uID, HMENU hMenu, INT x, INT y, INT cx, INT cy,
		DWORD dwWinFormID, DWORD dwUnitID, HWND hDesignWnd, BOOL blInDesignMode)
{

	CViewHtml* pUnit=new CViewHtml;

	pUnit->m_dwWinFormID = dwWinFormID;
	pUnit->m_dwUnitID = dwUnitID;
	pUnit->m_blInDesignMode = blInDesignMode;
	if (pUnit->m_info.LoadData (pAllData, nAllDataSize) == FALSE)
	{
		delete pUnit;
		return NULL;
	}

	RECT rect={x,y,x+cx,y+cy};

	if(pUnit->Create (NULL,NULL,dwStyle,rect,CWnd::FromHandle(hParentWnd),uID))
	{
		ChangeBorder(pUnit,pUnit->m_info.m_Style);
		pUnit->SetSilent (pUnit->m_info.m_blSilent);
		pUnit->SetOffline (pUnit->m_info.m_blOffline);
		pUnit->SetRegisterAsDropTarget (pUnit->m_info.m_blRegisterAsDropTarget);
		pUnit->SetRegisterAsBrowser(pUnit->m_info.m_blRegisterAsBrowser);


		return (HUNIT)pUnit;

	}
	return NULL;
}

BOOL WINAPI NotifyPropertyChanged_HtmlViewer (HUNIT hUnit, INT nPropertyIndex,
											  PUNIT_PROPERTY_VALUE pPropertyVaule,
											  LPTSTR* ppszTipText)
{
	ASSERT (hUnit != NULL);
	if (hUnit == NULL)  return FALSE;
	CViewHtml* pUnit = (CViewHtml*)hUnit;
	ASSERT (pUnit->GetSafeHwnd () != NULL);

	if (ppszTipText != NULL)
		*ppszTipText = NULL;

// 注意此处的属性索引必须与属性表完全一致。
	switch (nPropertyIndex)
	{
	case 0:
		pUnit->m_info.m_Style=pPropertyVaule->m_int;
		ChangeBorder(pUnit,pUnit->m_info.m_Style);
		break;
	case 1:
		pUnit->m_info.m_blSilent = pPropertyVaule->m_bool;
		pUnit->SetSilent (pUnit->m_info.m_blSilent? -1 : 0);
		break;
	case 2:
		pUnit->m_info.m_blOffline = pPropertyVaule->m_bool;
		pUnit->SetOffline (pUnit->m_info.m_blOffline? -1 : 0);
		break;
	case 3:
		pUnit->m_info.m_blRegisterAsDropTarget = pPropertyVaule->m_bool;
		pUnit->SetRegisterAsDropTarget (pUnit->m_info.m_blRegisterAsDropTarget? -1 : 0);
		break;
	case 4:
		pUnit->m_info.m_blRegisterAsBrowser = pPropertyVaule->m_bool;
		pUnit->SetRegisterAsBrowser(pUnit->m_info.m_blRegisterAsBrowser? -1 : 0);
		break;
	case 20:
		pUnit->m_bEditMode=pPropertyVaule->m_bool;
		if(pUnit->m_bEditMode)
			pUnit->ExecHTMCommand(IDM_EDITMODE);
		else
			pUnit->ExecHTMCommand(IDM_BROWSEMODE);
		break;
	case 21:
	    pUnit->SetFontName(pPropertyVaule->m_szText);
		break;
	case 22:
	    pUnit->SetFontValue(0,pPropertyVaule->m_int);//SetFontValue
		break;
	case 23:
	    pUnit->SetFontValue(1,pPropertyVaule->m_int);
		break;
	case 24:
	    pUnit->SetFontValue(2,pPropertyVaule->m_int);
		break;
    default:
        ASSERT (FALSE);
        break;
	}

	return FALSE;
}

// !! GetFontValue对于运行时可能被用户操作改变（不考虑直接调用API函数）的属性，在运行时必须取其现行实际值。
BOOL WINAPI GetPropertyData_HtmlViewer (HUNIT hUnit, INT nPropertyIndex,
										PUNIT_PROPERTY_VALUE pPropertyVaule)
{
	ASSERT (hUnit != NULL);
	if (hUnit == NULL)  return FALSE;
	CViewHtml* pUnit = (CViewHtml*)hUnit;
	ASSERT (pUnit->GetSafeHwnd () != NULL);

// 注意此处的属性索引必须与属性表完全一致。
	switch (nPropertyIndex)
	{
	case 0:
		pPropertyVaule->m_int = pUnit->m_info.m_Style;

		break;
	case 1:
		pUnit->m_info.m_blSilent=pUnit->GetSilent ()!=0 ;
		pPropertyVaule->m_bool=pUnit->m_info.m_blSilent ;
		break;
	case 2:
		pUnit->m_info.m_blOffline=pUnit->GetOffline ()!=0 ;
		pPropertyVaule->m_bool=pUnit->m_info.m_blOffline;

		break;
	case 3:
		pUnit->m_info.m_blRegisterAsDropTarget=pUnit->GetRegisterAsDropTarget()!=0 ;
		pPropertyVaule->m_bool=pUnit->m_info.m_blRegisterAsDropTarget;

		break;
	case 4:
		pUnit->m_info.m_blRegisterAsBrowser=pUnit->GetRegisterAsBrowser()!=0 ;
		pPropertyVaule->m_bool=pUnit->m_info.m_blRegisterAsBrowser;

		break;
	case 5:
		pPropertyVaule->m_bool=pUnit->GetAddressBar()!=0 ;
		break;
	case 6:
		pPropertyVaule->m_bool=pUnit->GetFullScreen()!=0 ;

		break;
	case 7:

		pPropertyVaule->m_bool =pUnit->GetMenuBar()!=0 ;

		break;
	case 8:
		//pPropertyVaule->m_bool=pUnit->GetResizble;

		break;
	case 9:
		pPropertyVaule->m_bool=pUnit->GetStatusBar () !=0 ;
		break;
	case 10:
		pPropertyVaule->m_bool=pUnit->GetTheaterMode ()!=0 ;

		break;
	case 11:
		pPropertyVaule->m_bool=pUnit->GetToolBar()!=0 ;

		break;
	case 12:
		pPropertyVaule->m_bool=pUnit->GetVisible () !=0 ;
		break;
	case 13:
		pPropertyVaule->m_bool=pUnit->GetBusy () !=0 ;

		break;
	case 14:
		pPropertyVaule->m_bool=pUnit->GetTopLevelContainer()!=0 ;

		break;
	case 15:
		pPropertyVaule->m_int=pUnit->GetReadyState () ;

		break;
	case 16:
		pUnit->m_strFullName=pUnit->GetFullName();
		pPropertyVaule->m_szText=(LPTSTR)(LPCSTR)pUnit->m_strFullName ;
		break;
	case 17:
		pUnit->m_strLocationURL=pUnit->GetLocationURL();
		pPropertyVaule->m_szText=(LPTSTR)(LPCSTR)pUnit->m_strLocationURL ;
		break;
	case 18:
		pUnit->m_strLocationName=pUnit->GetLocationName();
		pPropertyVaule->m_szText=(LPTSTR)(LPCSTR)pUnit->m_strLocationName ;
		break;
	case 19:
		pUnit->m_strType=pUnit->GetType ();
		pPropertyVaule->m_szText=(LPTSTR)(LPCSTR)pUnit->m_strType ;
		break;
	case 20:

		pPropertyVaule->m_bool = pUnit->GetEditMode ();

		break;
	case 21:
	    pPropertyVaule->m_szText = CloneTextData ((LPTSTR)(LPCTSTR)pUnit->GetFontName());
		break;
	case 22:
	    pPropertyVaule->m_int=pUnit->GetFontValue(0);//SetFontValue
		break;
	case 23:
	    pPropertyVaule->m_int=pUnit->GetFontValue(1);
		break;
	case 24:
	    pPropertyVaule->m_int=pUnit->GetFontValue(2);//GetFontStyle(UINT nCode)
		break;
	case 25:
	    pPropertyVaule->m_bool=pUnit->GetFontStyle(0);
		break;
	case 26:
	    pPropertyVaule->m_bool=pUnit->GetFontStyle(1);
		break;
	case 27:
	    pPropertyVaule->m_bool=pUnit->GetFontStyle(2);
		break;
	case 28:
	    pPropertyVaule->m_bool=pUnit->GetFontStyle(3);
		break;
	case 29:
	    pPropertyVaule->m_bool=pUnit->GetFontStyle(4);
		break;
	case 30:
	    pPropertyVaule->m_bool=pUnit->GetFontStyle(5);
		break;
	case 31:
	    pPropertyVaule->m_bool=pUnit->GetFontStyle(6);//TheCommandIsEnabled
		break;
	case 32:
	    pPropertyVaule->m_bool=pUnit->TheCommandIsEnabled(0);
		break;
	case 33:
	    pPropertyVaule->m_bool=pUnit->TheCommandIsEnabled(1);
		break;
	case 34:
	    pPropertyVaule->m_bool=pUnit->TheCommandIsEnabled(2);
		break;
	case 35:
	    pPropertyVaule->m_bool=pUnit->TheCommandIsEnabled(3);
		break;
	case 36:
	    pPropertyVaule->m_bool=pUnit->TheCommandIsEnabled(4);
		break;
	default:
		ASSERT (FALSE);
		return FALSE;
	}

	return TRUE;
}

HGLOBAL WINAPI GetAllPropertyData_HtmlViewer (HUNIT hUnit)
{
	ASSERT (hUnit != NULL);
	return ((CViewHtml*)hUnit)->m_info.SaveData ();
}

BOOL WINAPI Property_Update_HtmlViewer(
        HUNIT hUnit,
        INT nPropertyIndex)
{
	if (hUnit == NULL)  return FALSE;
	CViewHtml* pUnit = (CViewHtml*)hUnit;

	return TRUE;
}


extern "C"
PFN_INTERFACE WINAPI webbrowser2_GetInterface_WebBrowser (INT nInterfaceNO)
{
	return nInterfaceNO == ITF_CREATE_UNIT ? (PFN_INTERFACE)Create_HtmlViewer :
	nInterfaceNO == ITF_NOTIFY_PROPERTY_CHANGED ? (PFN_INTERFACE)NotifyPropertyChanged_HtmlViewer :
	nInterfaceNO == ITF_GET_ALL_PROPERTY_DATA ? (PFN_INTERFACE)GetAllPropertyData_HtmlViewer :
	nInterfaceNO == ITF_GET_PROPERTY_DATA ? (PFN_INTERFACE)GetPropertyData_HtmlViewer :
	nInterfaceNO == ITF_PROPERTY_UPDATE_UI ? (PFN_INTERFACE)Property_Update_HtmlViewer :
	NULL;
}





BOOL CViewHtml::OnEraseBkgnd(CDC* pDC) 
{
	// TODO: Add your message handler code here and/or call default
	return TRUE;
	//return CHtmlView::OnEraseBkgnd(pDC);
}


