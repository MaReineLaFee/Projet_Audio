#include <fftw3.h>
#include <stdlib.h>
#include "../Include/Fonctions.h"
#include <math.h>



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
	
	fprintf(stderr, "taille_wav : j'ai trouvé la taille\n");
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
 *  This fonction create a signal of sinus of 2 differents frequencies
 *  The first half of the signal is a sinus with the first frequency (ex a standart guy frequency)
 *  The second half of the singal is a sinus with the seconde frequency (ex a standard girl frequency)
 */
 
void signal_sinus(double* vecteur_son, int nombre_echantillon, double frequence_echantillonnage, double frequence_garcon, double frequence_fille)
{
	int i;
	
	for (i=0; i<nombre_echantillon; i++)
	{
		if (i<=(nombre_echantillon/2))
		{
			vecteur_son[i] = sin(2*M_PI*frequence_garcon*i*(1/frequence_echantillonnage));
		}
		
		else
		{
			vecteur_son[i] = sin(2*M_PI*frequence_fille*i*(1/frequence_echantillonnage));
		}
	}
}

/** 
 * This fonction makes the complex spectrum of a signal
 **/

void creation_spectre(int nombre_echantillon, double* signal, fftw_complex* spectre)
{
	fftw_plan plan;
	
	//fprintf(stderr, "creation_spectre : j'ai cree le plan\n");
	
	plan = fftw_plan_dft_r2c_1d(nombre_echantillon, signal, spectre, FFTW_ESTIMATE | FFTW_PRESERVE_INPUT); //FFTW_FORWARD );
	
	//fprintf(stderr, "creation_spectre : j'ai rempli le plan\n");
	
	fftw_execute(plan);
	//fprintf(stderr, "creation_spectre : j'ai execute le plan\n");
	
	fftw_destroy_plan(plan);
	//fprintf(stderr, "creation_spectre : j'ai detruit le plan\n");

}
/**
 * This function convert the complex spectrum into is module
 **/

void module_du_spectre(fftw_complex* spectre, double* module, int taille_spectre)
{
	int i;
	
	for (i=0; i<taille_spectre; i++)
	{
		module[i] = sqrt(spectre[i][0]*spectre[i][0] + spectre[i][1]*spectre[i][1]);
	}

}

/**
 *  Search the max of a table of float of a column and idim lignes 
 */

void max_search_table_double(double* tableau, int idim, double* max, int* indice)
{
	int i;
	*indice = 0;
	*max = tableau[0];
	
	for (i=1; i<idim; i++)
	{
		if (tableau[i]> *max)
		{
			*max=tableau[i];
			*indice=i;
		}
	}
}

/**
 * This fonction take a portion of the signal from "indice_debut" and long of "taille_fenetre" samples
 */
 
 void signal_reduit_fenetre(double* vecteur_son, double* signal_fenetre, int indice_debut, int taille_fenetre)
 {
	 int i;
	 int indice_balayage = 0;
	 
	 for(i=0; i<taille_fenetre; i++)
	 {
		 indice_balayage = indice_debut + i;
		 signal_fenetre[i]=vecteur_son[indice_balayage];
	 }
 }
 
 /** 
  * This fonction create a gausian signal sampled at frequence_echantillonnage of lenght nombre_echantillon, of centrale position indice_moyenne and of relative sigma indice_sigma
  * in the function, indice_moyenne and indice_sigma are divided by the sampled frequency to create the temporal mean and the temporal sigma
  **/

void signal_gaussien(double* vecteur_son, int nombre_echantillon, double frequence_echantillonnage, int indice_moyenne, int indice_sigma)
{
	int i;
	double indice;
	double argument;
	double indice_moyenne_double = double(indice_moyenne);
	double indice_sigma_double = double(indice_sigma);
	
	fprintf(stderr, "signal_gaussien : avant de faire ma gaussienne\n");
	for (i=0; i<nombre_echantillon; i++)
	{
		indice = double(i);
		argument = (indice - indice_moyenne_double)*(indice - indice_moyenne_double);
		//vecteur_son[i]= (1/(sqrt(2*M_PI)*indice_sigma_double))*exp(-(1/(2*indice_sigma_double*indice_sigma_double))*argument);
		vecteur_son[i]= (frequence_echantillonnage/(sqrt(2*M_PI)*indice_sigma_double))*exp(-(1/(2*indice_sigma_double*indice_sigma_double))*argument);
	}
	fprintf(stderr, "signal_gaussien : après avoir fait la gaussienne\n");
}

/**
 * 
 **/
 
double integral_signal_echantillonne_double(double* vecteur, int taille_vecteur, double frequence_echantillonnage)
 {
	 int i;
	double module=0;
	
	for (i=0;i<taille_vecteur;i++)
	{
		module=module+(vecteur[i]/frequence_echantillonnage);
	}
	
	return module;
 }
/**
 * This fonction compute the approximate integral of the signal vecteur sampled at the frequence_echantillonnage frequency
 * And normalize this signal so its approximate integral is one.
 **/

void normalisation_signal_echantillonne_double(double* vecteur, int taille_vecteur, double frequence_echantillonnage)
{
	int i;
	double module=integral_signal_echantillonne_double(vecteur, taille_vecteur, frequence_echantillonnage);
	
	for (i=0; i<taille_vecteur; i++)
	{
		vecteur[i] = vecteur[i]/module;
	}
	
}
