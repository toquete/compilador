/**@<typecheck.c>::**/

#include <typecheck.h>
#include <errorhandler.h>

/**
 * Validacao de tipos dos operandos
 *
 * 0 -> BOOLEAN
 * 1 -> NUMBER (INTEGER + REAL + DOUBLE)
 * 2 -> INTEGER
 * 3 -> REAL
 * 4 -> DOUBLE
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
