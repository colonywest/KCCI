#include <string>
using namespace std;

#ifndef URL_H
#define URL_H

class URL
{
public:
    int parse(const char *);

    const char * getProtocol();
    const char * getHost();
    const char * getFile();
    const char * getURI();
    const char * getParams();
    const char * getFullFile();
    int getPort();

private:
    string prot;               /* Protocol */
    string host;               /* Host name */
    int port;                  /* Port number */
    string file;               /* File path */
    string params;             /* Parameters to the file path */
    string fullfile;           /* Full path and parameters */

    string uri;                /* Full URI */
};

#endif
