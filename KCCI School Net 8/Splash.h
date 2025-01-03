#if !defined(AFX_SPLASH_H__3BE95B55_9809_42D7_974F_0A50D4CBA6A4__INCLUDED_)
#define AFX_SPLASH_H__3BE95B55_9809_42D7_974F_0A50D4CBA6A4__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Splash.h : header file
//

#include "xImage.h"

/////////////////////////////////////////////////////////////////////////////
// CSplash dialog

class CSplash : public CDialog
{
// Construction
public:
	CSplash(CWnd* pParent = NULL);   // standard constructor

	void PumpMessages();
	CxImage image;

// Dialog Data
	//{{AFX_DATA(CSplash)
	enum { IDD = IDD_Splash };
	CStatic	m_Status;
	CStatic	m_SplashImage;
	CProgressCtrl	m_Progress;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSplash)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CSplash)
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnOK();
	afx_msg void OnCancel();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SPLASH_H__3BE95B55_9809_42D7_974F_0A50D4CBA6A4__INCLUDED_)
