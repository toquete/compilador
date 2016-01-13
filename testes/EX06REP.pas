Program bois;
uses crt;
 var
 cont:integer;
 id:string;
 peso,maior,menor,soma,media:real;
 resp:char;
 Begin
      clrscr;
      cont:=1;
      maior:=0;
      menor:=1000;
      soma:=0;
      media:=0;
      while cont<=5 do
      begin
	 writeln('Digite a identificação do boi');
      readln(id);
      writeln('Digite o peso do boi (em kg)');
      readln(peso);
      writeln('Boi ',id,' tem ',peso:2:2,' kg');
      writeln('Deseja continuar? (s/n)');
	 readln(resp);
	 if resp='s' then
	 begin
	 if peso>maior then
	 maior:=peso
	 else
	 if peso<menor then
	 menor:=peso
	 else
	 soma:=soma+peso;
	 media:=soma/cont;
	 cont:=cont+1;
	 end
	 else
	 cont:=6;
	 end;
	 writeln('Boi mais gordo: ',maior:2:2,'kg');
	 writeln('Boi mais magro: ',menor:2:2,'kg');
	 writeln('Soma dos pesos: ',soma:2:2,'kg');
	 writeln('Peso medio: ',media:2:2,'kg');     
 End.
