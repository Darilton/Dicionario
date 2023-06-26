#ifndef STRING_H
#define STRING_H
#include <stdio.h>
#include <stdlib.h>

int tamanho_da_palavra(char *palavra);

char *ler_palavra(FILE *fluxo_de_dados);

char *add_char_na_palavra(char *palavra, char char_para_adicionar);

#endif
