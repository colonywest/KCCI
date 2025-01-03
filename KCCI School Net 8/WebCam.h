#if !defined(AFX_WEBCAM_H__BDC312DC_9540_4860_B0B3_30E7AA5EB314__INCLUDED_)
#define AFX_WEBCAM_H__BDC312DC_9540_4860_B0B3_30E7AA5EB314__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// WebCam.h : header file
//

#include "LinkedList.h"
#include "xImage.h"

/////////////////////////////////////////////////////////////////////////////
// CWebCam dialog

class CWebCam : public CDialog
{
// Construction
public:
	CWebCam(CWnd* pParent = NULL);   // standard constructor

	LinkedList * cams;
	CxImage image;

// Dialog Data
	//{{AFX_DATA(CWebCam)
	enum { IDD = IDD_WebCam };
	CStatic	m_Image;
	CProgressCtrl	m_Progress;
	CComboBox	m_Camera;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CWebCam)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CWebCam)
	virtual BOOL OnInitDialog();
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnSelendokCamera();
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_WEBCAM_H__BDC312DC_9540_4860_B0B3_30E7AA5EB314__INCLUDED_)
