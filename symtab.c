/**@<symtab.h>::**/
#include <string.h>

#include <lexer.h>
#include <symtab.h>
#include <errorhandler.h>
#include <errorhandler.c>

char     symtab_names[MAXTBENTRIES][MAXIDLEN + 1];
int      symtab_lexlevels[MAXTBENTRIES];
int      symtab_types[MAXTBENTRIES];


char            symtab[MAXTBENTRIES][MAXIDLEN + 1];

double          memory[MAXTBENTRIES];

int             symtab_next = 0;

int
symtab_lookup(char const *symbol)
{
    int             i;
    for (i = symtab_next - 1; i > -1; i--) {
        if (strcmp(symtab_names[i], symbol) == 0)
            return i;
    }
    return -1;
}

//** CHECAR OVERFLOW DOS ARRAYS!!!!! DESCONA METADE DA NOTA**//
//** CHECAR FIM DE ARQUIVO NOS COMENTARIOS!!**//
//** ARRUMAR O PONTO FLUTUANTE!!!**//


int symtab_append(const char* symbol, int lexlevel)
{
    int j = symtab_next;
    int entry = symtab_lookup(symbol);
    if(entry == -1 || symtab_lexlevels[entry] < lexlevel){
        strcpy(symtab_names[symtab_next], symbol);
        symtab_lexlevels[symtab_next] = lexlevel;
        symtab_next++;
    }else{
        fatal_error(SYMB_OVRL);//tabela de erros
        return -1;
    }
    return j;
}

void symtab_settype(int first, int last, int builtintype)
{
    int i;
    /**/for(i = first; i < last; i++){
        symtab_types[i] = builtintype;
    }
}
