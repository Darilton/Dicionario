#include "string.h"

char *ler_palavra(FILE *fluxo_de_dados){
	char *palavra;

	palavra = malloc(sizeof(char));

	int ch, i = 1;
	
	while((ch = fgetc(fluxo_de_dados)) != '\n'){
		palavra[i++ - 1] = ch;
		char *tmp = realloc(palavra, sizeof(char)*i);

		if(tmp == NULL){
			printf("Error! could not read word\n");
			break;
		}

		palavra = tmp;
	}

	palavra[i] = '\0';

	return palavra;
}

