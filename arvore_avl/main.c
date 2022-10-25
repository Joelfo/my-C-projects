#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct sNoA {
    int chave;
    struct sNoA *esq;
    struct sNoA *dir;
} TNoA;
//Calcula a altura da subarvore direita de um no
int calcula_altura(TNoA *no){
    if (no == NULL){
        return 0;
    }

    int altura_do_no;
    int altura_direita;
    int altura_esquerda;
    int nivel;
    altura_do_no = 1;
    //nivel = altura_do_no - 1;
    altura_direita = calcula_altura(no->dir);
    altura_esquerda = calcula_altura(no->esq);

    if (altura_esquerda >= altura_direita) {
        altura_do_no = altura_do_no + altura_esquerda;
        return altura_do_no;
    }

    altura_do_no = altura_do_no + altura_direita;
    return altura_do_no;



}

//Calcula o fator de balanceamento de uma no sendo ele a raiz de uma árvore binaria de busca
int calcula_fb(TNoA *no) {

    int fator_de_balanceamento;
    int altura_direita;
    int altura_esquerda;

    altura_direita = calcula_altura(no->dir);
    altura_esquerda = calcula_altura(no->esq);
    fator_de_balanceamento = altura_direita - altura_esquerda;

    return fator_de_balanceamento;

}

int ehAVL(TNoA *raiz) {

    if (raiz == NULL){
       return 1;
    }

    int filho_esquerdo;
    int filho_direito;
    int fator_b;
    filho_esquerdo = ehAVL(raiz->esq);
    filho_direito = ehAVL(raiz->dir);
    if (filho_esquerdo == 0 || filho_direito == 0){
        return 0;
    }

    fator_b = calcula_fb(raiz);
    if(fator_b > -2 && fator_b < 2){
        return 1;
    }

    return 0;




    //Ela recebe a raiz da árvore
    //Ela retorna um inteiro (1 se a árvore for AVL, 0 caso contrário)

}

void imprime(TNoA *nodo, int tab) {
    for (int i = 0; i < tab; i++) {
        printf("-");
    }
    if (nodo != NULL) {
        printf("%d\n", nodo->chave);
        imprime(nodo->esq, tab + 2);
        printf("\n");
        imprime(nodo->dir, tab + 2);
    } else printf("vazio");
}

TNoA *insere(TNoA *no, int chave) {
    if (no == NULL) {
        no = (TNoA *) malloc(sizeof(TNoA));
        no->chave = chave;
        no->esq = NULL;
        no->dir = NULL;
    } else if (chave < (no->chave))
        no->esq = insere(no->esq, chave);
    else if (chave > (no->chave)) {
        no->dir = insere(no->dir, chave);
    } else {
        printf("Inserção inválida! ");
        exit(1);
    }
    return no;
}

int main(void) {

    /* A função main lê os dados de entrada, cria a árvore e chama a função solicitada no problema
     * depois imprime o resultado solicitado
     * ELA NÃO DEVE SER MODIFICADA
     * */
    TNoA *raiz;
    raiz = NULL;

    char l[100];
    char delimitador[] = "-";
    char *ptr;
    int valor;

    /* lê valores para criar a arvore
     * valores devem ser informados separados por traço
     * exemplo: 1-3-5-2-7-9-21-6 */
    scanf("%s", l);
    //quebra a string de entrada
    ptr = strtok(l, delimitador);
    while(ptr != NULL) {
        valor = atoi(ptr);
        raiz = insere(raiz, valor);
        ptr = strtok(NULL, delimitador);
    }

    //Chama função
    printf("%d", ehAVL(raiz));
};