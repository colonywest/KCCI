// TrayFinder.h : main header file for the TRAYFINDER application
//

#if !defined(AFX_TRAYFINDER_H__879D05C5_451A_11D7_B751_00304F20BD3B__INCLUDED_)
#define AFX_TRAYFINDER_H__879D05C5_451A_11D7_B751_00304F20BD3B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CTrayFinderApp:
// See TrayFinder.cpp for the implementation of this class
//

class CTrayFinderApp : public CWinApp
{
public:
	CTrayFinderApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTrayFinderApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CTrayFinderApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TRAYFINDER_H__879D05C5_451A_11D7_B751_00304F20BD3B__INCLUDED_)
