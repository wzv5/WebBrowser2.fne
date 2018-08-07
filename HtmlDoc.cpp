// HtmlDoc.cpp : implementation file
//

#include "stdafx.h"
#include "WebBrowser2.h"
#include "HtmlDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CHtmlDoc

IMPLEMENT_DYNCREATE(CHtmlDoc, CDocument)

CHtmlDoc::CHtmlDoc()
{
}

BOOL CHtmlDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;
	return TRUE;
}

CHtmlDoc::~CHtmlDoc()
{
}


BEGIN_MESSAGE_MAP(CHtmlDoc, CDocument)
	//{{AFX_MSG_MAP(CHtmlDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CHtmlDoc diagnostics

#ifdef _DEBUG
void CHtmlDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CHtmlDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CHtmlDoc serialization

void CHtmlDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: add storing code here
	}
	else
	{
		// TODO: add loading code here
	}
}

/////////////////////////////////////////////////////////////////////////////
// CHtmlDoc commands
