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
	int nombre_echantillon = 251904;
	short vecteur_son[nombre_echantillon];
	int i;
	
	lire_wav(argv[1],vecteur_son, nombre_echantillon );
	fprintf(stderr, "j'ai lu la chanson\n");
	
	for (i=0; i<200 ;i++)
	{
		printf("%d %d \n", i, vecteur_son[i]);
	}
	
	return 0;
}

