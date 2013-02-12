Projet : Main.o Fonctions.o
	g++  Main.o Fonctions.o -o ./Bin/Main
	
Main.o : Main.c ./Include/Fonctions.h
	g++  -c Main.c
	
Fonctions.o : ./Sources/Fonctions.c ./Include/Fonctions.h
	g++  -c ./Sources/Fonctions.cb 

clean :
	rm *.o ./Bin/Main
