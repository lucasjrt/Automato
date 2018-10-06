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
    Automato ret = (Automato) malloc(sizeof(struct automato));
    char temp[100];
    //Carrega os estados do autômato
    fscanf(f, "%s", temp);
    if(!strcmp(temp, "estados")) {
        fscanf(f, "%s", temp);
        if(!carrega_estados(&ret, temp) return NULL;
    } else {
        printf("Nao foi encontrado os estados do automato\n");
        return NULL;
    }
    //Carrega o alfabeto do autômato
    fscanf(f, "%s", temp);
    if(!strcmp(temp, "alfabeto")) {
        if(!carrega_alfabeto(&ret, temp)) return NULL;
    } else {

    }
    fscanf(f, "%s", temp);
    if(!carrega_alfabeto())
    return ret;
}

//retorna 1 caso sucesso, 0 caso acontença algum erro
int carrega_estados(Automato *a, char *estados) {
    int i, j = 0;
    char temp[3];

    return 1;
}

int carrega_alfabeto(Automato *a, char *alfabeto) {
    int i, j = 0;
}
