// KCCIDlg.h : header file
//

#if !defined(AFX_KCCIDLG_H__85BF1A1A_C4F9_4CFC_9914_D3B40BE0A1FB__INCLUDED_)
#define AFX_KCCIDLG_H__85BF1A1A_C4F9_4CFC_9914_D3B40BE0A1FB__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "LinkedList.h"
#include "xImage.h"
#include "KCCISchoolNet.h"

#include "TrayNot.h"
#include "PPToolTip.h"
#include "BtnST.h"

/////////////////////////////////////////////////////////////////////////////
// CKCCIDlg dialog

//class CKCCIDlg : public CDialog
class CKCCIDlg : public CNewDialog
{
// Construction
public:
	CKCCIDlg(CWnd* pParent = NULL);	// standard constructor

	LinkedList schoolNetStations;
	LinkedList schoolNetData;
	LinkedList cameraList;

	CxImage * image, schoolNetImage, radarImage, forecastImage;
	CxImage animationImage;
	KCCISchoolNet * kcci;

	CTrayNot * tray;
	HICON hTrayIcon;
	HBITMAP hMaskBitmap;
	HBITMAP hBitmap;

	HBITMAP hViewBitmap;

	HBITMAP hSchoolNetBitmap;
	HBITMAP hRadarBitmap;
	HBITMAP hForecastBitmap;

	HBITMAP hSmallSchoolNetBitmap;
	HBITMAP hSmallRadarBitmap;
	HBITMAP hSmallForecastBitmap;

	void CreateTrayIcon();

	CxImage trayIcon;
	CxImage trayMaskIcon;

	int currentLayout;
	int timerSchoolNet;
	int timerRadar;

	bool radarSelect;
    bool progressLock;

    HANDLE detailedThread; DWORD detailedThreadID;
	HANDLE dataPlotThread; DWORD dataPlotThreadID;
	HANDLE webCamThread; DWORD webCamThreadID;

	HANDLE optionsThread; DWORD optionsThreadID;

	HANDLE checkConnection; DWORD checkConnectionID;
	HANDLE updateRadarImage; DWORD updateRadarImageID;
	HANDLE updateSchoolNetData; DWORD updateSchoolNetDataID;
	HANDLE updateSchoolNetStations; DWORD updateSchoolNetStationsID;
	HANDLE updateForecastImage; DWORD updateForecastImageID;
    HANDLE updateCameraList; DWORD updateCameraListID;

    CPPToolTip ppToolTip;
	CFont font;

/*
	CWinThread * detailedThread;
	CWinThread * dataPlotThread;
	CWinThread * webCamThread;

	CWinThread * optionsThread;

	CWinThread * checkConnection;
	CWinThread * updateRadarImage;
	CWinThread * updateSchoolNetData;
	CWinThread * updateSchoolNetStations;
	CWinThread * updateForecastImage;
    CWinThread * updateCameraList;
*/	
// Dialog Data
	//{{AFX_DATA(CKCCIDlg)
	enum { IDD = IDD_KCCI_DIALOG };
	CProgressCtrl	m_Progress;
	CButton	m_Update;
	CButtonST	m_OK;
	CButton	m_Border2;
	CButton	m_Border1;
	CStatic	m_SchoolNetStationLabel;
	CStatic	m_RadarLabel;
	CButton	m_WebCams;
	CComboBox	m_SchoolNetStation;
	CButton	m_SchoolNet;
	CComboBox	m_RadarImage;
	CButtonST	m_Radar;
	CButton	m_Options;
	CButton	m_Forecast;
	CButton	m_Details;
	CButton	m_DataPlot;
	CButton	m_About;
	CStatic	m_View;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CKCCIDlg)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CKCCIDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnOptions();
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnAbout();
	afx_msg void OnSchoolNet();
	afx_msg void OnRadar();
	afx_msg void OnForecast();
	afx_msg void OnSelendokSchoolNetStation();
	afx_msg void OnSelendokRadarImage();
	afx_msg void OnUpdate();
	afx_msg void OnDetails();
	afx_msg void OnWebCams();
	afx_msg void OnDataPlot();
	afx_msg LRESULT OnTaskbarCreated(WPARAM, LPARAM);
	afx_msg LRESULT OnTrayNotify(WPARAM, LPARAM );
	afx_msg void OnTrayRestore();
	afx_msg void OnTrayExit();
	afx_msg void OnCancel();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	virtual void OnOK();
	afx_msg void OnSelendcancelRadarImage();
	afx_msg void OnSelendcancelSchoolNetStation();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_KCCIDLG_H__85BF1A1A_C4F9_4CFC_9914_D3B40BE0A1FB__INCLUDED_)
