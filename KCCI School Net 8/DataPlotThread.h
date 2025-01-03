#if !defined(AFX_DATAPLOTTHREAD_H__D53A53F9_5B06_4576_B0A1_DCA9A849D449__INCLUDED_)
#define AFX_DATAPLOTTHREAD_H__D53A53F9_5B06_4576_B0A1_DCA9A849D449__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DataPlotThread.h : header file
//

#include "DataPlot.h"
#include "LinkedList.h"

/////////////////////////////////////////////////////////////////////////////
// CDataPlotThread thread

class CDataPlotThread : public CWinThread
{
	DECLARE_DYNCREATE(CDataPlotThread)
protected:
	CDataPlotThread();           // protected constructor used by dynamic creation

// Attributes
public:
	LinkedList * stations;
	int currentStation;
	CDataPlot * dataPlotDlg;
	CWinThread ** parent;

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDataPlotThread)
	public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~CDataPlotThread();

	// Generated message map functions
	//{{AFX_MSG(CDataPlotThread)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DATAPLOTTHREAD_H__D53A53F9_5B06_4576_B0A1_DCA9A849D449__INCLUDED_)
