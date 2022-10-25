#include <stdio.h>
int tam_string(char str_enviada[]){
    int tam;


    tam = 0;
    while(str_enviada[tam] != '\0'){
        tam = tam + 1;

    }
    tam = tam + 1;

    return tam;
}

int main(){
    char string[100];
    char caractere;
    int i;
    int resultado;
    i = 0;
    do {
        caractere = getchar();
        string[i] = caractere;
        i = i + 1;

    } while(caractere != '\n');
    string[i - 1] = '\0';

    printf("%s", string);
    resultado = tam_string(string);
    printf("%i", resultado);

    return 0;
}