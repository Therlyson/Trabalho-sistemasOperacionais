// sistema_de_arquivos.c
#include "sistema_de_arquivos.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Variáveis globais
char disco[DISK_SIZE];
Diretorio diretorio;

// Função para criar um arquivo no diretório
void cat(const char* nome_arquivo, int tamanho) {
    if (diretorio.contador_arquivos >= MAX_FILES) {
        printf("Diretório cheio.\n");
        return;
    }

    // Encontrar espaço contíguo no disco
    int start = -1;
    for (int i = 0; i <= DISK_SIZE - tamanho; ++i) {
        int j;
        for (j = 0; j < tamanho; ++j) {
            if (disco[i + j] != 0) break;
        }
        if (j == tamanho) {
            start = i;
            break;
        }
    }

    if (start == -1) {
        printf("Espaço insuficiente no disco.\n");
        return;
    }

    // Alocar espaço no disco
    for (int i = start; i < start + tamanho; ++i) {
        disco[i] = 1; // Usando '1' para indicar espaço ocupado
    }

    // Adicionar arquivo ao diretório
    strcpy(diretorio.arquivos[diretorio.contador_arquivos].nome, nome_arquivo);
    diretorio.arquivos[diretorio.contador_arquivos].tamanho = tamanho;
    diretorio.arquivos[diretorio.contador_arquivos].start = start;
    diretorio.contador_arquivos++;

    // Salvar a alteração no arquivo do diretório
    salvar_no_diretorio("diretorio.txt");

    printf("Arquivo %s criado.\n", nome_arquivo);
}

// Função para listar todos os arquivos no diretório
void ls() {
    for (int i = 0; i < diretorio.contador_arquivos; ++i) {
        printf("%s\t%d\t%d\n", diretorio.arquivos[i].nome, diretorio.arquivos[i].tamanho, diretorio.arquivos[i].start);
    }
}

// Função para mostrar o conteúdo de um arquivo especificado
void more(const char* nome_arquivo) {
    for (int i = 0; i < diretorio.contador_arquivos; ++i) {
        if (strcmp(diretorio.arquivos[i].nome, nome_arquivo) == 0) {
            int start = diretorio.arquivos[i].start;
            int size = diretorio.arquivos[i].tamanho;
            for (int j = start; j < start + size; ++j) {
                printf("%d ", disco[j]);
            }
            printf("\n");
            return;
        }
    }
    printf("Arquivo não encontrado.\n");
}

// Função para salvar o diretório em um arquivo de texto
void salvar_no_diretorio(const char* nome_arquivo) {
    FILE *file = fopen(nome_arquivo, "w");
    if (file == NULL) {
        printf("Erro ao abrir o arquivo para salvar o diretório.\n");
        return;
    }

    for (int i = 0; i < diretorio.contador_arquivos; ++i) {
        fprintf(file, "%s %d %d\n", diretorio.arquivos[i].nome, diretorio.arquivos[i].tamanho, diretorio.arquivos[i].start);
    }

    fclose(file);
    printf("Diretório salvo em %s\n", nome_arquivo);
}

// Função para carregar o diretório de um arquivo de texto
void carregar_diretorio(const char* nome_arquivo) {
    FILE *arquivo = fopen(nome_arquivo, "r");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo do diretório.\n");
        return;
    }

    diretorio.contador_arquivos = 0;
    memset(disco, 0, sizeof(disco)); // Limpar o disco ao carregar o diretório
    char name[20];
    int tamanho, start;
    while (fscanf(arquivo, "%s %d %d", name, &tamanho, &start) == 3) {
        strcpy(diretorio.arquivos[diretorio.contador_arquivos].nome, name);
        diretorio.arquivos[diretorio.contador_arquivos].tamanho = tamanho;
        diretorio.arquivos[diretorio.contador_arquivos].start = start;
        diretorio.contador_arquivos++;
        
        // Marcar o espaço do arquivo no disco
        for (int i = start; i < start + tamanho; ++i) {
            disco[i] = 1;
        }
    }

    fclose(arquivo);
    printf("Diretório carregado de %s\n", nome_arquivo);
}
