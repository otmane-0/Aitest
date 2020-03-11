#ifndef TAQUIN_H_INCLUDED
#define TAQUIN_H_INCLUDED
struct elementstruct
{
  int block[9];
  char* str;
  int coutpath;
  int valid;
  int couttotal;
  elementstruct* next;
};
int invoquerTaquin();
int heur(int block[]);
void lier(elementstruct* nouveaunoeud, elementstruct* anciennoeud, int op);
int but(int* block);
int nonVisite(int block[]);
elementstruct* plusPetiteHeur();

int resultatAction(int* nouveauetat, int* ancienetat, int op);
elementstruct* nouveauelement();
int op(char);

#endif // TAQUIN_H_INCLUDED
