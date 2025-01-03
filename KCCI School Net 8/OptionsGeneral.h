#if !defined(AFX_OPTIONSGENERAL_H__B89A2A49_CE47_4B44_A8B0_62300A873326__INCLUDED_)
#define AFX_OPTIONSGENERAL_H__B89A2A49_CE47_4B44_A8B0_62300A873326__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// OptionsGeneral.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// COptionsGeneral dialog

class COptionsGeneral : public CPropertyPage
{
	DECLARE_DYNCREATE(COptionsGeneral)

// Construction
public:
	COptionsGeneral();
	~COptionsGeneral();

	int ControlPanel, DefaultView;
	int RunStartup;

	void OnOK();

// Dialog Data
	//{{AFX_DATA(COptionsGeneral)
	enum { IDD = IDD_Options_General };
	CComboBox	m_ControlPanel;
	CComboBox	m_DefaultView;
	CButton	m_RunStart;
	//}}AFX_DATA


// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(COptionsGeneral)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(COptionsGeneral)
	virtual BOOL OnInitDialog();
	afx_msg void OnRunStart();
	afx_msg void OnSelendokDefaultView();
	afx_msg void OnSelendokControlPanel();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_OPTIONSGENERAL_H__B89A2A49_CE47_4B44_A8B0_62300A873326__INCLUDED_)
