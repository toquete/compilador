#include <stdio.h>

#include <utils.h>

int linecount = 0;
int linecursor[MAXLINES];

int _getc(FILE *__stream) {
    int c = getc(__stream);
    linecursor[linecount]++;

    if (c == '\n') {
        linecount++;
    }

    return c;
}

int _ungetc(int __c, FILE *__stream) {
    ungetc(__c, __stream);

    if (__c == '\n') {
        linecount--;
    }

    linecursor[linecount]--;

    return __c;
}
