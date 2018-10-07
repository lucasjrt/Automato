#include <stdlib.h>
#include <string.h>
#include "automato.h"

struct delta {
    int estado1;
    char transicao;
    int estado2;
};

struct automato {
    char estados[30][15]; //Possível armazenar 30 estados com 15 digitos
    int num_estados;
    char alfabeto[36];
    struct delta funcoes[100];
    char estado_inicial;
    char estado_final[30][15];
    int num_final;
};

//Retorna um ponteiro pro autômato, ou NULL caso acontença algum erro.
Automato carrega_automato(char* caminho) {
    FILE* f = fopen(caminho, "r");
    Automato a = (Automato) malloc(sizeof(struct automato));
    char temp[100];
    //Carrega os estados do autômato
    fscanf(f, "%s", temp); //Lê "estados"
    if(!strcmp(temp, "estados")) {
        fscanf(f, "%s", temp); //Lê os estados
        carrega_estados(&a, temp);
        printf("%d estados carregados: \n", a->num_estados);
        int i;
        for(i = 0; i < a->num_estados; i++) {
            int j = 0;
            while(a->estados[i][j] != '\0') {
                printf("%c", a->estados[i][j]);
                j++;
            }
            if(i < a->num_estados - 1) printf(", ");
        }
        printf("\n\n");
    } else {
        printf("Os estados do automato nao puderam ser carregados\n");
        return NULL;
    }
    //Carrega o alfabeto do autômato
    fscanf(f, "%s", temp); //Lê "alfabeto"
    if(!strcmp(temp, "alfabeto")) {
        fscanf(f, "%s", temp); //Lê o alfabeto
        carrega_alfabeto(&a, temp);
        printf("Alfabeto carregado:\n");
        int i;
        for(i = 0; i < strlen(a->alfabeto); i++) {
            printf("%c%s", a->alfabeto[i], (i < strlen(a->alfabeto) - 1 ? ",":""));
        }
        printf("\n\n");
    } else {
        printf("Nao foi possivel encontrar o alfabeto do automato\n");
        return NULL;
    }
    fscanf(f, "%s", temp); //Lê "delta"
    //Carrega as funcoes delta do automato
    fscanf(f, "%s", temp); //Lê as funções delta

    fscanf(f, "%s", temp); // Lê "inicial"
    //Carrega o estado inicial do automato
    fscanf(f, "%s", temp); // Lê os estados iniciais

    fscanf(f, "%s", temp); // Lê "final"
    //Carrega o estado final do Automato
    if(!strcmp(temp, "final")) {
        fscanf(f, "%s", temp); //Lê os estados finais
        if(!carrega_final(&a, temp))
            return NULL;
        printf("Estados finais carregados:\n");
        int i;
        for(i = 0; i < a->num_final; i++) {
            int j = 0;
            while(a->estado_final[i][j] != '\0') {
                printf("%c", a->estado_final[i][j], a->estado_final[i][j]);
                j++;
            }
            if(i < a->num_final - 1) printf(", ");
        }
        printf("\n");
    } else {
        printf("Nao foi possivel encontrar o estado inicial do automato\n");
        return NULL;
    }
    return a;
}

void carrega_estados(Automato *a, char *estados) {
    int i, j = 0, k = 0;
    char temp[16];
    for(i = 0; i <= strlen(estados); i++) {
        if(estados[i] != ',' && estados[i] != '\0') {
            temp[k] = estados[i];
            temp[k+1] = '\0';
            k++;
        } else {
            k = 0;
            int n;
            for(n = 0; n < strlen(temp); n++)
                (*a)->estados[j][n] = temp[n];
            j++;
        }
    }
    (*a)->num_estados = j;
}

void carrega_alfabeto(Automato *a, char *alfabeto) {
    int i, j = 0;
    for(i = 0; i <= strlen(alfabeto); i++) {
        if(alfabeto[i] != ',' && alfabeto[i] != '\0') {
            (*a)->alfabeto[j] = alfabeto[i];
            j++;
        }
    }
}

//Retorna 1 se sucesso, 0 se erro
int carrega_final(Automato *a, char *final) {
    int i = 0, j = 0, k = 0, m = 0; //k: quantidade de estados finais
    char temp[16];
    //i percorre os estados do automato
    //j percore o vetor temp e o de estado final
    //k percorre o vetor de estados finais
    //m percorre o vetor final
    while(1) { //Percore todo o vetor de estados finais recebido
        if(final[m] != ',' && final[m] != '\0') { //Verifica se acabou a palavra lida
            if((*a)->estados[i][j] == final[m]) {  //Verifica se cada caractere são iguais
                temp[j] = final[m];
                temp[j+1] = '\0';
                j++;
                m++;
            } else { //Se os dois estados forem diferentes, avança pro próximo estado
                if(i < (*a)->num_estados) { //Verifica se os estados acabaram
                    i++;
                }
                    else { //Se os estados tiverem acabado, retorna erro
                    printf("Estado final invalido encontrado\n");
                    return 0;
                }
            }
        } else { //Se a palavra acabou, escreve temp em um estado final
            int n;
            for(n = 0; n < strlen(temp); n++) {
                (*a)->estado_final[k][n] = temp[n];
            }
            temp[0] = '\0';
            k++;
            if(final[m] == '\0') break;
            m++;
            j = 0;
            i = 0;
        }
    }
    (*a)->num_final = k;
    return 1;
}
