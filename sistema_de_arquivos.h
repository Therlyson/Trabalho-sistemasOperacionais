// sistema_de_arquivos.h
#ifndef SISTEMA_DE_ARQUIVOS_H
#define SISTEMA_DE_ARQUIVOS_H

#define MAX_FILES 100
#define DISK_SIZE 25

// Estrutura para armazenar informações de um arquivo
typedef struct {
    char nome[20];
    int tamanho;
    int start;
} arquivo_de_entrada;

// Estrutura para representar o diretório
typedef struct {
    arquivo_de_entrada arquivos[MAX_FILES];
    int contador_arquivos;
} Diretorio;

// Variáveis globais
extern char disco[DISK_SIZE];
extern Diretorio diretorio;

// Declaração das funções
void cat(const char* nome_arquivo, int size);
void ls();
void more(const char* nome_arquivo);
void salvar_no_diretorio(const char* nome_arquivo);
void carregar_diretorio(const char* nome_arquivo);

#endif // SISTEMA_DE_ARQUIVOS_H
