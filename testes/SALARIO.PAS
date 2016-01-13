program salario;
uses crt;
var
sb,pre,acr,vhe,vhn,prdep,inss,irpf,sl:real;
ano,nf,he,dep:integer;

begin
clrscr;
writeln('Digite o salario base do funcionario');
readln(sb);
writeln('Digite o ano de sua admissao');
readln(ano);
writeln('Digite o numero de faltas');
readln(nf);
writeln('Horas extras trabalhadas no mes');
readln(he);
writeln('Digite a quantidade de dependentes');
readln(dep);

vhn:=sb/220;
acr:=(2011-ano)*((sb*0.02)*sb);
prdep:=dep*125;

if he>0 then
vhe:=(vhn*0.5)+vhn
else
vhe:=0;
writeln('O funcionario nao possui horas extras');

if nf=0 then
pre:=(sb*0.05)+sb
else
pre:=0;
writeln('O funcionario nao possui premios por assiduidade');

if sb<=1106.90 then
inss:=sb-(sb*0.08)
else
if sb<1844.83 then
inss:=sb-(sb*0.09)
else
if sb<3689.66 then
inss:=sb-(sb-0.11)
else

if inss>405.86 then
inss:=405.86
else

if sb<=1499.15 then
writeln('Isento de imposto de renda')
else
if sb<=2246.75 then
irpf:=sb-(sb*0.075)
else
if sb<=2995.70 then
irpf:=sb-(sb*0.15)
else
if sb<=3743.19 then
irpf:=sb-(sb*0.225)
else
if sb>3743.19 then
irpf:=sb-(sb*0.275);


sl:=sb+pre+acr+vhe+prdep-inss-irpf;
writeln('Salario liquido do funcionario: R$ ',sl:2:2);
readkey;
end.










