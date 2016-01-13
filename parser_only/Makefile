# Project MyPas
#
CFLAGS=-g -I. 

mypas: mypas.o parser.o lexer.o keywords.o utils.o
	$(CC) -o $@ $^ -w
clean:
	$(RM) *.o
mostlyclean: clean
	$(RM) *~

