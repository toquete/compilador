/*******************PARSER ONLY***************************************
 *
 * UNIVERSIDADE ESTADUAL PAULISTA
 *
 * PROJETO FINAL DA DISCIPLINA DE COMPILADORES DESENVOLVIDO PELOS ALUNOS:
 *        CÉSAR OKADA;
 *        GUILHERME TOQUETE;
 *        WEBSTER LIMA.
 *
 * COM BASE NOS CÓDIGOS ELABORADOS PELO PROFESSOR DURANTE AS AULAS PRATICAS.
 *
 ***************************************************************************/

/*
 * @<main.c>::
 */

#include <stdio.h>
#include <stdlib.h>

#include <mypas.h>
#include <parser.h>

FILE           *tape;

int main(int argc, char *argv[])
{
    if (argc > 1) {
        tape = fopen(argv[1], "r");
        if (tape == NULL) {
            fprintf(stderr, "file not found... exiting\n");
            exit(-2);
        }
    } else {
        tape = fopen("../teste2.pas", "r");
        if (tape == NULL) {
            fprintf(stderr, "file not found... exiting\n");
            exit(-2);
        }
    }

    lookahead = gettoken(tape);
    mypas();

    printf("\n");

    return 0;
}
