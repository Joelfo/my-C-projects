#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif

#include "nomes.c"
#include "cliente.c"

#include <limits.h>
#include <dirent.h>
#include <string.h>

typedef struct vetor {
    TCliente *cli;
    FILE *f;
} TVet;

typedef struct vetorNomes {
    char *nome;
} TVetNomes;

typedef struct No {
    TCliente *vencedor;
    struct No *endvencedor;
    FILE* f;
    struct No *esq;
    struct No *dir;
} TNo;

TNomes *gera_nomes_particoes(int num){
    TVetNomes nomes[num];
    TNomes* lista_nomes_particoes = NULL;
    for (int i = num-1; i >= 0; i--) {
        nomes[i].nome = (char *) malloc(sizeof(char[10]));
        char num_particao[10];
        strcpy(nomes[i].nome, "p");
        sprintf(num_particao, "%d", i+1);
        strcat(nomes[i].nome, num_particao);
        strcat(nomes[i].nome, ".txt");
        lista_nomes_particoes = insere_inicio(lista_nomes_particoes, nomes[i].nome);
    }
    return lista_nomes_particoes;
}

char *gera_nome_particao(int num_part) {
    char *nome_particao = (char *) malloc(sizeof(char[10]));
    char num_particao[10];

    strcpy(nome_particao, "p");
    sprintf(num_particao, "%d", num_part);
    strcat(nome_particao, num_particao);
    strcat(nome_particao, ".txt");

    return nome_particao;
}

void imprime_arquivo(char *name) {
    FILE *arq; //declara ponteiro para arquivo
    // abre arquivo para leitura
    arq = fopen(name, "r");
    if (arq != NULL) {// checa se não deu erro na abertura do arquivo
        char linha[150];
        fgets (linha, 150, arq);
        while (!feof(arq)) {//testa se chegou ao final do arquivo
            printf("%s", linha);
            fgets (linha, 150, arq);
        }
        fclose(arq); //fecha arquivo
    } else printf("Erro ao abrir arquivo\n");
}


TNomes *remove_inicio(TNomes *nome_i){
    TNomes *temp;
    temp = nome_i;
    nome_i = nome_i->prox;
    free(temp);

    return nome_i;
}

TNo *no(TCliente *vencedor_n, TNo *endvencedor_n, FILE* f_n, TNo *esq_n, TNo *dir_n) {
    TNo *no;
    no = (TNo *) malloc(sizeof(TNo));

    no->vencedor = vencedor_n;
    no->endvencedor = endvencedor_n;
    no->f = f_n;
    no->esq = esq_n;
    no->dir = dir_n;

    return no;
}

//Compara dois nós de uma Árvore de Vencedores e retorna o ponteiro para o pai da árvore
//Equivalente a função rearranja
TNo *compara_nos(TNo *esquerda, TNo *direita){
    TNo *pai;
    if(esquerda->vencedor->cod_cliente < direita->vencedor->cod_cliente){
        pai = no(esquerda->vencedor, esquerda, esquerda->f, esquerda, direita);
    }
    else{
        pai = no(direita->vencedor, direita, direita->f, esquerda, direita);
    }
    return pai;
}
//Apaga um valor em uma arvore binária de busca e rearranja a árvore
TNo *apaga_e_rearranja(TNo *raiz){
    if(raiz->dir == NULL){
        TCliente *reg_cliente;
        reg_cliente = le_cliente(raiz->f);
        if(reg_cliente == NULL){
            raiz->vencedor->cod_cliente = INT_MAX;
        }
        else{
            raiz->vencedor = reg_cliente;
        }
        return raiz;
    }
    else{
        if(raiz->endvencedor == raiz->esq){
            raiz->esq = apaga_e_rearranja(raiz->esq);
        }
        else {
            raiz->dir = apaga_e_rearranja(raiz->dir);
        }

        raiz = compara_nos(raiz->esq, raiz->dir);
    }
    return raiz;
}

FILE* intercala_arvbv(FILE** lista_part, int num_part, char *out){
     //Lista contendo os nós folha da árvore
     TNo **lista_nos;
     //Ponteiro para o arquivo de saída(out)
     FILE *f_out;
     //Variaveis auxiliares para ciclo for
     int i;
     //Variavel auxiliar para ciclo while
     int k;
     //Variavel auxiliar armazenando o tamanho da fila
     int tam_fila;
     //Variavel auxiliar para armazenar o vencedor
     TNo *pai;
     //Inicializando a lista de nós folha(alocando a memória)
     lista_nos = (TNo**) malloc(num_part * sizeof(TNo*));
     //Abrindo o arquivo de saída(Modalidade "w")
     f_out = fopen(out, "w");
     //Criando nós folha e os adicionando na lista;
     for(i = 0; i < num_part; i = i + 1){
         lista_nos[i] = no(le_cliente(lista_part[i]), lista_nos[i], lista_part[i], NULL, NULL);
     }
     //Etapa de fila: Montando a Árvore de Vencedores
     /* Enquanto a lista tiver mais de 1 elemento, os 2 primeiros devem ser retirados e o
      * vencedor adicionado ao fim da fila */
     tam_fila = num_part; //O primeiro valor para tam_fila é o numero de partições
     while(tam_fila > 1){
         //pai é resultado da comparação do primeiro e segundo nó da fila
         if(lista_nos[0]->vencedor->cod_cliente < lista_nos[1]->vencedor->cod_cliente){
             pai = no(lista_nos[0]->vencedor, lista_nos[0], lista_nos[0]->f, lista_nos[0], lista_nos[1]);
         }
         else{
             pai = no(lista_nos[1]->vencedor, lista_nos[1], lista_nos[1]->f, lista_nos[0], lista_nos[1]);
         }
         //O primeiro e o segundo nós são removidos e o "shift" é realizado com os demais elementos em 2 posições
         for(i = 0; i < tam_fila - 2; i = i + 1) {
             lista_nos[i] = lista_nos[i + 2];
         }


         lista_nos[tam_fila - 2] = pai;

         //O tamanho da fila é decrescido em 1
         tam_fila = tam_fila - 1;

         //O pai dos dois elementos comparados é adicionado na atual ultima posição da lista



     }




     //Etapa de intercalação das partições(Inscrição no arquivo de saída)
     while(lista_nos[0]->vencedor->cod_cliente != INT_MAX){
         salva_cliente(lista_nos[0]->vencedor, f_out);
         lista_nos[0] = apaga_e_rearranja(lista_nos[0]);
     }

     return f_out;

}

int intercalacao_otima(char *nome_arquivo_saida, int num_p, TNomes *nome_particoes, int f) {
    //TODO Implementar essa função

    //Conterá a lista de partições de tamanho (F-1) a se intercalar a cada iteração da função
    /* Lista(fila) alocada dinamicamente para armazenar os ponteiros para os arquivos FILE de entrada(partições)
     * A memória será alocada mais adiante
     * A varíavel contém um ponteiro para ponteiro para o inicio do vetor de elementos FILE* alocado
     * dinamicamente */
    FILE **lista_p;
    //Lista auxiliar que armazenará os ponteiros FILE* para cada iteração do algorítimo de intercalação
    FILE **lista_aux;

    /* Ponteiro que irá servir para abrir o arquivo de saída e armazenar a
     * última partição ordenada(com todos os elementos) dentro do arquivo. */
    FILE *arq_saida;

    FILE *p_aux;

    TCliente *c_aux;
    //Variaveis auxiliares para percorrer ciclos for
    int i;
    //Variaveis auxiliares para percorrer ciclos for
    int j;
    //Variaveis auxiliares para percorrer ciclos for
    int k;
    //Variaveis auxiliares para percorrer ciclos for
    int h;
    //Variaveis auxiliares para percorrer ciclos for
    int m;
    //Variavel auxiliar, armazena quantos arquivos podem ser lidos em cada etapa, significa (f - 1)
    int leitura;
    leitura = f - 1;
    //Ponteiro(String) auxiliar para receber o nome das partições de saída
    char *part_saida;

    //Variavel auxiliar para armazenar o tamanho da lista(fila) de ponteiros FILE*
    int tam_fila;
    //A variavel é iniciada com o número de partições, que é o tamanho inicial da fila
    tam_fila = num_p;

    //Armazena o número de partições geradas até o fim do arquivo; O número começa em 0
    int p_geradas;
    p_geradas = 0;

    //Alocando a memória para a lista de ponteiros FILE* para as partições
    lista_p = (FILE**) malloc(num_p * sizeof(FILE*));
    //Alocando a memória para a lista auxiliar(Que armazena os valores para ser intercalados na função intercala)
    lista_aux = (FILE**) malloc((leitura) * sizeof(FILE*));


    //Abrindo cada partição e adicionando os ponteiros FILE* na lista(fila) de ponteiros
    for(i = 0; i < num_p; i = i + 1){
        lista_p[i] = fopen(nome_particoes->nome, "r");
        nome_particoes = nome_particoes->prox;
    }
    //Etapa de fila
    /*A cada etapa do ciclo while (f-1) itens serão tirados da lista e
     * 1 item(o arquivo ordenado resultante) será adicionado */

    while(tam_fila > 1){
        if(tam_fila < leitura){
            leitura = tam_fila;
        }
        for (k = 0; k < leitura; k = k + 1) {
            lista_aux[k] = lista_p[k];
        }
        for (h = 0; h < tam_fila - (leitura); h = h + 1) {
            lista_p[h] = lista_p[h + (f - 1)];
        }
        //Caso tam_fila == leitura, tam_fila se tornará 1 aqui
        tam_fila = (tam_fila - (leitura - 1));
        p_geradas = p_geradas + 1;
        part_saida = gera_nome_particao(num_p + p_geradas);
        lista_p[tam_fila - 1] = intercala_arvbv(lista_aux, (leitura), part_saida);

    }

    arq_saida = fopen(nome_arquivo_saida, "w");
    p_aux = freopen(part_saida, "r", lista_p[0]);


    c_aux = le_cliente(p_aux);
    while(c_aux != NULL) {
        salva_cliente(c_aux, arq_saida);
        c_aux = le_cliente(p_aux);
    }
    fclose(arq_saida);
    /* A lista(fila) com os nomes dos arquivos a se intercalar já está em nome_particoes
     * É uma lista encadeada, o tamanho inicial dessa lista pode ser consultado em num_p */

    return p_geradas;

}

int main() {
    int num_particoes;
    int f;
    int num_particoes_intermediarias;
    TNomes *nomes_particoes = NULL;
    //le numero de particoes a serem intercaladas
    scanf("%d", &num_particoes);
    nomes_particoes = gera_nomes_particoes(num_particoes);
    //le f (número total de arquivos a serem manipulados ao mesmo tempo)
    //lembrar que o método usa f-1 arquivos para leitura, e 1 arquivo para saída
    scanf("%d", &f);
    num_particoes_intermediarias = intercalacao_otima("saida.txt", num_particoes, nomes_particoes, f);
    printf("%d\n", num_particoes_intermediarias);
    printf("*** saida.txt\n");
    imprime_arquivo("saida.txt");
}