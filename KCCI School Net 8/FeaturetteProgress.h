#if !defined(AFX_FEATURETTEPROGRESS_H__9C384704_2F0F_4776_A1AA_45CC63F1AD50__INCLUDED_)
#define AFX_FEATURETTEPROGRESS_H__9C384704_2F0F_4776_A1AA_45CC63F1AD50__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// FeaturetteProgress.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CFeaturetteProgress dialog

class CFeaturetteProgress : public CDialog
{
// Construction
public:
	CFeaturetteProgress(CWnd* pParent = NULL);   // standard constructor

	void PumpMessages();

// Dialog Data
	//{{AFX_DATA(CFeaturetteProgress)
	enum { IDD = IDD_FeaturetteProgress };
	CProgressCtrl	m_Progress;
	CStatic	m_Featurette;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CFeaturetteProgress)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CFeaturetteProgress)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_FEATURETTEPROGRESS_H__9C384704_2F0F_4776_A1AA_45CC63F1AD50__INCLUDED_)
