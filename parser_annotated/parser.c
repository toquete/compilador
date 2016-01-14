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

/**/ int label_counter = 1; /**/

/**
 * Top-down recursive parser emulating an EBNF for the simplified
 * Pascal (MyPas):
 *
 * mypas -> PROGRAM ID ; body .
 *
 * body -> { VAR ID { , ID } : type ; { ID { , ID } : type ; } }
 *       | { PROCEDURE ID parmlist ; body ; | FUNCTION ID parmlist : type ; body ; }
 */
void idlist (void)
{
ID_list:
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
        idlist();
        match(':');
        type();

        if (lookahead == ';'){
            match(';');
            goto _parm_spec;
        }
        match(')');
    }
}

void type(void)
{
    switch (lookahead) {
    case INTEGER:
        match(INTEGER);
        break;
    case REAL:
        match(REAL);
        break;
    case DOUBLE:
        match(DOUBLE);
        break;
    default:
        match(BOOLEAN);
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
    expression();
    if (lookahead == ',') {
        match(',');
        goto expr_list;
    }
}

int isrelop()
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

void expression (void)
{
    expr();
    if (isrelop()) {
        expr();
    }
}

void expr(void)
{
    switch (lookahead) {
    case '+': case '-':
        match(lookahead);
    }
_plus_term:
    term();
    switch (lookahead) {
    case '+': case '-': case OR:
        match(lookahead);
        goto _plus_term;
    }
}


void term(void)
{
_times_fact:
    fact();
    switch (lookahead) {
    case'*':case'/':case DIV:case MOD:case AND:
        match(lookahead);
        goto _times_fact;
    }
}

void fact(void)
{
    switch (lookahead) {
    case '(':
        match('(');
        expression();
        match(')');
        break;
    case NOT:
        match(NOT);
        fact();
        break;
    case UINT: case UFLOAT: case NIL:
        match(lookahead);
        break;
    default:
        match(ID);
    }
}

void var(void)
{
    while (lookahead == VAR) {
        match (VAR);
ID_list_2:
        idlist();
        match(':');
        type();
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
    match(ID);

    if (lookahead == '(') {
        match('(');
expr_id_list:
        if (lookahead == ID)
            match(ID);
        else
            expression();
        if (lookahead == ',') {
            match(',');
            goto expr_id_list;
        }
        match(')');
    } else if (lookahead == ':') {
        match(':');
        match('=');
        expression();
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
    expression();

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

    expression();

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
    expression();

    /**/printf("\tjnz .L%i\n", label_repeat);/**/
}

void forstmt(void)
{
    /**/ int label_for, label_end_for; /**/

    match(FOR);
    match(ID);
    match(':');
    match('=');
    expression();
    match(TO);
    expression();

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
