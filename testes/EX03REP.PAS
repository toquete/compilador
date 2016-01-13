Program som_media ;
uses crt;
var
cont:integer;
num,med,soma:real;
 Begin
 clrscr;
 cont:=1;
 soma:=0;
 med:=0;
 num:=0;
 while cont<=10 do
 begin
 writeln('Digite um número');
 readln(num);
 if num<>0 then
 begin
 soma:=soma+num;
 med:=soma/10;
 cont:=cont+1;
 end
 else
 cont:=11;
 end;
 writeln('Soma dos números: ',soma:2:2);
 writeln('Média dos números: ',med:2:2);
 End.
