program nome_sexo;
uses crt;
var
cont,nh,nm:integer;
name:string;
sex:char;
ph,pm:real;
begin
clrscr;
nh:=0;
nm:=0;
ph:=0;
pm:=0;
for cont:=1 to 10 do
begin
writeln('Nome');
readln(name);
writeln('Sexo - M-masculino F-feminino');
readln(sex);
if sex='m' then
begin
nh:=nh+1;
end
else
begin
nm:=nm+1;
end;
end;
ph:=(nh*100)/10;
pm:=(nm*100)/10;
writeln('Numero de homens: ',nh);
writeln('Numero de mulheres: ',nm);
writeln('Porcentagem de homens: ',ph:2:2,'%');
writeln('Porcentagem de mulheres: ',pm:2:2,'%');
readkey;
end.
