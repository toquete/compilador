program indice;
uses crt;
var
peso,alt,imc:real;
begin
clrscr;
writeln('Informe o seu peso');
readln(peso);
writeln('Informe sua altura');
readln(alt);
imc:=peso/sqr(alt);
write('IMC igual a: ',imc:2:2);
readkey;
end.