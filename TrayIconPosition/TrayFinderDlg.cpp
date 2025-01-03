// TrayFinderDlg.cpp : implementation file
//

#include "stdafx.h"
#include "TrayFinder.h"
#include "TrayFinderDlg.h"
#include "BalloonHelp.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	//{{AFX_MSG(CAboutDlg)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
		// No message handlers
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTrayFinderDlg dialog

CTrayFinderDlg::CTrayFinderDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CTrayFinderDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CTrayFinderDlg)
	m_iTrackType = 0;
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CTrayFinderDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CTrayFinderDlg)
	DDX_Radio(pDX, IDC_RADIO1, m_iTrackType);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CTrayFinderDlg, CDialog)
	//{{AFX_MSG_MAP(CTrayFinderDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_ADD, OnAdd)
	ON_BN_CLICKED(IDC_DELETE, OnDelete)
	ON_WM_DESTROY()
	ON_BN_CLICKED(IDC_CALCULATE, OnCalculate)
	ON_BN_CLICKED(IDC_IZSOFT, OnIzsoft)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTrayFinderDlg message handlers

BOOL CTrayFinderDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
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
	
	// TODO: Add extra initialization here
	
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CTrayFinderDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CTrayFinderDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CTrayFinderDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CTrayFinderDlg::OnAdd() 
{
	  NOTIFYICONDATA nid; 
	  nid.cbSize = sizeof(nid); 
	  nid.hWnd = m_hWnd; 
	  nid.uID = 1; 
	  nid.uFlags = NIF_ICON|NIF_TIP; 
	  strncpy(nid.szTip, "Our icon in tray :-D", 64);
	  nid.hIcon = AfxGetApp()->LoadIcon(IDI_TRAY_HELPER);
	  Shell_NotifyIcon(NIM_ADD, &nid);

	  //let's initialize tray icon position tracking
	  //second argument it's ID of icon (nid.uID)
	  m_tipPosition.InitializePositionTracking(m_hWnd,1);
}

void CTrayFinderDlg::OnDelete() 
{
	  NOTIFYICONDATA nid; 
	  nid.cbSize = sizeof(nid); 
	  nid.hWnd = m_hWnd; 
	  nid.uID = 1; 
	  Shell_NotifyIcon(NIM_DELETE, &nid);	
}

void CTrayFinderDlg::OnDestroy() 
{
	CDialog::OnDestroy();
	OnDelete();
}

void CTrayFinderDlg::OnCalculate() 
{
	UpdateData();
	
	CTrayIconPosition::TrackType eTrackType = CTrayIconPosition::UseBothTechniquesDirectPrefered;
	
	switch (m_iTrackType) {
	case 0:
		eTrackType = CTrayIconPosition::UseBothTechniquesDirectPrefered;	
		break;
	case 1:
		eTrackType = CTrayIconPosition::UseDirectOnly;
		break;
	case 2:
		eTrackType = CTrayIconPosition::UseVisualScanOnly;
		break;
	default:
		ASSERT(0);
		break;
	}



	//use m_tipPosition.Invalidate(); if you want to avoid few-seconds postion cashing (visual scan mode only)

	CPoint ptIcon;
	BOOL bIconFound = m_tipPosition.GetTrayIconPosition(ptIcon, eTrackType);

	if(bIconFound == -1)
	{
		AfxMessageBox("There is no icon to track!\nInitialize CTrayIconPosition before!");
		return;
	}

	//GetTrayIconPosition in order to find out position sets a black icon in tray - let's restore it now
	//This code commes from my application Tray Helper (http://www.trayhelper.com) and if you want you can easy
	//change it to auto-restore previous icon. In my application tray icon isn't static so I reset previous icon manualy:
	m_tipPosition.RestoreTrayIcon(AfxGetApp()->LoadIcon(IDI_TRAY_HELPER));
	
	if(bIconFound)
	{
		//we were able to find out icon on the screen
		CString str;
		str.Format("We were able to find out position of the tray icon!\nIt's located at: X:[%d] Y:[%d]", ptIcon.x, ptIcon.y);
		CBalloonHelp::LaunchBalloon("CTrayIconPosition class demonstration", str, ptIcon);
	}
	else
	{
		//we were not able to find out position of icon - but in 99% of times this function returns usefull data
		CString str;
		str.Format("We were NOT ABLE to find out position of the tray icon!\nMaybe we're under Windows XP and our icon is hidden ?\nBut the best place to display our balloon is:\nX:[%d] Y:[%d]", ptIcon.x, ptIcon.y);
		CBalloonHelp::LaunchBalloon("CTrayIconPosition class demonstration", str, ptIcon);
	}
}

void CTrayFinderDlg::OnIzsoft() 
{
	ShellExecute(NULL,"open","http://www.trayhelper.com/indexeng.html",NULL,NULL,SW_SHOWNORMAL);	
}
