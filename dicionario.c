#include <stdio.h>
#include <stdlib.h>

#if defined(_WIN32) || defined(_WIN64)
#	include "sourcefiles\\string\\string.h"
#	include "sourcefiles\\trie\\trie.h"
#	include "sourcefiles\\menu_utils\\menu_utils.h"
#	define LIMPAR_TELA system("cls")
#	define DICIONARIO "resources\\dicionario.dat"
#else
#	include "sourcefiles/string/string.h"
#	include "sourcefiles/trie/trie.h"
#	include "sourcefiles/menu_utils/menu_utils.h"
#	define LIMPAR_TELA system("clear")
#	define DICIONARIO "resources/dicionario.dat"
#endif

void carregar_trie_com_ficheiro(Trie *arvore, FILE *ficheiro);

int main(){
	char *palavra;
	int opcao;

	Trie *arvore = trie_nova_arvore();

	FILE *dicionario = fopen(DICIONARIO, "r");

	carregar_trie_com_ficheiro(arvore, dicionario);

	printf("Bem vindo\n");

	do{
		apresentar_menu();

		opcao = ler_opcao();
		getchar();

		if((opcao > 0) && (opcao <= 10))
			LIMPAR_TELA;

		switch(opcao){
			case 1:
				printf("INSERCAO\n\n");
				printf("Insira a palavra que deseja guardar neste dicionario\n");
				printf("Palavra: ");
				palavra = ler_palavra(stdin);

				if(trie_procurar_palavra(arvore, palavra))
					printf("%s: palavra ja existe no dicionario!\n", palavra);
				else{
					trie_inserir_palavra(arvore, palavra);
					printf("%s: palavra inserida no dicionario!\n", palavra);
				}

				break;
			case 2:
				//ler palavra
				printf("CONSULTA\n\n");
				printf("Insira a palavra que deseja consultar\n");
				printf("Palavra: ");
				palavra = ler_palavra(stdin);

				if(trie_procurar_palavra(arvore, palavra))
					printf("%s: palavra existe no dicionario!\n", palavra);
				else
					printf("%s: palavra nao existe no dicionario!\n", palavra);

				break;
			case 3:
				break;
			case 4:
				break;
			case 5:
				//ler prefixo
				printf("\nInsira o prefixo\n");
				printf("Prefixo: ");
				palavra = ler_palavra(stdin);

				if(trie_procurar_prefixo(arvore, palavra)){
					printf("Palavras comecadas em: %s\n", palavra);
					trie_imprimir_palavras_comecadas_em(arvore,palavra);
				}else{
					printf("O prefixo inserido nao existe neste dicionario!\n");
				}

				break;
			case 6:
				break;
			case 7:
				break;
			case 8:
				break;
			case 9:
				break;
			case 10:   
				break;
			case 0: 
				printf("\nA terminar o programa...\n");
				break;
			default:
				printf("Opcao invalida! Por favor, tente novamente\n");
				break;
		}

		if((opcao > 0) && (opcao <= 10)){			//evita o "double free() in tcashe2 erro"
			esperar_tecla();
			LIMPAR_TELA;
			free(palavra);
		}

	}while(opcao != 0);

	//atualizar_ficheiro_de_dados();
	printf("Programa terminado com sucesso!\n");
	
	return 0;
}
void carregar_trie_com_ficheiro(Trie *arvore, FILE *ficheiro){
	char *palavra;
	int i = 1;
	while(palavra = ler_palavra(ficheiro)){
		trie_inserir_palavra(arvore, palavra);
	}
}
