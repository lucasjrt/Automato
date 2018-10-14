/* Alunos: Breno Correa                11711BCC003
*        : Lucas Justino               11711BCC046
         : Tarcisio Junio              11711BCC037
*/
#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include "automato.h"

int main() {
    char cadeia[100];
    char sequencia[20];
    printf("Digite a sequencia: ");
    scanf("%s",&sequencia);
    if(strcmp("E",sequencia)==0){
        printf("%s\n",sequencia);
        sequencia[0]='\0';
    }

    Automato a = carrega_automato("Automato.dat");
    printf("Digite a cadeia para verificar se o automato a reconhece: ");
    scanf("%s", cadeia);
    le_sequencia(a, cadeia);
//    Automato a = malloc(sizeof(struct automato));
    a->estados[0][0] = '1'; a->estados[0][1] = '\0';
    a->estados[1][0] = '2'; a->estados[1][1] = '\0';
    a->estados[2][0] = '3'; a->estados[2][1] = '\0';
    a->estados[3][0] = '4'; a->estados[3][1] = '\0';
    a->estados[4][0] = '5'; a->estados[4][1] = '\0';
    a->estados[5][0] = '\0';
    a->num_estados = 5;
    a->alfabeto[0] = 'a'; a->alfabeto[1] = 'b'; a->alfabeto[2] = 'c'; a->alfabeto[3] = 'd'; a->alfabeto[4] = '\0';
    a->funcoes[0].estado1[0] = '1'; a->funcoes[0].estado1[1] = '\0'; a->funcoes[0].transicao = '&'; a->funcoes[0].estado2[0] = '2'; a->funcoes[0].estado2[1] = '\0';
    a->funcoes[1].estado1[0] = '1'; a->funcoes[1].estado1[1] = '\0'; a->funcoes[1].transicao = 'a'; a->funcoes[1].estado2[0] = '4'; a->funcoes[1].estado2[1] = '\0';
    a->funcoes[2].estado1[0] = '1'; a->funcoes[2].estado1[1] = '\0'; a->funcoes[2].transicao = 'b'; a->funcoes[2].estado2[0] = '4'; a->funcoes[2].estado2[1] = '\0';
    a->funcoes[3].estado1[0] = '1'; a->funcoes[3].estado1[1] = '\0'; a->funcoes[3].transicao = 'c'; a->funcoes[3].estado2[0] = '3'; a->funcoes[3].estado2[1] = '\0';
    a->funcoes[4].estado1[0] = '1'; a->funcoes[4].estado1[1] = '\0'; a->funcoes[4].transicao = '&'; a->funcoes[4].estado2[0] = '5'; a->funcoes[4].estado2[1] = '\0';
    a->funcoes[5].estado1[0] = '2'; a->funcoes[5].estado1[1] = '\0'; a->funcoes[5].transicao = 'a'; a->funcoes[5].estado2[0] = '2'; a->funcoes[5].estado2[1] = '\0';
    a->funcoes[6].estado1[0] = '2'; a->funcoes[6].estado1[1] = '\0'; a->funcoes[6].transicao = 'b'; a->funcoes[6].estado2[0] = '2'; a->funcoes[6].estado2[1] = '\0';
    a->funcoes[7].estado1[0] = '2'; a->funcoes[7].estado1[1] = '\0'; a->funcoes[7].transicao = 'c'; a->funcoes[7].estado2[0] = '2'; a->funcoes[7].estado2[1] = '\0';
    a->funcoes[8].estado1[0] = '2'; a->funcoes[8].estado1[1] = '\0'; a->funcoes[8].transicao = 'd'; a->funcoes[8].estado2[0] = '4'; a->funcoes[8].estado2[1] = '\0';
    a->funcoes[9].estado1[0] = '3'; a->funcoes[9].estado1[1] = '\0'; a->funcoes[9].transicao = 'a'; a->funcoes[9].estado2[0] = '4'; a->funcoes[9].estado2[1] = '\0';
    a->funcoes[10].estado1[0] = '3'; a->funcoes[10].estado1[1] = '\0'; a->funcoes[10].transicao = 'c'; a->funcoes[10].estado2[0] = '5'; a->funcoes[9].estado2[1] = '\0';
    a->funcoes[11].estado1[0] = '4'; a->funcoes[11].estado1[1] = '\0'; a->funcoes[11].transicao = 'd'; a->funcoes[11].estado2[0] = '5'; a->funcoes[9].estado2[1] = '\0';
    a->funcoes[12].estado1[0] = '4'; a->funcoes[12].estado1[1] = '\0'; a->funcoes[12].transicao = '&'; a->funcoes[12].estado2[0] = '3'; a->funcoes[9].estado2[1] = '\0';
    a->num_funcoes = 13;
    a->estado_inicial[0] = '1'; a->estado_inicial[1] = '\0';
    a->estado_final[0][0] = '5'; a->estado_final[0][1] = '\0';
    a->num_final = 1;
    int reconheceu;
    reconheceu = reconhece(a,sequencia,a->estado_inicial);
    if(reconheceu)printf("Reconheceu\n");
    else printf("Nao reconheceu\n");
}

/*
a->estados[0][0] = '1'; a->estados[0][1] = '\0';
    a->estados[1][0] = '2'; a->estados[1][1] = '\0';
    a->estados[2][0] = '3'; a->estados[2][1] = '\0';
    a->estados[3][0] = '\0';
    a->num_estados = 3;
    a->alfabeto[0] = 'a'; a->alfabeto[1] = 'b'; a->alfabeto[2] = 'c'; a->alfabeto[3] = '\0';
    a->funcoes[0].estado1[0] = '1'; a->funcoes[0].estado1[1] = '\0'; a->funcoes[0].transicao = 'a'; a->funcoes[0].estado2[0] = '1'; a->funcoes[0].estado2[1] = '\0';
    a->funcoes[1].estado1[0] = '1'; a->funcoes[1].estado1[1] = '\0'; a->funcoes[1].transicao = 'b'; a->funcoes[1].estado2[0] = '1'; a->funcoes[1].estado2[1] = '\0';
    a->funcoes[2].estado1[0] = '1'; a->funcoes[2].estado1[1] = '\0'; a->funcoes[2].transicao = 'c'; a->funcoes[2].estado2[0] = '1'; a->funcoes[2].estado2[1] = '\0';
    a->funcoes[3].estado1[0] = '1'; a->funcoes[3].estado1[1] = '\0'; a->funcoes[3].transicao = '&'; a->funcoes[3].estado2[0] = '2'; a->funcoes[3].estado2[1] = '\0';
    a->funcoes[4].estado1[0] = '2'; a->funcoes[4].estado1[1] = '\0'; a->funcoes[4].transicao = 'a'; a->funcoes[4].estado2[0] = '3'; a->funcoes[4].estado2[1] = '\0';
    //a->funcoes[5].estado1[0] = '1'; a->funcoes[5].estado1[1] = '\0'; a->funcoes[5].transicao = 'a'; a->funcoes[5].estado2[0] = '2'; a->funcoes[5].estado2[1] = '\0';
    a->num_funcoes = 6;
    a->estado_inicial[0] = '1'; a->estado_inicial[1] = '\0';
    a->estado_final[0][0] = '3'; a->estado_final[0][1] = '\0';
    a->num_final = 1;

*/

/*
a->estados[0][0] = '1'; a->estados[0][1] = '\0';
    a->estados[1][0] = '2'; a->estados[1][1] = '\0';
    a->estados[2][0] = '3'; a->estados[2][1] = '\0';
    a->estados[3][0] = '\0';
    a->num_estados = 3;
    a->alfabeto[0] = 'a'; a->alfabeto[1] = 'b'; a->alfabeto[2] = 'c'; a->alfabeto[3] = '\0';
    a->funcoes[0].estado1[0] = '1'; a->funcoes[0].estado1[1] = '\0'; a->funcoes[0].transicao = 'a'; a->funcoes[0].estado2[0] = '1'; a->funcoes[0].estado2[1] = '\0';
    a->funcoes[1].estado1[0] = '1'; a->funcoes[1].estado1[1] = '\0'; a->funcoes[1].transicao = 'b'; a->funcoes[1].estado2[0] = '1'; a->funcoes[1].estado2[1] = '\0';
    a->funcoes[2].estado1[0] = '1'; a->funcoes[2].estado1[1] = '\0'; a->funcoes[2].transicao = 'c'; a->funcoes[2].estado2[0] = '1'; a->funcoes[2].estado2[1] = '\0';
    a->funcoes[3].estado1[0] = '1'; a->funcoes[3].estado1[1] = '\0'; a->funcoes[3].transicao = '&'; a->funcoes[3].estado2[0] = '2'; a->funcoes[3].estado2[1] = '\0';
    a->funcoes[4].estado1[0] = '2'; a->funcoes[4].estado1[1] = '\0'; a->funcoes[4].transicao = 'a'; a->funcoes[4].estado2[0] = '3'; a->funcoes[4].estado2[1] = '\0';
    //a->funcoes[5].estado1[0] = '1'; a->funcoes[5].estado1[1] = '\0'; a->funcoes[5].transicao = 'a'; a->funcoes[5].estado2[0] = '2'; a->funcoes[5].estado2[1] = '\0';
    a->num_funcoes = 6;
    a->estado_inicial[0] = '1'; a->estado_inicial[1] = '\0';
    a->estado_final[0][0] = '3'; a->estado_final[0][1] = '\0';
    a->num_final = 1;

*/


/*
    a->estados[0][0] = '1'; a->estados[0][1] = '\0';
    a->estados[1][0] = '2'; a->estados[1][1] = '\0';
    a->estados[2][0] = '3'; a->estados[2][1] = '\0';
    a->estados[3][0] = '4'; a->estados[3][1] = '\0';
    a->estados[4][0] = '5'; a->estados[4][1] = '\0';
    a->estados[5][0] = '\0';
    a->num_estados = 5;
    a->alfabeto[0] = 'a'; a->alfabeto[1] = 'b'; a->alfabeto[2] = 'c'; a->alfabeto[3] = 'd'; a->alfabeto[4] = '\0';
    a->funcoes[0].estado1[0] = '1'; a->funcoes[0].estado1[1] = '\0'; a->funcoes[0].transicao = '&'; a->funcoes[0].estado2[0] = '2'; a->funcoes[0].estado2[1] = '\0';
    a->funcoes[1].estado1[0] = '1'; a->funcoes[1].estado1[1] = '\0'; a->funcoes[1].transicao = 'a'; a->funcoes[1].estado2[0] = '4'; a->funcoes[1].estado2[1] = '\0';
    a->funcoes[2].estado1[0] = '1'; a->funcoes[2].estado1[1] = '\0'; a->funcoes[2].transicao = 'b'; a->funcoes[2].estado2[0] = '4'; a->funcoes[2].estado2[1] = '\0';
    a->funcoes[3].estado1[0] = '1'; a->funcoes[3].estado1[1] = '\0'; a->funcoes[3].transicao = 'c'; a->funcoes[3].estado2[0] = '3'; a->funcoes[3].estado2[1] = '\0';
    a->funcoes[4].estado1[0] = '1'; a->funcoes[4].estado1[1] = '\0'; a->funcoes[4].transicao = '&'; a->funcoes[4].estado2[0] = '5'; a->funcoes[4].estado2[1] = '\0';
    a->funcoes[5].estado1[0] = '2'; a->funcoes[5].estado1[1] = '\0'; a->funcoes[5].transicao = 'a'; a->funcoes[5].estado2[0] = '2'; a->funcoes[5].estado2[1] = '\0';
    a->funcoes[6].estado1[0] = '2'; a->funcoes[6].estado1[1] = '\0'; a->funcoes[6].transicao = 'b'; a->funcoes[6].estado2[0] = '2'; a->funcoes[6].estado2[1] = '\0';
    a->funcoes[7].estado1[0] = '2'; a->funcoes[7].estado1[1] = '\0'; a->funcoes[7].transicao = 'c'; a->funcoes[7].estado2[0] = '2'; a->funcoes[7].estado2[1] = '\0';
    a->funcoes[8].estado1[0] = '2'; a->funcoes[8].estado1[1] = '\0'; a->funcoes[8].transicao = 'd'; a->funcoes[8].estado2[0] = '4'; a->funcoes[8].estado2[1] = '\0';
    a->funcoes[9].estado1[0] = '3'; a->funcoes[9].estado1[1] = '\0'; a->funcoes[9].transicao = 'a'; a->funcoes[9].estado2[0] = '4'; a->funcoes[9].estado2[1] = '\0';
    a->funcoes[10].estado1[0] = '3'; a->funcoes[10].estado1[1] = '\0'; a->funcoes[10].transicao = 'c'; a->funcoes[10].estado2[0] = '5'; a->funcoes[9].estado2[1] = '\0';
    a->funcoes[11].estado1[0] = '4'; a->funcoes[11].estado1[1] = '\0'; a->funcoes[11].transicao = 'd'; a->funcoes[11].estado2[0] = '5'; a->funcoes[9].estado2[1] = '\0';
    a->funcoes[12].estado1[0] = '4'; a->funcoes[12].estado1[1] = '\0'; a->funcoes[12].transicao = '&'; a->funcoes[12].estado2[0] = '3'; a->funcoes[9].estado2[1] = '\0';
    a->num_funcoes = 13;
    a->estado_inicial[0] = '1'; a->estado_inicial[1] = '\0';
    a->estado_final[0][0] = '5'; a->estado_final[0][1] = '\0';
    a->num_final = 1;
*/
