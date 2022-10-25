#include <limits.h>
#include <stdio.h>

#include "cliente.c"
#include "compartimento_hash.c"

#define M 7

void imprime_arquivos(char *nome_arquivo_hash, char *nome_arquivo_dados) {
    //Imprime arquivo de hash
    printf("TABELA HASH:\n");
    imprime_arquivo_hash(nome_arquivo_hash);

    //Imprime arquivo de dados
    printf("\nDADOS:\n");
    imprime_arquivo_dados(nome_arquivo_dados);
}

/* Executa insercao em Arquivos por Encadeamento Exterior (Hash)
 * cod_cli: chave do cliente que esta sendo inserido
 * nome_cli: nome do cliente a ser inserido
 * nome_arquivo_hash: nome do arquivo que contem a tabela hash
 * nome_arquivo_dados: nome do arquivo onde os dados estao armazenados
 * Retorna o endereco (lógico) onde o cliente foi inserido, ou -1 se nao conseguiu inserir
 */
//Função de Hash que aplica o método da divisão
int fhash(int cod_cli, int m){
    return (cod_cli % m);
}

int insere(int cod_cli, char *nome_cli, char *nome_arquivo_hash, char *nome_arquivo_dados, int m) {
    //TODO: Implementar essa função
    //Ponteiros que respectivamente, irão apontar para o arquivo hash e o arquivo de dados
    FILE *arq_tabhash;
    FILE *arq_dados;

    //Variável para armazenar o endereço lógico do compartimento onde o cliente buscado deve estar
    int pos_comp;
    //Variável auxiliar para armazenar o tamanho do registro compartimento
    int tam_comp;
    //Variável auxiliar para armazenar o tamanho do registro cliente
    int tam_cli;

    //Variável auxiliar para armazenar o endereço LÓGICO aonde for inserido o novo cliente, ela é iniciada com -1(NULL);
    TCompartimento *pos_cliente_in;
    pos_cliente_in = compartimento_hash(-1);
    //Variável para armazenar o endereço lógico do registro cliente no arquivo de dados;
    TCompartimento *pos_cli;
    //Variável para armazenar os valores do cliente a ser inserido no arquivo, para a função salva cliente
    TCliente *cliente_in;
    //Variável auxiliar para comparar tipos cliente e percorrer ciclos de repetição;
    TCliente *aux_cli;

    //Alocando as variáveis de tamanho
    tam_comp = sizeof(TCompartimento);
    tam_cli = sizeof(TCliente);
    cliente_in = cliente(cod_cli, nome_cli, -1, 1);
    //Abrindo ambos os arquivos e fazendo os ponteiros apontarem para eles
    arq_tabhash = fopen(nome_arquivo_hash, "rb+");
    arq_dados = fopen(nome_arquivo_dados, "rb+");
    /*Calcula o endereço lógico do compartimento onde o cliente buscado deve estar inserido, utilizando a função de hash
     * OBS: Esse endereço dará a posição do inicio da lista encadeada associada ao compartimento, se existir */
    pos_comp = fhash(cod_cli, m);
    /* Fazemos o fseek para a posição do compartimento no arquivo utilizando o endereço lógico(multiplicado pelo tamanho
    /  do registro compartimento), logo em seguida o compartimento será lido e armazenado */
    fseek(arq_tabhash, pos_comp * tam_comp, SEEK_SET);
    pos_cli = le_compartimento(arq_tabhash);
    //printf("%i\n", pos_cli->prox);
    /* Caso o compartimento aponte para NULL, será criada uma lista encadeada associada a esse compartimento, e ele
     * passará a apontar para o endereço do inicio dessa lista no arquivo de dados */
    if(pos_cli->prox == -1){
        /* O cliclo irá se repetir até o cursor estar posicionado no fim do último registro escrito, onde o novo
         * será inserido */
        do {aux_cli = le_cliente(arq_dados);}
        while(aux_cli != NULL);
        pos_cliente_in->prox = ftell(arq_dados)/tam_cli;
        //Inserindo o novo registro
        //salva_cliente(cliente_in, arq_dados);
        //fseek(arq_tabhash, pos_comp * tam_comp, SEEK_SET);
        //salva_compartimento(pos_cliente_in, arq_tabhash);
    }
    //Do contrário, iniciaremos a busca pela chave no arquivo de dados(Clientes)
    /*else{
        Posicionando o cursor no endereço do primeiro cliente(nó) da lista encadeada associada ao compartimento
        fseek(arq_dados, pos_cli->prox * tam_cli, SEEK_SET);
        aux_cli = le_cliente(arq_dados);
        while(aux_cli->prox != -1 && aux_cli->cod != cliente_in->cod){
            if(aux_cli->ocupado != 1 && pos_cliente_in->prox != -1){
                pos_cliente_in->prox = (ftell(arq_dados) - tam_cli)/tam_cli;
            }

        }

    }*/
    //Fechando ambos os arquivos para evitar problemas com o salvamento das operações
    fclose(arq_tabhash);
    fclose(arq_dados);
    return INT_MAX;
}

int main() {
    /* Essa função gera a saída que é usada no teste do run.codes. Ela NÃO DEVE SER MODIFICADA */
    int cod;
    char nome[TAM_NOME] = "";
    int pont;

    //le dados a serem inseridos
    scanf("%d", &cod);
    scanf("%s", nome);

    //Imprime arquivos de entrada
    imprime_arquivos("tabHash.dat", "clientes.dat");

    pont = insere(cod, nome, "tabHash.dat", "clientes.dat", M);
    imprime_arquivos("tabHash.dat", "clientes.dat");
    //Imprime resultado da função
    printf("\nRESULTADO: %d", pont);
}