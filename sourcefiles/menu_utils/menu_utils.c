#include "menu_utils.h"
#include <stdio.h>

void apresentar_menu(){
	printf("Por favor, escolha uma das opcoes!\n");
        printf("1 - Inserir nova palavra\n");
        printf("2 - Consultar palavra no dicionario\n");
        printf("3 - Remover palavra do dicionario\n");
        printf("4 - Atualizar palavra no dicionario\n");
        printf("5 - Mostrar palavras com o mesmo prefixo\n");
        printf("6 - Mostrar palavra com o prefixo mais longo\n");
        printf("7 - Mostrar palavras similares por distanciamento minimo\n");
        printf("8 - Verificador ortográfico\n");
        printf("9 - Indice\n");
        printf("10 - Verificar integridade do ficheiro\n");
        printf("0 - Terminar programa\n");
	printf("opcao: ");
}

void esperar_tecla(){
	char ch;
	printf("\nPrima Enter para voltar ao menu...");
	while((ch = getchar()) != '\n')
		;
}

int ler_opcao(){
	char opcao = getchar();

	if((opcao >= 48) && (opcao <= 57))
		return opcao - '0'; 

	return -1;
}
