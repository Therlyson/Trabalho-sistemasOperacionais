#ifndef SISTEMA_DE_ARQUIVOS_H
#define SISTEMA_DE_ARQUIVOS_H

#define MAX_FILES 100
#define DISK_SIZE 50
#define MAX_CONTENT_SIZE 100

// Estrutura para armazenar informações do arquivo
typedef struct {
    char nome[20];
    int tamanho;
    int start;
    char conteudo[MAX_CONTENT_SIZE];
} arquivo_de_entrada;

// Estrutura para representar o diretório
typedef struct {
    arquivo_de_entrada arquivos[MAX_FILES];
    int contador_arquivos;
} Diretorio;

extern char disco[DISK_SIZE]; //variável global que representa o disco
extern Diretorio diretorio;

void cat(const char* nome_arquivo, const char* conteudo);
void ls();
void more(const char* nome_arquivo);
void salvar_no_diretorio(const char* nome_arquivo);
void carregar_diretorio(const char* nome_arquivo);

#endif
