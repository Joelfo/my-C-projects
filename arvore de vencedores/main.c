#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include "funcoes cliente.c"

typedef struct No{
    TCliente *vencedor;
    struct No *endvencedor;
    FILE *f;
    struct No *pai;
    struct No *dir;
    struct No *esq;
} TNo;

//Função auxiliar para criação de nós(Para adicionar na fila)
TNo *no(TCliente *c_vencedor, TNo *n_edvencedor, FILE *n_f, TNo *n_pai, TNo *n_dir, TNo *n_esq){
    TNo *no_criado;
    //Aloca espaço para o nó criado
    no_criado = (TNo*) malloc(sizeof(TNo));
    //Atribui os valores a cada campo do nó
    no_criado->vencedor = c_vencedor;
    no_criado->endvencedor = n_edvencedor;
    no_criado->f = n_f;
    no_criado->pai = n_pai;
    no_criado->dir = n_dir;
    no_criado->esq = n_esq;

    //Retorna o ponteiro para o nó criado
    return no_criado;
}

//Compara dois códigos de clientes vencedores de um nó e retorna o nó com o menor código.
void *rearranja(TNo *esquerda, TNo *direita) {
    if (esquerda->vencedor->cod_cliente < direita->vencedor->cod_cliente) {
        esquerda->pai->vencedor = esquerda->vencedor;
        esquerda->pai->endvencedor = esquerda;
        esquerda->pai->f = esquerda->f;
    } else if (direita->vencedor->cod_cliente <= esquerda->vencedor->cod_cliente) {
        direita->pai->vencedor = direita->vencedor;
        direita->pai->endvencedor = direita;
        direita->pai->f = direita->f;
    }

}

//Função para apagar um elemento da arvore binaria de vencedores e rearrumá-la
TNo *apaga_e_rearranja(TNo *raiz){
    //Se for o nó folha, o vencedor desse nó se torna o proximo Cliente do arquivo
    if(raiz->dir == NULL){
        TCliente *aux;
        aux = le_cliente(raiz->f);
        //Se não houverem mais clientes para serem lidos, a função retornará NULL
        //Nesse caso, a chave do cliente da raiz passa a ser int max
        if(aux == NULL){
            raiz->vencedor->cod_cliente = INT_MAX;
        }
        /* Se ainda houverem registros a serem lidos no arquivo, o "vencedor" recebe a
        leitura do próximo cliente(que já está armazenado na variavel aux) */
        else {
            raiz->vencedor = aux;
        }
        return raiz;
    }
    /*Se não for um nó folha, será chamada a função recursivamente até encontrar um.
    Então a substituição ocorrerá em nó por nó, rearranjando a árvore */
    else {
        //Se o vencedor estiver na subarvore da esquerda, chamaremos a função recursivamente para sua raiz
        if(raiz->endvencedor == raiz->esq){
            raiz->esq = apaga_e_rearranja(raiz->esq);
        }
        //Se estiver na direita, faremos o mesmo, para a subárvore esquerda.
        else {
            raiz->dir = apaga_e_rearranja(raiz->dir);
        }
        rearranja(raiz->esq, raiz->dir);
    }
    return raiz;
}

void arvore_de_vencedores(char *lista_n[], int num_arq, char *out_nome){
    //Lista contendo os ponteiros para os arquivos(partições)
    FILE *particoes[num_arq];
    //Ponteiro para o arquivo de saída
    FILE *out;
    //Variaveis para as iterações for e while
    int i;
    int j;
    int k;
    int h;
    //Variavel auxiliar para as comparações na fila
    int prox;
    //Variavel auxiliar(ponteiro) para a criação de nós pai na árvore de vencedores
    TNo *n_pai;
    //Variavel auxiliar(ponteiro) que apontará para a raiz da árvore de vencedores
    TNo *raiz_v;
    //Variavel que armazenará o tamanho da lista fila, para facilitar a iteração na fila
    int tam_fila;
    //Lista de nós(fila), seu tamanho é o numero de partições(arquivos de entrada)
    TNo *fila[num_arq];

    //Iteração para abrir cada uma das partições
    for(i = 0; i < num_arq; i = i + 1){
        particoes[i] = fopen(lista_n[i], "r");
    }
    //Abrindo arquivo de saída
    out = fopen(out_nome, "w");
    //todo: Iniciando a montagem da árvore de vencedores
    //For para criar os nós folha na fila de nós
    //OBS: Cada nó folha representa o topo da pilha da partição de entrada referente àquele nó
    for(j = 0; j < num_arq; j = j + 1) {
        //Cria o no e retorna o ponteiro para a lista de nós
        fila[j] = no(le_cliente(particoes[j]), fila[j], particoes[j], NULL, NULL, NULL);
        printf("%i\n", fila[j]->vencedor->cod_cliente);
    }

    k = 0;
    tam_fila = num_arq;
    //Executa o processamento da fila até que a raiz esteja na posição [0] e o tamanho da fila seja 1
    //Ao fim do ciclo o while, o valor de n_pai é a raiz da árvore de vencedores
    while(tam_fila > 1){
        //Compara os dois elementos no inicio da fila para criar o nó pai
        if(fila[0]->vencedor->cod_cliente < fila[1]->vencedor->cod_cliente){
            n_pai = no(fila[0]->vencedor, fila[0], fila[0]->f, NULL, fila[0], fila[1]);
        }
        else{
            n_pai = no(fila[1]->vencedor, fila[1], fila[1]->f, NULL, fila[0], fila[1]);
        }

        fila[0]->pai = n_pai;
        fila[1]->pai = n_pai;

        //Fazendo a fila andar(de 2 em 2 posições)
        for(k = 0; k < tam_fila - 2; k = k + 1){
        fila[k] = fila[k + 2];
        }
        //Insere o pai no "fim" da fila
        fila[tam_fila - 2] = n_pai;
        tam_fila = tam_fila - 1;
    }
    /* Após o fim do ciclo While, a árvore de vencedores foi montada, agora basta iterar sobre ela escrevendo
     sua raiz no arquivo até que a raiz retornada seja INT_MAX */
    //todo: Árvore de vencedores já foi montada
    printf("Chave da Raiz: %i\n", n_pai->vencedor->cod_cliente);
    //O ponteiro raiz receberá o nó pai, que nesse ponto da execução é a raiz da árvore
    raiz_v = n_pai;
    /* Itera sobre a árvore, pegando a raiz e salvando-a no arquivo,
     a cada iteração a raiz é apagada e a árvore é rearranjada; */
    while(raiz_v->vencedor->cod_cliente != INT_MAX){
        salva_cliente(raiz_v->vencedor, out);
        raiz_v = apaga_e_rearranja(raiz_v);
    }


}



int main(){
    char *lista[2] = {"p1.txt", "p2.txt"};
    char out[] = "clientes.txt";
    FILE *teste;

    arvore_de_vencedores(lista, 2, out);

    return 0;
}
