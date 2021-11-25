// Précondition doit être très courte car une fonction fait quelque chose de très précis

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define chemin_annuaire "Annuaire/annuaire_test.csv"
#define chemin_annuaire_sauvegarde "Annuaire/annuaire_sauvegarde.csv"

#define taille 70
#define taille_code_postal 6
#define taille_telephone 15

typedef struct informations
{
	char prenom[taille], nom[taille], ville[taille], code_postal[taille_code_postal], telephone[taille_telephone], email[taille], metier[taille];
} infos;

/****************Prototype de fonction****************/
void Clear();
void Pause();
char * ChoixColonne(infos * personne, int value);
void Ouverture(infos (*personne)[], int * cpt_ligne);
void AffichageRecherche(infos *personne, int indice);
void AffichageEmpty(char * value);
void Ajout(infos * personne, int * cpt_ligne);
void Modif(infos *personne, int indice);
void SaisiInfo(char * value, int size);
void EcritureFichier(FILE * fichier, infos * personne);
void DonneeManquante(infos (*personne)[], int cpt_ligne);
int DonneeEmpty(infos * personne);
void Sauvegarde(infos  (*personne)[], int cpt_ligne);

void Clear()
{
    #ifdef _WIN32
        system("cls");
    #elif defined __unix__
        system("clear");
    #endif
}

void Pause()
{
    #ifdef _WIN32
        system("pause > nul | echo Appuyez sur une touche pour continuer...");
    #elif defined __unix__
		system("read -n1 -r -p 'Appuyez sur une touche pour continuer...'");
    #endif
}

char * ChoixColonne(infos * personne, int value)
{
    switch (value)
    {
    case 0:
        return (*personne).prenom;
    
    case 1:
        return (*personne).nom;

    case 2:
        return (*personne).ville;

    case 3:
        return (*personne).code_postal;

    case 4:
        return (*personne).telephone;

    case 5:
        return (*personne).email;

    case 6:
        return (*personne).metier;

	default:
		printf("Erreur switch");
    }
}

void Ouverture(infos (*personne)[], int * cpt_ligne)
{
	char ligne[300];
	int cpt_char = 0, cpt_virgule = 0, cpt_var = 0;

	/****************Lecture du fichier****************/
	FILE * annuaire_file = fopen(chemin_annuaire, "r");
	if (annuaire_file == NULL)
	{
		printf("Echec ouverture fichier\n");
		exit(EXIT_FAILURE);
	}
	/****************Assignation de toutes les cellules à des variables****************/
	while (fgets(ligne, sizeof(ligne), annuaire_file) != NULL)
	{
		while (ligne[cpt_char] != '\0')
		{
			if (ligne[cpt_char] == ',' || ligne[cpt_char] == '\n')
			{
				ChoixColonne(&(*personne)[(*cpt_ligne)], cpt_virgule)[cpt_char] = '\0';
				cpt_virgule++;
				cpt_var = 0;
			}
			else
			{
				ChoixColonne(&(*personne)[(*cpt_ligne)], cpt_virgule)[cpt_var] = ligne[cpt_char];
				cpt_var++;
			}
			cpt_char++;
		}
		cpt_char = 0;
		cpt_virgule = 0;
		(*cpt_ligne)++;
	}
	fclose(annuaire_file);
}

void AffichageRecherche(infos *personne, int indice) // créer un affichage réduit si jamais je doit afficher plusieurs clients
{
	printf("\nPersonne %d\n", indice);
	printf("Prenom       : ");
	AffichageEmpty(ChoixColonne(&(*personne), 0));

	printf("Nom          : ");
	AffichageEmpty(ChoixColonne(&(*personne), 1));

	printf("Ville        : ");
	AffichageEmpty(ChoixColonne(&(*personne), 2));

	printf("Code postal  : ");
	AffichageEmpty(ChoixColonne(&(*personne), 3));

	printf("Telephone    : ");
	AffichageEmpty(ChoixColonne(&(*personne), 4));

	printf("Email        : ");
	AffichageEmpty(ChoixColonne(&(*personne), 5));

	printf("Metier       : ");
	AffichageEmpty(ChoixColonne(&(*personne), 6));

	printf("\n");
}

void AffichageEmpty(char * value)
{
	if (strlen(value) != 0 )
	{
		printf("%s\n", value);
	}
	else
	{
		printf("N/A\n");
	}
}

void Ajout(infos * personne, int * cpt_ligne)
{
	do
	{
		Clear();
		int size = sizeof((*personne).nom);
		printf("Saisir le prenom : ");
		SaisiInfo(ChoixColonne(&(*personne), 0), size);
		printf("Saisir le nom : ");
		SaisiInfo(ChoixColonne(&(*personne), 1), size);
		printf("Saisir la ville : ");
		SaisiInfo(ChoixColonne(&(*personne), 2), size);
		printf("Saisir le code postal : ");
		SaisiInfo(ChoixColonne(&(*personne), 3), sizeof((*personne).code_postal));
		printf("Saisir le numero de telephone : ");
		SaisiInfo(ChoixColonne(&(*personne), 4), sizeof((*personne).telephone));
		printf("Saisir le email : ");
		SaisiInfo(ChoixColonne(&(*personne), 5), size);
		printf("Saisir le metier : ");
		SaisiInfo(ChoixColonne(&(*personne), 6), size);
	}
	while (strlen((*personne).prenom) == 0
		&& strlen((*personne).nom) == 0
		&& strlen((*personne).ville) == 0
		&& strlen((*personne).code_postal) == 0
		&& strlen((*personne).telephone) == 0
		&& strlen((*personne).email) == 0
		&& strlen((*personne).metier) == 0
	);
	(*cpt_ligne)++;
}

void Modif(infos *personne, int indice)
{
	int nb_col;
	do
	{
		Clear();
		printf("(1: Prenom, 2: Nom, 3: Ville Code, 4: postal, 5: Telephone, 6: Email, 7: Metier)\n\nSaisissez le numero de la colonne a modifier (0 pour quitter): ");
		scanf("%d", &nb_col);
		fflush(stdin);
		if (nb_col >= 1 && nb_col <= 7)
		{
			printf("\nSaisir la nouvelle valeur : ");
			if (nb_col == 4)  // faire une fonction qui renvoie la taille si j'en ai besoin
			{
				SaisiInfo(ChoixColonne(&(*personne), nb_col-1), taille_code_postal);
			}
			else if (nb_col == 5)
			{
				SaisiInfo(ChoixColonne(&(*personne), nb_col-1), taille_telephone);
			}
			else
			{
				SaisiInfo(ChoixColonne(&(*personne), nb_col-1), taille);
			}
			printf("\n");
			Pause();
			Clear();
		}
		else if (nb_col != 0)
		{
			printf("\nErreur de saisie\n\n");
			Pause();
		}
	}
	while (nb_col != 0);
}

void SaisiInfo(char * value, int size)
{
	fgets(value, size, stdin);
	fflush(stdin);
	for(int i = 0; i < strlen(value); i++ )
	{
    	if(value[i] == '\n')
		{
			value[i] = '\0';
		}
	}
}

void EcritureFichier(FILE * annuaire, infos * personne)
{
	int i = 0;
	for (i; i <= 5; i++)
	{
		fprintf(annuaire, "%s,", ChoixColonne(&(*personne), i));
	}
	fprintf(annuaire, "%s\n", ChoixColonne(&(*personne), i));
}

void DonneeManquante(infos (*personne)[], int cpt_ligne)
{
	int indice = 0, cpt_clientvide = 0;
	for (indice = 0; indice <= cpt_ligne; indice++)
	{
		if (DonneeEmpty(&((*personne)[indice])) == 1)
		{
			cpt_clientvide++;
			AffichageRecherche(&(*personne)[indice], indice);
		}
	}
	printf("Il y a %d clients ayant au moins une case vide\n\n", cpt_clientvide);
}

int DonneeEmpty(infos * personne)
{
	for (int i = 0; i <= 6; i++)
	{
		if (strlen(ChoixColonne(&(*personne), i)) == 0)
		{
			return 1;
		}
	}
	return 0;
}

void Sauvegarde(infos  (*personne)[], int cpt_ligne)
{
	printf("Creation du fichier de sauvegarde\n\n");
	FILE * save_file = fopen(chemin_annuaire_sauvegarde, "w");
	if (save_file == NULL)
	{
		printf("Echec creation du fichier de sauvegarde\n");
		exit(EXIT_FAILURE);
	}
	for (int i = 0; i <= cpt_ligne; i++)
	{
		EcritureFichier(save_file, &((*personne)[i]));
	}
	fclose(save_file);
	printf("Sauvegarde effectue (annuaire_sauvegarde.csv)\n\n");
}

int main()
{
	infos personne[5200];
	infos (*pt_infos)[] = &personne;
	int cpt_ligne = 0;
	int choix_menu;
	int nb_recherche, nb_modif;
	/****************Lecture du csv, rempli le tableau de structure****************/
	Ouverture(pt_infos, &cpt_ligne);
	/****************Menu****************/
	do
	{
		Clear();  // en commentaire pour pouvoir voir les erreurs
		printf("Bienvenue dans le menu du gestionnaire d'annuaire\n");
		printf("\t-Saisir 1 pour effectuer une recherche par indice\n");
		printf("\t-Saisir 2 pour ajouter une personne a l'annuaire\n");
		printf("\t-Saisir 3 pour modifier une personne dans l'annuaire\n");
		printf("\t-Saisir 4 pour lister les personnes avec au moins une donnee manquante\n");
		printf("\t-Saisir 5 pour effectuer une sauvegarde dans un nouveau fichier\n");
		printf("\t-Saisir 6 pour quitter\n\n");
		scanf("%d", &choix_menu);
		fflush(stdin);
		if (choix_menu >= 1 && choix_menu <= 6)
		{
			switch (choix_menu)
			{
			/****************Recherche par indice****************/
			case 1:
				do
				{
					Clear();
					printf("Saisir le numero de la personne a rechercher, il y a %d personnes rensignees (0 pour quitter) : ", cpt_ligne);
					scanf("%d", &nb_recherche);
					fflush(stdin);
					if (nb_recherche > 0 && nb_recherche <= cpt_ligne)
					{
						AffichageRecherche(&personne[nb_recherche-1], nb_recherche);
						Pause();
					}
					else if (nb_recherche != 0)
					{
						printf("\nErreur de saisie\n\n");
						Pause();
					}
				}
				while (nb_recherche != 0);
				break;

			/****************Ajout d'une personne****************/
			case 2:
				Clear();
				Ajout(&personne[cpt_ligne], &cpt_ligne);
				printf("\n");
				Pause();
				Clear();
				break;

			/****************Modification d'une personne****************/
			case 3:
				do
				{
					Clear();
					printf("Saisir le numero de la personne a modifier, il y a %d personnes rensignees (0 pour quitter) : ", cpt_ligne);
					scanf("%d", &nb_modif);
					fflush(stdin);
					if (nb_modif > 0 && nb_modif <= cpt_ligne)
					{
						Modif(&personne[nb_modif-1], nb_modif);
					}
					else if (nb_modif != 0)
					{
						printf("\nErreur de saisie\n\n");
						Pause();
					}
				}
				while (nb_modif != 0);
				break;

			/****************Client avec au moins une case vide****************/
			case 4:
				Clear();
				DonneeManquante(pt_infos, cpt_ligne - 1);
				Pause();
				Clear();
				break;

			/****************Sauvegarde dans un nouveau fichier****************/
			case 5:
				Clear();
				Sauvegarde(pt_infos, cpt_ligne - 1);
				Pause();
				Clear();
				break;

			case 6:
				break;

			default:
				printf("Erreur switch");
				break;
			}
		}
		else
		{
			printf("\nErreur de saisie\n\n");
			Pause();
		}
	}
	while (choix_menu != 6);
	return 0;
}