program raiz;
uses crt;
var
r,num:real;
begin
clrscr;
writeln('Digite o numero');
readln(num);
r:=sqrt(num);
write('Raiz Quadrada= ',r:2:0);
readkey;
end.
