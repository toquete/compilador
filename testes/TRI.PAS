program triang;
uses crt;
var
a,b,c:real;
begin
clrscr;
writeln('Digite o valor de A');
readln(a);
writeln('Digite o valor de B');
readln(b);
writeln('Digite o valor de C');
readln(c);
if (a<b+c) and (b<a+c) and (c<a+b) then
begin
writeln('E um triangulo');
if (a=b) and (b=c) then
writeln('Triangulo equilatero')
else
if (a=b) or (a=c) or (b=c) then
writeln('Triangulo isosceles')
else
writeln('Triangulo escaleno');
end
else
writeln('Nao e um triangulo');
readkey;
end.
