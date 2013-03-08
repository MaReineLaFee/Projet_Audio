//      Main.c
//      
//      Copyright 2013 Weissgerber Flora <fweissgerber@roucas103>
//      
//      This program is free software; you can redistribute it and/or modify
//      it under the terms of the GNU General Public License as published by
//      the Free Software Foundation; either version 2 of the License, or
//      (at your option) any later version.
//      
//      This program is distributed in the hope that it will be useful,
//      but WITHOUT ANY WARRANTY; without even the implied warranty of
//      MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//      GNU General Public License for more details.
//      
//      You should have received a copy of the GNU General Public License
//      along with this program; if not, write to the Free Software
//      Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
//      MA 02110-1301, USA.


#include <stdio.h>
#include <fftw3.h>
#include <stdlib.h>
#include <math.h>

#include "./Include/Fonctions.h"

int main(int argc, char **argv)
{
	// initialisation des indices de boucles
	int i;
	int j;
	
	// initialisation de la lectre des wav
	int taille_header = 44;
	int nombre_echantillon = taille_wav(argv[1], taille_header);
	printf("%d echantillons\n", nombre_echantillon);
	double vecteur_son[nombre_echantillon];
	
	// initialisation de la recherche des pitch
	float temps_acquisition_pitch = 0.02;
	float frequence_echantillonnage = 44100;
	int indice_pitch = (int)(temps_acquisition_pitch*frequence_echantillonnage + 0.5);
	printf("le nombre d'échatillon necessaire pour calculer le pitch est %d\n", indice_pitch);
	
	// initilisation de la FFT et du module du spectre
	int taille_spectre = indice_pitch/2+1;
	fftw_complex* spectre = (fftw_complex*)fftw_malloc(sizeof(fftw_complex)*(taille_spectre));
	float module_spectre[taille_spectre];
	
	// initialisation de la recherche de maximum pour un tableau
	float max_spectre = 0;
	int indice_max_spectre = 0;
	
	// initialisation du test de pitch
	int nombre_test_possible = nombre_echantillon/indice_pitch;
	printf("on peut faire %d tests avec cet echantillon\n", nombre_test_possible);
	float resultat_test[nombre_test_possible];
	double signal_fenetre[indice_pitch];
	
	//lecture du wav
	lire_wav(argv[1],vecteur_son, nombre_echantillon, taille_header );
	fprintf(stderr, "j'ai lu la chanson\n");
	

	
	// boucle de test des pitch
	
	for(i=0; i<nombre_test_possible; i++)
	{
		
		// creation du signal sur la fenetre
		for(j=0 ;j<indice_pitch; j++)
		{
			signal_fenetre[j]= vecteur_son[i*indice_pitch + j];
		}
		
		// creation du spectre sur la fenêtre et de son module
		creation_spectre(indice_pitch, signal_fenetre, spectre);
		module_du_spectre(spectre,module_spectre, taille_spectre);
		
		// recherche du maximum du spectre
		max_search_table_float (module_spectre, indice_pitch, &max_spectre, &indice_max_spectre);
		
		// sauvegarde et affichache du pitch
		resultat_test[i] = indice_max_spectre;
		printf("le resultat du test %d est %lf à la frequence %d\n", i, max_spectre, indice_max_spectre);
		
	}
	
	
	
	return 0;
}

