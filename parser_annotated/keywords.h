/*@<keywords.h>::*/

extern char *keyword[];

int is_keyword (char *);

enum {
    BEGIN = 1025,
    FOR,
    TO,
    DO,
    WHILE,
    REPEAT,
    UNTIL,
    IF,
    THEN,
    ELSE,
    AND,
    OR,
    NOT,
    DIV,
    MOD,
    VAR,
    PROGRAM,
    INTEGER,
    REAL,
    DOUBLE,
    BOOLEAN,
    TRUE,
    FALSE,
    END
};
