// OptionsSchoolNet.cpp : implementation file
//

#include "stdafx.h"
#include "KCCI.h"
#include "OptionsSchoolNet.h"

#include "Registry.h"
#include "PopulateLists.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// COptionsSchoolNet property page

IMPLEMENT_DYNCREATE(COptionsSchoolNet, CPropertyPage)

COptionsSchoolNet::COptionsSchoolNet() : CPropertyPage(COptionsSchoolNet::IDD)
{
	//{{AFX_DATA_INIT(COptionsSchoolNet)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}

COptionsSchoolNet::~COptionsSchoolNet()
{
}

void COptionsSchoolNet::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(COptionsSchoolNet)
	DDX_Control(pDX, IDC_TimeOld, m_TimeOld);
	DDX_Control(pDX, IDC_SchoolNetUpdate, m_SchoolNetUpdate);
	DDX_Control(pDX, IDC_DefaultStation, m_DefaultStation);
	DDX_Control(pDX, IDC_DataPlotUpdate, m_DataPlotUpdate);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(COptionsSchoolNet, CPropertyPage)
	//{{AFX_MSG_MAP(COptionsSchoolNet)
	ON_EN_CHANGE(IDC_DataPlotUpdate, OnChangeDataPlotUpdate)
	ON_CBN_SELENDOK(IDC_DefaultStation, OnSelendokDefaultStation)
	ON_EN_CHANGE(IDC_SchoolNetUpdate, OnChangeSchoolNetUpdate)
	ON_EN_CHANGE(IDC_TimeOld, OnChangeTimeOld)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// COptionsSchoolNet message handlers

BOOL COptionsSchoolNet::OnInitDialog() 
{
	CPropertyPage::OnInitDialog();
	
	// TODO: Add extra initialization here

	CString temp;

	temp.Format("%i", GetSchoolNetUpdateInterval());
	m_SchoolNetUpdate.SetWindowText(temp);

	temp.Format("%i", GetDataPlotUpdateInterval());
	m_DataPlotUpdate.SetWindowText(temp);

	temp.Format("%i", GetTimeRed());
	m_TimeOld.SetWindowText(temp);

	/* Populate the list */

	PopulateStationList(* stationList, m_DefaultStation);
	m_DefaultStation.SetCurSel(FindDefaultStation(* stationList));
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void COptionsSchoolNet::OnOK()
{
	/* Write the values to the registry */

	CString temp;

	m_SchoolNetUpdate.GetWindowText(temp);
	SetSchoolNetUpdateInterval(atoi(temp));

	FindStationID(m_DefaultStation.GetCurSel(), * stationList, temp);
	SetDefaultStation(temp);

	m_DataPlotUpdate.GetWindowText(temp);
	SetDataPlotUpdateInterval(atoi(temp));

	m_TimeOld.GetWindowText(temp);
	SetTimeRed(atoi(temp));
}

BOOL COptionsSchoolNet::OnKillActive()
{
	CString temp; int x;

	/* Check the School Net update interval */

	m_SchoolNetUpdate.GetWindowText(temp);
	x = atoi(temp);

	if(x < 1 || x > 30)
	{
		MessageBox("School Net update time must be between 1 and 30 minutes", "Error", MB_OK | MB_ICONEXCLAMATION);
		return 0;
	}

	/* Check the data plot update interval */

	m_DataPlotUpdate.GetWindowText(temp);
	x = atoi(temp);

	if(x < 1 || x > 30)
	{
		MessageBox("Data plot update time must be between 1 and 30 minutes", "Error", MB_OK | MB_ICONEXCLAMATION);
		return 0;
	}

	/* Check the time-in-red value */

	m_TimeOld.GetWindowText(temp);
	x = atoi(temp);

	if(x < 1 || x > 24)
	{
		MessageBox("Time-in-red value must be between 1 and 24 hours", "Error", MB_OK | MB_ICONEXCLAMATION);
		return 0;
	}

	return 1;
}

void COptionsSchoolNet::OnChangeDataPlotUpdate() 
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CPropertyPage::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.
	
	// TODO: Add your control notification handler code here
	
	SetModified();
}

void COptionsSchoolNet::OnSelendokDefaultStation() 
{
	// TODO: Add your control notification handler code here
	
	SetModified();
}

void COptionsSchoolNet::OnChangeSchoolNetUpdate() 
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CPropertyPage::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.
	
	// TODO: Add your control notification handler code here
	
	SetModified();
}

void COptionsSchoolNet::OnChangeTimeOld() 
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CPropertyPage::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.
	
	// TODO: Add your control notification handler code here
	
	SetModified();
}
