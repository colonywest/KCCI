// OptionsGeneral.cpp : implementation file
//

#include "stdafx.h"
#include "KCCI.h"
#include "OptionsGeneral.h"

#include "Registry.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// COptionsGeneral property page

IMPLEMENT_DYNCREATE(COptionsGeneral, CPropertyPage)

COptionsGeneral::COptionsGeneral() : CPropertyPage(COptionsGeneral::IDD)
{
	//{{AFX_DATA_INIT(COptionsGeneral)
	//}}AFX_DATA_INIT
}

COptionsGeneral::~COptionsGeneral()
{
}

void COptionsGeneral::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(COptionsGeneral)
	DDX_Control(pDX, IDC_ControlPanel, m_ControlPanel);
	DDX_Control(pDX, IDC_DefaultView, m_DefaultView);
	DDX_Control(pDX, IDC_RunStart, m_RunStart);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(COptionsGeneral, CPropertyPage)
	//{{AFX_MSG_MAP(COptionsGeneral)
	ON_BN_CLICKED(IDC_RunStart, OnRunStart)
	ON_CBN_SELENDOK(IDC_DefaultView, OnSelendokDefaultView)
	ON_CBN_SELENDOK(IDC_ControlPanel, OnSelendokControlPanel)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// COptionsGeneral message handlers

BOOL COptionsGeneral::OnInitDialog() 
{
	CPropertyPage::OnInitDialog();
	
	// TODO: Add extra initialization here

	if(GetStartup()) m_RunStart.SetCheck(1);
	m_DefaultView.SetCurSel(GetDefaultView());
	m_ControlPanel.SetCurSel(GetControlPanelLocation());
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

/* An override to allow the variables to be written to the registry when OK is pressed */

void COptionsGeneral::OnOK()
{
	TRACE("COptionsGeneral::OnOK()\n");

	if(m_RunStart.GetCheck()) SetAtStartup();
	else RemoveStartup();

	SetDefaultView(m_DefaultView.GetCurSel());
	SetControlPanelLocation(m_ControlPanel.GetCurSel());
}

void COptionsGeneral::OnRunStart() 
{
	// TODO: Add your control notification handler code here

	SetModified();
}

void COptionsGeneral::OnSelendokDefaultView() 
{
	// TODO: Add your control notification handler code here

	SetModified();
}

void COptionsGeneral::OnSelendokControlPanel() 
{
	// TODO: Add your control notification handler code here
	
	SetModified();
}
