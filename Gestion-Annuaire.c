// Spécification formelle : Précondition doit être très courte car une fonction fait quelque chose de très précis
// Interdire les ',' dans les input
// Enlever les pointeurs dans les fonctions où je n'ai pas besoin de modifier les valeurs
// fflush avec la méthode du TP6 si jamais ça marche pas sur un certain OS

// La recherche et l'affichage des données sur un client à partir de son nom, son prénom et son numéro de téléphone ou son adresse mél (une occurrence car ces couples sont uniques => recherche dichotomique => trié ?)
// Nom Prénom Tel / Nom Prénom Mail
// OU
// Nom Prénom Tel / Mail

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

/***************Prototype de fonction***************/
void Clear();
void Pause();
char * ChoixColonne(infos * personne, int value);
void Ouverture(infos personne[5200], int * cpt_ligne);
void AffichageComplet(infos personne, int indice);
void AffichageUnique(char * value);
void Ajout(infos * personne, int * cpt_ligne);
void Modif(infos * personne, int indice);
void SaisiInfo(char * value, int size);
void EcritureFichier(FILE * annuaire, infos personne);
void DonneeManquante(infos personne[5200], int cpt_ligne);
char DonneeEmpty(infos personne);
void Sauvegarde(infos personne[5200], int cpt_ligne);
void TriInsertion(infos personne[5200], int colonne);
void TriSelection(infos (*personne)[], int colonne, int cpt_ligne);

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

void Ouverture(infos personne[5200], int * cpt_ligne)
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
				ChoixColonne(&personne[(*cpt_ligne)], cpt_virgule)[cpt_char] = '\0';
				cpt_virgule++;
				cpt_var = 0;
			}
			else
			{
				ChoixColonne(&personne[(*cpt_ligne)], cpt_virgule)[cpt_var] = ligne[cpt_char];
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

void AffichageComplet(infos personne, int indice) // créer un affichage réduit si jamais je doit afficher plusieurs clients
{
	int i, taille_aff;
	printf("%*d | ", 4, indice);
	for (i = 0; i <= 5; i++)
	{
		switch (i)
		{
		case 0:
			taille_aff = 20;
			break;
		
		case 1:
			taille_aff = 20;
			break;

		case 2:
			taille_aff = 15;
			break;

		case 3:
			taille_aff = taille_code_postal - 1;
			break;

		case 4:
			taille_aff = taille_telephone - 1;
			break;

		case 5:
			taille_aff = 30;
			break;
		}
		printf("%*.*s | ", -taille_aff, taille_aff, ChoixColonne(&personne, i));
	}
	taille_aff = 20;
	printf("%*.*s\n", -taille_aff, taille_aff, ChoixColonne(&personne, i));
}

void AffichageUnique(char * value)
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
	while ((strlen((*personne).prenom) == 0
		 && strlen((*personne).nom) == 0
		 && strlen((*personne).ville) == 0
		 && strlen((*personne).code_postal) == 0
		 && strlen((*personne).telephone) == 0
		 && strlen((*personne).email) == 0
		 && strlen((*personne).metier) == 0)
		 || (strlen((*personne).telephone) == 0)
	);
	(*cpt_ligne)++;
}

void Modif(infos * personne, int indice)
{
	int nb_col;
	do
	{
		Clear();
		printf("1: Prenom, 2: Nom, 3: Ville Code, 4: postal, 5: Telephone, 6: Email, 7: Metier\n\nSaisissez le numero de la colonne a modifier (0 pour quitter): ");
		scanf("%d", &nb_col);
		fflush(stdin);
		if (nb_col >= 1 && nb_col <= 7)
		{
			printf("\nPersonne : %d\n", indice);
			printf("Valeur actuelle : ");
			AffichageUnique(ChoixColonne(&(*personne), nb_col-1));
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

void EcritureFichier(FILE * annuaire, infos personne)
{
	int i = 0;
	for (i; i <= 5; i++)
	{
		fprintf(annuaire, "%s,", ChoixColonne(&personne, i));
	}
	fprintf(annuaire, "%s\n", ChoixColonne(&personne, i));
}

void DonneeManquante(infos personne[5200], int cpt_ligne)
{
	int indice = 0, cpt_clientvide = 0;
	for (indice = 0; indice <= cpt_ligne; indice++)
	{
		if (DonneeEmpty(personne[indice]) == 1)
		{
			cpt_clientvide++;
			AffichageComplet(personne[indice], indice);
		}
	}
	printf("\nIl y a %d clients ayant au moins une case vide\n\n", cpt_clientvide);
}

char DonneeEmpty(infos personne)
{
	for (int i = 0; i <= 6; i++)
	{
		if (strlen(ChoixColonne(&personne, i)) == 0)
		{
			return 1;
		}
	}
	return 0;
}

void Sauvegarde(infos personne[5200], int cpt_ligne)
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
		EcritureFichier(save_file, personne[i]);
	}
	fclose(save_file);
	printf("Sauvegarde effectue (annuaire_sauvegarde.csv)\n\n");
}

void TriInsertion(infos personne[5200], int colonne)
{
	int i = 0, j;
	char petit[taille];
	while (i < 5200)
	{
		int x = 0;
		for (x; ChoixColonne(&personne[i], colonne)[x] != '\0'; x++)
		{
			petit[x] = ChoixColonne(&personne[i], colonne)[x];
			// printf("%d %c\n", x, petit[x]);
		}
		petit[x] = '\0';
		// printf("%d %c\n", x, petit[x]);
		// Pause();
		j = i - 1;
		while (j >= 0 && petit < ChoixColonne(&personne[j], colonne))
		{
			int y = 0;
			for (y; ChoixColonne(&personne[j], colonne)[y] != '\0'; y++)
			{
				ChoixColonne(&personne[j + 1], colonne)[y] = ChoixColonne(&personne[j], colonne)[y];
			}
			ChoixColonne(&personne[j + 1], colonne)[y] = '\0';
			j--;
		}
		int z = 0;
		for (z; petit[z] != '\0'; z++)
		{
			ChoixColonne(&personne[j + 1], colonne)[z] = petit[z];
		}
		ChoixColonne(&personne[j + 1], colonne)[z] = '\0';
		i++;
	}
}

void TriSelection(infos (*personne)[], int colonne, int cpt_ligne)
{
	int i = 0, j, ipp;
	infos petit;
	while (i < cpt_ligne - 1)
	{
		ipp = i;
		petit = (*personne)[ipp];
		j = i + 1;
		while (j < cpt_ligne)
		{
			if (strcasecmp(ChoixColonne(&petit, colonne), ChoixColonne(&(*personne)[j], colonne)) > 0)
			{
				ipp = j;
				petit = (*personne)[ipp];
			}
			j++;
		}
		(*personne)[ipp] = (*personne)[i];
		(*personne)[i] = petit;
		i++;
	}
}

int main()
{
	infos personne[5200];
	int cpt_ligne = 0;
	int choix_menu, colonne;
	int nb_recherche, nb_modif;
	/***************Lecture du csv, rempli le tableau de structure***************/
	Ouverture(personne, &cpt_ligne);
	/***************Menu***************/
	do
	{
		// Clear();  // en commentaire pour pouvoir voir les erreurs
		printf("Bienvenue dans le menu du gestionnaire d'annuaire\n");
		printf("\t-Saisir 1 pour effectuer une recherche par indice\n");
		printf("\t-Saisir 2 pour ajouter une personne a l'annuaire\n");
		printf("\t-Saisir 3 pour modifier une personne dans l'annuaire\n");
		printf("\t-Saisir 4 pour lister les personnes avec au moins une donnee manquante\n");
		printf("\t-Saisir 5 pour effectuer une sauvegarde dans un nouveau fichier\n");
		printf("\t-Saisir 6 pour effectuer un tri par insertion\n");
		printf("\t-Saisir 7 pour quitter\n\n");
		scanf("%d", &choix_menu);
		fflush(stdin);
		if (choix_menu >= 1 && choix_menu <= 7)
		{
			switch (choix_menu)
			{
			/***************Recherche par indice***************/
			case 1:
				do
				{
					Clear();
					printf("Saisir le numero de la personne a rechercher, il y a %d personnes rensignees (0 pour quitter) : ", cpt_ligne);
					scanf("%d", &nb_recherche);
					fflush(stdin);
					if (nb_recherche > 0 && nb_recherche <= cpt_ligne)
					{
						printf("\n");
						AffichageComplet(personne[nb_recherche-1], nb_recherche);
						printf("\n");
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

			/***************Ajout d'une personne***************/
			case 2:
				Clear();
				Ajout(&personne[cpt_ligne], &cpt_ligne);
				printf("\n");
				Pause();
				Clear();
				break;

			/***************Modification d'une personne***************/
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

			/***************Client avec au moins une case vide***************/
			case 4:
				Clear();
				DonneeManquante(personne, cpt_ligne - 1);
				Pause();
				Clear();
				break;

			/***************Sauvegarde dans un nouveau fichier***************/
			case 5:
				Clear();
				Sauvegarde(personne, cpt_ligne - 1);
				Pause();
				Clear();
				break;

			/***************Tri par sélection***************/
			case 6:
				do
				{
					Clear();
					printf("1: Prenom, 2: Nom, 3: Ville, 4: Code postal, 5: Telephone, 6: Email, 7: Metier\n\nSaisir le numero de la colonne selon laquelle l'annuaire va etre trie : ");
					scanf("%d", &colonne);
					fflush(stdin);
					if (colonne >= 1 && colonne <= 7)
					{
						// TriInsertion(personne, colonne-1);
						TriSelection(&personne, colonne - 1, cpt_ligne);
						printf("\nLe tri par selection a ete effectue\n\n");
					}
					else
					{
						printf("\nErreur de saisie\n\n");
					}
					Pause();
				}
				while (colonne < 1 || colonne > 7);
				break;

			case 7:
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
	while (choix_menu != 7);
	return 0;
}