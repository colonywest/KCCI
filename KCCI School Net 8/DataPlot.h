#if !defined(AFX_DATAPLOT_H__C2C53A7D_6BC6_4B7C_A7B7_91C53CACC528__INCLUDED_)
#define AFX_DATAPLOT_H__C2C53A7D_6BC6_4B7C_A7B7_91C53CACC528__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DataPlot.h : header file
//

#include "LinkedList.h"
#include "xImage.h"

/////////////////////////////////////////////////////////////////////////////
// CDataPlot dialog

class CDataPlot : public CDialog
{
// Construction
public:
	CDataPlot(CWnd* pParent = NULL);   // standard constructor

	LinkedList * stations;
	int currentStation;
	CxImage image;


// Dialog Data
	//{{AFX_DATA(CDataPlot)
	enum { IDD = IDD_DataPlot };
	CProgressCtrl	m_Progress;
	CStatic	m_View;
	CComboBox	m_Variable;
	CComboBox	m_Station;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDataPlot)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDataPlot)
	virtual BOOL OnInitDialog();
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnSelendokStation();
	afx_msg void OnSelendokVariable();
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DATAPLOT_H__C2C53A7D_6BC6_4B7C_A7B7_91C53CACC528__INCLUDED_)
