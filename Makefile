all: main.o memproc.o auxiliary.o environment.o value.o eval.o parser.o token-tree.o
	gcc main.o memproc.o auxiliary.o environment.o value.o eval.o parser.o token-tree.o -o main

main.o:	main.c main.h memproc.h auxiliary.h environment.h value.h eval.h parser.h
	gcc -c main.c -o main.o

memproc.o: memproc.c memproc.h
	gcc -c memproc.c -o memproc.o

auxiliary.o: auxiliary.c auxiliary.h memproc.h
	gcc -c auxiliary.c -o auxiliary.o

environment.o: environment.c environment.h value.h
	gcc -c environment.c -o environment.o

value.o: value.c value.h
	gcc -c value.c -o value.o

eval.o: eval.c eval.h token-tree.h
	gcc -c eval.c -o eval.o

parser.o: parser.c parser.h token-tree.h
	gcc -c parser.c -o parser.o

token-tree.o: token-tree.c token-tree.h
	gcc -c token-tree.c -o token-tree.o

clear:
	rm main.o memproc.o environment.o auxiliary.o value.o eval.o parser.o token-tree.o main.exe


