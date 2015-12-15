/*
 * @<lexer.c>::
 */

#include <stdio.h>
#include <ctype.h>

#include <lexer.h>
#include <tokens.h>
#include <keywords.h>

/*
 * automata cock-tail 
 */

/*
 * skip spaces 
 */

int
skipcomments(FILE * tape)
{
    int             head;

_skipspaces:
    while (isspace(head = getc(tape)));
    if(head == '{') {
	    while((head = getc(tape)) != '}') {
		if (head == EOF)
                    return EOF;
	    }
	    goto _skipspaces;
    } else {
	    ungetc(head, tape);
    }
    return 0;
}

/*
 * lexeme definition 
 */
char            lexeme[MAXIDLEN + 1];
int             lexcursor;

/*
 * ID = [A-Za-z][A-Za-z0-9_]*
 */
int
is_ID(FILE * tape)
{
    lexcursor = 0;
    lexeme[lexcursor] = getc(tape);
    if (isalpha(lexeme[lexcursor])) {
        lexcursor++;
        while (isalpha(lexeme[lexcursor] = getc(tape)) ||
               isdigit(lexeme[lexcursor]) || lexeme[lexcursor] == '_') {
            if (lexcursor < MAXIDLEN)
                lexcursor++;
        }
        ungetc(lexeme[lexcursor], tape);
        lexeme[lexcursor] = 0;

        int id;

        if (id = is_keyword(lexeme)) {
            return id;
        }

        return ID;
    }
    ungetc(lexeme[lexcursor], tape);
    return 0;
}

/*
 * EXP = ('e'|'E')('+'|'-')?[0-9]+
 */
int
is_EXP(FILE * tape)
{
    lexeme[lexcursor] = getc(tape);
}

/*
 * NUM = [1-9][0-9]* | '0'
 */
int
is_NUM(FILE * tape)
{
    int numtype = 0;
    lexcursor = 0;
    lexeme[lexcursor] = getc(tape);
    if (isdigit(lexeme[lexcursor])) {
        numtype = UINT;
        if (lexeme[lexcursor] != '0') {
            lexcursor++;
            while (isdigit(lexeme[lexcursor] = getc(tape)))
                lexcursor++;
        } else {
            lexcursor++;
            lexeme[lexcursor] = getc(tape);
        }
        if (lexeme[lexcursor] == '.') {
	  numtype = FLOAT;
            lexcursor++;
            while (isdigit(lexeme[lexcursor] = getc(tape)))
                lexcursor++;
        }
        ungetc(lexeme[lexcursor], tape);
        lexeme[lexcursor] = 0;
        return numtype;
    }
    if (lexeme[lexcursor] == '.') {
        lexcursor++;
        if (isdigit(lexeme[lexcursor] = getc(tape))) {
            lexcursor++;
            while (isdigit(lexeme[lexcursor] = getc(tape)))
                lexcursor++;
            ungetc(lexeme[lexcursor], tape);
            lexeme[lexcursor] = 0;
            return FLOAT;
        }
        ungetc(lexeme[lexcursor], tape);
        lexcursor--;
    }
    ungetc(lexeme[lexcursor], tape);
    return 0;
}

/*
 * visible module is gettokent below: 
 */

int
gettoken(FILE * tape)
{
    int             token;

    if (token = skipcomments(tape))
        return token;

    if (token = is_ID(tape))
        return token;

    if (token = is_NUM(tape))
        return token;

    return token = getc(tape);
}
