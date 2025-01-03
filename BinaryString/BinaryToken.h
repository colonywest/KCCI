#include "BinaryString.h"

#ifndef BINARYTOKEN_H
#define BINARYTOKEN_H

class BinaryToken
{
public:
    BinaryToken(BinaryString &, BinaryString &);
    BinaryToken(BinaryString &, unsigned char );
    BinaryToken(BinaryString &, unsigned char * , int );
    BinaryToken(unsigned char *, int, BinaryString &);
    BinaryToken(unsigned char *, int, unsigned char );
    BinaryToken(unsigned char *, int, unsigned char *, int);

    int moreTokens();
    int count();
    void reset();

    void newToken(BinaryString &, BinaryString &);
    void newToken(BinaryString &, unsigned char );
    void newToken(BinaryString &, unsigned char * , int );
    void newToken(unsigned char *, int, BinaryString &);
    void newToken(unsigned char *, int, unsigned char );
    void newToken(unsigned char *, int, unsigned char *, int);

    BinaryString nextToken();
    BinaryString nextToken(unsigned char );
    BinaryString nextToken(BinaryString & );
    BinaryString nextToken(unsigned char *, int );

private:
    BinaryString bstr;
    BinaryString delim;
    int pos;

    void token(BinaryString & d);
};

#endif
