/*
 * @<keywords.c>::
 */
#include <string.h>
#include <keywords.h>

char *keyword[] = {
    "begin",
    "for",
    "to",
    "do",
    "while",
    "repeat",
    "until",
    "case",
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
    "procedure",
    "function",
    "integer",
    "real",
    "double",
    "boolean",
    "string",
    "true",
    "false",
    "array",
    "of",
    "label",
    "const",
    "type",
    "packed",
    "set",
    "record",
    "end"
};

int
is_keyword(char *identifier)
{
    int             i;
    for (i = BEGIN; i <= END; i++) {
        if (strcmp(identifier, keyword[i - BEGIN]) == 0)
            return i;
    }
    return 0;
}
