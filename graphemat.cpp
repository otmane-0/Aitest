#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "graphemat.h"
#include "liste.h"
#include <time.h>
#include <math.h>
booleen  grapheDetruit = vrai;
static int d=0;
static int niveau=0;
static bool trouve=false;
static int compteurVisiteG=0;
static float valeur=0;

typedef char NomS[50];

static NomS* path = (NomS*) malloc((sizeof(NomS))*100);
static int* cout = (int*)malloc(sizeof(int)*100) ;

static int nbEltTab=0;
static bool trouveS = false;
static float coutTotal =0;
// remise à zéro du tableau de marquage
static void razMarque (GrapheMat* graphe)
{

    for (int i=0; i<graphe->n; i++) graphe->marque [i] = faux;
}

GrapheMat* creerGrapheMat (int nMax, int value)
{
    // allocation de graphe
    GrapheMat* graphe  = (GrapheMat*) malloc (sizeof (GrapheMat));
    graphe->n       = 0;
    graphe->nMax    = nMax;
    graphe->value   = value; // value : vrai si le graphe est valué
    graphe->nomS    = (NomSom*)  malloc (sizeof(NomSom)  *nMax);

    graphe->marque  = (booleen*) malloc (sizeof(booleen) *nMax);
    graphe->element = (float*)     malloc (sizeof(float)*nMax*nMax);
    graphe->valeur  = (float*)     malloc (sizeof(float)*nMax*nMax);
    // initialisation par défaut
    for (int i=0; i<nMax; i++)
    {
        for (int j=0; j<nMax; j++)
        {
            graphe->element [i*nMax+j] = faux;
            graphe->valeur  [i*nMax+j] = INFINI;
        }
    }
    razMarque (graphe);
    grapheDetruit = faux;
    return graphe;
}

void shuffle(int array[], int n)
{
    if (n > 1)
    {
        int i;
        for (i = 1; i < n - 1; i++)
        {
          size_t j = i + rand() / (RAND_MAX / (n - i) + 1);
          int t = array[j];
          array[j] = array[i];
          array[i] = t;
        }
    }
}
// désallocation d'un graphe
void detruireGraphe (GrapheMat* graphe)
{
    free (graphe->nomS);

    free (graphe->marque);
    free (graphe->element);
    free (graphe->valeur);
    free (graphe);
    grapheDetruit = vrai;
}

static int rang (GrapheMat* graphe, NomSom nom)
{
    int      i      = 0;
    booleen  trouve = faux;
    while ( (i<graphe->n) && !trouve)
    {
        trouve = strcmp (graphe->nomS [i], nom) == 0;
        if (!trouve) i++;
    }
    return trouve ? i : -1;
}

void ajouterUnSommet (GrapheMat* graphe, NomSom nom)
{
    if (rang (graphe, nom) == -1)
    {
        if (graphe->n < graphe->nMax)
        {
            strcpy (graphe->nomS [graphe->n++], nom);
        }
        else
        {
            printf ("\nNombre de sommets > %d\n", graphe->nMax);
        }
    }
    else
    {
        printf ("\n%s déjà défini\n", nom);
    }
}

void ajouterUnArc (GrapheMat* graphe, NomSom somD, NomSom somA, int cout)
{
    int nMax = graphe->nMax;
    int rd = rang (graphe, somD);
    int rg = rang (graphe, somA);
    graphe->element [rd*nMax+rg] = vrai;
    graphe->valeur  [rd*nMax+rg] = cout;
}
void ajouterUnArcBis (GrapheMat* graphe, NomSom somD, int rg, float cout)
{
    int nMax = graphe->nMax;
    int rd = rang (graphe, somD);

    graphe->element [rd*nMax+rg] = vrai;
    graphe->valeur  [rd*nMax+rg] = cout;
}

void ecrireGraphe (GrapheMat* graphe)
{
    if (grapheDetruit == vrai)
    {
        printf ("Le graphe a ete detruit ou n'est pas encore cree\n");
    }
    else
    {
        int nMax = graphe->nMax;
        for (int i=0; i<graphe->n; i++) printf ("%s ", graphe->nomS[i]);
        printf (";\n");
        for (int i=0; i<graphe->n; i++)
        {
            printf ("\n%s : ", graphe->nomS[i]);
            for (int j=0; j<graphe->n; j++)
            {
                if (graphe->element [i*nMax+j] == vrai)
                {
                    printf ("%s ", graphe->nomS[j]) ;
                    if (graphe->value)
                    {
                        printf (" (%f) ", graphe->valeur [i*nMax+j] );
                    }
                }
            }
            printf (";");
        }
    }
}

static void profondeur (GrapheMat* graphe, int numSommet, char but[])
{

    //Ce if est uniquement pour sortir de la boucle et ne pas afficher les autres noeuds
    if(!trouveS){
    int nMax = graphe->nMax;
    graphe->marque [numSommet] = vrai;
    printf ("->%s", graphe->nomS [numSommet]);
    compteurVisiteG++;
    for (int i=0; i<graphe->n; i++)
    {
        if ( (graphe->element [numSommet*nMax+i] == vrai)
                && !graphe->marque [i]&&!trouve )
        {
             if(strcmp(graphe->nomS [i],but)==0){

                printf("->%s (Noeud but) ",but);
                trouveS=true;

             }
            profondeur (graphe, i,but);

        }
    }
}}

void parcoursProfond (GrapheMat* graphe)
{ clock_t begin, end;
double time_spent;
    razMarque (graphe);
    char str[20];
    printf("Entrez le sommet but : (le sommet but designe par le prof est S7) ");
    scanf("%s", str);
    printf("Chemin suivi par le parcous :   ");



    begin = clock();
/* here, do your time-consuming job */

    for (int i=0; i<graphe->n; i++)
    {
        if (!graphe->marque [i]) profondeur (graphe, i,str);
    }
    if(!trouveS){

        printf("\nLe noeud %s est INTROUVABLE",str);
    }
    end = clock();
    time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
    printf("\nLe temps pris :  %f",time_spent);
    printf("\nNoeuds visites : %d",compteurVisiteG);
    compteurVisiteG=0;
}

static void coutUniforme (GrapheMat* graphe, Liste* li, int numSommet, int but)
{


for(int j=0;j<100;j++){
    strcpy (*(path+j),"");}

    strcpy (*(path+numSommet),graphe->nomS[numSommet]);
    int nMax = graphe->nMax;
    Element* extraite=NULL;

    insererEnFinDeListe (li,graphe->nomS[numSommet],cout+numSommet);
    graphe->marque [numSommet]=true;

    while (!listeVide (li) && !trouve )
    {

    extraite = (Element*) extraireEnTeteDeListe(li);
  compteurVisiteG++;
    numSommet = rang (graphe,(char*)extraite);



    if(numSommet==but){
            trouveS=true;
return;
}

    for (int i=0; i<graphe->n; i++)
    {

         if ( (graphe->element [numSommet*nMax+i] == vrai)
                && !graphe->marque [i] )
        {



strcat (*(path+i),*(path+numSommet));
strcat (*(path+i),"->");
strcat (*(path+i),graphe->nomS[i]);



           *(cout+i)=graphe->valeur[numSommet*nMax+i]+*(cout+numSommet );

           insererEnOrdre(li,graphe->nomS[i],cout+i);

           graphe->marque[i] = vrai;

        }
        else{
                bool trouvee = chercherUnObjetBis(li,graphe->nomS[i]);
            if((graphe->element [numSommet*nMax+i] == vrai)&& trouvee &&*(cout+i)>graphe->valeur[numSommet*nMax+i]+*(cout+numSommet )){
             *(cout+i)=graphe->valeur[numSommet*nMax+i]+*(cout+numSommet );
             strcpy (*(path+i),"");
        strcat (*(path+i),*(path+numSommet));
strcat (*(path+i),"->");
strcat (*(path+i),graphe->nomS[i]);

    }}
}

}
}
void parcoursCoutUniforme (GrapheMat* graphe )
{
clock_t begin, end;
double time_spent;


 int but;
    printf("Entrez le numero du sommet but : (le numero du sommet but designe par le prof est 7) ");
     scanf("%d", &but);
Liste* li=creerListe(1);
    razMarque (graphe);
    for(int j=0;j<graphe->n;j++){
        *(cout+j)=0;
    }
    begin = clock();
    for (int i=0; i<graphe->n; i++)
    {
        if (!graphe->marque [i]){
         *(cout+i)=0;
            coutUniforme (graphe, li,i,but);}

        break;
    }

if(trouveS){
        printf("\n\n Le plus court  chemin vers le noeud   %s   :",graphe->nomS[but]);
          printf("%s\n",*(path+but));
          printf("Le cout de ce chemin :  %d ",*(cout+but));
          trouveS=false;
}
else {
    printf("\nNoeud INTROUVABLE");
}
end = clock();
time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
printf("\nLe temps pris :  %f",time_spent);
    printf("\nNoeuds visites : %d",compteurVisiteG);
    compteurVisiteG=0;
}
 void largeur (GrapheMat* graphe, Liste* li, int numSommet,char but[])
{
    int nMax = graphe->nMax;
    NomSom* extraite=NULL;
    insererEnFinDeListe (li,graphe->nomS[numSommet]);
    graphe->marque [numSommet]=true;
  printf("Chemin pris par le parcours  :   ");

    while (!listeVide (li) )
    {

     extraite = (NomSom*) extraireEnTeteDeListe (li);
     compteurVisiteG++;
        if(strcmp(*extraite,but)==0){

                printf("->%s (Noeud but) ",but);
                return;
             }

    numSommet = rang (graphe,*extraite);

  printf("->%s",*extraite);


    for (int i=0; i<graphe->nMax; i++)
    {
         if ( (graphe->element [numSommet*nMax+i] == vrai)
                && !graphe->marque [i] )
        {


           insererEnFinDeListe(li,graphe->nomS[i]);
           graphe->marque[i] = vrai;

        }

    }

}
printf("\nLe noeud but %s est INTROUVABLE. ",but);
}
float coutDistance(GrapheMat* graphe,int tab[]){
    float valeurTemp=0;
    int nMax=graphe->nMax;
    for(int i=0;i<(graphe->n);i++){
       valeurTemp+= graphe->valeur[tab[i]*nMax+tab[i+1]];
    }
    return valeurTemp;
}

static void inverserTableau(int t[],int debut,int fin){
    int temp;

    for(int i=debut;i<(fin+debut+1)/2;i++){
        temp=t[i];
        t[i]=t[(fin+1+debut)-i-1];
        t[(fin+1+debut)-i-1]=temp;
    }

}
static void deuxOptV2(GrapheMat* graphe, int numSommet, int tab[]){
int tabTemp[(graphe->n)+1];
int tabBut[(graphe->n)+1];
valeur=100000;
 for(int k=0;k<(graphe->n)+1;k++){
          tabTemp[k]=tab[k];
         }
for(int i=1;i<graphe->n;i++){

    for(int j=i+1;j<graphe->n;j++){
        if(i==1&&j==(graphe->n)-1){
            continue;
        }
        inverserTableau(tab,i,j);
        if(debug){
           for(int k=0;k<(graphe->n)+1;k++){
               printf("%d",tab[k]);
              }
           printf("   %f",coutDistance(graphe,tab));
           printf("\n");
         }
        if(valeur>coutDistance(graphe,tab)){
            valeur=coutDistance(graphe,tab);
            for(int n=0;n<(graphe->n)+1;n++){
                tabBut[n]=tab[n];
             }

        }

 for(int k=0;k<(graphe->n)+1;k++){
          tab[k]=tabTemp[k];
         }
    }
}
for(int n=0;n<(graphe->n)+1;n++){
    tab[n]=tabBut[n];
    }
}
static void deuxOptV1(GrapheMat* graphe, int numSommet, int tab[]){
        int i= rand() % ((graphe->n-2)+1);
        int j= i+1;
        inverserTableau(tab,i,j);
        valeur=coutDistance(graphe,tab);



}

void parcoursLargeur(GrapheMat* graphe){
clock_t begin, end;
double time_spent;


razMarque(graphe);
 Liste* li = creerListe();
 char str[20];

   printf("Entrez le sommet but : (le sommet but designe par le prof est S7) ");
   scanf("%s", str);
   begin = clock();
 for (int i=0; i<graphe->n; i++)
    {
        if(!graphe->marque[i]){
            largeur(graphe,li,i,str);}
            break;
    }

end = clock();
time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
   printf("\n Le temps pris :  %f",time_spent);
    printf("\nNoeuds visites : %d",compteurVisiteG);
    compteurVisiteG=0;
}


static void plusProcheVoisin (GrapheMat* graphe, int numSommet,int tab[]) {
    int nMax = graphe->nMax;
if(nbEltTab!=graphe->n){
    valeur=100000;
    tab[nbEltTab]=numSommet;
    nbEltTab++;
    graphe->marque [numSommet]=true;
    for (int i=0; i<graphe->n; i++)
    {
        if ( (graphe->element [numSommet*nMax+i] == vrai)
                && !graphe->marque [i] )
        {
            if (valeur>graphe->valeur [numSommet*nMax+i]){
                valeur=graphe->valeur [numSommet*nMax+i];
                tab[nbEltTab]=i;
            }
        }
    }
   if(valeur!=100000)
   coutTotal+=valeur;
   plusProcheVoisin(graphe,tab[nbEltTab],tab);
}
else{
        coutTotal+=graphe->valeur [tab[nbEltTab-1]*nMax+SOMMET_INITIAL];

            tab[nbEltTab]=SOMMET_INITIAL;

}

}




void parcoursRecuitSimule(GrapheMat* graphe){
clock_t begin, end;
double time_spent;
int temperature=10000;
float valeurRS=1000000;
float factDecroi=0.93;
razMarque(graphe);
int p1,p2;
float p3;
int tab[(graphe->n)+1];
int tabSucc[(graphe->n)+1];
int tabBut[(graphe->n)+1];
begin=clock();
plusProcheVoisin(graphe,0,tab);


while(temperature>0){
    for(int i=0;i<(graphe->n)+1;i++){
        tabSucc[i]=tab[i];
    }
    if(debug){
           for(int k=0;k<(graphe->n)+1;k++){
               printf("%d",tabSucc[k]);
              }
           printf("   %f",coutDistance(graphe,tabSucc));
           printf("\n");
         }
    deuxOptV2(graphe,0,tabSucc);
  // p1=rand()%(graphe->n-1)+1;
   // p2=rand()%(graphe->n-1)+1;
   //p3=tabSucc [p1];
   //tabSucc[p1]=tabSucc[p2];
   //tabSucc[p2]=p3;
    if(coutDistance(graphe,tabSucc)<coutDistance(graphe,tab)){
       for(int i=0;i<(graphe->n)+1;i++){
        tab[i]=tabSucc[i];

    }
    if(valeurRS>coutDistance(graphe,tabSucc)){
     valeurRS=coutDistance(graphe,tabSucc);
      for(int k=0;k<(graphe->n)+1;k++){
         tabBut[k]=tabSucc[k];
         }
    }}
    else{
        if(exp(-(coutDistance(graphe,tabSucc)-coutDistance(graphe,tab))/temperature)>0,5){
             for(int i=0;i<(graphe->n)+1;i++){
        tab[i]=tabSucc[i];
    }
        }


    }
    temperature=temperature*factDecroi;
    }
end=clock();
time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
printf("\nLe temps d execution : %f ",time_spent);
printf("\nLe trajet Recuit simule : \n");
for(int k=0;k<(graphe->n)+1;k++){
    printf("%d",tabBut[k]);
    printf("->");
}
printf("\nLe cout Recuit Simule %f \n",valeurRS);
 valeur=0;
 coutTotal=0;
nbEltTab=0;

}




void parcoursPlusProcheVoisin(GrapheMat* graphe){
clock_t begin, end;
double time_spent;
int nMax=graphe->nMax;
int tabPPV[(graphe->n)+1];
razMarque(graphe);
begin = clock();
for (int i=0; i<graphe->n; i++)
    {
        if(!graphe->marque[i]){
            plusProcheVoisin(graphe,SOMMET_INITIAL,tabPPV);

}
            break;
    }
end = clock();
time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
printf("\n Le temps pris :  %f ",time_spent);
printf("\n Le trajet de PPV :  \n");
for(int j=0;j<(graphe->n)+1;j++){
    printf("%d",tabPPV[j]);
    printf("%->");
    }
printf("\n Le cout total de PPV :  %f \n",coutTotal);
valeur=0;
nbEltTab=0;
coutTotal=0;
}

void crossover(int population[NOMBRE_TRAJETS][NOMBRE_VILLES],int parent1[], int parent2[], int fils[]){
int pointDeCoupure1, pointDeCoupure2, temp;
int indice1,indice2;

//Initialisation des deux points de coupure et tri
pointDeCoupure1=rand()%(NOMBRE_VILLES-2)+1;
pointDeCoupure2=rand()%(NOMBRE_VILLES-2)+1;
if(pointDeCoupure2<pointDeCoupure1){
    temp=pointDeCoupure1;
    pointDeCoupure1=pointDeCoupure2;
    pointDeCoupure2=temp;
}

//On copie le parent1 dans le fils
for(int i=0;i<NOMBRE_VILLES;i++){
    fils[i]=parent1[i];
}

//Traitement du crossover
for(int i =pointDeCoupure1; i<=pointDeCoupure2;i++){
    for(int j=0;j<NOMBRE_VILLES;j++){
        if(fils[j]==parent1[i]){
            indice1=j;
        }
        else if(fils[j]==parent2[i]){
            indice2=j;
        }
    }
    if(parent1[i]!=parent2[i]){
        fils[indice1]=parent2[i];
        fils[indice2]=parent1[i];
        }
}

}
void genererNouvellePopulation(GrapheMat* graphe,int population[NOMBRE_TRAJETS][NOMBRE_VILLES], int populationSuivante[NOMBRE_TRAJETS][NOMBRE_VILLES]){
int populationTemp[NOMBRE_TRAJETS*2][NOMBRE_VILLES];
int temp[NOMBRE_VILLES];
for(int i=0;i<NOMBRE_TRAJETS;i++){
        for(int j=0;j<NOMBRE_VILLES;j++){
                populationTemp[i][j]=population[i][j];
                populationTemp[i+NOMBRE_TRAJETS][j]=populationSuivante[i][j];
        }
}

   for (int i = 0; i <NOMBRE_TRAJETS; i++)
    {
        for (int j = i + 1; j < NOMBRE_TRAJETS; j++)
        {
            if (coutDistance(graphe,populationTemp[i])< coutDistance(graphe,populationTemp[j]))
            {

                for(int l=0;l<NOMBRE_VILLES;l++){
                temp[l] = populationTemp[i][l];
                populationTemp[i][l]= populationTemp[j][l];
                populationTemp[j][l] = temp[l];
            }}
        }
    }

for(int i=0;i<NOMBRE_TRAJETS;i++){
        for(int j=0;j<NOMBRE_VILLES;j++){
                population[i][j]=populationTemp[i+NOMBRE_TRAJETS][j];

        }

}
}
int tournamentSelection(GrapheMat* graphe,int population[NOMBRE_TRAJETS][NOMBRE_VILLES], int k)
{
    int indice;
    int indiceGagnant;
    int tab[NOMBRE_VILLES];
    int coutTrajet=100000;
for(int i=0;i<k;i++){
    indice=rand()%NOMBRE_TRAJETS;
    for(int j=0;j<NOMBRE_VILLES;j++){
    tab[j]=population[indice][j];
   }
   if(coutTrajet>coutDistance(graphe,tab)){
    coutTrajet=coutDistance(graphe,tab);
    indiceGagnant=indice;
   }
}
return indiceGagnant;
}
void parcoursGenetique(GrapheMat* graphe){
int population[NOMBRE_TRAJETS][NOMBRE_VILLES];
int populationSuivante[NOMBRE_TRAJETS][NOMBRE_VILLES];
int tab[NOMBRE_VILLES];
int parent1[NOMBRE_VILLES],parent2[NOMBRE_VILLES], fils[NOMBRE_VILLES],tabBut[NOMBRE_VILLES];
int pointDeCoupure1,pointDeCoupure2, mutation, parent1Tour,parent2Tour,temp,reproduction=300;
float cout_genetique=100000;
clock_t begin, end;
double time_spent;
razMarque(graphe);

for(int i=0;i<graphe->n;i++){
        tab[i]=i;
      }
 tab[graphe->n]=0;

//INITIALISATION ALEATOIRE AVEC SHUFFLE
for(int i=0;i<NOMBRE_TRAJETS;i++){
   shuffle(tab,graphe->n);

    for(int j=0;j<NOMBRE_VILLES;j++){
        population[i][j]=tab[j];
    }
}
begin = clock();

//SELECTION DES PARENTS
//Selon une etude en 2011, tournamenet selection est meilleure que la "roulette wheel" en PVC
while(reproduction>0){
for(int i=0;i<NOMBRE_TRAJETS;i++){
    parent1Tour=tournamentSelection(graphe,population,NOMBRE_TRAJETS);
    parent2Tour=tournamentSelection(graphe,population,10);
    for(int m=0;m<NOMBRE_VILLES;m++){

        parent1[m]=population[parent1Tour][m];
         parent2[m]=population[parent2Tour][m];
    }

//Crossover entre les 2 parents
crossover(population,parent1,parent2,fils);

//Mutation
mutation=rand()%(int)(1.0/TAUX_MUTATION);
if(mutation==0){
    pointDeCoupure1=rand()%(NOMBRE_VILLES-2)+1;
    pointDeCoupure2=rand()%(NOMBRE_VILLES-2)+1;
    if(pointDeCoupure2<pointDeCoupure1){
        temp=pointDeCoupure1;
        pointDeCoupure1=pointDeCoupure2;
        pointDeCoupure2=temp;
      }
    inverserTableau(fils,pointDeCoupure1,pointDeCoupure2);
}
if(cout_genetique>coutDistance(graphe,fils)){
    cout_genetique=coutDistance(graphe,fils);
    for(int j=0;j<NOMBRE_VILLES;j++){
    tabBut[j]=fils[j];
}
}
for(int j=0;j<NOMBRE_VILLES;j++){
    populationSuivante[i][j]=fils[j];
}
}

genererNouvellePopulation(graphe,population,populationSuivante);
reproduction--;
}
end = clock();
time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
printf("\n Le temps d execution genetique : %f ",time_spent);
printf("\n Le trajet de l'algorithme genetique :\n");
for(int k=0;k<NOMBRE_VILLES;k++){
    printf("%d",tabBut[k]);
    printf("->");
}
printf("\nLe cout de l'algorithme genetique %f \n",cout_genetique);
 valeur=0;
 coutTotal=0;
nbEltTab=0;

}
void modifierPoids(float w[],int d[],int x[],int e[NOMBRE_POIDS][NOMBRE_ENTREE],int i){
for(int j=0;j<NOMBRE_POIDS;j++){
    w[j]=w[j]+MU*((d[i]-x[i])*e[j][i]);

}
}
int calculerSortie(float w[],int e[NOMBRE_POIDS][NOMBRE_ENTREE],int i){
float resultat=0;
int resultatTemp;
for(int j=0;j<NOMBRE_POIDS;j++){
    resultat+=w[j]*e[j][i];
}
resultat=resultat-TETA;
if(resultat>0){
    resultatTemp=1;
}
else
    resultatTemp=0;

return resultatTemp;
}
void perceptron(){

float w[NOMBRE_POIDS]={0.3,-0.1};
int e[NOMBRE_POIDS][NOMBRE_ENTREE]={{0,0,1,1},{0,1,0,1}};
int d[NOMBRE_ENTREE]={0,0,0,1};
int x[NOMBRE_ENTREE];
booleen fini=false;
int compteur=0;

while(!fini){
compteur=0;
printf("e1 e2 d    w1        w2         x    w1f         w2f   \n");
for (int i=0;i<NOMBRE_ENTREE;i++){
    x[i]=calculerSortie(w,e,i);
    printf("%d  %d  %d  %f   %f   %d   ",e[0][i],e[1][i],d[i],w[0],w[1],x[i]);
    if(x[i]!=d[i]){
        modifierPoids(w,d,x,e,i);
    }
      else
        compteur++;
printf("%f  %f",w[0],w[1]);
    if(compteur==4)
        fini=true;
     printf("\n");
}
printf("\n");
printf("\n");
printf("\n");
}




}


 void parcoursDeuxOptV2(GrapheMat* graphe){
clock_t begin, end;
double time_spent;
int tab[(graphe->n)+1];
//={0,3,1,2,4,0};
razMarque(graphe);
begin = clock();
for (int i=0; i<graphe->n; i++)
    {
        if(!graphe->marque[i]){


         plusProcheVoisin(graphe,i,tab);
          // shuffle(tab,(graphe->n)+1);
           deuxOptV2(graphe,i,tab);}
           break;
    }

end = clock();
time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
printf("\n Le temps pris par 2-OPTV2 :  %f ",time_spent);
printf("\n Le trajet de 2-OPTV2:  \n");
for(int k=0;k<(graphe->n)+1;k++){
           printf("%d",tab[k]);
           printf("->");
         }

printf("\n Le meilleur cout 2-OPTV2 : %f \n ",valeur);
valeur=0;
nbEltTab=0;
coutTotal=0;
}
float sigmoide(float x)
{
    return 1/(1+exp(-x));
}
void multiCouches(){
float w[NOMBRE_ACTIVATION][NOMBRE_ACTIVATION+1]={{0,0,0,0,0,0,0,0},
    {0,0,0,0.5,-1,0,0,0},
    {0,0,0,1.5,-2,0,0,0},
    {0,0,0,0,0,1,-1,0},
    {0,0,0,0,0,3,-4,0},
    {0,0,0,0,0,0,0,1},
    {0,0,0,0,0,0,0,-3}};


float temp=0.0;
float alpha=0.1;
float delta[NOMBRE_ACTIVATION+1]={0,0,0,0,0,0,0,0};
float in[NOMBRE_ACTIVATION+1]={0,0,0,0,0,0,0,0};
float d=1;


float teta=0;
float a[NOMBRE_ACTIVATION+1]={0,0,0,0,0,0,0,0};
float x[NOMBRE_ENTREE_MULTI+1]={0,2,-1};

//while(delta[NOMBRE_ACTIVATION]>0.1){
 for(int i=0; i<3; i++)
    {
        a[i]=x[i];
    }

  for( int j=3; j<=NOMBRE_ACTIVATION; j++)
    {
        for( int i=0; i<NOMBRE_ACTIVATION; i++)
        {
            in[j]+=w[i][j]*a[i];

        }


        a[j]=sigmoide(in[j]);
    }
  for(int j=1; j<NOMBRE_ACTIVATION+1; j++)
    {
        printf("a%d<--%f\n",j,a[j]);
    }

    //Couche de sortie contient un seul element
    delta[NOMBRE_ACTIVATION]=1-a[NOMBRE_ACTIVATION];
    printf("\n\n");
    printf("delta7<--%f\n",delta[NOMBRE_ACTIVATION]);
    for(int i=NOMBRE_ACTIVATION-1; i>2; i--)
    {
        for(int j=1; j<NOMBRE_ACTIVATION+1; j++)
        {
            temp+=w[i][j]*delta[j];
        }
        delta[i]=sigmoide(in[i])*(1-sigmoide(in[i]))*temp;
        printf("delta%d<--%f\n",i,delta[i]);
        temp=0;
    }
     printf("\n\n");
    for(int i=1; i<NOMBRE_ACTIVATION; i++)
    {
        for(int j=1; j<NOMBRE_ACTIVATION+1; j++)
        {
            if(w[i][j]!=0){
            w[i][j]=w[i][j]+alpha*a[i]*delta[j];
            }
        }
    }
    for(int i=1; i<NOMBRE_ACTIVATION; i++)
    {
        for(int j=1; j<NOMBRE_ACTIVATION+1; j++)
        {
           if(w[i][j]!=0){
            printf("w%d%d<--%f\n",i,j,w[i][j]);
        }
        }
    }
}
 void parcoursDeuxOptV1(GrapheMat* graphe){
clock_t begin, end;
double time_spent;
int tab[(graphe->n)+1];
razMarque(graphe);
begin = clock();
for (int i=0; i<graphe->n; i++)
    {
        if(!graphe->marque[i]){
           plusProcheVoisin(graphe,i,tab);
          // shuffle(tab,(graphe->n)+1);
           deuxOptV1(graphe,i,tab);}
           break;
    }

end = clock();
time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
printf("\n Le temps pris par 2-OptV1 :  %f \n",time_spent);
printf("\n Le trajet de 2-OPTV1: \n ");
for(int k=0;k<(graphe->n)+1;k++){
           printf("%d",tab[k]);
           printf("->");
         }

printf("\n Le meilleur cout 2-OPTV1 : %f \n ",valeur);
valeur=0;
nbEltTab=0;
coutTotal=0;
}

static void profondeurIteratif (GrapheMat* graphe, int numSommet,int d,char but[])
{ if(!trouveS){
compteurVisiteG++;
     if(strcmp(graphe->nomS[numSommet],but)==0){

                printf("->%s (Noeud but) ",but);
               trouveS=true;
             }

       else if(d==0){
     printf ("->%s", graphe->nomS [numSommet]);

     graphe->marque [numSommet] = vrai;
     }
        else {
            if (d>0){
    int nMax = graphe->nMax;
    graphe->marque [numSommet] = vrai;
printf ("->%s", graphe->nomS [numSommet]);
    for (int i=0; i<graphe->n; i++)
    {

        if ( (graphe->element [numSommet*nMax+i] == vrai)
                && !graphe->marque [i] )
        {

            profondeurIteratif(graphe, i, d-1,but);

        }

    }
     }}
}}

void parcoursProfondeurIteratif(GrapheMat* graphe){
clock_t begin, end;
double time_spent;
 char str[20];
 int niveau;
 printf("Entrez le sommet but : (le sommet but designe par le prof est S7) ");
 scanf("%s", str);
  printf("Entrez le niveau maximal ");
 scanf("%d", &niveau);
  razMarque (graphe);
Liste* li = creerListe();
printf("Chemin suivi par le parcous :   ");

  d=0;
  begin = clock();
    for ( d=0; d<niveau; d++)
    {razMarque (graphe);
 for (int i=0; i<graphe->n; i++)
    {

        if(!graphe->marque[i])
            profondeurIteratif(graphe,i,d,str);

            break;

    }
}
 if(!trouveS){
        trouveS=false;
        printf("\nLe noeud %s est INTROUVABLE",str);
    }
    end = clock();
time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
printf("\n Le temps pris :  %f",time_spent);
printf("\nNoeuds visites : %d",compteurVisiteG);
    compteurVisiteG=0;
    trouveS=false;
}

static void ecrireEtape (Matrice a, Matrice p, int k, int ns, int nMax)
{
    printf ("Passage par le sommet numéro %d\n", k);

    for (int i=0; i<ns; i++)
    {
        for (int j=0; j<ns; j++)
        {
            if (a [i*nMax+j]==INFINI)
            {
                printf (" %3s", "*");

            }
            else
            {
                printf (" %3d", a [i*nMax+j]);
            }
        }
        printf ("%6s", " ");
        for (int j=0; j<ns; j++)
        {
            printf ("%3d", p [i*nMax+j]);
        }
        printf ("\n");
    }
    printf ("\n");
}

// initialiser les matrices a et p à partir de graphe
static void initFloyd (GrapheMat* graphe, Matrice* a, Matrice* p)
{
    int nMax = graphe->nMax;

    Matrice ta = (float*) malloc (sizeof(int)*nMax*nMax);
    Matrice tp = (float*) malloc (sizeof(int)*nMax*nMax);


    for (int i=0; i<graphe->n; i++)
    {
        for (int j=0; j<graphe->n; j++)
        {
            if(i==j){
                ta [i*nMax+j]=0;
                tp [i*nMax+j] = i;
            }
            else{
                ta [i*nMax+j] = graphe->valeur [i*nMax+j];
                tp [i*nMax+j] = i;
            }
        }
    }
    *a = ta;
    *p = tp;
}

void floyd (GrapheMat* graphe)
{
    Matrice a, p;
    int n = graphe->n;
    int nMax = graphe->nMax;

    initFloyd (graphe, &a, &p);


    for (int k=0; k<n; k++)
    {
        for (int i=0; i<n; i++)
        {
            for (int j=0; j<n; j++)
            {
                if ( (a [i*nMax+k] != INFINI) &&
                        (a [k*nMax+j] != INFINI) &&
                        (a [i*nMax+k] + a [k*nMax+j] < a [i*nMax+j]) )
                {
                    a [i*nMax+j] = a [i*nMax+k] + a [k*nMax+j];
                    p [i*nMax+j] = p [k*nMax+j];
                }
            }
        }
        ecrireEtape (a, p, k, n, nMax);
    }
}
