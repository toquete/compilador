/**@<errorhandler.h>::**/
enum {
    SYMB_OVRLP = -0x100,/** symbol already exists **/
    SYMB_OVRFL,/** symbol table reached the maximum number of entries **/
    SYMB_NFND,
    IVLD_OPDS,
};


void fatal_error(int);
void type_fatal_error(int, int, int);
