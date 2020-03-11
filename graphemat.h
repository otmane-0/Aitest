#ifndef GRAPHEMAT_H_INCLUDED
#define GRAPHEMAT_H_INCLUDED
#define NOMBRE_TRAJETS    73
#define NOMBRE_VILLES     73 //C'est le nombre de villes +1 car on doit ajouter le sommet initial a la finS
#define TAUX_MUTATION    0.3
#define NOMBRE_ENTREE 4
#define NOMBRE_ENTREE_MULTI 2
#define NOMBRE_POIDS 2
#define NOMBRE_POIDS_MULTI 10
#define NOMBRE_ACTIVATION 7
#define MU 0.1
#define TETA 0.2
#define SOMMET_INITIAL 0
#define debug 0

#include <limits.h>

typedef int  booleen;
#define faux 0
#define vrai 1
typedef char NomSom[20];  // nom d'un sommet
#define INFINI INT_MAX
#define tailleMax 100
typedef float* Matrice;
typedef struct taquin {
  int*          caseTaquin;
  int      n;       // nombre de sommets
  int      nMax;    // nombre max de sommets
  booleen  value;   // graphe valué ou non

  Matrice  element; // existence d'un arc (i, j)
  Matrice  valeur;  // cout de l'arc (i, j)
  booleen* marque;  // sommet marqué (visité) ou non
} Taquin;
typedef struct {
	int* numSommet;
	int* cout;
}listeTemp;

typedef struct {
  int      n;       // nombre de sommets
  int      nMax;    // nombre max de sommets
  booleen  value;   // graphe valué ou non
  NomSom*  nomS;
  int* caseTaquin;
  Matrice  element; // existence d'un arc (i, j)
  Matrice  valeur;  // cout de l'arc (i, j)
  booleen* marque;  // sommet marqué (visité) ou non

} GrapheMat;
GrapheMat* creerGrapheMat     (int nMax, int value);
void       detruireGraphe     (GrapheMat* graphe);
void       ajouterUnSommet    (GrapheMat* graphe, NomSom nom);
void       ajouterUnArc       (GrapheMat* graphe, NomSom somD, NomSom somA, int cout);
void       ajouterUnArcBis       (GrapheMat* graphe, NomSom somD, int somA, float cout);
void       parcoursPlusProcheVoisin     (GrapheMat* graphe);
void       parcoursDeuxOptV2             (GrapheMat* graphe);
void       parcoursRecuitSimule             (GrapheMat* graphe);
void       parcoursDeuxOptV1              (GrapheMat* graphe);
void       ecrireGraphe       (GrapheMat* graphe);
void perceptron();
void multiCouches();

void       parcoursProfond    (GrapheMat* graphe);
void       parcoursLargeur (GrapheMat* graphe);
void       parcoursProfondeurIteratif(GrapheMat* graphe);
void       parcoursCoutUniforme(GrapheMat* graphe);
void       parcoursGenetique(GrapheMat* graphe);
void       parcoursAEtoile(GrapheMat* graphe, int* but);
void       floyd              (GrapheMat* graphe);



#endif // GRAPHEMAT_H_INCLUDED
