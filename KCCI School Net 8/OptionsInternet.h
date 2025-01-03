#if !defined(AFX_OPTIONSINTERNET_H__2ED53937_93A8_4151_ADC6_68C774C7A45C__INCLUDED_)
#define AFX_OPTIONSINTERNET_H__2ED53937_93A8_4151_ADC6_68C774C7A45C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// OptionsInternet.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// COptionsInternet dialog

class COptionsInternet : public CPropertyPage
{
	DECLARE_DYNCREATE(COptionsInternet)

// Construction
public:
	COptionsInternet();
	~COptionsInternet();

	void OnOK();
	BOOL OnKillActive();

// Dialog Data
	//{{AFX_DATA(COptionsInternet)
	enum { IDD = IDD_Options_Internet };
	CStatic	m_ProxyServerLabel;
	CStatic	m_ProxyPortLabel;
	CButton	m_UseProxy;
	CButton	m_UpdateCheck;
	CEdit	m_ProxyServer;
	CEdit	m_ProxyPort;
	CEdit	m_NetworkTimeout;
	CEdit	m_InternetCheck;
	//}}AFX_DATA


// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(COptionsInternet)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(COptionsInternet)
	virtual BOOL OnInitDialog();
	afx_msg void OnUseProxy();
	afx_msg void OnChangeInternetCheck();
	afx_msg void OnChangeNetworkTimeout();
	afx_msg void OnChangeProxyPort();
	afx_msg void OnChangeProxyServer();
	afx_msg void OnUpdateCheck();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_OPTIONSINTERNET_H__2ED53937_93A8_4151_ADC6_68C774C7A45C__INCLUDED_)
