#include <stdlib.h>
#include <stdio.h>
#include "trie.h"
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

	for(int i = 0; i < TAMANHO_DO_ALFABETO; i++)
		temp_no->proxima_letra[i] = NULL;

	return temp_no;
}

Trie *trie_nova_arvore() {return novo_no();};

void trie_inserir_palavra(Trie *raiz, char *palavra){
	int indice, i = 0;

	while(palavra[i] != '\0'){
		indice = char_to_num(palavra[i++]);
		if(!raiz->proxima_letra[indice])
			raiz->proxima_letra[indice] = novo_no();

		raiz = raiz->proxima_letra[indice];
	}

	raiz->fim_palavra = 1;
}

int trie_procurar_palavra(Trie *raiz, char *palavra){
	Trie *ultimo_no_prefixo = trie_procurar_prefixo(raiz, palavra);

	if(ultimo_no_prefixo)
		return ultimo_no_prefixo->fim_palavra;

	else return 0;
		
}

Trie* trie_procurar_prefixo(Trie *raiz, char *palavra){
	int indice, i = 0;
	if(raiz == NULL)
		return 0;

	while(palavra[i] != '\0'){
		indice = char_to_num(palavra[i++]);
		if(!raiz->proxima_letra[indice]){
			return NULL;
		}

		raiz = raiz->proxima_letra[indice];
	}

	return raiz;
	printf("%d", raiz->fim_palavra);
}
