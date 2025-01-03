// Splash.cpp : implementation file
//

#include "stdafx.h"
#include "KCCI.h"
#include "Splash.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSplash dialog


CSplash::CSplash(CWnd* pParent /*=NULL*/)
	: CDialog(CSplash::IDD, pParent)
{
	//{{AFX_DATA_INIT(CSplash)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CSplash::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CSplash)
	DDX_Control(pDX, IDC_Status, m_Status);
	DDX_Control(pDX, IDC_SplashImage, m_SplashImage);
	DDX_Control(pDX, IDC_Progress, m_Progress);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CSplash, CDialog)
	//{{AFX_MSG_MAP(CSplash)
	ON_WM_PAINT()
	ON_WM_TIMER()
	ON_BN_CLICKED(IDOK, OnOK)
	ON_BN_CLICKED(IDCANCEL, OnCancel)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSplash message handlers

BOOL CSplash::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here

	/* Load the Splash image and set the transparency */

	RGBQUAD transColor;
	memset(&transColor, 0, sizeof(RGBQUAD)); transColor.rgbGreen = 255;

	image.LoadResource(FindResource(NULL, MAKEINTRESOURCE(IDR_Splash), "PNG"), CXIMAGE_FORMAT_PNG);
	image.SetTransColor(transColor); image.SetTransIndex(0);
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CSplash::PumpMessages()
{
	ASSERT(m_hWnd != NULL);

	MSG msg;

	while(PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
	{
		if(!IsDialogMessage(&msg))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}
}

void CSplash::OnPaint() 
{
	CPaintDC dc(this); // device context for painting
	
	// TODO: Add your message handler code here

	/* Draw the image using transparency */
	
	CDC * cDC = m_SplashImage.GetDC();
	image.Draw(cDC->m_hDC, 0, 0);
	m_SplashImage.ReleaseDC(cDC);
	
	// Do not call CDialog::OnPaint() for painting messages
}

void CSplash::OnTimer(UINT nIDEvent) 
{
	// TODO: Add your message handler code here and/or call default
	
	CDialog::OnTimer(nIDEvent);
}

void CSplash::OnOK()
{
	return;
}

void CSplash::OnCancel()
{
	return;
}