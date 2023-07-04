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

int num_ponteiros_validos(Trie *no){
	int num_filhos = 0;

	//se existe ponteiro na posicao n incrementa a variavel
	for(int n = 0; n < TAMANHO_DO_ALFABETO; n++){
		if((no->proxima_letra[n]) != NULL)
			num_filhos++;
	}

	return num_filhos;
}

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

Trie *trie_nova_arvore() { return novo_no(NULL); }

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

Trie *apagar_subprefixo(Trie *raiz, char *palavra, int inicio_subprefixo){
	// apaga a folha
	if(num_ponteiros_validos(raiz)){
		int indice = char_to_num(palavra[inicio_subprefixo]);
		apagar_subprefixo(raiz->proxima_letra[indice], palavra, inicio_subprefixo + 1);
	}
	
	free(raiz);
	return NULL;
}

Trie *trie_inicio_remocao(Trie *raiz, char *palavra, int *inicio_substring){
	int i = 0, profundidade;
	Trie *aux;

	//enquanto nao for o fim da palavra
	while(palavra[i] != '\0'){
		int indice = char_to_num(palavra[i]);

		//se a proxima letra nao existe no vetor cria um novo no para essa letra
		if((raiz->fim_palavra == 1) || (num_ponteiros_validos(raiz) > 1)){
			aux = raiz;
			profundidade = i;
		}

		raiz = raiz->proxima_letra[indice];
		i++;
	}

	//caso a palavra seja um subprefixo
	if(raiz->fim_palavra == 1){
		aux = raiz;
		profundidade = i;
	}

	*inicio_substring = profundidade;
	
	return aux;
}

Trie *trie_remover_palavra(Trie *raiz, char *palavra){
	if(trie_procurar_palavra(raiz,palavra)){
		int profundidade;
		Trie *inicio_remocao = trie_inicio_remocao(raiz, palavra, &profundidade);

		if((profundidade == tamanho_da_palavra(palavra)) && (num_ponteiros_validos(inicio_remocao))){
			printf("Aconteceu\n");
			inicio_remocao->fim_palavra = 0;
		}else{
			int indice = char_to_num(palavra[profundidade]);
			inicio_remocao->proxima_letra[indice] = apagar_subprefixo(inicio_remocao->proxima_letra[indice], palavra, profundidade + 1);
		}
		printf("%s: palavra eliminada com sucesso\n", palavra);
	}else{
		printf("%s: palavra nao existe no dicionario\n", palavra);
	}

	return raiz;
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
