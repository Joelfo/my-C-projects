#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#define M 21
//Funções para ler, inicializar, imprimir e escrever na tabela hash.

int tamanho_chave(){
    return sizeof(int);
}
//Salva uma chave no arquivo da tabela hash.
void salva_chave(FILE *tabela, int chave){
    fwrite(&chave, tamanho_chave(), 1, tabela);
}
//Lê uma chave do arquivo de tabela hash.
int *le_chave(FILE *tabela){
    int *chave_lida;
    chave_lida = (int*) malloc(sizeof(int));
    fread(chave_lida, tamanho_chave(), 1, tabela);
    return chave_lida;
}

void inicializa_tabela_hash(FILE *arquivo){
    //Armazena -1, que inicialmente é o valor de todos os compartimentos, mostrando que estão vazios.
    int aux;
    aux = -1;
    //Variavel auxiliar para o ciclo for.
    int i;
    //Insere o valor -1 em todos os compartimentos da tabela.
    for(i = 0; i < M; i++) {
        salva_chave(arquivo, aux);
    }
}

void imprime_tabela_hash(FILE *arquivo){
    //Variavel auxiliar para o ciclo de repetição.
    int i;
    //Variavel auxiliar, armazena a chave lida.
    int *chave_lida;
    //Posiciona o cursor no inicio do arquivo;
    fseek(arquivo, 0, SEEK_SET);
    for(i = 0; i < M; i++){
        chave_lida = le_chave(arquivo);
        printf("|%i|: %i\n", i, *chave_lida);
    }

}

//Funções para INSERÇÃO na Tabela Hash de endereçamento aberto, utiliza como h(x,k) a TENTATIVA LINEAR.

//Calcula h'(x) para x fornecido.
int hash_linha(int x){
    return x % M;
}
//Calcula h(x, k) para x e k fornecidos.
int hash(int x, int k){
    return (hash_linha(x) + k) % M;
}
//Função de busca, considera o método da TENTATIVA LINEAR.
int busca_chave(FILE *tabela, int chave, int k, int *colisoes){
    //Armazena o endereço de hash calculado para a inserção da chave na tentativa k.
    int end_hash;
    end_hash = hash(chave, k);
    //Auxiliar, armazena o valor presente no compartimento onde quer se realizar a inserção
    int *compartimento;
    //Posiciona o cursor para a leitura do compartimento
    fseek(tabela, end_hash * tamanho_chave(), SEEK_SET);
    compartimento = le_chave(tabela);
    //Se K tiver atingido o valor limite, retorna -1, significando OVERFLOW
    if (k >= M){
        return -1;
    }
    //Do contrario irá ler o conteúdo do compartimento
    else {
        //Se encontrar um compartimento vazio ou com a chave buscada, retorna o endereço desse compartimento(LÓGICO)
        if(*compartimento == -1 || *compartimento == chave){
            return end_hash;
        }
        //Do contrário, chama a função de busca novamente, acrescendo em 1 o número da tentativa e de colisões.
        else{
           // printf("Colisao do valor %i com o compartimento[%i]: %i\n", chave, end_hash, *compartimento);
            *colisoes = *colisoes + 1;
            return busca_chave(tabela, chave, k + 1, colisoes);
        }
    }
}

/* Realiza inserção da chave na tabela hash, utilizando o método de TENTATIVA LINEAR.
 * Retorna o número de colisões ocorridas durante a inserção. */
int insere_chave(FILE *tabela, int chave){
    //Armazena o número de colisões ocorridas durante a inserção, é iniciado em 0.
    int num_colisoes;
    num_colisoes = 0;
    //Armazena o endereço onde será realizado a inserção, recebe o valor retornado pela busca.
    int end_A_inserir;
    end_A_inserir = busca_chave(tabela, chave, 0, &num_colisoes);
    /* A inserção será realizada no endereço lógico retornado pela busca, se for OVERFLOW,
     * a busca retorna -1 e a inserção é inválida, do contrário ela é realizada nesse endereço.
     * O número de colisões é acrescido durante a busca. */
    if(end_A_inserir == -1){
        printf("Insercao Inválida(OVERFLOW), M colisoes somadas.\n");
    }
    else{
        printf("Inserção do valor %i feita no compartimento |%i|\n", chave, end_A_inserir);
        fseek(tabela, end_A_inserir * tamanho_chave(), SEEK_SET);
        salva_chave(tabela, chave);
    }
    //printf("\n\n\n");
    printf("Ocorreram mais %i colisoes na insercao do valor %i!\n", num_colisoes, chave);
    return num_colisoes;
}

int main(){
    FILE *arq_tabela;
    arq_tabela = fopen("tabelahashEA.dat", "wb+");
    inicializa_tabela_hash(arq_tabela);
    imprime_tabela_hash(arq_tabela);
    //Armazena o valor da chave a ser inserida.
    int valor_in;
    printf("Digite a chave a ser inserida: ");
    scanf("%i", &valor_in);
    //Armazena o total de colisões ocorridas no cenário.
    int total_colisoes;
    total_colisoes = 0;
    /*Entra em um ciclo de repetição, a primeira chave informada será inserida e o número de colisões será
     * acrescido, assim ocorrerá também com as demais inserções. */
    while(valor_in >= 0){
        total_colisoes = total_colisoes + insere_chave(arq_tabela, valor_in);
        printf("Digite a chave a ser inserida: ");
        scanf("%i", &valor_in);
    }
    printf("\n");
    imprime_tabela_hash(arq_tabela);
    fclose(arq_tabela);
    printf("Numero total de colisoes ocorridas no cenario: %i\n", total_colisoes);
    return 0;
}