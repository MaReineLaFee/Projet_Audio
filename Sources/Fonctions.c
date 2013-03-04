#include <fftw3.h>
#include <stdlib.h>
#include "../Include/Fonctions.h"


int taille_wav(char* titre, int taille_header)
{
	FILE* fichier;
	
	fichier = fopen(titre, "rb");
	fprintf(stderr, "taille_wav : je lis le titre\n");
	int size = 0;
	
	
	if(fichier==NULL)
		{
			printf("taille_wav : impossible d'ouvrir");
		}
		
	else
		{
			fseek(fichier, 0, SEEK_END);
			size = (ftell(fichier) - taille_header )/2;
		}
		
	fclose(fichier);
	
	return size;
	
}

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

void lire_wav(char* titre, double* vecteur_son, int nombre_echantillon, int taille_header )
{
	FILE* fichier;
	
	fichier = fopen(titre, "rb");
	fprintf(stderr, "lire_wav : je lis le titre\n");
	short* buffer=(short*)malloc(nombre_echantillon*sizeof(short));
	int i;
	
	
	if(fichier==NULL)
		{
			printf("lire_wav : impossible d'ouvrir");
		}
		
	else
		{
			fprintf(stderr, "lire_wav : avant de remplir\n");
			
			fseek(fichier, taille_header, SEEK_SET);
			fprintf(stderr, "lire_wav : j'ai sauté les lignes\n");
			
			fread( buffer, sizeof(short), nombre_echantillon, fichier);
			
			fprintf(stderr, "lire_wav : j'ai rempli le buffer\n");
			
			for(i=0; i<nombre_echantillon; i++)
			{
			vecteur_son[i] = buffer[i];
			}
			
			fprintf(stderr, "lire_wav : j'ai rempli le vecteur son \n");
		}
	fclose(fichier);
	free(buffer);
}

/** 
 * This fonction makes the spectrum of a signal
 **/

void creation_spectre(int nombre_echantillon, double* signal, fftw_complex* spectre)
{
	fftw_plan plan;
	
	fprintf(stderr, "creation_spectre : j'ai cree le plan\n");
	
	plan = fftw_plan_dft_r2c_1d(nombre_echantillon, signal, spectre, FFTW_ESTIMATE | FFTW_PRESERVE_INPUT); //FFTW_FORWARD );
	
	fprintf(stderr, "creation_spectre : j'ai rempli le plan\n");
	
	fftw_execute(plan);
	fprintf(stderr, "creation_spectre : j'ai execute le plan\n");
	
	fftw_destroy_plan(plan);
	fprintf(stderr, "creation_spectre : j'ai detruit le plan\n");

}
