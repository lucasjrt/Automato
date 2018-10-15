#include <stdlib.h>
#include <string.h>
#include "automato.h"
//#define COLOR_RED     "\x1b[31m"
#define COLOR_RED ""
//#define COLOR_GREEN   "\x1b[32m"
#define COLOR_GREEN ""
//#define COLOR_RESET   "\x1b[0m"
#define COLOR_RESET ""

struct delta {
    char estado1[15];
    char transicao;
    char estado2[15];
};

struct automato {
    char estados[30][15]; //Possível armazenar 30 estados com 15 digitos
    int num_estados;
    char alfabeto[36];
    struct delta funcoes[200];
    int num_funcoes;
    char estado_inicial[15];
    char estado_final[30][15];
    int num_final;
};

///Retorna se a cadeia eh aceita pelo automato
int reconhece(Automato a,char *sequencia){
    if(strcmp("E",sequencia)==0){ ///Caso o usuario digite "E", sera interpretado que ele digitou nada, ou seja, cadeia vazia
        sequencia[0]='\0';
    }
    return reconhece_(a,sequencia,a->estado_inicial);
}

///Dado o estado inicial do automato, retorna se a cadeia eh aceita pelo automato
int reconhece_(Automato a,char *sequencia,char *estado_atual){
    //printf("Recebeu a sequencia %s\n",sequencia);
    //printf("Esta no estado %s\n",estado_atual);
    char simbolos_aceitos[36];
    int i, qtd_destinos=0,j=0;
    char **estados_destinos;
    if(sequencia[0]=='\0'){ ///Se a sequencia acabou
        //printf("ACABOU A SEQUENCIA\n");
        if(eh_estado_final(a,estado_atual))return 1;
        else{
            retorna_simbolos(a,estado_atual,simbolos_aceitos);
            if(ja_existe('&',simbolos_aceitos,strlen(simbolos_aceitos))==0){/*printf("Voltando\n");*/return 0;} ///Caso a E-transicao nao seja um simbolo aceito por esse estado e sequencia acabou, entao retorna.
        }
    }
    retorna_simbolos(a,estado_atual,simbolos_aceitos);
    //printf("Simbolos aceitos pelo estado %s: %s\n",estado_atual,simbolos_aceitos);
    if(ja_existe(sequencia[0],simbolos_aceitos,strlen(simbolos_aceitos))==0 && ja_existe('&',simbolos_aceitos,strlen(simbolos_aceitos))==0){/*printf("Voltando\n");*/return 0;} ///Se o caractere nao for aceito pelo estado e simbolos aceitos do estado nao tenha E-fecho entao retorna
    for(i=0;i<strlen(simbolos_aceitos);i++){ ///Percorre simbolos aceitos pelo estado
        j=0;
        if(simbolos_aceitos[i]==sequencia[0] && sequencia[0]!='\0'){ ///Se o caractere da sequencia eh um dos simbolos de transicao deste estado e a sequencia nao esteja vazia
            estados_destinos = aplicar_funcao_ao_estado(a,estado_atual,sequencia[0],&qtd_destinos);
            //printf("Tem %d destinos lendo %c a partir de %s\n",qtd_destinos,sequencia[0],estado_atual);
            do{ ///Faz passar por todas as funcoes de transicao deste estado com o mesmo simbolo de transicao
                //printf("Chamando funcao recursiva, para ir para %s, pois leu %c a partir de %s\n",estados_destinos[j],sequencia[0],estado_atual);
                if(reconhece_(a,(sequencia+1),estados_destinos[j])==1)return 1;
                j++;
            }while(j<qtd_destinos);
        }
        else{
            if(simbolos_aceitos[i]=='&'){ ///Caso o estado aceite E-transicao
                //printf("&&&&&&&&&&&&&&\n");
                estados_destinos = aplicar_funcao_ao_estado(a,estado_atual,'&',&qtd_destinos);
                //printf("Tem %d destinos lendo %c a partir de %s\n",qtd_destinos,'&',estado_atual);
                do{ ///Faz passar por todas as funcoes de transicao deste estado com o simbolo E-transicao
                    //printf("Chamando funcao recursiva, para ir para %s, pois leu %c a partir de %s\n",estados_destinos[j],'&',estado_atual);
                    //printf("Mandando a sequencia %s\n",sequencia);
                    if(reconhece_(a,sequencia,estados_destinos[j])==1)return 1;
                    j++;
                }while(j<qtd_destinos);
            }
        }
    }
    //printf("Retornando final\n");
    return 0;
}

///Dado um estado e um simbolo de transicao, retorna os estados de destino e a quatidade de estados de destinos pelo parametro
char **aplicar_funcao_ao_estado(Automato a, char *estado, char simbolo, int *qtd_destinos){
    int i,j=0;*qtd_destinos=0;
    char **destinos;
    destinos = (char**)malloc(sizeof(char*)*30);
    for(int i=0;i<30;i++){
        destinos[i] = (char*)malloc(sizeof(char)*15);
    }
    for(i=0;i<a->num_funcoes;i++){
        if((strcmp(estado,a->funcoes[i].estado1)==0)&&simbolo==a->funcoes[i].transicao){ ///Se funcao de transicao tenha a origem e simbolo de transicao desejados entao copia o destino para o vetor de destinos
            (*qtd_destinos)++;
            strcpy(destinos[j],a->funcoes[i].estado2);
            j++;
        }
    }
    return destinos;
}

///Retorna 1 caso o estado seja final e 0 caso contrario
int eh_estado_final(Automato a,char *estado){
    int i;
    for(i=0;i<a->num_final;i++){
        if(strcmp(a->estado_final[i],estado)==0)return 1;
    }
    return 0;
}

///Retorna 1 se o caractere esta contido no vetor, 0 caso contrario
int ja_existe(char caractere,char *vetor,int tam){
    int i;
    for(i=0;i<tam;i++){
        if(vetor[i]==caractere)return 1;
    }
    return 0;
}

///Retorna um array dos simbolos que podem ser recebidos a partir deste estado
void retorna_simbolos(Automato a, char *estado, char *simbolos_possiveis){
    int i,j=0;
    simbolos_possiveis[0] = '\0';
    for(i=0;i<a->num_funcoes;i++){
        if(strcmp(a->funcoes[i].estado1, estado)==0){
            if(ja_existe(a->funcoes[i].transicao,simbolos_possiveis,j)==0){
                simbolos_possiveis[j] =  a->funcoes[i].transicao;
                j++;
            }
        }
    }
    simbolos_possiveis[j] = '\0';
}

//Retorna um ponteiro pro autômato, ou NULL caso acontença algum erro.
Automato carrega_automato(char* caminho) {
    FILE* f = fopen(caminho, "r");
    Automato a = (Automato) malloc(sizeof(struct automato));
    char temp[300];
    //Carrega os estados do autômato
    fscanf(f, "%s", temp); //Lê "estados"
    if(!strcmp(temp, "estados")) {
        fscanf(f, "%s", temp); //Lê os estados
        carrega_estados(&a, temp);
        printf(COLOR_GREEN "%d estados carregados: \n" COLOR_RESET, a->num_estados);
        int i;
        for(i = 0; i < a->num_estados; i++) {
            printf("%s%s", a->estados[i], (i < a->num_estados - 1 ? ", ":""));
        }
        printf("\n");
    }
    else {
        printf(COLOR_RED "Os estados do automato nao puderam ser carregados do arquivo\n" COLOR_GREEN);
        return NULL;
    }
    //Carrega o alfabeto do autômato
    fscanf(f, "%s", temp); //Lê "alfabeto"
    if(!strcmp(temp, "alfabeto")) {
        fscanf(f, "%s", temp); //Lê o alfabeto
        if(!carrega_alfabeto(&a, temp)) {
            printf(COLOR_RED "Houve um erro ao carregar o alfabeto do automato\n" COLOR_RESET);
            return NULL;
        }
        printf(COLOR_GREEN "Alfabeto carregado:\n" COLOR_RESET);
        int i;
        for(i = 0; i < strlen(a->alfabeto); i++) {
            printf("%c%s", a->alfabeto[i], (i < strlen(a->alfabeto) - 1 ? ",":""));
        }
        printf("\n");
    }
    else {
        printf(COLOR_RED "Nao foi possivel encontrar o alfabeto do automato no arquivo\n" COLOR_RESET);
        return NULL;
    }
    fscanf(f, "%s", temp); //Lê "delta"
    //Carrega as funcoes delta do automato
    if(!strcmp(temp, "delta")) {
        fscanf(f, "%s", temp); //Lê as funções delta
        if(!carrega_delta(&a, temp)) {
            printf(COLOR_RED "Erro na leitura das funcoes do automato\n" COLOR_RESET);
            return NULL;
        }
        printf(COLOR_GREEN "%d funcoes carregadas:\n" COLOR_RESET, a->num_funcoes);
        int i;
        for(i = 0; i < a->num_funcoes; i++) {
            printf("(%s,%c,%s)\n", a->funcoes[i].estado1, a->funcoes[i].transicao, a->funcoes[i].estado2);
        }
    }
    else {
        printf(COLOR_RED "Nao foi possivel encontrar as funcoes delta no arquivo\n" COLOR_RESET);
        return NULL;
    }
    fscanf(f, "%s", temp); // Lê "inicial"
    //Carrega o estado inicial do automato
    if(!strcmp(temp, "inicial")) {
        fscanf(f, "%s", temp); // Lê os estados iniciais
        if(!carrega_inicial(&a, temp))
            return NULL;
        printf(COLOR_GREEN "Estado inicial carregado:\n" COLOR_RESET "%s\n", a->estado_inicial);
    }
    else {
        printf(COLOR_RED "Nao foi possivel encontrar o estado inicial do automato no arquivo\n" COLOR_RESET);
        return NULL;
    }
    fscanf(f, "%s", temp); // Lê "final"
    //Carrega os estados final do Automato
    if(!strcmp(temp, "final")) {
        fscanf(f, "%s", temp); //Lê os estados finais
        if(!carrega_final(&a, temp))
            return NULL;
        printf(COLOR_GREEN "%d estados finais carregados:\n" COLOR_RESET, a->num_final);
        int i;
        for(i = 0; i < a->num_final; i++) {
            printf("%s%s", a->estado_final[i], (i < a->num_final - 1 ? ", ":""));
        }
        printf("\n");
    }
    else {
        printf(COLOR_RED "Nao foi possivel encontrar o estado final do automato\n" COLOR_RESET);
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
            for(n = 0; n <= strlen(temp); n++)
                (*a)->estados[j][n] = temp[n];

            j++;
        }
    }
    (*a)->num_estados = j;
}

int carrega_alfabeto(Automato *a, char *alfabeto) {
    int i, j = 0;
    for(i = 0; i <= strlen(alfabeto); i++) {
        if(alfabeto[i] != ',' && alfabeto[i] != '\0') {
            (*a)->alfabeto[j] = alfabeto[i];
            if(alfabeto[i+1] != ',' && alfabeto[i+1] != '\0') {
                printf(COLOR_RED "O alfabeto do automato deve ser apenas de caracteres individuais, separados por virgula\n" COLOR_RESET);
                return 0;
            }
            j++;
        }
    }
    return 1;
}

//Retorna 1 se sucesso, 0 se erro
int carrega_delta(Automato *a, char *delta) {
    if(delta[0] != '{') {
        printf(COLOR_RED "As funcoes devem estar entre chaves, no seguinte formato: {([estado origem],[caractere do alfabeto],[estado destino]),([estado origem],[caractere do alfabeto],[estado destino]),...}. Note que nao se usa espaco entre cada funcao\n" COLOR_RESET);
        return 0;
    }
    int j = 1, k, n = 0;
    //j: percorre delta
    //k: percorre o vetor temp
    while(delta[j] != '\0') { //Percorre todo o vetor delta
        if(delta[j] == '(') {
            while(delta[j] != ')') { //Percorre cada tupla
                if(delta[j] != '(') {
                    printf(COLOR_RED "Formato invalido das funcoes no arquivo\n" COLOR_RESET);
                    return 0;
                }
                else
                    j++;
                char temp[15];
                k = 0;
                while(delta[j] != ',') {
                    temp[k] = delta[j];
                    j++;
                    k++;
                }
                temp[k]='\0';
                if(!pertence_estado(*a, temp)) {
                    printf(COLOR_RED "Estado 1: O estado nao %s pertence ao automato\n" COLOR_RESET, temp);
                    return 0;
                }
                atribui((*a)->funcoes[n].estado1, temp);
                j++;
                if(!pertence_alfabeto(*a, delta[j])) {
                    printf(COLOR_RED "O simbolo de transicao deve fazer parte do alfabeto do automato, \"%c\" nao pertence ao alfabeto\n" COLOR_RESET, delta[j]);
                    return 0;
                }
                (*a)->funcoes[n].transicao = delta[j];
                if(delta[j+1] != ',') {
                    printf(COLOR_RED "O simbolo de transicao deve ser apenas um caractere\n" COLOR_RESET);
                    return 0;
                }
                j+=2;
                k = 0;
                while(delta[j] != ')') {
                    temp[k] = delta[j];
                    j++;
                    k++;
                }
                temp[k]='\0';
                if(!pertence_estado(*a, temp)) {
                    printf(COLOR_RED "Estado 2: O estado %s nao pertence ao automato\n" COLOR_RESET, temp);
                    return 0;
                }
                atribui((*a)->funcoes[n].estado2, temp);
                n++;
            }
        }
        else {
            j++;
        }
    }
    if(delta[j-1] != '}') {
        printf(COLOR_RED "As funcoes devem estar entre chaves no arquivo\n" COLOR_RESET);
        return 0;
    }
    (*a)->num_funcoes = n;
    return 1;
}

//Retorna 1 se sucesso, 0 se erro
int carrega_inicial(Automato *a, char *inicial) {
    int i, j;
    for(i = 0; i < (*a)->num_estados; i++) { //Verifica se a palavra existe nos estados do automato
        j = 0;
        while((*a)->estados[i][j] != '\0' && inicial[j] != '\0') { //Equanto a palavra não acabar
            if(inicial[j+1] == ',') {
                printf(COLOR_RED "So e permitido um estado inicial para o automato\n" COLOR_RESET);
                return 0;
            }
            if((*a)->estados[i][j] != inicial[j])
                break;
            if(inicial[j+1] != '\0')
                j++;
            else {
                int n;
                for(n = 0; n < strlen(inicial); n++) {
                    (*a)->estado_inicial[n] = inicial[n];
                }
                j++;
                break;
            }
        }
        if(j >= strlen(inicial))
            break;
    }
    if(!strlen((*a)->estado_inicial)) {
        printf(COLOR_RED "Nenhum estado inicial foi encontrado\n" COLOR_RESET);
        return 0;
    }
    return 1;
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
                    printf(COLOR_RED "Estado final invalido encontrado\n" COLOR_RESET);
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

//Verifica se o estado pertence ao automato
int pertence_estado(Automato a, char *estado) {
    int i;
    for(i = 0; i < a->num_estados; i++) {
        if(!strcmp(a->estados[i], estado))
            return 1;
    }
    return 0;
}

int pertence_alfabeto(Automato a, char simbolo) {
    int i;
    for(i = 0; i < strlen(a->alfabeto); i++) {
        if(a->alfabeto[i] == simbolo)
            return 1;
    }
    return 0;
}

//Atribui o valor de b em a
void atribui(char *a, char *b) {
    int i;
    for(i = 0; i < strlen(b); i++) {
        a[i] = b[i];
        a[i+1] = '\0';
    }
}
