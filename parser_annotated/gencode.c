/**@<gencode.h>::**/

#include <stdio.h>
#include <stdarg.h>
#include <gencode.h>
#include <typecheck.h>
#include <symtab.h>
#include <errorhandler.h>

void genprint(const char *format, ...)
{
    if (error)
        return;

    va_list args;
    va_start(args, format);
    vfprintf(ascode, format, args);
    va_end(args);
}

void gensecdata()
{
    genprint("\t.data\n");
}

void gensectext()
{
    genprint("\t.text\n");
    genprint("\t.global _start\n\n");
    genprint("_start:\n");
}

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

