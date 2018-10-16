#ifndef DEFINED_AUTOMATO_H
#define DEFINED_AUTOMATO_H
#include <stdio.h>
#include "automato.h"

typedef struct automato* Automato;

Automato carrega_automato(char *caminho);
void carrega_estados(Automato *a, char *estados);
int carrega_alfabeto(Automato *a, char *alfabeto);
int carrega_delta(Automato *a, char *delta);
int carrega_inicial(Automato *a, char *inicial);
int carrega_final(Automato *a, char *final);
int pertence_estado(Automato a, char *estado);
int pertence_alfabeto(Automato a, char simbolo);
void atribui(char *a, char *b);
void retorna_simbolos(Automato a, char *estado, char *simbolos_possiveis);
int ja_existe(char caractere,char *vetor,int tam);
int eh_estado_final(Automato a,char *estado_atual);
int reconhece_(Automato a,char *sequencia,char *estado_atual);
int reconhece(Automato a,char *sequencia);
char **aplicar_funcao_ao_estado(Automato a, char *estado, char simbolo, int *qtd_destinos);

#endif //DEFINED_AUTOMATO_H
