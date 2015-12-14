/*
 * @<main.c>::
 */

#include <stdio.h>
#include <stdlib.h>

#include <mypas.h>

FILE           *tape;

main(int argc, char *argv[])
{
    if (argc > 1) {
        tape = fopen(argv[1], "r");
        if (tape == NULL) {
            fprintf(stderr, "file not found... exiting\n");
            exit(-2);
        }
    } else {
        tape = stdin;
    }

    lookahead = gettoken(tape);

    //cmd();

    printf("\n");

    return 0;
}
