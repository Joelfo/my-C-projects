#include <limits.h>
#include <stdlib.h>

#include "cliente.c"

void imprime_arquivo(char *nome_arquivo_dados) {
    FILE *in = fopen(nome_arquivo_dados, "rb");
    TCliente *cliente = le_cliente(in);
    int pos = 0;
    while (cliente != NULL) {
        printf("[%3d] %3d, %12s, %3d, %8s\n", pos, cliente->cod, cliente->nome, cliente->prox,
               (cliente->ocupado? "OCUPADO" : "LIBERADO"));
        pos++;
        cliente = le_cliente(in);
    }
    fclose(in);
}

int hash(int cod_cli) {
    return cod_cli % 7;
}

void excluiHashk(char *nome_arquivo, int k) {
    //TODO: Implementar essa função
    //Abrindo o arquivo para a manipulação, no modo rb+(Leitura e escrita, com o cursor no inicio do arquivo).
    FILE *arquivo;
    arquivo = fopen(nome_arquivo, "rb+");
    //Variavel auxiliar, armazena registros cliente lidos do arquivo
    TCliente *cliente_Lido;
    //Variavel auxiliar, armazena o tamanho do registro cliente.
    int tam_cliente;
    tam_cliente = tamanho_cliente();
    /* Varíavel auxiliar, armazena o ponteiro para o próximo registro a ser lido, se for -1 indica o fim da lista
     * Associada ao endereço base */
    int i;
    i = k;

    // O primeiro valor de i é o valor de hash k
    do {
        /* Posiciona o cursor no endereço i(físico), que significa o endereço do primeiro registro associado a k
         * Ou o proximo registro da lista encadeada.
         * Após posicionar o cursor, inicia a leitura.*/
        fseek(arquivo, i * tam_cliente, SEEK_SET);
        cliente_Lido = le_cliente(arquivo);
        //Cada cliente percorrido e/ou lido será impresso.
        imprime_cliente(cliente_Lido);
        if(cliente_Lido == NULL) {
            return;
        }
        //Se o hash da chave conferir com k, o flag "ocupado" é setado para 0 e o registro é reescrito no arquivo.
        if (hash(cliente_Lido->cod) == k) {
            cliente_Lido->ocupado = 0;
            fseek(arquivo, ftell(arquivo) - tam_cliente, SEEK_SET);
            salva_cliente(cliente_Lido, arquivo);
        }
        i = cliente_Lido->prox;
    } while(i > -1);
    //Fechando o arquivo para evitar problemas com o stream
    fclose(arquivo);
    //Liberando os espaços alocados dinamicamente(Boa prática!)
    free(cliente_Lido);
}

int main() {
    /* Essa função gera a saída que é usada no teste do run.codes. Ela NÃO DEVE SER MODIFICADA */
    int k;

    //Imprime arquivos de entrada
    //imprime_arquivo("tabHash.dat");

    //le o valor de k
    scanf("%d", &k);
    printf("REGISTROS EXAMINADOS:\n");
    excluiHashk("tabHash.dat", k);
    printf("ARQUIVO FINAL:\n");
    imprime_arquivo("tabHash.dat");
}