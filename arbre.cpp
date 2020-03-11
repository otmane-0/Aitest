#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "arbre.h"
#include "liste.h"
#include <time.h>
static int compteurVisite=0;

static bool trouveA = false;
static char* toChar (Objet* objet)
{
    return (char*) objet;
}

static int comparerCar (Objet* objet1, Objet* objet2)
{
    return strcmp ((char*)objet1,(char*)objet2);
}

booleen arbreVide (Arbre* arbre)
{
    return arbre->racine == NULL;
}


// création d'un noeud interne contenant objet,
// gauche comme pointeur de SAG, et droite comme pointeur de SAD
Noeud* cNd (Objet* objet, Noeud* gauche, Noeud* droite)
{
    Noeud* nouveau     = new Noeud();
    nouveau->reference = objet;
    nouveau->gauche    = gauche;
    nouveau->droite    = droite;
    return nouveau;
}

// création d'un noeud feuille contenant objet
Noeud* cNd (Objet* objet)
{
    return cNd (objet, NULL, NULL);
}
// création d'une feuille contenant objet
Noeud* cF (Objet* objet)
{
    return cNd (objet, NULL, NULL);
}

void initArbre (Arbre* arbre, Noeud* racine,
                char* (*toString) (Objet*), int (*comparer) (Objet*, Objet*))
{
    arbre->racine   = racine;
    arbre->toString = toString;
    arbre->comparer = comparer;
}

Arbre* creerArbre (Noeud* racine, char* (*toString) (Objet*),
                   int (*comparer) (Objet*, Objet*))
{
    Arbre* arbre = new Arbre();
    initArbre (arbre, racine, toString, comparer);
    return arbre;
}

Arbre* creerArbre (Noeud* racine)
{
    return creerArbre (racine, toChar, comparerCar);
}

Arbre* creerArbre ()
{
    return creerArbre (NULL, toChar, comparerCar);  // valeurs par défaut
}

Noeud* cF (char* message)
{
    return cF ( (Objet*) message);
}

Noeud* cNd (char* message, Noeud* gauche, Noeud* droite)
{
    return cNd ( (Objet*) message, gauche, droite);
}

// créer un arbre binaire généalogique
Arbre* creerArbreGene ()
{
    Noeud* racine =
        cNd ( "Samir",
              cNd ( "Kamal",
                    cNd ( "Yassine",
                          NULL,
                          cNd ( "Hind", NULL, cF ("Yasmine") )
                        ),
                    cNd ( "Sarah", cF ("Karim"), NULL)
                  ),
              NULL
            );
    return creerArbre (racine);
}

// créer un arbre binaire (expression arithmétique)
Arbre* creerArbreExp ()
{
    Noeud* racine =
        cNd ( "-",
              cNd ( "*",
                    cNd ("+", cF ("a"), cF ("b") ),
                    cNd ("-", cF ("c"), cF ("d") )
                  ),
              cF  ("e")
            );
    return creerArbre (racine);
}
Arbre* creerArbreQuatreNiveaux ()
{
    Noeud* racine =
        cNd ( "S0",
              cNd ( "S1",
                    cNd ("S3", cF ("S7"), cF ("S8") ),
                    cNd ("S4", cF ("S9"), cF ("S10") )
                  ),
              cNd ( "S2",
                    cNd ("S5", cF ("S11"), cF ("S12") ),
                    cNd ("S6", cF ("S13"), cF ("S14") )
                  )
            );
    return creerArbre (racine);
}
// toString fournit la chaîne de caractères à écrire pour un objet donné
static void prefixe (Noeud* racine, char* (*toString) (Objet*),char but[])
{

    if(!trouveA){
    if (racine != NULL)
    {
        printf ("->%s", toString (racine->reference));
        compteurVisite++;
        if(strcmp((char*)racine->reference,but)==0){

                printf("(Noeud but) ");
                trouveA=true;

             }

        prefixe (racine->gauche, toString,but);

        prefixe (racine->droite, toString,but);

    }
}}
void enProfondeurIteratif(Arbre* arbre){

clock_t begin, end;
double time_spent;
 char str[20];
 int niveau;
 printf("Entrez le noeud but : (le noeud but designe par le prof est S14) ");
 scanf("%s", str);
  printf("Entrez le niveau maximal ");
 scanf("%d", &niveau);

Liste* li = creerListe();
printf("Chemin suivi par le parcous :   ");
begin = clock();
  int l=0;
    for ( l=0; l<niveau; l++)
    {



        parcoursProfondeurIteratifA(arbre->racine,arbre->toString,l,str);


    }

 if(!trouveA){
        trouveA=false;
        printf("\nLe noeud %s est INTROUVABLE",str);
    }
end = clock();
time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
 printf("\nLe temps pris :  %f",time_spent);
 printf("\nNoeuds developpes : %d",compteurVisite);
compteurVisite=0;
}

void parcoursProfondeurIteratifA(Noeud* racine, char* (*toString) (Objet*), int d, char but[])
{
    if(!trouveA){
compteurVisite++;
     if(strcmp((char*)racine->reference,but)==0){

                printf("->%s (Noeud but) ",but);
               trouveA=true;
             }

       else if(d==0){
      printf ("->%s ", toString (racine->reference));


     }
        else {
            if (d>0){

  printf ("->%s ", toString (racine->reference));
            parcoursProfondeurIteratifA(racine->gauche,  toString, d-1,but);
           parcoursProfondeurIteratifA(racine->droite,  toString, d-1,but);

        }

    }
     }}

// parcours préfixé de l'arbre
void prefixe (Arbre* arbre)
{
clock_t begin, end;
double time_spent;
char str[20];
printf("Entrez le noeud but : (le dernier designe par le prof est S14 qui est le dernier) ");
scanf("%s", str);
printf("Chemin suivi par le parcous :   ");
begin = clock();
prefixe (arbre->racine, arbre->toString,str);


         if (trouveA){
                trouveA=false;


       }
    else
         printf("\n\nNoeud %s INTROUVABLE",str);
end = clock();
time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
 printf("\nLe temps pris :  %f",time_spent);
         printf("\nNoeud developpes : %d",compteurVisite);
compteurVisite=0;
}
// toString fournit la chaîne de caractères à écrire pour un objet
static void infixe (Noeud* racine, char* (*toString) (Objet*))
{
    if (racine != NULL)
    {
        infixe (racine->gauche, toString);
        printf ("%s ", toString (racine->reference));
        infixe (racine->droite, toString);
    }
}

// parcours infixé de l'arbre
void infixe (Arbre* arbre)
{
    infixe (arbre->racine, arbre->toString);
}

// toString fournit la chaîne de caractères à écrire pour un objet
static void postfixe (Noeud* racine, char* (*toString) (Objet*))
{
    if (racine != NULL)
    {
        postfixe (racine->gauche, toString);
        postfixe (racine->droite, toString);
        printf ("%s ", toString (racine->reference));
    }
}

// parcours postfixé de l'arbre
void postfixe (Arbre* arbre)
{
    postfixe (arbre->racine, arbre->toString);
}


static Noeud* trouverNoeud (Noeud* racine, Objet* objet,
                            int (*comparer) (Objet*, Objet*))
{
    Noeud* pNom;
    if (racine == NULL)
    {
        pNom = NULL;
    }
    else if (comparer (racine->reference, objet) == 0)
    {
        pNom = racine;
    }
    else
    {
        pNom = trouverNoeud (racine->gauche, objet, comparer);
        if (pNom == NULL) pNom = trouverNoeud (racine->droite, objet,
                                                   comparer);
    }
    return pNom;
}

// recherche le noeud objet dans l'arbre
Noeud* trouverNoeud (Arbre* arbre, Objet* objet)
{
    return trouverNoeud (arbre->racine, objet, arbre->comparer);
}

static void enLargeur (Noeud* racine, char* (*toString) (Objet*), char but[])
{
    Liste* li = creerListe();
    insererEnFinDeListe (li, racine);
    while (!listeVide (li) )
    {
        Noeud* extrait = (Noeud*) extraireEnTeteDeListe (li);
         compteurVisite++;
          if(strcmp((char*)extrait->reference,but)==0){

                printf("->%s (Noeud but) ",but);
                return;
             }
 printf ("->%s", toString (extrait->reference));
        if (extrait->gauche != NULL)
            insererEnFinDeListe (li,
                    extrait->gauche);
        if (extrait->droite != NULL)
        insererEnFinDeListe (li,
                    extrait->droite);
    }
    printf("\nLe noeud but %s est INTROUVABLE. ",but);
}

// parcours en largeur de l'arbre
void enLargeur (Arbre* arbre)
{
clock_t begin, end;
double time_spent;


         char str[20];
    printf("Entrez le noeud but : (le dernier designe par le prof est S14 qui est le dernier) ");
     scanf("%s", str);
     printf("Chemin suivi par le parcous :   ");
begin = clock();
enLargeur (arbre->racine, arbre->toString,str);

end = clock();
time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
 printf("\nLe temps pris :  %f",time_spent);
  printf("\nNoeuds visites : %d",compteurVisite);
compteurVisite=0;

}

int taille (Noeud* racine)
{
    if (racine == NULL)
    {
        return 0;
    }
    else
    {
        return 1 + taille (racine->gauche) + taille (racine->droite);
    }
}

// nombre de noeuds de l'arbre
int taille (Arbre* arbre)
{
    return taille (arbre->racine);
}

// Le noeud racine est-il une feuille ?
booleen estFeuille (Noeud* racine)
{
    return (racine->gauche==NULL) && (racine->droite==NULL);
}

static int nbFeuilles (Noeud* racine)
{
    if (racine == NULL)
    {
        return 0;
    }
    else if ( estFeuille (racine) )
    {
        return 1;
    }
    else
    {
        return nbFeuilles (racine->gauche) + nbFeuilles (racine->droite);
    }
}

// fournir le nombre de feuilles de l'arbre binaire
int nbFeuilles (Arbre* arbre)
{
    return nbFeuilles (arbre->racine);
}

static void listerFeuilles (Noeud* racine, char* (*toString) (Objet*))
{
    if (racine != NULL)
    {
        if (estFeuille (racine))
        {
            printf ("%s ", toString (racine->reference));
        }
        else
        {
            listerFeuilles (racine->gauche, toString);
            listerFeuilles (racine->droite, toString);
        }
    }
}

// lister les feuilles de l'arbre binaire
void listerFeuilles (Arbre* arbre)
{
    listerFeuilles (arbre->racine, arbre->toString);
}

int max (int a, int b)
{
    return (a<b)?b:a;
}

static int hauteur (Noeud* racine)
{
    if (racine == NULL)
    {
        return 0;
    }
    else
    {
        return 1 + max (hauteur (racine->gauche),
                        hauteur (racine->droite) );
    }
}

// hauteur de l'arbre
int hauteur (Arbre* arbre)
{
    return hauteur (arbre->racine);
}

// égalité de deux arbres
static booleen egaliteArbre (Noeud* racine1, Noeud* racine2,
                             int (*comparer) (Objet*, Objet*))
{
    booleen resu = faux;
    if ( (racine1==NULL) && (racine2==NULL) )
    {
        resu = vrai;
    }
    else if ( (racine1!=NULL) && (racine2!=NULL) )
    {
        if (comparer (racine1->reference, racine2->reference) == 0)
        {
            if (egaliteArbre (racine1->gauche, racine2->gauche, comparer) )
            {
                resu = egaliteArbre (racine1->droite, racine2->droite, comparer);
            }
        }
    }
    return resu;
}

booleen egaliteArbre (Arbre* arbre1, Arbre* arbre2)
{
    return egaliteArbre (arbre1->racine, arbre2->racine, arbre1->comparer);
}
