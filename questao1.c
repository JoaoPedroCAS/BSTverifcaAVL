#include <stdio.h>
#include <stdlib.h>

typedef struct Nodo{ // Estrutura de um nodo da arvore
    int chave, altura;
    struct Nodo *filhoEsq, *filhoDir;
} nodo;

int max(int a, int b){ // Retorna o maior valor
    return (a > b) ? a : b;
}

int height(nodo *raiz){ // Funcao que define a altura
    if(raiz == NULL) return -1;
    else return raiz->altura;
}

nodo *criaNodo(int valor){ // Criando uma BST qualquer
    nodo *novo = (nodo*)malloc(sizeof(nodo));
    novo->chave = valor;
    novo->altura = 0;
    novo->filhoDir = NULL;
    novo->filhoEsq = NULL;
    return novo;
}

nodo *insere(nodo *raiz, int valor){ // Insercao em uma arvore BST
    if(raiz == NULL) return criaNodo(valor);
    if(valor > raiz->chave) raiz->filhoDir = insere(raiz->filhoDir, valor);
    else raiz->filhoEsq = insere(raiz->filhoEsq, valor);
    raiz->altura = max(height(raiz->filhoDir), height(raiz->filhoEsq)) + 1;
    return raiz;
}

int verifica(nodo *raiz){ // Funcao que verifica se a arvore e ou nao AVL
    if(raiz == NULL) return 1;
    int balance = height(raiz->filhoDir) - height(raiz->filhoEsq);
    if(balance > 1 || balance < -1) return 0;
    return verifica(raiz->filhoDir) && verifica(raiz->filhoEsq);
}

void freeBst(nodo *raiz){
    if(raiz == NULL) return;
    freeBst(raiz->filhoEsq);
    freeBst(raiz->filhoDir);
    free(raiz);
    raiz = NULL;
}

int main(){ // Recebendo o vetor pos order da arvore
    int N, i;
    scanf("%d", &N);
    int *V = (int*)malloc(N * sizeof(int));
    for(i = 0; i < N; i++){
        scanf("%d", &V[i]);
    }

    nodo *raiz = NULL;  // Criando a BST
    for(i = N - 1; i >= 0; i--){
        raiz = insere(raiz, V[i]); 
    }

    int avl = verifica(raiz);
    if(avl) printf("eh avl\n");
    else printf("nao eh avl\n");

    free(V);
    freeBst(raiz);
    return 0;
}
