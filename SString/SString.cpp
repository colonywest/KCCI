#include "SString.h"
#include "Token.h"

using namespace std;

/* Default constructor */

SString::SString()
{
    buf = NULL;
    alloclength = 0;
}

/* Constructor - sets internal buffer to a single character */

SString::SString(char T)
{
    allocate(1);
    buf[0] = T;
}

/* Constructor - sets internal buffer equal to a string */

SString::SString(const char * T)
{
    unsigned long q;
    if(T == NULL) { buf = NULL; alloclength = 0; }
    else { q = strlen(T); allocate(q); strcpy(buf, T); }
}

/* Constructor - sets internal buffer equal to an STL string */

SString::SString(string & t)
{
    allocate(t.length());
    strcpy(buf, t.c_str());
}

/* Copy constructor */

SString::SString(const SString & T)
{
    allocate(strlen(T.buf));
    strcpy(buf, T.buf);
}

/* Destructor */

SString::~SString()
{
    delete [] buf;
}

/* Returns the length of the string */

int SString::length()
{
    if(buf == NULL) return 0;
    else return strlen(buf);
}

/* Resets the string to a null state */

void SString::reset()
{
    if(buf == NULL) return;
    buf[0] = 0;
}

int SString::compare(const char * t)
{
    if(buf == NULL) return 1;
    return strcmp(buf, t);
}

int SString::compareToIgnoreCase(const char * p)
{
    if(buf == NULL) return 1;
    return strcmpi(buf, p);
}

int SString::indexOf(char t)
{
    return indexOf(t, 0);
}

int SString::indexOf(char t, int u)
{
    int x;
    for(x = u; x < strlen(buf); x++)
    {
        if(buf[x] == t)
            return x;
    }

    return -1;
}

int SString::indexOf(const char * t)
{
    return indexOf(t, 0);
}

int SString::indexOf(const char * t, int u)
{
    int x;
    for(x = u; x < strlen(buf) - strlen(t) + 1; x++)
    {
        if(strncmp(buf + x, t, strlen(t)) == 0)
            return x;

    }

    return -1;
}

int SString::indexOf(string & t)
{
    return indexOf(t.c_str());
}

int SString::indexOf(string & t, int u)
{
    return indexOf(t.c_str(), u);
}

SString SString::left(int r)
{
    SString I = buf;
    I.setLength(r);
    return I;
}

SString SString::right(int r)
{
    SString I;
    unsigned long q = length() - r;
    I = buf + q;
    return I;
}

void SString::setLength(int r)
{
    if(r >= length()) return;
    buf[r] = 0;
}

SString SString::substring(int start, int len)
{
    String I;
    if(start >= length()) return I;
    I = buf + start;
    I.setLength(len);
    return I;
}

SString SString::substring(int start)
{
    String I;
    if(start < length()) I = buf + start;
    return I;
}

void SString::trim()
{
    char * u, * v, * w;

    if(length() == 0) return;

    /* First copy the internal buffer to a temporary buffer */

    u = new char[strlen(buf) + 1];
    strcpy(u, buf);

    /* Locate the first position where the character is not a
     * whitespace character using a second pointer.
     */

    v = u;
    while(*v != '\0' && strchr(" \r\n\f\t", *v) != NULL) v++;

    /* Now, using a third pointer, find the last occurrence of a
     * whitespace character.
     */

    if(* v != '\0')
    {
        w = strrchr(v, '\0') - 1;
        while(w > v && strchr(" \r\n\f\t", *w) != NULL) { *w = '\0'; w--; }
    }

    /* Now, copy the remaining buffer back into the internal buffer,
     * reallocating for it.
     */

    strcpy(buf, v);
    delete [] u;
}

/* Will append binary data to the end of the string, but will stop at the
 * first binary 0 it encounters.
 */

void SString::append(const unsigned char * p, int l)
{
    int w, x; char * y; w = length();

    /* Search for a binary 0 */

    for(x = 0; x < l; x++) { if(p[x] == 0) break; }
    y = new char[w + 1]; memset(y, 0, w + 1);
    if(buf != NULL) strcpy(y, buf);

    if(reallocate(w + x)) allocate(w + x);
    strcpy(buf, y); memcpy(buf + w, p, x);
    buf[w + x] = 0; delete [] y;
}

void SString::toUpperCase()
{
    strupr(buf);
}

void SString::toLowerCase()
{
    strlwr(buf);
}

/* Will return 1 if the buffer has been deleted, meaning it needed to be
 * reallocated for the requested amount.
 */

int SString::reallocate(unsigned long p)
{
    if(alloclength > p + 1) return 0;

    delete [] buf; buf = NULL; alloclength = 0;
    return 1;
}

void SString::allocate(unsigned long p)
{
    alloclength = p + 1;
    buf = new char[alloclength];
    memset(buf, 0, alloclength);
}

void SString::allocate(char * p)
{
    unsigned long q = strlen(p);
    alloclength = q + 1;
    buf = new char[alloclength];
    strcpy(buf, p);
}

void SString::set(const char * p)
{
    delete buf;
    allocate(strlen(p));
    strcpy(buf, p);
}
