// ashsystray.h : main header file for the ASHSYSTRAY application
//

#if !defined(AFX_ASHSYSTRAY_H__4861817C_B708_4733_B220_51AEC32F88D1__INCLUDED_)
#define AFX_ASHSYSTRAY_H__4861817C_B708_4733_B220_51AEC32F88D1__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CAshsystrayApp:
// See ashsystray.cpp for the implementation of this class
//

class CAshsystrayApp : public CWinApp
{
public:
	HICON m_pIconList[3];
	CAshsystrayApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAshsystrayApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CAshsystrayApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

extern CAshsystrayApp theApp;


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ASHSYSTRAY_H__4861817C_B708_4733_B220_51AEC32F88D1__INCLUDED_)
