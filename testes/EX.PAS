{Construa um programa que calcule o salario
liquido de um funcionario. O programa devera
ler o salario base do funcionario, o ano de
adimissao, o numero de faltas e o numero de
horas extras(ocorrido no mes) e a quantidade
de dependentes. O funcionario que nao possuir
faltas no fim do mes tera como premio um acrescimo
de 5% sobre o salario base. A cada ano trabalhado,
o funcionario tera 2% de acrescimo sobre o salario
base. Calcule o inss e o irpf(imposto de renda)
de acordo com a tabela ao lado:

inss            desconto
ate 1106.90            8%
ate 1844.83            9%
ate 3689.66            11%
teto maximo max de contribuicao 408.86

irpf
ate 1499.15             Isento
menor = 2246.75         7.5%
menor = 2995.70         15%
menor = 3743.19         22.5%
maior 3743.19)          27.5%}

program ex;

uses crt;
var
sb,ad,nf,he,qd,aa:real;
a,b,c,d,e,f,g,h:real;

begin
clrscr;

writeln('salario base ');
readln(sb);
writeln('o ano de adimissao ');
readln(ad);
writeln('o numero de faltas no mes ');
readln(nf);
writeln('numero de horas extras no mes ');
readln(he);
writeln('quantidade de dependentes ');
readln(qd);
writeln('qual o ano atual ');
readln(aa);

if nf=0 then
a:= (sb*5)/100
else
a:= 0 ;

if qd>0 then
g:= qd*125
else
g:= 0;

if aa>ad then begin
b:= aa-ad;
c:= ((sb*2)/100)*b ; end
else
c:= 0 ;


if sb<=1106.90 then
d:= (sb*8)/100
else
if sb<=1844.83 then
d:= (sb*9)/100
else
if sb<=3689.66 then
d:= (sb*11)/100;


if sb<=1499.15 then
writeln('isento de irpf')
else
if sb<=2246.75 then
e:= (sb*7.5)/100
else
if sb<=2995.70 then
e:= (sb*15)/100
else
if sb<=3743.19 then
e:= (sb*22.5)/100
else
e:= (sb*27.50)/100;


if he>0 then
h:= (((sb/220)*50)/100)*he
else
h:= 0 ;


f:= (sb+a+c+g+h-d-e) ;

writeln;
writeln('salario liquido R$ ',f:2:2);

readkey;
end.