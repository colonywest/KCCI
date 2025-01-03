// FeaturetteProgress.cpp : implementation file
//

#include "stdafx.h"
#include "KCCI.h"
#include "FeaturetteProgress.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CFeaturetteProgress dialog


CFeaturetteProgress::CFeaturetteProgress(CWnd* pParent /*=NULL*/)
	: CDialog(CFeaturetteProgress::IDD, pParent)
{
	//{{AFX_DATA_INIT(CFeaturetteProgress)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CFeaturetteProgress::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CFeaturetteProgress)
	DDX_Control(pDX, IDC_Progress, m_Progress);
	DDX_Control(pDX, IDC_Featurette, m_Featurette);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CFeaturetteProgress, CDialog)
	//{{AFX_MSG_MAP(CFeaturetteProgress)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CFeaturetteProgress message handlers

void CFeaturetteProgress::PumpMessages()
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
