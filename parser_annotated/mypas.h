/*
 * @<main.h>::
 */

#include <stdio.h>
extern int            lookahead;
extern FILE           *ascode;
extern int            error;

int             gettoken(FILE * tape);
