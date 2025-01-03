// Waiting.cpp : implementation file
//

#include "stdafx.h"
#include "KCCI.h"
#include "Waiting.h"

#include "CheckConnection.h"
#include "Registry.h"
#include "WaitOptionsThread.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CWaiting dialog


CWaiting::CWaiting(CWnd* pParent /*=NULL*/)
	: CDialog(CWaiting::IDD, pParent)
{
	//{{AFX_DATA_INIT(CWaiting)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CWaiting::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CWaiting)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}

extern UINT WM_TASKBARCREATED;
#define WM_TRAYNOTIFY (WM_APP + 10)

BEGIN_MESSAGE_MAP(CWaiting, CDialog)
	//{{AFX_MSG_MAP(CWaiting)
	ON_WM_TIMER()
	ON_WM_DESTROY()
	ON_WM_SIZE()
	ON_REGISTERED_MESSAGE(WM_TASKBARCREATED, OnTaskbarCreated)
	ON_MESSAGE(WM_TRAYNOTIFY, OnTrayNotify)
	ON_COMMAND(ID_WAIT_Exit, OnWAITExit)
	ON_COMMAND(ID_WAIT_Restore, OnWAITRestore)
	ON_COMMAND(ID_WAIT_Options, OnWAITOptions)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CWaiting message handlers

void CWaiting::OnTimer(UINT nIDEvent) 
{
	// TODO: Add your message handler code here and/or call default

	if(nIDEvent == 95631)
	{
		/* Make sure we're not currently checking the connection. Check the
		 * exit code of the thread.  If the thread is still active, abort.
		 */
/*
		if(checkConnection)
		{
			DWORD exitCode;
			GetExitCodeThread(checkConnection->m_hThread, & exitCode);
			if(exitCode == STILL_ACTIVE) return;
			delete checkConnection;
		}

		checkConnection = AfxBeginThread(WaitingCheckConnection, this, 0, CREATE_SUSPENDED);
		checkConnection->m_bAutoDelete = FALSE;
		checkConnection->ResumeThread();
*/
	}
	else CDialog::OnTimer(nIDEvent);
}

BOOL CWaiting::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here

	/* Add a timer to check for an Internet connection every so many seconds
	 */

	SetTimer(95631, GetCheckConnection() * 1000, NULL);

	HICON hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	this->SetIcon(hIcon, TRUE);

	tray = new CTrayNot(this, WM_TRAYNOTIFY, "KCCI School Net 8", & hIcon);
	tray->SetState();

	waitOptionsThread = NULL;
	checkConnection = NULL;
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CWaiting::OnDestroy() 
{
	CDialog::OnDestroy();
	
	// TODO: Add your message handler code here

	/* Is the options dialog open, if so, kill it */

	if(waitOptionsThread)
	{
		DWORD exitCode = STILL_ACTIVE;
		waitOptionsThread->PostThreadMessage(WM_QUIT, 0, 0);
		for( ; exitCode == STILL_ACTIVE; )
			GetExitCodeThread(waitOptionsThread->m_hThread, & exitCode);
		delete waitOptionsThread;
	}

	/* Are we checking for an active connection? Wait till it's done. */

	if(checkConnection)
	{
		DWORD exitCode = STILL_ACTIVE;
		for( ; exitCode == STILL_ACTIVE; )
			GetExitCodeThread(checkConnection->m_hThread, & exitCode);
		delete checkConnection;
	}

	delete tray;
}

void CWaiting::OnSize(UINT nType, int cx, int cy) 
{
	CDialog::OnSize(nType, cx, cy);
	
	// TODO: Add your message handler code here

	if(nType == SIZE_MINIMIZED) ShowWindow(SW_HIDE);
	
}

void CWaiting::OnTaskbarCreated()
{
	tray->SetState();
}

void CWaiting::OnTrayNotify(WPARAM wParam, LPARAM lParam)
{
	switch(lParam)
	{

	case WM_RBUTTONDOWN:
	{
		CMenu menu, * popup;
		POINT pt;

		/* Load and verify the menu */

		VERIFY(menu.LoadMenu(IDR_WaitMenu));
		popup = menu.GetSubMenu(0);
		if(popup == NULL) return;
		popup->SetDefaultItem(ID_WAIT_Restore);

		/* Get the cursor position */

		GetCursorPos(& pt);
		SetForegroundWindow();

		/* Display the menu */

		popup->TrackPopupMenu(TPM_LEFTALIGN | TPM_RIGHTBUTTON, pt.x, pt.y, AfxGetMainWnd());
		break;
	}

	case WM_LBUTTONDBLCLK:

		/* Regardless of whether the window is up or not, show it and
		 * bring it to the foreground.
		 */

		ShowWindow(SW_RESTORE);
		SetForegroundWindow();
		break;
	}
}

void CWaiting::OnWAITExit() 
{
	// TODO: Add your command handler code here
	
	OnCancel();
}

void CWaiting::OnWAITRestore() 
{
	// TODO: Add your command handler code here
	
	ShowWindow(SW_RESTORE);
	SetForegroundWindow();
}

void CWaiting::OnWAITOptions() 
{
	// TODO: Add your command handler code here

	CWaitOptionsThread * thread;

	if(waitOptionsThread)
	{
		DWORD exitCode;
		GetExitCodeThread(waitOptionsThread->m_hThread, & exitCode);
		if(exitCode == STILL_ACTIVE)
		{
			waitOptionsThread->m_pMainWnd->ShowWindow(SW_NORMAL);
			waitOptionsThread->m_pMainWnd->SetForegroundWindow();
			return;
		}
		else
			delete waitOptionsThread;
	}

	thread = (CWaitOptionsThread * ) AfxBeginThread(RUNTIME_CLASS(CWaitOptionsThread), THREAD_PRIORITY_NORMAL, 0, CREATE_SUSPENDED);
	thread->wait = this;
	waitOptionsThread = thread;
	thread->m_bAutoDelete = FALSE;
	thread->parent = & waitOptionsThread;
	thread->ResumeThread();
}
