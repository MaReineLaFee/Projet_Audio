
int taille_wav(char* titre, int taille_header);

void lire_wav(char* titre, double* vecteur_son, int nombre_echantillon, int taille_header );

void creation_spectre(int nombre_echantillon, double* signal, fftw_complex* spectre);

