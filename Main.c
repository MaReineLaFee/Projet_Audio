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
	// ouverture du fichier de test
	FILE* fichier_vecteur_son = fopen("../vecteur_son.txt", "w+");
	FILE* fichier_module = fopen("../module.txt", "w+");
	
	// initialisation des indices de boucles
	int i;
	int j;
	
	// initialisation de la lecture des wav
	int taille_header = 44;
	int nombre_echantillon = taille_wav(argv[1], taille_header);
	printf("%d echantillons\n", nombre_echantillon);
	double vecteur_son[nombre_echantillon];
	
	// initialisation de la recherche des pitch
	double temps_acquisition_pitch = 0.2;
	double frequence_echantillonnage = 44100;
	int nombre_echantillon_pitch = (int)(temps_acquisition_pitch*frequence_echantillonnage + 0.5);
	printf("le nombre d'échantillon necessaire pour calculer le pitch est %d\n", nombre_echantillon_pitch);
	
	// initilisation de la FFT et du module du spectre
	int taille_spectre = nombre_echantillon_pitch/2+1;
	fftw_complex* spectre = (fftw_complex*)fftw_malloc(sizeof(fftw_complex)*(taille_spectre));
	float module_spectre[taille_spectre];
	
	// initialisation de la recherche de maximum pour un tableau
	float max_spectre = 0;
	int indice_max_spectre = 0;
	
	// initialisation du test de pitch
	int nombre_test_possible = nombre_echantillon/nombre_echantillon_pitch;
	printf("on peut faire %d tests avec cet echantillon\n", nombre_test_possible);
	double resultat_test[nombre_test_possible];
	double signal_fenetre[nombre_echantillon_pitch];
	
	// initialisation du test avec un sinus
	double frequence_garcon = 200;
	double frequence_fille = 350;
	
	//lecture du wav
	
	//lire_wav(argv[1],vecteur_son, nombre_echantillon, taille_header );
	signal_sinus(vecteur_son, nombre_echantillon, frequence_echantillonnage, frequence_garcon, frequence_fille);
	for(i=0; i<nombre_echantillon; i++)
	{
		fprintf(fichier_vecteur_son, "%f\n", vecteur_son[i]);
	}
	fprintf(stderr, "j'ai lu la chanson\n");

	
	// boucle de test des pitch

	for(i=0; i<nombre_test_possible; i++)
	{
		// creation du signal sur la fenetre
		int indice_debut = i*nombre_echantillon_pitch;
		signal_reduit_fenetre(vecteur_son, signal_fenetre, indice_debut, nombre_echantillon_pitch);
		
		// creation du spectre sur la fenêtre et de son module
		creation_spectre(nombre_echantillon_pitch, signal_fenetre, spectre);
		module_du_spectre(spectre, module_spectre, taille_spectre);
		for(j=0; j<taille_spectre; j++)
		{
			fprintf(fichier_module, "%lf\n", module_spectre[j]);
		}
		
		// recherche du maximum du spectre
		max_search_table_float (module_spectre, taille_spectre, &max_spectre, &indice_max_spectre);
		
		// sauvegarde et affichache du pitch
		resultat_test[i] = (indice_max_spectre / temps_acquisition_pitch );
		if (i>0)
		{
			if ( resultat_test[i] != resultat_test[i-1])
			{
				printf(" l'interlocuteur à changer à %f secondes\n", i*temps_acquisition_pitch);
			}
		}
		printf("le resultat du test %d à la frequence %f\n", i, resultat_test[i]);
	}
	
	fclose(fichier_vecteur_son);
	fclose(fichier_module);
	
	return 0;
}

