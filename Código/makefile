all: compila clean executa

compila: tad.o psinterface.o trab2.o
	gcc -o trab2 tad.o psinterface.o trab2.o -lm
tad.o: tad.c
	gcc -c tad.c
psinterface.o: psinterface.c
	gcc -c psinterface.c
trab2.o: tad.c psinterface.c tad.h psinterface.h
	gcc -c trab2.c	
clean:
	rm -rf *.o
executa:
	./trab2
