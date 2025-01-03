// OptionsWebCam.cpp : implementation file
//

#include "stdafx.h"
#include "KCCI.h"
#include "OptionsWebCam.h"

#include "Registry.h"
#include "PopulateLists.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// COptionsWebCam property page

IMPLEMENT_DYNCREATE(COptionsWebCam, CPropertyPage)

COptionsWebCam::COptionsWebCam() : CPropertyPage(COptionsWebCam::IDD)
{
	//{{AFX_DATA_INIT(COptionsWebCam)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}

COptionsWebCam::~COptionsWebCam()
{
}

void COptionsWebCam::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(COptionsWebCam)
	DDX_Control(pDX, IDC_DefaultCamera, m_DefaultCamera);
	DDX_Control(pDX, IDC_CameraUpdate, m_CameraUpdate);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(COptionsWebCam, CPropertyPage)
	//{{AFX_MSG_MAP(COptionsWebCam)
	ON_EN_CHANGE(IDC_CameraUpdate, OnChangeCameraUpdate)
	ON_CBN_SELENDOK(IDC_DefaultCamera, OnSelendokDefaultCamera)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// COptionsWebCam message handlers

BOOL COptionsWebCam::OnInitDialog() 
{
	CPropertyPage::OnInitDialog();
	
	// TODO: Add extra initialization here

	CString temp;

	temp.Format("%i", GetWebCamUpdateInterval());
	m_CameraUpdate.SetWindowText(temp);

	PopulateWebCamList(* cameraList, m_DefaultCamera);
	m_DefaultCamera.SetCurSel(GetDefaultWebCam());

	/* Add code for the default web camera */
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void COptionsWebCam::OnOK()
{
	/* Write the options to the registry */

	CString temp;

	SetDefaultWebCam(m_DefaultCamera.GetCurSel());
	m_CameraUpdate.GetWindowText(temp);
	SetWebCamUpdateInterval(atoi(temp));
}

BOOL COptionsWebCam::OnKillActive()
{
	CString temp; int x;

	m_CameraUpdate.GetWindowText(temp);
	x = atoi(temp);

	if(x < 1 || x > 15)
	{
		MessageBox("Camera update time must be between 1 and 15 minutes", "Error", MB_OK | MB_ICONEXCLAMATION);
		return 0;
	}

	return 1;
}

void COptionsWebCam::OnChangeCameraUpdate() 
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CPropertyPage::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.
	
	// TODO: Add your control notification handler code here
	
	SetModified();
}

void COptionsWebCam::OnSelendokDefaultCamera() 
{
	// TODO: Add your control notification handler code here

	SetModified();	
}
