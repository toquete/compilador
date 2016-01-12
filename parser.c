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

void conslist(void)
{
cons_list:
    match(STRCONST);
    if (lookahead == ','){
        match(',');
        goto cons_list;
    }
}

void parmlist (void)
{
    if (lookahead == '(') {
        match('(');
_parm_spec:
        if(lookahead == VAR)
            match(VAR);
        idlist();
        if(lookahead==';'){
            match(';');
            goto _parm_spec;
        }
        match(')');
    }
}

void range(void)
{
    match('[');
_UINT_list:
    match(UINT);
    if(lookahead==','){
        match(',');
        goto _UINT_list;
    }
    match(']');
}

void type (void)
{
    switch(lookahead){
    case INTEGER:case REAL:case DOUBLE:case BOOLEAN:case STRING:
        match(lookahead);
        break;
    default:
        match(ARRAY);
        range();
        match(OF);
        type();
    }
}

int isrelop(int lookahead)
{
    switch(lookahead){
    case '>':
        match('>');
        if(lookahead=='='){
            match('=');
            return GEQ;
        }
        return '>';
    case '<':
        match('<');
        if(lookahead=='='){
            match('=');
            return LEQ;
        }
        else if(lookahead=='>'){
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
    if(isrelop(lookahead)){
        expr();
    }
}

void expr(void)
{
    switch(lookahead){
    case PROCEDURE:
        match(PROCEDURE);
        match(ID);
        parmlist();
        break;
    case FUNCTION:
        match(FUNCTION);
        match(ID);
        parmlist();
        match(':');
        type();
    case '+':case '-':case NOT:
        match(lookahead);
    }
_plus_term:
    term();
    switch(lookahead){
    case'+':case'-':case OR:
        match(lookahead);
        goto _plus_term;
    }
}


void term(void)
{
_times_fact:
    fact();
    switch(lookahead){
    case'*':case'/':case DIV:case MOD:case AND:
        match(lookahead);
        goto _times_fact;
    }
}

void fact(void)
{
    switch(lookahead){
    case ID:
        match(ID);
        if(lookahead==':'){
            match(':');
            match('=');
            expression();
        }
        break;
    case UINT:case UFLOAT:case STRCONST:case TRUE:case FALSE:
        match(lookahead);
        break;
    default:
        match('(');
        expression();
        match(')');
    }
}

void body (void)
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
    while (lookahead == PROCEDURE || lookahead == FUNCTION) {
        switch (lookahead) {
        case PROCEDURE:
            match(PROCEDURE);
            match(ID);
            parmlist();
            break;
        case FUNCTION:
            match(FUNCTION);
            match(ID);
            parmlist();
            match(':');
            type();
            match(ID);
        }
        match(';');
        body();
        match(';');
    }
    stmtlist();
}

void mypas (void)
{
    match(PROGRAM);
    match(ID);
    match(';');
    body();
    match('.');
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

void beginend(void)
{
    match(BEGIN);
    stmtlist();
    match(END);
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

void repeatstmt()
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

void forstmt()
{
    /**/ int label_for, label_end_for; /**/
    match(FOR);

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

/**
* stmtlist -> stmt ; {stmt ;}
* stmt -> begin_end | ifstmt | whilestmt | repstmt | forstmt | idstmt
* begin_end -> BEGIN stmtlist END
* ifstmt -> IF expr THEN stmt [ELSE stmt]
* whilestmt -> WHILE expr DO stmt
* repstmt -> REPEAT stmtlist UNTIL expr
* forstmt -> FOR expr := expr TO expr DO stmt
* idstmt -> expr := expr
**/

void stmt(void)
{
    switch(lookahead){
    case BEGIN:
        beginend();
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
    case CASE:
        match(CASE);
        expression();
        match(OF);
case_list:
        conslist();
        match(':');
        stmt();
        if (lookahead == ';'){
            match(';');
            goto case_list;
        }
        match(END);
        break;
    case ID:
        match(ID);
        match(':');
        match('=');
        expression();
        break;
    }
}

void stmtlist(void)
{
stmt_list:
    stmt();
    if (lookahead == ';'){
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
        fprintf(stderr, "token mismatch... exiting\n");
        exit(-1);
    }
}
