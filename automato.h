#ifndef DEFINED_AUTOMATO_H
#define DEFINED_AUTOMATO_H
#include <stdio.h>
#include "automato.h"

typedef struct automato* Automato;

Automato carrega_automato(char *caminho);
int carrega_estados(Automato *a, char *estados);
int carrega_alfabeto(Automato *a, char *alfabet);

#endif //
