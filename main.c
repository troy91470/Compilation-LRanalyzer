#include "automatePile.h"

int main(int argc, char const *argv[])
{

	nettoie_fichier_latex();

	char debutFichierLatex[100] = "";
	char ligne1[50] = "\\documentclass[12pt]{article}\n";
	char ligne2[50] = "\\begin{document}\n"; 
	strcat(debutFichierLatex,ligne1);
	strcat(debutFichierLatex,ligne2);
	ecrit_fichier_latex(debutFichierLatex);


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
	analyseflot(argv[2],file.G,file.t);

	ecrit_fichier_latex("\\end{document}\n");
	system("pdflatex -synctex=1 -interaction=nonstopmode resultat.tex");
	system("evince resultat.pdf");

	return 0;
}
