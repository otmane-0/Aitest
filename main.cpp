
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "graphemat.h"
#include "arbre.h"
#include "taquin.h"
#include "liregraphe.h"

typedef GrapheMat Graphe;

void afficherTableau();
int menu () {

    printf ("\n\nGRAPHES avec matrices\n\n");

    printf ("0  - Fin du programme\n");
    printf ("1  - Creation a partir d un fichier\n");
    printf ("\n");
    printf ("2  - Initialisation d'un graphe vide\n");
    printf ("3  - Ajout d'un sommet\n");
    printf ("4  - Ajout d'un arc\n");
    printf ("\n");
    printf ("5  - Liste des sommets et des arcs\n");
    printf ("6  - Destruction du graphe\n");
    printf ("8  - Floyd \n");
    printf ("\n");
    printf ("8  - Parcours en profondeur d'un graphe\n");
    printf ("9  - Parcours en largeur d'un graphe \n");
    printf ("10 - Parcours profondeur iteratif d'un graphe  \n");
    printf ("11 - Parcours cout uniforme d'un graphe \n");
    printf ("\n");
    printf ("\n");
    printf ("12 - Creation d'un arbre 4 niveaux\n");
    printf ("13 - Parcours en profondeur d'une arbre\n");
    printf ("14 - Parcours en largeur d'une arbre \n");
    printf ("15 - Parcours profondeur iteratif d'une arbre  \n");

    printf ("16 - Afficher Tableau  \n");

    printf ("17- Plus Proche voisin  \n");
    printf ("18- 2OPTv1 \n");
    printf("19- 2OPTv2 \n");
    printf("20- Recuit Simule \n");
    printf("21- Parcours Genetique \n");
    printf("22- Perceptron \n");
    printf("23- Multicouches \n");
    printf("24- All \n");
    printf ("Votre choix ? ");
    int cod; scanf ("%d", &cod); getchar();
    printf ("\n");
    return cod;
}
int main (void) {
    Graphe* graphe;
    Arbre* arbre;
    booleen fini = false;
    while (!fini) {
        switch ( menu() ) {
            case 0:
                fini = true;
                break;
            case 1: {  // cr�ation � partir d'un fichier
                printf ("Nom du fichier contenant le graphe ? ");
                char nomFe [50];
                scanf  ("%s", nomFe);
                //strcpy (nomFe, "graphe.txt");
                //char* nom = strcat("C://Users/User/CLionProjects/Aitest",nomFe);
                FILE* fe = fopen ("C:\\Users\\User\\CLionProjects\\Aitest\\Testos.txt", "r");
                if (fe == NULL) {
                    perror (nomFe);
                } else {
                    graphe = lireGraphe (fe, 75); // 20 sommets maximum
                    fclose (fe);
                }
            } break;
            case 2: {             // cr�ation d�un graphe vide
                printf ("Nombre maximum de sommets ? ");
                int nMaxSom; scanf  ("%d", &nMaxSom);
                printf ("0) non valu�; 1) graphe valu� ? ");
                int value; scanf ("%d", &value);

                graphe = creerGrapheMat (nMaxSom, value);

            } break;
            case 3: {  // ajouter un sommet
                printf ("Nom du sommet � ins�rer ? ");
                NomSom somD; scanf  ("%s", somD);
                ajouterUnSommet (graphe, somD);
            } break;
            case 4: {  // ajouter un arc
                printf ("Nom du sommet de d�part ? ");
                NomSom somD; scanf  ("%s", somD);
                printf ("Nom du sommet d'arriv�e ? ");
                NomSom somA; scanf  ("%s", somA);
                int cout;
                if (graphe->value) {
                    printf ("Cout de la relation ? ");
                    scanf ("%d", &cout);
                } else {
                    cout = 0;
                }
                ajouterUnArc (graphe, somD, somA, cout);
            } break;
            case 5:
                ecrireGraphe (graphe);
                break;
            case 6:
                detruireGraphe (graphe);
                break;

            case 7:
                if (graphe->value) {
                    printf ("\nLes plus courts chemins\n\n");
                    floyd (graphe);
                } else {
                    printf ("Graphe non valu�\n");
                }
                break;
            case 8:
                parcoursProfond (graphe);
                break;
            case 9:
                parcoursLargeur(graphe);
                break;

            case 10:
                parcoursProfondeurIteratif(graphe);
                break;
            case 11:
                parcoursCoutUniforme(graphe);
                break;
            case 12:
                arbre=creerArbreQuatreNiveaux();
                break;
            case 13:

                prefixe(arbre);

                break;
            case 14:
                enLargeur(arbre);
                break;
            case 15:
                enProfondeurIteratif(arbre);
                break;
            case 16:
                afficherTableau();
                invoquerTaquin();
                break;
            case 17:
                parcoursPlusProcheVoisin(graphe);

                break;
            case 18:
                parcoursDeuxOptV1(graphe);

                break;
            case 19:
                parcoursDeuxOptV2(graphe);

                break;
            case 20:
                parcoursRecuitSimule(graphe);

                break;
            case 21:
                parcoursGenetique(graphe);

                break;
            case 22:
                perceptron();

                break;
            case 23:
                multiCouches();
                break;
            case 24:
                parcoursPlusProcheVoisin(graphe);
                printf("\n\n\n");
                parcoursDeuxOptV1(graphe);
                printf("\n\n\n");
                parcoursDeuxOptV2(graphe);
                printf("\n\n\n");
                parcoursRecuitSimule(graphe);
                printf("\n\n\n");
                parcoursGenetique(graphe);
                printf("\n\n\n");
                perceptron();
                printf("\n\n\n");
                multiCouches();
                printf("\n\n\n");
                break;
        }
        // switch
        if (!fini) {
            printf ("\n\nTaper Return pour continuer\n");
            getchar();
        }
    }

    return 0;
}
void afficherTableau(){
    printf("          Profondeur       Largeur       Uniforme        Iteratif");
    printf(" \n");
    printf(" %c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c   ",201, 205, 205,205,205,205, 205, 203, 205, 205,205,205,205, 205, 203,  205, 205,205,205,205, 205, 203, 205, 205,205,205,205, 205, 203,205,205, 205, 205,205,205,205, 205, 203,205, 205,205,205,205, 205, 203,205, 205,205,205,205, 205, 203,205, 205,205,205,205, 205, 203,205, 205,205,205,205, 205,187);

    printf(" \n");

    printf(" %cXXXXXX%c Temps%c ND   %c Temps%c   ND   %cTemps %c  ND  %c Temps%c ND   %c ",   186, 186, 186,   186, 186, 186,   186, 186, 186,   186);
    printf(" \n");
    printf(" %c      %c      %c      %c      %c        %c      %c      %c      %c      %c ",   186, 186, 186,   186, 186, 186,   186, 186, 186,   186);
    printf(" \n");
    printf(" %c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c   ",204, 205, 205,205,205,205, 205, 206, 205, 205,205,205,205, 205, 206,  205, 205,205,205,205, 205, 206, 205, 205,205,205,205, 205, 206,205,205, 205, 205,205,205,205, 205, 206,205, 205,205,205,205, 205, 206,205, 205,205,205,205, 205, 206,205, 205,205,205,205, 205, 206,205, 205,205,205,205, 205,185);

    printf(" \n");
    printf(" %c Arbre%c 0.003%c  15  %c 0.005%c   15   %c      %c      %c 0.006%c  26  %c ",   186, 186, 186,   186, 186, 186,   186, 186, 186,   186);
    printf(" \n");
    printf(" %c      %c      %c      %c      %c        %c      %c      %c      %c      %c ",   186, 186, 186,   186, 186, 186,   186, 186, 186,   186);
    printf(" \n");
    printf(" %c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c   ",204, 205, 205,205,205,205, 205, 206, 205, 205,205,205,205, 205, 206,  205, 205,205,205,205, 205, 206, 205, 205,205,205,205, 205, 206,205,205, 205, 205,205,205,205, 205, 206,205, 205,205,205,205, 205, 206,205, 205,205,205,205, 205, 206,205, 205,205,205,205, 205, 206,205, 205,205,205,205, 205,185);

    printf(" \n");
    printf(" %cGraphe%c 0.001%c  3   %c 0.003%c   8    %c 0.003%c   9  %c 0.003%c  16  %c ",   186, 186, 186,   186, 186, 186,   186, 186, 186,   186);
    printf(" \n");
    printf(" %c      %c      %c      %c      %c        %c      %c      %c      %c      %c ",   186, 186, 186,   186, 186, 186,   186, 186, 186,   186);
    printf(" \n");
    printf(" %c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c   ",200, 205, 205,205,205,205, 205, 202, 205, 205,205,205,205, 205, 202,  205, 205,205,205,205, 205, 202, 205, 205,205,205,205, 205, 202,205,205, 205, 205,205,205,205, 205, 202,205, 205,205,205,205, 205, 202,205, 205,205,205,205, 205, 202,205, 205,205,205,205, 205, 202,205, 205,205,205,205, 205,188);
}
