CFLAGS=  -std=c11

all: main.o memproc.o string.o environment.o value.o eval.o parser.o token-tree.o
	gcc main.o memproc.o string.o environment.o value.o eval.o parser.o token-tree.o -o main $(CFLAGS)

main.o:	main.c main.h memproc.h string.h environment.h value.h eval.h parser.h
	gcc -c main.c -o main.o $(CFLAGS)

memproc.o: memproc.c memproc.h
	gcc -c memproc.c -o memproc.o $(CFLAGS)

string.o: string.c string.h memproc.h
	gcc -c string.c -o string.o $(CFLAGS)

environment.o: environment.c environment.h value.h
	gcc -c environment.c -o environment.o $(CFLAGS)

value.o: value.c value.h
	gcc -c value.c -o value.o $(CFLAGS)

eval.o: eval.c eval.h token-tree.h
	gcc -c eval.c -o eval.o $(CFLAGS)

parser.o: parser.c parser.h token-tree.h
	gcc -c parser.c -o parser.o $(CFLAGS)

token-tree.o: token-tree.c token-tree.h
	gcc -c token-tree.c -o token-tree.o $(CFLAGS)

clear:
	rm main.o memproc.o environment.o string.o value.o eval.o parser.o token-tree.o main.exe main *.stackdump


