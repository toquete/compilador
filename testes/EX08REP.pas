Program distancia ;
uses crt;
var
cont:integer;
dist,litros,auto,maior,menor:real;
carro:string;
 Begin
      clrscr;
      cont:=1;
      maior:=0;
      menor:=1000;
      while cont<=3 do
      begin
      writeln('Digite o código do carro');
      readln(carro);
      writeln('Digite a distancia percorrida pelo carro (km)');
      readln(dist);
      if dist<>0 then
      begin
      writeln('Digite o consumo de gasolina (L)');
      readln(litros);
      auto:=dist/litros;
      writeln('Autonomia do carro: ',auto:2:2,'km/L');
      if auto>maior then
      maior:=auto
      else
      if auto<menor then
      menor:=auto;
      cont:=cont+1;
      end
      else
      cont:=4;
      end;
      writeln('Carro mais economico: ',maior:2:2);
      writeln('Carrro menos economico: ',menor:2:2); 
 End.
