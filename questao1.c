#include <stdio.h>
#include <stdlib.h>

typedef struct Nodo{ //Estrutura de um nodo da arvore
    int chave, altura;
    struct Nodo *filhoEsq, *filhoDir;
}nodo;

int max(int a, int b){
    if(a>b) return a;
    return b;
}

int height(nodo *raiz){
    if(raiz == NULL) return -1;
    else return raiz->altura;
}

nodo *criaNodo(int valor){
    nodo *novo = (nodo*)malloc(sizeof(nodo));
    novo->chave = valor;
    novo->altura = 0;
    novo->filhoDir = NULL;
    novo->filhoEsq = NULL;
    return novo;
}

nodo *insere(nodo *raiz, int valor){
    if(raiz == NULL) return criaNodo(valor);
    if(valor > raiz->chave) raiz->filhoDir = insere(raiz->filhoDir, valor);
    else raiz->filhoEsq = insere(raiz->filhoEsq, valor);
    raiz->altura = max(height(raiz->filhoDir), height(raiz->filhoEsq)) + 1;
    return raiz;
}

int verifica(nodo *raiz){
    if(raiz->filhoDir != NULL || raiz->filhoEsq != NULL){
        int balanceamento = raiz->filhoEsq->altura - raiz->filhoDir->altura;
        if(balanceamento>1 || balanceamento<-1) return 0;
        return verifica(raiz->filhoEsq);
        return verifica(raiz->filhoDir);
    }
    else{
        if(raiz->altura > 1 || raiz->altura < -1) return 0;
        return 1;
    }
}

int main(){ //RECEBENDO O VETOR POS ORDER DA ARVORE
    int N, i;
    scanf("%d", &N);
    int *V = (int*)malloc(N*sizeof(int));
    for(i = 0;i<N;i++){
        scanf("%d", &V[i]);
    }

    nodo *raiz = NULL;  //CRIANDO A BST
    for(i=N-1; i>=0; i--){
        raiz = insere(raiz, V[i]); 
    }

    int avl = verifica(raiz);
    if(avl == 0) printf("nao eh avl");
    else printf("eh avl");
    free(V);
    printf("\n");
    return 0;
}