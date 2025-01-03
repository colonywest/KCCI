#include "SString.h"

using namespace std;

/* Type cast operator */

SString::operator const char * ()
{
    return buf;
}

SString::operator char * ()
{
    return buf;
}

/* Array operators */

char & SString::operator [] (int I)
{
    return * (buf + I);
}

/* Assignment operators */

SString & SString::operator = (char t)
{
    if(reallocate(1)) allocate(1);
    else buf[1] = 0;
    buf[0] = t;
    return * this;
}

SString & SString::operator = (const char * t)
{
    unsigned long q;
    if(t == NULL) { delete buf; buf = NULL; alloclength = 0; }
    else { q = strlen(t); if(reallocate(q)) allocate(q); strcpy(buf, t); }
    return * this;
}

SString & SString::operator = (string & t)
{
    unsigned long q = t.length();
    if(reallocate(q)) allocate(q);
    strcpy(buf, t.c_str());
    return * this;
}

SString & SString::operator = (const SString & t)
{
    unsigned long q = strlen(t.buf);
    if(reallocate(q)) allocate(q);
    strcpy(buf, t.buf);
    return * this;
}

/* Concatenation with assignment */

SString & SString::operator += (const char * t)
{
    unsigned long q; char * p;
    if(t == NULL) return * this;

    if(buf == NULL) { set(t); return * this; }

    q = strlen(t) + length();
    p = new char[length() + 1];
    strcpy(p, buf);
    if(reallocate(q)) { allocate(q); strcpy(buf, p); }
    strcat(buf, t); delete [] p;
    return * this;
}

SString & SString::operator += (string & t)
{
    unsigned long q; char * p;

    if(buf == NULL) { set(t.c_str()); return * this; }

    q = strlen(t.c_str()) + length();
    if(q == length()) return * this;
    p = new char[length() + 1];
    strcpy(p, buf);
    if(reallocate(q)) { allocate(q); strcpy(buf, p); }
    strcat(buf, t.c_str()); delete [] p;
    return * this;
}

SString & SString::operator += (char t)
{
    char * p; char r[2] = { t, 0 }; unsigned long q;

    if(buf == NULL) { set(r); return * this; }

    q = length() + strlen(r);
    if(q == length()) return * this;
    p = new char[length() + 1];
    strcpy(p, buf);
    if(reallocate(q)) { allocate(q); strcpy(buf, p); }
    strcat(buf, r); delete p;
    return * this;
}

/* Concatenation */

SString SString::operator + (const char * t)
{
    SString Y = buf;
    Y += t;
    return Y;
}

SString SString::operator + (string & t)
{
    SString Y = buf;
    Y += t;
    return Y;
}

SString SString::operator + (char t)
{
    SString Y = buf;
    Y += t;
    return Y;
}

/* Comparison */

short SString::operator < (const char * t)
{
    if(compare(t) < 0) return 1;
    else return 0;
}

short SString::operator <= (const char * t)
{
    if(compare(t) <= 0) return 1;
    else return 0;
}

short SString::operator == (const char * t)
{
    if(compare(t) == 0) return 1;
    return 0;
}

short SString::operator != (const char * t)
{
    if(compare(t) != 0) return 1;
    return 0;
}

short SString::operator > (const char * t)
{
    if(compare(t) > 0) return 1;
    else return 0;
}

short SString::operator >= (const char * t)
{
    if(compare(t) >= 0) return 1;
    else return 0;
}

short SString::operator > (string & t)
{
    if(compare(t.c_str()) > 0) return 1;
    else return 0;
}

short SString::operator >= (string & t)
{
    if(compare(t.c_str()) >= 0) return 1;
    else return 0;
}

short SString::operator == (string & t)
{
    if(compare(t.c_str()) == 0) return 1;
    else return 0;
}

short SString::operator != (string & t)
{
    if(compare(t.c_str()) != 0) return 1;
    else return 0;
}

short SString::operator < (string & t)
{
    if(compare(t.c_str()) < 0) return 1;
    else return 0;
}

short SString::operator <= (string & t)
{
    if(compare(t.c_str()) <= 0) return 1;
    else return 0;
}

istream & operator >> (istream &theStream, SString & T)
{
    char l; theStream.get(l);
    while(!theStream.eof() && l != '\n') { T += l; theStream.get(l); }
    return theStream;
}

ostream & operator << (ostream & theStream, SString & t)
{
    theStream.write((const char *) t, t.length());
    return theStream;
}
