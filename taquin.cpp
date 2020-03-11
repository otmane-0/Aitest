

#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>
#include "taquin.h"
#define BAS 0
#define HAUT 1
#define GAUCHE 2
#define DROITE 3
#define H2



int heur(int block[]);
void lier(elementstruct* nouveaunoeud, elementstruct* anciennoeud, int op);
int but(int* block);
int nonVisite(int block[]);
elementstruct* plusPetiteHeur();

int resultatAction(int* nouveauetat, int* ancienetat, int op);
elementstruct* nouveauelement();
int op(char);


char rep[] = "bhgd";
int orientation1[4] = { 6, 0, 0, 2 };
int orientation2[4] = { 7, 1, 3, 5 };
int orientation3[4] = { 8, 2, 6, 8 };
int mvPossible[4] = { +3, -3, -1, +1 };
int but_block[9] = { 0, 1, 2, 3, 4, 5, 6, 7, 8};
int profondeurmax;
elementstruct* top;

int invoquerTaquin()
{
  int block[9];

  printf("\n----------------------Taquin a 8pieces------------------------\n");
  printf("\n--------------------------------------------------------------\n");

  printf("\nVeuillez entrer l'etat initial du taquin \n"
         "exemple :  '1 4 2 3 b 6 7 8 5' avec b la case vide \n"
         );

  int i = 0;
  while(i<9)
	{
	char chr;
	chr = fgetc(stdin);
	if (chr==32) continue;
	if (chr=='b') block[i] = 8;
	else if (chr >= '1' && chr <= '9') block[i] = chr - '1';
	else { printf("Ecriture incorrecte, exemple d'ecriture correcte...2 1 3 4 7 5 6 8 b."); return 1; }
	i++;
	}

  fgetc(stdin);

  printf("\n Entrez l'etat final comme precedemment. (Exemple: 1 2 3 4 5 6 7 8 b): \n");

  i = 0;
  while(i<9)
	{
	char chr;
	chr = fgetc(stdin);
	if (chr==32) continue;
	if (chr=='b') but_block[i] = 8;
	else if (chr >= '1' && chr <= '9') but_block[i] = chr - '1';
	else { printf("Ecriture incorrecte, exemple d'ecriture correcte...2 1 3 4 7 5 6 8 b.") ;
	return 1;
	 }
	i++;
	}

  printf("Entrez la profondeur max de recherche: \n");
  scanf("%d", &profondeurmax);



  top = nouveauelement();
  for(i=0; i<9; i++)
    top->block[i] = block[i];
  top->couttotal = heur(block);

  elementstruct* nouveaunoeud = nouveauelement();

  while (1)
    {
      elementstruct* noeud = plusPetiteHeur();
      if (noeud == NULL) {
	printf("Pas de solution pour cette %d profondeur.\n", profondeurmax);

	break;
      }
      else if (but(noeud->block)) {
	char chr[15];
	printf("Chemin trouve\n.\nNombre d'etapes pour trouver la solution: (%d).", noeud->coutpath);

	  printf("\n (Deplacement case vide h=haut, b=bas, g=gauche, d=droite)\n");
	  printf("Chemin : %s",noeud->str);
	  printf("\n");
	  break;


      }

      if (noeud->couttotal > profondeurmax) continue;

      for(i=0; i<=3; i++) {
	if (resultatAction(nouveaunoeud->block, noeud->block, i) == -1)
	  continue;

	if (nonVisite(nouveaunoeud->block)) {
	  lier(nouveaunoeud, noeud, i);
	  nouveaunoeud = nouveauelement();
	  if (nouveaunoeud==NULL) { printf ("ERREUR!! Pas de memoire!!"); return 1; }
	}
      }

	}
	return 0;
}

int heur(int* block)
{

  int to_return = 0;

  for(int i=0; i<9; i++)
    {
    to_return += abs((i/3) - (block[i]/3));
    to_return += abs((i%3) - (block[i]%3));
    }
  return to_return;



}


void lier(elementstruct* nouveaunoeud, elementstruct* anciennoeud, int op)
{
  nouveaunoeud->next=top;
  top = nouveaunoeud; // commentaitre on change de top,utile pour le bestfromqueue et notonqueue

  strcpy(nouveaunoeud->str, anciennoeud->str);
  nouveaunoeud->str[anciennoeud->coutpath] = rep[op];
  nouveaunoeud->str[anciennoeud->coutpath+1] = 0;

  nouveaunoeud->coutpath = anciennoeud->coutpath+1; //commentaire incremenatation du coutpath(nombre detapes)
  nouveaunoeud->couttotal = nouveaunoeud->coutpath + heur(nouveaunoeud->block);
  if (nouveaunoeud->couttotal < anciennoeud->couttotal) nouveaunoeud->couttotal = anciennoeud->couttotal;
}


int but(int* block)
{
  int* g_block = but_block;

  for(int i=0; i<9; i++)
    if ((*(block+i))!=(*(g_block+i)))
      return 0;

  return 1;
}

int nonVisite(int* block)
{
  int i,j;
  elementstruct* t = top;

  while (t!=NULL)
    {
      for(i=0; i<9; i++)
	if (t->block[i] != block[i]) break;
      if (i==9) return 0;

      t = t->next;
    }
  return 1;
}

elementstruct* plusPetiteHeur()
{
  elementstruct* t = top;
  int min_couttotalpath = 1000;
  elementstruct* to_return = NULL;

  while (t != NULL)
    {
	  if (t->valid==1 && t->couttotal < min_couttotalpath)
	{
	min_couttotalpath = t->couttotal;
	to_return = t;
	}
      t = t->next;
    }

  if (to_return != NULL) to_return->valid = 0;

  return to_return;
}


int resultatAction (int* nouveauetat, int* ancienetat, int op)
{
  int j;
  int blank;

  for (j=0; j<9; j++)
	if (ancienetat[j]==8) { blank=j; break; }

  if (blank==orientation1[op] || blank==orientation2[op] || blank==orientation3[op])
    return -1;

  for (j=0; j<9; j++)
    nouveauetat[j] = ancienetat[j];

  nouveauetat[blank] = nouveauetat[blank+mvPossible[op]];
  nouveauetat[blank+mvPossible[op]] = 8;

  return 1;
}

elementstruct* nouveauelement()
{
  elementstruct* t = new elementstruct;
  if (t==NULL) return NULL;
  t->valid = 1;
  t->str = new char[profondeurmax+1];
  if (t->str ==NULL) return NULL;
  t->str[0] = 0;
  t->coutpath = t->couttotal  = 0;
  t->next = NULL;
  return t;
}




int op(char i)
{
switch (i)
  {
  case 'b': return 0;
  case 'h': return 1;
  case 'g': return 2;
  case 'd': return 3;
  default: printf("ERREUR!"); return -1;
  }
}




