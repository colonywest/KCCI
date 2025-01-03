#include "stdafx.h"

/* Checks for a newer version */

#include <winsock2.h>

#include "BinaryString.h"
#include "HttpComm.h"
#include "SString.h"
#include "Registry.h"

bool DownloadData(const char * url, BinaryString & output)
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
	}

	/* Close the socket and return */

	if(httpComm.chunked) parseChunkedBody(output);
	closesocket(httpComm.socket);
	return true;
}

#define MAJOR_VERSION 2
#define MINOR_VERSION 4
#define REVISION 1

bool CheckNewerVersion()
{
	BinaryString output;
	SString version;

	int major, minor, revision;

	if(!DownloadData("http://kcci.kennethballard.com/version.txt", output)) return false;
	
	version.append(output, output.length()); version.trim();

	sscanf(version, "%i.%i.%i", & major, & minor, & revision);

	if(major > MAJOR_VERSION) return true;
    if(major == MAJOR_VERSION && minor > MINOR_VERSION) return true;
    if(major == MAJOR_VERSION && minor == MINOR_VERSION && revision > REVISION) return true;
	return false;
}
