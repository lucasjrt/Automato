/* Alunos: Breno Correa                11711BCC003
*        : Lucas Justino               11711BCC046
         : Tarcisio Junio              11711BCC037
*/
#include <stdlib.h>
#include <string.h>
#include "automato.h"
#ifdef __unix__
  #include <stdio_ext.h>
  #define COLOR_RED         "\e[91m"
  #define COLOR_GREEN       "\e[32m"
  #define COLOR_LIGH_YELLOW "\e[93m"
  #define COLOR_RESET       "\e[0m"
  #define COLOR_BLUE        "\e[34m"
  #define limpar_buffer()   __fpurge(stdin)
  #define clear()           system("clear")
#elif defined(_WIN32) || defined(WIN32)
  #include <stdio.h>
  #define COLOR_RED         ""
  #define COLOR_GREEN       ""
  #define COLOR_LIGH_YELLOW ""
  #define COLOR_RESET       ""
  #define COLOR_BLUE        ""
  #define limpar_buffer    fflush(stdin)
  #define clear()           system("cls")
#endif

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
      printf(COLOR_LIGH_YELLOW"Digite a cadeia para verificar se o automato a reconhece: ");
      scanf("%s",cadeia);
      printf(COLOR_RESET);
      reconheceu = reconhece(a,cadeia);
      if(reconheceu)printf(COLOR_GREEN"Aceita\n"COLOR_RESET);
      else printf(COLOR_RED"Nao aceita\n"COLOR_RESET);
      printf(COLOR_LIGH_YELLOW"Quer analisar outra sequencia (s/n)? "COLOR_RESET);
      limpar_buffer();
      scanf("%c",&repete);
    }
    printf(COLOR_LIGH_YELLOW"Trocar de arquivo (s/n)?"COLOR_RESET);
    limpar_buffer();
    scanf("%c", &repete);
  } while(repete!='n');
  clear();
  printf(COLOR_BLUE "Fim da apresentacao!!!\n");
  printf("Integrantes do grupo:\n");
  printf("\tBreno Correa\n");
  printf("\tLucas Justino\n");
  printf("\tTarcisio Junio\n"COLOR_RESET);
  limpar_buffer();
  scanf("%c", &repete);
}
