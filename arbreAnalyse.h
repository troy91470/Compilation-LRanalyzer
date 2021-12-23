//Arbre inversé
//Garder en mémoire la liste des noeuds et leur niveu
//Ne considérer uniquement les noeuds qui n'ont pas de de racine
//Regarder par la droite quand on combine car sinon problème de cohérence. Voir comme une pile.
//Exemple : 0E1+4E7X5E -> E+ExE(pile trouvé avec le test3 et le mot a+a+axa) si on combine par la droite on combine les E les plus vieux ensemble.
// Alors que les E les plus récent sont surement ceux que l'on interagir.

#include "LRGrammar.h"
#include "ecritureLatex.h"

typedef struct noeud{
	struct noeud* racine;
	rule* regleGeneratrice;
	struct noeud** fils;
	unsigned int nombreNonTerminaux;
} noeud;

typedef struct arbre{
	noeud** pile;
	int tailleMax;
	int taille;
} arbre;


noeud* creeNoeud(rule*);
arbre* creeArbre();
void litArbreAnalyse(noeud* noeud);
void ajouteNoeudArbreAnalyse(arbre* arbre,rule* regle);
void LibereMemoireArbre(arbre *);
void LibereMemoireNoeud(noeud* n);
//void ajouteRuleArbreAnalyse(noeud* noeud, rule rule);
//void ajouteNoeudArbreAnalyse(noeud** pile,char racine, rule regleGeneratrice);

