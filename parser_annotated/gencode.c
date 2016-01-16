/**@<gencode.h>::**/

#include <stdio.h>
#include <gencode.h>
#include <typecheck.h>
#include <symtab.h>

void gensecdata()
{
    fprintf(ascode,"\t.data\n");
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

    for (i = initial; i < final; i++) {
        printf("%-*s\t%s", MAXIDLEN, &(symtab_names[symtab_descriptor[i][0]]),sizebyte);
        fprintf(ascode,"%-*s\t%s\n", MAXIDLEN, &(symtab_names[symtab_descriptor[i][0]]),sizebyte);
    }

    //fprintf(ascode, "%s:\t%s\n",varName,sizebyte);
}


