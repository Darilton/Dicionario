#include <stdio.h>
#include <stdlib.h>
#include "sourcefiles/string/string.h"
#include "sourcefiles/trie/trie.h"
#include "sourcefiles/string/string.h"
#include "sourcefiles/menu_utils/menu_utils.h"

int main(){
	char *palavra;
	int opcao;
	Trie *arvore = trie_nova_arvore();

	//abrir_ficheiro_de_dados();

	//carregar_arvore_com_dados_do_ficheiro();
	
	printf("Bem vindo\n");
	printf("Por favor, escolha uma das opcoes!\n");

	do{
		apresentar_menu();

		opcao = ler_opcao();
		getchar();

		switch(opcao){
			case 1:
				//ler palavra
				printf("\nInsira a palavra que deseja guardar neste dicionario\n");
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
				printf("\nInsira a palavra que deseja consultar\n");
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

		if((opcao > 0) && (opcao <= 10))			//evita o "double free() in tcashe2 erro"
			free(palavra);

		if(opcao != 0)
			putchar('\n');

	}while(opcao != 0);

	//atualizar_ficheiro_de_dados();
	printf("Programa terminado com sucesso!\n");
	
	return 0;
}
