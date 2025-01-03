#include "BinaryToken.h"
#include <string.h>

BinaryToken::BinaryToken(BinaryString & p, BinaryString & d)
{
    bstr = p;
    delim = d;
    pos = 0;
}

BinaryToken::BinaryToken(BinaryString & p, unsigned char d)
{
    bstr = p;
    delim = d;
    pos = 0;
}

BinaryToken::BinaryToken(BinaryString & p, unsigned char * d, int l)
{
    bstr = p;
    delim.set(d, l);
    pos = 0;
}

BinaryToken::BinaryToken(unsigned char * p, int l, BinaryString & d)
{
    bstr.set(p, l);
    delim = d;
    pos = 0;
}

BinaryToken::BinaryToken(unsigned char * p, int l, unsigned char d)
{
    bstr.set(p, l);
    delim = d;
    pos = 0;
}

BinaryToken::BinaryToken(unsigned char * p, int l, unsigned char * d, int m)
{
    bstr.set(p, l);
    delim.set(d, m);
    pos = 0;
}

void BinaryToken::reset()
{
    pos = 0;
}

int BinaryToken::moreTokens()
{
    if(pos == -1) return 0;
    return 1;
}

int BinaryToken::count()
{
    int c = 0, x;
    if(pos == -1) return 0;
    for(x = pos; x < bstr.length() - delim.length() - 1; )
    {
        if(memcmp(delim, (const unsigned char *)bstr + x, delim.length()) != 0)
        {
            x++;
            continue;
        }
        x += delim.length();
        c++;
    }
    c++; return c;
}

void BinaryToken::newToken(BinaryString & p, BinaryString & d)
{
    bstr = p;
    delim = d;
    pos = 0;
}

void BinaryToken::newToken(BinaryString & p, unsigned char d)
{
    bstr = p;
    delim = d;
    pos = 0;
}

void BinaryToken::newToken(BinaryString & p, unsigned char * d, int l)
{
    bstr = p;
    delim.set(d, l);
    pos = 0;
}

void BinaryToken::newToken(unsigned char * p, int l, BinaryString & d)
{
    bstr.set(p, l);
    delim = d;
    pos = 0;
}

void BinaryToken::newToken(unsigned char * p, int l, unsigned char d)
{
    bstr.set(p, l);
    delim = d;
    pos = 0;
}

void BinaryToken::newToken(unsigned char * p, int l, unsigned char * d, int m)
{
    bstr.set(p, l);
    delim.set(d, m);
    pos = 0;
}

BinaryString BinaryToken::nextToken()
{
    BinaryString p;
    token(p);
    return p;
}

BinaryString BinaryToken::nextToken(BinaryString & d)
{
    BinaryString p;
    delim = d;
    token(p);
    return p;
}

BinaryString BinaryToken::nextToken(unsigned char d)
{
    BinaryString p;
    delim = d;
    token(p);
    return p;
}

BinaryString BinaryToken::nextToken(unsigned char * d, int l)
{
    BinaryString p;
    delim.set(d, l);
    token(p);
    return p;
}

void BinaryToken::token(BinaryString & q)
{
    const unsigned char * p = bstr; p += pos;
    const unsigned char * n = p;
    if(pos == -1) return;

    int x, z;

    /* Beginning at pos, find the next occurence of the delimiter */

    for(x = pos; x < bstr.length(); x++)
    {
        z = memcmp(delim, p, delim.length());
        if(z != 0) { p ++; continue; }

        /* Find the length of the token we just marked */

        q.append(n, x - pos);
        pos = x + delim.length();
        if(pos == bstr.length()) pos = -1;
        return;
    }

    q.set(p, x - pos);
    pos = -1;
    return;
}
