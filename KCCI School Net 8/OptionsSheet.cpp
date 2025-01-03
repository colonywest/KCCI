// OptionsSheet.cpp : implementation file
//

#include "stdafx.h"
#include "KCCI.h"
#include "OptionsSheet.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// COptionsSheet

IMPLEMENT_DYNAMIC(COptionsSheet, CPropertySheet)

COptionsSheet::COptionsSheet(UINT nIDCaption, CWnd* pParentWnd, UINT iSelectPage)
	:CPropertySheet(nIDCaption, pParentWnd, iSelectPage)
{
}

COptionsSheet::COptionsSheet(LPCTSTR pszCaption, CWnd* pParentWnd, UINT iSelectPage)
	:CPropertySheet(pszCaption, pParentWnd, iSelectPage)
{
}

COptionsSheet::~COptionsSheet()
{
}


BEGIN_MESSAGE_MAP(COptionsSheet, CPropertySheet)
	//{{AFX_MSG_MAP(COptionsSheet)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		ON_COMMAND(IDOK, OnOK)
		ON_COMMAND(IDCANCEL, OnCancel)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// COptionsSheet message handlers

BOOL COptionsSheet::OnInitDialog() 
{

	/* Because I want the standard buttons, I need to tell CPropertySheet that this
	 * is a modal dialog box, even though it isn't.
	 */

	BOOL bModeless = m_bModeless;

	m_bModeless = FALSE;

	BOOL bResult = CPropertySheet::OnInitDialog();

	m_bModeless = bModeless;
	
	// TODO: Add your specialized code here
	
	return bResult;
}

void COptionsSheet::OnOK()
{
	exitCode = 1;

	for(int x = 0; x < GetPageCount(); x++)
	{
		CPropertyPage * page = GetPage(x);
		page->OnOK();
	}

	PostMessage(WM_QUIT);
}

void COptionsSheet::OnCancel()
{
	exitCode = 0;
	PostMessage(WM_QUIT);
}
