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

void constantlist(void)
{
constant_list:
    constant();
    if (lookahead == ','){
        match(',');
        goto constant_list;
    }
}

void parmlist (void)
{
    if (lookahead == '(') {
        match('(');
_parm_spec:
        if (lookahead == PROCEDURE || lookahead == FUNCTION)
            proc_func();
        else {
            if(lookahead == VAR)
                match(VAR);
            idlist();
            match(':');
            typeidentifier();
        }
        if(lookahead==';'){
            match(';');
            goto _parm_spec;
        }
        match(')');
    }
}

void constant(void)
{
    if (lookahead == STRCONST)
        match(STRCONST);
    else {
        if (lookahead == '+' || lookahead == '-')
            match(lookahead);
        switch(lookahead){
        case ID:
            match(ID);
            break;
        default:
            match(UINT);
        }
    }
}

void typeidentifier(void)
{
    switch(lookahead){
    case INTEGER:
        match(INTEGER);
        break;
    case REAL:
        match(REAL);
        break;
    case DOUBLE:
        match(DOUBLE);
        break;
    case BOOLEAN:
        match(BOOLEAN);
        break;
    default:
        match(STRING);
    }
}

int istypeidentifier(void)
{
    switch(lookahead){
    case INTEGER:case REAL:case DOUBLE:case BOOLEAN:case STRING:
        return lookahead;
    }

    return 0;
}

void simple_type(void)
{
    if (istypeidentifier())
        typeidentifier();
    else{
        switch(lookahead){
        case '(':
            match('(');
            idlist();
            match(')');
            break;
        default:
            constant();
            match('.');
            match('.');
            constant();
        }
    }
}

void field_list(void)
{
    if(lookahead == ID){
        idlist();
        match(':');
        type();
        if(lookahead == ';'){
            match(';');
            goto _CASE_lbl;
        }
    } else {
_CASE_lbl:
        match(CASE);
        if(lookahead == ID){
            match(ID);
            match(':');
        }
        typeidentifier();
        match(OF);
_CONST_list:
        const_pas();
        match(':');
        match('(');
        field_list();
        match(')');
        if(lookahead == ';'){
            match(';');
            goto _CONST_list;
        }
    }

}

void range(void)
{
    match('[');
_UINT_list:
    simple_type();
    if(lookahead==','){
        match(',');
        goto _UINT_list;
    }
    match(']');
}

void type (void)
{
    if (lookahead == '^'){
        match('^');
        typeidentifier();
    } else {
        if (lookahead == PACKED)
            match(PACKED);
        switch (lookahead){
        case SET:
            match(SET);
            match(OF);
            simple_type();
            break;
        case ARRAY:
            match(ARRAY);
            range();
            match(OF);
            type();
            break;
        case RECORD:
            match(RECORD);
            field_list();
            match(END);
        case pasFILE:
            match(pasFILE);
            match(OF);
            type();
        default:
            simple_type();
        }
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
    case UINT:case FLOAT:case STRCONST:case TRUE:case FALSE:
        match(lookahead);
        break;
    default:
        match('(');
        expression();
        match(')');
    }
}

void label(void)
{
    if (lookahead == LABEL){
        match(LABEL);
UINT_list:
        match(UINT);
        if (lookahead == ','){
            match(',');
            goto UINT_list;
        }
        match(';');
    }
}

void const_pas(void)
{
    if (lookahead == CONST){
        match(CONST);
const_list:
        match(ID);
        match('=');
        constant();
        match(';');
        if (lookahead == ID)
            goto const_list;
    }
}

void type_pas(void)
{
    if (lookahead == TYPE){
        match(TYPE);
type_list:
        match(ID);
        match('=');
        type();
        match(';');
        if (lookahead == ID)
            goto type_list;
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

void proc_func(void)
{
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
        typeidentifier();
    }
}

void body (void)
{
    label();
    const_pas();
    type_pas();
    var();

    while (lookahead == PROCEDURE || lookahead == FUNCTION){
        proc_func();
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
    match('(');
    idlist();
    match(')');
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
void stmt(void)
{
    switch(lookahead){
    case BEGIN:
        match(BEGIN);
        stmtlist();
        match(END);
        break;
    case IF:
        match(IF);
        expression();
        match(THEN);
        stmt();

        if(lookahead==ELSE){
            match(ELSE);
            stmt();
        }
        break;
    case WHILE:
        match(WHILE);
        expression();
        match(DO);
        stmt();
        break;
    case REPEAT:
        match(REPEAT);
        stmtlist();
        match(UNTIL);
        expression();
        break;
    case FOR:
        match(FOR);
        expression();
        match(TO);
        expression();
        match(DO);
        stmt();
        break;
    case CASE:
        match(CASE);
        expression();
        match(OF);
case_list:
        constantlist();
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
