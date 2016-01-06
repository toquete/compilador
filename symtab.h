/**@<symtab.h>::**/
#define MAXTBENTRIES 0x1000
extern char     symtab_names[MAXTBENTRIES][MAXIDLEN + 1];
extern int      symtab_lexlevels[MAXTBENTRIES];
extern int      symtab_types[MAXTBENTRIES];
extern int      symtab_next;
int             symtab_lookup(char const *symbol);
int             symtab_append(char const *symbol, int lexlevel);
void            symtab_settype(int, int, int);
