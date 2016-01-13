Program idade_etapa ;
uses crt;
 var
 nome:string;
 idade,cont:integer;
 resp:char;
 Begin
 clrscr;
 cont:=1;
 resp:='s';
 writeln('Digite o nome');
 readln(nome);
 writeln('Digite a idade');
 readln(idade);
 while cont<=5 do
 begin
 if resp='s' then
 begin
 if idade<=10 then
 begin
 writeln('Criança');
 end
 else
 if idade<=18 then
 begin
 writeln('Adolescente');
 end
 else
 if idade<=25 then
 begin
 writeln('Jovem');
 end
 else
 if idade<=35 then
 begin
 writeln('Adulto');
 end
 else
 if idade<=50 then
 begin
 writeln('Experiente');
 end
 else
 if idade>50 then
 begin
 writeln('Idoso');
 end;
 writeln('Deseja continuar? (s/n)');
 readln(resp);
 cont:=cont+1;
 end
 else
 cont:=6;
 end;
 End.
