/* Auteurs: Bjorn LIM CHOU SANG et Thomas ROY */

#include "arbreAnalyse.h"


noeud* creeNoeud(rule* regle)
{
	unsigned int tailleTexte = 0;
	noeud *Nouveaunoeud = malloc(sizeof(noeud));
	if(Nouveaunoeud == NULL)
	{
		fprintf(stderr, "Erreur allocation memoire.\n");
		exit(EXIT_FAILURE);
	}

	Nouveaunoeud->racine = NULL;
	Nouveaunoeud->nombreNonTerminaux = 0;
	Nouveaunoeud->regleGeneratrice = regle;
    while (Nouveaunoeud->regleGeneratrice->rhs[tailleTexte] != 0)
    {
        tailleTexte++;
    }
	if (tailleTexte != 0)
	{
		for(int i = tailleTexte -1; i > -1; i--)
		{
			if ( Nouveaunoeud->regleGeneratrice->rhs[i] < 0)
			{
				Nouveaunoeud->nombreNonTerminaux ++;
			}
		}
	}

	Nouveaunoeud->fils = malloc(sizeof(noeud*) * Nouveaunoeud->nombreNonTerminaux);

	return Nouveaunoeud;
}

arbre* creeArbre()
{
	arbre* arbre = malloc(sizeof(struct arbre));
	arbre->taille = 0;
	arbre->tailleMax = 1;
	arbre->pile = malloc(sizeof(noeud*));
	return arbre;
}

void ajouteNoeudArbreAnalyse(arbre* arbre,rule* regle)
{
	noeud* nouveauNoeud = creeNoeud(regle);
	if (nouveauNoeud->nombreNonTerminaux == 0) //Ajout sur la pile
	{
		if (arbre->taille + 1  > arbre->tailleMax) // Verification de la taille max de la pile
		{
			arbre->pile = realloc(arbre->pile,sizeof(noeud*) * arbre->taille + 1);
			if(arbre->pile == NULL)
			{
				fprintf(stderr, "Erreur reallocation memoire Arbre.\n");
				exit(EXIT_FAILURE);
			}
			arbre->tailleMax = arbre->taille + 1;
		}
		arbre->taille ++;
		arbre->pile[arbre->taille -1] = nouveauNoeud;
	}
	else //Combinaison de noeud deja sur la pile
	{
		for (size_t i = 1; i <= nouveauNoeud->nombreNonTerminaux; i++)
		{
			//printf("POSITION %d\n",arbre->taille - 1 - i);
			nouveauNoeud->fils[i -1] = arbre->pile[arbre->taille - i];
			arbre->pile[arbre->taille - i] = NULL;
		}
		arbre->taille -= nouveauNoeud->nombreNonTerminaux;
		arbre->taille++;
		//printf("TAILLE : %d\n",arbre->taille - 1);
		arbre->pile[arbre->taille - 1] = nouveauNoeud;

	}
}


void litArbreAnalyse(noeud* noeud)
{
	unsigned int tailleTexte = 0;
	size_t nonTerminalSuivant = 0;
	char aEcrire[256];

	if (noeud != NULL)
	{
		printf("%c(",noeud->regleGeneratrice->lhs);
		sprintf(aEcrire,"%c(",noeud->regleGeneratrice->lhs);
		ecrit_fichier_latex(aEcrire);

		while (noeud->regleGeneratrice->rhs[tailleTexte] != 0)
		{
			tailleTexte++;
		}
		if (tailleTexte != 0)
		{
			if (noeud->nombreNonTerminaux == 0)
			{
				for (size_t i = 0; i < tailleTexte; i++)
				{
					printf("%c",noeud->regleGeneratrice->rhs[i]);
					sprintf(aEcrire,"%c",noeud->regleGeneratrice->rhs[i]);
					ecrit_fichier_latex(aEcrire);
				}
			}
			else
			{
				for (size_t i = 0; i < tailleTexte; i++)
				{
					if (noeud->regleGeneratrice->rhs[i] < 0)
					{
						litArbreAnalyse(noeud->fils[nonTerminalSuivant]);
						nonTerminalSuivant ++;
					}
					else
					{
						printf("%c",noeud->regleGeneratrice->rhs[i]);
						sprintf(aEcrire,"%c",noeud->regleGeneratrice->rhs[i]);
						ecrit_fichier_latex(aEcrire);
					}
				}
			}
		}
		printf(")");
		ecrit_fichier_latex(")");
	}
}

void LibereMemoireArbre(arbre * a)
{
	for (size_t i = 0; i < a->taille; i++)
	{
		LibereMemoireNoeud(a->pile[i]);
	}
}

void LibereMemoireNoeud(noeud* n)
{
	if (n != NULL)
	{
		for (size_t i = 0; i < n->nombreNonTerminaux; i++)
		{
			LibereMemoireNoeud(n->fils[i]);
		}
		free(n->fils);
		free(n->racine);
		free(n);
	}
}
