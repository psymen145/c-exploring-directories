/* how_good():  tries to decide the closeness of two strings */
/*
 *  return values
 *  0   the two strings are identical
 *  1   two characters are transposed: "char" and "cahr"
 *  2   one character is wrong:  "char" "cher"
 *  3   one character is added:  "chaar" "char"
 *  4   one character is deleted: "chr" "char"
 *  -1  no match found
*/

#include    <string.h>
#define     EQ(s,t)  (strcmp(s,t) == 0)

int how_good(const char *s, const char *t)
{

    if(EQ(s,t))
      return 0;     /* exact match*/

    while(*s++ == *t++)     /* move to discrepancy*/
        ;

    if (*--s) {
       if (*--t) {
        if (s[1] && t[1] && *s == t[1] && *t == s[1] && EQ(s+2,t+2))
           return 1;    /*two characters transposed*/

        if (EQ(s+1, t+1))
           return 2;    /* one character mismatch */
       
        if (EQ(s+1, t))
           return 3;    /*extra character in the middle of one string*/
        
        if (EQ(s, t+1))
           return 4;    /*character missing in the string*/
       }

       if (EQ(s+1,t))
           return 3;    /*extra character at end of string*/
    }

    if (*--t && EQ(s, t+1))
       return 4;        /*missing character at end of string*/

    return -1;      /* no match found */
}