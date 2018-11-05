/* Alunos: Breno Correa                11711BCC003
*        : Lucas Justino               11711BCC046
         : Tarcisio Junio              11711BCC037
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "automato.h"

int main() {
    char cadeia[200],repete='s';
    int reconheceu,opcao;
    Automato a;
    printf("1 - Ler de arquivo\n2 - Ler expressao regular\n3 - SAIR\nEscolha uma opcao: ");
    scanf("%d",&opcao);
    if(opcao==1)a = carrega_automato("Automato05.dat");
    else if(opcao==2){
        char sequencia[100];
        printf("Digite a expressao regular: \n");
        scanf("%s",sequencia);
        a = trataSeq(sequencia);
        //mostrarAutomato(a);
    }else return 1;
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
