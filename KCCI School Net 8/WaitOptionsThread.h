#if !defined(AFX_WAITOPTIONSTHREAD_H__7A004C89_847B_4965_809F_3B26C3A31984__INCLUDED_)
#define AFX_WAITOPTIONSTHREAD_H__7A004C89_847B_4965_809F_3B26C3A31984__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// WaitOptionsThread.h : header file
//

#include "Waiting.h"
#include "OptionsSheet.h"
#include "OptionsInternet.h"

/////////////////////////////////////////////////////////////////////////////
// CWaitOptionsThread thread

class CWaitOptionsThread : public CWinThread
{
	DECLARE_DYNCREATE(CWaitOptionsThread)
protected:
	CWaitOptionsThread();           // protected constructor used by dynamic creation

// Attributes
public:
	CWaiting * wait;
	CWinThread ** parent;
	COptionsSheet * optionsSheet;
	COptionsInternet * internet;

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CWaitOptionsThread)
	public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~CWaitOptionsThread();

	// Generated message map functions
	//{{AFX_MSG(CWaitOptionsThread)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_WAITOPTIONSTHREAD_H__7A004C89_847B_4965_809F_3B26C3A31984__INCLUDED_)
