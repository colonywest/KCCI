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

bool readStatusLine(int s, HttpComm & output)
{
    unsigned char CRLF [] = { 0x0D, 0x0A };
    unsigned char data [1024];
    const unsigned char * p;

    BinaryString binaryBuf;
    SString tempString, tokenString;
    Token * l;

    int x, dataLen;

    /* Read in 1024 bytes */

    x = recv(s, (char *)data, 1024, 0) ;

    if(x == SOCKET_ERROR)
    {
        processError(output);
        closesocket(s);
        return false;
    }

    binaryBuf.append(data, x);
	dataLen = x;

    /* Check for a CRLF */

    if(binaryBuf.indexOf(CRLF, 2) < 0)
    {
        closesocket(s);
        strcpy(output.errorMessage, "Does not appear to be an HTTP server");
        return false;
    }

    /* Parse the response */

    tempString.append(binaryBuf, binaryBuf.indexOf(CRLF, 2));

    l = new Token(tempString, " ");
    l->nextToken(tokenString);
    if(tokenString != "HTTP/1.1" && tokenString != "HTTP/1.0")
    {
        closesocket(s);
        strcpy(output.errorMessage, "Does not appear to be an HTTP server");
        return false;
    }

    /* Retrieve the status code and status message */

    l->nextToken(tokenString);
    sscanf(tokenString, "%i", &output.httpStatusCode);

    l->nextToken(tokenString);
    strncpy(output.errorMessage, tokenString, 99);
    output.errorMessage[99] = 0;

    delete l;

    x = binaryBuf.indexOf(CRLF, 2); p = binaryBuf; p += x + 2;
    output.databuf = new unsigned char[dataLen - 2 - x];
    output.databuflen = dataLen - 2 - x;
    memcpy(output.databuf, p, dataLen - 2 - x);
    return true;
}
