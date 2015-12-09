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
void mypas (void)
{
  match (PROGRAM); match (ID); match (';'); body();
}

void idlist (void)
{
ID_list: 
    match(ID);
    if (lookahead == ',') {
      match (','); goto ID_list;
    }
}

void parmlist (void)
{
  if (lookahead == '(') {
    match('(');
    _parm_spec:
    if(lookahead==VAR)match(VAR);
    idlist();
    if(lookahead==';'){
      match(';');goto _parm_spec;
    }
    match(')');
  }
}

void range(void)
{
  match('[');
  _UINT_list:
  match(UINT);if(lookahead==','){match(',');goto _UINT_list;}
  match(']');
}

void type (void)
{
    switch(lookahead){
      case INTEGER:case REAL:case DOUBLE:case BOOLEAN:case STRING:
	match(lookahead);
      break;
      default:
	match(ARRAY);range();match(OF);type();
    }	
}

void body (void)
{
  while (lookahead == VAR) {
    match (VAR);
ID_list_2:
    idlist();
    match (':'); type(); match (';');
    if (lookahead == ID) goto ID_list_2;
  }
  while (lookahead == PROCEDURE || lookahead == FUNCTION) {
    switch (lookahead) {
    case PROCEDURE:
      match(PROCEDURE);match(ID);parmlist();
      break;
    case FUNCTION:
      match(FUNCTION);match(ID);parmlist();match(':');type();
    }
    match(';');body();match(';');
  }
  begin_end();
}
/**
* stmt -> begin_end | ifstmt | whilestmt | repstmt | forstmt | idstmt
*/
void stmt(void)
{
  switch(lookahead){
    case BEGIN:
      match(BEGIN);stmtlist();match(END);break;
    case IF:
      match(IF);expression();match(THEN);stmt();
      if(lookahead==ELSE){
	match(ELSE);stmt();
      }
      break;
  }
}

int isrelop(int lookahead)
{
    switch(lookahead){
    case '>':
      match('>');
      if(lookahead=='='){match('=');return GEQ;}
      return '>';
    case '<':
      match('<');
      if(lookahead=='='){match('=');return LEQ;}
      else if(lookahead=='>'){match('>');return NEQ;}
      return '<';
    case '=':
      match('='); return '=';
  }
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
    case '+':case '-':case NOT:
      match(lookahead);
  }
  _plus_term:
  term();
  switch(lookahead){
    case'+':case'-':case OR:
      match(lookahead);goto _plus_term;
  }
}
      

void term(void)
{
  _times_fact:
  fact();
  switch(lookahead){
    case'*':case'/':case DIV:case MOD:case AND:
      match(lookahead);goto _times_fact;
  }
}

void fact(void)
{
  switch(lookahead){
    case ID:
      variable();
      if(lookahead==':'){
	match(':');match('=');expression();
      }
      break;
    case UINT:case FLOAT:case STRCONST:case TRUE:case FALSE:
      match(lookahead);break;
    default:
      match('(');expression();match(')');
  }
}   

/** lexer-to-parser interface **/

int             lookahead;

void
match(int predicted)
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
