/**@<errorhandler.c>::**/
#include <stdio.h>
#include <errorhandler.h>

void errorsDictionary(char *err, int errorcode)
{
    switch(errorcode){
    case SYMB_OVRLP:
        sprintf(err,"FATAL ERROR %i: redeclaration of variable\n", errorcode);
        break;
    case SYMB_NFND:
        sprintf(err,"FATAL ERROR %i: variable is not declared\n", errorcode);
        break;
    case SYMB_OVRFL:
        sprintf(err,"FATAL ERROR %i: variable overflow\n", errorcode);
        break;
    case IVLD_OPDS:
        sprintf(err,"FATAL ERROR %i: Invalid type of operands\n", errorcode);
        break;
    }
}

void
fatal_error(int errorcode)
{
    char errMsg[100];
    errorsDictionary(errMsg,errorcode);
    fprintf(stderr, errMsg);
}
