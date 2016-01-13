/**@<symtab.h>::**/
#include <string.h>

#include <lexer.h>
#include <symtab.h>

char            symtab[MAXTBENTRIES][MAXIDLEN + 1];

double          memory[MAXTBENTRIES];

int             symtab_next = 0;

int
symtab_lookup(char const *symbol)
{
    int             i;
    for (i = 0; i < symtab_next; i++) {
        if (strcmp(symtab[i], symbol) == 0)
            return i;
    }
    return -1;
}

double
retrieve(const char *varname)
{
    int             address;
    if ((address = symtab_lookup(varname)) > -1) {
        return memory[address];
    }
    strcpy(symtab[symtab_next], varname);
    symtab_next++;
    return 0;
}

void
store(const char *varname, double val)
{
    int             address;
    if ((address = symtab_lookup(varname)) < 0) {
        strcpy(symtab[address = symtab_next], varname);
        symtab_next++;
    }
    memory[address] = val;
}
