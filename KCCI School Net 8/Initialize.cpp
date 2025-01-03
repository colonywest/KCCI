#include "stdafx.h"

#include <winsock2.h>

#include "KCCI.h"
#include "KCCIDlg.h"
#include "Splash.h"

#include "../HttpComm/HttpComm.h"
#include "KCCISchoolNet.h"

#include "Registry.h"
#include "Radar.h"

bool DownloadData(const char * url, BinaryString & output, CSplash & dlg)
{
	HttpComm httpComm;
	HttpRequest httpRequest;

	unsigned char buffer [16384];
	CString proxyServer; int proxyPort; bool useProxy = false;
	int timeout = GetDefaultTimeout(), currentTime;

	/* Use a proxy server? */

	if(GetUseProxy())
	{
		useProxy = true;
		GetProxyServer(proxyServer);
		proxyPort = GetProxyPort();
	}

	/* Create the request and attempt to connect to the server */

	if(useProxy) newProxyRequest(httpRequest, url, proxyServer, proxyPort);
	else newRequest(httpRequest, url);

	if(!attemptConnect(httpRequest, httpComm)) return false;

	/* Set up the progress bar, setting it's position to what was already downloaded */

	dlg.m_Progress.SetRange32(0, httpComm.contentLength);
	dlg.m_Progress.SetPos(httpComm.databuflen);


	/* Clear the buffer and send to it what was already downloaded */

	output.reset();
	output.append(httpComm.databuf, httpComm.databuflen);

	currentTime = time(NULL);

	/* Continue downloading the rest of the data until the socket is closed */

	while(isSocketOpen(httpComm.socket))
	{
		int y, pending;

		/* Check to see if data is available */

        pending = dataPending(httpComm.socket);

		if(pending == 0)
		{
			/* Have we timed out? */

			if(time(NULL) > currentTime + timeout)
			{
				closesocket(httpComm.socket);
				return false;
			}

			/* Return to the start of the loop */

			dlg.UpdateWindow();
			dlg.PumpMessages();
			continue;
		}
        else if(pending == SOCKET_ERROR)
        {
            closesocket(httpComm.socket);
            return false;
        }

		/* Download and store the data and update the current time for
		 * the next timeout check.
		 */

        if(pending > 16384) pending = 16384;

		y = recv(httpComm.socket, (char *)buffer, pending, 0);
		currentTime = time(NULL);

		if(y == SOCKET_ERROR)
		{ 
			closesocket(httpComm.socket); 
			return false; 
		}

		output.append(buffer, y);

		/* Update the progress bar and the window */

		dlg.m_Progress.SetPos(dlg.m_Progress.GetPos() + y);
		dlg.UpdateWindow();		
		dlg.PumpMessages();
	}

	/* Close the socket and return */

	closesocket(httpComm.socket);
	return true;
}

/* Downloads the School Net station list */

bool DownloadSchoolNetStations(BinaryString & output, CSplash & dlg)
{
	dlg.m_Status.SetWindowText("Downloading School Net Stations...");
	return DownloadData("http://mesonet.agron.iastate.edu/data/csv/kcci.stns", output, dlg);
}

/* Downloads the School Net data */

bool DownloadSchoolNetData(BinaryString & output, CSplash & dlg)
{
	dlg.m_Status.SetWindowText("Downloading School Net network data...");
	return DownloadData("http://mesonet.agron.iastate.edu/data/csv/kcci.dat", output, dlg);
}

/* Downloads the Camera list */

bool DownloadCameraList(BinaryString & output, CSplash & dlg)
{
	dlg.m_Status.SetWindowText("Downloading School Net camera list...");
	return DownloadData("http://mesonet.agron.iastate.edu/data/csv/camera.dat", output, dlg);
}

/* Downloads the Radar image */

bool DownloadRadarImage(BinaryString & output, CSplash & dlg)
{
	CString radarURL;

	dlg.m_Status.SetWindowText("Downloading Super Doppler Radar image...");
	GetRadarURL(GetDefaultRadarImage(), radarURL);
	return DownloadData(radarURL, output, dlg);
}

/* Downlads the Forecast image */

bool DownloadForecastImage(BinaryString & output, CSplash & dlg)
{
	dlg.m_Status.SetWindowText("Downloading Super Doppler Forecast image...");
	return DownloadData("http://images.ibsys.com/des/images/weather/auto/extended_640x480.jpg", output, dlg);
}

/* Downloads the School Net station list, School Net data, Camera list, Radar image,
 * and Forecast image from the Internet.  It assumes there's an active connection.
 */

bool Initialize(KCCISchoolNet & output)
{
	CSplash splash;

	/* Create the dialog box */

	splash.Create(IDD_Splash);
	splash.ShowWindow(SW_NORMAL);
	splash.UpdateWindow();

	/* Download the School Net station list */

	if(!DownloadSchoolNetStations(output.schoolNetStations, splash))
	{
		MessageBox(NULL, "Error while downloading School Net station list", "Error", MB_OK | MB_ICONEXCLAMATION);
//		splash.DestroyWindow();
//		return false;
	}

	splash.m_Progress.SetPos(0);

	/* Download the School Net network data */

	if(!DownloadSchoolNetData(output.schoolNetData, splash))
	{
		MessageBox(NULL, "Error while downloading School Net network data", "Error", MB_OK | MB_ICONEXCLAMATION);
//		splash.DestroyWindow();
//		return false;
	}

	splash.m_Progress.SetPos(0);

	/* Download the Camera list */

	if(!DownloadCameraList(output.cameraList, splash))
	{
		MessageBox(NULL, "Error while downloading the Web camera list", "Error", MB_OK | MB_ICONEXCLAMATION);
//		splash.DestroyWindow();
//		return false;
	}

	splash.m_Progress.SetPos(0);

	/* Download the Radar image */

	if(!DownloadRadarImage(output.radarImage, splash))
	{
		MessageBox(NULL, "Error while downloading Super Doppler Radar image", "Error", MB_OK | MB_ICONEXCLAMATION);
//		splash.DestroyWindow();
//		return false;
	}

	splash.m_Progress.SetPos(0);

	/* Download the Forecast image */

	if(!DownloadForecastImage(output.forecastImage, splash))
	{
		MessageBox(NULL, "Error while downloading Super Doppler Forecast image", "Error", MB_OK | MB_ICONEXCLAMATION);
//		splash.DestroyWindow();
//		return false;
	}

	/* Destroy the dialog and return */

	splash.DestroyWindow();
	return true;
}
