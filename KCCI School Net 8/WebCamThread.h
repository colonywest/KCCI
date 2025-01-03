#if !defined(AFX_WEBCAMTHREAD_H__40BC0E78_523C_4AF9_A1BA_287F8664B269__INCLUDED_)
#define AFX_WEBCAMTHREAD_H__40BC0E78_523C_4AF9_A1BA_287F8664B269__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// WebCamThread.h : header file
//

#include "WebCam.h"
#include "LinkedList.h"

/////////////////////////////////////////////////////////////////////////////
// CWebCamThread thread

class CWebCamThread : public CWinThread
{
	DECLARE_DYNCREATE(CWebCamThread)
protected:
	CWebCamThread();           // protected constructor used by dynamic creation

// Attributes
public:
	LinkedList * webcams;
	CWebCam * webcam;
	CWinThread ** parent;

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CWebCamThread)
	public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~CWebCamThread();

	// Generated message map functions
	//{{AFX_MSG(CWebCamThread)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_WEBCAMTHREAD_H__40BC0E78_523C_4AF9_A1BA_287F8664B269__INCLUDED_)
