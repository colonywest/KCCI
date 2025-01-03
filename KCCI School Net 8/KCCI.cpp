// KCCI.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "KCCI.h"
#include "KCCIDlg.h"

#include <winsock2.h>

#include "KCCISchoolNet.h"
#include "Initialize.h"
#include "CheckConnection.h"
#include "Registry.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CKCCIApp

BEGIN_MESSAGE_MAP(CKCCIApp, CWinApp)
	//{{AFX_MSG_MAP(CKCCIApp)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG
	ON_COMMAND(ID_HELP, CWinApp::OnHelp)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CKCCIApp construction

CKCCIApp::CKCCIApp()
{
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}

/////////////////////////////////////////////////////////////////////////////
// The one and only CKCCIApp object

CKCCIApp theApp;
UINT WM_TASKBARCREATED;

/////////////////////////////////////////////////////////////////////////////
// CKCCIApp initialization

BOOL CKCCIApp::InitInstance()
{
	// Standard initialization
	// If you are not using these features and wish to reduce the size
	//  of your final executable, you should remove from the following
	//  the specific initialization routines you do not need.
/*
#ifdef _AFXDLL
	Enable3dControls();			// Call this when using MFC in a shared DLL
#else
	Enable3dControlsStatic();	// Call this when linking to MFC statically
#endif
*/

	CKCCIDlg * dlg;
	m_pMainWnd = NULL;

	CNewMenu::SetMenuDrawMode(CNewMenu::STYLE_XP_2003_NOBORDER);
	CNewMenu::SetSelectDisableMode(FALSE);

//	titlefont.CreatePointFont(100, _T("BankGothic Md BT"));
//	CNewMenu::SetMenuTitleFont(& titlefont);

	CWnd prevWnd; HWND hPrevWnd;
	KCCISchoolNet kcci;
	int nResponse;
	SString temp;

	/* Check for another instance.  If one exists, transfer control to it and exit. */

	hPrevWnd = FindWindow(NULL, "KCCI School Net 8");

	if(hPrevWnd)
	{
		prevWnd.Attach(hPrevWnd);
		prevWnd.ShowWindow(SW_NORMAL);
		prevWnd.SetForegroundWindow();
		prevWnd.Detach();
		return FALSE;
	}

	SetDefaults();

	/* Attempt to register the TasbarCreated message */

	WM_TASKBARCREATED = RegisterWindowMessage(_T("TaskbarCreated"));
	if(WM_TASKBARCREATED == 0)
	{
		MessageBox(NULL, "Unable to register a Windows message", "Error", MB_OK | MB_ICONEXCLAMATION);
		return FALSE;
	}

	/* Initialize the Winsock library */

	WSADATA wsaData;
	if(WSAStartup(MAKEWORD(2, 2), &wsaData))
	{
		MessageBox(NULL, "Unable to initialize Winsock", "Error", MB_OK | MB_ICONEXCLAMATION);
		return FALSE;
	}

	do
	{
		/* If the option is selected, check for a newer version */

		if(GetCheckNewerVersion())
		{
			if(CheckNewerVersion())
			{
				int y = MessageBox(NULL, "A newer version is available. Would you like to visit the web site to download it?", "New Version", MB_YESNO | MB_ICONEXCLAMATION);
				if(y == IDYES)
					ShellExecute(NULL, "open", "http://kcci.kennethballard.com/", NULL, NULL, SW_SHOWNORMAL);
			}
		}
			
		/* After exiting the wait state, if it even needed to be entered, attempt
		 * to initialize the application.
		 */

//		if(!Initialize(kcci)) break;
        Initialize(kcci);

		/* Create the main window */

		dlg = new CKCCIDlg;
		m_pMainWnd = dlg;

		/* Parse in the data */

		temp.append(kcci.schoolNetStations, kcci.schoolNetStations.length());
		temp.trim();
		ParseSchoolNetStationList(temp, dlg->schoolNetStations);

		temp.reset();
		temp.append(kcci.schoolNetData, kcci.schoolNetData.length());
		temp.trim();
		ParseSchoolNetData(temp, dlg->schoolNetData);

		temp.reset();
		temp.append(kcci.cameraList, kcci.cameraList.length());
		temp.trim();
		ParseCameraList(temp, dlg->cameraList);

		dlg->kcci = & kcci;

		nResponse = dlg->DoModal();

		/* This is to allow the dialog to be shown multiple times.  This code was found
		 * at http://www.codeguru.com/forum/showthread.php?
		 * s=c21a7fe0eca6f05d6a0b0ade51327d72&threadid=252156&perpage=15&pagenumber=3
		 * and dumps the message queue so that the dialog can be displayed again.
		 */

		MSG msg;
		while (::PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
	    {
			::TranslateMessage(&msg);
			::DispatchMessage(&msg);
	    }

		delete dlg;
		m_pMainWnd = NULL;

		/* If the response was IDOK, which is the return code for the exit button,
		 * then quit the application.  If it was IDCANCEL, then the Internet connection
		 * was lost and we need to drop into a wait state.
		 */

		if (nResponse == IDOK)
		{
			// TODO: Place code here to handle when the dialog is
			//  dismissed with OK
			break;
		}
		else if (nResponse == IDCANCEL)
		{
			// TODO: Place code here to handle when the dialog is
			//  dismissed with Cancel
		}

	} while(nResponse == IDCANCEL);

	/* Clean up after the Winsock and exit */

	WSACleanup();

	// Since the dialog has been closed, return FALSE so that we exit the
	//  application, rather than start the application's message pump.
	return FALSE;
}
