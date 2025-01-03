#if !defined(AFX_DETAILEDTHREAD_H__139C6503_0964_47C1_8DF6_24BDA7B4CDC4__INCLUDED_)
#define AFX_DETAILEDTHREAD_H__139C6503_0964_47C1_8DF6_24BDA7B4CDC4__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DetailedThread.h : header file
//

#include "Detailed.h"
#include "KCCISchoolNet.h"

/////////////////////////////////////////////////////////////////////////////
// CDetailedThread thread

class CDetailedThread : public CWinThread
{
	DECLARE_DYNCREATE(CDetailedThread)
protected:
	CDetailedThread();           // protected constructor used by dynamic creation

// Attributes
public:
	KCCISchoolNetData * data;
	KCCIStationList * station;

	CDetailed * detailed;
	CWinThread ** parent;

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDetailedThread)
	public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();
	//}}AFX_VIRTUAL

// Implementation
	virtual ~CDetailedThread();

protected:

	// Generated message map functions
	//{{AFX_MSG(CDetailedThread)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DETAILEDTHREAD_H__139C6503_0964_47C1_8DF6_24BDA7B4CDC4__INCLUDED_)
