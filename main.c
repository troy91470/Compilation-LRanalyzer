#include "enonce/read_file.h"

int main(int argc, char const *argv[])
{
    file_read file;
    // if (argc != 2)
    // {
    //     printf("Usage : ./a.out fichier\n");
    //     exit(-1);
    // }
    file = read_file(argv[1]);
    printf("Grammaire\n");
    print_grammar(file.G);
    printf("table\n");
    print_table(file.t,file.G);
    printf("\n-----------TEST------------");
    int state = 0;
    int headReader = 0;
    const char* text = argv[2];
    printf("%s\n",text);
    while (1)
    {
        signed char c = text[headReader];
        signed char operation = file.t.trans[state * 256 + c];
        if (operation == -127)
        {
            printf("REUSSITE\n");
            exit(0);
        }
        else if(operation == 0)
        {
            printf("ECHEC\n");
        }
        else if (operation > 0)
        {
            state = operation;
            headReader++;
            printf("LU %c Etat %d decalage vers %d\n",c,state,state);
        }
        else
        {
            printf("LU %c Etat %d reduction par %d\n",c,state,-operation);
            exit(0);
        }
    }
    return 0;
}
