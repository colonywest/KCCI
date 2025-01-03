#include "BinaryString.h"
#include "BinaryToken.h"

#include <stdio.h>
#include <string.h>

void main()
{
    BinaryString q;
    int x;
    char * y = "HTTP/1.1 200 OK\x0d\x0aHost: kenneth\x0d\x0aConnection: Close\x0d\x0a\x0d\x0aHello there";
    unsigned char CRLF [] = { 13, 10, 13, 10 };

    q += 'a'; q += 'b';
    q += 'a'; q += 'b';
    q += 'a'; q += 'b';
    q += 'a'; q += 'b';

    BinaryToken w(q, 'a');
    printf("Number of tokens: %i\n", w.count());
    while(w.moreTokens())
    {
        BinaryString r = w.nextToken();
        if(r.length() > 0) printf("%c", r[0]);
    }

    q.set(y, strlen(y));
    printf("\n%i\n", q.indexOf(CRLF, 4));
}

