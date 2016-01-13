program calc;
uses crt;
var
comb:char;
o,d:string;
dist,pre,ql,total:real;
begin
clrscr;
writeln('Digite a cidade de origem');
readln(o);
writeln('Digite a cidade destino');
readln(d);
writeln('Digite a distancia entre elas');
readln(dist);
writeln('Digite o combustivel usado - A=alcool G=gasolina');
readln(comb);
writeln('Digite o preco do litro de combustivel');
readln(pre);
case comb of
'A':ql:=(dist/8.55);
'G':ql:=(dist/13.75);
end;
total:=ql*pre;
writeln('Quantidade de litros gastos: ', ql:2:2);
writeln('Total gasto: ', total:2:2);
readkey;
end.
