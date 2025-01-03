#include "stdafx.h"

/* Provides functions to move the controls on the dialog */

#include "KCCI.h"
#include "KCCIDlg.h"
#include "Registry.h"

#define MAPXY kcci.MapDialogRect(&rect)
#define NEWXY SetWindowPos(NULL, rect.left, rect.top, 0, 0, SWP_NOSIZE)

int Lcoordinates [36] = { 17, 17,	// School Net Station label
	17, 27,							// School Net Station drop box
	37, 77,							// Refresh button
	17, 47,							// Radar label
	17, 57,							// Radar combo box
	7, 110,							// Group box
	17, 125,						// School Net button
	17, 145,						// Radar button
	17, 165,						// Forecast button
	67, 125,						// Details button
	67, 145,						// Compare button
	67, 165,						// Cams button
	17, 200,						// About button
	67, 200,						// Options button
	37, 220,						// Exit button
	143, 7,							// View box
	7, 7,
	7, 270 };

int Rcoordinates[36] = { 455, 17,	// School Net Station label
	455, 27,						// School Net Station drop box
	485, 77,						// Refresh button
	455, 47,						// Radar label
	455, 57,						// Radar combo box
	445, 110,						// Group box
	455, 125,						// School Net button
	455, 145,
	455, 165,
	515, 125,
	515, 145,
	515, 165,
	455, 200,
	515, 200,
	485, 220,
	7, 7,
	445, 7,
	445, 270 };

int Bcoordinates[36] = { 15, 310,
	15, 320,
	250, 315,
	130, 310,
	130, 320,
	10, 10,
	450, 70,
	450, 90,
	450, 110,
	450, 130,
	450, 150,
	450, 170,
	335, 315,
	385, 315,
	450, 190,
	7, 7,
	10, 10,
	335, 335 };

void MoveEverything(int * coordinates, CKCCIDlg & kcci)
{
	RECT rect; 

	/* Move the main view */

	rect.left = coordinates[30]; rect.top = coordinates[31];
	MAPXY; kcci.m_View.NEWXY;

	/* Move the border boxes */

	rect.left = coordinates[32]; rect.top = coordinates[33];
	MAPXY; kcci.m_Border1.NEWXY;

	rect.left = coordinates[10]; rect.top = coordinates[11];
	MAPXY; kcci.m_Border2.NEWXY;

	/* Move the School Net Station label */

	rect.left = coordinates[0]; rect.top = coordinates[1];
	MAPXY; kcci.m_SchoolNetStationLabel.NEWXY;

	/* Move the School Net combo box */
	
	rect.left = coordinates[2]; rect.top = coordinates[3];
	MAPXY; kcci.m_SchoolNetStation.NEWXY;

	/* Move the Refresh button */

	rect.left = coordinates[4]; rect.top = coordinates[5];
	MAPXY; kcci.m_Update.NEWXY;

	/* Move the Radar label and button */

	rect.left = coordinates[6]; rect.top = coordinates[7];
	MAPXY; kcci.m_RadarLabel.NEWXY;

	rect.left = coordinates[8]; rect.top = coordinates[9];
	MAPXY; kcci.m_RadarImage.NEWXY;

	/* Move the buttons */

	rect.left = coordinates[12]; rect.top = coordinates[13];
	MAPXY; kcci.m_SchoolNet.NEWXY;

	rect.left = coordinates[14]; rect.top = coordinates[15];
	MAPXY; kcci.m_Radar.NEWXY;

	rect.left = coordinates[16]; rect.top = coordinates[17];
	MAPXY; kcci.m_Forecast.NEWXY;

	rect.left = coordinates[18]; rect.top = coordinates[19];
	MAPXY; kcci.m_Details.NEWXY;

	rect.left = coordinates[20]; rect.top = coordinates[21];
	MAPXY; kcci.m_DataPlot.NEWXY;

	rect.left = coordinates[22]; rect.top = coordinates[23];
	MAPXY; kcci.m_WebCams.NEWXY;

	rect.left = coordinates[24]; rect.top = coordinates[25];
	MAPXY; kcci.m_About.NEWXY;

	rect.left = coordinates[26]; rect.top = coordinates[27];
	MAPXY; kcci.m_Options.NEWXY;

	rect.left = coordinates[28]; rect.top = coordinates[29];
	MAPXY; kcci.m_OK.NEWXY;

	rect.left = coordinates[34]; rect.top = coordinates[35];
	MAPXY; kcci.m_Progress.NEWXY;
}

void ResizeWindow(RECT & size, CKCCIDlg & kcci)
{
	kcci.SetWindowPos(NULL, 0, 0, size.right, size.bottom, SWP_NOMOVE);
}

void MovetoLeft(CKCCIDlg & kcci)
{
	int * coordinates = Lcoordinates;
	RECT windowSize;

	kcci.m_Border1.ShowWindow(SW_NORMAL);
	kcci.m_Border2.ShowWindow(SW_NORMAL);

	MoveEverything(coordinates, kcci);
	windowSize.bottom = 310; windowSize.right = 577;
	kcci.MapDialogRect(&windowSize);
	windowSize.right += GetSystemMetrics(SM_CXDLGFRAME) * 2;
	windowSize.bottom += GetSystemMetrics(SM_CYCAPTION) + GetSystemMetrics(SM_CYDLGFRAME) * 2;
	ResizeWindow(windowSize, kcci);
}

void MovetoRight(CKCCIDlg & kcci)
{
	RECT windowSize;

	kcci.m_Border1.ShowWindow(SW_NORMAL);
	kcci.m_Border2.ShowWindow(SW_NORMAL);

	MoveEverything(Rcoordinates, kcci);
	windowSize.bottom = 310; windowSize.right = 577;
	kcci.MapDialogRect(&windowSize);
	windowSize.right += GetSystemMetrics(SM_CXDLGFRAME) * 2;
	windowSize.bottom += GetSystemMetrics(SM_CYCAPTION) + GetSystemMetrics(SM_CYDLGFRAME) * 2;
	ResizeWindow(windowSize, kcci);
}


void MovetoBottom(CKCCIDlg & kcci)
{
	RECT windowSize;

	kcci.m_Border1.ShowWindow(SW_HIDE);
	kcci.m_Border2.ShowWindow(SW_HIDE);

	MoveEverything(Bcoordinates, kcci);
	windowSize.bottom = 345; windowSize.right = 505;
	kcci.MapDialogRect(&windowSize);
	windowSize.right += GetSystemMetrics(SM_CXDLGFRAME) * 2;
	windowSize.bottom += GetSystemMetrics(SM_CYCAPTION) + GetSystemMetrics(SM_CYDLGFRAME) * 2;
	ResizeWindow(windowSize, kcci);
}

/* Background thread to facilitate updating the main dialog box */

void MoveControls(CKCCIDlg * dlg)
{
	int location = GetControlPanelLocation();

	dlg->ShowWindow(SW_HIDE);

	if(location == 0) MovetoLeft(* dlg);
	else if(location == 1) MovetoBottom(* dlg);
	else if(location == 2) MovetoRight(* dlg);

	dlg->ShowWindow(SW_NORMAL);
}
