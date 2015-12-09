/**@<symtab.h>::**/
#define MAXTBENTRIES 0x1000
char            symtab[MAXTBENTRIES][MAXIDLEN + 1];
double          memory[MAXTBENTRIES];
extern int      symtab_next;
int             symtab_lookup(char const *symbol);
double          retrieve(const char *varname);
void            store(const char *varname, double val);
