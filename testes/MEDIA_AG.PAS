program media;
uses crt;

var
n1,n2,n3,n4:real;
med:real;

begin
clrscr;
writeln('Digite a Nota 1');
readln(n1);
writeln('Digite a Nota 2');
readln(n2);
writeln('Digite a Nota 3');
readln(n3);
writeln('Digite a Nota 4');
readln(n4);
med:= (n1+n2+n3+n4)/4;
write('media= ',med:2:1);
readkey;
end.