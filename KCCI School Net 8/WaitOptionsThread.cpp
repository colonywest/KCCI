// WaitOptionsThread.cpp : implementation file
//

#include "stdafx.h"
#include "KCCI.h"
#include "WaitOptionsThread.h"

#include "Registry.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CWaitOptionsThread

IMPLEMENT_DYNCREATE(CWaitOptionsThread, CWinThread)

CWaitOptionsThread::CWaitOptionsThread()
{
}

CWaitOptionsThread::~CWaitOptionsThread()
{
}

BOOL CWaitOptionsThread::InitInstance()
{
	// TODO:  perform and per-thread initialization here

	internet = new COptionsInternet();
	optionsSheet = new COptionsSheet("Options");

	optionsSheet->exitCode = IDCANCEL;

	/* Removes the Help button from the sheet */

	optionsSheet->m_psh.dwFlags &= ~(PSH_HASHELP);

	/* Removes the Help buttons from each of the pages */

	internet->m_psp.dwFlags &= ~(PSP_HASHELP);

	optionsSheet->AddPage(internet);

	/* Sets the title and displays the dialog */

	if(!optionsSheet->Create()) return FALSE;
	m_pMainWnd = optionsSheet;
	optionsSheet->SetActivePage(0);

	return TRUE;
}

int CWaitOptionsThread::ExitInstance()
{
	// TODO:  perform any per-thread cleanup here

	if(optionsSheet->exitCode)
	{
		int timer = GetCheckConnection();
		if(GetCheckConnection() != timer)
		{
			timer = GetCheckConnection(); wait->KillTimer(95631);
			wait->SetTimer(95631, timer * 1000, NULL);
		}
	}

	optionsSheet->DestroyWindow();
	
	delete internet;
	delete optionsSheet;

	TRACE("Exiting CWaitOptionsThread\n");

	return CWinThread::ExitInstance();
}

BEGIN_MESSAGE_MAP(CWaitOptionsThread, CWinThread)
	//{{AFX_MSG_MAP(CWaitOptionsThread)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CWaitOptionsThread message handlers
