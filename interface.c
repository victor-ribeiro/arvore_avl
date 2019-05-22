void menu(){
    printf("Arvore AVL\n");
    printf("1 - Inserir\n");
    printf("2 - Remover\n");
    printf("3 - Buscar\n");
    printf("4 - Exibir arvore\n");
    printf("5 - Altura da arvore\n");
    printf("6 - Limpar Arvore\n");
    printf("7 - Sair\n\n");
    printf("Digite uma opcao: ");

}

void i_insere(){
    int n;
    printf("Digite o numero a inserir: ");
    scanf("%d", &n);
    if(insere(n) == -1) printf("Não inserido\n");
    else printf("Inserido\n");
}

int imprimirArvore( arvore *aux, int nivel){
    if(!raiz) printf("arvore vazia\n");
    if(aux){
        imprimirArvore(aux->esquerda, altura(aux->esquerda));
        for(int i = 0; i <= nivel; i++) printf("--");
        printf(">%4d(%d)\n", aux->valor, aux->fator_balanceamento);
        imprimirArvore(aux->direita, altura(aux->direita));
    }
}

void i_remove(){
    arvore *aux;
    int n;
    printf("Digite o numero que deseja remover: ");
    scanf("%d", &n);
    aux = buscar(n);
    if(aux) remover(aux);
    else printf("O numero nao existe na arvore!\n");
}

void i_procura(){
    int n;
    arvore *tmp;
    printf("Digite o numero a procurar: ");
    scanf("%d", &n);
    tmp = buscar(n);
    if(tmp) printf("Elemento encontrado: %d\n", tmp->valor);
    else printf("Elemento nao encontrado!\n");
    tmp = NULL;
}

void i_limpa(){
    if(raiz){
        limparArvore(raiz);
        printf("Arvore limpa!\n");
    }
    else printf("A arvore ja estava limpa!\n");
}