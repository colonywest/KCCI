// ashsystrayDlg.cpp : implementation file
//

#include "stdafx.h"
#include "ashsystray.h"
#include "ashsystrayDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAshsystrayDlg dialog

CAshsystrayDlg::CAshsystrayDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CAshsystrayDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CAshsystrayDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CAshsystrayDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAshsystrayDlg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAshsystrayDlg, CDialog)
	//{{AFX_MSG_MAP(CAshsystrayDlg)
	ON_MESSAGE(WM_TRAY_NOTIFY, OnTrayNotify)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_COMMAND(ID_TRAY_RESTORE, OnTrayRestore)
	ON_BN_CLICKED(IDC_HIDEAPP, OnHideapp)
	ON_COMMAND(IDCANCEL,CANCEL)
	ON_BN_CLICKED(ID_APP_EXIT, OnAppExit)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CAshsystrayDlg message handlers

BOOL CAshsystrayDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	OnHide();
	
		
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CAshsystrayDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
//		CAboutDlg dlgAbout; Who needs this? NOT MEEEE
		//dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

void CAshsystrayDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}


HCURSOR CAshsystrayDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

/*Modified tray code
What it has been modified to do it to set the state of the program as active in the system tray.
Upon minimising it, it is returned to the system tray.
*/

void CAshsystrayDlg::OnHide() 
{
	// Load icon onto taskbar tray
	m_pTray = new CTrayNot (this,WM_TRAY_NOTIFY,
	NULL,theApp.m_pIconList);
	m_pTray->SetState(IDR_MAINFRAME);
	m_bHidden = TRUE;
		
}

void CAshsystrayDlg::OnUnHide()
{
	ShowWindow (SW_RESTORE) ;
	m_bHidden = FALSE ;
	/////////////////////////////////////
	// Remove icon from taskbar tray
	if (m_pTray)
	{
		delete m_pTray ;
		m_pTray = NULL ;
	}
}


LONG CAshsystrayDlg::OnTrayNotify ( WPARAM wParam, LPARAM lParam )
{
	switch (lParam)
	{
		case WM_RBUTTONDOWN:
		{
			CMenu menu ;
			/////////////////////////////////////
			// Load and Verify Menu
			VERIFY(menu.LoadMenu(IDR_TRAY));
			CMenu* pPopup = menu.GetSubMenu (0) ;
			ASSERT(pPopup != NULL);

			// Get the cursor position
			POINT pt ;
			GetCursorPos (&pt) ;

			// Fix Microsofts' BUG!!!!
			SetForegroundWindow();

			///////////////////////////////////
			// Display The Menu
			pPopup->TrackPopupMenu(TPM_LEFTALIGN |
			TPM_RIGHTBUTTON,pt.x, pt.y, AfxGetMainWnd());
				break ;
		}
		case WM_LBUTTONDBLCLK:
			//////////////////////////////////
			// Unhide our Window
			if (m_bHidden)
				ShowWindow (SW_RESTORE);
				//OnUnHide() ;
				break ;
		}
			return (0) ;
}

void CAshsystrayDlg::OnDestroy() 
{
	CDialog::OnDestroy();
	
	// Remove Icon from Tray
	if (m_pTray)
	{
		delete m_pTray ;
		m_pTray = NULL ;
	}	
}

void CAshsystrayDlg::OnTrayRestore() 
{
	// UnHide Application
	if (m_bHidden)
	ShowWindow (SW_RESTORE) ;
	m_bHidden = FALSE ;
	//OnTrayRestore();		
}

void CAshsystrayDlg::OnHideapp() 
{
	//This will be the onclick for the hide button
	//in order to call that the app is minimised.
	theApp.HideApplication() ;
}

void CAshsystrayDlg::CANCEL()
{
	int msg = MessageBox("Vote for me so I get a T-Shirt","Did this help?",MB_ICONQUESTION|MB_YESNO);
	switch(msg)
	{
	case IDYES:
	delete m_pTray ;
		DestroyWindow();
		break;
	case IDNO:
		break;
	}
}

void CAshsystrayDlg::OnAppExit() 
{
	// TODO: Add your control notification handler code here
	CANCEL();
}
