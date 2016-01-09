/*
 * @<parser.h>::
 */
#include <stdio.h>

/*
 * standard input buffer is here:
 */
extern FILE    *tape;

extern int      lookahead;
/*
 * Hi-level IO resources:
 */

/*
 * gettoken is essentially the lexer method, which abstracts * a finite
 * automata archive -- implemented in lexer.c
 */
int             gettoken(FILE * tape);

/*
 * parser modules
 */

void            expr(void);
void            term(void);
void            fact(void);
void            match(int);
void            mypas(void);
void            stmt(void);
void            stmtlist(void);
void            proc_func(void);
void            type(void);
void            simple_type(void);
void            typeidentifier(void);
void            idlist (void);
void            constantlist(void);
void            parmlist (void);
void            constant(void);
int             istypeidentifier(void);
void            fieldlist(void);
void            range(void);
int             isrelop(int lookahead);
void            expression (void);
void            label(void);
void            const_pas(void);
void            type_pas(void);
void            var(void);
void            body (void);
void            field_list(void);
void            variable(void);
void            expr_list(void);
void            idstmt(void);
void            beginstmt(void);
void            ifstmt(void);
void            whilestmt(void);
void            repeatstmt(void);
void            forstmt(void);
void            casestmt(void);
void            variablelist(void);
void            withstmt(void);
void            gotostmt(void);

#define MAXSTACKSIZE 0x100
extern double   E_val[MAXSTACKSIZE];
extern double   T_val[MAXSTACKSIZE];

double          retrieve(const char *varname);
void            store(const char *varname, double val);
