#if !defined(AFX_OPTIONSTHREAD_H__269BE339_9152_4347_A072_EFE22A03AD29__INCLUDED_)
#define AFX_OPTIONSTHREAD_H__269BE339_9152_4347_A072_EFE22A03AD29__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// OptionsThread.h : header file
//

#include "KCCI.h"
#include "KCCIDlg.h"

#include "OptionsSheet.h"
#include "OptionsGeneral.h"
#include "OptionsInternet.h"
#include "OptionsRadar.h"
#include "OptionsSchoolNet.h"
#include "OptionsWebCam.h"

/////////////////////////////////////////////////////////////////////////////
// COptionsThread thread

class COptionsThread : public CWinThread
{
	DECLARE_DYNCREATE(COptionsThread)
protected:
	COptionsThread();           // protected constructor used by dynamic creation

// Attributes
public:
	CKCCIDlg * kcci;

	COptionsSheet * optionsSheet;
	COptionsGeneral * generalTab;
	COptionsSchoolNet * schoolNet;
	COptionsRadar * radar;
	COptionsWebCam * webCam;
	COptionsInternet * internet;


// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(COptionsThread)
	public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~COptionsThread();

	// Generated message map functions
	//{{AFX_MSG(COptionsThread)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_OPTIONSTHREAD_H__269BE339_9152_4347_A072_EFE22A03AD29__INCLUDED_)
