/* Auteurs: Bjorn LIM CHOU SANG et Thomas ROY */

#include "ecritureLatex.h"


void init_fichier_latex(char const *chaineAnalysee,char *nomGrammaire)
{
	FILE *fichier;
	fichier = fopen("resultat.tex","w");

	if(fichier == NULL)
	{
		printf("Erreur fopen\n");
		exit(-1);
	}

	char texte[650] = "";
	char ligne1[50] = "\\documentclass[12pt]{article}\n";
	char ligne2[50] = "\\usepackage[utf8]{inputenc}\n";
	char ligne3[50] = "\\usepackage[francais]{babel}\n";
	char ligne4[50] = "\\usepackage{supertabular}\n";
	char ligne5[150] = "\\title{Résultat de l'execution de la chaîne de caractères \n"; 
	strcat(ligne5,chaineAnalysee);
	strcat(ligne5," pour la grammaire ");
	strcat(ligne5,nomGrammaire);
	strcat(ligne5,"}");
	char ligne6[100] = "\\author{Bjorn LIM CHOU SANG \\and Thomas ROY}\n"; 
	char ligne7[100] = "\\date{}\n"; 
	char ligne8[50] = "\\begin{document}\n"; 
	char ligne9[50] = "\\maketitle\n"; 

	strcat(texte,ligne1);
	strcat(texte,ligne2);
	strcat(texte,ligne3);
	strcat(texte,ligne4);
	strcat(texte,ligne5);
	strcat(texte,ligne6);
	strcat(texte,ligne7);
	strcat(texte,ligne8);
	strcat(texte,ligne9);

	if(fputs(texte, fichier) == EOF)
	{
		printf("Erreur fputs");
		exit(-1);
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
		exit(-1);
	}

	if(fputs(texte, fichier) == EOF)
	{
		printf("Erreur fputs");
		exit(-1);
	}

	fclose(fichier);
}



void ouvreFichierLatex()
{
	char veutOuvrirFichierLatex;
	printf("Voulez-vous voir le résultat sur un fichier latex ? package evince et texlive-full requis\no=Oui n=Non: ");
	scanf("%c", &veutOuvrirFichierLatex);

	if(veutOuvrirFichierLatex == 'o'){
		FILE *fichier;
		fichier = fopen("ecraseMsgSystem.txt","w");

		if(fichier == NULL)
		{
			printf("Erreur fopen\n");
			exit(-1);
		}

		system("pdflatex -synctex=1 -interaction=nonstopmode resultat.tex > ecraseMsgSystem.txt");
		system("evince resultat.pdf");

		fclose(fichier);
	}
}



