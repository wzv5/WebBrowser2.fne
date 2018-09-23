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
	ON_EVENT(CViewHtml, 59648, 273, OnNewWindow3, VTS_PDISPATCH VTS_PBOOL VTS_I4 VTS_BSTR VTS_BSTR)

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
	return (LRESULT)this;//����������TAB�Ȱ�����Ϣ
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
				pDoc2,  //�����Ӷ���Ľӿ�ָ��		
				DIID_HTMLDocumentEvents2, //���ӽӿ�ID
				GetIDispatch(FALSE), //����Ƕ��IDispatchʵ�����һ������ʵ��m_xDispatch���˳�ȥ
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

void CViewHtml::OnNewWindow3(LPDISPATCH* ppDisp, BOOL* Cancel, long dwFlags, LPCTSTR bstrUrlContext, LPCTSTR bstrUrl)
{
	// TODO: Add your control notification handler code here
	EVENT_NOTIFY2 event(m_dwWinFormID, m_dwUnitID, 18);
	event.m_nArgCount = 5;

	event.m_arg[0].m_inf.m_ppCompoundData = (void **)&ppDisp;
	event.m_arg[0].m_dwState = EAV_IS_POINTER;

	event.m_arg[1].m_inf.m_pBool = Cancel;

	event.m_arg[2].m_inf.m_int = dwFlags;

	event.m_arg[3].m_inf.m_pText = (char *)(&bstrUrlContext);
	event.m_arg[3].m_dwState = EAV_IS_POINTER;

	event.m_arg[4].m_inf.m_pText = (char *)(&bstrUrl);
	event.m_arg[4].m_dwState = EAV_IS_POINTER;

	NotifySys(NRS_EVENT_NOTIFY2, (DWORD)&event);
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
// !!! �˴��Ķ���˳����Բ��ɸı�
static EVENT_ARG_INFO2 s_HtmlViewerArgInfo [] =
{

//****** ��ת��ַ0
	{
/*name*/	_WT("��ַ"),
/*explain*/	_WT("Ϊ�¼�������URL��ַ���ơ�"),
/*state*/	EAS_BY_REF,
/*m_dtDataType*/ SDT_TEXT,
	},
//****** ��־1
	{
/*name*/	_WT("���"),
/*explain*/	_WT("�����ҳ��صı��"),
/*state*/	(1<<0),//EAS_BY_REF,
/*m_dtDataType*/ SDT_INT,
	},
//****** Ŀ�괰����2
	{
/*name*/	_WT("Ŀ�괰������"),
/*explain*/	_WT("Ϊ��Ҫ��ת����Ŀ�괰�����ơ�"),
/*state*/	EAS_BY_REF,
/*m_dtDataType*/ SDT_TEXT,
	},
//****** Ͷ�͵�����3
	{
/*name*/	_WT("Ͷ�͵�����ָ��"),
/*explain*/	_WT("ΪPOST����Ͷ�͵����ݣ��á�ָ�뵽�ֽڼ�������ȡ����"),
/*state*/	 (1<<0),//EAS_BY_REF,,
/*m_dtDataType*/ SDT_INT,
	},
//****** Ͷ�͵�����4
	{
/*name*/	_WT("Ͷ�͵����ݳ���"),
/*explain*/	_WT("ΪPOST����Ͷ�͵����ݳ��ȣ��á�ָ�뵽�ֽڼ�������ȡ����"),
/*state*/	 (1<<0),//EAS_BY_REF,,
/*m_dtDataType*/ SDT_INT,
	},
//****** ͷ�ı�5
	{
/*name*/	_WT("����˵��"),
/*explain*/	_WT("ΪPOST����Ͷ�����ݵı������͡�"),
/*state*/	EAS_BY_REF,
/*m_dtDataType*/ SDT_TEXT,
	},
//****** ��ǰ��ַ6
	{
/*name*/	_WT("ȡ����ת"),
/*explain*/	_WT("��ֵ�治������ת����ֵ�ٻ򲻸�ֵֵ������ת��"),
/*state*/	EAS_BY_REF,
/*m_dtDataType*/ SDT_BOOL,
	},
//****** ��ǰ��ַ7
	{
/*name*/	_WT("���������"),
/*explain*/	_WT("Ϊ�ö���ֵ��Ҫ�򿪵�����������ڶ���"),
/*state*/	EAS_BY_REF,
/*m_dtDataType*/ DTP_COM_OBJECT,
	},
//****** ��ǰ��ַ8
	{
/*name*/	_WT("ȡ����"),
/*explain*/	_WT("��ֵ�治����򿪣���ֵ�ٻ򲻸�ֵֵ����򿪡�"),
/*state*/	EAS_BY_REF,
/*m_dtDataType*/ SDT_BOOL,
	},
//****** ������ȸı�9
	{
/*name*/	_WT("����ֵ"),
/*explain*/	_WT("����ֵָʾ��ǰ�ĵ��Ѿ�������Ľ���ֵ"),
/*state*/	(1<<0),
/*m_dtDataType*/ SDT_INT,
	},
//****** ������ȸı�10
	{
/*name*/	_WT("������ֵ"),
/*explain*/	_WT("����ֵָʾ��ǰ�ĵ��Ѿ��������������ֵ"),
/*state*/	(1<<0),
/*m_dtDataType*/ SDT_INT,
	},
//****** ͷ�ı�11
	{
/*name*/	_WT("״̬�ı�"),
/*explain*/	_WT(""),
/*state*/	EAS_BY_REF,
/*m_dtDataType*/ SDT_TEXT,
	},
//****** ͷ�ı�12
	{
/*name*/	_WT("�����ı�"),
/*explain*/	_WT(""),
/*state*/	EAS_BY_REF,
/*m_dtDataType*/ SDT_TEXT,
	},
//****** ����״̬���ı�13
	{
/*name*/	_WT("����"),
/*explain*/	_WT("����ֵָʾ����״̬���ı���������ͣ�Ϊ���³���ֵ֮һ��"
		"0: #ǰ���� 1: #����"),
/*state*/	(1<<0),
/*state*/	SDT_INT,
	}, {
/*name*/	_WT("�Ƿ�����"),
/*explain*/	_WT("����ֵָʾ�����ǰ�Ƿ�����"),
/*state*/	(1<<0),
/*m_dtDataType*/ SDT_BOOL,
	},//****** ����״̬���ı�15
	{
/*name*/	_WT("���ڶ���"),
/*explain*/	_WT(""),
/*state*/	(1<<0),
/*state*/	SDT_INT,
	},//****** ����״̬���ı�16
	{
/*name*/	_WT("�������"),
/*explain*/	_WT(""),
/*state*/	(1<<0),
/*state*/	SDT_INT,
	},//****** ����״̬���ı�17
	{
/*name*/	_WT("���ڸ߶�"),
/*explain*/	_WT(""),
/*state*/	(1<<0),
/*state*/	SDT_INT,
	},//****** ����״̬���ı�18
	{
/*name*/	_WT("���ڿ��"),
/*explain*/	_WT(""),
/*state*/	(1<<0),
/*state*/	SDT_INT,
	},//****** ����״̬���ı�19
	{
/*name*/	_WT("�Ƿ�ɵ�"),
/*explain*/	_WT("����ֵָʾ�߿��Ƿ�ɵ�"),
/*state*/	(1<<0),
/*m_dtDataType*/ SDT_BOOL,
	},//****** ����״̬���ı�20
	{
/*name*/	_WT("�Ƿ��Ӵ���"),
/*explain*/	_WT(""),
/*state*/	(1<<0),
/*state*/	SDT_BOOL,
	},//****** ����״̬���ı�21
	{
/*name*/	_WT("ȡ���ر�"),
/*explain*/	_WT(""),
/*state*/	EAS_BY_REF,
/*m_dtDataType*/ SDT_BOOL,
	},//****** ����״̬���ı�22
	{
/*name*/	_WT("�¼�����"),
/*explain*/	_WT("�ö������������¼��Ĳ���������˵��ĵ���λ�úͷ����¼��Ķ���"),
/*state*/	EAS_BY_REF,
/*m_dtDataType*/ DTP_COM_OBJECT,
	},
	
	//****** ���´���23
	{
		/*name*/	_WT("���������"),
		/*explain*/	_WT("Ϊ�ö���ֵ��Ҫ�򿪵�����������ڶ���"),
		/*state*/	EAS_BY_REF,
		/*m_dtDataType*/ DTP_COM_OBJECT,
	},
	//****** ���´���24
	{
		/*name*/	_WT("ȡ����"),
		/*explain*/	_WT("��ֵ�治����򿪣���ֵ�ٻ򲻸�ֵֵ����򿪡�"),
		/*state*/	EAS_BY_REF,
		/*m_dtDataType*/ SDT_BOOL,
	},
	//****** ���´���25
	{
		/*name*/	_WT("Flag"),
		/*explain*/	_WT("The flags from the NWMF enumeration that pertain to the new window."),
		/*state*/	(1 << 0),
		/*m_dtDataType*/ SDT_INT,
	},
	//****** ���´���26
	{
		/*name*/	_WT("UrlContext"),
		/*explain*/	_WT("The URL of the page that is opening the new window."),
		/*state*/	(1 << 0),
		/*m_dtDataType*/ SDT_TEXT,
	},
	//****** ���´���27
	{
		/*name*/	_WT("Url"),
		/*explain*/	_WT("The URL that is opened in the new window."),
		/*state*/	(1 << 0),
		/*m_dtDataType*/ SDT_TEXT,
	}
};

// !!! �˴��Ķ���˳����Բ��ɸı䣬��Ĭ����Ϣ������λ��
EVENT_INFO2 g_HtmlViewerEvent [] =
{
	{
	_WT("������ת"),
	_WT("�������������ת����һ��ҳ��֮ǰ�������¼���"
		"�ڲ���һ�ж�ȡ����ת��ַ�����ɵ�֪������ת���ĵ�ַ"),
/*m_dwState*/			EV_IS_VER2|_EVENT_OS(__OS_WIN),
/*m_nArgCount*/			7,
/*m_pBeginArgInfo*/		s_HtmlViewerArgInfo,
/*m_dtRetDataType*/		 _SDT_NULL,
	}, 
	{
	_WT("�������´���"),
	_WT("��������������´��������һ��ҳ��֮ǰ�������¼�����һ�����������ʹ��롰ȡ��������󣨣�����������ɴ��´��ڣ������������Ƿ��"),
/*m_dwState*/			EV_IS_VER2|_EVENT_OS(__OS_WIN),
/*m_nArgCount*/			2,
/*m_pBeginArgInfo*/		&s_HtmlViewerArgInfo[7],
/*m_dtRetDataType*/		 _SDT_NULL,
	}, {
	_WT("��ת���"),//2
	_WT("�����������ת����һ��ҳ��֮��������¼������¼������ӳ������һ�ж�ȡ����ַ���������ɵ�֪�Ѿ����ĵ��ĵ�ַ"),
/*m_dwState*/			EV_IS_VER2|_EVENT_OS(__OS_WIN),
/*m_nArgCount*/			1,
/*m_pBeginArgInfo*/		s_HtmlViewerArgInfo,
/*m_dtRetDataType*/		 _SDT_NULL,
	}, {
	_WT("���뿪ʼ"),//3
	_WT("���¼��ڡ�������ת���¼�֮�󴥷�����ʾ������ѿ�ʼ���뽫Ҫ��ʾ���ĵ�"),
/*m_dwState*/			EV_IS_VER2|_EVENT_OS(__OS_WIN),
/*m_nArgCount*/			0,
/*m_pBeginArgInfo*/		NULL,
/*m_dtRetDataType*/		 _SDT_NULL,
	}, {
	_WT("������ȸı�"),//4
	_WT("������������ĵ��Ĺ����У�ÿ���ĵ�������һ���ּ��������¼�������֪ͨ�������"),
/*m_dwState*/			EV_IS_VER2|_EVENT_OS(__OS_WIN),
/*m_nArgCount*/			2,
/*m_pBeginArgInfo*/		&s_HtmlViewerArgInfo [9],
/*m_dtRetDataType*/		 _SDT_NULL,
	}, {
	_WT("�������"),//5
	_WT("����Ҫ��ʾ��������ڵ��ĵ���������Ϻ󴥷����¼�"),
/*m_dwState*/			EV_IS_VER2|_EVENT_OS(__OS_WIN),
/*m_nArgCount*/			0,
/*m_pBeginArgInfo*/		NULL,
/*m_dtRetDataType*/		 _SDT_NULL,
	}, {
	_WT("�Ѿ���"),//6
	_WT("��������Ѿ���������ʾ���ĵ�������Ϻ��ͱ��¼������¼������ӳ������һ�ж�ȡ����ַ���������ɵ�֪�Ѿ����ĵ��ĵ�ַ"),
/*m_dwState*/			EV_IS_VER2|_EVENT_OS(__OS_WIN),
/*m_nArgCount*/			1,
/*m_pBeginArgInfo*/		s_HtmlViewerArgInfo,
/*m_dtRetDataType*/		 _SDT_NULL,
	}, {
	_WT("״̬�ı����ı�"),//7
	_WT("���������״̬���ı����ı���ͱ��¼������¼������ӳ������һ�ж�ȡ��״̬�ı����������ɵ�֪����"),
/*m_dwState*/			EV_IS_VER2|_EVENT_OS(__OS_WIN),
/*m_nArgCount*/			1,
/*m_pBeginArgInfo*/		&s_HtmlViewerArgInfo [11],
/*m_dtRetDataType*/		 _SDT_NULL,
	}, {
	_WT("���ⱻ�ı�"),//8
	_WT("��������ı����ı����ı���ͱ��¼������¼������ӳ������һ�ж�ȡ�������ı����������ɵ�֪����"),
/*m_dwState*/			EV_IS_VER2|_EVENT_OS(__OS_WIN),
/*m_nArgCount*/			1,
/*m_pBeginArgInfo*/		&s_HtmlViewerArgInfo [12],
/*m_dtRetDataType*/		 _SDT_NULL,
	}, {
	_WT("����״̬���ı�"),//9
	_WT("����ǰ�����������ˡ������������״̬���ı���ʹ��¼���"
		"�û�����Ӧ�ø���״ֵ̬������ֹ��Ӧ�İ�ť��˵��"),
/*m_dwState*/			EV_IS_VER2|_EVENT_OS(__OS_WIN),
/*m_nArgCount*/			2,
/*m_pBeginArgInfo*/		&s_HtmlViewerArgInfo [13],
/*m_dtRetDataType*/		 _SDT_NULL,
	},{
	_WT("�ô��ڶ���"),//10
	_WT("����ҳ�ű��ı䴰�ڶ���"),
/*m_dwState*/			EV_IS_VER2|_EVENT_OS(__OS_WIN),
/*m_nArgCount*/			1,
/*m_pBeginArgInfo*/		&s_HtmlViewerArgInfo [15],
/*m_dtRetDataType*/		 _SDT_NULL,
	},{
	_WT("�ô������"),//11
	_WT("����ҳ�ű��ı䴰�����"),
/*m_dwState*/			EV_IS_VER2|_EVENT_OS(__OS_WIN),
/*m_nArgCount*/			1,
/*m_pBeginArgInfo*/		&s_HtmlViewerArgInfo [16],
/*m_dtRetDataType*/		 _SDT_NULL,
	},{
	_WT("�ô��ڸ߶�"),//12
	_WT("����ҳ�ű��ı䴰�ڸ߶�"),
/*m_dwState*/			EV_IS_VER2|_EVENT_OS(__OS_WIN),
/*m_nArgCount*/			1,
/*m_pBeginArgInfo*/		&s_HtmlViewerArgInfo [17],
/*m_dtRetDataType*/		 _SDT_NULL,
	},{
	_WT("�ô��ڿ��"),//13
	_WT("����ҳ�ű��ı䴰�ڿ��"),
/*m_dwState*/			EV_IS_VER2|_EVENT_OS(__OS_WIN),
/*m_nArgCount*/			1,
/*m_pBeginArgInfo*/		&s_HtmlViewerArgInfo [18],
/*m_dtRetDataType*/		 _SDT_NULL,
	},{
	_WT("�ô��ڱ߿�ɵ�"),//14
	_WT("����ҳ�ű��ı䴰�ڷ��"),
/*m_dwState*/			EV_IS_VER2|_EVENT_OS(__OS_WIN),
/*m_nArgCount*/			1,
/*m_pBeginArgInfo*/		&s_HtmlViewerArgInfo [19],
/*m_dtRetDataType*/		 _SDT_NULL,
	},{
	_WT("���ڱ��ر�"),//15
	_WT("���ڱ���ҳ�ű��ر�"),
/*m_dwState*/			EV_IS_VER2|_EVENT_OS(__OS_WIN),
/*m_nArgCount*/			2,
/*m_pBeginArgInfo*/		&s_HtmlViewerArgInfo [20],
/*m_dtRetDataType*/		 _SDT_NULL,
	},{
	_WT("��ҳ������"),//16
	_WT("����ҳ������ʱ�������¼��������¼����ӳ���������ؼ٣���ȡ�����¼������¼���ҪIE 5.5���ϰ汾�Ż����"),
/*m_dwState*/			EV_IS_VER2|_EVENT_OS(__OS_WIN),
/*m_nArgCount*/			1,
/*m_pBeginArgInfo*/		&s_HtmlViewerArgInfo [22],
/*m_dtRetDataType*/		SDT_BOOL,
	},{
	_WT("�����Ҽ��˵�"),//17
	_WT("������ҳ���Ҽ��˵��������¼����ӳ���������ؼ٣���ȡ�����¼������¼���ҪIE 5.5���ϰ汾�Ż����"),
/*m_dwState*/			EV_RETURN_BOOL|EV_IS_VER2|_EVENT_OS(__OS_WIN),
/*m_nArgCount*/			1,
/*m_pBeginArgInfo*/		&s_HtmlViewerArgInfo [22],
/*m_dtRetDataType*/		SDT_BOOL,
	},
	{
	_WT("�������´���2"),//18
	_WT("��������������´��������һ��ҳ��֮ǰ�������¼��������´��ڵĶ�����Ϣ�������������Ƿ��"),
	/*m_dwState*/			EV_IS_VER2 | _EVENT_OS(__OS_WIN),
	/*m_nArgCount*/			5,
	/*m_pBeginArgInfo*/		&s_HtmlViewerArgInfo[23],
	/*m_dtRetDataType*/		 _SDT_NULL,
	},
};
INT g_HtmlViewerEventCount = sizeof (g_HtmlViewerEvent) / sizeof (g_HtmlViewerEvent [0]);

// ע��˳�򲻿ɸı�!!!
UNIT_PROPERTY g_HtmlViewerProperty [] =
{
	FIXED_WIN_UNIT_PROPERTY,
	{
	/*m_szName*/			_WT("�߿�"),
	/*m_szEgName*/			_WT("Style"),
	/*m_szExplain*/			_WT(""),
	/*m_shtType*/			UD_PICK_INT,
	/*m_wState*/			_PROP_OS(__OS_WIN),
	/*m_szzPickStr*/		_WT("�ޱ߿�\0����ʽ\0͹��ʽ\0ǳ����ʽ\0����ʽ\0���߱߿�ʽ\0\0"),
	},
	{
	/*m_szName*/			_WT("��Ĭ"),
	/*m_szEgName*/			_WT("Silent"),
	/*m_szExplain*/			_WT("����������в������������ʾ�Լ��ĶԻ��򡣰����ű�������ʾ"),
	/*m_shtType*/			UD_BOOL,
	/*m_wState*/			_PROP_OS(__OS_WIN),
	/*m_szzPickStr*/		NULL,
	}, 	
	{
	/*m_szName*/			_WT("�������"),
	/*m_szEgName*/			_WT("Offline"),
	/*m_szExplain*/			_WT("ָ��������Ƿ�ӻ��������ȡ���ı�ҳ������"),
	/*m_shtType*/			UD_BOOL,
	/*m_wState*/			_PROP_OS(__OS_WIN),
	/*m_szzPickStr*/		NULL,
	}, 	
	{
	/*m_szName*/			_WT("���Ϸ�"),
	/*m_szEgName*/			_WT("RegisterAsDropTarget"),
	/*m_szExplain*/			_WT("�����ע��Ϊ�����ϷŵĶ��󣬿���������ֱַ�Ӵ򿪡�"),
	/*m_shtType*/			UD_BOOL,
	/*m_wState*/			_PROP_OS(__OS_WIN),
	/*m_szzPickStr*/		NULL,
	}, 	
	{
	/*m_szName*/			_WT("���������"),
	/*m_szEgName*/			_WT("RegisterAsBrowser"),
	/*m_szExplain*/			_WT("ָ�����ע��Ϊ���������"),
	/*m_shtType*/			UD_BOOL,
	/*m_wState*/			_PROP_OS(__OS_WIN),
	/*m_szzPickStr*/		NULL,
	}, 	
	{
	/*m_szName*/			_WT("��ַ��"),
	/*m_szEgName*/			_WT("AddressBar"),
	/*m_szExplain*/			_WT("������Ƿ��е�ַ��"),
	/*m_shtType*/			UD_BOOL,
	/*m_wState*/			_PROP_OS(__OS_WIN)|UW_ONLY_READ,
	/*m_szzPickStr*/		NULL,
	}, 	
	{
	/*m_szName*/			_WT("ȫ��Ļ"),
	/*m_szEgName*/			_WT("FullScreen"),
	/*m_szExplain*/			_WT("������Ƿ�ȫ��Ļ"),
	/*m_shtType*/			UD_BOOL,
	/*m_wState*/			_PROP_OS(__OS_WIN)|UW_ONLY_READ,
	/*m_szzPickStr*/		NULL,
	}, 	
	{
	/*m_szName*/			_WT("�˵���"),
	/*m_szEgName*/			_WT("MenuBar"),
	/*m_szExplain*/			_WT("������Ƿ��в˵���"),
	/*m_shtType*/			UD_BOOL,
	/*m_wState*/			_PROP_OS(__OS_WIN)|UW_ONLY_READ,
	/*m_szzPickStr*/		NULL,
	}, 	
	{
	/*m_szName*/			_WT("�ɵ��߿�"),
	/*m_szEgName*/			_WT("Resizble"),
	/*m_szExplain*/			_WT("�����Ϊ�ɵ��߿򴰿�"),
	/*m_shtType*/			UD_BOOL,
	/*m_wState*/			_PROP_OS(__OS_WIN)|UW_ONLY_READ|UW_IS_HIDED,
	/*m_szzPickStr*/		NULL,
	}, 	
	{
	/*m_szName*/			_WT("״̬��"),
	/*m_szEgName*/			_WT("StatusBar"),
	/*m_szExplain*/			_WT("������Ƿ���״̬��"),
	/*m_shtType*/			UD_BOOL,
	/*m_wState*/			_PROP_OS(__OS_WIN)|UW_ONLY_READ,
	/*m_szzPickStr*/		NULL,
	}, 	
	{
	/*m_szName*/			_WT("ӰԺģʽ"),
	/*m_szEgName*/			_WT("TheaterMode"),
	/*m_szExplain*/			_WT("�����ΪӰԺģʽ"),
	/*m_shtType*/			UD_BOOL,
	/*m_wState*/			_PROP_OS(__OS_WIN)|UW_ONLY_READ,
	/*m_szzPickStr*/		NULL,
	}, 	
	{
	/*m_szName*/			_WT("������"),
	/*m_szEgName*/			_WT("ToolBar"),
	/*m_szExplain*/			_WT("������Ƿ��й�����"),
	/*m_shtType*/			UD_BOOL,
	/*m_wState*/			_PROP_OS(__OS_WIN)|UW_ONLY_READ,
	/*m_szzPickStr*/		NULL,
	}, 	
	{
	/*m_szName*/			_WT("�Ƿ����"),
	/*m_szEgName*/			_WT("Visible"),
	/*m_szExplain*/			_WT("������Ƿ����"),
	/*m_shtType*/			UD_BOOL,
	/*m_wState*/			_PROP_OS(__OS_WIN)|UW_ONLY_READ,
	/*m_szzPickStr*/		NULL,
	}, 	
	{
	/*m_szName*/			_WT("��æ"),
	/*m_szEgName*/			_WT("Busy"),
	/*m_szExplain*/			_WT("������Ƿ�æ״̬��"),
	/*m_shtType*/			UD_BOOL,
	/*m_wState*/			_PROP_OS(__OS_WIN)|UW_ONLY_READ,
	/*m_szzPickStr*/		NULL,
	}, 	
	{
	/*m_szName*/			_WT("�Ƿ񶥲�����"),
	/*m_szEgName*/			_WT("TopLevelContainer"),
	/*m_szExplain*/			_WT("������Ƿ�Ϊ��������"),
	/*m_shtType*/			UD_BOOL,
	/*m_wState*/			_PROP_OS(__OS_WIN)|UW_ONLY_READ,
	/*m_szzPickStr*/		NULL,
	}, 	
	{
	/*m_szName*/			_WT("����״̬"),
	/*m_szEgName*/			_WT("ReadyState"),
	/*m_szExplain*/			_WT("��ȡ���������״̬��"
		"0. δ��ʼ����1.  �������ء�2.  �����ء�3.  ͨ���С�4.  ���"),
	/*m_shtType*/			UD_INT,
	/*m_wState*/			_PROP_OS(__OS_WIN)|UW_ONLY_READ,
	/*m_szzPickStr*/		NULL,
	}, {
	/*m_szName*/			_WT("����ȫ·��"),
	/*m_szEgName*/			_WT("FullName"),
	/*m_szExplain*/			_WT("����Ӧ�ó����ȫ·��"),
	/*m_shtType*/			UD_TEXT,
	/*m_wState*/			_PROP_OS(__OS_WIN)|UW_ONLY_READ,
	/*m_szzPickStr*/		NULL,
	}, {
	/*m_szName*/			_WT("��ַ"),
	/*m_szEgName*/			_WT("LocationURL"),
	/*m_szExplain*/			_WT("���ص�ǰ���������ҳ��ַ"),
	/*m_shtType*/			UD_TEXT,
	/*m_wState*/			_PROP_OS(__OS_WIN)|UW_ONLY_READ,
	/*m_szzPickStr*/		NULL,
	}, {
	/*m_szName*/			_WT("����"),
	/*m_szEgName*/			_WT("Caption"),
	/*m_szExplain*/			_WT("����������ʱ�ṩ������ĵ�ǰ�����ı�"),
	/*m_shtType*/			UD_TEXT,
	/*m_wState*/			_PROP_OS(__OS_WIN)|UW_ONLY_READ,
	/*m_szzPickStr*/		NULL,
	}, {
	/*m_szName*/			_WT("�ĵ�����"),/////19
	/*m_szEgName*/			_WT("Type"),
	/*m_szExplain*/			_WT("����������������ĵ��������ı�"),
	/*m_shtType*/			UD_TEXT,
	/*m_wState*/			_PROP_OS(__OS_WIN)|UW_ONLY_READ,
	/*m_szzPickStr*/		NULL,
	}, {
	/*m_szName*/			_WT("�༭ģʽ"),//20
	/*m_szEgName*/			_WT("EditMode"),
	/*m_szExplain*/			_WT("���úͻ�ȡ������Ƿ�Ϊ�༭ģʽ��"),
	/*m_shtType*/			UD_BOOL,
	/*m_wState*/			_PROP_OS(__OS_WIN)|UW_CANNOT_INIT,
	/*m_szzPickStr*/		NULL,
	},{
	/*m_szName*/			_WT("��������"),//21
	/*m_szEgName*/			_WT("FontName"),
	/*m_szExplain*/			_WT("�ڱ༭ģʽ�£����ú�ȡ�ñ�ѡ���ı����������ơ����������ѡ��,��ȡ�ÿ��ı���"),
	/*m_shtType*/			UD_TEXT,
	/*m_wState*/			_PROP_OS(__OS_WIN)|UW_CANNOT_INIT |UW_HAS_INDENT,
	/*m_szzPickStr*/		NULL,
	},{
	/*m_szName*/			_WT("�����С"),//22
	/*m_szEgName*/			_WT("FontSize"),
	/*m_szExplain*/			_WT("�ڱ༭ģʽ�£����ú�ȡ�ñ�ѡ���ı��������С��Ϊ��ҳ�ֺš����������ѡ�У���ȡ���㡣"),
	/*m_shtType*/			UD_INT,
	/*m_wState*/			_PROP_OS(__OS_WIN)|UW_CANNOT_INIT |UW_HAS_INDENT,
	/*m_szzPickStr*/		NULL,
	},{
	/*m_szName*/			_WT("�ı���ɫ"),//23
	/*m_szEgName*/			_WT("ForeColor"),
	/*m_szExplain*/			_WT("�ڱ༭ģʽ�£����ú�ȡ�ñ�ѡ���ı�����ɫֵ�����������ѡ��,��ȡ���㡣"),
	/*m_shtType*/			UD_INT,
	/*m_wState*/			_PROP_OS(__OS_WIN)|UW_CANNOT_INIT |UW_HAS_INDENT,
	/*m_szzPickStr*/		NULL,
	},{
	/*m_szName*/			_WT("������ɫ"),//24
	/*m_szEgName*/			_WT("BackColor"),
	/*m_szExplain*/			_WT("�ڱ༭ģʽ�£����ú�ȡ�ñ�ѡ���ı��ı�����ɫֵ�����������ѡ��,��ȡ���㡣"),
	/*m_shtType*/			UD_INT,
	/*m_wState*/			_PROP_OS(__OS_WIN)|UW_CANNOT_INIT |UW_HAS_INDENT,
	/*m_szzPickStr*/		NULL,
	},{
	/*m_szName*/			_WT("����"),//25
	/*m_szEgName*/			_WT("Bold"),
	/*m_szExplain*/			_WT("�ڱ༭ģʽ�£���ѡ���ı��Ƿ�Ϊ���塣���������ѡ��,���Ե�һ���ַ�Ϊ׼��"),
	/*m_shtType*/			UD_BOOL,
	/*m_wState*/			_PROP_OS(__OS_WIN)|UW_ONLY_READ |UW_CANNOT_INIT |UW_HAS_INDENT,
	/*m_szzPickStr*/		NULL,
	},{
	/*m_szName*/			_WT("б��"),//26
	/*m_szEgName*/			_WT("Italic"),
	/*m_szExplain*/			_WT("�ڱ༭ģʽ�£���ѡ���ı��Ƿ�Ϊб�塣���������ѡ��,���Ե�һ���ַ�Ϊ׼��"),
	/*m_shtType*/			UD_BOOL,
	/*m_wState*/			_PROP_OS(__OS_WIN)|UW_ONLY_READ |UW_CANNOT_INIT |UW_HAS_INDENT,
	/*m_szzPickStr*/		NULL,
	},{
	/*m_szName*/			_WT("�»���"),//27
	/*m_szEgName*/			_WT("Underline"),
	/*m_szExplain*/			_WT("�ڱ༭ģʽ�£���ѡ���ı��Ƿ�Ϊ�»��ߡ����������ѡ��,���Ե�һ���ַ�Ϊ׼��"),
	/*m_shtType*/			UD_BOOL,
	/*m_wState*/			_PROP_OS(__OS_WIN)|UW_ONLY_READ |UW_CANNOT_INIT |UW_HAS_INDENT,
	/*m_szzPickStr*/		NULL,
	},{
	/*m_szName*/			_WT("ɾ����"),//28
	/*m_szEgName*/			_WT("StrikeThrough"),
	/*m_szExplain*/			_WT("�ڱ༭ģʽ�£���ѡ���ı��Ƿ�Ϊɾ���ߡ����������ѡ��,���Ե�һ���ַ�Ϊ׼��"),
	/*m_shtType*/			UD_BOOL,
	/*m_wState*/			_PROP_OS(__OS_WIN)|UW_ONLY_READ |UW_CANNOT_INIT |UW_HAS_INDENT,
	/*m_szzPickStr*/		NULL,
	},{
	/*m_szName*/			_WT("�ϱ�"),//29
	/*m_szEgName*/			_WT("Superscript"),
	/*m_szExplain*/			_WT("�ڱ༭ģʽ�£���ѡ���ı��Ƿ�Ϊ�ϱꡣ���������ѡ��,���Ե�һ���ַ�Ϊ׼��"),
	/*m_shtType*/			UD_BOOL,
	/*m_wState*/			_PROP_OS(__OS_WIN)|UW_ONLY_READ |UW_CANNOT_INIT |UW_HAS_INDENT,
	/*m_szzPickStr*/		NULL,
	},{
	/*m_szName*/			_WT("�±�"),//30
	/*m_szEgName*/			_WT("Subscript"),
	/*m_szExplain*/			_WT("�ڱ༭ģʽ�£���ѡ���ı��Ƿ�Ϊ�±ꡣ���������ѡ��,���Ե�һ���ַ�Ϊ׼��"),
	/*m_shtType*/			UD_BOOL,
	/*m_wState*/			_PROP_OS(__OS_WIN)|UW_ONLY_READ |UW_CANNOT_INIT |UW_HAS_INDENT,
	/*m_szzPickStr*/		NULL,
	},{
	/*m_szName*/			_WT("����״̬"),//31
	/*m_szEgName*/			_WT("OverWrite"),
	/*m_szExplain*/			_WT("�ڱ༭ģʽ�£���ҳ�༭���Ƿ�Ϊ���븲��״̬��"),
	/*m_shtType*/			UD_BOOL,
	/*m_wState*/			_PROP_OS(__OS_WIN)|UW_ONLY_READ |UW_CANNOT_INIT |UW_HAS_INDENT,
	/*m_szzPickStr*/		NULL,
	},{
	/*m_szName*/			_WT("�ɷ�ճ��"),//32
	/*m_szEgName*/			_WT("Paste"),
	/*m_szExplain*/			_WT("ָʾ�������Ƿ���á�"),
	/*m_shtType*/			UD_BOOL,
	/*m_wState*/			_PROP_OS(__OS_WIN)|UW_ONLY_READ |UW_CANNOT_INIT |UW_HAS_INDENT,
	/*m_szzPickStr*/		NULL,
	},{
	/*m_szName*/			_WT("�ɷ���"),//33
	/*m_szEgName*/			_WT("Copy"),
	/*m_szExplain*/			_WT("ָʾ�������Ƿ���á�"),
	/*m_shtType*/			UD_BOOL,
	/*m_wState*/			_PROP_OS(__OS_WIN)|UW_ONLY_READ |UW_CANNOT_INIT |UW_HAS_INDENT,
	/*m_szzPickStr*/		NULL,
	},{
	/*m_szName*/			_WT("�ɷ����"),//34
	/*m_szEgName*/			_WT("Cut"),
	/*m_szExplain*/			_WT("ָʾ�������Ƿ���á�"),
	/*m_shtType*/			UD_BOOL,
	/*m_wState*/			_PROP_OS(__OS_WIN)|UW_ONLY_READ |UW_CANNOT_INIT |UW_HAS_INDENT,
	/*m_szzPickStr*/		NULL,
	},{
	/*m_szName*/			_WT("�ɷ�����"),//35
	/*m_szEgName*/			_WT("Redo"),
	/*m_szExplain*/			_WT("ָʾ�������Ƿ���á�"),
	/*m_shtType*/			UD_BOOL,
	/*m_wState*/			_PROP_OS(__OS_WIN)|UW_ONLY_READ |UW_CANNOT_INIT |UW_HAS_INDENT,
	/*m_szzPickStr*/		NULL,
	},{
	/*m_szName*/			_WT("�ɷ���"),//36
	/*m_szEgName*/			_WT("Undo"),
	/*m_szExplain*/			_WT("ָʾ�������Ƿ���á�"),
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

// ע��˴��������������������Ա���ȫһ�¡�
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

// !! GetFontValue��������ʱ���ܱ��û������ı䣨������ֱ�ӵ���API�����������ԣ�������ʱ����ȡ������ʵ��ֵ��
BOOL WINAPI GetPropertyData_HtmlViewer (HUNIT hUnit, INT nPropertyIndex,
										PUNIT_PROPERTY_VALUE pPropertyVaule)
{
	ASSERT (hUnit != NULL);
	if (hUnit == NULL)  return FALSE;
	CViewHtml* pUnit = (CViewHtml*)hUnit;
	ASSERT (pUnit->GetSafeHwnd () != NULL);

// ע��˴��������������������Ա���ȫһ�¡�
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


