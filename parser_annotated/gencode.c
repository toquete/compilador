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

void genprint(const char *format, ...)
{
    if (error)
        return;

    va_list args;
    va_start(args, format);
    vfprintf(stdout, format, args);
    va_end(args);
}

void gensecdata()
{
    genprint("\t.data\n");
}

void genvar(char *varname)
{
    genprint("%s:\tdb\n", varname);
}


