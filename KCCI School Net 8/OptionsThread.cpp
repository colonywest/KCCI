// OptionsThread.cpp : implementation file
//

#include "stdafx.h"
#include "KCCI.h"
#include "OptionsThread.h"

#include "MoveControls.h"
#include "Registry.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// COptionsThread

IMPLEMENT_DYNCREATE(COptionsThread, CWinThread)

COptionsThread::COptionsThread()
{
}

COptionsThread::~COptionsThread()
{
}

BOOL COptionsThread::InitInstance()
{
	// TODO:  perform and per-thread initialization here

	TRACE("COptionsThread starting\n");

	/* Create the property sheet and property pages */

	generalTab = new COptionsGeneral;
	schoolNet = new COptionsSchoolNet;
	radar = new COptionsRadar;
	webCam = new COptionsWebCam;
	internet = new COptionsInternet;

	optionsSheet = new COptionsSheet("Options");

	/* Set the exit code to IDCANCEL in case the thread is forcefully closed */

	optionsSheet->exitCode = IDCANCEL;

	/* Take care of some internal variables */

	schoolNet->stationList = &kcci->schoolNetStations;
	webCam->cameraList = &kcci->cameraList;

	/* Removes the Help button from the sheet */

	optionsSheet->m_psh.dwFlags &= ~(PSH_HASHELP);

	/* Removes the Help buttons from each of the pages */

	generalTab->m_psp.dwFlags &= ~(PSP_HASHELP);
	schoolNet->m_psp.dwFlags &= ~(PSP_HASHELP);
	radar->m_psp.dwFlags &= ~(PSP_HASHELP);
	webCam->m_psp.dwFlags &= ~(PSP_HASHELP);
	internet->m_psp.dwFlags &= ~(PSP_HASHELP);

	/* Adds each of the pages to the property sheet */

	optionsSheet->AddPage(generalTab);
	optionsSheet->AddPage(schoolNet);
	optionsSheet->AddPage(radar);
	optionsSheet->AddPage(webCam);
	optionsSheet->AddPage(internet);

	/* Displays the dialog */

	if(!optionsSheet->Create()) return FALSE;
	m_pMainWnd = optionsSheet;
	optionsSheet->SetActivePage(0);

	return TRUE;
}

int COptionsThread::ExitInstance()
{
	// TODO:  perform any per-thread cleanup here

	/* If the current view has changed, we need to start a background thread to
	 * change the current display setting.  If they didn't change, then this will
	 * only flicker the main window.
	 */

	if(optionsSheet->exitCode)
	{
		MoveControls(kcci);

		/* This will update the timers if they changed */

		if(GetSchoolNetUpdateInterval() != kcci->timerSchoolNet)
		{
			KillTimer(kcci->m_hWnd, 95633);
			//kcci->KillTimer(95633); 
			kcci->timerSchoolNet = GetSchoolNetUpdateInterval();
			kcci->SetTimer(95633, kcci->timerSchoolNet * 60000, NULL);
		}

		if(GetRadarUpdateInterval() != kcci->timerRadar)
		{
			kcci->timerRadar = GetRadarUpdateInterval(); 
			//kcci->KillTimer(95632);
			KillTimer(kcci->m_hWnd, 95632);
			kcci->SetTimer(95632, kcci->timerRadar * 60000, NULL);
		}
/*
		if(GetCheckConnection() != kcci->timerInternet)
		{
			kcci->timerInternet = GetCheckConnection(); kcci->KillTimer(95631);
			kcci->SetTimer(95631, kcci->timerInternet * 1000, NULL);
		}
*/
    }

	optionsSheet->DestroyWindow();

	delete optionsSheet;
	delete generalTab;
	delete schoolNet;
	delete radar;
	delete webCam;
	delete internet;

	TRACE("Exiting COptionsThread\n");

	return CWinThread::ExitInstance();
}

BEGIN_MESSAGE_MAP(COptionsThread, CWinThread)
	//{{AFX_MSG_MAP(COptionsThread)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// COptionsThread message handlers
