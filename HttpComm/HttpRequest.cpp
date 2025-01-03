// Functions used to set up an HttpRequest structure

#ifndef __cplusplus
#error This must be used with a C++ compiler
#endif

#include <stdio.h>
#include <winsock2.h>

#include "HttpComm.h"
#include "SString.h"
#include "URL.h"

/* Creates a blank request to the URL */

bool newRequest(HttpRequest & p, const char * url, const char * referer)
{
    URL y;
    SString blank;

    if(!y.parse(url)) return false;

    if(stricmp(y.getProtocol(), "http") != 0) return false;

    p.host = new char[strlen(y.getHost()) + 1];
    strcpy(p.host, y.getHost());
    p.port = y.getPort(); if(p.port == -1) p.port = 80;

    blank = "GET "; blank += y.getFullFile(); blank += " HTTP/1.1\r\n";
    blank += "Host: "; blank += y.getHost(); blank += "\r\n";
    blank += "Connection: close\r\n";
	blank += "Cache-Control: no-cache\r\n";
	blank += "Pragma: no-cache\r\n";
	blank += "User-Agent: KCCI School Net 8 Desktop Weather Client 2.0.2004\r\n";
    if(referer) { blank += "Referer: "; blank += referer; blank += "\r\n"; }
    blank += "\r\n";

    p.requestData = new unsigned char [blank.length()];
    memcpy(p.requestData, (const char *)blank, blank.length());
    p.requestDataLength = blank.length();

    return true;
}

bool newProxyRequest(HttpRequest & p, const char * url, const char * proxyHost, int proxyPort, const char * referer)
{
    URL y;
    SString blank;

    if(!y.parse(url)) return false;

    if(stricmp(y.getProtocol(), "http") != 0) return false;

    p.host = new char[strlen(proxyHost) + 1];
    strcpy(p.host, proxyHost);
    p.port = proxyPort; if(p.port == -1) p.port = 80;

    blank = "GET "; blank += url; blank += " HTTP/1.1\r\n";
    blank += "Host: "; blank += y.getHost(); blank += "\r\n";
    blank += "Connection: close\r\n";
 	blank += "Cache-Control: no-cache\r\n";
	blank += "Pragma: no-cache\r\n";
	blank += "User-Agent: KCCI School Net 8 Desktop Weather Client 2.0.2004\r\n";
	if(referer) { blank += "Referer: "; blank += referer; blank += "\r\n"; }
    blank += "\r\n";

    p.requestData = new unsigned char [blank.length()];
    memcpy(p.requestData, (const char *)blank, blank.length());
    p.requestDataLength = blank.length();

    return true;
}