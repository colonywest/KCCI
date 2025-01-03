// KCCI.h : main header file for the KCCI application
//

#if !defined(AFX_KCCI_H__97B8E07E_D8DD_4846_B1F2_FE6AA6B7F089__INCLUDED_)
#define AFX_KCCI_H__97B8E07E_D8DD_4846_B1F2_FE6AA6B7F089__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CKCCIApp:
// See KCCI.cpp for the implementation of this class
//

class CKCCIApp : public CWinApp
{
public:
	CKCCIApp();
	CFont titlefont;

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CKCCIApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CKCCIApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_KCCI_H__97B8E07E_D8DD_4846_B1F2_FE6AA6B7F089__INCLUDED_)
