#include "Fonction.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

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

void Ouverture(infos personne[], int indice_personne[], int * cpt_ligne)
{
	char ligne[300]; //chemin_annuaire[100];
	int cpt_char = 0, cpt_virgule = 0, cpt_var = 0;

	// printf("Saisir le chemin d'acces a l'annuaire : ");
	// scanf("%s", &chemin_annuaire);
	// fflush(stdin);

	/****************Lecture du fichier****************/
	FILE * annuaire_file = fopen(chemin_annuaire, "r");
	if (annuaire_file == NULL)
	{
		printf("\nEchec ouverture fichier\n");
		exit(EXIT_FAILURE);
	}
	/****************Assignation de toutes les cellules à des variables****************/
	while (fgets(ligne, sizeof(ligne), annuaire_file) != NULL)
	{
		indice_personne[(*cpt_ligne)] = (*cpt_ligne);
		while (ligne[cpt_char] != '\0')
		{
			if (ligne[cpt_char] == ',' || ligne[cpt_char] == '\n')
			{
				ChoixColonne(&personne[indice_personne[(*cpt_ligne)]], cpt_virgule)[cpt_char] = '\0';
				cpt_virgule++;
				cpt_var = 0;
			}
			else
			{
				ChoixColonne(&personne[indice_personne[(*cpt_ligne)]], cpt_virgule)[cpt_var] = ligne[cpt_char];
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

void AffichageComplet(infos personne, int indice)
{
	int i, taille_aff;
	printf("%*d | ", 4, indice + 1);
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

		default:
			printf("Erreur switch");
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

void Ajout(infos * personne, int indice_personne[], int * cpt_ligne)
{
	do
	{
		Clear();
		printf("Saisir le prenom : ");
		SaisiInfo(ChoixColonne(personne, 0), taille);
		printf("Saisir le nom : ");
		SaisiInfo(ChoixColonne(personne, 1), taille);
		printf("Saisir la ville : ");
		SaisiInfo(ChoixColonne(personne, 2), taille);
		printf("Saisir le code postal : ");
		SaisiInfo(ChoixColonne(personne, 3), taille_code_postal);
		printf("Saisir le numero de telephone : ");
		SaisiInfo(ChoixColonne(personne, 4), taille_telephone);
		printf("Saisir le email : ");
		SaisiInfo(ChoixColonne(personne, 5), taille);
		printf("Saisir le metier : ");
		SaisiInfo(ChoixColonne(personne, 6), taille);
	}
	while ((strlen((*personne).prenom) == 0
		 && strlen((*personne).nom) == 0
		 && strlen((*personne).ville) == 0
		 && strlen((*personne).code_postal) == 0
		 && strlen((*personne).telephone) == 0
		 && strlen((*personne).email) == 0
		 && strlen((*personne).metier) == 0)
		 || (strlen((*personne).telephone) == 0)
		 || (strlen((*personne).email) == 0)
	);
	indice_personne[(*cpt_ligne)] = (*cpt_ligne);
	(*cpt_ligne)++;
}

void Suppression(infos personne[], int indice_personne[], int * cpt_ligne, int nb_suppression)
{
	for (int i = nb_suppression; i < *(cpt_ligne) - 1; i++)
	{
		personne[indice_personne[i]] = personne[indice_personne[i + 1]];
	}
	(*cpt_ligne)--;
}

void Modif(infos * personne)
{
	char nb_col;
	printf("\n1: Prenom, 2: Nom, 3: Ville, 4: Code postal, 5: Telephone, 6: Email, 7: Metier\n(0 pour quitter)\n\nSaisissez le numero de la colonne a modifier : ");
	scanf("%d", &nb_col);
	fflush(stdin);
	if (nb_col >= 1 && nb_col <= 7)
	{
		printf("\nValeur actuelle : ");
		AffichageUnique(ChoixColonne(personne, nb_col-1));
		printf("Saisir la nouvelle valeur : ");
		if (nb_col == 4)
		{
			SaisiInfo(ChoixColonne(personne, nb_col-1), taille_code_postal);
		}
		else if (nb_col == 5)
		{
			SaisiInfo(ChoixColonne(personne, nb_col-1), taille_telephone);
		}
		else
		{
			SaisiInfo(ChoixColonne(personne, nb_col-1), taille);
		}
		printf("\n");
	}
	else if (nb_col != 0)
	{
		printf("\nErreur de saisie\n\n");
	}
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

void DonneeManquante(infos personne[], int indice_personne[], int cpt_ligne)
{
	int indice = 0, cpt_clientvide = 0;
	for (indice = 0; indice <= cpt_ligne; indice++)
	{
		if (DonneeEmpty(personne[indice_personne[indice]]) == 1)
		{
			cpt_clientvide++;
			AffichageComplet(personne[indice_personne[indice]], indice_personne[indice]);
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

void Sauvegarde(infos personne[], int indice_personne[], int cpt_ligne)
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
		// EcritureFichier(save_file, personne[indice_personne[i]]);
		int j = 0;
		for (j; j <= 5; j++)
		{
			fprintf(save_file, "%s,", ChoixColonne(&personne[indice_personne[i]], j));
		}
		fprintf(save_file, "%s\n", ChoixColonne(&personne[indice_personne[i]], j));
	}
	fclose(save_file);
	printf("Sauvegarde effectue (annuaire_sauvegarde.csv)\n\n");
}

void Tri(infos personne[], int indice_personne[], unsigned int nb_colonne, int cpt_ligne)
{
	int i = 1, j, petit;
	while (i <= cpt_ligne - 1)
	{
		petit = indice_personne[i];
		j = i - 1;
		while (j >= 0 && strcasecmp(ChoixColonne(&personne[indice_personne[j]], nb_colonne), ChoixColonne(&personne[petit], nb_colonne)) > 0)
		{
			indice_personne[j + 1] = indice_personne[j];
			j--;
		}
		indice_personne[j + 1] = petit;
		i++;
	}
}

int Recherche(infos personne[], int indice_personne[], int cpt_ligne, char str_prenom[], char str_nom[], char str_third[], unsigned int nb_colonne)
{
	int i = 0;
	while (i < cpt_ligne && strcasecmp(ChoixColonne(&personne[indice_personne[i]], 0), str_prenom) < 0)
	{
		i++;
	}
	while (i < cpt_ligne && strcasecmp(ChoixColonne(&personne[indice_personne[i]], 0), str_prenom) == 0)
	{
		if (strcasecmp(ChoixColonne(&personne[indice_personne[i]], 1), str_nom) == 0 && strcasecmp(ChoixColonne(&personne[indice_personne[i]], nb_colonne), str_third) == 0)
		{
			AffichageComplet(personne[indice_personne[i]], indice_personne[i]);
			return i;
		}
		i++;
	}
	return -1;
}

void Filtre(infos personne[], int indice_personne[], int cpt_ligne, unsigned int nb_colonne, char str_filtre[], int nb_mode)
{
	/***************Créer une fonction pour chaque groupe de recherche (case 1 + case 3 / case 2 / case 4)***************/
	int i = 0, j;
	switch (nb_mode)
	{
	case 1: // Séquentielle triée
		while (i < cpt_ligne && strcasecmp(ChoixColonne(&personne[indice_personne[i]], nb_colonne), str_filtre) < 0)
		{
			i++;
		}
		while (i < cpt_ligne && strcasecmp(ChoixColonne(&personne[indice_personne[i]], nb_colonne), str_filtre) == 0)
		{
			AffichageComplet(personne[indice_personne[i]], indice_personne[i]);
			i++;
		}
		break;
	
	case 2: // Filtre sous-chaine
		while (i < cpt_ligne)
		{
			char str_lower[taille];
			strcpy(str_lower, ChoixColonne(&personne[indice_personne[i]], nb_colonne));
			for (int j = 0; j < strlen(str_lower); j++)
			{
				/***************To lower car strstr est sensible à la casse***************/
				if (str_lower[j] >= 'A' && str_lower[j] <= 'Z')
				{	
					str_lower[j] = str_lower[j] + 32;
				}
				else
				{
					str_lower[j] = str_lower[j];
				}
			}
			if (strstr(str_lower, str_filtre) != NULL)
			{
				AffichageComplet(personne[indice_personne[i]], indice_personne[i]);
			}
			i++;
		}
		break;

	case 3: // Filtre de début de chaine (séquentielle triée)
		while (i < cpt_ligne && strncasecmp(ChoixColonne(&personne[indice_personne[i]], nb_colonne), str_filtre, strlen(str_filtre) - 1) < 0)
		{
			i++;
		}
		while (i < cpt_ligne && strncasecmp(ChoixColonne(&personne[indice_personne[i]], nb_colonne), str_filtre, strlen(str_filtre) - 1) == 0)
		{
			AffichageComplet(personne[indice_personne[i]], indice_personne[i]);
			i++;
		}
		break;

	case 4: // Filtre de fin de chaine
		while (i < cpt_ligne)
		{
			int diff;
			char elem[taille], elem_etu[taille] = "";
			strcpy(elem, ChoixColonne(&personne[indice_personne[i]], nb_colonne));
			diff = strlen(elem) - strlen(str_filtre);
			if (diff >= 0)
			{
				j = 0;
				for (int i = diff; i < strlen(elem); i++)
				{
					elem_etu[j] = elem[i];
					j++;
				}
				if (strcasecmp(elem_etu, str_filtre) == 0)
				{
					AffichageComplet(personne[indice_personne[i]], indice_personne[i]);
				}
			}
			i++;
		}
		break;
	
	default:
		printf("Erreur switch");
	}
}