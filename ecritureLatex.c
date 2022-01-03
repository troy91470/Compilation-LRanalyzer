/* Auteurs: Bjorn LIM CHOU SANG et Thomas ROY */

#include "ecritureLatex.h"




void nettoie_fichier_latex()
{
	FILE *fichier;
	fichier = fopen("resultat.tex","w");

	if(fichier == NULL)
	{
		printf("Erreur fopen\n");
	}

	fclose(fichier);
}


void ecrit_fichier_latex(char *texte)
{
	FILE *fichier;
	fichier = fopen("resultat.tex","a");

	if(fichier == NULL)
	{
		printf("Erreur fopen\n");
	}

	if(fputs(texte, fichier) == EOF)
	{
		printf("Erreur fputs");
	}

	fclose(fichier);
}
