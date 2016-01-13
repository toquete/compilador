program meses;
uses crt;
var
mes:integer;
begin
clrscr;
writeln('Digite o numero do mes');
readln(mes);
case mes of
1:writeln('Janeiro');
2:writeln('Fevereiro');
3:writeln('Marco');
4:writeln('Abril');
5:writeln('Maio');
6:writeln('Junho');
7:writeln('Julho');
8:writeln('Agosto');
9:writeln('Setembro');
10:writeln('Outubro');
11:writeln('Novembro');
12:writeln('Dezembro');
else
writeln('Mes inexistente');
end;
readkey;
end.
