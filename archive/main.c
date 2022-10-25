#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#define TAM (sizeof(int) + (sizeof(char) * 20))

typedef struct Sfunc {
    int cod;
    char nome[20];
} Tfunc;

int tamanho_func(){
    return sizeof(int) + (sizeof(char) * 20);
}

void escreve(FILE *arq, Tfunc *funcionario) {

    printf("Escrevendo...\n");

    fwrite(&funcionario->cod, sizeof(int), 1, arq);
    fwrite(funcionario->nome, sizeof(char), sizeof(funcionario->nome), arq);
}

Tfunc *le_reg(FILE *arq){
    Tfunc *reg;
    //Aloca o espaço de memória para reg;
    reg = (Tfunc*) malloc(sizeof(Tfunc));
    //Lê o código;
    fread(&reg->cod, sizeof(int), 1, arq);
    //Lê o nome;
    fread(reg->nome, sizeof(char), sizeof(reg->nome), arq);
    //printf("%li\n", ftell(arq));
    return reg;
}

void imprime_arq(FILE *arq){
    Tfunc *funcionario;
    funcionario = (Tfunc*) malloc(sizeof(Tfunc));
    printf("Lendo...\n");
    while(!(0 >= fread(&funcionario->cod, sizeof(int), 1, arq))){
        fread(funcionario->nome, sizeof(char), sizeof(funcionario->nome), arq);
        printf("Codigo do funcionario: %i\n", funcionario->cod);
        printf("Nome do funcionario: %s\n", funcionario->nome);
        printf("-----------------------------------------------\n");
    }
    free(funcionario);

}

Tfunc *busca_binaria(int codigo, FILE *arq, int tam_arquivo){
    Tfunc *resultado;
    int cod_atual;
    int meio;
    int inicio = ftell(arq);
    float aux;
    float aux2;

    resultado = (Tfunc*) malloc(sizeof(Tfunc));


    meio = (trunc( (( 1 + inicio)/tamanho_func() + tam_arquivo) / 2) + (tam_arquivo % 2)) + trunc(inicio/tamanho_func());



    printf("o meio e %i na iteracao de tamanho %i\n", meio, tam_arquivo);


    if (tam_arquivo <= 0) {
        free(resultado);
        return NULL;
    }

    fseek(arq, tamanho_func() * (meio - 1), SEEK_SET);
    printf("%li\n", ftell(arq));
    fread(&cod_atual, sizeof(int), 1, arq);
    if (cod_atual == codigo) {
        resultado->cod = cod_atual;
        fread(resultado->nome, sizeof(char), sizeof(resultado->nome), arq);
        return resultado;
    } else if (codigo < cod_atual) {
        fseek(arq, inicio - ftell(arq), SEEK_CUR);
        busca_binaria(codigo, arq, meio - 1);
    } else if (codigo > cod_atual) {
        fseek(arq, tamanho_func(), SEEK_SET);
        printf("%li\n", ftell(arq));
        busca_binaria(codigo, arq, tam_arquivo - meio);
    }

}

void selection_sort_archive(FILE *arq, int tam_arq){
    //Indice do registro no for
    int i;
    //Indice do menor registro
    int i_min;
    //Indice do for para comparar os elementos e encontrar o menor
    int j;
    //Armazena o registro de índice i
    Tfunc *reg_I;
    //Auxiliará na etapa de comparações no arquivo
    Tfunc *reg_Aux;
    //Armazena o registro minimo para aquela iteração
    Tfunc *reg_min;
    rewind(arq);
    for(i = 1; i <= tam_arq; i = i + 1){
        //Fórmula para achar o registro(i): (i - 1) * tam_registro;
        //Iguala o indice j a i
        //j = i;
        //Posiciona o cursor no início do registro i;
        fseek(arq, (i - 1) * tamanho_func(), SEEK_SET);
        reg_I = le_reg(arq);
        //No inicio da iteração, o menor registro é o registro i
        reg_min = reg_I;
        i_min = i;
        //Posiciona o cursor no final de i e no início de i + 1, para percorrer os outros elementos do arquivo
        fseek(arq, i * tamanho_func(), SEEK_SET);
        for(j = i + 1; j <= tam_arq; j = j + 1){
            reg_Aux = le_reg(arq);

            printf("j no byte: %li\n", ftell(arq));


            printf("J na iteracao %i: %i\n", i, j);
            if(reg_min->cod > reg_Aux->cod){
                reg_min = reg_Aux;
                i_min = j;
            }
        }
        //Executa o swap entre o reg_I e o reg_min no ARQUIVO
        //Posiciona o cursor no endereço do registro i
        fseek(arq, (i - 1) * tamanho_func(), SEEK_SET);
        //Sobrescreve o conteúdo do Registro mínimo sobre o conteúdo do registro I
        fwrite(&reg_min->cod, sizeof(int), 1, arq);
        fwrite(reg_min->nome, sizeof(char), sizeof(reg_min->nome), arq);
        printf("O endereco do registro %i foi trocado com o endereco do registro %i\n", i, i_min);
        //Posiciona o cursor no endereço do registro mínimo
        fseek(arq, (i_min - 1) * tamanho_func(), SEEK_SET);
        //Escreve o conteúdo do Registro I no conteúdo do Registro Mínimo
        fwrite(&reg_I->cod, sizeof(int), 1, arq);
        fwrite(reg_I->nome, sizeof(char), sizeof(reg_I->nome), arq);
        //Depois das alterações, posiciona o cursor no início do arquivo
        rewind(arq);
    }
    //todo: Da free em todo mundo que foi utilizado
    free(reg_I);
    free(reg_Aux);
    free(reg_min);
}

int main(){
    Tfunc *func1;
    Tfunc *func2;
    Tfunc *func3;
    Tfunc *func4;
    Tfunc *func5;
    Tfunc *leitura;
    Tfunc *func_busca;
    FILE *arquivo;
    int cod;

    func1 = (Tfunc*) malloc(sizeof(Tfunc));
    func2 = (Tfunc*) malloc(sizeof(Tfunc));
    func3 = (Tfunc*) malloc(sizeof(Tfunc));
    func4 = (Tfunc*) malloc(sizeof(Tfunc));
    func5 = (Tfunc*) malloc(sizeof(Tfunc));
    func1->cod = 9;
    strcpy(func1->nome, "Augusto Oliveira");
    func2->cod = 5;
    strcpy(func2->nome, "Getrudes Adamastora");
    func3->cod = 1;
    strcpy(func3->nome, "Josefino");
    func4->cod = 4;
    strcpy(func4->nome, "Luke Skywalker");
    func5->cod = 93;
    strcpy(func5->nome, "Robocop");

    arquivo = fopen("Funcionarios.dat", "wb+");
    escreve(arquivo, func1);
    escreve(arquivo, func2);
    escreve(arquivo, func3);
    escreve(arquivo, func4);
    escreve(arquivo, func5);
    rewind(arquivo);

    imprime_arq(arquivo);

    selection_sort_archive(arquivo, 5);

    printf("Imprimindo Arquivo Ordenado: \n");
    imprime_arq(arquivo);

    free(func1);
    free(func2);
    free(func3);
    free(func4);
    free(func5);

    fclose(arquivo);

    return 0;
}