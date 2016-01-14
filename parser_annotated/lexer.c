/*
 * @<lexer.c>::
 */

#include <stdio.h>
#include <ctype.h>

#include <lexer.h>
#include <tokens.h>
#include <keywords.h>
#include <utils.h>

/*
 * automata cock-tail 
 */

/*
 * skip spaces 
 */

int
skipcomments(FILE * tape)
{
    int head;

_skipspaces:
    while (isspace(head = _getc(tape)));
    if (head == '{') {
        while ((head = _getc(tape)) != '}') {
            if (head == EOF)
                return EOF;
	    }
	    goto _skipspaces;
    } else {
        _ungetc(head, tape);
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
    lexeme[lexcursor] = _getc(tape);
    if (isalpha(lexeme[lexcursor])) {
        lexcursor++;
        while (isalpha(lexeme[lexcursor] = _getc(tape)) ||
               isdigit(lexeme[lexcursor]) || lexeme[lexcursor] == '_') {
            if (lexcursor < MAXIDLEN)
                lexcursor++;
        }
        _ungetc(lexeme[lexcursor], tape);
        lexeme[lexcursor] = 0;

        int id;

        if ((id = is_keyword(lexeme))) {
            return id;
        }

        return ID;
    }
    _ungetc(lexeme[lexcursor], tape);
    return 0;
}

/*
 * digit = [0-9]
 * number = '0'|[1-9][0-9]*
 * exp = ('e'|'E')('+'|'-')?digit+
 * NUM = number(\.digit*)?exp?|\.digit+exp?
 */
int
is_NUM(FILE * tape)
{
    int numtype = 0;
    lexcursor = 0;

    int isRange = 0;

    fseek(tape, -1, SEEK_CUR);
    int isFirstPoint = _getc(tape) == '.';

    lexeme[lexcursor] = _getc(tape);

    if (isFirstPoint && lexeme[lexcursor] == '.') {
        goto end_is_NUM;
    }

    if (isdigit(lexeme[lexcursor])) {
        numtype = UINT;
        if (lexeme[lexcursor] == '0') {
            if ((lexeme[++lexcursor] = _getc(tape)) == '.') {
                if ((lexeme[++lexcursor] = _getc(tape)) == '.') {
                    lexcursor--;
                    _ungetc('.', tape);
                    isRange = 1;
                } else {
                    numtype = UFLOAT;
                    if (isdigit(lexeme[lexcursor]))
                        while (isdigit(lexeme[++lexcursor] = _getc(tape)));
                }
            }
        } else {
            while (isdigit(lexeme[++lexcursor] = _getc(tape)));
            if (lexeme[lexcursor] == '.') {
                if ((lexeme[++lexcursor] = _getc(tape)) == '.') {
                    lexcursor--;
                    _ungetc('.', tape);
                    isRange = 1;
                } else {
                    numtype = UFLOAT;
                    if (isdigit(lexeme[lexcursor]))
                        while (isdigit(lexeme[++lexcursor] = _getc(tape)));
                }
            }
        }
    } else if (lexeme[lexcursor] == '.') {
        if (isdigit(lexeme[++lexcursor] = _getc(tape))) {
            if ((lexeme[++lexcursor] = _getc(tape)) == '.') {
                lexcursor--;
                _ungetc('.', tape);
                isRange = 1;
            } else {
                numtype = UFLOAT;
                if (isdigit(lexeme[lexcursor]))
                    while (isdigit(lexeme[++lexcursor] = _getc(tape)));
            }
        } else {
            _ungetc(lexeme[lexcursor--], tape);
        }
    }

    if (numtype && !isRange) {
        int lexcursorCheck = lexcursor;
        if (tolower(lexeme[lexcursor]) == 'e') {
            lexeme[++lexcursor] = _getc(tape);

            if (lexeme[lexcursor] == '+' || lexeme[lexcursor] == '-') {
                lexeme[++lexcursor] = _getc(tape);
            }

            if (isdigit(lexeme[lexcursor])) {
                numtype = UFLOAT;
                while (isdigit(lexeme[++lexcursor] = _getc(tape)));
            } else {
                while (lexcursor > lexcursorCheck) {
                    _ungetc(lexeme[lexcursor--], tape);
                }
            }
        }
    }

end_is_NUM:
    _ungetc(lexeme[lexcursor], tape);
    lexeme[lexcursor] = 0;
    return numtype;
}

/*
 * visible module is gettokent below: 
 */

int
gettoken(FILE * tape)
{
    int token;

    if ((token = skipcomments(tape)))
        return token;

    if ((token = is_ID(tape)))
        return token;

    if ((token = is_NUM(tape)))
        return token;

    return token = _getc(tape);
}
