/* Token.h - definition of a tokenizing class for SString */

#include "SString.h"

#ifndef TOKEN_H
#define TOKEN_H

class Token
{
public:

    /* Constructors */

    Token(const char *, std::string & );
    Token(const char *, const char * );
    Token(const char *, char);
    Token(std::string & , std::string & );
    Token(std::string & , const char * );
    Token(std::string & , char );

    /* Token retrieval */

    void nextToken(std::string & );
    void nextToken(char , std::string & );
    void nextToken(const char * , std::string & );
    void nextToken(std::string & , std::string & );

    void nextToken(SString & );
    void nextToken(char , SString & );
    void nextToken(const char * , SString & );
    void nextToken(std::string & , SString & );

    /* Status */

    short moreTokens();
    int count();

	void reset();

private:

    SString buffer;
    SString delim;
    int pos;

    void token(std::string &);
};

#endif
