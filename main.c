// main.c
#include "sistema_de_arquivos.h"
#include <stdio.h>
#include <string.h>

void show_menu() {
    printf("\nMenu:\n");
    printf("1. Criar arquivo\n");
    printf("2. Listar arquivos\n");
    printf("3. Ver conteúdo de um arquivo\n");
    printf("4. Sair\n");
    printf("Escolha uma opção: ");
}

int main() {
    // Inicializa o disco e o diretório
    memset(disco, 0, sizeof(disco));
    diretorio.contador_arquivos = 0;

    // Carrega o diretório do arquivo
    carregar_diretorio("diretorio.txt");

    int opcao;
    char nome_arquivo[20];
    int tamanho;

    while (1) {
        show_menu();
        scanf("%d", &opcao);
        getchar(); // Limpar o buffer do \n

        switch (opcao) {
            case 1:
                printf("\nDigite o nome do arquivo: ");
                fgets(nome_arquivo, sizeof(nome_arquivo), stdin);
                nome_arquivo[strcspn(nome_arquivo, "\n")] = '\0'; // Remove o newline do input

                printf("Digite o tamanho do arquivo: ");
                scanf("%d", &tamanho);
                getchar(); // Limpar o buffer do \n

                cat(nome_arquivo, tamanho);
                break;

            case 2:
                printf("\nListando arquivos:\n");
                ls();
                break;

            case 3:
                printf("\nDigite o nome do arquivo para ver o conteúdo: ");
                fgets(nome_arquivo, sizeof(nome_arquivo), stdin);
                nome_arquivo[strcspn(nome_arquivo, "\n")] = '\0'; // Remove o newline do input

                printf("Conteúdo de %s:\n", nome_arquivo);
                more(nome_arquivo);
                break;

            case 4:
                salvar_no_diretorio("diretorio.txt");
                printf("Saindo...\n");
                return 0;

            default:
                printf("Opção inválida, tente novamente.\n");
        }
    }

    return 0;
}
