Projet : Main.o Fonctions.o
	g++  `pkg-config --libs fftw3` Main.o Fonctions.o -o ./Bin/Main
	
Main.o : Main.c ./Include/Fonctions.h
	g++  `pkg-config --cflags fftw3` -c Main.c
	
Fonctions.o : ./Sources/Fonctions.c ./Include/Fonctions.h
	g++  `pkg-config --cflags fftw3` -c ./Sources/Fonctions.c

clean :
	rm *.o ./Bin/Main
