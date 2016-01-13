program equacao;
uses crt;
var
a,b,c,del,x1,x2:real;
begin
clrscr;
writeln('Escreva o valor de a, b e c');
readln(a);
readln(b);
readln(c);
del:=sqr(b)-4*a*c;
writeln('delta= ',del:2:2);
if del>0 then
begin
x1:=-b+sqrt(del)/(2*a);
x2:=-b-sqrt(del)/(2*a);
end
else
if del=0 then
x1:=-b/(2*a)
else
if del<0 then
writeln('Nao existe raiz real');
readkey;
end.