#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif

#include "cliente.c"

#include <dirent.h>
#include <string.h>

typedef struct vetor {
    TCliente *cli;
    int congelado;
} TVet;

void imprime_arquivo(char *nome) {
    FILE *arq; //declara ponteiro para arquivo
    // abre arquivo para leitura
    arq = fopen(nome, "r");
    if (arq != NULL) {// checa se não deu erro na abertura do arquivo
        char linha[150];
        fgets(linha, 150, arq);
        while (!feof(arq)) {//testa se chegou ao final do arquivo
            printf("%s", linha);
            fgets(linha, 150, arq);
        }
        fclose(arq); //fecha arquivo
    } else printf("Erro ao abrir arquivo\n");
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


int selecao_substituicao(char *nome_arquivo_entrada, int tam_memoria) {
    FILE *arq_entrada;
    int i;

    arq_entrada = fopen(nome_arquivo_entrada, "r");
    TVet vetorMem[tam_memoria];

    for(i = 0; i < tam_memoria; i++){
        vetorMem[i].cli = (TCliente*) malloc(sizeof(TCliente));
        fscanf(arq_entrada, "%[^;]i", vetorMem[i].cli->cod_cliente);
        fscanf(arq_entrada, "%s", vetorMem[i].cli->nome);

    }

}

int main() {
    int tam_memoria;
    scanf("%d", &tam_memoria);
    int num_part = selecao_substituicao("entrada.txt", tam_memoria);
    for (int i = 1; i < num_part+1; i++) {
        printf("*** %s\n", gera_nome_particao(i));
        imprime_arquivo(gera_nome_particao(i));
    }
}