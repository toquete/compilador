program aulas;
uses crt;
var
na,nf:integer;
begin
clrscr;
writeln('Digite o numero de aulas do semestre');
readln(na);
writeln('Digite o numero de faltas do aluno');
readln(nf);
writeln('Porcentagem de faltas= ',(nf/na)*100:2:2, '%');
write('Porcentagem de presenca= ',((na-nf)/na)*100:2:2, '%');
readkey;
end.