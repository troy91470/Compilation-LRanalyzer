#include <string.h>

typedef struct automatePile
{
    char* pile;
    int taillePile;
}automatePile;

void ajoutPile(automatePile* automate,char c,int etat);

int reduirePile(automatePile* automate,char axiome,char* texteAReduire,int tailleTexte);