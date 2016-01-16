/*
 * @<main.c>::
 */

#include <stdio.h>
#include <stdlib.h>

#include <mypas.h>
#include <parser.h>

FILE           *tape;
FILE           *ascode;

int main(int argc, char *argv[])
{
    if (argc > 1) {
        tape = fopen(argv[1], "r");
        if (tape == NULL) {
            fprintf(stderr, "file not found... exiting\n");
            exit(-2);
        }

        ascode = fopen(argv[2], "w");
    } else {
        tape = fopen("../teste.pas", "r");
        if (tape == NULL) {
            fprintf(stderr, "file not found... exiting\n");
            exit(-2);
        }

        ascode = fopen("../teste.s", "w");
    }

    lookahead = gettoken(tape);
    mypas();

    fcloseall();
    printf("\n");

    return 0;
}
