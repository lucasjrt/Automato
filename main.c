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
    char cadeia[200],repete='s', imprimir, arquivo[50];
    int reconheceu,opcao;
    Automato a;
    do{
      repete = 0;
      clear();
      printf(COLOR_LIGH_YELLOW"1 - Ler de arquivo\n2 - Ler expressão regular\n0 - Sair\nEscolha uma opção: ");
      scanf("%d",&opcao);
      if(opcao==1) {
        do{
          printf(COLOR_LIGH_YELLOW"Nome do arquivo: ");
          limpar_buffer();
          scanf("%s", arquivo);
          printf(COLOR_RESET);
          a = carrega_automato(arquivo);
        } while(a == NULL);
      }
      else if(opcao==2){
          char sequencia[300];
          printf(COLOR_LIGH_YELLOW"Digite a expressão regular: \n");
          scanf("%s",sequencia);
          a = trataSeq(sequencia);
          printf("Imprimir autômato? (s/n): ");
          limpar_buffer();
          scanf("%c", &imprimir);
          if(imprimir == 's')
              mostrarAutomato(a);
          printf(COLOR_RESET);
      }else if(opcao == 0) {
        clear();
        printf(COLOR_BLUE "Fim da apresentação!!!\n");
        printf("Integrantes do grupo:\n");
        printf("\tBreno Corrêa\n");
        printf("\tLucas Justino\n");
        printf("\tTarcisio Junio\n"COLOR_RESET);
        limpar_buffer();
        getchar();
        return 0;
      }
      else {
        printf("Opcao invalida, saindo...\n");
        return 0;
      }
      while(repete!='n'){
        printf(COLOR_LIGH_YELLOW"Digite a cadeia para verificar se o autômato a reconhece: ");
        scanf("%s",cadeia);
        printf(COLOR_RESET);
        reconheceu = reconhece(a,cadeia);
        if(reconheceu)printf(COLOR_GREEN"Aceita\n"COLOR_RESET);
        else printf(COLOR_RED"Não aceita\n"COLOR_RESET);
        printf(COLOR_LIGH_YELLOW"Analisar outra sequência com essa expressão? (s/n): ");
        limpar_buffer();
        scanf("%c",&repete);
        printf(COLOR_RESET);
      }
      printf(COLOR_LIGH_YELLOW"Voltar para o menu? (s/n):"COLOR_RESET);
      limpar_buffer();
      scanf("%c", &repete);
    } while(repete!='n');
  clear();
  printf(COLOR_BLUE "Fim da apresentação!!!\n");
  printf("Integrantes do grupo:\n");
  printf("\tBreno Corrêa\n");
  printf("\tLucas Justino\n");
  printf("\tTarcisio Junio\n"COLOR_RESET);
  limpar_buffer();
  scanf("%c", &repete);
}
