#ifndef TRIE
#define TRIE

typedef struct no Trie;


void trie_inserir_palavra(Trie *raiz, char *palavra);

Trie *trie_nova_arvore();

void trie_remover_palavra(Trie *raiz, char *palavra);

int trie_procurar_palavra(Trie *raiz, char *palavra);

void trie_imprimir_palavras(Trie *raiz);

void trie_imprimir_palavra_comecada_em(Trie *raiz, char *prefixo);

Trie *trie_procurar_prefixo(Trie *raiz, char *palavra);

#endif
