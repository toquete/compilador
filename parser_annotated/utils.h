/**@<utils.h>::**/

#include <stdio.h>

#define MAXLINES 2048

extern int linecount;
extern int linecursor[MAXLINES];

int _getc(FILE *);
int _ungetc(int, FILE *);
int _strcmp(const char *, const char *);
