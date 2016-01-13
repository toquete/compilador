program tabuada;
uses crt;
var
num,cont:integer;
begin
clrscr;
writeln('Digite um numero');
readln(num);
cont:=1;
while cont<=10 do
begin
writeln(cont,'x',num,'=',cont*num);
cont:=cont+1;
readkey;
end;
readkey;
end.
