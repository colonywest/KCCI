// OptionsRadar.cpp : implementation file
//

#include "stdafx.h"
#include "KCCI.h"
#include "OptionsRadar.h"

#include "Registry.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// COptionsRadar property page

IMPLEMENT_DYNCREATE(COptionsRadar, CPropertyPage)

COptionsRadar::COptionsRadar() : CPropertyPage(COptionsRadar::IDD)
{
	//{{AFX_DATA_INIT(COptionsRadar)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}

COptionsRadar::~COptionsRadar()
{
}

void COptionsRadar::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(COptionsRadar)
	DDX_Control(pDX, IDC_RadarUpdate, m_RadarUpdate);
	DDX_Control(pDX, IDC_DisableWhenMinimized, m_DisableWhenMinimized);
	DDX_Control(pDX, IDC_DisableRadarUpdate, m_DisableRadarUpdate);
	DDX_Control(pDX, IDC_DefaultRadar, m_DefaultRadar);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(COptionsRadar, CPropertyPage)
	//{{AFX_MSG_MAP(COptionsRadar)
	ON_BN_CLICKED(IDC_DisableRadarUpdate, OnDisableRadarUpdate)
	ON_BN_CLICKED(IDC_DisableWhenMinimized, OnDisableWhenMinimized)
	ON_EN_CHANGE(IDC_RadarUpdate, OnChangeRadarUpdate)
	ON_CBN_SELENDOK(IDC_DefaultRadar, OnSelendokDefaultRadar)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// COptionsRadar message handlers

BOOL COptionsRadar::OnInitDialog() 
{
	CPropertyPage::OnInitDialog();
	
	// TODO: Add extra initialization here

	CString temp;

	m_DefaultRadar.SetCurSel(GetDefaultRadarImage());
	m_DisableWhenMinimized.SetCheck(GetDisableRadarWhenMinimized());
	m_DisableRadarUpdate.SetCheck(GetDisableRadarUpdate());

	temp.Format("%i", GetRadarUpdateInterval());
	m_RadarUpdate.SetWindowText(temp);
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

BOOL COptionsRadar::OnKillActive()
{
	CString temp; int x;

	m_RadarUpdate.GetWindowText(temp);
	x = atoi(temp);

	if(x < 1 || x > 60)
	{
		MessageBox("Radar update interval must be between 1 and 60 minutes", "Error", MB_OK | MB_ICONEXCLAMATION);
		return 0;
	}

	return 1;
}

void COptionsRadar::OnOK()
{
	CString temp;

	/* Write everything to the registry */

	SetDefaultRadarImage(m_DefaultRadar.GetCurSel());
	SetDisableRadarUpdate(m_DisableRadarUpdate.GetCheck());
	SetDisableRadarWhenMinimized(m_DisableWhenMinimized.GetCheck());
	
	m_RadarUpdate.GetWindowText(temp);
	SetRadarUpdateInterval(atoi(temp));
}

void COptionsRadar::OnDisableRadarUpdate() 
{
	// TODO: Add your control notification handler code here
	
	SetModified();
}

void COptionsRadar::OnDisableWhenMinimized() 
{
	// TODO: Add your control notification handler code here
	
	SetModified();
}

void COptionsRadar::OnChangeRadarUpdate() 
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CPropertyPage::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.
	
	// TODO: Add your control notification handler code here
	
	SetModified();
}

void COptionsRadar::OnSelendokDefaultRadar() 
{
	// TODO: Add your control notification handler code here
	
	SetModified();
}
