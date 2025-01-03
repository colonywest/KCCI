// ashsystrayDlg.h : header file
//

#if !defined(AFX_ASHSYSTRAYDLG_H__E3615DCB_AA0B_497C_BF37_CD933FAD5AF6__INCLUDED_)
#define AFX_ASHSYSTRAYDLG_H__E3615DCB_AA0B_497C_BF37_CD933FAD5AF6__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "TrayNot.h"
/////////////////////////////////////////////////////////////////////////////
// CAshsystrayDlg dialog

class CAshsystrayDlg : public CDialog
{
// Construction
public:
	CTrayNot*	m_pTray;
	BOOL  m_bHidden;
	CAshsystrayDlg(CWnd* pParent = NULL);	// standard constructor
	
	void CANCEL();
// Dialog Data
	//{{AFX_DATA(CAshsystrayDlg)
	enum { IDD = IDD_ASHSYSTRAY_DIALOG };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAshsystrayDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CAshsystrayDlg)
	virtual BOOL OnInitDialog();
	afx_msg LONG OnTrayNotify ( WPARAM wParam, LPARAM lParam ) ;
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnTrayRestore();
	afx_msg void OnHideapp();
	afx_msg void OnHide();
	afx_msg void OnUnHide();
	afx_msg void OnDestroy();
	afx_msg void OnAppExit();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ASHSYSTRAYDLG_H__E3615DCB_AA0B_497C_BF37_CD933FAD5AF6__INCLUDED_)
