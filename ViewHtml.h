#if !defined(AFX_VIEWHTML_H__7876400C_2260_4A88_90C2_148AAF342BEA__INCLUDED_)
#define AFX_VIEWHTML_H__7876400C_2260_4A88_90C2_148AAF342BEA__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ViewHtml.h : header file
//
#include "lib2.h"
#include "untshare.h"
#define CUR_UNIT_VER		1

#include <MsHTML.h>//定义了IHTMLDocument2等接口
#include <mshtmdid.h>//定义了HTMLDocumentEvents2接口的方法DISPID
#include <afxctl.h>//定义了AfxConnectionAdvise、AfxConnectionUnadvise等函数,等会连接到事件源时要用到


class CPIHtmlViewer : public CPropertyInfo
{
public:
	INT m_Style;
    BOOL m_blSilent;
    BOOL m_blOffline;
    BOOL m_blRegisterAsDropTarget;
    BOOL m_blRegisterAsBrowser;

public:
	CPIHtmlViewer ()  { }

	virtual void init ();
	virtual BOOL Serialize (CArchive& ar);
};

extern "C"
PFN_INTERFACE WINAPI webbrowser2_GetInterface_WebBrowser (INT nInterfaceNO);

HUNIT WINAPI Create_HtmlViewer (LPBYTE pAllData, INT nAllDataSize,
		DWORD dwStyle, HWND hParentWnd, UINT uID, HMENU hMenu, INT x, INT y, INT cx, INT cy,
		DWORD dwWinFormID, DWORD dwUnitID, HWND hDesignWnd = 0, BOOL blInDesignMode = FALSE);
BOOL WINAPI NotifyPropertyChanged_HtmlViewer (HUNIT hUnit, INT nPropertyIndex,
		PUNIT_PROPERTY_VALUE pPropertyVaule, LPTSTR* ppszTipText);
BOOL WINAPI GetPropertyData_HtmlViewer (HUNIT hUnit, INT nPropertyIndex,
		PUNIT_PROPERTY_VALUE pPropertyVaule);
HGLOBAL WINAPI GetAllPropertyData_HtmlViewer (HUNIT hUnit);

/////////////////////////////////////////////////////////////////////////////
// CViewHtml html view

#ifndef __AFXEXT_H__
#include <afxext.h>
#endif
#include <afxhtml.h>

class CViewHtml : public CHtmlView
{
protected:
	DECLARE_DYNCREATE(CViewHtml)

// html Data
public:
	CViewHtml();           // protected constructor used by dynamic creation
	virtual ~CViewHtml();
	//{{AFX_DATA(CViewHtml)
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

// Attributes
public:
	DWORD m_dwWinFormID, m_dwUnitID;
	BOOL m_blInDesignMode;
	CPIHtmlViewer m_info;
	CString m_strFullName;
	CString m_strLocationURL;
	CString m_strLocationName;
	CString m_strType;
	BOOL m_blTemp;
	IHTMLDocument2* pDoc2;
// Operations
public:
	BOOL m_bEditMode;
	BOOL m_bIsEvenConn;
	DWORD m_dwCookie;
	BOOL OnHtmlOnclick(IHTMLEventObj *pEvtObj);
	BOOL OnHtmlContextMenu(IHTMLEventObj *pEvtObj);

	INT ExecHTMCommand(INT nCID);
	LRESULT OnGetWndPtr(WPARAM wparam, LPARAM lparam);
	BOOL execCommand(CString sCmd);
	BOOL TheCommandIsEnabled(UINT nCode);
	BOOL GetFontStyle(UINT nCode);
	void SetFontValue(UINT nCode,INT nValue);
	INT GetFontValue(UINT nCode);
	void SetFontName(LPCTSTR lpszfn);
	BOOL GetEditMode();
	CString GetFontName();
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CViewHtml)
	public:
	virtual void OnBeforeNavigate2(LPCTSTR lpszURL, DWORD nFlags, LPCTSTR lpszTargetFrameName, CByteArray& baPostedData, LPCTSTR lpszHeaders, BOOL* pbCancel);
	virtual void OnCommandStateChange(long nCommand, BOOL bEnable);
	virtual void OnDocumentComplete(LPCTSTR lpszURL);
	virtual void OnDownloadBegin();
	virtual void OnDownloadComplete();
	virtual void OnProgressChange(long nProgress, long nProgressMax);
	virtual void OnStatusTextChange(LPCTSTR lpszText);
	virtual void OnTitleChange(LPCTSTR lpszText);
	virtual void OnNavigateComplete2(LPCTSTR strURL);
	virtual void OnNewWindow2(LPDISPATCH* ppDisp, BOOL* Cancel);
	virtual void OnQuit();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual void PostNcDestroy();
	//}}AFX_VIRTUAL

// Implementation
protected:

#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// Generated message map functions
	//{{AFX_MSG(CViewHtml)
	afx_msg void OnFileDownload(BOOL FAR* Cancel);
	afx_msg void OnWindowSetTop(long Top);
	afx_msg void OnWindowSetHeight(long Height);
	afx_msg void OnWindowSetLeft(long Left);
	afx_msg void OnWindowSetWidth(long Width);
	afx_msg void OnWindowSetResizable(BOOL Resizable);
	afx_msg void OnWindowClosing(BOOL IsChildWindow, BOOL FAR* Cancel);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	DECLARE_EVENTSINK_MAP()
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
	DECLARE_DISPATCH_MAP()//声明dispatch map表
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_VIEWHTML_H__7876400C_2260_4A88_90C2_148AAF342BEA__INCLUDED_)
