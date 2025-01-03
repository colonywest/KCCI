// OptionsInternet.cpp : implementation file
//

#include "stdafx.h"
#include "KCCI.h"
#include "OptionsInternet.h"

#include "Registry.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// COptionsInternet property page

IMPLEMENT_DYNCREATE(COptionsInternet, CPropertyPage)

COptionsInternet::COptionsInternet() : CPropertyPage(COptionsInternet::IDD)
{
	//{{AFX_DATA_INIT(COptionsInternet)
	//}}AFX_DATA_INIT
}

COptionsInternet::~COptionsInternet()
{
}

void COptionsInternet::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(COptionsInternet)
	DDX_Control(pDX, IDC_ProxyServerLabel, m_ProxyServerLabel);
	DDX_Control(pDX, IDC_ProxyPortLabel, m_ProxyPortLabel);
	DDX_Control(pDX, IDC_UseProxy, m_UseProxy);
	DDX_Control(pDX, IDC_UpdateCheck, m_UpdateCheck);
	DDX_Control(pDX, IDC_ProxyServer, m_ProxyServer);
	DDX_Control(pDX, IDC_ProxyPort, m_ProxyPort);
	DDX_Control(pDX, IDC_NetworkTimeout, m_NetworkTimeout);
	DDX_Control(pDX, IDC_InternetCheck, m_InternetCheck);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(COptionsInternet, CPropertyPage)
	//{{AFX_MSG_MAP(COptionsInternet)
	ON_BN_CLICKED(IDC_UseProxy, OnUseProxy)
	ON_EN_CHANGE(IDC_InternetCheck, OnChangeInternetCheck)
	ON_EN_CHANGE(IDC_NetworkTimeout, OnChangeNetworkTimeout)
	ON_EN_CHANGE(IDC_ProxyPort, OnChangeProxyPort)
	ON_EN_CHANGE(IDC_ProxyServer, OnChangeProxyServer)
	ON_BN_CLICKED(IDC_UpdateCheck, OnUpdateCheck)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// COptionsInternet message handlers

BOOL COptionsInternet::OnInitDialog() 
{
	CPropertyPage::OnInitDialog();
	
	// TODO: Add extra initialization here

	CString temp;

	temp.Format("%i", GetDefaultTimeout());
	m_NetworkTimeout.SetWindowText(temp);

	temp.Format("%i", GetCheckConnection());
	m_InternetCheck.SetWindowText(temp);

	m_UpdateCheck.SetCheck(GetCheckNewerVersion());

	if(GetUseProxy())
	{
		m_UseProxy.SetCheck(1);
		GetProxyServer(temp);
		m_ProxyServer.SetWindowText(temp);
		temp.Format("%i", GetProxyPort());
		m_ProxyPort.SetWindowText(temp);
	}
	else
	{
		m_UseProxy.SetCheck(0);
		m_ProxyServerLabel.EnableWindow(FALSE);
		m_ProxyServer.EnableWindow(FALSE);
		m_ProxyPortLabel.EnableWindow(FALSE);
		m_ProxyPort.EnableWindow(FALSE);
	}
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void COptionsInternet::OnUseProxy() 
{
	// TODO: Add your control notification handler code here

	SetModified();

	if(m_UseProxy.GetCheck())
	{
		m_ProxyServerLabel.EnableWindow(TRUE);
		m_ProxyServer.EnableWindow(TRUE);
		m_ProxyPortLabel.EnableWindow(TRUE);
		m_ProxyPort.EnableWindow(TRUE);
	}
	else
	{
		m_ProxyServerLabel.EnableWindow(FALSE);
		m_ProxyServer.EnableWindow(FALSE);
		m_ProxyPortLabel.EnableWindow(FALSE);
		m_ProxyPort.EnableWindow(FALSE);
	}
}

BOOL COptionsInternet::OnKillActive()
{
	CString temp; int x;

	/* Check the network timeout value - Must be between 15 and 60 */

	m_NetworkTimeout.GetWindowText(temp);
	x = atoi(temp);

	if(x < 15 || x > 60)
	{
		MessageBox("Network Timeout must be a value between 15 and 60 seconds", "Error", MB_OK | MB_ICONEXCLAMATION);
		return 0;
	}

	/* Check the Internet check value - Must be between 5 and 30 */

	m_InternetCheck.GetWindowText(temp);
	x = atoi(temp);

	if(x < 5 || x > 30)
	{
		MessageBox("Internet check value must be between 5 and 30 seconds", "Error", MB_OK | MB_ICONEXCLAMATION);
		return 0;
	}

	/* Check the Proxy server name and port number */

	if(m_UseProxy.GetCheck())
	{
		m_ProxyServer.GetWindowText(temp);
		temp.TrimLeft(); temp.TrimRight();

		if(temp.GetLength() == 0)
		{
			MessageBox("Must provide a proxy server", "Error", MB_OK | MB_ICONEXCLAMATION);
			return 0;
		}

		m_ProxyPort.GetWindowText(temp);
		x = atoi(temp);
		if(x > 65535)
		{
			MessageBox("Proxy server port number must be less than 65536", "Error", MB_OK | MB_ICONEXCLAMATION);
			return 0;
		}
	}

	return 1;
}

/* Write the options to the registry */

void COptionsInternet::OnOK()
{
	CString temp;

	m_InternetCheck.GetWindowText(temp);
	SetCheckConnection(atoi(temp));

	m_NetworkTimeout.GetWindowText(temp);
	SetDefaultTimeout(atoi(temp));

	SetUseProxy(m_UseProxy.GetCheck());

	if(m_UseProxy.GetCheck())
	{
		m_ProxyServer.GetWindowText(temp);
		SetProxyServer(temp);
		m_ProxyPort.GetWindowText(temp);
		SetProxyPort(atoi(temp));
	}

	SetCheckNewerVersion(m_UpdateCheck.GetCheck());
}

void COptionsInternet::OnChangeInternetCheck() 
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CPropertyPage::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.
	
	// TODO: Add your control notification handler code here
	
	SetModified();
}

void COptionsInternet::OnChangeNetworkTimeout() 
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CPropertyPage::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.
	
	// TODO: Add your control notification handler code here
	
	SetModified();
}

void COptionsInternet::OnChangeProxyPort() 
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CPropertyPage::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.
	
	// TODO: Add your control notification handler code here
	
	SetModified();
}

void COptionsInternet::OnChangeProxyServer() 
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CPropertyPage::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.
	
	// TODO: Add your control notification handler code here
	
	SetModified();
}

void COptionsInternet::OnUpdateCheck() 
{
	// TODO: Add your control notification handler code here
	
	SetModified();
}
