#include <stdio.h>
#include <stdlib.h>


typedef struct NoAB{
    int vallue;
    int key;
    struct NoAB* esq;
    struct NoAB* dir;
} No;

No* busca(No* raiz, int chave_procurada){
    No* aux_no;
    aux_no = raiz;
    if(aux_no->key == chave_procurada){
        return aux_no;
    }
    if(aux_no->key > chave_procurada){
        if (aux_no->esq == NULL) return NULL;
        busca(aux_no->esq, chave_procurada);
    }
    if(aux_no->key < chave_procurada){
        if (aux_no->dir == NULL) return NULL;
        busca(aux_no->dir, chave_procurada);
    }


}

int main(){

    return 0;
}