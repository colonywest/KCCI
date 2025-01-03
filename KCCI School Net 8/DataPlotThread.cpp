// DataPlotThread.cpp : implementation file
//

#include "stdafx.h"
#include "KCCI.h"
#include "DataPlotThread.h"

#include "FeaturetteProgress.h"
#include "PopulateLists.h"

#include "BinaryString.h"
#include "SString.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDataPlotThread

IMPLEMENT_DYNCREATE(CDataPlotThread, CWinThread)

CDataPlotThread::CDataPlotThread()
{
}

CDataPlotThread::~CDataPlotThread()
{
}

bool DownloadData(const char *, BinaryString & , CFeaturetteProgress & );

BOOL CDataPlotThread::InitInstance()
{
	// TODO:  perform and per-thread initialization here

	BinaryString output; SString imageURL;
	CFeaturetteProgress featuretteProgress;
	bool downloadSucceeded; CString stationID;

	dataPlotDlg = new CDataPlot();
	m_pMainWnd = dataPlotDlg;

	FindStationID(currentStation, * stations, stationID);
	imageURL = "http://www.schoolnet8.com/GIS/apps/radar/site.php?station=";
	imageURL += stationID;
	imageURL += "&var=tmpf";

	featuretteProgress.Create(IDD_FeaturetteProgress);
	featuretteProgress.m_Featurette.SetWindowText("Downloading data plot...");

	featuretteProgress.ShowWindow(SW_NORMAL);
	featuretteProgress.UpdateWindow();

	downloadSucceeded = DownloadData(imageURL, output, featuretteProgress);
	featuretteProgress.DestroyWindow();

	if(! downloadSucceeded)
	{
		MessageBox(NULL, "Error downloading image", "Error", MB_OK | MB_ICONEXCLAMATION);
		return FALSE;
	}

	dataPlotDlg->image.Decode((BYTE *)(const unsigned char *)output, output.length(), CXIMAGE_FORMAT_PNG);

	dataPlotDlg->stations = stations;
	dataPlotDlg->currentStation = currentStation;


	dataPlotDlg->Create(IDD_DataPlot);
	dataPlotDlg->ShowWindow(SW_NORMAL);

	return TRUE;
}

int CDataPlotThread::ExitInstance()
{
	// TODO:  perform any per-thread cleanup here

	TRACE("Exiting CDataPlotThread\n");

	dataPlotDlg->DestroyWindow();	
	delete dataPlotDlg;

	return CWinThread::ExitInstance();
}

BEGIN_MESSAGE_MAP(CDataPlotThread, CWinThread)
	//{{AFX_MSG_MAP(CDataPlotThread)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDataPlotThread message handlers

