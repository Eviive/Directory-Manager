// #define chemin_annuaire "annuaire_test.csv"
#define chemin_annuaire_sauvegarde "annuaire_sauvegarde.csv"

#define taille 70
#define taille_code_postal 6
#define taille_telephone 15

typedef struct informations
{
	char prenom[taille], nom[taille], ville[taille], code_postal[taille_code_postal], telephone[taille_telephone], email[taille], metier[taille];
} infos;

/**
:postcondition : détermine la commande a effectuer pour clear en fonction de l'OS
*/
void Clear();

/**
:postcondition : détermine la commande a effectuer pour effectuer une pause en fonction de l'OS
*/
void Pause();

/**
:entrée personne : pointeur d'une structure de type infos
:entrée value : int
:pré-condition : value est entre 0 et 6
:postcondition : renvoie le pointeur d'une des catégorie de la personne
*/
char * ChoixColonne(infos * personne, int value);

/**
:entrée value : int
:pré-condition : value est entre 0 et 6
:postcondition : renvoie la chaine de caractères correspondant au nom de la catégorie
*/
char * NomColonne(int value);

/**
:entrée personne : tableau de structures de type infos
:entrée indice_personne : tableau d'unsigned int
:entrée cpt_ligne : pointeur d'unsigned int
:pré-condition : cpt_ligne égal 0
:postcondition : lit l'annuaire, stock toutes les informations dans le tableau de structures infos, cpt_ligne est égal au nombre de personne
*/
void Ouverture(infos personne[], int unsigned indice_personne[], unsigned int * cpt_ligne);

/**
:entrée personne : structure de type infos
:entrée indice : int
:pré-condition : indice égal à l'indice de la personne dans l'annuaire
:postcondition : affiche toutes les informations sur la personne
*/
void AffichageComplet(infos personne, int indice);

/**
:entrée value : pointeur de char
:postcondition : affiche la valeur d'entrée si elle est non-nul, sinon affiche N/A
*/
void AffichageUnique(char * value);

/**
:entrée value : pointeur de char
:entrée size : int
:postcondition : demande à l'utilisateur de saisir une valeur puis remplace les ',' par des ' ' et les '\n' par '\0'
*/
void Saisi(char * value, unsigned int size);

/**
:entrée personne : pointeur de structure de type infos
:entrée indice_personne : tableau d'unsigned int
:entrée cpt_ligne : pointeur d'unsigned int
:postcondition : ajoute une personne à la dernière ligne de l'annuaire
*/
void Ajout(infos * personne, unsigned int indice_personne[], unsigned int * cpt_ligne);

/**
:entrée personne : tableau de structures de type infos
:entrée indice_personne : tableau d'unsigned int
:entrée cpt_ligne : pointeur d'unsigned int
:entrée nb_suppression : int
:pré-condition : nb_suppression égal à l'indice de la personne à supprimer
:postcondition : décale toutes les personnes après l'indice passé en paramètre, permet d'écraser la personne à supprimer
*/
void Suppression(infos personne[], unsigned int indice_personne[], unsigned int * cpt_ligne, int nb_suppression);

/**
:entrée/sortie personne : pointeur de structure de type infos
:pré-condition : personne est la structure à modifier
:postcondition : modifie une des valeurs de la structure passé en entrée
*/
void Modif(infos * personne);

/**
:entrée personne : tableau de structures de type infos
:entrée indice_personne : tableau d'unsigned int
:entrée cpt_ligne : unsigned int
:postcondition : Affiche les données sur une personne si la fonction DonneeEmpty renvoie 1
*/
void DonneeManquante(infos personne[], unsigned int indice_personne[], unsigned int cpt_ligne);

/**
:entrée personne : structure de type infos
:postcondition : renvoie 1 si une des chaines de caractères de la structure est vide, sinon renvoie 0
*/
char DonneeEmpty(infos personne);

/**
:entrée personne : tableau de structures de type infos
:entrée indice_personne : tableau d'unsigned int
:entrée cpt_ligne : unsigned int
:postcondition : écrit dans un fichier de sauvegarde le contenu de chaque structure sur une ligne
*/
void Sauvegarde(infos personne[], unsigned int indice_personne[], unsigned int cpt_ligne);

/**
:entrée personne : tableau de structures de type infos
:entrée indice_personne : tableau d'unsigned int
:entrée cpt_ligne : unsigned int
:entrée nb_colonne : unsigned int
:pré-condition : nb_colonne entre 0 et 6
:postcondition : tri le tableau selon la colonne passé en paramètre
*/
void Tri(infos personne[], unsigned int indice_personne[], unsigned int nb_colonne, unsigned int cpt_ligne);

/**
:entrée personne : tableau de structures de type infos
:entrée indice_personne : tableau d'unsigned int
:entrée cpt_ligne : unsigned int
:entrée str_prenom, str_nom, str_third : tableau de caractères
:entrée nb_colonne : unsigned int
:pré-condition : nb_colonne entre 0 et 6
:postcondition : renvoie l'indice de la personne si elle est trouvée dans le tableau de structure, sinon renvoie -1
*/
int Recherche(infos personne[], unsigned int indice_personne[], unsigned int cpt_ligne, char str_prenom[], char str_nom[], char str_third[], unsigned int nb_colonne);

/**
:entrée personne : tableau de structures de type infos
:entrée indice_personne : tableau d'unsigned int
:entrée cpt_ligne : pointeur d'unsigned int
:entrée nb_colonne : unsigned int
:entrée str_filtre : tableau de caractères
:pré-condition : nb_colonne entre 0 et 6
:postcondition : effectue une recherche filtrée triée ("contient" et "début de chaine") et affiche les données des occurences trouvées
*/
void FiltreTrie(infos personne[], unsigned int indice_personne[], unsigned int cpt_ligne, unsigned int nb_colonne, char str_filtre[]);

/**
:entrée personne : tableau de structures de type infos
:entrée indice_personne : tableau d'unsigned int
:entrée cpt_ligne : pointeur d'unsigned int
:entrée nb_colonne : unsigned int
:entrée str_filtre : tableau de caractères
:pré-condition : nb_colonne entre 0 et 6
:postcondition : effectue une recherche filtrée ("fin de chaine") et affiche les données des occurences trouvées
*/
void FinDeChaine(infos personne[], unsigned int indice_personne[], unsigned int cpt_ligne, unsigned int nb_colonne, char str_filtre[]);

/**
:entrée personne : tableau de structures de type infos
:entrée indice_personne : tableau d'unsigned int
:entrée cpt_ligne : pointeur d'unsigned int
:entrée nb_colonne : unsigned int
:entrée str_filtre : tableau de caractères
:pré-condition : nb_colonne entre 0 et 6
:postcondition : effectue une recherche filtrée ("sous-chaine") et affiche les données des occurences trouvées
*/
void SousChaine(infos personne[], unsigned int indice_personne[], unsigned int cpt_ligne, unsigned int nb_colonne, char str_filtre[]);