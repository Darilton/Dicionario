#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#if defined(_WIN32) || defined(_WIN64)
#	include "sourcefiles\\palavra\\palavra.h"
#	include "sourcefiles\\trie\\trie.h"
#	include "sourcefiles\\menu_utils\\menu_utils.h"
#	define LIMPAR_TELA system("cls")
#	define DICIONARIO "resources\\dicionario.dat"
#else
#	include "sourcefiles/palavra/palavra.h"
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
				//ler palavra
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
				//ler palavra
				printf("ELIMINAR PALAVRA\n\n");
				printf("Insira a palavra que deseja eliminar\n");
				printf("Palavra: ");
				palavra = ler_palavra(stdin);

				trie_remover_palavra(arvore,palavra);

				break;
			case 4:
				//ler palavra antiga
				printf("ATUALIZAR PALAVRA\n\n");
				printf("Insira a palavra que deseja atualizar\n");
				printf("Palavra antiga: ");
				palavra = ler_palavra(stdin);

				//ler nova palavra
				printf("Insira a palavra atualizada\n");
				printf("Palavra atualizada: ");
				char *palavra_nova = ler_palavra(stdin);

				switch(trie_atualizar_palavra(arvore, palavra, palavra_nova)){
					case 0: printf("%s: palavra nao existe na arvore! Nada a fazer\n", palavra);
					case 1: printf("%s: palavra atualizada para %s\n", palavra, palavra_nova);
					case 2: printf("%s: palavra ja existe na arvore! Nada a fazer\n", palavra_nova);
				}

				free(palavra_nova);
				break;
			case 5:
				//ler prefixo
				printf("\nPALAVRAS COMECADAS POR PREFIXO\n");
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
				//Verificador Ortografico
				printf("\nVERIFICADOR ORTOGRAFICO\n");
				printf("por favor insira o caminho para o ficheiro\nNo windows nao se esqueca de inserir duas barras\nEx: ..\\\\pasta\\\\ficheiro.dat\n");
				char caminho[50], resposta;
				int palavras_existem_no_dicionario = 1;		//flag que diz se todas as palavras do dicionario existem no ficheiro

				//le o caminho
				printf("ficheiro: ");
				fgets(caminho, 50, stdin);

				//remove o \n lido da variavel
				size_t ln = strlen(caminho) - 1;
				if (*caminho && caminho[ln] == '\n')
					caminho[ln] = '\0';	

				printf("caminho: %s\n", caminho);
				
				
				FILE *ficheiro = fopen(caminho, "r+");

				if(ficheiro == NULL){
					printf("Nao foi possivel abrir o ficheiro especificado\n");
					break;
				}

				while(palavra = ler_palavra(ficheiro)){
					//se palavra nao existe
					if(!trie_procurar_palavra(arvore,palavra)){
						palavras_existem_no_dicionario = 0;
						//Sugere insercao no dicionario
						printf("%s nao existe no dicionario! Deseja adiciona-la?(s/n): ", palavra);
						scanf("%c", &resposta);
						putchar('\n');
						
						if((resposta == 's') || (resposta == 'S')){
							trie_inserir_palavra(arvore,palavra);
							printf("%s: palavra inserida com sucesso\n", palavra);
						}else{
							long num_carac_a_voltar = - sizeof(char);

							fseek(ficheiro, num_carac_a_voltar, SEEK_CUR);
							fprintf(ficheiro,"*");
						}
						getchar();
					}
					free(palavra);
				}

				if(palavras_existem_no_dicionario)
					printf("Todas as palavras deste ficheiro existem no dicionario!\nNada a fazer\n");

				fclose(ficheiro);
				break;
			case 9:
				//imprimir arvore
				trie_imprimir_arvore(arvore);
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
			esperar_enter();
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
		free(palavra);
	}
}
