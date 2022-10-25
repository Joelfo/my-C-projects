#include <stdio.h>
#include "metadados.c"
#include "no_interno.c"

void imprime_arquivos() {
    int i;
    //Imprime arquivo de metadados
    FILE *arq_m = fopen("metadados.dat", "rb");
    TMetadados *m = le_metadados(arq_m);
    printf("*** Arquivo de Metadados ***\n");
    imprime_metadados(m);
    fclose(arq_m);

    //Imprime arquivo de índice (nós internos da árvore)
    //A leitura não segue ordem específica -- os nós são lidos na ordem em que foram gravados no arquivo
    FILE *arq_i = fopen("indice.dat", "rb");
    printf("\n\n*** Arquivo de Indice ***\n");
    i = 0;
    TNoInterno *ni = le_no_interno(m->d, arq_i);
    while (ni != NULL) {
        printf("(((Endereco %d)))\n", i * tamanho_no_interno(m->d));
        imprime_no_interno(m->d, ni);
        ni = le_no_interno(m->d, arq_i);
        i += 1;
    }
    fclose(arq_i);

    //Imprime arquivo de dados (nós folha da árvore)
    //A leitura não segue ordem específica -- os nós são lidos na ordem em que foram gravados no arquivo
    FILE *arq_d = fopen("clientes.dat", "rb");
    printf("\n*** Arquivo de Dados ***\n");
    i = 0;
    TNoFolha *nf = le_no_folha(m->d, arq_d);
    while (nf != NULL) {
        printf("(((Endereco %d)))\n", i * tamanho_no_folha(m->d));
        imprime_no_folha(m->d, nf);
        nf = le_no_folha(m->d, arq_d);
        i += 1;
    }
    fclose(arq_d);
}

/*
 * Executa busca em Arquivos utilizando Arvore B+
 * Assumir que ponteiros para NULL têm valor -1
 *
 * chave: chave do cliente que esta sendo buscado
 * nome_arquivo_metadados: nome do arquivo binário que contem os metadados
 * nome_arquivo_indice: nome do arquivo binário de indice (que contem os nohs internos da arvore B+)
 * nome_arquivo_dados: nome do arquivo binário de dados (que contem as folhas da arvore B+)
 *
 * Retorna ponteiro para nó em que a chave está ou deveria estar
 */
//Implementa a parte recursiva da busca em nós internos, se necessário utilizá-la
/*int busca_recursiva_interna(int ind_chave, int d, FILE *indices, TNoInterno *no_buscado){
    //Variável auxiliar para ciclo de repetição
    int i;
    i = 0;
    Testa se o valor da chave na posição i é igual a chave buscada ou se percorreu todas as chaves e executa
     * o ciclo enquanto atender a condição
    while(i < no_buscado->m && no_buscado->chaves[i] != ind_chave) {
        if (no_buscado->chaves[i] > ind_chave) {
            fseek(indices, no_buscado->p[i], SEEK_SET);
            if (no_buscado->aponta_folha == 0) {
                no_buscado = le_no_interno(d, indices);
                return busca_recursiva_interna(ind_chave, d, indices, no_buscado);
            }
        }
        i = i + 1;
        printf("iteração %i rodando\n", i);
    }
    //printf("%i\n", i);
    if(no_buscado->chaves[i] == ind_chave || i == no_buscado->m){

    }
    return 0;


} */
int busca(int chave, char *nome_arquivo_metadados, char *nome_arquivo_indice, char *nome_arquivo_dados)
{
	//TODO: Implementar essa função

	FILE *arq_indice;
	FILE *arq_dados;
	//Variável para armazenar a ordem da árvore ab+
	int ordem_d;
	//Variável auxiliar para ciclos de repetição
	int i;
	//Variável auxiliar para ciclos de repetição
	int j;
	//Variável para armazenar o endereço do nó onde o chave buscada realmente está ou deveria estar
	// (junto com seu registro)
	int end_chave;

	//Variável do tipo TNoInterno para armazenar os valores da leitura de um nó interno(ou um nó raiz)
	TNoInterno *no_interno;
	//Variavel do tipo TNoFolha para armazenar os valores da leitura de um nó folha
	TNoFolha *no_folha;
	//Variavel do tipo TMetadados para armazenar as informações do arquivo de metadados
	TMetadados *meta_info;

	//Abrindo o arquivo de metadados e lendo seu conteúdo por meio da função le_arq_metadados()
	meta_info = le_arq_metadados(nome_arquivo_metadados);
	ordem_d = meta_info->d;


    /* Caso a raiz seja uma folha, a unica possibilidade caso o registro com a chave buscada exista é que ele esteja
     * na raiz, então imprimiremos ela e retornaremos o ponteiro para ela */
    if (meta_info->raiz_folha == 1) {
        arq_dados = fopen(nome_arquivo_dados, "rb");
        fseek(arq_dados, meta_info->pont_raiz, SEEK_SET);
        no_folha = le_no_folha(ordem_d, arq_dados);
        imprime_no_folha(ordem_d, no_folha);
        end_chave = meta_info->pont_raiz;
    } else {
        //Abrindo os arquivos de indices e de dados, respectivamente
        arq_indice = fopen(nome_arquivo_indice, "rb");
        arq_dados = fopen(nome_arquivo_dados, "rb");
        //A leitura começa na raiz da árvore, que está dentro do arquivo de índice
        fseek(arq_indice, meta_info->pont_raiz, SEEK_SET);
        no_interno = le_no_interno(ordem_d, arq_indice);
        //Imprime o primeiro nó em que a chave será buscada, a raiz da árvore b+
        imprime_no_interno(ordem_d, no_interno);
        //Inicializando a variável auxiliar
        i = 0;
        //no_interno->m = quantidade de chaves existentes no nó
        /* O ciclo é repetido enquanto o nó interno não apontar para uma folha, quando ele terminar, teremos um
         * ponteiro para um nó que aponta para uma folha */
        while (no_interno->aponta_folha != 1) {
            while (i < no_interno->m && no_interno->chaves[i] <= chave) {
                i = i + 1;
            }
            fseek(arq_indice, no_interno->p[i], SEEK_SET);
            no_interno = le_no_interno(ordem_d, arq_indice);
            //Cada vez que a busca for realizada em um novo nó, este deve ser impresso
            imprime_no_interno(ordem_d, no_interno);
        }
        /* Ao fim do ciclo while acima, a variável nó_interno aponta para
         * o nó interno que aponta para a raiz onde a chave buscada está ou deveria estar */
        /* Então a busca deve ser realizada nesse nó, para saber em qual posição está o ponteiro que aponta para o nó
         * contendo o registro chave */
        j = 0;
        while (j < no_interno->m && no_interno->chaves[j] <= chave) {
            j = j + 1;
        }
        /* Uma vez encontrada a posição do nó contendo a chave buscada, então imprimiremos esse nó e encerraremos
         * a função retornando o seu endereço */
        fseek(arq_dados, no_interno->p[j], SEEK_SET);
        end_chave = no_interno->p[j];
        no_folha = le_no_folha(ordem_d, arq_dados);
        imprime_no_folha(ordem_d, no_folha);

    }

	return end_chave;
}

int main () {
    //Descomente essa linha de código caso deseje imprimir o conteúdo dos arquivos de entrada para analisar
    //o comportamento da sua implementação

    //imprime_arquivos();

    /* Le chave a ser buscada */
    int chave;

    scanf("%d", &chave);

    //Chama função de busca
    int pont = busca(chave, "metadados.dat", "indice.dat", "clientes.dat");

    //Imprime resultado da função
    printf("RESULTADO DA BUSCA: %d", pont);
}