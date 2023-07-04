#ifndef STRING_H
#define STRING_H
#include <stdio.h>

int tamanho_da_palavra(char *palavra);

int distancia_de_edicao(char *palavra1, int tam_palavra1, char *palavra2, int tam_palavra2);

char *ler_palavra(FILE *fluxo_de_dados);

char *add_char_na_palavra(char *palavra, char char_para_adicionar);

#endif
