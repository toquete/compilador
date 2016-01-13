program hipotenusa;
uses crt;

var
l1,l2,hip:real;
begin
clrscr;
writeln('Digite o Cateto 1');
readln(l1);
writeln('Digite o Cateto 2');
readln(l2);
hip:=sqrt(sqr(l1)+sqr(l2));
write('Hipotenusa= ',hip:2:1);
readkey;
end.

























































