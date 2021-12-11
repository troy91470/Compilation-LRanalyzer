#include "automatePile.h"

void ajoutPile(automatePile* automatePile,char c,int etat)
{
    //A utiliser lors d'un decalage
    //Ajoute le caractere lu et le prochain etat à la pile.
}

int reduirePile(automatePile* automate,char axiome,char* texteAReduire,int tailleTexte)
{
    //A utiliser lors d'une reduction
    //Cherche dans la pile le texte a réduire, on cherche depuis la fin jusqu'a trouvé tous les symboles.
    //Puis supprime le texte. -> Ajouter texte à l'arbre d'analyse
    //Renvoie le prochain etat
}
