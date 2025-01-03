#if !defined(AFX_UPDATE_H__269F7549_613C_4641_8815_90B522B2D40F__INCLUDED_)
#define AFX_UPDATE_H__269F7549_613C_4641_8815_90B522B2D40F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Update.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CUpdate dialog

class CUpdate : public CDialog
{
// Construction
public:
	CUpdate(CWnd* pParent = NULL);   // standard constructor

	int updateSchoolNetStations;
	int updateSchoolNetData;
	int updateRadarImage;
	int updateForecastImage;
    int updateCameras;

// Dialog Data
	//{{AFX_DATA(CUpdate)
	enum { IDD = IDD_Update };
	CButton	m_Camera;
	CButton	m_SchoolNetStation;
	CButton	m_SchoolNetData;
	CButton	m_Radar;
	CButton	m_Forecast;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CUpdate)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CUpdate)
	afx_msg void OnSelectAll();
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	afx_msg void OnSchoolNetStation();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_UPDATE_H__269F7549_613C_4641_8815_90B522B2D40F__INCLUDED_)
