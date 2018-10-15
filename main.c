/* Alunos: Breno Correa                11711BCC003
*        : Lucas Justino               11711BCC046
         : Tarcisio Junio              11711BCC037
*/
#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include "automato.h"

int main() {
    char cadeia[100],repete='s';
    int reconheceu;
    Automato a = carrega_automato("Automato03.dat");
    while(repete=='s'){
        printf("Digite a cadeia para verificar se o automato a reconhece: ");
        scanf("%s",cadeia);
        reconheceu = reconhece(a,cadeia);
        if(reconheceu)printf("Aceita\n");
        else printf("Nao aceita\n");
        printf("Quer analisar outra sequencia (s/n)? ");
        getchar();
        scanf("%c",&repete);
    }
}
