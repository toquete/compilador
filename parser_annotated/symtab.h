/**@<symtab.h>::**/
#include <lexer.h>
#define MAXTBENTRIES 0x1000
enum {
    ID_POS = 0,
    DATYPE,
};
char            symtab_names[MAXTBENTRIES * (MAXIDLEN + 1)];
extern int      symtab_descriptor[MAXTBENTRIES][2];
extern int      symtab_next_entry;
int             symtab_lookup(char const *symbol);
int             symtab_append(char const *symbol);
void            symtab_settype(int, int, int);
