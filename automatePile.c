#include "automatePile.h"

void ajoutPile(automatePile* a,char c,int etat)
{
    //A utiliser lors d'un decalage
    //Ajoute le caractere lu et le prochain etat à la pile.
    int longeur = (int)((ceil(log10(etat))+1)*sizeof(char));
    char nombre[longeur];
    sprintf(nombre, "%d", etat);
    char * str = (char *)malloc((longeur+1) * sizeof(char));
    str[0] = c;
    str[1] = '\0';
    strcat(str,nombre);
    //TODO Realloc uniquement si besoin, regarder si taille de la pile plus nouveau str plus grand que max
    a->pile = (char *) realloc(a->pile,(a->taillePile+longeur+1) * sizeof(char));
    if (a->pile == NULL)
    {
        fprintf(stderr,"ERROR : Echec reallocation\n");
        exit(-2);
    }
    strcat(a->pile,str);
    free(str);
    a->taillePile = a->taillePile+longeur;
}

void reduirePile(automatePile* a,table table,rule regle)
{
    //A utiliser lors d'une reduction
    //Cherche dans la pile le texte a réduire, on cherche depuis la fin jusqu'a trouvé tous les symboles.
    //Puis supprime le texte. -> Ajouter texte à l'arbre d'analyse
    //Renvoie le prochain etat
    unsigned int tailleTexte = 0;
    //TODO Vérifier des grammaires vides
    while (regle.rhs[tailleTexte] != 0)
    {
       // printf("%c\n",regle.rhs[tailleTexte]);
        tailleTexte++;
    }
    int rechercheEnCours = 1;
    unsigned int teteDeRecherche = tailleTexte;
    if (tailleTexte == 0)
    {
        rechercheEnCours = 0;
    }
    while (rechercheEnCours)
    {
        if (teteDeRecherche == -1)
        {
            rechercheEnCours = 0;
        }
        else
        {
            //VERIFIE SI CHAR NON TERMINAL
            // if ( (regle.rhs[teteDeRecherche] & (1 << 8)) != 0)
            // {
            //    teteDeRecherche--;
            // }
            if (a->pile[a->taillePile-1] == regle.rhs[teteDeRecherche] || a->pile[a->taillePile-1] == -regle.rhs[teteDeRecherche])
            {
                teteDeRecherche--;
            }
            a->taillePile--;
        }
    }
    if(tailleTexte != 0)
    {
        a->taillePile++;
        a->pile[a->taillePile -1] = regle.lhs;
       //printf("PILE : %c ANCIEN ETAT : %d CODE AXIOME : %d %d Prochain etat %d\n",a->pile[a->taillePile - 2],(int)(a->pile[a->taillePile - 2] - '0'),regle.lhs,256 - regle.lhs,table.trans[(int)(a->pile[a->taillePile - 2] - '0') * 256  + 256 - regle.lhs]);
        a->etat = table.trans[(int)(a->pile[a->taillePile - 2] - '0') * 256  + 256 - regle.lhs];
        printf("ETAT : %d\n",a->etat);
        //TODO PEUT ETRE FAIRE UNE FONCTION UTILITAIRE DE CONVERSION DE CHIFFRE EN STRING
        int longeur = (int)((ceil(log10(a->etat)+1)*sizeof(char)));
        char nombre[longeur];
        sprintf(nombre, "%d", a->etat);
        a->pile[a->taillePile] = '\0';
        strcat(a->pile,nombre);
        //TODO ATTENTION NOMBRE PEUT DEPASSER TAILLE DU TEXTE
        a->pile[a->taillePile + longeur+1] = '\0';
        a->taillePile += 2 + longeur;
       // a->etat = etat;
       // ajoutPile(a,regle.lhs,a->etat);
    }
    else
    {
        a->etat = table.trans[(int)(a->pile[a->taillePile - 2] - '0') * 256  + 256 - regle.lhs];
        ajoutPile(a,regle.lhs,a->etat);
    }

}
void analyseflot(const char* texte,grammar gram,table table)
{
    automatePile a = initialiseAutomate(texte);

    while (1)
    {
        signed char c = a.flot[a.teteLecture];
        //printf("TETE : %d CHAR : %c",a.teteLecture,a.flot[a.teteLecture]);
        signed char operation = table.trans[a.etat * 256 + c];
        if (operation == -127)
        {
            printf("REUSSITE\n");
            exit(0);
        }
        else if(operation == 0)
        {
            printf("ECHEC\n");
            exit(0);
        }
        else if (operation > 0)
        {
            a.etat = operation;
            a.teteLecture++;
            printf("LU %c Etat %d decalage vers %d\n",c,a.etat,operation);
            ajoutPile(&a,c,a.etat);
            printf("Pile : %s\n",a.pile);
        }
        else
        {
            printf("LU %c Etat %d reduction par %d\n",c,a.etat,-operation -1);
            reduirePile(&a,table,gram.rules[(-operation)-1]);
            printf("Pile : %s\n",a.pile);
        }
    }

}
automatePile initialiseAutomate(const char* texte)
{
    automatePile automate;
    automate.tailleflot = strlen(texte);
    printf("Taille texte : %d\n",automate.tailleflot);
    automate.flot = malloc(sizeof(char) * automate.tailleflot + 1);
    strcpy(automate.flot,texte);
    automate.pile = malloc(sizeof(char) * 2);
    automate.pile[0]='0';
    automate.pile[1]='\0';
    automate.taillePile = 2;
    automate.teteLecture = 0;
    automate.etat = 0;
    return automate;
}