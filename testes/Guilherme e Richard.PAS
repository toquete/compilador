program pessoal;
uses crt;
var
idade,homens,mulheres,mulheresa,homensa:integer;
resp,sexo:char;
nome:string;
porc:real;

begin
clrscr;
mulheres:=0;
homensa:=0;
mulheresa:=0;
homens:=0;

repeat
writeln('Digite o nome');
readln(nome);
writeln('Digite o sexo');
readln(sexo);
writeln('Digite a idade');
readln(idade);
writeln('Deseja continuar? (s/n)');
readln(resp);

if sexo='m' then
begin
homens:=homens+1;
if idade>25 then
homensa:=homensa+1;
end
else

if sexo='f' then
begin
mulheres:=mulheres+1;
if idade>18 then
mulheresa:=mulheresa+1;
end;

porc:=((homensa)*100)/(homens+mulheres);
until resp='n';

writeln('Numero de homens: ',homens);
writeln('Numero de mulheres acima de 18 anos: ',mulheresa);
writeln('Porcentagem de homens acima de 25 anos: ',porc:2:2);
readkey;
end.
