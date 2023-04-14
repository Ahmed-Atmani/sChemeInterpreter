all: main.o parser.o token-tree.o
	gcc main.o parser.o token-tree.o -o main

main.o:	main.c parser.h
	gcc -c main.c -o main.o

parser.o: parser.c parser.h token-tree.h
	gcc -c  parser.c -o parser.o

token-tree.o: token-tree.c token-tree.h
	gcc -c token-tree.c -o token-tree.o

clear:
	rm main.o 
	rm parser.o
	rm token-tree.o
	rm main.exe
