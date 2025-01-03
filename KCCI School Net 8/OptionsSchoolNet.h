#if !defined(AFX_OPTIONSSCHOOLNET_H__D823776A_57C0_4DE9_846E_7293A51756E4__INCLUDED_)
#define AFX_OPTIONSSCHOOLNET_H__D823776A_57C0_4DE9_846E_7293A51756E4__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// OptionsSchoolNet.h : header file
//

#include "LinkedList.h"

/////////////////////////////////////////////////////////////////////////////
// COptionsSchoolNet dialog

class COptionsSchoolNet : public CPropertyPage
{
	DECLARE_DYNCREATE(COptionsSchoolNet)

// Construction
public:
	COptionsSchoolNet();
	~COptionsSchoolNet();

	void OnOK();
	BOOL OnKillActive();

	LinkedList * stationList;

// Dialog Data
	//{{AFX_DATA(COptionsSchoolNet)
	enum { IDD = IDD_Options_SchoolNet };
	CEdit	m_TimeOld;
	CEdit	m_SchoolNetUpdate;
	CComboBox	m_DefaultStation;
	CEdit	m_DataPlotUpdate;
	//}}AFX_DATA


// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(COptionsSchoolNet)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(COptionsSchoolNet)
	virtual BOOL OnInitDialog();
	afx_msg void OnChangeDataPlotUpdate();
	afx_msg void OnSelendokDefaultStation();
	afx_msg void OnChangeSchoolNetUpdate();
	afx_msg void OnChangeTimeOld();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_OPTIONSSCHOOLNET_H__D823776A_57C0_4DE9_846E_7293A51756E4__INCLUDED_)
