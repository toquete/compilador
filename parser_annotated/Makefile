# Project MyPas
#
CFLAGS=-g -I. 

mypas: mypas.o parser.o lexer.o keywords.o utils.o symtab.o
	$(CC) -o $@ $^ -w
clean:
	$(RM) *.o
mostlyclean: clean
	$(RM) *~

