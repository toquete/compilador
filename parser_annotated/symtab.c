/**@<symtab.c>::**/
#include <string.h>
#include <lexer.h>
#include <symtab.h>
#include <errorhandler.h>

char            symtab_names[MAXTBENTRIES * (MAXIDLEN + 1)];
int             symtab_names_next_entry = 0;
/** 
 * symtab:
 *          0         1
      |id_position|datatype|
**/

int             symtab_descriptor[MAXTBENTRIES][2];
int             symtab_next_entry = 0;

int
symtab_lookup(char const *symbol)
{
    int             i;
    for (i = symtab_next_entry - 1; i > -1; i--) {
        if (strcmp(symtab_names + symtab_descriptor[i][ID_POS], symbol)
            == 0)
            return i;
    }
    return -1;
}

int
symtab_append(const char *symbol)
{
    int             j = symtab_next_entry;
    int             entry = symtab_lookup(symbol);
    if (entry == -1) {
        strcpy(&symtab_names[symtab_names_next_entry], symbol);
        symtab_descriptor[symtab_next_entry][ID_POS] =
            symtab_names_next_entry;
        symtab_names_next_entry += strlen(symbol) + 1;
        symtab_next_entry++;
    } else {
        fatal_error(SYMB_OVRLP);
        return -1;
    }
    return j;
}

void
symtab_settype(int first, int last, int buitintype)
{
    int             i;
    for (i = first; i < last; i++) {
        symtab_descriptor[i][DATYPE] = buitintype;
    }
}
