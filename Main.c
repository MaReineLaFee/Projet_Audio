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
	int taille_header = 44;
	int i;
	int j;
	
	int nombre_echantillon = taille_wav(argv[1], taille_header);
	int taille_spectre = nombre_echantillon/2+1;
	printf("%d echantillons\n", nombre_echantillon);
	
	double vecteur_son[nombre_echantillon];
	fftw_complex* spectre = (fftw_complex*)fftw_malloc(sizeof(fftw_complex)*(taille_spectre));
	float module_spectre[taille_spectre];
	
	float temps_acquisition_pitch = 0.02;
	float frequence_echantillonnage = 44100;
	int indice_pitch = (int)(temps_acquisition_pitch*frequence_echantillonnage + 0.5);
	printf("le nombre d'échatillon necessaire pour calculer le pitch est %d\n", indice_pitch);
	
	float max_spectre = 0;
	int indice_max_spectre = 0;
	
	int nombre_test_possible = nombre_echantillon/indice_pitch;
	printf("on peut faire %d tests avec cet echantillon\n", nombre_test_possible);
	float resultat_test[nombre_test_possible];
	float module_spectre_test[indice_pitch];
	
	lire_wav(argv[1],vecteur_son, nombre_echantillon, taille_header );
	fprintf(stderr, "j'ai lu la chanson\n");
	
	creation_spectre(nombre_echantillon, vecteur_son, spectre);
	
	fprintf(stderr, "j'ai rempli le spectre\n");
	
	module_du_spectre(spectre,module_spectre, taille_spectre);
	
	fprintf(stderr, "j'ai fait le module du spectre\n");
	
	// boucle de test des pitch
	
	for(i=0; i<nombre_test_possible; i++)
	{
		for(j=0 ;j<indice_pitch; j++)
		{
			module_spectre_test[j]= module_spectre[i*indice_pitch + j];
		}
		
		max_search_table_float (module_spectre_test, indice_pitch, &max_spectre, &indice_max_spectre);
		
		resultat_test[i] = max_spectre;
		
		printf("le resultat du test %d est %lf\n", i, max_spectre);
	}
	
	
	
	return 0;
}

