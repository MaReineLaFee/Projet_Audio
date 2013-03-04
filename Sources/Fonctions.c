#include <fftw3.h>
#include <stdlib.h>
#include "../Include/Fonctions.h"


/**
 * This fonction allow you to read a .wav file
 * The entries of the fonction are
 * 		the name of the file you want to read
 * 		the vector of short in which it will be stored
 * 		the number of short thar are in your wav file
 * 
 * Please notice that wav file have a header of 44 octets
 * 
 **/

void lire_wav(char* titre, short* vecteur_son, int nombre_echantillon )
{
	FILE* fichier;
	
	fichier = fopen(titre, "rb");
	fprintf(stderr, "lire_wav : je lis le titre\n");
	int i;
	
	
	if(fichier==NULL)
		{
			printf("lire_wav : impossible d'ouvrir");
		}
		
	else
		{
			fprintf(stderr, "lire_wav : avant de remplir\n");
			
			fseek(fichier, 11*sizeof(int), SEEK_SET);
			fprintf(stderr, "lire_wav : j'ai sauté les lignes\n");
			
			for(i=0; i<nombre_echantillon; i++)
			{
			fread(&vecteur_son[i], sizeof(short), 1, fichier);
			}
			//fread( vecteur_son, sizeof(short), nombre_echantillon, fichier);
			fprintf(stderr, "lire_wav : après \n");
		}
	fclose(fichier);
}

/** 
 * This fonction makes the spectrum of a signal
 * 
 **/

void creation_spectre(int nombre_echantillon, double* signal, fftw_complex* spectre)
{
	fftw_plan plan;

	
	
	fprintf(stderr, "creation_spectre : j'ai cree le plan\n");
	
	plan = fftw_plan_dft_r2c_1d(nombre_echantillon, signal, spectre, FFTW_FORWARD );
	
	fprintf(stderr, "creation_spectre : j'ai rempli le plan\n");
	
	fftw_execute(plan);
	fprintf(stderr, "creation_spectre : j'ai execute le plan\n");
	
	fftw_destroy_plan(plan);
	fprintf(stderr, "creation_spectre : j'ai detruit le plan\n");

}
