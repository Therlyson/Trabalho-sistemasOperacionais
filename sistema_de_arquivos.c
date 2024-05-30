#include "sistema_de_arquivos.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char disco[DISK_SIZE];
Diretorio diretorio;

void cat(const char* nome_arquivo, const char* conteudo) {
    if (diretorio.contador_arquivos >= MAX_FILES) {
        printf("\nDiretório cheio, não é possivel criar mais arquivos.\n");
        return;
    }

    for (int i = 0; i < diretorio.contador_arquivos; ++i) {
        if (strcmp(diretorio.arquivos[i].nome, nome_arquivo) == 0) {
            printf("\nERRO! O arquivo %s já existe.\n", nome_arquivo);
            return;
        }
    }

    int tamanho = (int) strlen(conteudo);

    // Encontrar espaço contíguo no disco
    int start = -1;
    for (int i = 0; i <= DISK_SIZE - tamanho; ++i) { // desde o início até a posição onde ainda há espaço suficiente para o novo arquivo.
        int j;
        for (j = 0; j < tamanho; ++j) {
            if (disco[i + j] != 0) break; // posição i + j está ocupada, então o loop interno é interrompido
        }
        if (j == tamanho) { //bloco contíguo de espaço livre foi encontrado.
            start = i; //indicando a posição inicial do espaço livre.
            break;
        }
    }

    if (start == -1) {
        printf("ERRO! Espaço insuficiente no disco.\n");
        return;
    }

    // Alocar espaço no disco
    for (int i = start; i < start + tamanho; ++i) {
        disco[i] = 1; // Usando '1' para indicar que o espaço está ocupado
    }

    // Adicionando arquivo ao diretório
    strcpy(diretorio.arquivos[diretorio.contador_arquivos].nome, nome_arquivo);
    diretorio.arquivos[diretorio.contador_arquivos].tamanho = tamanho;
    diretorio.arquivos[diretorio.contador_arquivos].start = start;
    strncpy(diretorio.arquivos[diretorio.contador_arquivos].conteudo, conteudo, MAX_CONTENT_SIZE - 1);
    diretorio.arquivos[diretorio.contador_arquivos].conteudo[MAX_CONTENT_SIZE - 1] = '\0';
    diretorio.contador_arquivos++;

    printf("\nArquivo %s criado com sucesso.\n", nome_arquivo);
}


void ls() {
    for (int i = 0; i < diretorio.contador_arquivos; ++i) {
        printf("%-20s\t%d\t%d\n", diretorio.arquivos[i].nome, diretorio.arquivos[i].tamanho, diretorio.arquivos[i].start);
    }
    if(diretorio.contador_arquivos == 0){
        printf("Diretório está vazio.\n");
    }
}


void more(const char* nome_arquivo) {
    for (int i = 0; i < diretorio.contador_arquivos; ++i) {
        if (strcmp(diretorio.arquivos[i].nome, nome_arquivo) == 0) {
            printf("\nConteúdo de %s: %s\n", nome_arquivo, diretorio.arquivos[i].conteudo);
            return;
        }
    }
    printf("\nO arquivo %s não foi encontrado no diretório.\n",nome_arquivo);
}


void salvar_no_diretorio(const char* nome_diretorio) {
    FILE *file = fopen(nome_diretorio, "w");
    if (file == NULL) {
        printf("Erro ao abrir o arquivo para salvar o diretório.\n");
        return;
    }

    for (int i = 0; i < diretorio.contador_arquivos; ++i) {
        fprintf(file, "%s %d %d %s\n", diretorio.arquivos[i].nome, diretorio.arquivos[i].tamanho, diretorio.arquivos[i].start, diretorio.arquivos[i].conteudo);
    }

    fclose(file);
    printf("\nArquivo de diretório salvo em %s\n", nome_diretorio);
}


void carregar_diretorio(const char* nome_diretorio) {
    FILE *file = fopen(nome_diretorio, "r");
    if (file == NULL) {
        printf("Erro ao abrir o arquivo do diretório.\n");
        return;
    }

    diretorio.contador_arquivos = 0;
    memset(disco, 0, sizeof(disco)); // Limpar o disco ao carregar o diretório, definindo todos os bytes da região de memória como zero.
    char name[20];
    int tamanho, start;
    char conteudo[MAX_CONTENT_SIZE];
    while (fscanf(file, "%s %d %d", name, &tamanho, &start) == 3) {
        fgets(conteudo, MAX_CONTENT_SIZE, file); // Lê o resto da linha como conteúdo
        conteudo[strcspn(conteudo, "\n")] = 0; // Remove o '\n' do final

        strcpy(diretorio.arquivos[diretorio.contador_arquivos].nome, name);
        diretorio.arquivos[diretorio.contador_arquivos].tamanho = tamanho;
        diretorio.arquivos[diretorio.contador_arquivos].start = start;
        strncpy(diretorio.arquivos[diretorio.contador_arquivos].conteudo, conteudo, MAX_CONTENT_SIZE - 1);
     diretorio.arquivos[diretorio.contador_arquivos].conteudo[MAX_CONTENT_SIZE - 1] = '\0';
        diretorio.contador_arquivos++;

        // Marcando o espaço do arquivo no disco
        for (int i = start; i < start + tamanho; ++i) {
            disco[i] = 1;
        }
    }

    fclose(file);
    printf("Diretório carregado de %s\n", nome_diretorio);
}