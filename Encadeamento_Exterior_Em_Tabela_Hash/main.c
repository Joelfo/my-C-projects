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
    //Ponteiros que respectivamente, irão apontar para o arquivo hash e o arquivo de dados.
    FILE *arq_tabhash;
    FILE *arq_dados;

    //Armazena um registro compartimento que é lido do arquivo tabela hash.
    TCompartimento *compartimento_Lido;

    //Armazena um registro cliente que é lido do arquivo de dados(Clientes).
    TCliente *cliente_Lido;
    //Armazena o registro cliente a ser inserido no arquivo de dados, para facilitar a inserção e comparações.
    TCliente *cliente_A_inserir;

    //Armazena o tamanho do registro TCliente
    int tam_RegCliente;
    tam_RegCliente = sizeof(TCliente);
    //Armazena o tamanho do registro TCompartimento;
    int tam_RegCompart;
    tam_RegCompart = sizeof(TCompartimento);
    /* Armazena o resultado do cálculo do endereço LÓGICO onde o ponteiro para o registro deve ser inserido na
     * Tabela Hash. */
    int resultado_hash;
    //Armazena o endereço lógico da inserção do registro desejado no arquivo de dados(Clientes).
    int end_A_inserir;
    //Armazena o endereço do último registro da lista encadeada para o caso de inserção no final dela
    int end_Ultimo;

    //Abrindo ambos os arquivos e alocando seus ponteiros.
    arq_tabhash = fopen(nome_arquivo_hash, "rb+");
    arq_dados = fopen(nome_arquivo_dados, "rb+");
    //Criando o registro do cliente a ser inserido e alocando seu ponteiro;
    cliente_A_inserir = cliente(cod_cli, nome_cli, -1, 1);
    //Aplicando a função de hash, nesse caso o método da divisão.
    resultado_hash = fhash(cliente_A_inserir->cod, m);
    //Posicionando o cursor na posição certa para leitura do compartimento aonde o cliente deve estar inserido.
    fseek(arq_tabhash, resultado_hash * tam_RegCompart, SEEK_SET);
    compartimento_Lido = le_compartimento(arq_tabhash);
    /* Se o compartimento lido(aonde o novo registro deve ser inserido) estiver vazio
     * (seu ponteiro aponta para -1), então teremos que inicializar aquele compartimento e inserir o registro na
     * primeira posição da lista encadeada associada ao compartimento, pois o registro ainda não existe no arquivo */
    if (compartimento_Lido->prox == -1){
        //Percorre o arquivo até o final
        while(!feof(arq_dados)){
            le_cliente(arq_dados);
        }
        //Atribuindo o endereço lógico da inserção para a tabela hash
        end_A_inserir = ftell(arq_dados) / tam_RegCliente;
        /* O compartimento da tabela hash onde o registro deveria estar passará a apontar para a posição onde será
         * inserido no arquivo de dados. */
        fseek(arq_tabhash, resultado_hash * tam_RegCompart, SEEK_SET);
        salva_compartimento(compartimento_hash(end_A_inserir), arq_tabhash);
        //Por fim, o registro é salvo no arquivo de dados
        salva_cliente(cliente_A_inserir, arq_dados);
        cliente_Lido = NULL;
    }
    /* Caso o compartimento não esteja vazio, então iniciaremos a busca pelo registro para saber se ele já existe no
     * arquivo, lembrando de salvar o endereço do primeiro nó(registro) desocupado na lista associada ao compartimento
     * */
    else{
        /* O valor -1 em end_A_inserir vai servir como um flag para saber se foi encontrado algum nó(registro)
         * desocupado */
        end_A_inserir = -1;
        fseek(arq_dados, compartimento_Lido->prox * tam_RegCliente, SEEK_SET);
        cliente_Lido = le_cliente(arq_dados);
        /* A lista encadeada associada ao compartimento é percorrida, até que se encontre um registro com prox igual a
         * NULL(-1) ou se encontre um registro com chave igual a que se deseja inserir, mais tarde essas condições
         * serão testadas, LEMBRANDO que se o a chave do registro for igual, porém o registro estiver marcado como
         * desocupado, a condição não contará, pois aquele registro foi apagado e pode ser sobrescrito. */
        while(cliente_Lido->prox != -1 && (cliente_Lido->cod != cliente_A_inserir->cod || cliente_Lido->ocupado == 0)) {
            //Se encontrar um nó desocupado, salvará o endereço lógico daquele nó(para inserção).
            if (cliente_Lido->ocupado == 0 && end_A_inserir == -1) {
                end_A_inserir = (ftell(arq_dados) - tam_RegCliente) / tam_RegCliente;
            }
            fseek(arq_dados, cliente_Lido->prox * tam_RegCliente, SEEK_SET);
            cliente_Lido = le_cliente(arq_dados);
        }

        //Se encontrou um registro ocupado e com chave igual, não fará nada e retornará -1.
        if(cliente_Lido->cod == cliente_A_inserir->cod && cliente_Lido->ocupado == 1){
            end_A_inserir = -1;
        }
        //Do contrário:
        else{
            //Se um registro com flag desocupado foi encontrado durante a busca, será feita a inserção na posição dele
            if(end_A_inserir > -1){
                //Primeiro, o registro com a flag desocupado deve ser lido para seu ponteiro prox ser copiado e mantido
                fseek(arq_dados, end_A_inserir * tam_RegCliente, SEEK_SET);
                cliente_Lido = le_cliente(arq_dados);
                /* O prox do antigo registro será copiado para o novo, que será então inserido na posição do antigo,
                 * mantendo seu ponteiro próx. */
                cliente_A_inserir->prox = cliente_Lido->prox;
                fseek(arq_dados, end_A_inserir * tam_RegCliente, SEEK_SET);
                salva_cliente(cliente_A_inserir, arq_dados);
            }
            //Se o último registro está com a flag desocupado:
            else if(cliente_Lido->ocupado == 0){
                //A inserção será feita na posição desse registro, quer ele tenha chave igual ou não a do novo registro
                //O procedimento aqui é o mesmo para a inserção no endereço de um registro com flag desocupado
                end_A_inserir = (ftell(arq_dados) - tam_RegCliente) / tam_RegCliente;
                fseek(arq_dados, end_A_inserir * tam_RegCliente, SEEK_SET);
                cliente_Lido = le_cliente(arq_dados);
                /* O prox do antigo registro será copiado para o novo, que será então inserido na posição do antigo,
                 * mantendo seu ponteiro próx. */
                cliente_A_inserir->prox = cliente_Lido->prox;
                fseek(arq_dados, end_A_inserir * tam_RegCliente, SEEK_SET);
                salva_cliente(cliente_A_inserir, arq_dados);
            }
            else{
                /* Guarda o endereço do ultimo registro(nó) da lista encadeada para depois atualizar seu ponteiro para
                 * o endereço lógico do novo registro inserido. */

                end_Ultimo = (ftell(arq_dados) - tam_RegCliente) / tam_RegCliente;
                //Posiciona o cursor no fim do arquivo
                while(!feof(arq_dados)){
                    le_cliente(arq_dados);
                }
                /* Calcula o endereço lógico em que a inserção será realizada e posiciona o cursor a partir dele,
                 * inserindo o registro no final do arquivo */
                end_A_inserir = ftell(arq_dados) / tam_RegCliente;
                salva_cliente(cliente_A_inserir, arq_dados);

                /* Agora devemos atualizar o antigo último registro para que seu próx aponte para o novo
                 * registro inserido, lembrando que o Último registro ja está armazenado em memória com o ponteiro
                 * cliente_Lido apontando para ele, basta atualizá-lo em memória e sobrescrever o antigo registro. */
                cliente_Lido->prox = end_A_inserir;
                //Posicionando o cursor na posição do último registro para sobrescrevê-lo.
                fseek(arq_dados, end_Ultimo * tam_RegCliente, SEEK_SET);
                salva_cliente(cliente_Lido, arq_dados);
            }

        }

    }

    //Liberando os espaços de memória que foram alocados a ponteiros(exceto FILE):
    free(cliente_Lido);
    free(cliente_A_inserir);
    free(compartimento_Lido);
    //Fechando ambos os arquivos para evitar problemas com o salvamento das operações.
    fclose(arq_tabhash);
    fclose(arq_dados);
    return end_A_inserir;
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
    //imprime_arquivos("tabHash.dat", "clientes.dat");

    pont = insere(cod, nome, "tabHash.dat", "clientes.dat", M);
    imprime_arquivos("tabHash.dat", "clientes.dat");
    //Imprime resultado da função
    printf("\nRESULTADO: %d", pont);
}