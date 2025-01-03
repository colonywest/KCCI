/* Token.cpp - implementation of Token */

#include "Token.h"

Token::Token(std::string & E, char t)
{
    buffer = E; delim = t; pos = 0;
    if(buffer.length() == 0) pos = -1;
}

Token::Token(std::string & E, const char * t)
{
    buffer = E; delim = t; pos = 0;
    if(buffer.length() == 0) pos = -1;
}

Token::Token(std::string & E, std::string & t)
{
    buffer = E; delim = t; pos = 0;
    if(buffer.length() == 0) pos = -1;
}

Token::Token(const char * E, char t)
{
    buffer = E; delim = t; pos = 0;
    if(buffer.length() == 0) pos = -1;
}

Token::Token(const char * E, const char * t)
{
    buffer = E; delim = t; pos = 0;
    if(buffer.length() == 0) pos = -1;
}

Token::Token(const char * E, std::string & t)
{
    buffer = E; delim = t; pos = 0;
    if(buffer.length() == 0) pos = -1;
}

short Token::moreTokens()
{
    if(pos == -1) return 0;
    else return 1;
}

int Token::count()
{
    int count = 1, p;

    if(buffer.length() == 0) return 0;
    if(pos == -1) return 0;

    p = buffer.indexOf(delim, pos);

    while(p != -1)
    {
        count++; p += delim.length();
        p = buffer.indexOf(delim, p);
    }
    return count;
}

void Token::nextToken(std::string & I)
{
    token(I);
}

void Token::nextToken(char d, std::string & I)
{
    delim = d;
    token(I);
}

void Token::nextToken(const char * d, std::string & I)
{
    delim = d;
    token(I);
}

void Token::nextToken(std::string & d, std::string & I)
{
    delim = d;
    token(I);
}

void Token::nextToken(SString & I)
{
    std::string j; token(j);
    I = j;
}

void Token::nextToken(char d, SString & I)
{
    std::string j; delim = d;
    token(j); I = j;
}

void Token::nextToken(const char * d, SString & I)
{
    std::string j; delim = d;
    token(j); I = j;
}

void Token::nextToken(std::string & d, SString & I)
{
    std::string j; delim = d;
    token(j); I = j;
}


void Token::token(std::string & J)
{
    int p;

    if(pos == -1) return;
    if(pos == buffer.length())
    {
        pos = -1;
        return;
    }

    p = buffer.indexOf(delim, pos);

    if(p < 0) J = buffer.substring(pos);
    else J = buffer.substring(pos, p - pos);

    if(p < 0 || p == buffer.length() - delim.length()) pos = -1;
    else pos = p + delim.length();
}

void Token::reset()
{
	pos = 0;
}