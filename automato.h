#ifndef DEFINED_AUTOMATO_H
#define DEFINED_AUTOMATO_H
#include <stdio.h>
#include "automato.h"

typedef struct automato* Automato;
typedef struct automatoPilha* AutomatoP;

Automato carrega_automato(char *caminho);
void carrega_estados(Automato *a, char *estados);
int carrega_alfabeto(Automato *a, char *alfabeto);
int carrega_delta(Automato *a, char *delta);
int carrega_inicial(Automato *a, char *inicial);
int carrega_final(Automato *a, char *final);
int pertence_estado(Automato a, char *estado);
int pertence_estadoP(AutomatoP a, char *estado);
int pertence_alfabeto(Automato a, char simbolo);
int pertence_alfabetoP(AutomatoP a, char simbolo);
void atribui(char *a, char *b);
void retorna_simbolos(Automato a, char *estado, char *simbolos_possiveis);
int ja_existe(char caractere,char *vetor,int tam);
int eh_estado_final(Automato a,char *estado_atual);
int reconhece_(Automato a,char *sequencia,char *estado_atual);
int reconhece(Automato a,char *sequencia);
char **aplicar_funcao_ao_estado(Automato a, char *estado, char simbolo, int *qtd_destinos);


int retornaMeio(char *sequencia);
Automato trataSeq(char *sequencia);
int iniciaAutomato(Automato *a);
void trataSeq_(Automato a, char *sequencia, char *inicioR, char *fimR);
void trataFechamento(Automato a, char *r1, char *inicioR, char *fimR);
void trataConcatenacao(Automato a, char *r1, char *r2, char *inicioR, char *fimR);
void trataUniao(Automato a, char *r1, char *r2, char *inicioR, char *fimR);
int ehSimbolo(char *sequencia);
void insereEstado(Automato a, char *estado);
void insereTransicao(Automato a, char *origem, char *destino, char transicao);
void trataParenteses(char *sequencia);
void mostrarAutomato(Automato a);
int possuiAlfabeto(Automato a, char caracter,int tam);
void insereEstadoFinal(Automato a,char *estado);
void insereEstadoInicial(Automato a, char *estado);
void preencheAlfabeto(Automato a,char *sequencia);
void inserePonto(char *sequencia);
int possuiAlfabeto(Automato a, char caracter,int tam);

void reverse(char s[]);
void itoal(int n, char s[]);




int possuiEstadoPilha(AutomatoP a,char simbolo, char *estadoAtual);
int reconhecePilha(AutomatoP a,char *sequencia);
int reconhecePilha_(AutomatoP a,char *sequencia,char *estado_atual);
char **aplicar_funcao_ao_estadoP(AutomatoP a, char *estado, char simbolo, int *qtd_destinos);
void retorna_simbolosP(AutomatoP a, char *estado, char *simbolos_possiveis);
AutomatoP criaAutomato();
int eh_estado_finalP(AutomatoP a,char *estado);
void insereTransicaoP(AutomatoP a, const char *origem, const char *destino, const char transicao, const char p_antes, const char *p_depois);
void insereEstadoP(AutomatoP a, const char *estado);
void insereEstadoFinalP(AutomatoP a,const char *estado);
void mostrarAutomatoP(AutomatoP a);
void insereEstadoInicialP(AutomatoP a, char *estado);
#endif //
