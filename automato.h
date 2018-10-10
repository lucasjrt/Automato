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

#endif //
