/**@<errorhandler.c>::**/
#include <stdio.h>

//#include <errorhandler.h>

void fatal_error(int errorcode)
{
    fprintf(stderr,"FATAL ERROR %i\n:",errorcode);
}
