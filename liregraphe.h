#ifndef LIREGRAPHE_H_INCLUDED
#define LIREGRAPHE_H_INCLUDED



// ignorer les blancs
void lireBlancs (FILE* fe);

// lire un nom de sommet en ignorant les espaces
void lireUnMot (FILE* fe, char* chaine);

// fournir un pointeur sur un graphe construit
// à partir d'un fichier fe de données
GrapheMat* lireGraphe (FILE* fe, int nMaxSom);
GrapheMat* lireGraphe2 (FILE* fe, int nMaxSom);

#endif // LIREGRAPHE_H_INCLUDED
