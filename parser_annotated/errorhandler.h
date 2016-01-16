/**@<errorhandler.h>::**/
enum {
    SYMB_OVRLP = -0x100,/** symbol already exists **/
    SYMB_OVRFL,/** symbol table reached the maximum number of entries **/
    SYMB_NFND,/** symbol not found**/
    IVLD_OPDS,/** conflit types of operands**/
};

int error;

void fatal_error(int);
void type_fatal_error(int, int, int);
