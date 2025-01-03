// WebCam.cpp : implementation file
//

#include "stdafx.h"
#include "KCCI.h"
#include "WebCam.h"
#include "FeaturetteProgress.h"

#include "PopulateLists.h"
#include "Registry.h"

#include "UpdateData.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CWebCam dialog


CWebCam::CWebCam(CWnd* pParent /*=NULL*/)
	: CDialog(CWebCam::IDD, pParent)
{
	//{{AFX_DATA_INIT(CWebCam)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CWebCam::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CWebCam)
	DDX_Control(pDX, IDC_Image, m_Image);
	DDX_Control(pDX, IDC_Progress, m_Progress);
	DDX_Control(pDX, IDC_Camera, m_Camera);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CWebCam, CDialog)
	//{{AFX_MSG_MAP(CWebCam)
	ON_WM_TIMER()
	ON_CBN_SELENDOK(IDC_Camera, OnSelendokCamera)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CWebCam message handlers

bool DownloadData(const char *, BinaryString &);

BOOL CWebCam::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here

	PopulateWebCamList(* cams, m_Camera);
	m_Camera.SetCurSel(GetDefaultWebCam());
	m_Progress.ShowWindow(SW_HIDE);

	m_Image.SetBitmap(image.MakeBitmap());

	SetTimer(WM_APP + 1, GetWebCamUpdateInterval() * 1000 * 60, NULL);
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CWebCam::OnTimer(UINT nIDEvent) 
{
	// TODO: Add your message handler code here and/or call default

	int * array;
	KCCICameraList * camera = (KCCICameraList *)cams->elementAt(m_Camera.GetCurSel());

	/* If the progress bar is already visible, exit */

	if(m_Progress.IsWindowVisible()) return;

	/* In this case, the dummy is an array of integers, all of which are pointers.
	 * The first is a pointer to the URL to download the image, the second is a pointer
	 * to the CxImage object to render the image, the third is a pointer to the
	 * progress bar, the fourth is a pointer to a CDialog object, and the fifth is a
	 * pointer to a CStatic object (the image view).
	 */

	array = new int[5];
	array[0] = (int )(const char *)camera->stationURL;
	array[1] = (int ) & image;
	array[2] = (int ) & m_Progress;
	array[3] = (int ) this;
	array[4] = (int ) & m_Image;

	AfxBeginThread(UpdateFeaturetteImage, array);

//	CDialog::OnTimer(nIDEvent);
}

void CWebCam::OnSelendokCamera() 
{
	// TODO: Add your control notification handler code here

	OnTimer(WM_APP + 1);	
}

void CWebCam::OnOK() 
{
	// TODO: Add extra validation here

	for( ; m_Progress.IsWindowVisible(); );
	PostMessage(WM_QUIT);

	
//	CDialog::OnOK();
}
