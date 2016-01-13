program area_retangulo;
uses crt;

var
a,b,ar:real;

begin
clrscr;
writeln('Digite a base');
readln(b);
writeln('Digite a altura');
readln(a);
ar:=b*a;
write('Area= ',ar:2:1);
readkey;
end.