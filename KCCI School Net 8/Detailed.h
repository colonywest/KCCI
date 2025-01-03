#if !defined(AFX_DETAILED_H__4608B003_A2E3_4513_AA15_D4B66A34CF15__INCLUDED_)
#define AFX_DETAILED_H__4608B003_A2E3_4513_AA15_D4B66A34CF15__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Detailed.h : header file
//

#include "KCCISchoolNet.h"

/////////////////////////////////////////////////////////////////////////////
// CDetailed dialog

class CDetailed : public CDialog
{
// Construction
public:
	CDetailed(CWnd* pParent = NULL);   // standard constructor
	KCCISchoolNetData * data;
	KCCIStationList * station;

// Dialog Data
	//{{AFX_DATA(CDetailed)
	enum { IDD = IDD_Detailed };
	CRichEditCtrl	m_View;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDetailed)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDetailed)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DETAILED_H__4608B003_A2E3_4513_AA15_D4B66A34CF15__INCLUDED_)
