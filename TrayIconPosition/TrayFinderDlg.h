// TrayFinderDlg.h : header file
//

#if !defined(AFX_TRAYFINDERDLG_H__879D05C7_451A_11D7_B751_00304F20BD3B__INCLUDED_)
#define AFX_TRAYFINDERDLG_H__879D05C7_451A_11D7_B751_00304F20BD3B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "TrayIconPosition.h"
/////////////////////////////////////////////////////////////////////////////
// CTrayFinderDlg dialog

class CTrayFinderDlg : public CDialog
{
// Construction
public:
	CTrayFinderDlg(CWnd* pParent = NULL);	// standard constructor
	CTrayIconPosition m_tipPosition;

// Dialog Data
	//{{AFX_DATA(CTrayFinderDlg)
	enum { IDD = IDD_TRAYFINDER_DIALOG };
	int		m_iTrackType;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTrayFinderDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CTrayFinderDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnAdd();
	afx_msg void OnDelete();
	afx_msg void OnDestroy();
	afx_msg void OnCalculate();
	afx_msg void OnIzsoft();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TRAYFINDERDLG_H__879D05C7_451A_11D7_B751_00304F20BD3B__INCLUDED_)
