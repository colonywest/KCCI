// DataPlot.cpp : implementation file
//

#include "stdafx.h"
#include "KCCI.h"

#include "FeaturetteProgress.h"

#include "DataPlot.h"
#include "PopulateLists.h"


#include "Registry.h"
#include "UpdateData.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDataPlot dialog


CDataPlot::CDataPlot(CWnd* pParent /*=NULL*/)
	: CDialog(CDataPlot::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDataPlot)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CDataPlot::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDataPlot)
	DDX_Control(pDX, IDC_Progress, m_Progress);
	DDX_Control(pDX, IDC_View, m_View);
	DDX_Control(pDX, IDC_Variable, m_Variable);
	DDX_Control(pDX, IDC_Station, m_Station);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDataPlot, CDialog)
	//{{AFX_MSG_MAP(CDataPlot)
	ON_WM_TIMER()
	ON_CBN_SELENDOK(IDC_Station, OnSelendokStation)
	ON_CBN_SELENDOK(IDC_Variable, OnSelendokVariable)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDataPlot message handlers

bool DownloadData(const char *, BinaryString &);
bool DownloadData(const char *, BinaryString & , CFeaturetteProgress & );

BOOL CDataPlot::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here

	m_Progress.ShowWindow(SW_HIDE);

	PopulateStationList(* stations, m_Station);
	m_Station.SetCurSel(currentStation);
	m_Variable.SetCurSel(0);

	m_View.SetBitmap(image.MakeBitmap());

	SetTimer(WM_APP + 2, GetDataPlotUpdateInterval() * 60 * 1000, NULL);
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CDataPlot::OnTimer(UINT nIDEvent) 
{
	// TODO: Add your message handler code here and/or call default

	if(nIDEvent == WM_APP + 2) OnSelendokStation();
	else CDialog::OnTimer(nIDEvent);
}

void MapVariable(int var, CString & out)
{
	switch(var)
	{
	default:
	case 0: out = "tmpf"; break;
	case 1: out = "dwpf"; break;
	case 2: out = "relh"; break;
	case 3: out = "feel"; break;
	case 4: out = "alti"; break;
	case 5: out = "sped"; break;
	case 6: out = "gmph"; break;
	case 7: out = "tmpf_max"; break;
	case 8: out = "tmpf_min"; break;
	}
}

void CDataPlot::OnSelendokStation() 
{
	// TODO: Add your control notification handler code here

	/* Change of station, so get the new station ID, the current variable, and go */

	int * array = new int [5];
	char * p;

	CString stationID; SString imageURL;
	CString var; BinaryString output;

	FindStationID(m_Station.GetCurSel(), * stations, stationID);
	MapVariable(m_Variable.GetCurSel(), var);
	imageURL = "http://www.schoolnet8.com/GIS/apps/radar/site.php?station=";
	imageURL += stationID; imageURL += "&var="; imageURL += var;

	p = new char [imageURL.length() + 1];
	strcpy(p, imageURL);

	/* In this case, the dummy is an array of integers, all of which are pointers.
	 * The first is a pointer to the URL to download the image, the second is a pointer
	 * to the CxImage object to render the image, the third is a pointer to the
	 * progress bar, the fourth is a pointer to a CDialog object, and the fifth is a
	 * pointer to a CStatic object (the image view).
	 */

	array[0] = (int ) p;
	array[1] = (int ) & image;
	array[2] = (int ) & m_Progress;
	array[3] = (int ) this;
	array[4] = (int ) & m_View;

	AfxBeginThread(UpdateFeaturetteImage, array);
}

void CDataPlot::OnSelendokVariable() 
{
	// TODO: Add your control notification handler code here

	OnSelendokStation();

}

void CDataPlot::OnOK() 
{
	// TODO: Add extra validation here

	/* Wait for the progress bar to disappear, if it is visible */

	for( ; m_Progress.IsWindowVisible(); );
	PostMessage(WM_QUIT);
	
	// CDialog::OnOK();
}
