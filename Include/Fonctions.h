
int taille_wav(char* titre, int taille_header);

void lire_wav(char* titre, double* vecteur_son, int nombre_echantillon, int taille_header );

void signal_sinus(double* vecteur_son, int nombre_echantillon, double frequence_echantillonnage, double frequence_fille, double frequence_garcon);

void creation_spectre(int nombre_echantillon, double* signal, fftw_complex* spectre);

void module_du_spectre(fftw_complex* spectre, float* module, int taille_spectre);

void max_search_table_float (float* tableau, int idim, float* max, int* indice);

void signal_reduit_fenetre(double* vecteur_son, double* signal_fenetre, int indice_debut, int taille_fenetre);
