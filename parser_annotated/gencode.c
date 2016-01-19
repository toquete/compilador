/**@<gencode.h>::**/

#include <stdio.h>
#include <stdarg.h>
#include <gencode.h>
#include <typecheck.h>
#include <symtab.h>
#include <errorhandler.h>

/*
 *Encapsula metodo de escrita de arquivo e verifica a presenca de erros na compilacao
*/
void genprint(const char *format, ...)
{
    if (error)
        return;

    va_list args;
    va_start(args, format);
    vfprintf(ascode, format, args);
    va_end(args);
}

/*
 *Geracao da secao .data em assembly
*/
void gensecdata()
{
    genprint("\t.data\n");
}


/*
 *Geracao da secao .text em assembly
*/
void gensectext()
{
    genprint("\t.text\n");
    genprint("\t.global _start\n\n");
    genprint("_start:\n");
}

/*
 * Geracao de codigo da declaracao de variaveis
*/

void genvar(int initial, int final, int typevar)
{
    int i;
    char sizebyte[5];

    switch(typevar){
    case INTEGER_TYPE:
    case REAL_TYPE:
        sprintf(sizebyte,"dd");
        break;
    case BOOLEAN_TYPE:
        sprintf(sizebyte,"db");
        break;
    default:
        sprintf(sizebyte,"dq");
    }

    for (i = initial; i < final; i++)
        genprint("%-*s: %s\n", MAXIDLEN, &(symtab_names[symtab_descriptor[i][0]]), sizebyte);

}

