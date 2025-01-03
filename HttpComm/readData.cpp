#ifndef __cplusplus
#error This must be used with a C++ compiler
#endif

#include <stdio.h>
#include <winsock2.h>

#include "HttpComm.h"

void readData(int s)
{
    /* Since we are only reading until the socket is closed, just read in.
     */

    char data[1024];
    int x;

    while(s)
    {
        int g = dataPending(s);
        if(g == 0) continue;
        else if(g < 0) break;

        x = recv(s, data, 1024, 0);
        if(x == SOCKET_ERROR || x == 0) break;
    }

    closesocket(s);
}
