/* Auteurs: Bjorn LIM CHOU SANG et Thomas ROY */

#include "automatePile.h"
/*
    Fonction qui ajoute deux caractere sur le dessus de la pile de l'automate.
    Le dernier caractere lu et le prochain etat de l'automate.
    La taille de la pile a une taille égale au nombre de caractere + 1.
    Donc reallocation couteuse de la memoire a chaque utilisation de la fonction.
*/
void ajoutPile(automatePile* a,char c,int etat)
{
    //Transformation de l'etat d'entier vers un char *
    int longeur = (int)((ceil(log10(etat))+1)*sizeof(char));
    char nombre[longeur];
    sprintf(nombre, "%d", etat);
    char * str = (char *)malloc((longeur+2) * sizeof(char));
    str[0] = c;
    str[1] = '\0';
    strcat(str,nombre);
    if (a->taillePile+longeur+1 > a->taillePileMax)
    {
        a->taillePileMax = a->taillePileMax+longeur+1;
        a->pile = (char *) realloc(a->pile,(a->taillePileMax+longeur+1) * sizeof(char));
        if (a->pile == NULL)
        {
            fprintf(stderr,"ERROR : Echec reallocation\n");
            exit(-2);
        }
    }
    strcat(a->pile,str);
    free(str);
    a->taillePile = a->taillePile+longeur;
}


/*
    Cherche sur la pile la production de la regle. Ignore les nombres composants les etats.
    On lit la pile de la fin vers le début car c'est une situation FILO.
    Pas de situation d'echec possible si on respecte la table et la grammaire.
*/
void reduirePile(automatePile* a,table table,rule regle)
{
    //A utiliser lors d'une reduction
    //Cherche dans la pile le texte a réduire, on cherche depuis la fin jusqu'a trouvé tous les symboles.
    //Puis supprime le texte. -> Ajouter texte à l'arbre d'analyse
    //Renvoie le prochain etat
    unsigned int tailleTexte = 0;
    while (regle.rhs[tailleTexte] != 0)
    {
        tailleTexte++;
    }
    int rechercheEnCours = 1;
    unsigned int teteDeRecherche = tailleTexte - 1;
    if (tailleTexte == 0)
    {
        rechercheEnCours = 0;
    }
    while (rechercheEnCours && a->taillePile != -1)
    {
        if (teteDeRecherche == -1)
        {
            rechercheEnCours = 0;
        }
        else
        {
            if (a->pile[a->taillePile-1] == regle.rhs[teteDeRecherche] || a->pile[a->taillePile-1] == -regle.rhs[teteDeRecherche])
            {
                teteDeRecherche--;
            }
            a->taillePile--;
        }
    }
    if(a->taillePile < 0)
    {
        fprintf(stderr,"ECHEC DE LA REDUCTION");
        exit(-3);
    }
    if(tailleTexte != 0)
    {
        a->taillePile++;
        a->pile[a->taillePile -1] = '\0';
        int puissance10 = 1;
        int nombre = 0;
        int k = 0;
        while ( (a->pile[a->taillePile - 2 - k]) >= '0' && (a->pile[a->taillePile - 2 - k]) <= '9')
        {
            nombre += (a->pile[a->taillePile - 2 - k] - '0') * puissance10;
            puissance10 *= 10;
            k++;
        }
        a->etat = table.trans[nombre * 256  + 256 - regle.lhs];
        ajoutPile(a,regle.lhs,a->etat);
    }
    else
    {
        int puissance10 = 1;
        int nombre = 0;
        int k = 0;
        while ( (a->pile[a->taillePile - 2 - k]) >= '0' && (a->pile[a->taillePile - 2 - k]) <= '9')
        {
            nombre += (a->pile[a->taillePile - 2 - k] - '0') * puissance10;
            puissance10 *= 10;
            k++;
        }
        a->etat = table.trans[nombre * 256  + 256 - regle.lhs];
        ajoutPile(a,regle.lhs,a->etat);
    }

}


/*
    Execute l'automate a pile grace a la grammaire et la table sur le texte d'entree.
*/
void analyseflot(const char* texte,grammar gram,table table)
{
	char aEcrire[256];
	ecrit_fichier_latex("\\begin{tabular}{l r|l}\n");

	printf("           Flot  |  Pile\n\n    -------------------------------------\n");
	ecrit_fichier_latex(" & Flot & Pile \\\\ \n\\hline\n");

	automatePile a = initialiseAutomate(texte);
	printf("%16s | \n",a.flot + a.teteLecture);
	sprintf(aEcrire," & %s & \\\\ \n",a.flot + a.teteLecture);
	ecrit_fichier_latex(aEcrire);

	arbre* arbre = creeArbre();
	while (1)
	{
		signed char c = a.flot[a.teteLecture];
		signed char operation = table.trans[a.etat * 256 + c];
		int nbChiffresOperation = 1;

		if (operation == -127) // ACCEPTER
		{
			printf("accept \n");
			ecrit_fichier_latex("\\multicolumn{3}{c}{accept} \\\\ \n");
			break;
		}
		else if(operation == 0) // REFUSER
		{
			printf("refuse\n");
			ecrit_fichier_latex("\\multicolumn{3}{c}{refuse} \\\\ \n");
			break;
		}
		else if (operation > 0) //DECALAGE
		{
			a.etat = operation;
			a.teteLecture++;
			ajoutPile(&a,c,a.etat);
			if(operation >= 10)
			{
				nbChiffresOperation = 2;
			}
			printf("d%d %*s | %s\n", operation, 14-nbChiffresOperation, a.flot + a.teteLecture, a.pile);

			sprintf(aEcrire,"d%d & %s & %s\\\\ \n", operation, a.flot + a.teteLecture, a.pile);
			ecrit_fichier_latex(aEcrire);
		}
		else //REDUCTION
		{
			reduirePile(&a,table,gram.rules[(-operation)-1]);
	    		ajouteNoeudArbreAnalyse(arbre,&(gram.rules[(-operation)-1]));
	    		if(-operation -1 >= 10)
	   	 	{
				nbChiffresOperation = 2;
	    		}
	    		printf("r%d %*s | %s\n", -operation -1, 14-nbChiffresOperation, a.flot + a.teteLecture, a.pile);

			sprintf(aEcrire,"r%d & %s & %s\\\\ \n", -operation -1, a.flot + a.teteLecture, a.pile);
			ecrit_fichier_latex(aEcrire);
		}
	}

 	ecrit_fichier_latex("\\end{tabular} \\\\ \n\n");

	for (size_t i = 0; i < arbre->taille; i++)
	{
		litArbreAnalyse(arbre->pile[i]);
		printf("\n\n");
		ecrit_fichier_latex("\n");
	}

	LibereMemoireArbre(arbre);
	free(arbre->pile);
	free(arbre);
	free(a.flot);
	free(a.pile);
}


/*
    Initialise l'automate a pile avec les valeur par defaut.
*/
automatePile initialiseAutomate(const char* texte)
{
    automatePile automate;
    automate.tailleflot = strlen(texte);
    automate.flot = malloc(sizeof(char) * automate.tailleflot + 1);
    strcpy(automate.flot,texte);
    automate.pile = malloc(sizeof(char) * 2);
    automate.pile[0]='0';
    automate.pile[1]='\0';
    automate.taillePile = 2;
    automate.taillePileMax = 2;
    automate.teteLecture = 0;
    automate.etat = 0;
    return automate;
}
