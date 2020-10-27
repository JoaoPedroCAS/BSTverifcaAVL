#include <stdio.h>
#include <stdlib.h>

typedef struct Nodo{ //Estrutura de um nodo da arvore
    int chave, altura;
    struct Nodo *filhoEsq, *filhoDir;
}nodo;

int max(int a, int b){ // RETORNA O MAIOR VALOR
    if(a>b) return a;
    return b;
}

int height(nodo *raiz){ //FUNCAO QUE DEFINE A ALTURA
    if(raiz == NULL) return -1;
    else return raiz->altura;
}

nodo *criaNodo(int valor){ //CRIANDO UMA BST QUALQUER
    nodo *novo = (nodo*)malloc(sizeof(nodo));
    novo->chave = valor;
    novo->altura = 0;
    novo->filhoDir = NULL;
    novo->filhoEsq = NULL;
    return novo;
}

nodo *insere(nodo *raiz, int valor){ //INSERCAO EM UMA ARVORE BST
    if(raiz == NULL) return criaNodo(valor);
    if(valor > raiz->chave) raiz->filhoDir = insere(raiz->filhoDir, valor);
    else raiz->filhoEsq = insere(raiz->filhoEsq, valor);
    raiz->altura = max(height(raiz->filhoDir), height(raiz->filhoEsq)) + 1;
    return raiz;
}

int verifica(nodo *raiz, int veri){ //FUNCAO QUE VERIFICA SE A ARVORE E OU NAO AVL, SE QUALQUER NODO ESTIVER DESBALANCEADO A BST NAO EH AVL
    if(raiz == NULL) return veri;
    if(height(raiz->filhoDir) - height(raiz->filhoEsq) > 1){
        return 1;
    }
    else if(height(raiz->filhoEsq) - height(raiz->filhoDir) > 1){
        return 1;
    }
    else{
        return verifica(raiz->filhoDir, veri);
        return verifica(raiz->filhoEsq, veri);
    }
}

void freeBst(nodo *raiz){
    if(raiz == NULL) return;
    freeBst(raiz->filhoEsq);
    freeBst(raiz->filhoDir);
    free(raiz);
    raiz = NULL;
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

    int avl = verifica(raiz, 0);
    if(avl == 1) printf("nao eh avl");
    else printf("eh avl");
    free(V);
    freeBst(raiz);
    printf("\n");
    return 0;
}