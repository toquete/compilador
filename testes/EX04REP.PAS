Program temperatura ;
uses crt;
 var
    cont:integer;
    resp:char;
    temp,med,maior,menor,soma:real;
 Begin   
      clrscr;
      cont:=1;
      med:=0;
      maior:=-100;
      menor:=100;
      soma:=0;
      resp:='s';
      while cont<=12 do
      begin
      if resp='s' then
      begin
      writeln('Temperatura média do mês');
      readln(temp);
      if temp>maior then
      maior:=temp
      else
      if temp<menor then
      menor:=temp
      else
      soma:=soma+temp;
      med:=soma/cont;
      writeln('Deseja continuar? (s/n)');
      readln(resp);
	 cont:=cont+1;
	 end
	 else
	 cont:=13;
	 end;  
	 writeln('Média anual: ',med:2:2);
      writeln('Maior temperatura: ',maior:2:2);
      writeln('Menor temperatura: ',menor:2:2);
      readkey;  
 End.
