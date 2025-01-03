#if !defined(AFX_WAITING_H__35090BB5_EFC1_4006_A6CA_9DDD78AC5BD1__INCLUDED_)
#define AFX_WAITING_H__35090BB5_EFC1_4006_A6CA_9DDD78AC5BD1__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Waiting.h : header file
//

#include "TrayNot.h"

/////////////////////////////////////////////////////////////////////////////
// CWaiting dialog

class CWaiting : public CDialog
{
// Construction
public:
	CWaiting(CWnd* pParent = NULL);   // standard constructor
	CTrayNot * tray;

	CWinThread * waitOptionsThread;
	CWinThread * checkConnection;

// Dialog Data
	//{{AFX_DATA(CWaiting)
	enum { IDD = IDD_Waiting };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CWaiting)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CWaiting)
	afx_msg void OnTimer(UINT nIDEvent);
	virtual BOOL OnInitDialog();
	afx_msg void OnDestroy();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnTaskbarCreated();
	afx_msg void OnTrayNotify(WPARAM, LPARAM);
	afx_msg void OnWAITExit();
	afx_msg void OnWAITRestore();
	afx_msg void OnWAITOptions();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_WAITING_H__35090BB5_EFC1_4006_A6CA_9DDD78AC5BD1__INCLUDED_)
