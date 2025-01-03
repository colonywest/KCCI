#ifndef __cplusplus
#error This must be used with a C++ compiler
#endif

#include <stdio.h>
#include <winsock2.h>

#include "HttpComm.h"
#include "SString.h"
#include "BinaryString.h"

HttpComm::HttpComm()
{
    httpStatusCode = 0;
    contentLength = 0;
    databuf = NULL;
    databuflen = 0;
    socket = 0;
	chunked = 0;
}

HttpComm::~HttpComm()
{
    if(databuflen) delete [] databuf;
}

HttpRequest::HttpRequest()
{
    host = NULL;
    port = 0;
    requestData = NULL;
    requestDataLength = 0;
}

HttpRequest::~HttpRequest()
{
    delete [] host;
    if(requestDataLength) delete [] requestData;
}

bool readStatusLine(int , HttpComm & );
bool readHeaders(int , HttpComm & );
void readData(int);
int openConnection(const char * , int );

void processError(HttpComm & p)
{
    int error = WSAGetLastError();

    switch(error)
    {
    case WSANOTINITIALISED:
        strcpy(p.errorMessage, "Windows Socket API not initialized");
        break;

    case WSAENETDOWN:
        strcpy(p.errorMessage, "Network appears to be down");
        break;

    case WSAHOST_NOT_FOUND:
        strcpy(p.errorMessage, "Could not find host");
        break;

    case WSATRY_AGAIN:
        strcpy(p.errorMessage, "Could not connect to host");
        break;

    case WSANO_RECOVERY:
        strcpy(p.errorMessage, "Nonrecoverable error occurred");
        break;

    case WSAETIMEDOUT:
        strcpy(p.errorMessage, "Connection timed out");
        break;

    default:
        sprintf(p.errorMessage, "Unknown error: %i", error);
        break;
    };
}

bool attemptConnect(HttpRequest & input, HttpComm & output)
{
    /* Open a socket connection to the host.  Uses NBIO. */

    unsigned long x = 1;

    SOCKET s = openConnection(input.host, input.port);

    if(s == SOCKET_ERROR)
    {
        output.socket = -1;
        processError(output);
        return false;
    }

    /* Send the request */

    if(send(s, (char *)input.requestData, input.requestDataLength, 0) == SOCKET_ERROR)
    {
        processError(output);
        closesocket(s);
        output.socket = -1;
        return false;
    }

    /* Read in and parse the status line */

    if(!readStatusLine(s, output)) { output.socket = -1; return false; }

    /* Read in and parse the response headers */

    if(!readHeaders(s, output)) { output.socket = -1; return false; }

    /* Change the socket to non-blocking IO */

    if(ioctlsocket(s, FIONBIO, &x) == SOCKET_ERROR)
    {
        processError(output);
        closesocket(s);
        output.socket = -1;
        return false;
    }

    /* If the status code is anything but 2xx, read in the remaining data
     * and close the connection.
     */

    if(output.httpStatusCode / 100 != 2)
    {
        readData(s);
        output.socket = -1;
        delete [] output.databuf;
        output.databuflen = 0;
        return false;
    }

    output.socket = s;
    return true;
}

int openConnection(const char * host, int port)
{
    SOCKET u;
    sockaddr_in sa;
    hostent * i;
    int r;

    i = gethostbyname(host);
    if(i == NULL) { return SOCKET_ERROR; }

    memset(&sa, 0, sizeof(sockaddr_in));
    sa.sin_family = AF_INET;
    sa.sin_port = htons(port);
    memcpy((char *)&sa.sin_addr, i->h_addr, i->h_length);

    u = socket(AF_INET, SOCK_STREAM, 0);
    if(u == INVALID_SOCKET) return SOCKET_ERROR;

    r = connect(u, (sockaddr *)&sa, sizeof(sockaddr_in));
    if(r == SOCKET_ERROR) { return r; }

    return u;
}

int isSocketOpen(int t)
{
    char p; int q;

    if(t == 0) return 0;

    q = recv(t, &p, 1, MSG_PEEK);

    if(q == SOCKET_ERROR)
    {
        switch(WSAGetLastError())
        {
        case WSAENOTCONN: return 0;
        case WSAESHUTDOWN: return 0;
        case WSAEWOULDBLOCK: return 1;
        default: return -1;
        }
    }

    return q;
}

int dataPending(int s)
{
    int r; unsigned long p;
    r = ioctlsocket(s, FIONREAD, &p);
    if(r == SOCKET_ERROR) return r;
    else return p;
}

void parseChunkedBody(BinaryString & data)
{
	unsigned char CRLF [] = { 0x0D, 0x0A };
	SString temp; int x = 0, chunkSize;
	BinaryString output, binaryTemp = data;
	unsigned char * p;

	while(x >= 0)
	{
		/* Find the size of the chunk */

		p = (unsigned char *)(const unsigned char *)binaryTemp;
		x = binaryTemp.indexOf(CRLF, 2);
		temp.append(binaryTemp, x);
		sscanf(temp, "%x", &chunkSize);
		p += x + 2;

		if(chunkSize == 0) break;

		/* Copy the chunk */

		output.append(p, chunkSize);
		temp.reset();

		/* Delete out of the temp the chunk */

		p += chunkSize;	// Advance to next CRLF
		p += 2;			// Advance beyond CRLF

		binaryTemp.set(p, binaryTemp.length() - (x + 2 + chunkSize + 2));
	}

	data = output;
}
