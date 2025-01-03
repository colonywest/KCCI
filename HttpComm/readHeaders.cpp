#ifndef __cplusplus
#error This must be used with a C++ compiler
#endif

#include <stdio.h>
#include <winsock2.h>

#include "HttpComm.h"
#include "SString.h"
#include "Token.h"
#include "BinaryString.h"

void processError(HttpComm & );

bool readHeaders(int s, HttpComm & output)
{
    unsigned char CRLF [] = { 0x0D, 0x0A, 0x0D, 0x0A };
    unsigned char data [1024];
    const unsigned char * p;

    BinaryString binaryBuf;
    SString tempString, tokenString, headerString;
    Token * l, * m;
    int x;

    /* Retrieve and delete the temporary storage */

    binaryBuf.append(output.databuf, output.databuflen);
    delete [] output.databuf;
    output.databuflen = 0;

    /* Check the buffer for a CRLFCRLF combination */

    while(binaryBuf.indexOf(CRLF, 4) < 0)
    {
        /* Read in 1024 bytes */

        x = recv(s, (char *)data, 1024, 0);

        if(x == SOCKET_ERROR)
        {
            processError(output);
            closesocket(s);
            return false;
        }
        else if(x == -1)
        {
            closesocket(s);
            strcpy(output.errorMessage, "Socket unexpectedly closed");
            return false;
        }

        binaryBuf.append(data, x);
    }

    /* CRLFCRLF found, so parse the headers.  We are only interested in
     * the Content-Length header.
     */

    tempString.append(binaryBuf, binaryBuf.indexOf(CRLF, 4));
    output.contentLength = -1;

    l = new Token(tempString, "\n");
    while(l->moreTokens())
    {
        l->nextToken(tokenString); tokenString.trim();
        m = new Token(tokenString, ": ");
        m->nextToken(headerString);
        if(headerString.compareToIgnoreCase("Content-Length") == 0)
        {
            m->nextToken(headerString);
            headerString.trim();
            output.contentLength = atoi(headerString);
        }
		if(headerString.compareToIgnoreCase("Transfer-Encoding") == 0)
		{
			m->nextToken(headerString);
			headerString.trim(); headerString.toLowerCase();
			if(headerString.indexOf("chunked") >= 0)
				output.chunked = 1;
			else output.chunked = 0;
		}

        delete m;
    }
    delete l;

    /* Save the downloaded data */

    x = binaryBuf.indexOf(CRLF, 4); p = binaryBuf; p += x + 4;
    output.databuflen = binaryBuf.length() - (x + 4);
    if(output.databuflen > 0)
    {
        output.databuf = new unsigned char[output.databuflen];
        memcpy(output.databuf, p, output.databuflen);
    }
    else output.databuflen = 0;
    return true;
}
