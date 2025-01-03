#include "stdafx.h"

#include "KCCI.h"
#include "KCCIDlg.h"

#include "KCCISchoolNet.h"
#include "PopulateLists.h"
#include "Radar.h"
#include "Render.h"
#include "Registry.h"

#include "xImage.h"
#include "BinaryString.h"
#include "SString.h"

bool DownloadData(const char *, BinaryString &, CKCCIDlg &);
bool DownloadData(const char *, BinaryString &, CProgressCtrl &);

UINT UpdateSchoolNetData(void * dummy)
{
    CKCCIDlg * kcci = (CKCCIDlg *)dummy;
	BinaryString output; SString data;
	CDC * cDC = kcci->m_View.GetDC();
	int x = kcci->m_SchoolNetStation.GetCurSel();
	KCCISchoolNetData * schoolNetData;
    bool dataDownloaded;

	KCCIStationList * station = (KCCIStationList * )kcci->schoolNetStations.elementAt(x);

    if(station == NULL) return 0;

	/* If the progress bar is being displayed, wait 10 ms. Then once we are able to access it,
     * lock it.
     */

	while(kcci->progressLock) _sleep(10);
    kcci->progressLock = true;

	TRACE("Updating School Net data...\n");

	dataDownloaded = DownloadData("http://mesonet.agron.iastate.edu/data/csv/kcci.dat", output, * kcci);
    kcci->progressLock = false;
    if(!dataDownloaded) return 0;


	data.append(output, output.length());

	kcci->kcci->schoolNetData = output;

	ParseSchoolNetData(data, kcci->schoolNetData);
	schoolNetData = FindData(station->stationID, kcci->schoolNetData);
	RenderSchoolNetData(cDC, kcci->schoolNetImage, station->stationName, * schoolNetData);

	if(kcci->hViewBitmap)
		DeleteObject(kcci->hViewBitmap);

	kcci->hViewBitmap = kcci->image->MakeBitmap();
	kcci->m_View.SetBitmap(kcci->hViewBitmap);
	kcci->RedrawWindow();
	kcci->m_View.ReleaseDC(cDC);
	return 0;
}

UINT UpdateRadarImage(void * dummy)
{
    CKCCIDlg * kcci = (CKCCIDlg *)dummy;
	BinaryString output; CString radarURL;
    bool dataDownloaded;

	/* If the radar update is set to be disabled when minimized or just flat disabled,
	 * then we should not even be in this thread, so kill it.
	 */

	if(GetDisableRadarUpdate() && ! kcci->radarSelect) return 0;
	if(GetDisableRadarWhenMinimized() && ! kcci->IsWindowVisible()) return 0;

	/* If the progress bar is being displayed, wait 10 ms */

	if(kcci->progressLock) _sleep(10);
    kcci->progressLock = true;

	TRACE("Updating Radar image...\n");

	/* Get the current radar image */

	GetRadarURL(kcci->m_RadarImage.GetCurSel(), radarURL);

	dataDownloaded = DownloadData(radarURL, output, * kcci);
    kcci->progressLock = false;
    if(!dataDownloaded) return 0;

	kcci->kcci->radarImage.reset();
	kcci->kcci->radarImage = output;
	kcci->radarImage.Decode((BYTE *)(const unsigned char *) output, output.length(), CXIMAGE_FORMAT_UNKNOWN);

	if(kcci->radarSelect)
	{
		kcci->image = &kcci->radarImage;
		kcci->m_View.SetBitmap(kcci->image->MakeBitmap());
	}

	kcci->radarSelect = false;

	if(kcci->hViewBitmap)
		DeleteObject(kcci->hViewBitmap);

	kcci->hViewBitmap = kcci->image->MakeBitmap();
	kcci->m_View.SetBitmap(kcci->hViewBitmap);
	kcci->RedrawWindow();
	kcci->CreateTrayIcon();
	return 0;
}

UINT UpdateForecastImage(void * dummy)
{
    CKCCIDlg * kcci = (CKCCIDlg *)dummy;
	BinaryString output;
    bool dataDownloaded;

	/* If the progress bar is being displayed, wait 10 ms */

	while(kcci->progressLock) _sleep(10);
    kcci->progressLock = true;

	TRACE("Updating forecast image...");

	/* Get the current forecast image */

	dataDownloaded = DownloadData("http://images.ibsys.com/des/images/weather/auto/extended_640x480.jpg", output, * kcci);
    kcci->progressLock = false;
    if(!dataDownloaded) return 0;

	kcci->kcci->forecastImage.reset();
	kcci->kcci->forecastImage = output;
	kcci->forecastImage.Decode((BYTE *)(const unsigned char *)output, output.length(), CXIMAGE_FORMAT_UNKNOWN);

	if(kcci->hViewBitmap)
		DeleteObject(kcci->hViewBitmap);

	kcci->hViewBitmap = kcci->image->MakeBitmap();
	kcci->m_View.SetBitmap(kcci->hViewBitmap);
	kcci->RedrawWindow();
	return 0;
}

UINT UpdateCameraList(void * dummy)
{
    CKCCIDlg * kcci = (CKCCIDlg *)dummy;
	BinaryString output; SString data;
    bool dataDownloaded;

	/* If the progress bar is being displayed, wait 10 ms */

	while(kcci->progressLock) _sleep(10);
    kcci->progressLock = true;

	TRACE("Updating School Net data...\n");

	dataDownloaded = DownloadData("http://mesonet.agron.iastate.edu/data/csv/camera.dat", output, * kcci);
    kcci->progressLock = false;
    if(!dataDownloaded) return 0;

	data.append(output, output.length());

	kcci->kcci->cameraList = output;

	ParseCameraList(data, kcci->cameraList);
	return 0;
}


int FindStationIndex(const char * stationID, LinkedList & input)
{
	KCCIStationList * kcci;

	for(int x = 0; x < input.size(); x++)
	{
		kcci = (KCCIStationList * )input.elementAt(x);
		if(kcci->stationID.compareToIgnoreCase(stationID) == 0) return x;
	}
	
	return 0;
}

UINT UpdateSchoolNetStations(void * dummy)
{
	CKCCIDlg * kcci = (CKCCIDlg *)dummy;
	BinaryString output; SString list;
	int curSel; CString currentStation;
    bool downloadedData;

	/* If the progress bar is being displayed, wait 10 ms */

	while(kcci->progressLock) _sleep(10);
    kcci->progressLock = true;

	/* Download the list */

	TRACE("Updating School Net station list...\n");

	downloadedData = DownloadData("http://mesonet.agron.iastate.edu/data/csv/kcci.stns", output, * kcci);
    kcci->progressLock = false;
    if(!downloadedData) return 0;

	list.append(output, output.length());

	/* Parse the data and repopulate the list */

	kcci->kcci->schoolNetStations = output;

	ParseSchoolNetStationList(list, kcci->schoolNetStations);
	UpdateSchoolNetData(dummy);

	/* Get the current station */

	curSel = kcci->m_SchoolNetStation.GetCurSel();
	FindStationID(curSel, kcci->schoolNetStations, currentStation);

	PopulateStationList(kcci->schoolNetStations, kcci->m_SchoolNetStation);

	/* Restore the current station */

	kcci->m_SchoolNetStation.SetCurSel(FindStationIndex(currentStation, kcci->schoolNetStations));
	return 0;
}

UINT UpdateFeaturetteImage(void * dummy)
{
	/* In this case, the dummy is an array of integers, all of which are pointers.
	 * The first is a pointer to the URL to download the image, the second is a pointer
	 * to the CxImage object to render the image, the third is a pointer to the
	 * progress bar, the fourth is a pointer to a CDialog object, and the fifth is a
	 * pointer to a CStatic object (the image view).
	 */

	int * array = (int *)dummy;
	BinaryString output;

	char * imageURL = (char *)array[0];
	CxImage * image = (CxImage *)array[1];
	CProgressCtrl * progress = (CProgressCtrl * )array[2];
	CDialog * dlg = (CDialog *)array[3];
	CStatic * view = (CStatic *)array[4];

	TRACE("Updating featurette...\n");

	/* Show the progress bar, download the data, then hide the bar */

	progress->SetPos(0);
	progress->ShowWindow(SW_NORMAL);
	DownloadData(imageURL, output, * progress);

	TRACE("Hiding progress bar\n");

	progress->ShowWindow(SW_HIDE);

	/* Render the image */

	image->Decode((BYTE *)(const unsigned char *)output, output.length(), CXIMAGE_FORMAT_UNKNOWN);
	view->SetBitmap(image->MakeBitmap());

	if(strstr(imageURL, "schoolnet8") != NULL) delete [] imageURL;
	delete [] array;

	return 0;
}
