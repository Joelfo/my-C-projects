#include <stdio.h>
#include <stdlib.h>

typedef struct sNoA{
    char dado;
    int chave;
    struct sNoA *esq;
    struct SNoA *dir;
} TNoA;

TNoA* busca(TNoA *no, int chave){
    if (no == NULL){
        return NULL;
    }
    else if(chave == no->chave){
        return no;
    }
    else if(chave > no->chave){
        return busca(no->dir, chave);
    }
    else{
        return busca(no->esq, chave);
    }

}

int main(){


    return 0;
}