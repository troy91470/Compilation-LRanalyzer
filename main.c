#include "automatePile.h"

int main(int argc, char const *argv[])
{
    file_read file;
    if (argc != 3)
    {
        printf("Usage : ./a.out table texte\n");
        exit(-1);
    }
    file = read_file(argv[1]);
    printf("Grammaire\n");
    print_grammar(file.G);
    printf("table\n");
    print_table(file.t,file.G);
    printf("\n-----------TEST------------\n");
    analyseflot(argv[2],file.G,file.t);
    return 0;
}
