#include "string.h"
#include "../char_utils/char_utils.h"
#include <stdio.h>
#include <stdlib.h>

#define SPACE_FOR_END_OF_STRING 1
#define SPACE_FOR_NEW_CHAR 1

int min(int a, int b, int c){
    if (a < b && a < c) {
        return a;
    }
    else if (b < a && b < c) {
        return b;
    }
    else {
        return c;
    }
}

int encontrar_char_valido(FILE *fluxo_de_dados){
	int ch;
	while(!(is_valid_char(ch = fgetc(fluxo_de_dados)))){
		if(ch == EOF)
			return EOF;
	}
	return ch;
}

char *ler_palavra(FILE *fluxo_de_dados){
	char *palavra;	int ch, i = 0;
	int char_valido_encontrado = 0;

	//se nao existir nenhuma palavra 
	if(!(ch = encontrar_char_valido(fluxo_de_dados)))
		return NULL;
	
	palavra = malloc(sizeof(char));

	//le enquanto for um caracter valido
	while((is_valid_char(ch))){
		char_valido_encontrado = 1;
		palavra[i++] = char_to_lower(ch);
		
		//adiciona espaco para o proximo caracter
		char *tmp = realloc(palavra, i);

		if(tmp == NULL){
			printf("Error! could not read word\n");
			break;
		}

		ch = fgetc(fluxo_de_dados);
		palavra = tmp;
	}

	if(char_valido_encontrado){
		palavra[i] = '\0';
		return palavra;
	}
	free(palavra);

	return NULL;
}

int tamanho_da_palavra(char *palavra){
	int tamanho = 0;
	if(palavra == NULL)
		return tamanho;

	while(palavra[tamanho++] != '\0')
		;

	return tamanho - 1;
}

//naive levenshtein distance with O(3**max(m,n))
int distancia_de_edicao(char *palavra1, int tam_palavra1, char *palavra2, int tam_palavra2){
	if(tam_palavra1 == 0)
		return tam_palavra2;

	if(tam_palavra2 == 0)
		return tam_palavra1;
	
	//se os ultimos caracteres fore iguais nao contribuem na distancia de edicao
	if(palavra1[tam_palavra1 - 1] == palavra2[tam_palavra2 - 1])
		return distancia_de_edicao(palavra1, tam_palavra1 - 1, palavra2, tam_palavra2 - 1);
	
	//se nao verifica os 3 casos e retorna o menor deles
	return 1 + min(distancia_de_edicao(palavra1, tam_palavra1 - 1, palavra2, tam_palavra2 - 1),     //insercao
		   distancia_de_edicao(palavra1, tam_palavra1, palavra2, tam_palavra2 - 1),		//remocao
		   distancia_de_edicao(palavra1, tam_palavra1 - 1, palavra2, tam_palavra2)		//troca
		   );
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
