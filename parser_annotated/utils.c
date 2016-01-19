/**@<utils.h>::**/

#include <stdio.h>
#include <utils.h>

int linecount = 0;
int linecursor[MAXLINES];

/*
 * Metodos _getc e _ungetc encapsulam, respectivamente, os metodos getc e ungetc,
 * e manipulam os contadores de linha e coluna do codigo.
*/

int _getc(FILE *__stream)
{
    int c = getc(__stream);
    linecursor[linecount]++;

    if (c == '\n') {
        linecount++;
    }

    return c;
}

int _ungetc(int __c, FILE *__stream)
{
    ungetc(__c, __stream);

    if (__c == '\n') {
        linecount--;
    }

    linecursor[linecount]--;

    return __c;
}


/*
 * Metodo que compara strings ignorando maiusculas e minusculas
*/
int _strcmp (const char *p1, const char *p2)
{
    register unsigned char *s1 = (unsigned char *) p1;
    register unsigned char *s2 = (unsigned char *) p2;
    unsigned char c1, c2;

    do {
        c1 = (unsigned char) toupper((int)*s1++);
        c2 = (unsigned char) toupper((int)*s2++);
        if (!c1) {
            return c1 - c2;
        }
    } while (c1 == c2);

    return c1 - c2;
}
