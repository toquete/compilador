/**@<errorhandler.c>::**/
#include <stdio.h>
#include <lexer.h>
#include <utils.h>
#include <typecheck.h>
#include <errorhandler.h>
#include <gencode.h>

int error = 0;

void
gettypename(char *typestring, int type) {
    switch (type) {
    case BOOLEAN_TYPE:
        sprintf(typestring, "boolean");
        break;
    case NUMBER_TYPE:
        sprintf(typestring, "numeric");
        break;
    case INTEGER_TYPE:
        sprintf(typestring, "int");
        break;
    case REAL_TYPE:
        sprintf(typestring, "real");
        break;
    case DOUBLE_TYPE:
        sprintf(typestring, "double");
        break;
    }
}

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
        sprintf(err, "symbol table overflow (error %i)", errorcode);
        break;
    case IVLD_OPDS:
        sprintf(err, "invalid type of operands. (error %i)", errorcode);
        break;
    }
}

void closedestfile() {
    fclose(ascode);
    remove(nametmp);
}

void
fatal_error(int errorcode)
{
    /*Secao de tratamento dos erros de semantica*/
    char errMsg[100];
    errorsDictionary(errMsg, errorcode);

    fprintf(stderr, "Fatal error:%d:%d: %s\n",
            linecount + 1,
            linecursor[linecount] + 1 - lexcursor,
            errMsg);

    error = 1;

    closedestfile();
}

void
type_fatal_error(int errorcode, int expectedtype, int gottype)
{
    /*Secao de tratamento dos erros relacionados aos tipos dos operandos*/
    char errMsg[100];
    errorsDictionary(errMsg, errorcode);

    char expected[100];
    gettypename(expected, expectedtype);

    fprintf(stderr, "Fatal error:%d:%d: invalid type of operands. Expected '%s' (error %i)\n",
            linecount + 1,
            linecursor[linecount] + 1 - lexcursor,
            expected,
            errorcode);

    error = 1;

    closedestfile();
}
