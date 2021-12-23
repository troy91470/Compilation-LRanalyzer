#include <string.h>
#include <stdlib.h>
#include <math.h>
#include "read_file.h"
#include "arbreAnalyse.h"
#include "ecritureLatex.h"


typedef struct automatePile
{
    char* pile;
    char* flot;
    int tailleflot;
    int taillePile;
    int teteLecture;
    int etat;
}automatePile;

void ajoutPile(automatePile* automate,char c,int etat);

void reduirePile(automatePile* automate,table table,rule regle);

void analyseflot(const char* texte,grammar gram,table table);

automatePile initialiseAutomate(const char* texte);
