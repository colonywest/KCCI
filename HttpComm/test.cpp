#include <stdio.h>
#include <winsock2.h>

#include "HttpComm.h"
#include "SString.h"

void main()
{
    HttpRequest httpRequest;
    HttpComm httpComm; int g, x, total;
    FILE * out;

    /* Initialize TCP */

    WSAData info;
    if(WSAStartup(MAKEWORD(2, 2), &info))
    {
        printf("Error starting Windows Socket API\n");
        return;
    }

    /* Create a request */

    newRequest(httpRequest, "http://kenneth/images/logo.png");
//    newRequest(httpRequest, "http://domai.com/-today/BoD-late-2003/lotte-666.jpg", "http://domai.com/pics/index.html");
//    newRequest(httpRequest, "http://images.ibsys.com/des/images/weather/auto/southwest_radar_640x480.gif");

    /* Attempt to send the request */

    if(attemptConnect(httpRequest, httpComm))
    {
        unsigned char data[1024];

        out = fopen("test.png", "wb");

        if(httpComm.databuflen)
            fwrite(httpComm.databuf, 1, httpComm.databuflen, out);

        total = httpComm.databuflen;
        printf("Status Code: %i\n", httpComm.httpStatusCode);
        printf("Content Length: %i\n", httpComm.contentLength);

        printf("Downloading: %i\r", total);

        while(isSocketOpen(httpComm.socket))
        {
            g = dataPending(httpComm.socket);
            if(g == 0) continue;
            else if(g < 0) break;

            x = recv(httpComm.socket, data, 1024, 0);
            if(x == SOCKET_ERROR || x == 0) break;
            total += x;

            printf("Downloading: %i\r", total);
            fwrite(data, 1, x, out);
        }

        if(x == SOCKET_ERROR || g == SOCKET_ERROR)
            printf("\nAborted due to error: %i", WSAGetLastError());

        closesocket(httpComm.socket);
        fclose(out);
        printf("\n");
    }
    else
    {
        printf("Connection failed: %s\n", httpComm.errorMessage);
    }

    WSACleanup();
}
