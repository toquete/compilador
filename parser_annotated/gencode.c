/**@<gencode.h>::**/

#include <stdio.h>
#include <stdarg.h>
#include <gencode.h>
#include <typecheck.h>
#include <symtab.h>
#include <errorhandler.h>

/*void readln()
{


}

void read()
{


}

void write(char *str)
{
    write("string");
    fprintf(ascode, str);
}

void writeln()
{

}*/

void genprint(const char* s, ...)
{
    if (error)
        return;

    va_list arg;
    va_start (arg, s);

    fprintf(ascode, s, arg);

    va_end(arg);
}

void gensecdata()
{
    genprint("\t.data\n");
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
        fprintf(ascode,"%-*s:\t%s\n", MAXIDLEN, &(symtab_names[symtab_descriptor[i][0]]),sizebyte);

}

