#include "BinaryString.h"

#include <string.h>
#include <stdlib.h>
#include <stdio.h>

BinaryString::BinaryString()
{
    buf = NULL;
    buflength = 0;
    alloclength = 0;
}

BinaryString::BinaryString(const BinaryString & p)
{
    buf = new unsigned char[p.buflength];
    memcpy(buf, p.buf, p.buflength);
    buflength = p.buflength;
    alloclength = p.buflength;
}

BinaryString::BinaryString(const unsigned char * p, int l)
{
    if(l == 0) return;
    buf = new unsigned char[l];
    memcpy(buf, p, l);
    buflength = l;
    alloclength = l;
}

BinaryString::BinaryString(unsigned char p)
{
    buf = new unsigned char[1];
    buf[0] = p;
    buflength = 1;
    alloclength = 1;
}

BinaryString::~BinaryString()
{
    delete [] buf;
}

void BinaryString::reallocate(unsigned q)
{
    if(alloclength < q)
    {
        delete [] buf;
        buf = NULL;
    }

    if(buf == NULL)
    {
        buf = new unsigned char[q];
        alloclength = q;
    }
}

BinaryString & BinaryString::operator=(const BinaryString & p)
{
    reallocate(p.buflength);
    memcpy(buf, p.buf, p.buflength);
    buflength = p.buflength;
    return * this;
}

void BinaryString::operator=(unsigned char p)
{
    reallocate(1);
    buf[0] = p;
    buflength = 1;
}

void BinaryString::operator+=(BinaryString & p)
{
    if(buflength == 0)
    {
        set(p.buf, p.buflength);
        return;
    }

    unsigned char * q = new unsigned char[buflength];
    memcpy(q, buf, buflength);

    reallocate(buflength + p.buflength);

    memcpy(buf, q, buflength);
    memcpy(buf + buflength, p, p.buflength);
    buflength += p.buflength;
    delete [] q;
}

void BinaryString::operator+=(unsigned char p)
{
    if(buflength == 0)
    {
        set(&p, 1);
        return;
    }

    unsigned char * q = new unsigned char[buflength];
    memcpy(q, buf, buflength);

    reallocate(buflength + 1);

    memcpy(buf, q, buflength);
    buf[buflength] = p;
    buflength ++;
    delete [] q;
}

BinaryString BinaryString::operator+(BinaryString & p)
{
    BinaryString q(buf, buflength);
    q += p;
    return q;
}

BinaryString BinaryString::operator+(unsigned char p)
{
    BinaryString q(buf, buflength);
    q += p;
    return q;
}

BinaryString::operator unsigned char * ()
{
	return buf;
}

BinaryString::operator const unsigned char * ()
{
	return buf;
}

unsigned char & BinaryString::operator [] (int p)
{
    return * (buf + p);
}

int BinaryString::length()
{
    return buflength;
}

void BinaryString::reset()
{
    buflength = 0;
}

void BinaryString::append(const unsigned char * p, int l)
{
    if(l == 0 || p == NULL) return;
    if(buflength == 0) { set(p, l); return; }

    /* Store the current buffer */

    unsigned char * q = new unsigned char [buflength + l];
    memcpy(q, buf, buflength);
    memcpy(q + buflength, p, l);

    /* Reallocate the buffer and copy it back */

    delete [] buf; buf = q;
    alloclength = buflength + l; buflength += l;
}

void BinaryString::append(const char * p)
{
    size_t l;
    if(p == NULL) return; l = strlen(p); if(l == 0) return;
    if(buflength == 0)
	{ 
		set((unsigned char *)p, l); 
		return;
	}

    /* Store the current buffer */

    unsigned char * q = new unsigned char [buflength + l + 1];
    memcpy(q, buf, buflength);
    memcpy(q + buflength, p, l);

    /* Reallocate the buffer and copy it back */

    reallocate(buflength + l); buflength += l;
    memcpy(buf, q, buflength + l);
    delete [] q;
}

void BinaryString::set(const unsigned char * p, int l)
{
    if(l == 0 || p == NULL) return;
    reallocate(l);
    memcpy(buf, p, l);
    buflength = l;
}

int BinaryString::indexOf(BinaryString & p)
{
    return indexOf(p.buf, p.buflength);
}

int BinaryString::indexOf(unsigned char p)
{
    int x;
    if(buflength == 0) return -1;
    for(x = 0; x < buflength; x++)
        if(buf[x] == p) return x;
    return -1;
}

int BinaryString::indexOf(const unsigned char * p, int l)
{
    int x;
    if(buflength == 0) return -1;
    if(l == 0) return -1;
    for(x = 0; x < buflength - l + 1; x++)
        if(memcmp(buf + x, p, l) == 0) return x;
    return -1;
}
