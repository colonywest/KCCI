#if !defined(AFX_OPTIONSWEBCAM_H__76A415C8_BC68_4012_BD8E_DD6A42FAD492__INCLUDED_)
#define AFX_OPTIONSWEBCAM_H__76A415C8_BC68_4012_BD8E_DD6A42FAD492__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// OptionsWebCam.h : header file
//

#include "LinkedList.h"

/////////////////////////////////////////////////////////////////////////////
// COptionsWebCam dialog

class COptionsWebCam : public CPropertyPage
{
	DECLARE_DYNCREATE(COptionsWebCam)

// Construction
public:
	COptionsWebCam();
	~COptionsWebCam();

	void OnOK();
	BOOL OnKillActive();

	LinkedList * cameraList;

// Dialog Data
	//{{AFX_DATA(COptionsWebCam)
	enum { IDD = IDD_Options_WebCam };
	CComboBox	m_DefaultCamera;
	CEdit	m_CameraUpdate;
	//}}AFX_DATA


// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(COptionsWebCam)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(COptionsWebCam)
	virtual BOOL OnInitDialog();
	afx_msg void OnChangeCameraUpdate();
	afx_msg void OnSelendokDefaultCamera();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_OPTIONSWEBCAM_H__76A415C8_BC68_4012_BD8E_DD6A42FAD492__INCLUDED_)
