Program nota_situacao ;
uses crt;
 var
 cont:integer;
 n1,n2,n3,n4,soma,somaclasse,med,medclasse,acima,abaixo:real;
 nome:string;
 Begin
      clrscr;
      acima:=0;
      abaixo:=0;
	 for cont:=1 to 5 do
      begin
      writeln('Digite o nome do aluno');
      readln(nome);
      writeln('Digite a 1 nota do 1 semestre');
      readln(n1);
      writeln('Digite a 2 nota do 1 semestre');
      readln(n2);
      writeln('Digite a 1 nota do 2 semestre');
      readln(n3);
      writeln('Digite a 2 nota do 2 semestre');
      readln(n4);
      soma:=(n1+n2+n3+n4);
      med:=soma/4;
      writeln('Media do aluno: ',med:2:2);
      if med<=3 then
      begin
	 writeln('Reprovado');
      end
      else
      if med<7 then
      begin
      writeln('Em exame');
      end
      else
      if med>=7 then
      begin
      writeln('Aprovado');
      end;
      if med>=7 then
      acima:=acima+1
      else
      abaixo:= abaixo+1;
      end;
	 somaclasse:=soma*cont;
      medclasse:=somaclasse/cont;
      writeln('Media da classe: ',medclasse:2:2);
      writeln('Alunos abaixo da media da classe: ',abaixo:2:0);
      writeln('Alunos acima da media da classe: ',acima:2:0);
      readkey;
      
      
 End.
