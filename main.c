/* Auteurs: Bjorn LIM CHOU SANG et Thomas ROY */

#include "automatePile.h"

int main(int argc, char const *argv[])
{
	char nomGrammaire[2];
	nomGrammaire[0] = read_file(argv[1]).G.start;
	init_fichier_latex(argv[2], nomGrammaire);

	file_read file;
	if (argc != 3)
	{
		printf("Usage : ./a.out table texte\n");
		exit(-1);
	}
	file = read_file(argv[1]);

	analyseflot(argv[2],file.G,file.t);

	ecrit_fichier_latex("\\end{document}\n");
	ouvreFichierLatex();	

	return 0;
}
