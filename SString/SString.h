#include <stdarg.h>
#include <string>
#include <iostream>

#ifndef SSTRING_H
#define SSTRING_H

class SString
{
public:

    /* Constructors */

    SString();                  /**< Default constructor */
    SString(char );             /**< Sets object equal to a character */
    SString(const char * );     /**< Sets object equal to a string */
    SString(std::string & );    /**< Sets object equal to a STL string */

    /* Copy constructor */

    SString(const SString & );  /**< Copy constructor */

    /* Destructor */

    ~SString();                 /**< Destructor */

    /* Type conversion operator */

    operator const char * ();
    operator char * ();

    /* Concatenation operators */

    SString operator + (std::string & );
    SString operator + (const char * );
    SString operator + (char );

    SString & operator += (std::string & );
    SString & operator += (const char * );
    SString & operator += (char );

    /* Assignment operator */

    SString & operator = (std::string & );
    SString & operator = (const char * );
    SString & operator = (char );
    SString & operator = (const SString & );

    /* Comparison operators - Case sensitive */

    short operator >  (const char * );
    short operator <  (const char * );
    short operator >= (const char * );
    short operator <= (const char * );
    short operator == (const char * );
    short operator != (const char * );

    short operator >  (std::string & );
    short operator <  (std::string & );
    short operator >= (std::string & );
    short operator <= (std::string & );
    short operator == (std::string & );
    short operator != (std::string & );

    /* Array operators */

    char & operator [] (int );

    /* Miscellaneous functions */

    void reset();
    int length();

    void append(const unsigned char *, int );

    void format(const char *, ... );
    void format(std::string &, ... );
    void format(const char *, va_list );
    void format(std::string &, va_list );

    int indexOf(char );
    int indexOf(char , int );
    int indexOf(const char * );
    int indexOf(const char *, int );
    int indexOf(std::string & );
    int indexOf(std::string &, int );

    int replace(std::string &, std::string & );
    int replace(std::string &, const char * );
    int replace(std::string &, char );
    int replace(const char *, std::string & );
    int replace(const char *, const char * );
    int replace(const char *, char );
    int replace(char, std::string & );
    int replace(char, const char * );
    int replace(char , char );

    SString substring(int, int );
    SString substring(int );
    SString left(int );
    SString right(int );

    int compareToIgnoreCase(std::string &);
    int compareToIgnoreCase(const char * );

    void toLowerCase();
    void toUpperCase();

    void setSub(const char *, int, int );
    void setSub(std::string &, int, int );
    void set(const char * );

    void trim();
    void setLength(int );

protected:

    char * buf;
    unsigned long alloclength;

    void allocate(unsigned long );
    void allocate(char * );
    int reallocate(unsigned long );

    int compare(const char * );
    void print(const char *, va_list );
};

typedef SString String;

std::istream & operator >> (std::istream &, SString &);
std::ostream & operator << (std::ostream &, SString &);

#endif
