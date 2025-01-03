// Update.cpp : implementation file
//

#include "stdafx.h"
#include "KCCI.h"
#include "Update.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CUpdate dialog


CUpdate::CUpdate(CWnd* pParent /*=NULL*/)
	: CDialog(CUpdate::IDD, pParent)
{
	//{{AFX_DATA_INIT(CUpdate)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CUpdate::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CUpdate)
	DDX_Control(pDX, IDC_Camera, m_Camera);
	DDX_Control(pDX, IDC_SchoolNetStation, m_SchoolNetStation);
	DDX_Control(pDX, IDC_SchoolNetData, m_SchoolNetData);
	DDX_Control(pDX, IDC_Radar, m_Radar);
	DDX_Control(pDX, IDC_Forecast, m_Forecast);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CUpdate, CDialog)
	//{{AFX_MSG_MAP(CUpdate)
	ON_BN_CLICKED(IDC_SelectAll, OnSelectAll)
	ON_BN_CLICKED(IDC_SchoolNetStation, OnSchoolNetStation)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CUpdate message handlers

void CUpdate::OnSelectAll() 
{
	// TODO: Add your control notification handler code here

	m_Forecast.SetCheck(1);
	m_Radar.SetCheck(1);
	m_SchoolNetData.SetCheck(1);
	m_SchoolNetStation.SetCheck(1);
	m_SchoolNetData.EnableWindow(FALSE);
    m_Camera.SetCheck(1);	
}

BOOL CUpdate::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here

	m_SchoolNetData.SetCheck(1);
	m_Radar.SetCheck(1);
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CUpdate::OnOK() 
{
	// TODO: Add extra validation here
	
	updateSchoolNetStations = m_SchoolNetStation.GetCheck();
	updateSchoolNetData = m_SchoolNetData.GetCheck();
	updateRadarImage = m_Radar.GetCheck();
	updateForecastImage = m_Forecast.GetCheck();
    updateCameras = m_Camera.GetCheck();
	
	CDialog::OnOK();
}

void CUpdate::OnSchoolNetStation() 
{
	// TODO: Add your control notification handler code here

	if(m_SchoolNetStation.GetCheck()) m_SchoolNetData.EnableWindow(FALSE);
	else m_SchoolNetData.EnableWindow();
	
}
