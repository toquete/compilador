program idade;
uses crt;
var
id:integer;
begin
clrscr;
writeln('Digite sua idade');
readln(id);
if id<7 then
writeln('Infantil A')
else
if id<10 then
writeln('Infantil B')
else
if id<13 then
writeln('Juvenil A')
else
if id<18 then
writeln('Juvenil B')
else
if id>=18 then
writeln('Senior');
readkey;
end.
