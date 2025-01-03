#include "URL.h"
#include "Token.h"

/* Parse the given URL into the object */

int URL::parse(const char * url)
{
    int i, j; Token * Y; SString temp;

    uri = url; port = -1;

    /* First, validate that there are only two tokens. */

    Y = new Token(url, "://");
    Y->nextToken(prot);
    delete Y;

    /* Next, the host name.  To do this, search for a colon and a forward
     * slash.  Whichever comes first becomes the delimiter.
     */

    i = uri.find(':', prot.length() + 3);
    j = uri.find('/', prot.length() + 3);

    if(j < 0) j = uri.length();
    if(i < 0) i = j + 1;

    if(i < j) Y = new Token(uri.c_str() + prot.length() + 3, ':');
    else Y = new Token(uri.c_str() + prot.length() + 3, '/');

    Y->nextToken(host);

    if(i < j)
    {
        Y->nextToken('/', temp);
        port = atoi(temp);
    }
    else
        port = -1;

    /* Now for the file name and parameters */

    Y->nextToken('\xFF', temp);

    fullfile = "/"; fullfile += temp;

    delete Y;

    Y = new Token(fullfile.c_str(), "?");

    Y->nextToken(file);
    Y->nextToken('\xFF', params);

    delete Y;
    return 1;
}

const char * URL::getProtocol()
{
    return prot.c_str();
}

const char * URL::getFile()
{
    return file.c_str();
}

const char * URL::getHost()
{
    return host.c_str();
}

int URL::getPort()
{
    return port;
}

const char * URL::getURI()
{
    return uri.c_str();
}

const char * URL::getParams()
{
    return params.c_str();
}

const char * URL::getFullFile()
{
    return fullfile.c_str();
}
