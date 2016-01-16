/**@<errorhandler.c>::**/
#include <stdio.h>
#include <lexer.h>
#include <utils.h>
#include <errorhandler.h>

void errorsDictionary(char *err, int errorcode)
{
    switch(errorcode){
    case SYMB_OVRLP:
        sprintf(err, "redeclaration of variable (error %i)", errorcode);
        break;
    case SYMB_NFND:
        sprintf(err, "variable is not declared (error %i)", errorcode);
        break;
    case SYMB_OVRFL:
        sprintf(err, "variable overflow (error %i)", errorcode);
        break;
    case IVLD_OPDS:
        sprintf(err, "invalid type of operands (error %i)", errorcode);
        break;
    }
}

void
fatal_error(int errorcode)
{
    char errMsg[100];
    errorsDictionary(errMsg, errorcode);

    fprintf(stderr, "Fatal error:%d:%d: %s\n",
            linecount + 1,
            linecursor[linecount] + 1 - lexcursor,
            errMsg);
}
