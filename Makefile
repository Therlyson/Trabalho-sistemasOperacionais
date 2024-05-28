all: output/sistema_de_arquivos

output/sistema_de_arquivos: main.o sistema_de_arquivos.o | output
	gcc -o output/sistema_de_arquivos main.o sistema_de_arquivos.o

main.o: main.c sistema_de_arquivos.h
	gcc -c main.c

sistema_de_arquivos.o: sistema_de_arquivos.c sistema_de_arquivos.h
	gcc -c sistema_de_arquivos.c

output:
	mkdir -p output

clean:
	rm -f *.o output/sistema_de_arquivos
	rm -rf output