program tabuada;
uses crt;
var
num,cont:integer;
begin
clrscr;
writeln('Digite um numero');
readln(num);
for cont:=1 to 10 do
begin
writeln(cont,'x',num,'=',num*cont);
readkey;
end;
readkey;
end.