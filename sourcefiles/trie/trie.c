#include <stdlib.h>
#include <stdio.h>
#include "trie.h"
#include "../string/string.h"
#include "../char_utils/char_utils.h"

#define TAMANHO_DO_ALFABETO 26

struct no{
	int fim_palavra;
	struct no *proxima_letra[TAMANHO_DO_ALFABETO];
};

Trie *trie_procurar_prefixo(Trie *raiz, char *palavra);

Trie *novo_no(){
	Trie *temp_no = malloc(sizeof(struct no));

	if(temp_no ==  NULL){
		printf("Trie: Sem espaco para nova palavra\n");
		return NULL;
	}

	temp_no->fim_palavra = 0;

	//inicializa o ponteiro das letras com NULL
	for(int i = 0; i < TAMANHO_DO_ALFABETO; i++)
		temp_no->proxima_letra[i] = NULL;

	return temp_no;
}

Trie *trie_nova_arvore() { return novo_no(); }

void trie_inserir_palavra(Trie *raiz, char *palavra){
	int indice, i = 0;

	//enquanto nao for o fim da palavra
	while(palavra[i] != '\0'){
		indice = char_to_num(palavra[i++]);

		//se a proxima letra nao existe no vetor cria um novo no para essa letra
		if(!raiz->proxima_letra[indice])
			raiz->proxima_letra[indice] = novo_no();

		raiz = raiz->proxima_letra[indice];
	}

	raiz->fim_palavra = 1;
}

void trie_imprimir_palavras_comecadas_em(Trie *raiz, char *prefixo){
	Trie *ultimo_no_prefixo = trie_procurar_prefixo(raiz, prefixo);

	if(ultimo_no_prefixo){
		if(ultimo_no_prefixo->fim_palavra)
			printf("%s\n", prefixo);

		//procuar pela proxima letra da palavra no vetor
		int i = 0;
		for(; (i < TAMANHO_DO_ALFABETO); i++){
			if(ultimo_no_prefixo->proxima_letra[i]){
				//acrescenta a letra encontrada
				char *novo_prefixo = add_char_na_palavra(prefixo,int_to_char(i));
				trie_imprimir_palavras_comecadas_em(raiz, novo_prefixo);
				free(novo_prefixo);
			}
		}
	}
}

int trie_procurar_palavra(Trie *raiz, char *palavra){
	Trie *ultimo_no_prefixo = trie_procurar_prefixo(raiz, palavra);

	//se o prefixo existe, verifica se é palavra
	if(ultimo_no_prefixo != NULL)
		return ultimo_no_prefixo->fim_palavra;

	else 
		return 0;
		
}

Trie* trie_procurar_prefixo(Trie *raiz, char *palavra){
	int indice, i = 0;
	if(raiz == NULL)
		return 0;

	//enquanto nao for o fim da palavra
	while(palavra[i] != '\0'){
		indice = char_to_num(palavra[i++]);

		//se a proxima letra não existe 
		if(!raiz->proxima_letra[indice]){
			return NULL;
		}

		raiz = raiz->proxima_letra[indice];
	}

	return raiz;
}

void trie_imprimir_arvore(Trie *raiz){
	printf("Palavras na arvore:\n\n");
	
	//Imprime as palavras começadas por cada vogal que existe na trie.
	for(int i = 0; i < TAMANHO_DO_ALFABETO; i++){
		char palavra[] = "";	//palavra para a funcao de impressao

		if(raiz->proxima_letra[i]){
			char *prefixo = add_char_na_palavra(palavra,int_to_char(i));
			trie_imprimir_palavras_comecadas_em(raiz, prefixo);
			free(prefixo);
		}
	}
}
