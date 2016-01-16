/**@<gencode.h>::**/

#include <stdio.h>
#include <stdarg.h>
#include <gencode.h>
#include <errorhandler.h>

/*void readln()
{


}

void read()
{


}

void write(char *str)
{
    write("string");
    fprintf(ascode, str);
}

void writeln()
{

}*/

void genprint(const char* s, ...)
{
    if (error)
        return;

    va_list arg;
    va_start (arg, s);

    fprintf(ascode, s, arg);

    va_end(arg);
}

void gensecdata()
{
    genprint("\t.data\n");
}

void genvar(char *varname)
{
    genprint("%s:\tdb\n", varname);
}


