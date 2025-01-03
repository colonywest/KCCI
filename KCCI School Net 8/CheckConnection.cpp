#include "stdafx.h"

#include <winsock2.h>

#include "IPExport.h"
#include "ICMPAPI.h"
#include "WinInet.h"

#include "KCCI.h"
#include "KCCIDlg.h"
#include "Waiting.h"

#include "Registry.h"

/* Attempts to connect to the proxy server */

bool CheckProxyConnection()
{
	CString temp; GetProxyServer(temp);
	SOCKET s; int r;
	sockaddr_in sa;

	hostent * hostEnt = gethostbyname(temp);
	if(hostEnt == NULL) return false;

    memset(&sa, 0, sizeof(sockaddr_in));
    sa.sin_family = AF_INET;
    sa.sin_port = htons(GetProxyPort());
    memcpy((char *)&sa.sin_addr, hostEnt->h_addr, hostEnt->h_length);

	s = socket(AF_INET, SOCK_STREAM, 0);
	if(s == INVALID_SOCKET) return false;

	r = connect(s, (sockaddr *)&sa, sizeof(sockaddr_in));
	closesocket(s);

	if(r != SOCKET_ERROR) return true;
	else return false;
}

/* Checks to see if there is an active Internet connection by pinging the root
 * Internet servers.
 */

bool CheckConnection()
{
	/* List of the 13 root servers pre-formatted as long values for use in the ICMP
	 * library provided by Microsoft
	 */

	unsigned long rootServers [13] = { 
		MAKELONG( MAKEWORD(198,  41), MAKEWORD(  0,   4) ),	// 198.41.0.4
		MAKELONG( MAKEWORD(192, 228), MAKEWORD( 79, 201) ),	// 192.228.79.201
		MAKELONG( MAKEWORD(192,  33), MAKEWORD(  4,  12) ),	// 192.33.4.12
		MAKELONG( MAKEWORD(128,   8), MAKEWORD( 10,  90) ),	// 128.8.10.90
		MAKELONG( MAKEWORD(192, 203), MAKEWORD(230,  10) ),	// 192.203.230.10
		MAKELONG( MAKEWORD(192,   5), MAKEWORD(  5, 241) ),	// 192.5.5.241
		MAKELONG( MAKEWORD(192, 112), MAKEWORD( 36,   4) ),	// 192.112.36.4
		MAKELONG( MAKEWORD(128,  63), MAKEWORD(  2,  53) ),	// 128.63.2.53
		MAKELONG( MAKEWORD(192,  36), MAKEWORD(148,  17) ),	// 192.36.148.17
		MAKELONG( MAKEWORD(192,  58), MAKEWORD(128,  30) ),	// 192.58.128.30
		MAKELONG( MAKEWORD(193,   0), MAKEWORD( 14, 129) ),	// 193.0.14.129
		MAKELONG( MAKEWORD(198,  32), MAKEWORD( 64,  12) ),	// 198.32.64.12
		MAKELONG( MAKEWORD(202,  12), MAKEWORD( 27,  33) )	// 202.12.27.33
	
	};

	DWORD internetConnectionFlag;

	/* Set up some other variables to prepare for the ICMP request */

	HANDLE icmpHandle = IcmpCreateFile();
	int size = sizeof(icmp_echo_reply) + 8, x;
	char * buff = new char [size];

	/* If using a proxy server, attempt to connect to it */

	if(GetUseProxy()) return CheckProxyConnection();

	/* Attempt to ping each of the 13 servers.  On the first response, 
	 * break out of the loop
	 */

	for(x = 0; x < 13; x++)
	{
		DWORD res = IcmpSendEcho(icmpHandle, rootServers [x], 0, 0, 0, buff, size, 1500);
		if(res) break;
	}

	/* Close the ICMP Handle */

	IcmpCloseHandle(icmpHandle);
	delete [] buff;

	/* If not all 13 servers were checked, one of them responded, so return True.
	 * Otherwise, we need to take another approach to checking for an Internet connection:
	 * going through Internet Explorer.
	 */

	if(x < 13) return true;
	
	if(InternetGetConnectedState(& internetConnectionFlag, 0)) return true;
	else return false;
}
/*
UINT CheckConnection(void * dummy)
{
	CKCCIDlg * kcci = (CKCCIDlg *) dummy;
	if(!CheckConnection()) kcci->EndDialog(IDCANCEL);
	return 0;
}
*/

/*
UINT WaitingCheckConnection(void * dummy)
{
	CWaiting * dlg = (CWaiting * ) dummy;
	if(CheckConnection()) dlg->EndDialog(IDOK);
	return 0;
}
*/