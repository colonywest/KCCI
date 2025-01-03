// KCCIDlg.cpp : implementation file
//

#include "stdafx.h"
#include "KCCI.h"
#include "KCCIDlg.h"
#include "Update.h"

#include <process.h>

#include "DetailedThread.h"
#include "WebCamThread.h"
#include "DataPlotThread.h"
#include "OptionsThread.h"

#include "CheckConnection.h"
#include "Registry.h"
#include "MoveControls.h"
#include "PopulateLists.h"
#include "Render.h"
#include "UpdateData.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About

class CAboutDlg : public CNewDialog
{
public:
	CAboutDlg();
	CxImage image;

// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	CStatic	m_Logo;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	//{{AFX_MSG(CAboutDlg)
	afx_msg void OnPaint();
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CNewDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	DDX_Control(pDX, IDC_Logo, m_Logo);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
	ON_WM_PAINT()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CKCCIDlg dialog

extern UINT WM_TASKBARCREATED;

CKCCIDlg::CKCCIDlg(CWnd* pParent /*=NULL*/)
	: CNewDialog(CKCCIDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CKCCIDlg)
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CKCCIDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CKCCIDlg)
	DDX_Control(pDX, IDC_Progress, m_Progress);
	DDX_Control(pDX, IDC_Update, m_Update);
	DDX_Control(pDX, IDOK, m_OK);
	DDX_Control(pDX, IDC_Border2, m_Border2);
	DDX_Control(pDX, IDC_Border1, m_Border1);
	DDX_Control(pDX, IDC_SchoolNetStationLabel, m_SchoolNetStationLabel);
	DDX_Control(pDX, IDC_RadarLabel, m_RadarLabel);
	DDX_Control(pDX, IDC_WebCams, m_WebCams);
	DDX_Control(pDX, IDC_SchoolNetStation, m_SchoolNetStation);
	DDX_Control(pDX, IDC_SchoolNet, m_SchoolNet);
	DDX_Control(pDX, IDC_RadarImage, m_RadarImage);
	DDX_Control(pDX, IDC_Radar, m_Radar);
	DDX_Control(pDX, IDC_Options, m_Options);
	DDX_Control(pDX, IDC_Forecast, m_Forecast);
	DDX_Control(pDX, IDC_Details, m_Details);
	DDX_Control(pDX, IDC_DataPlot, m_DataPlot);
	DDX_Control(pDX, IDC_About, m_About);
	DDX_Control(pDX, IDC_View, m_View);
	//}}AFX_DATA_MAP
}

#define WM_TRAYNOTIFY (WM_APP + 10)

BEGIN_MESSAGE_MAP(CKCCIDlg, CNewDialog)
	//{{AFX_MSG_MAP(CKCCIDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_Options, OnOptions)
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_About, OnAbout)
	ON_BN_CLICKED(IDC_SchoolNet, OnSchoolNet)
	ON_BN_CLICKED(IDC_Radar, OnRadar)
	ON_BN_CLICKED(IDC_Forecast, OnForecast)
	ON_CBN_SELENDOK(IDC_SchoolNetStation, OnSelendokSchoolNetStation)
	ON_CBN_SELENDOK(IDC_RadarImage, OnSelendokRadarImage)
	ON_BN_CLICKED(IDC_Update, OnUpdate)
	ON_BN_CLICKED(IDC_Details, OnDetails)
	ON_BN_CLICKED(IDC_WebCams, OnWebCams)
	ON_BN_CLICKED(IDC_DataPlot, OnDataPlot)
	ON_REGISTERED_MESSAGE(WM_TASKBARCREATED, OnTaskbarCreated)
	ON_MESSAGE(WM_TRAYNOTIFY, OnTrayNotify)
	ON_COMMAND(MID_Restore, OnTrayRestore)
	ON_COMMAND(MID_Exit, OnTrayExit)
	ON_WM_SIZE()
	ON_COMMAND(IDCANCEL, OnCancel)
	ON_COMMAND(MID_Detailed, OnDetails)
	ON_COMMAND(MID_WebCams, OnWebCams)
	ON_COMMAND(MID_DataPlots, OnDataPlot)
	ON_COMMAND(MID_Options, OnOptions)
	ON_CBN_SELENDCANCEL(IDC_RadarImage, OnSelendcancelRadarImage)
	ON_CBN_SELENDCANCEL(IDC_SchoolNetStation, OnSelendcancelSchoolNetStation)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CKCCIDlg message handlers

BOOL CKCCIDlg::OnInitDialog()
{
	CNewDialog::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu * pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
			pSysMenu->AppendMenu(MF_STRING, 48920, _T("Exit"));
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	// TODO: Add extra initialization here

	CNewMenu::SetAlpha(225);
//	this->m_SystemNewMenu.SetMenuTitle(_T("KCCI School Net 8"), MFT_SIDE_TITLE);

	RGBQUAD transColor;
	memset(&transColor, 255, sizeof(RGBQUAD));
	transColor.rgbReserved = 0;

	/* Populate the lists */

	PopulateStationList(this->schoolNetStations, m_SchoolNetStation);
	m_SchoolNetStation.SetCurSel(FindDefaultStation(schoolNetStations));
	m_RadarImage.SetCurSel(GetDefaultRadarImage());

	/* Set up the timers */

	currentLayout = GetControlPanelLocation();
	timerSchoolNet = GetSchoolNetUpdateInterval();
	timerRadar = GetRadarUpdateInterval();

    SetTimer(95632, timerRadar * 60000, NULL);
	SetTimer(95633, timerSchoolNet * 60000, NULL);
	SetTimer(95634, 24 * 60 * 60000, NULL);		// Updates School Net station list
	SetTimer(95635, 6 * 60 * 60000, NULL);		// Updates Forecast image

	/* Set the current layout */

	if(currentLayout == 0) MovetoLeft(* this);
	else if(currentLayout == 1) MovetoBottom(* this);
	else if(currentLayout == 2) MovetoRight(* this);

	/* Parse in the images */

	radarImage.Decode((unsigned char *)kcci->radarImage, kcci->radarImage.length(), CXIMAGE_FORMAT_UNKNOWN);
	forecastImage.Decode((unsigned char *)kcci->forecastImage, kcci->forecastImage.length(), CXIMAGE_FORMAT_UNKNOWN);

	/* Based on the default view, select the image to display */

	switch(GetDefaultView())
	{
	default:
	case 0: OnSchoolNet(); break;
	case 1: OnRadar(); break;
	case 2: OnForecast(); break;
	}

	radarSelect = false;
    progressLock = false;

	/* Create the tray icon */

	tray = NULL;

	hTrayIcon = NULL;
	hBitmap = NULL;
    hMaskBitmap = CreateBitmap(64,64,1,1,NULL);
	CreateTrayIcon();

	hViewBitmap = NULL;

	hSchoolNetBitmap = NULL;
	hRadarBitmap = NULL;
	hForecastBitmap = NULL;

	hSmallSchoolNetBitmap = NULL;
	hSmallRadarBitmap = NULL;
	hSmallForecastBitmap = NULL;

//	tray = new CTrayNot(this, WM_APP + 10, _T("KCCI School Net 8"), &hTrayIcon);
	tray = new CTrayNot(this, WM_APP + 10, _T(""), &hTrayIcon);
	tray->SetState(0);

	m_Progress.ShowWindow(SW_HIDE);

	/* NULL out the CWinThread pointers */

	dataPlotThread = NULL;
	detailedThread = NULL;
	webCamThread = NULL;

	optionsThread = NULL;

	checkConnection = NULL;
	updateSchoolNetData = NULL;
	updateSchoolNetStations = NULL;
	updateRadarImage = NULL;
	updateForecastImage = NULL;
    updateCameraList = NULL;

    ppToolTip.Create(this);
	font.CreatePointFont(100, _T("Bank Gothic Medium BT"));

	m_OK.DrawBorder();
	m_OK.SetFlat(0);
	m_OK.SetIcon(IDI_EXIT);
	m_OK.SetFont(&font);

	m_Radar.DrawBorder();
	m_Radar.SetFlat(0);
	m_Radar.SetIcon(IDI_RADAR);
	m_Radar.SetFont(&font);

	m_View.SetFocus();

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CKCCIDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else if (nID == 48920)
	{
		OnOK();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CKCCIDlg::OnPaint() 
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
HCURSOR CKCCIDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CKCCIDlg::OnOptions()
{
	// TODO: Add your control notification handler code here

	/* If the options window is currently open, then move the focus to it and exit
	 * the message handler.
	 */

	CWnd * hPrevWnd = FindWindow(NULL, "Options");
	if(hPrevWnd)
	{
		hPrevWnd->ShowWindow(SW_NORMAL);
		hPrevWnd->SetForegroundWindow();
		return;
	}

	/* Create the thread and execute it */

	COptionsThread * optionsThread;
	optionsThread = (COptionsThread * )AfxBeginThread(RUNTIME_CLASS(COptionsThread), THREAD_PRIORITY_NORMAL, 0, CREATE_SUSPENDED);
	this->optionsThread = optionsThread->m_hThread;
    this->optionsThreadID = optionsThread->m_nThreadID;

	optionsThread->kcci = this;

	optionsThread->ResumeThread();
}

void CKCCIDlg::OnTimer(UINT nIDEvent) 
{
	// TODO: Add your message handler code here and/or call default

	DWORD exitCode;
    CWinThread * temp;

    switch(nIDEvent)
	{

    case 95632:

		/* Are we currently downloading the radar image */

        if(GetExitCodeThread(updateRadarImage, & exitCode))
        {
            if(exitCode == STILL_ACTIVE) return;
        }

        temp = AfxBeginThread(UpdateRadarImage, this, 0, CREATE_SUSPENDED);
        updateRadarImage = temp->m_hThread;
		temp->ResumeThread();
		break;

	case 95633:

		/* Is the data being updated */

        if(GetExitCodeThread(updateSchoolNetData, & exitCode))
        {
            if(exitCode == STILL_ACTIVE) return;
        }

        temp = AfxBeginThread(UpdateSchoolNetData, this, 0, CREATE_SUSPENDED);
        updateRadarImage = temp->m_hThread;
		temp->ResumeThread();
		break;

	case 95634: 

		/* Is the station data being downloaded */

        if(GetExitCodeThread(updateSchoolNetStations, & exitCode))
        {
            if(exitCode == STILL_ACTIVE) return;
        }

        temp = AfxBeginThread(UpdateSchoolNetStations, this, 0, CREATE_SUSPENDED);
        updateRadarImage = temp->m_hThread;
		temp->ResumeThread();
		break;

	case 95635: 

		/* Is the forecast image being downloaded? */

        if(GetExitCodeThread(updateForecastImage, & exitCode))
        {
            if(exitCode == STILL_ACTIVE) return;
        }

        temp = AfxBeginThread(UpdateForecastImage, this, 0, CREATE_SUSPENDED);
        updateRadarImage = temp->m_hThread;
		temp->ResumeThread();
		break;

	default:	CDialog::OnTimer(nIDEvent);
	}
}

void CKCCIDlg::OnAbout() 
{
	// TODO: Add your control notification handler code here

	CAboutDlg about;
	about.DoModal();
}

void CKCCIDlg::OnSchoolNet() 
{
	// TODO: Add your control notification handler code here

	/* Get the current station from the drop list, render the image for that station,
	 * and draw it.
	 */

	int x = m_SchoolNetStation.GetCurSel();
	KCCIStationList * station;
	KCCISchoolNetData * data;

    station = (KCCIStationList * )schoolNetStations.elementAt(x);
    if(station == NULL) return;
    
    data = FindData(station->stationID, schoolNetData);
    if(data == NULL) return;

	CDC * cDC = m_View.GetDC();
	RenderSchoolNetData(cDC, schoolNetImage, station->stationName, * data);
	m_View.ReleaseDC(cDC);

	image = &schoolNetImage;

	if(hViewBitmap)
		DeleteObject(hViewBitmap);

	hViewBitmap = image->MakeBitmap();
	m_View.SetBitmap(hViewBitmap);
}

void CKCCIDlg::OnRadar() 
{
	// TODO: Add your control notification handler code here

	if(hViewBitmap)
		DeleteObject(hViewBitmap);

	image = &radarImage;
	radarImage.Decode((BYTE *)(const unsigned char *)kcci->radarImage, kcci->radarImage.length(), CXIMAGE_FORMAT_UNKNOWN);

	hViewBitmap = image->MakeBitmap();
	m_View.SetBitmap(hViewBitmap);
}

void CKCCIDlg::OnForecast() 
{
	// TODO: Add your control notification handler code here

	if(hViewBitmap)
		DeleteObject(hViewBitmap);

	image = &forecastImage;
	forecastImage.Decode((BYTE *)(const unsigned char *)kcci->forecastImage, kcci->forecastImage.length(), CXIMAGE_FORMAT_UNKNOWN);

	hViewBitmap = image->MakeBitmap();
	m_View.SetBitmap(hViewBitmap);
}

void CKCCIDlg::OnSelendokSchoolNetStation() 
{
	// TODO: Add your control notification handler code here

	/* Since all this does is draw a new School Net image, simply route it to the
	 * message handler for the School Net button.
	 */

	m_View.SetFocus();
	OnSchoolNet();
	CreateTrayIcon();
}

void CKCCIDlg::OnSelendokRadarImage() 
{
	// TODO: Add your control notification handler code here

    DWORD exitCode = STILL_ACTIVE;
    CWinThread * temp;

    while(exitCode == STILL_ACTIVE)
    {
        if(!GetExitCodeThread(updateRadarImage, & exitCode))
            exitCode = ~STILL_ACTIVE;
    }
	
	radarSelect = true;
    temp = AfxBeginThread(UpdateRadarImage, this, 0, CREATE_SUSPENDED);
    updateRadarImage = temp->m_hThread;
	temp->ResumeThread();
	m_View.SetFocus();
}

void CKCCIDlg::OnUpdate() 
{
	// TODO: Add your control notification handler code here
	
	CUpdate update; DWORD exitCode;
    CWinThread * temp;

	if(update.DoModal() == IDCANCEL) return;

	if(update.updateRadarImage)
	{
        /* Check to see if the thread is already running */

		if(! GetExitCodeThread(updateRadarImage, & exitCode)) 
            exitCode = ~STILL_ACTIVE;

		if(exitCode != STILL_ACTIVE)
		{
			radarSelect = true;
			temp = AfxBeginThread(UpdateRadarImage, this, 0, CREATE_SUSPENDED);
            updateRadarImage = temp->m_hThread;            
			temp->ResumeThread();
		}
	}

	if(update.updateSchoolNetStations)
	{
		if(! GetExitCodeThread(updateSchoolNetStations, & exitCode)) 
            exitCode = ~STILL_ACTIVE;

		if(exitCode != STILL_ACTIVE)
		{
			temp = AfxBeginThread(UpdateSchoolNetStations, this, 0, CREATE_SUSPENDED);
            updateSchoolNetStations = temp->m_hThread;
			temp->ResumeThread();
		}
	}

	if(update.updateSchoolNetData && ! update.updateSchoolNetStations)
	{
		if(! GetExitCodeThread(updateSchoolNetData, & exitCode)) 
            exitCode = ~STILL_ACTIVE;

		if(exitCode != STILL_ACTIVE)
		{
			temp = AfxBeginThread(UpdateSchoolNetData, this, 0, CREATE_SUSPENDED);
			updateSchoolNetData = temp->m_hThread;
			temp->ResumeThread();
		}
	}

	if(update.updateForecastImage)
	{
		if(! GetExitCodeThread(updateForecastImage, & exitCode)) 
            exitCode = ~STILL_ACTIVE;

		if(exitCode != STILL_ACTIVE)
		{
			temp = AfxBeginThread(UpdateForecastImage, this, 0, CREATE_SUSPENDED);
			updateForecastImage = temp->m_hThread;
			temp->ResumeThread();
		}
	}

    if(update.updateCameras)
    {
		if(! GetExitCodeThread(updateCameraList, & exitCode)) 
            exitCode = ~STILL_ACTIVE;

		if(exitCode != STILL_ACTIVE)
		{
			temp = AfxBeginThread(UpdateCameraList, this, 0, CREATE_SUSPENDED);
			updateForecastImage = temp->m_hThread;
			temp->ResumeThread();
		}
    }
}

void CKCCIDlg::OnDetails() 
{
	// TODO: Add your control notification handler code here

	/* First, let's make sure there isn't one already running.  If so, switch control
	 * over to it.
	 */

	CWnd * hPrevWnd = FindWindow(NULL, "Detailed Weather Information");
	if(hPrevWnd)
	{
		hPrevWnd->ShowWindow(SW_NORMAL);
		hPrevWnd->SetForegroundWindow();
		return;
	}

	CDetailedThread * details;

	details = (CDetailedThread * ) AfxBeginThread(RUNTIME_CLASS(CDetailedThread), THREAD_PRIORITY_NORMAL, 0, CREATE_SUSPENDED);
	detailedThread = details;

	details->station = (KCCIStationList * )schoolNetStations.elementAt(m_SchoolNetStation.GetCurSel());

    if(details->station == NULL)
    {
        delete details;
        return;
    }

	details->data = FindData(details->station->stationID, schoolNetData);
    this->detailedThread = details->m_hThread;
    this->detailedThreadID = details->m_nThreadID;
	details->ResumeThread();
}

void CKCCIDlg::OnWebCams() 
{
	// TODO: Add your control notification handler code here

	/* Start the thread suspended so that the list of web cams can be passed
	 * to the thread to populate the list box.
	 */

	CWebCamThread * camThread = (CWebCamThread * )AfxBeginThread(RUNTIME_CLASS(CWebCamThread), THREAD_PRIORITY_NORMAL, 0, CREATE_SUSPENDED);
	webCamThread = camThread;

	camThread->webcams = & cameraList;
    this->webCamThread = camThread->m_hThread;
    this->webCamThreadID = camThread->m_nThreadID;
	camThread->ResumeThread();
}

void CKCCIDlg::OnDataPlot() 
{
	// TODO: Add your control notification handler code here

	/* First, let's make sure there isn't one already running.  If so, switch control
	 * over to it.
	 */

	CWnd * hPrevWnd = FindWindow(NULL, "KCCI School Net 8 - Compare Area Stations");
	if(hPrevWnd)
	{
		hPrevWnd->ShowWindow(SW_NORMAL);
		hPrevWnd->SetForegroundWindow();
		return;
	}

	CDataPlotThread * plotThread;
	plotThread = (CDataPlotThread * )AfxBeginThread(RUNTIME_CLASS(CDataPlotThread), THREAD_PRIORITY_NORMAL, 0, CREATE_SUSPENDED);
	dataPlotThread = plotThread;

	plotThread->stations = & schoolNetStations;
	plotThread->currentStation = m_SchoolNetStation.GetCurSel();
    this->dataPlotThread = plotThread->m_hThread;
    this->dataPlotThreadID = plotThread->m_nThreadID;
	plotThread->ResumeThread();
}

LRESULT CKCCIDlg::OnTaskbarCreated(WPARAM wParam, LPARAM lParam)
{
	tray->SetState(0);
	return 0;
}

LRESULT CKCCIDlg::OnTrayNotify(WPARAM wParam, LPARAM lParam)
{
	switch(lParam)
	{

    case WM_MOUSEHOVER:
        SetWindowText(_T("Mouse Hover"));
        break;


	case WM_RBUTTONDOWN:
	{
		CNewMenu menu, * popup;
		POINT pt;

		/* Load and verify the menu */

		menu.LoadMenu(IDR_TrayMenu);
		popup = (CNewMenu *) menu.GetSubMenu(0);
		if(popup == NULL) return 0;
		popup->SetDefaultItem(MID_Restore);
		popup->ModifyODMenu(0, _T("Exit"), IDB_EXIT);

//		popup->SetMenuTitle(_T("KCCI School Net 8"), MFT_SIDE_TITLE);

		/* Get the cursor position */

		GetCursorPos(& pt);
		SetForegroundWindow();

		/* Display the menu */

		popup->TrackPopupMenu(TPM_LEFTALIGN | TPM_RIGHTBUTTON, pt.x, pt.y, this);
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

	return 0;
}

void CKCCIDlg::OnTrayRestore() 
{
	// TODO: Add your command handler code here
	
		ShowWindow(SW_RESTORE);
		SetForegroundWindow();
}

void CKCCIDlg::OnTrayExit() 
{
	// TODO: Add your command handler code here

	OnOK();	
}

void CKCCIDlg::OnCancel()
{
	/* This will only hide the application */

	AfxGetApp()->HideApplication();
}

void CKCCIDlg::OnSize(UINT nType, int cx, int cy) 
{
	CDialog::OnSize(nType, cx, cy);
	
	// TODO: Add your message handler code here
	
	if(nType == SIZE_MINIMIZED) AfxGetApp()->HideApplication();
}

void CAboutDlg::OnPaint() 
{
	CPaintDC dc(this); // device context for painting
	
	// TODO: Add your message handler code here

	CDC * cDC = m_Logo.GetDC();
	image.Draw(cDC->m_hDC);
	
	// Do not call CDialog::OnPaint() for painting messages
}

BOOL CAboutDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here

	RGBQUAD transColor;
	memset(&transColor, 0, sizeof(RGBQUAD));
	transColor.rgbGreen = 255;

	image.LoadResource(FindResource(NULL,MAKEINTRESOURCE(IDR_Logo2), "PNG"), CXIMAGE_FORMAT_PNG);
	image.SetTransColor(transColor); image.SetTransIndex(0);
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CKCCIDlg::OnOK() 
{
	// TODO: Add extra validation here

	DWORD exitCode; bool done = false;

    /* First, post quit messages to the User Interface threads */

    PostThreadMessage(optionsThreadID, WM_QUIT, 0, 0);
    PostThreadMessage(dataPlotThreadID, WM_QUIT, 0, 0);
    PostThreadMessage(detailedThreadID, WM_QUIT, 0, 0);
    PostThreadMessage(webCamThreadID, WM_QUIT, 0, 0);

    /* Eye all threads to see if they are running. If even one thread is running, the
     * entire loop repeats, thus ensuring all threads get shut down. If the exit code
     * for the thread cannot be retrieved, assume the thread has exited.
     */

    while(! done)
    {
        if(!GetExitCodeThread(checkConnection, & exitCode)) done = true;
        else if(exitCode == STILL_ACTIVE) done = false;
        else done = true;

        if(!GetExitCodeThread(updateSchoolNetData, & exitCode)) done = true;
        else if(exitCode == STILL_ACTIVE) done = false;
        else done = true;

        if(!GetExitCodeThread(updateSchoolNetStations, & exitCode)) done = true;
        else if(exitCode == STILL_ACTIVE) done = false;
        else done = true;

        if(!GetExitCodeThread(updateRadarImage, & exitCode)) done = true;
        else if(exitCode == STILL_ACTIVE) done = false;
        else done = true;

        if(!GetExitCodeThread(updateForecastImage, & exitCode)) done = true;
        else if(exitCode == STILL_ACTIVE) done = false;
        else done = true;

        if(!GetExitCodeThread(updateCameraList, & exitCode)) done = true;
        else if(exitCode == STILL_ACTIVE) done = false;
        else done = true;

        if(!GetExitCodeThread(optionsThread, & exitCode)) done = true;
        else if(exitCode == STILL_ACTIVE) done = false;
        else done = true;

        if(!GetExitCodeThread(dataPlotThread, & exitCode)) done = true;
        else if(exitCode == STILL_ACTIVE) done = false;
        else done = true;

        if(!GetExitCodeThread(detailedThread, & exitCode)) done = true;
        else if(exitCode == STILL_ACTIVE) done = false;
        else done = true;
    
        if(!GetExitCodeThread(webCamThread, & exitCode)) done = true;
        else if(exitCode == STILL_ACTIVE) done = false;
        else done = true;
    }

	delete tray;
	image = NULL;

	TRACE("Destroying Window...\n");

	DestroyIcon(hTrayIcon);
	DeleteObject(hBitmap);
	DeleteObject(hMaskBitmap);
	DeleteObject(hViewBitmap);
	
	CDialog::OnOK();
}

void CKCCIDlg::OnSelendcancelRadarImage() 
{
	// TODO: Add your control notification handler code here

	m_View.SetFocus();

}

void CKCCIDlg::OnSelendcancelSchoolNetStation() 
{
	// TODO: Add your control notification handler code here
	
	m_View.SetFocus();
}

#define FontSize(x) -MulDiv(x, GetDeviceCaps(dc->m_hDC, LOGPIXELSY), 72)

void GetTextExtent(CDC * cDC, const TCHAR * textString, int size, CSize & s, const TCHAR * fontName)
{
	CFont font, * oldFont;
	
	font.CreatePointFont(size * 10, fontName, cDC);
	oldFont = cDC->SelectObject(&font);
	s = cDC->GetTextExtent(textString, strlen(textString));
	cDC->SelectObject(oldFont); font.DeleteObject();
}

void CKCCIDlg::CreateTrayIcon()
{
	CDC * dc = GetDC();
	CSize textSize;
	int fontSize;

	trayIcon.Create(16, 16, 24);
	trayIcon.Clear();

	CxImage maskBitmap;
	maskBitmap.Create(16, 16, 24);

	if(hTrayIcon) DestroyIcon(hTrayIcon);
	if(hBitmap) DeleteObject(hBitmap);
	if(hMaskBitmap) DeleteObject(hMaskBitmap);

	int x = m_SchoolNetStation.GetCurSel();
	KCCIStationList * station;
	KCCISchoolNetData * data;
	CString temp;

	RGBQUAD black, pixel;
	black.rgbBlue = black.rgbGreen = black.rgbRed = 1;
	black.rgbReserved = 0;

    station = (KCCIStationList * )schoolNetStations.elementAt(x);
    if(station == NULL) return;
    
    data = FindData(station->stationID, schoolNetData);
    if(data == NULL) return;

	if(data->tempFahrenheit < 10 && data->tempFahrenheit >= 0)
		temp.Format(_T("0%i"), data->tempFahrenheit);
	else
		temp.Format(_T("%i"), data->tempFahrenheit);

	for(fontSize = 16; fontSize > 0; fontSize --)
	{
		GetTextExtent(dc, temp, fontSize, textSize, _T("Digital dream Fat Narrow"));
		if(textSize.cx <= 16 && textSize.cy <= 16) break;
	}

	if(data->tempFahrenheit < 10 && data->tempFahrenheit >= 0)
	{
		temp.Format(_T("%i"), data->tempFahrenheit);
		GetTextExtent(dc, temp, fontSize, textSize, _T("Digital dream Fat Narrow"));
	}

	if(data->tempFahrenheit < -9 || data->tempFahrenheit > 99)
	{
		hTrayIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
		hBitmap = NULL;
		hMaskBitmap = NULL;
	}
	else
	{
		trayIcon.DrawString(dc->m_hDC, (16 - textSize.cx) / 2 , (15 + textSize.cy) / 2, temp, black, 
			_T("Digital dream Fat Narrow"), FontSize(fontSize));

		for(x = 0; x < 16; x++)
		{
			for(int y = 0; y < 16; y++)
			{
				pixel = trayIcon.GetPixelColor(x, y);
				if(pixel.rgbRed || pixel.rgbGreen || pixel.rgbBlue)
					maskBitmap.SetPixelColor(x, y, 0l);
				else
					maskBitmap.SetPixelColor(x, y, 0xFFFFFFl);
			}
		}

		ICONINFO iconInfo;
		iconInfo.fIcon = TRUE;
		iconInfo.hbmColor = trayIcon.MakeBitmap();
		iconInfo.hbmMask = maskBitmap.MakeBitmap();

		hBitmap = iconInfo.hbmColor;
		hMaskBitmap = iconInfo.hbmMask;

		hTrayIcon = CreateIconIndirect(&iconInfo);
	}

	if(tray)
	{
		tray->SetState(0);
		tray->Update();
	}

	ReleaseDC(dc);
}

BOOL CKCCIDlg::PreTranslateMessage(MSG* pMsg) 
{
	// TODO: Add your specialized code here and/or call the base class

    ppToolTip.RelayEvent(pMsg);
	
	return CNewDialog::PreTranslateMessage(pMsg);
}
