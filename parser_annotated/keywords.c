/*
 * @<keywords.c>::
 */
#include <string.h>
#include <keywords.h>
#include <utils.h>

char *keyword[] = {
    "begin",
    "for",
    "to",
    "do",
    "while",
    "repeat",
    "until",
    "if",
    "then",
    "else",
    "and",
    "or",
    "not",
    "div",
    "mod",
    "var",
    "program",
    "integer",
    "real",
    "double",
    "boolean",
    "true",
    "false",
    "end"
};

int
is_keyword(char *identifier)
{
    int             i;
    for (i = BEGIN; i <= END; i++) {
        if (_strcmp(identifier, keyword[i - BEGIN]) == 0)
            return i;
    }
    return 0;
}
