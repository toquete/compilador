/**@<gencode.h>::**/

#include <stdio.h>
#include <gencode.h>

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

void gensecdata()
{
    fprintf(ascode,"\t.data\n");
}

void genvar(char *varName)
{
    fprintf(ascode, "%s:\tdb\n",varName);
}
