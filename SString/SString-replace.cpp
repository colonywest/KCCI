#include "SString.h"
#include "Token.h"

using namespace std;

int SString::replace(const char * f, const char * r)
{
    Token g(buf, f);
    SString s, t; int x = 0;
    if(g.count() == 1) return 0;
    g.nextToken(s);
    while(g.moreTokens())
    {
        s += r;
        g.nextToken(t); s += t;
        x++;
    }

    delete buf;
    buf = new char[s.length() + 1];
    strcpy(buf, s);
    return x;
}

int SString::replace(const char * f, char r)
{
    Token g(buf, f);
    SString s, t; int x = 0;
    if(g.count() == 1) return 0;
    g.nextToken(s);
    while(g.moreTokens())
    {
        s += r;
        g.nextToken(t); s += t;
        x++;
    }

    delete buf;
    buf = new char[s.length() + 1];
    strcpy(buf, s);
    return x;
}

int SString::replace(char f, const char * r)
{
    Token g(buf, f);
    SString s, t; int x = 0;
    if(g.count() == 1) return 0;
    g.nextToken(s);
    while(g.moreTokens())
    {
        s += r;
        g.nextToken(t); s += t;
        x++;
    }

    delete buf;
    buf = new char[s.length() + 1];
    strcpy(buf, s);
    return x;
}

int SString::replace(char f, char r)
{
    Token g(buf, f);
    SString s, t; int x = 0;
    if(g.count() == 1) return 0;
    g.nextToken(s);
    while(g.moreTokens())
    {
        s += r;
        g.nextToken(t); s += t;
        x++;
    }

    delete buf;
    buf = new char[s.length() + 1];
    strcpy(buf, s);
    return x;
}

int SString::replace(string & t, string & u)
{
    return replace(t.c_str(), u.c_str());
}

int SString::replace(string & t, const char * u)
{
    return replace(t.c_str(), u);
}

int SString::replace(string & t, char u)
{
    return replace(t.c_str(), u);
}

int SString::replace(const char * t, string & u)
{
    return replace(t, u.c_str());
}

int SString::replace(char t, string & u)
{
    return replace(t, u.c_str());
}
