/*@<keywords.h>::*/

extern char *keyword[];

int is_keyword (char *);

enum {
    BEGIN = 1025,
    FOR,
    TO,
    DOWNTO,
    DO,
    WHILE,
    REPEAT,
    UNTIL,
    CASE,
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
    PROCEDURE,
    FUNCTION,
    INTEGER,
    REAL,
    DOUBLE,
    BOOLEAN,
    STRING,
    TRUE,
    FALSE,
    ARRAY,
    OF,
    LABEL,
    CONST,
    TYPE,
    PACKED,
    SET,
    RECORD,
    pasFILE,
    WITH,
    GOTO,
    IN,
    END
};
