Projet : Main.o Fonctions.o
	g++  -lfftw3 -lm Main.o Fonctions.o -o ./Bin/Main
	
Main.o : Main.c ./Include/Fonctions.h
	g++  -lfftw3 -lm -c Main.c
	
Fonctions.o : ./Sources/Fonctions.c ./Include/Fonctions.h
	g++  -lfftw3 -lm -c ./Sources/Fonctions.c

clean :
	rm *.o ./Bin/Main
