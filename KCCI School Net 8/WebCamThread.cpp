// WebCamThread.cpp : implementation file
//

#include "stdafx.h"
#include "KCCI.h"

#include "WebCamThread.h"
#include "WebCam.h"

#include "FeaturetteProgress.h"
#include "KCCISchoolNet.h"

#include "BinaryString.h"
#include "SString.h"
#include "Registry.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CWebCamThread

IMPLEMENT_DYNCREATE(CWebCamThread, CWinThread)

CWebCamThread::CWebCamThread()
{
}

CWebCamThread::~CWebCamThread()
{
}

bool DownloadData(const char *, BinaryString &, CFeaturetteProgress &);

BOOL CWebCamThread::InitInstance()
{
	// TODO:  perform and per-thread initialization here

	BinaryString output; SString imageURL;
	CFeaturetteProgress featuretteProgress;
	bool downloadSucceeded; CString stationID;

    webcam = NULL;

	KCCICameraList * camera = (KCCICameraList *)webcams->elementAt(GetDefaultWebCam());
    if(camera == NULL) return FALSE;

	webcam = new CWebCam;
	m_pMainWnd = webcam;

	featuretteProgress.Create(IDD_FeaturetteProgress);
	featuretteProgress.m_Featurette.SetWindowText("Downloading web cam image...");

	featuretteProgress.ShowWindow(SW_NORMAL);
	featuretteProgress.UpdateWindow();

	downloadSucceeded = DownloadData(camera->stationURL, output, featuretteProgress);
	featuretteProgress.DestroyWindow();

	if(! downloadSucceeded)
	{
		MessageBox(NULL, "Error downloading image", "Error", MB_OK | MB_ICONEXCLAMATION);
		return FALSE;
	}

	webcam->image.Decode((BYTE *)(const unsigned char *)output, output.length(), CXIMAGE_FORMAT_UNKNOWN);

	webcam->cams = webcams;
	webcam->Create(IDD_WebCam, NULL);
	webcam->ShowWindow(SW_NORMAL);

	return TRUE;
}

int CWebCamThread::ExitInstance()
{
	// TODO:  perform any per-thread cleanup here

	if(webcam) webcam->DestroyWindow();
	delete webcam;

	TRACE("Exiting CWebCamThread\n");

	return CWinThread::ExitInstance();
}

BEGIN_MESSAGE_MAP(CWebCamThread, CWinThread)
	//{{AFX_MSG_MAP(CWebCamThread)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CWebCamThread message handlers
