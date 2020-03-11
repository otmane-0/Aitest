#ifndef ARBRE_H_INCLUDED
#define ARBRE_H_INCLUDED

// arbre.h

typedef int  booleen;
#define faux 0
#define vrai 1

typedef void Objet;

typedef struct noeud
{
    Objet*        reference;
    struct noeud* gauche;
    struct noeud* droite;
    int    factEq;    // facteur d'�quilibre : si l'arbre est �quilibr�
} Noeud;

typedef struct
{
    Noeud* racine;
    char* (*toString) (Objet*);
    int   (*comparer) (Objet*, Objet*);
} Arbre;


// cr�ation de noeuds
Noeud*   cNd                  (Objet* objet, Noeud* Gauche, Noeud* Droite);
Noeud*   cNd                  (Objet* objet);
Noeud*   cF                   (Objet* objet);

// cr�ation d'arbre
void     initArbre            (Arbre* arbre, Noeud* racine,  char* (*toString) (Objet*), int (*comparer) (Objet*, Objet*));
Arbre*   creerArbre           (Noeud* racine, char* (*toString) (Objet*), int (*comparer) (Objet*, Objet*));
Arbre*   creerArbre           (Noeud* racine);
Arbre*   creerArbre           ();

Arbre* creerArbreGene ();
Arbre* creerArbreExp () ;
Arbre* creerArbreQuatreNiveaux () ;
// parcours
void     prefixe              (Arbre* arbre);
void     infixe               (Arbre* arbre);
void     postfixe             (Arbre* arbre);
void enProfondeurIteratif(Arbre* arbre);
void parcoursProfondeurIteratifA(Noeud* racine, char* (*toString) (Objet*), int d, char but[]);
Noeud*   trouverNoeud         (Arbre* arbre, Objet* objet);
void     enLargeur            (Arbre* arbre);
int      taille               (Arbre* arbre);
booleen  estFeuille           (Noeud* arbre);
int      nbFeuilles           (Arbre* arbre);
void     listerFeuilles       (Arbre* arbre);
int      hauteur              (Arbre* arbre);
booleen  egaliteArbre         (Arbre* arbre1, Arbre* arbre2);



#endif // ARBRE_H_INCLUDED
