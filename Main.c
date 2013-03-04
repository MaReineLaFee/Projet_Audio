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

#include "./Include/Fonctions.h"

int main(int argc, char **argv)
{
	int taille_header = 44;
	
	int nombre_echantillon = taille_wav(argv[1], taille_header);
	printf("%d echantillons\n", nombre_echantillon);
	
	double vecteur_son[nombre_echantillon];
	int i;
	
	lire_wav(argv[1],vecteur_son, nombre_echantillon, taille_header );
	fprintf(stderr, "j'ai lu la chanson\n");
	
	for (i=0; i<200 ;i++)
	{
		printf("%d %f \n", i, vecteur_son[i]);
	}
	
	fprintf(stderr, "j'ai montre la chanson\n");
	
	fftw_complex* spectre = (fftw_complex*)fftw_malloc(sizeof(fftw_complex)*(nombre_echantillon/2+1));
	
	fprintf(stderr, "j'ai initialise les vecteurs pour le spectre\n");
	
	creation_spectre(nombre_echantillon, vecteur_son, spectre);
	
	fprintf(stderr, "j'ai rempli le spectre\n");
	
	for (i=0; i<200; i++)
	{
		printf("%lf \n", spectre[i]);
	}
	
	return 0;
}

