/*
 * @<parser.c>::
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <parser.h>
#include <tokens.h>
#include <lexer.h>
#include <keywords.h>
#include <utils.h>
#include <symtab.h>
#include <errorhandler.h>
#include <typecheck.h>


/**/ int label_counter = 1; /**/

/**
 * Top-down recursive parser emulating an EBNF for the simplified
 * Pascal (MyPas):
 *
 * mypas -> PROGRAM ID ; body .
 *
 * body -> { VAR ID { , ID } : type ; { ID { , ID } : type ; } }
 */
void idlist (void)
{
    /**/int initial, final /**/;

ID_list:

    /**/initial = symtab_next_entry/**/;
    /**/final = symtab_append(lexeme)/**/;
    match(ID);

    if (lookahead == ',') {
        match (',');
        goto ID_list;
    }
}

void parmlist (void)
{
    if (lookahead == '(') {
        match('(');
_parm_spec:
        if (lookahead == VAR)
            match(VAR);

        /**/int initial = symtab_next_entry/**/;
        idlist();
        match(':');
        /**/symtab_settype(initial, symtab_next_entry, type())/**/;

        if (lookahead == ';'){
            match(';');
            goto _parm_spec;
        }
        match(')');
    }
}

/*
 * type return:
 * 0 -> BOOLEAN
 * 1 -> NUMBER (INTEGER + REAL + DOUBLE)
 * 2 -> INTEGER
 * 3 -> REAL
 * 4 -> DOUBLE
 */

int type(void)
{
    switch (lookahead) {
    case INTEGER:
        match(INTEGER);
        /**/return INTEGER_TYPE/**/;
        break;
    case REAL:
        match(REAL);
        /**/return REAL_TYPE/**/;
        break;
    case DOUBLE:
        match(DOUBLE);
        /**/return DOUBLE_TYPE/**/;
        break;
    default:
        match(BOOLEAN);
        /**/return BOOLEAN_TYPE/**/;
    }
}

int istype(void)
{
    switch (lookahead) {
    case INTEGER:case REAL:case DOUBLE:case BOOLEAN:
        return lookahead;
    }

    return 0;
}

void expr_list(void)
{
expr_list:
    expression(NONE);
    if (lookahead == ',') {
        match(',');
        goto expr_list;
    }
}

int isrelop(void)
{
    switch (lookahead) {
    case '>':
        match('>');
        if (lookahead == '=') {
            match('=');
            return GEQ;
        }
        return '>';
    case '<':
        match('<');
        if (lookahead == '=') {
            match('=');
            return LEQ;
        } else if (lookahead == '>') {
            match('>');
            return NEQ;
        }
        return '<';
    case '=':
        match('=');
        return '=';
    }

    return 0;
}

int expression(int inheritedtype)
{
    int impltype;

    impltype = expr();
    if (isrelop()) {
        if (typecheck(impltype, expr()) == -1) {
            fatal_error(INVL_TYPE);
        } else {
            impltype = BOOLEAN_TYPE;
        }
    }

    if (typecheck(inheritedtype, impltype))
        fatal_error(INVL_TYPE);

    return impltype;
}

int expr(void)
{
    int impltype = NONE;

    switch (lookahead) {
    case '+': case '-':
        impltype = NUMBER_TYPE;
        match(lookahead);
    }

    int synthtype;
_plus_term:
    synthtype = term(impltype);

    if (impltype > synthtype) {
        fatal_error(INVL_TYPE);
    }

    impltype = synthtype;

    switch (lookahead) {
    case '+': case '-':
        if (impltype < NUMBER_TYPE)
            fatal_error(INVL_TYPE);
    case OR:
        if (impltype != BOOLEAN_TYPE)
            fatal_error(INVL_TYPE);
        match(lookahead);
        goto _plus_term;
    }
}


int term(int inheritedtype)
{
    int impltype;

_times_fact:
    impltype = typecheck(inheritedtype, fact());
    switch (lookahead) {
    case '*': case '/':
        if (impltype < NUMBER_TYPE)
            fatal_error(INVL_TYPE);
    case DIV: case MOD:
        if (impltype != INTEGER_TYPE)
            fatal_error(INVL_TYPE);
    case AND:
        if (impltype != BOOLEAN_TYPE)
            fatal_error(INVL_TYPE);
        match(lookahead);
        goto _times_fact;
    }

    return impltype;
}

int fact(void)
{
    /**/int impltype;/**/

    int sym_index;

    switch (lookahead) {
    case '(':
        match('(');
        impltype = expression(NONE);
        match(')');
        break;
    case NOT:
        match(NOT);

        /**/impltype = fact();/**/
        /**/if (impltype != BOOLEAN_TYPE) {
            fatal_error(INVL_TYPE);
        }/**/

        break;
    case UINT:
        impltype = INTEGER_TYPE;
    case UFLOAT:
        impltype = REAL_TYPE;
    case UDOUBLE:
        impltype = DOUBLE_TYPE;
        match(lookahead);
        break;
    case TRUE:
    case FALSE:
        impltype = BOOLEAN_TYPE;
        match(lookahead);
        break;
    default:
        sym_index = symtab_lookup(lexeme);

        /**/if (sym_index == -1) {
            fatal_error(SYMB_NFND);
            impltype = -1;/**/
        } else {
            impltype = symtab_descriptor[sym_index][DATYPE];
        }

        match(ID);
    }

    return impltype;
}

void var(void)
{
    /**/int initial/**/;
    while (lookahead == VAR) {
        match (VAR);
ID_list_2:
        /**/initial = symtab_next_entry/**/;
        idlist();
        match(':');
        /**/symtab_settype(initial, symtab_next_entry, type())/**/;
        match(';');
        if (lookahead == ID)
            goto ID_list_2;
    }
}

void body (void)
{
    var();
    beginstmt();
}

void mypas (void)
{
    match(PROGRAM);
    match(ID);

    if (lookahead == '(') {
        match('(');
        idlist();
        match(')');
    }

    match(';');
    body();
    match('.');

    printf("\n\n-------------------------------------");
    printf("\n              VAR LIST               \n");
    printf("-------------------------------------\n\n");

    int i, j;
    for (i = 0; i < symtab_next_entry; i++) {
        printf("%-*s", MAXIDLEN, &(symtab_names[symtab_descriptor[i][0]]));
        for (j = 0; j < 2; j++) {
            printf("%3i", symtab_descriptor[i][j]);
        }
        printf("\n");
    }
}

/**
* stmtlist -> stmt ; {stmt ;}
* stmt -> begin_end | ifstmt | whilestmt | repstmt | forstmt | idstmt
* begin_end -> BEGIN stmtlist END
* ifstmt -> IF expr THEN stmt [ELSE stmt]
* whilestmt -> WHILE expr DO stmt
* repstmt -> REPEAT stmtlist UNTIL expr
* forstmt -> FOR expr := expr TO expr DO stmt
* idstmt -> expr := expr
*/
void idstmt(void)
{
    /**/int impltype;/**/
    int sym_index = symtab_lookup(lexeme);

    /**/if (sym_index == -1) {
        fatal_error(SYMB_NFND);
        impltype = -1;
    } else {
        symtab_descriptor[sym_index][DATYPE];
    }/**/

    match(ID);

//    if (lookahead == '(') {
//        match('(');
//expr_id_list:
//        if (lookahead == ID){
//            /**/if(symtab_lookup(lexeme) == -1)
//                fatal_error(SYMB_NFND);/**/
//            match(ID);
//        } else {
//            expression(NONE);
//        }
//        if (lookahead == ',') {
//            match(',');
//            goto expr_id_list;
//        }
//        match(')');
//    } else
    if (lookahead == ':') {
        match(':');
        match('=');
        expression(impltype);
    }
}

void beginstmt(void)
{
    match(BEGIN);
    stmtlist();
    match(END);
}

void ifstmt(void)
{
    /**/ int label_endif, label_else; /**/

    match(IF);
    expression(BOOLEAN_TYPE);

    /**/printf("\tjz .L%i\n", label_endif = label_else = label_counter);/**/
    /**/label_counter++;/**/

    match(THEN);
    stmt();

    if (lookahead == ELSE) {
        /**/printf("\tgoto .L%i\n", label_endif = label_counter);/**/
        /**/label_counter++;/**/
        /**/printf(".L%i:\n", label_else);/**/

        match(ELSE);
        stmt();
    }
}

void whilestmt(void)
{
    /**/ int label_while, label_end_while; /**/

    match(WHILE);

    /**/printf(".L%i:\n", label_while = label_counter);/**/
    /**/label_counter++;/**/

    expression(BOOLEAN_TYPE);

    /**/printf("\tjz .L%i\n", label_end_while = label_counter);/**/
    /**/label_counter++;/**/

    match(DO);
    stmt();

    /**/printf("\tgoto .L%i\n", label_while);/**/
    /**/printf(".L%i\n", label_end_while);/**/
}

void repeatstmt(void)
{
    /**/ int label_repeat; /**/
    match(REPEAT);

    /**/printf(".L%i:\n", label_repeat = label_counter);/**/
    /**/label_counter++;/**/

    stmtlist();

    match(UNTIL);
    expression(BOOLEAN_TYPE);

    /**/printf("\tjnz .L%i\n", label_repeat);/**/
}

void forstmt(void)
{
    /**/ int label_for, label_end_for; /**/

    match(FOR);
    match(ID);
    /**/if (symtab_lookup(lexeme) == -1)
        fatal_error(SYMB_NFND)/**/;
    match(':');
    match('=');

    if (expression(NONE) != INTEGER_TYPE)
        fatal_error(INVL_TYPE);

    match(TO);
    if (expression(NONE) != INTEGER_TYPE)
        fatal_error(INVL_TYPE);

    /**/printf(".L%i:\n", label_for = label_counter);/**/
    /**/label_counter++;/**/
    /**/printf("\tje .L%i\n", label_end_for);/**/

    match(DO);
    stmt();

    /**/printf("\tgoto .L%i\n", label_for);/**/
    /**/printf(".L%i\n", label_end_for);/**/
}

void variablelist(void)
{
variable_list:

    /**/if (symtab_lookup(lexeme) == -1)
        fatal_error(SYMB_NFND)/**/;

    match(ID);

    if (lookahead == ',' ) {
        match(',');
        goto variable_list;
    }
}

int stmt(void)
{
    int foundStmt = 1;

    switch (lookahead) {
    case BEGIN:
        beginstmt();
        break;
    case IF:
        ifstmt();
        break;
    case WHILE:
        whilestmt();
        break;
    case REPEAT:
        repeatstmt();
        break;
    case FOR:
        forstmt();
        break;
    case ID:
        idstmt();
        break;
    default:
        foundStmt = 0;
    }

    return foundStmt;
}

void stmtlist(void)
{
stmt_list:
    if (stmt() && lookahead == ';') {
        match(';');
        goto stmt_list;
    }
}

/** lexer-to-parser interface **/

int lookahead;

void match(int predicted)
{
    if (predicted == lookahead) {
        if (lookahead != EOF) {
            lookahead = gettoken(tape);
        }
    } else {
        if (predicted >= BEGIN) {
            fprintf(stderr, "Error:%d:%d: expected '%s' but was '%s'\n",
                    linecount + 1,
                    linecursor[linecount] + 1 - lexcursor,
                    keyword[predicted - BEGIN],
                    lexeme);
        } else if (!predicted) {
            fprintf(stderr, "Error:%d:%d: '%s' not expected\n",
                    linecount + 1,
                    linecursor[linecount] + 1 - lexcursor,
                    lexeme);
        } else  {
            fprintf(stderr, "Error:%d:%d: expected '%c' but was '%s'\n",
                    linecount + 1,
                    linecursor[linecount] + 1 - lexcursor,
                    predicted,
                    lexeme);
        }
        exit(-1);
    }
}
