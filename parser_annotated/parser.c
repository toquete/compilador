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
#include <gencode.h>

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
    int typevar;

    if (lookahead == '(') {
        match('(');
_parm_spec:
        if (lookahead == VAR)
            match(VAR);

        /**/int initial = symtab_next_entry/**/;
        idlist();
        match(':');
        typevar = type();
        /**/symtab_settype(initial, symtab_next_entry, typevar)/**/;

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

int initexpr = 0;

int expression(/**/int inheritedtype/**/)
{
    /**/int impltype;
    int impltypeAux;

    impltype = expr()/**/;

    initexpr = 0;

    /**/if (isrelop()) {
        impltypeAux = expr();
        if (typecheck(impltype, impltypeAux) == -1) {
            type_fatal_error(IVLD_OPDS, impltype, impltypeAux);
        }
        impltype = BOOLEAN_TYPE;
    }/**/

    /**/if (typecheck(inheritedtype, impltype) == -1)
        type_fatal_error(IVLD_OPDS, inheritedtype, impltype)/**/;

    /**/return impltype;/**/
}

int expr(void)
{
    /**/int impltype = NONE;/**/

    switch (lookahead) {
    case '+': case '-':
        /**/impltype = NUMBER_TYPE;/**/
        match(lookahead);
    }

    /**/int synthtype;/**/
_plus_term:
    /**/synthtype = term(impltype);/**/

    /**/if (impltype > synthtype) {
        type_fatal_error(IVLD_OPDS, impltype, synthtype);
    }

    impltype = synthtype;/**/

    switch (lookahead) {
    /**/case '+': case '-': case OR:
        switch (lookahead) {
        case '+': case '-':
            if (impltype < NUMBER_TYPE)
                type_fatal_error(IVLD_OPDS, NUMBER_TYPE, impltype);

            /**/genprint("\t%s ", lookahead == '+' ? "add" : "sub");/**/
            break;
        case OR:
            if (impltype != BOOLEAN_TYPE)
                /**/type_fatal_error(IVLD_OPDS, BOOLEAN_TYPE, impltype);/**/

            /**/genprint("\t%s ", lexeme);/**/
            break;
        }

        match(lookahead);
        goto _plus_term;
    }

    /**/return impltype;/**/
}


int term(/**/int inheritedtype/**/)
{
    /**/int impltype;/**/

_times_fact:
    /**/impltype = typecheck(inheritedtype, fact());/**/
    switch (lookahead) {
    case '*': case '/': case DIV: case MOD: case AND:
        switch (lookahead) {
        case '*': case '/':
            /**/if (impltype < NUMBER_TYPE)
                type_fatal_error(IVLD_OPDS, NUMBER_TYPE, impltype);/**/

            /**/genprint("\t%s ", lookahead == '*' ? "mul" : "div");/**/
            break;
        case DIV: case MOD:
            /**/if (impltype != INTEGER_TYPE)
                type_fatal_error(IVLD_OPDS, INTEGER_TYPE, impltype);/**/

            /**/genprint("\t%s ", lexeme);/**/
            break;
        case AND:
            /**/if (impltype != BOOLEAN_TYPE)
                type_fatal_error(IVLD_OPDS, BOOLEAN_TYPE, impltype);/**/

            /**/genprint("\t%s ", lexeme);/**/
            break;
        }

        match(lookahead);
        goto _times_fact;
    }

    /**/return impltype;/**/
}

int fact(void)
{
    /**/int impltype;/**/

    /**/int sym_index;/**/

    switch (lookahead) {
    case '(':
        match('(');
        /**/impltype = expression(NONE);/**/
        match(')');
        break;
    case NOT:
        match(NOT);

        /**/impltype = fact();/**/
        /**/if (impltype != BOOLEAN_TYPE) {
            type_fatal_error(IVLD_OPDS, BOOLEAN_TYPE, impltype);
        }/**/

        break;
    case UINT: case UFLOAT: case UDOUBLE:
        switch (lookahead) {
        case UINT:
            /**/impltype = INTEGER_TYPE;/**/
            break;
        case UFLOAT:
            /**/impltype = REAL_TYPE;/**/
            break;
        case UDOUBLE:
            /**/impltype = DOUBLE_TYPE;/**/
            break;
        }

        if (!initexpr) {
            /**/genprint("\tmov %s, _acc\n", lexeme);/**/
            initexpr = 1;
        } else {
            /**/genprint("%s, _acc\n", lexeme);/**/
        }

        match(lookahead);
        break;
    case TRUE:
    case FALSE:
        /**/impltype = BOOLEAN_TYPE;/**/

        if (!initexpr) {
            /**/genprint("\tmov %s, _acc\n", lexeme);/**/
            initexpr = 1;
        } else {
            /**/genprint("%s, _acc\n", lexeme);/**/
        }

        match(lookahead);
        break;
    default:
        /**/sym_index = symtab_lookup(lexeme);/**/

        /**/if (sym_index == -1) {
            fatal_error(SYMB_NFND);
            impltype = -1;
        } else {
            impltype = symtab_descriptor[sym_index][DATYPE];
        }/**/

        if (!initexpr) {
            /**/genprint("\tmov %s, _acc\n", lexeme);/**/
            initexpr = 1;
        } else {
            /**/genprint("%s, _acc\n", lexeme);/**/
        }

        match(ID);
    }

    /**/return impltype;/**/
}

void var(void)
{
    /**/gensecdata()/**/;

    int typevar;
    /**/int initial/**/;
    while (lookahead == VAR) {
        match (VAR);
ID_list_2:
        /**/initial = symtab_next_entry/**/;
        idlist();
        match(':');
        typevar = type();
        /**/symtab_settype(initial, symtab_next_entry, typevar)/**/;
        /**/genvar(initial, symtab_next_entry, typevar)/**/;

        match(';');
        if (lookahead == ID)
            goto ID_list_2;
    }
}

void body (void)
{
    var();

    /**/gensectext()/**/;

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
        impltype = symtab_descriptor[sym_index][DATYPE];
    }/**/

    /**/char id_label[100]/**/;
    /**/strcpy(id_label, lexeme);/**/

    match(ID);

    if (lookahead == ':') {
        match(':');
        match('=');

        /**/int synthtype;
        synthtype = expression(NONE);/**/

        genprint("\tmov _acc, %s\n", id_label);

        /**/switch (impltype) {
        case BOOLEAN_TYPE:
            if (synthtype != BOOLEAN_TYPE)
                type_fatal_error(IVLD_OPDS, BOOLEAN_TYPE, synthtype);
            break;
        case -1:
            break;
        default:
            if (impltype < synthtype || synthtype == BOOLEAN_TYPE)
                type_fatal_error(IVLD_OPDS, impltype, synthtype);
            break;
        }/**/
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

    /**/genprint("\tjz .L%i\n", label_endif = label_else = label_counter);/**/
    /**/label_counter++;/**/

    match(THEN);
    stmt();

    if (lookahead == ELSE) {
        /**/genprint("\tgoto .L%i\n", label_endif = label_counter);/**/
        /**/label_counter++;/**/
        /**/genprint(".L%i:\n", label_else);/**/

        match(ELSE);
        stmt();
    }
}

void whilestmt(void)
{
    /**/ int label_while, label_end_while; /**/

    match(WHILE);

    /**/genprint(".L%i:\n", label_while = label_counter);/**/
    /**/label_counter++;/**/

    expression(BOOLEAN_TYPE);

    /**/genprint("\tjz .L%i\n", label_end_while = label_counter);/**/
    /**/label_counter++;/**/

    match(DO);
    stmt();

    /**/genprint("\tgoto .L%i\n", label_while);/**/
    /**/genprint(".L%i\n", label_end_while);/**/
}

void repeatstmt(void)
{
    /**/ int label_repeat; /**/
    match(REPEAT);

    /**/genprint(".L%i:\n", label_repeat = label_counter);/**/
    /**/label_counter++;/**/

    stmtlist();

    match(UNTIL);
    expression(/**/BOOLEAN_TYPE/**/);

    /**/genprint("\tjnz .L%i\n", label_repeat);/**/
}

void forstmt(void)
{
    /**/ int label_for, label_end_for; /**/

    match(FOR);

    /**/int sym_index;/**/

    /**/if ((sym_index = symtab_lookup(lexeme)) == -1) {
        fatal_error(SYMB_NFND);
    } else {
        if (symtab_descriptor[sym_index][DATYPE] != INTEGER_TYPE)
            type_fatal_error(IVLD_OPDS, INTEGER_TYPE, symtab_descriptor[sym_index][DATYPE]);
    }/**/

    match(ID);
    match(':');
    match('=');

    /**/int synthtype = expression(NONE);

    if (synthtype != INTEGER_TYPE)
        type_fatal_error(IVLD_OPDS, INTEGER_TYPE, expression(NONE));

    match(TO);

    synthtype = expression(NONE);

    if (synthtype != INTEGER_TYPE)
        type_fatal_error(IVLD_OPDS, INTEGER_TYPE, expression(NONE));

    /**/genprint(".L%i:\n", label_for = label_counter);/**/
    /**/label_counter++;/**/
    /**/genprint("\tje .L%i\n", label_end_for);/**/

    match(DO);
    stmt();

    /**/genprint("\tgoto .L%i\n", label_for);/**/
    /**/genprint(".L%i\n", label_end_for);/**/
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
        if (predicted >= BEGIN && keyword[predicted - BEGIN]) {
            fprintf(stderr, "Syntax error:%d:%d: expected '%s' but was '%s'\n",
                    linecount + 1,
                    linecursor[linecount] + 1 - lexcursor,
                    keyword[predicted - BEGIN],
                    lexeme);
        } else if (!predicted || !keyword[predicted - BEGIN]) {
            fprintf(stderr, "Syntax error:%d:%d: '%s' not expected\n",
                    linecount + 1,
                    linecursor[linecount] + 1 - lexcursor,
                    lexeme);
        } else {
            fprintf(stderr, "Syntax error:%d:%d: expected '%c' but was '%s'\n",
                    linecount + 1,
                    linecursor[linecount] + 1 - lexcursor,
                    predicted,
                    lexeme);
        }
        exit(-1);
    }
}
