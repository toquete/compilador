/**@<typecheck.c>::**/

#include <typecheck.h>
#include <errorhandler.h>

/*
 * COMENTAR SOBRE OS VALORES DOS TIPOS NO ENUM
*/

int
typecheck(int impltype, int currtype)
{

    if (impltype < NONE || impltype == currtype) {
        return impltype;
    }

    if (impltype == NONE) {
        return currtype;
    }

    if ((impltype == BOOLEAN_TYPE || currtype == BOOLEAN_TYPE) && currtype != impltype) {
        return -1;
    }

    return impltype < currtype ? currtype : impltype;
}
