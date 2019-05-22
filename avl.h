#include <stdlib.h>
#include "avl.c"

arvore* criaArvore();
int altura( arvore *aux);
arvore* menorDireita( arvore *aux);
arvore* buscar(int n);
arvore* rotacaoDireita( arvore *aux);
arvore* rotacaoEsquerda( arvore *aux);
arvore* balanceia( arvore *aux);
int insere(int valor);
void remover( arvore *aux);
void limparArvore( arvore *aux);