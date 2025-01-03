#include "stdafx.h"

#include <winsock2.h>

#include "KCCI.h"
#include "KCCIDlg.h"
#include "FeaturetteProgress.h"

#include "Registry.h"

#include "xImage.h"
#include "HttpComm.h"
#include "BinaryString.h"
#include "SString.h"

bool DownloadData(const char * url, BinaryString & output, CKCCIDlg & kcci)
{
	HttpComm httpComm;
	HttpRequest httpRequest;

	unsigned char buffer [16384]; int frame = 1;
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

	kcci.m_Progress.SetPos(0);
	kcci.m_Progress.SetRange32(0, httpComm.contentLength);
	kcci.m_Progress.SetPos(httpComm.databuflen);

	kcci.m_Progress.ShowWindow(SW_NORMAL);

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
				kcci.m_Progress.ShowWindow(SW_HIDE);
				return false;
			}

			continue;
		}
        else if(pending == SOCKET_ERROR)
        {
            closesocket(httpComm.socket);
            kcci.m_Progress.ShowWindow(SW_HIDE);
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
			kcci.m_Progress.ShowWindow(SW_HIDE);
			return false; 
		}

		output.append(buffer, y);
		kcci.m_Progress.SetPos(kcci.m_Progress.GetPos() + y);
	}

	/* Close the socket and return */

	closesocket(httpComm.socket);
	kcci.m_Progress.ShowWindow(SW_HIDE);
	if(httpComm.chunked) parseChunkedBody(output);
	return true;
}

bool DownloadData(const char * url, BinaryString & output, CFeaturetteProgress & dlg)
{
	HttpComm httpComm;
	HttpRequest httpRequest;

	unsigned char buffer [16384]; int frame = 1;
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

	dlg.m_Progress.SetPos(0);
	dlg.m_Progress.SetRange32(0, httpComm.contentLength);
	dlg.m_Progress.SetPos(httpComm.databuflen);

	dlg.UpdateWindow();
	dlg.PumpMessages();

	/* Clear the buffer and send to it what was already downloaded */

	output.reset();
	output.append(httpComm.databuf, httpComm.databuflen);

	currentTime = time(NULL);

	/* Continue downloading the rest of the data until the socket is closed */

	while(isSocketOpen(httpComm.socket))
	{
		int y, pending;

		dlg.UpdateWindow();
		dlg.PumpMessages();

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
		dlg.m_Progress.SetPos(dlg.m_Progress.GetPos() + y);
	}

	/* Close the socket and return */

	closesocket(httpComm.socket);
	if(httpComm.chunked) parseChunkedBody(output);
	return true;
}

bool DownloadData(const char * url, BinaryString & output, CProgressCtrl & progress)
{
	HttpComm httpComm;
	HttpRequest httpRequest;

	unsigned char buffer [1024];
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

	progress.SetRange32(0, httpComm.contentLength);
	progress.SetPos(httpComm.databuflen);

	/* Clear the buffer and send to it what was already downloaded */

	output.reset();
	output.append(httpComm.databuf, httpComm.databuflen);

	currentTime = time(NULL);

	/* Continue downloading the rest of the data until the socket is closed */

	while(isSocketOpen(httpComm.socket))
	{
		int y;

		/* Check to see if data is available */

		if(!dataPending(httpComm.socket))
		{
			/* Have we timed out? */

			if(time(NULL) > currentTime + timeout)
			{
				closesocket(httpComm.socket);
				return false;
			}

			continue;
		}

		/* Download and store the data and update the current time for
		 * the next timeout check.
		 */

		y = recv(httpComm.socket, (char *)buffer, 1024, 0);
		currentTime = time(NULL);

		if(y == SOCKET_ERROR)
		{ 
			closesocket(httpComm.socket); 
			return false; 
		}

		output.append(buffer, y);
		progress.SetPos(progress.GetPos() + y);
	}

	/* Close the socket and return */

	if(httpComm.chunked) parseChunkedBody(output);
	closesocket(httpComm.socket);
	return true;
}
