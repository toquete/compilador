program media_while;
uses crt;
var
n1,n2,n3,med:real;
cont:integer;
begin
clrscr;
cont:=1;
while cont<=40 do
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
cont:=cont+1;
readkey;
end;
readkey;
end.
