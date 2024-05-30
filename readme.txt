IMPLEMENTAÇÃO DE UM SISTEMA DE ARQUIVOS
Aluno: Therlyson Ryan de Souza Santos

Descrição do Projeto:
Este projeto implementa um simples sistema de arquivos simulado em linguagem C. Ele permite criar arquivos, 
listar arquivos existentes, visualizar o conteúdo de arquivos e salvar o estado do sistema de arquivos em um único diretório. 


Estrutura do Código:

sistema_de_arquivos.h:
Este arquivo contém as definições de estruturas e declarações de funções usadas no meu sistema de arquivos. As principais estruturas são:
- arquivo_de_entrada: Representa um arquivo no sistema, contendo nome, tamanho, posição inicial e conteúdo do arquivo.
- Diretorio: Representa um diretório que contém vários arquivos.
- Variáveis globais: disco (simulação de um disco com tamanho definido) e diretorio (estrutura que contém arquivos).

sistema_de_arquivos.c:
Este arquivo implementa as funções declaradas em sistema_de_arquivos.h:
- cat: Cria um novo arquivo no diretório e aloca espaço no disco.
- ls: Lista todos os arquivos presentes no diretório.
- more: Exibe o conteúdo de um arquivo específico.
- salvar_no_diretorio: Salva o estado atual do diretório em um arquivo de texto.
- carregar_diretorio: Carrega o estado do diretório de um arquivo de texto.

main.c:
Este arquivo contém a função principal que exibe o menu para o usuário e chama as funções apropriadas com base na entrada do usuário. 

Makefile:
O Makefile define como compilar e vincular os arquivos do projeto. Ele inclui regras para criar os arquivos objeto, 
vincular os objetos em um executável, criar o diretório de saída e limpar os arquivos de objeto e executáveis.
Ou seja, ele basicamente vai facilitar a compilação do programa.


Compilação e Execução:

Para compilar e executar este projeto, siga os passos abaixo:

1. Se deseja apenas executar o programa:
    - Com o terminal aberto digite: ./output/sistema_de_arquivos

2. Se deseja compilar o programa:
   - No terminal digite: make clean (opcional, simplesmente para limpar os arquivos de objeto e começar a compilação do zero)
   
   - Para compilar basta digitar no terminal: make (Com isso o arquivo Makefile se responsabiliza pelo resto)
   - Agora execute: ./output/sistema_de_arquivos


Ambiente de Desenvolvimento:
A compilação e execução do trabalho foram realizadas em um ambiente Ubuntu Linux utilizando-se a linha de comando através do WSL (Windows Subsystem for Linux) 
do Windows. O Visual Studio Code (VSCode) foi utilizado com a extensão WSL para editar e rodar o código como se fosse em um ambiente Linux.


Conclusão:
Este projeto oferece uma visão básica de como sistemas de arquivos podem ser implementados em C. 
Melhorias podem ser feitas em várias áreas, como gerenciamento de espaço no disco, verificação de entradas do usuário e robustez da interface de usuário.