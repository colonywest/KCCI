#ifndef __cplusplus
#error This must be used with a C++ compiler
#endif

#include "BinaryString.h"

#ifndef HTTPCOMM_H
#define HTTPCOMM_H

class HttpComm
{
public:
    HttpComm();
    ~HttpComm();

    /* The HTTP status code and the value from the "Content-Length" header.
     * If there was not a "Content-Length" header, then a -1 is filled in
     * here instead.
     */

    short httpStatusCode;
    long contentLength;

    /* Error message if there was an error */

    char errorMessage[100];

    /* Data already downloaded so it can be subtracted from the content
     * length, if one exists.
     */

    unsigned char * databuf;
    unsigned long databuflen;

    /* Socket to download the rest of the data */

    int socket;
	int chunked;
};

class HttpRequest
{
public:
    HttpRequest();
    ~HttpRequest();

    char * host;
    int port;
    unsigned char * requestData;
    long requestDataLength;
};

bool newRequest(HttpRequest &, const char * , const char * = NULL);
bool newProxyRequest(HttpRequest &, const char *, const char * , int, const char * = NULL);

bool attemptConnect(HttpRequest & , HttpComm & );
int isSocketOpen(int );
int dataPending(int );

void parseChunkedBody(BinaryString &);

#endif
