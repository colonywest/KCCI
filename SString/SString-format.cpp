#include "SString.h"

using namespace std;

void SString::format(const char * s, ...)
{
    va_list arglist;
    va_start(arglist, s);
    print(s, arglist);
    va_end(arglist);
}

void SString::format(string & s, ...)
{
    va_list arglist;
    va_start(arglist, s);
    print(s.c_str(), arglist);
    va_end(arglist);
}

void SString::format(const char * s, va_list arglist)
{
    print(s, arglist);
    va_end(arglist);
}

void SString::format(string & s, va_list arglist)
{
    print(s.c_str(), arglist);
    va_end(arglist);
}

void SString::print(const char * s, va_list argument)
{
    char Types[] = "cdeEfgGinopsuxX";
    char Mods[] = "FNhlL";
    char * FormatString = new char[strlen(s) + 1];
    strcpy(FormatString, s);

    va_list arglist = argument;

    /* Step through the string trying to determine the approximate
     * total length of the string.  The total length will be a "safe"
     * number because the minimum length will be the length of the
     * format string itself.  As the format string is traversed and
     * format options are found, the number is increased accordingly.
     *
     * In the ANSI standard for printf and scanf, the formatting is
     * something like this:
     *    %[flag][width][precision][mod]type
     *
     * Here's how the sections break down as far as width is concerned
     * when traversing the string:
     *    flag - 1 character
     *    width - either a number or an * and a number
     *    precision - begins with a ., then same as width
     *    mod - 1 character
     *    type - 1 character
     *
     * If the width is less than the default, the default is used, otherwise
     * the specified number is used.  If the precision is less than the
     * default, the default is used, otherwise the precision is used.
     */

    int Length = strlen(s);
    int MinLength;
    char * h, * p, * n;

    p = strchr(FormatString, '%');
    if(p != NULL) n = strtok(p, "%");
    else n = NULL;

    while(n != NULL)
    {
        char Flag, Mod, Type;
        int wid, prec;
        char * i, * j;
        char u[5];
        MinLength = 0;
        h = new char[strlen(n) + 1];
        strcpy(h, n);

        /* Find the first space in the string after the first character.
         * If it exists, set it to NULL.
         */

        i = strpbrk(h + 1, " \t\n");
        if(i != NULL) *i = 0;

        /* h now contains only the format string.  It looks something
         * like this:
         *   [flag][wid][prec][mod]type
         */

        Flag = h[0];
        if(strchr(" -+#", Flag) != NULL)
            MinLength = 1;

        i = strpbrk(h, "1234567890");

        /* Determine if this position falls before or after a decimal
         * point to determine if we have the width or precision. If
         * this is a width, then the pointer needs to be advanced to
         * the decimal point (if there is one) to get the precision.
         */

        if(i == NULL)                   /* No numbers in string */
        {
            wid = 0;
            j = NULL;
        }
        else                            /* Numbers exist */
        {
            j = strchr(h, '.');         /* Find a decimal point */

            if(j == NULL)               /* No decimal, width */
            {
                strncpy(u, i, strcspn(i, "1234567890"));
                wid = atoi(u);
            }
            else if(j > i)              /* Decimal, width */
            {
                strncpy(u, i, j - i);
                wid = atoi(u);
            }
        }

        /* Get the precision only if there is a decimal point.  If
         * the first character after the decimal (j + 1) is an
         * asterick, then the number starts on the next position.
         */

        if(j != NULL)
        {
            if(*(j + 1) == '*') j += 2;
            else j++;

            strncpy(u, j, strcspn(j, "1234567890"));
            prec = atoi(u);
        }
        else
            prec = 0;

        /* Now for the modifier.  The only modifier that has any real
         * effect on the total length of the string is l or L.  For
         * an int type, the length will be set at 10 digits, whether
         * this is a 16-bit or 32-bit environment.  For doubles, the
         * bit length becomes 80, lengthening it to 25 from 20.
         */

        if(strpbrk(h, Mods) != NULL)
            Mod = *strpbrk(h, Mods);

        if(strpbrk(h, Types) != NULL)
            Type = *strpbrk(h, Types);

        /* Now to determine the total width, depending on the type
         * and modifier.
         */

        switch(Type)
        {
            case 'c': MinLength++; va_arg(arglist, int); break;
            case 'e':
            case 'E':
            case 'f':
            case 'g':
            case 'G': if(prec < 10 && wid < 10) MinLength++; else MinLength += (wid > prec) ? wid : prec; va_arg(arglist, double); break;
            case 'u':
            case 'd':
            case 'i': va_arg(arglist, int); MinLength += (wid > 10) ? wid : 10; break;
            case 'o': va_arg(arglist, int); MinLength += (wid > 15) ? wid : 15; break;
            case 'p': va_arg(arglist, int); MinLength += 16; break;
            case 'x':
            case 'X': va_arg(arglist, int); MinLength += (wid > 8) ? wid : 8; break;
            case 's': MinLength += strlen(va_arg(arglist, char *)); break;
        }

        if(Type == 'd' && (Mod == 'l' || Mod == 'L')) MinLength += 10;

        n = strtok(NULL, "%");
        delete h;
        Length += MinLength;
    }

    char * l = new char[Length + 1];

    va_end(arglist);
    vsprintf(l, s, argument);

    delete buf;
    buf = new char[strlen(l) + 1];
    strcpy(buf, l);
    delete l;
    delete FormatString;
    return;
}
