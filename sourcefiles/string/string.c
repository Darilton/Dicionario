#include "string.h"
#include <stdio.h>
#include <stdlib.h>

#define SPACE_FOR_END_OF_STRING 1
#define SPACE_FOR_NEW_CHAR 1

char *ler_palavra(FILE *fluxo_de_dados){
	char *palavra;

	palavra = malloc(sizeof(char));

	int ch, i = 0;
	
	while((ch = fgetc(fluxo_de_dados)) != '\n'){
		palavra[i++] = ch;
		char *tmp = realloc(palavra, i);

		if(tmp == NULL){
			printf("Error! could not read word\n");
			break;
		}

		palavra = tmp;
	}

	palavra[i] = '\0';

	return palavra;
}

int tamanho_da_palavra(char *palavra){
	int tamanho = 0;
	if(palavra == NULL)
		return tamanho;

	while(palavra[tamanho++] != '\0')
		;

	return tamanho - 1;
}

char *add_char_na_palavra(char *palavra, char char_para_adicionar){
	if(palavra == NULL)
		return NULL;

	char *nova_palavra = malloc(tamanho_da_palavra(palavra) + SPACE_FOR_END_OF_STRING + SPACE_FOR_NEW_CHAR);

	//copia palavra em nova_palavra
	int i = 0;
	while(palavra[i]){
		nova_palavra[i] = palavra[i];
		i++;
	}

	//addiciona o novo character e marca o fim da string
	nova_palavra[i++] = char_para_adicionar;
	nova_palavra[i] = '\0';

	return nova_palavra;
}
