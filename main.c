/* Alunos: Breno Correa                11711BCC003
*        : Lucas Justino               11711BCC046
         : Tarcisio Junio              11711BCC037
*/
#include <stdlib.h>
#include <string.h>
#include "automato.h"
#ifdef __unix__
  #include <stdio_ext.h>
  #define COLOR_RED         "\e[31m"
  #define COLOR_GREEN       "\e[32m"
  #define COLOR_LIGH_YELLOW "\e[93m"
  #define COLOR_RESET       "\e[0m"
  #define limpar_buffer()   __fpurge(stdin)
#elif defined(_WIN32) || defined(WIN32)
  #include <stdio.h>
  #define COLOR_RED         ""
  #define COLOR_GREEN       ""
  #define COLOR_LIGH_YELLOW ""
  #define COLOR_RESET       ""
  #define limpar_buffer    fflush(stdin)
#endif

int main() {
    char cadeia[200],repete='s';
    int reconheceu;
    Automato a = carrega_automato("Automato.dat");
    if(a == NULL) return 0;
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
}
