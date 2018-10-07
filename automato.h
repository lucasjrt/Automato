#ifndef DEFINED_AUTOMATO_H
#define DEFINED_AUTOMATO_H
#include <stdio.h>
#include "automato.h"

typedef struct automato* Automato;

Automato carrega_automato(char *caminho);
void carrega_estados(Automato *a, char *estados);
void carrega_alfabeto(Automato *a, char *alfabeto);
//int carrega_inicial(Automato *a, char *inicial);
int carrega_final(Automato *a, char *final);

#endif //
