#include <typecheck.h>
#include <errorhandler.h>

/*
 * COMENTAR SOBRE OS VALORES DOS TIPOS NO ENUM
*/

int
typecheck(int impltype, int currtype)
{
    if (impltype < BOOLEAN_TYPE || impltype == currtype) {
        return impltype;
    }

    if (impltype == BOOLEAN_TYPE) {
        return -1;
    }

    return impltype < currtype ? currtype : impltype;
}
