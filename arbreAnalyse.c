#include "arbreAnalyse.h"


noeud* creeNoeud()
{
	noeud *noeud = malloc(sizeof(*noeud));

	if(noeud == NULL)
	{
		fprintf(stderr, "Erreur allocation memoire.\n");
		exit(EXIT_FAILURE);
	} 

	noeud->racine = NULL;
	noeud->regleGeneratrice = NULL;
	noeud->fils = NULL;

	return noeud;
}


void litArbreAnalyse(noeud* noeud)
{

}



void ajouteRuleArbreAnalyse(noeud* noeud, rule rule)
{
	int j=0;

	while(rule.rhs[j]!='\0'){
		if(rule.rhs[j]<=0){
			ajouteNoeudArbreAnalyse(noeud, rule.lhs, rule.rhs[j]);
      		}
      		j++;
    	}	
}


void ajouteNoeudArbreAnalyse(noeud* noeud, char racine, char regleGeneratrice)
{
	noeud* nouveauNoeud = creeNoeud();

	nouveauNoeud->racine = racine;
	nouveauNoeud->regleGeneratrice = regleGeneratrice;
	nouveauNoeud->fils = noeud->racine ????????? //un bail du genre
}

