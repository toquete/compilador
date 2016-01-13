program media_for;
uses crt;
var
n1,n2,n3,med:real;
cont:integer;
begin
clrscr;
for cont:=1 to 40 do
begin
writeln('Digite a Nota 1');
readln(n1);
writeln('Digite a Nota 2');
readln(n2);
writeln('Digite a Nota 3');
readln(n3);
med:=(n1+n2+n3)/3;
writeln('Media: ',med:2:2);
if med<6 then
writeln ('Reprovado')
else
writeln('Aprovado');
readkey;
end;
readkey;
end.
