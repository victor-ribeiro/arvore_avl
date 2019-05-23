#include <stdio.h>
#include <stdlib.h>
#include"avl.h"
#include"interface.h"

int main(){
    arvore *b;
    int op, n;
    while(1){
        menu();
        scanf("%d", &op);
        getchar();
        switch(op){
            case 1:
                i_insere();
                printf("\n");
                imprimirArvore(raiz, altura(raiz));
                printf("\n\n");
                break;
            case 2: 
                i_remove();
                printf("Pronto!\n");
                break;
            case 3: 
                i_procura();
                break;
            case 4: 
                imprimirArvore(raiz, altura(raiz));
                printf("\nPronto!\n");
                break;
            case 5: 
                printf("Altura da arvore: %d\n", altura(raiz));

                break;
            case 6: 
                i_limpa();
                break;
            case 7: 
                if(raiz) limparArvore(raiz);
                exit(0);
            default: 
                printf("Opcao incorreta!\n");
                break;
        }
    }
    return 0;
}