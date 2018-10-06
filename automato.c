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
    char alfabeto[26];
    struct delta funcoes[100][3];
    int estado_inicial;
    int estado_final[20];
};

//Retorna um ponteiro pro autômato, ou NULL caso acontença algum erro.
Automato carrega_automato(char* caminho) {
    FILE* f = fopen(caminho, "r");
    Automato a = (Automato) malloc(sizeof(struct automato));
    char temp[100];
    //Carrega os estados do autômato
    fscanf(f, "%s", temp);
    if(!strcmp(temp, "estados")) {
        fscanf(f, "%s", temp);
        if(!carrega_estados(&a, temp)) return NULL;
        printf("Estados carregados: \n");
        int i;
        for(i = 0; i < a->num_estados; i++) {
            int j = 0;
            while(a->estados[i][j] != '\0') {
                printf("%c", a->estados[i][j]);
                j++;
            }
            if(i < a->num_estados - 1) printf(", ");
        }
        printf("\n");
    } else {
        printf("Os estados do automato nao puderam ser carregados\n");
        return NULL;
    }
    //Carrega o alfabeto do autômato
    fscanf(f, "%s", temp);
    if(!strcmp(temp, "alfabeto")) {
        fscanf(f, "%s", temp);
        if(!carrega_alfabeto(&a, temp)) return NULL;
        int i;
        printf("Alfabeto carregado:\n");
        for(i = 0; i < strlen(a->alfabeto); i++) {
            printf("%c%s", a->alfabeto[i], (i < strlen(a->alfabeto) - 1 ? ",":""));
        }
        printf("\n");
    } else {
        printf("Nao foi possivel encontrar o alfabeto do automato\n");
    }
    fscanf(f, "%s", temp);
    return a;
}

//retorna 1 caso sucesso, 0 caso acontença algum erro
int carrega_estados(Automato *a, char *estados) {
    int i, j = 0, k = 0;
    char temp[15];
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
    return 1;
}

int carrega_alfabeto(Automato *a, char *alfabeto) {
    int i, j = 0;
    for(i = 0; i <= strlen(alfabeto); i++) {
        if(alfabeto[i] != ',') {
            (*a)->alfabeto[j] = alfabeto[i];
            j++;
        }
    }
    return 1;
}
