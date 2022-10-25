#include <stdio.h>
#include <stdlib.h>

void insertion_sort(int vec[], int tam){
    int i;
    int j;
    int aux;


    for(i = 1; i < tam; i = i + 1){
        j = i;
        while(j > 0 && vec[j - 1] > vec[j]){
            aux = vec[j - 1];
            vec[j - 1] = vec[j];
            vec[j] = aux;
            j = j - 1;
        }

    }

}

int main(){
    int vetor[6];
    vetor[0] = 10;
    vetor[1] = 15;
    vetor[2] = 13;
    vetor[3] = 20;
    vetor[4] = 11;
    vetor[5] = 12;

    int i;
    for(i = 0; i < 5; i = i + 1){
        printf("%i > ", vetor[i]);
    }
    printf("\n");

    insertion_sort(vetor, 5);
    printf("Ordenado:\n");
    for(i = 0; i < 5; i = i + 1){
        printf("%i > ", vetor[i]);
    }



    return 0;
}