#if !defined(AFX_OPTIONSRADAR_H__7348772A_EE88_40F8_A663_70643BE632B5__INCLUDED_)
#define AFX_OPTIONSRADAR_H__7348772A_EE88_40F8_A663_70643BE632B5__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// OptionsRadar.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// COptionsRadar dialog

class COptionsRadar : public CPropertyPage
{
	DECLARE_DYNCREATE(COptionsRadar)

// Construction
public:
	COptionsRadar();
	~COptionsRadar();

	void OnOK();
	BOOL OnKillActive();

// Dialog Data
	//{{AFX_DATA(COptionsRadar)
	enum { IDD = IDD_Options_Radar };
	CEdit	m_RadarUpdate;
	CButton	m_DisableWhenMinimized;
	CButton	m_DisableRadarUpdate;
	CComboBox	m_DefaultRadar;
	//}}AFX_DATA


// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(COptionsRadar)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(COptionsRadar)
	virtual BOOL OnInitDialog();
	afx_msg void OnDisableRadarUpdate();
	afx_msg void OnDisableWhenMinimized();
	afx_msg void OnChangeRadarUpdate();
	afx_msg void OnSelendokDefaultRadar();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_OPTIONSRADAR_H__7348772A_EE88_40F8_A663_70643BE632B5__INCLUDED_)
