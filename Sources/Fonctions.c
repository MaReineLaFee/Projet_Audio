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
	fprintf(stderr, "je lis le titre\n");
	int i;
	
	fseek(fichier, 11*sizeof(int), SEEK_SET);
	
	if(fichier==NULL)
		{
			printf("impossible d'ouvrir");
		}
		
	else
		{
			fprintf(stderr, "avant de remplir\n");
			for(i=0; i<nombre_echantillon; i++)
			{
			fread(&vecteur_son[i], sizeof(short), 1, fichier);
			}
			//fread( vecteur_son, sizeof(short), nombre_echantillon, fichier);
			fprintf(stderr, "après \n");
		}
	fclose(fichier);
}

/**
 * 
 * 
 **/

void creation_spectre(int n, double* signal, fftw_complex* spectre)
{
	fftw_plan plan;
	
	plan = fftw_plan_dft_r2c_1d(n, signal, spectre, FFTW_FORWARD );
	fftw_execute(plan);
	fftw_destroy_plan(plan);

}
