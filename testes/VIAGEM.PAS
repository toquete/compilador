program viagem;
uses crt;
var
D,L,P,KM,V:real;
begin
clrscr;
writeln('Digite a distancia');
readln(D);
writeln('Digite o numero de litros');
readln(L);
writeln('Digite o preco do litro');
readln(P);
KM:=D/L;
V:=L*P;
writeln('A autonomia do veiculo e de: ', KM:2:2, 'km/l');
write('O total gasto e de: ',V:2:2, ' reais');
readkey;
end.