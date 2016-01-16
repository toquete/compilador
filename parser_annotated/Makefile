# Project MyPas
#
CFLAGS=-g -I. 

mypas: mypas.o parser.o lexer.o keywords.o utils.o symtab.o errorhandler.o typecheck.o
	$(CC) -o $@ $^
clean:
	$(RM) *.o
mostlyclean: clean
	$(RM) *~

