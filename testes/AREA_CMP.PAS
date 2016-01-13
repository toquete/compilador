program area_e_comp;
uses crt;

var
raio:integer;
ar,co:real;
begin
clrscr;
writeln('Digite o Raio');
readln(raio);
ar:=3.14*(raio*raio);
co:=2*3.14*raio;
writeln('Area= ',ar:2:2);
write('Comprimento= ',co:2:2);
readkey;
end.