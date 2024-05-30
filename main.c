#include "sistema_de_arquivos.h"
#include <stdio.h>
#include <string.h>

void show_menu() {
    printf("\n\nMenu:\n");
    printf("Criar arquivo digite o comando - cat nomeArquivo.txt\n");
    printf("Listar arquivos digite o comando - ls\n");
    printf("Ver conteúdo de um arquivo - more nomeArquivo.jpg\n");
    printf("Sair - exit\n");
    printf("Digite o comando que deseja: ");
}

int main() {
    memset(disco, 0, sizeof(disco)); // Inicializa o disco e o diretório
    diretorio.contador_arquivos = 0;

    carregar_diretorio("diretorio.txt");

    char comando[100];
    char nome_arquivo[20];
    char conteudo[MAX_CONTENT_SIZE];

    while (1) {
        show_menu();
        fgets(comando, sizeof(comando), stdin);
        comando[strcspn(comando, "\n")] = '\0'; // Remove o newline do input

        if (strncmp(comando, "cat ", 4) == 0) {
            strcpy(nome_arquivo, comando + 4);

            printf("\nDigite o conteúdo que deseja inserir em %s: ", nome_arquivo);
            fgets(conteudo, sizeof(conteudo), stdin);
            conteudo[strcspn(conteudo, "\n")] = '\0';

            cat(nome_arquivo, conteudo);
        } else if (strcmp(comando, "ls") == 0) {
            printf("\nListando arquivos:\n");
            ls();
        } else if (strncmp(comando, "more ", 5) == 0) {
            strcpy(nome_arquivo, comando + 5);
            more(nome_arquivo);
        } else if (strcmp(comando, "exit") == 0) {
            salvar_no_diretorio("diretorio.txt");
            printf("Saindo...\n");
            break;
        } else {
            printf("Opção inválida, tente novamente.\n");
        }
    }

    return 0;
}
