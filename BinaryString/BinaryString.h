#include <string>
#include <iostream>

#ifndef BINARYSTRING_H
#define BINARYSTRING_H

class BinaryString
{
public:

    /* Constructors */

    BinaryString();
    BinaryString(const unsigned char *, int);
    BinaryString(unsigned char );

    /* Copy constructor */

    BinaryString(const BinaryString &);

    /* Destructor */

    ~BinaryString();

    /* Set equal to a character or other BinaryString object */

    void operator=(unsigned char );
    BinaryString & operator=(const BinaryString &);

    /* Concatenation */

    BinaryString operator+(BinaryString &);
    BinaryString operator+(unsigned char );

    /* Concatenation with assignment */

    void operator+=(BinaryString &);
    void operator+=(unsigned char );

    /* Type cast and array operators */

    unsigned char & operator[](int );
	operator unsigned char * ();
	operator const unsigned char * ();

    /* Bitwise logic functions */

    void xor(unsigned char *, unsigned, int );
    void xor(const BinaryString &, int );
    void and(unsigned char *, unsigned, int );
    void and(const BinaryString &, int );
    void or(unsigned char *, unsigned, int );
    void or(const BinaryString &, int );

    /* Search for a byte or byte sequence */

    int indexOf(BinaryString &);
    int indexOf(unsigned char );
    int indexOf(const unsigned char *, int );

    /* Append data or overwrite the current buffer */

    void append(const unsigned char *, int );
    void append(const char * );
    void set(const unsigned char *, int );

    /* Reset or determine the length of the buffer */

    void reset();
    int length();

private:

    unsigned char * buf;
    unsigned long buflength;
    unsigned long alloclength;

    void reallocate(unsigned );
};

#endif
