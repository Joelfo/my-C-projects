#include <stdio.h>
 void multiplica_o_vetor(int *vector, int tamanho){
     for(int i = 0; i < tamanho; i++){
         vector[i] *= 10;
     }

}

int main(){
    int vet[10];
    for(int i = 0; i < 10; i++){
        vet[i] = i + 1;
    }
    multiplica_o_vetor(vet, 10);
    for(int i = 0; i < 10; i++){
        printf(":[%i]:", vet[i]);
    }

    return 0;

}
