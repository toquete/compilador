program imc;
uses crt;
var
peso,alt,ind:real;
begin
clrscr;
writeln('Digite o seu peso');
readln(peso);
writeln('Digite sua altura');
readln(alt);
ind:=peso/(sqr(alt));
writeln('Indice: ', ind:2:2);
if ind<18.5 then
writeln('Abaixo do peso')
else
if ind<=25 then
writeln('Peso normal')
else
if ind<=30 then
writeln('Acima do peso')
else
if ind>30 then
writeln('Obeso');
readkey;
end.