// DetailedThread.cpp : implementation file
//

#include "stdafx.h"
#include "KCCI.h"
#include "DetailedThread.h"
#include "Detailed.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDetailedThread

IMPLEMENT_DYNCREATE(CDetailedThread, CWinThread)

CDetailedThread::CDetailedThread()
{
}

CDetailedThread::~CDetailedThread()
{
	TRACE("CDetailedThread Destructor called\n");
}

BOOL CDetailedThread::InitInstance()
{
	// TODO:  perform and per-thread initialization here

	if(!AfxInitRichEdit()) return FALSE;

	detailed = new CDetailed;
	m_pMainWnd = detailed;

	/* Add the code to stream in the details before calling DoModal */

	detailed->data = data;
	detailed->station = station;

	detailed->Create(IDD_Detailed);
	detailed->ShowWindow(SW_NORMAL);

	return TRUE;
}

int CDetailedThread::ExitInstance()
{
	// TODO:  perform any per-thread cleanup here

	detailed->DestroyWindow();
	delete detailed;

	TRACE("Exiting CDetailedThread\n");

	return CWinThread::ExitInstance();
}

BEGIN_MESSAGE_MAP(CDetailedThread, CWinThread)
	//{{AFX_MSG_MAP(CDetailedThread)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDetailedThread message handlers
