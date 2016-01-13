program pares_impares;
uses crt;
var
cont,num,np,ni:integer;
pp,pi:real;
begin
clrscr;
np:=0;
ni:=0;
pp:=0;
pi:=0;
for cont:=1 to 10 do
begin
writeln('Digite o numero');
readln(num);
if (num mod 2)=0 then
begin
np:=np+1
end
else
begin
ni:=ni+1;
end;
end;
pp:=(np*100)/10;
pi:=(ni*100)/10;
writeln('Quantidade de numeros pares: ',np);
writeln('Quantidade de numeros impares: ',ni);
writeln('Porcentagem de numeros pares: ',pp:2:2,'%');
writeln('Porcentagem de numeros impares: ',pi:2:2,'%');
readkey;
end.



