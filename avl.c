typedef struct Arvore arvore;

struct Arvore{
    int valor, fator_balanceamento;
    arvore *esquerda;
    arvore *direita;
    arvore *pai;
};
arvore *raiz = NULL;

arvore* criaArvore(){
    arvore *tmp = (arvore*) malloc(sizeof(arvore));
    if(!tmp) return NULL;
    return tmp;
}

int altura( arvore *aux){
    if(!aux) return 0;
    return (altura(aux->esquerda) > altura(aux->direita)) ? altura(aux->esquerda) + 1: altura(aux->direita) + 1;
}

arvore* menorDireita( arvore *aux){
    while(aux->esquerda) aux = aux->esquerda;
    return aux;
}

arvore* buscar(int n){
    arvore *aux = raiz;
    while(aux && aux->valor != n){
        if(n < aux->valor) aux = aux->esquerda;
        else aux = aux->direita;
    }
    return aux;
}

arvore* rotacaoDireita( arvore *aux){
    arvore *esq = aux->esquerda;
    aux->esquerda = esq->direita;
    esq->direita = aux;

    if(aux->esquerda) aux->esquerda->pai = aux;

    esq->pai = aux->pai;
    aux->pai = esq;

    if(aux == raiz) raiz = esq;

    if(esq->pai){
        if(esq->valor < esq->pai->valor) esq->pai->esquerda = esq;
        else esq->pai->direita = esq;
    }
    esq->fator_balanceamento = altura(esq->direita) - altura(esq->esquerda);
    aux->fator_balanceamento = altura(aux->direita) - altura(aux->esquerda);

    return esq;
}

arvore* rotacaoEsquerda( arvore *aux){
    arvore *dir = aux->direita;
    aux->direita = dir->esquerda;
    dir->esquerda = aux;

    if(aux->direita) aux->direita->pai = aux;
    
    dir->pai = aux->pai;
    aux->pai = dir;

    if(aux == raiz) raiz = dir;

    if(dir->pai){
        if(dir->valor < dir->pai->valor) dir->pai->esquerda = dir;
        else dir->pai->direita = dir;
    }
    dir->fator_balanceamento = altura(dir->direita) - altura(dir->esquerda);
    aux->fator_balanceamento = altura(aux->direita) - altura(aux->esquerda);
    return dir;
}

arvore* balanceia( arvore *aux){
    if(aux->fator_balanceamento < -1){
        if(aux->esquerda->fator_balanceamento > 0) aux->esquerda = rotacaoEsquerda(aux->esquerda);
        aux = rotacaoDireita(aux);
    }
    else if(aux->fator_balanceamento > 1){
        if(aux->direita->fator_balanceamento < 0) aux->direita = rotacaoDireita(aux->direita);
        aux = rotacaoEsquerda(aux);
    }
    return aux;
}

int insere(int valor){
    arvore *aux1 = NULL, *aux2 = NULL;
    if(buscar(valor)) return -1; //verifica se o no ja exite
    if(!raiz){
        raiz = criaArvore();
        if(!raiz) return -1;
        raiz->valor = valor;
        raiz->esquerda = NULL;
        raiz->direita = NULL;
        raiz->pai = NULL;
        raiz->fator_balanceamento= 0;
    }
    else{
        aux1 = raiz;
        aux2 = aux1;
        while(aux2){
            if(valor < aux2->valor){
                aux2 = aux2->esquerda;
                if(!aux2){
                    aux1->esquerda = criaArvore();
                    if(!aux1->esquerda) return -1;
                    aux2 = aux1->esquerda;
                    aux2->esquerda = NULL;
                    aux2->direita = NULL;
                    aux2->pai = aux1;
                    aux2->valor = valor;
                    break;
                }
                else aux1 = aux2;
            }
            else{
                aux2 = aux2->direita;
                if(!aux2){
                    aux1->direita = criaArvore();
                    if(!aux1->direita) return -1;
                    aux2 = aux1->direita;
                    aux2->esquerda = NULL;
                    aux2->direita = NULL;
                    aux2->pai = aux1;
                    aux2->valor = valor;
                    break;
                }
                else aux1 = aux2;
            }
        }
    }
    /*faz o balanceamento*/
    if(aux2){
        while(aux2){
            aux2->fator_balanceamento = altura(aux2->direita) - altura(aux2->esquerda);
            if(aux2->fator_balanceamento > 1 || aux2->fator_balanceamento < -1) aux2 = balanceia(aux2);
            aux2 = aux2->pai;
        }
    }
    return 0;
}

void remover( arvore *aux){
    arvore *aux2, *salva = aux->pai;
    if(aux != raiz){
        if(!aux->esquerda && !aux->direita){
            if(aux->valor < aux->pai->valor) aux->pai->esquerda = NULL;
            else aux->pai->direita = NULL;
            free(aux);
        }
        else if(!aux->direita){
            if(aux->valor < aux->pai->valor) aux->pai->esquerda = aux->esquerda;
            else aux->pai->direita = aux->esquerda;
            aux->esquerda->pai = aux->pai;
            free(aux);
        }
        else if(!aux->esquerda){
            if(aux->valor < aux->pai->valor) aux->pai->esquerda = aux->direita;
            else aux->pai->direita = aux->direita;
            aux->direita->pai = aux->pai;
            free(aux);
        }
        else{
            aux2 = menorDireita(aux->direita);
            aux->valor = aux2->valor;
            remover(aux2);
        }
    }
    else{
        if(!aux->esquerda && !aux->direita){
            free(aux);
            raiz = NULL;
        }
        else if(!aux->direita){
            aux->esquerda->pai = NULL;
            raiz = aux->esquerda;
            free(aux);
        }
        else if(!aux->esquerda){
            aux->direita->pai = NULL;
            raiz = aux->direita;
            free(aux);
        }
        else{
            aux2 = menorDireita(aux->direita);
            aux->valor = aux2->valor;
            remover(aux2);
        }
    }
    if(salva){
        while(salva){
            salva->fator_balanceamento = altura(salva->direita) - altura(salva->esquerda);
            if(salva->fator_balanceamento > 1 || salva->fator_balanceamento < -1) salva = balanceia(salva);
            salva = salva->pai;
        }
    }
}

void limparArvore( arvore *aux){
    if(aux->esquerda) limparArvore(aux->esquerda);
    if(aux->direita) limparArvore(aux->direita);
    free(aux);
    raiz = NULL;
}