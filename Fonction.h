#define chemin_annuaire "annuaire_test.csv"
#define chemin_annuaire_sauvegarde "annuaire_sauvegarde.csv"

#define taille 70
#define taille_code_postal 6
#define taille_telephone 15

typedef struct informations
{
	char prenom[taille], nom[taille], ville[taille], code_postal[taille_code_postal], telephone[taille_telephone], email[taille], metier[taille];
} infos;

void Clear();
void Pause();
char * ChoixColonne(infos * personne, int value);
char * NomColonne(int value);
void Ouverture(infos personne[], int indice_personne[], int * cpt_ligne);
void AffichageComplet(infos personne, int indice);
void AffichageUnique(char * value);
void Ajout(infos * personne, int indice_personne[], int * cpt_ligne);
void Suppression(infos personne[], int indice_personne[], int * cpt_ligne, int nb_suppression);
void Modif(infos * personne);
void DonneeManquante(infos personne[], int indice_personne[], int cpt_ligne);
char DonneeEmpty(infos personne);
void Sauvegarde(infos personne[], int indice_personne[], int cpt_ligne);
void Tri(infos personne[], int indice_personne[], unsigned int nb_colonne, int cpt_ligne);
int Recherche(infos personne[], int indice_personne[], int cpt_ligne, char str_prenom[], char str_nom[], char str_third[], unsigned int nb_colonne);
void FiltreTrie(infos personne[], int indice_personne[], int cpt_ligne, unsigned int nb_colonne, char str_filtre[]);
void FinDeChaine(infos personne[], int indice_personne[], int cpt_ligne, unsigned int nb_colonne, char str_filtre[]);
void SousChaine(infos personne[], int indice_personne[], int cpt_ligne, unsigned int nb_colonne, char str_filtre[]);