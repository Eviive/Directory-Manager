#include "Fonction.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

void Clear()
{
	#ifdef _WIN32
		system("cls");
	#elif defined __unix__ || __APPLE__
		system("clear");
	#endif
}

void Pause()
{
	#ifdef _WIN32
		system("pause > nul | echo Appuyez sur une touche pour continuer...");
	#elif defined __unix__
		system("read -n1 -r -p 'Appuyez sur une touche pour continuer...'");
	#elif defined __APPLE__
		system("echo Appuyez sur une touche pour continuer...")
		system("read touche")
	#endif
}

char * ChoixColonne(infos * personne, int value)
{
	switch (value)
	{
	case 0:
		return personne->prenom;
	
	case 1:
		return personne->nom;

	case 2:
		return personne->ville;

	case 3:
		return personne->code_postal;

	case 4:
		return personne->telephone;

	case 5:
		return personne->email;

	case 6:
		return personne->metier;

	default:
		printf("Erreur switch ChoixColonne");
		exit(EXIT_FAILURE);
	}
}

char * NomColonne(int value)
{
	switch (value)
	{
	case 0:
		return "le prenom";

	case 1:
		return "le nom";

	case 2:
		return "la ville";

	case 3:
		return "le code postal";

	case 4:
		return "le numero de telephone";

	case 5:
		return "l'email";

	case 6:
		return "le metier";

	default:
		printf("Erreur switch NomColonne");
		exit(EXIT_FAILURE);
	}
}

void Ouverture(infos personne[], unsigned int indice_personne[], unsigned int * cpt_ligne)
{
	char ligne[300], chemin_annuaire[100];
	int cpt_char = 0, cpt_virgule = 0, cpt_var = 0;

	printf("Saisir le chemin d'acces a l'annuaire : ");
	Saisi(chemin_annuaire, sizeof(chemin_annuaire));

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
			printf("Erreur switch AffichageComplet");
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

void Saisi(char * value, unsigned int size)
{
	fgets(value, size, stdin);
	fflush(stdin);
	for (int i = 0; i < strlen(value); i++)
	{
		if (value[i] == ',')
		{
			value[i] = ' ';
		}
		else if (value[i] == '\n')
		{
			value[i] = '\0';
		}
	}
}

void Ajout(infos * personne, unsigned int indice_personne[], unsigned int * cpt_ligne)
{
	unsigned int size;
	Clear();
	for (int i = 0; i <= 6; i++)
	{
		printf("Saisir %s : ", NomColonne(i));
		if (i == 3)
		{
			size = taille_code_postal;
		}
		else if (i == 4)
		{
			size = taille_telephone;
		}
		else
		{
			size = taille;
		}
		Saisi(ChoixColonne(personne, i), size);
	}
	indice_personne[(*cpt_ligne)] = (*cpt_ligne);
	(*cpt_ligne)++;
}

void Suppression(infos personne[], unsigned int indice_personne[], unsigned int * cpt_ligne, int nb_suppression)
{
	personne[indice_personne[nb_suppression]] = personne[*(cpt_ligne) - 1];
	(*cpt_ligne)--;
}

void Modif(infos * personne)
{
	int nb_col;
	unsigned int size = taille;
	printf("\n1: Prenom, 2: Nom, 3: Ville, 4: Code postal, 5: Telephone, 6: Email, 7: Metier\n(0 pour quitter)\n\nSaisissez le numero de la colonne a modifier : ");
	scanf("%d", &nb_col);
	fflush(stdin);
	if (nb_col >= 1 && nb_col <= 7)
	{
		printf("\nValeur actuelle : ");
		AffichageUnique(ChoixColonne(personne, nb_col-1));
		printf("Saisir la nouvelle valeur : ");
		if (nb_col - 1 == 3)
		{
			size = taille_code_postal;
		}
		else if (nb_col - 1 == 4)
		{
			size = taille_telephone;
		}
		Saisi(ChoixColonne(personne, nb_col-1), size);
		printf("\n");
	}
	else if (nb_col != 0)
	{
		printf("\nErreur de saisie\n\n");
	}
}

void DonneeManquante(infos personne[], unsigned int indice_personne[], unsigned int cpt_ligne)
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

void Sauvegarde(infos personne[], unsigned int indice_personne[], unsigned int cpt_ligne)
{
	printf("Creation du fichier de sauvegarde\n\n");
	FILE * save_file = fopen(chemin_annuaire_sauvegarde, "w");
	if (save_file == NULL)
	{
		printf("Echec creation du fichier de sauvegarde\n");
		exit(EXIT_FAILURE);
	}
	int j;
	for (int i = 0; i <= cpt_ligne; i++)
	{
		j = 0;
		while(j <= 5)
		{
			if (fprintf(save_file, "%s,", ChoixColonne(&personne[indice_personne[i]], j)) == 0)
			{
				printf("Echec de l'ecriture dans la sauvegarde\n\n");
				exit(EXIT_FAILURE);
			}
			j++;
		}
		if (fprintf(save_file, "%s\n", ChoixColonne(&personne[indice_personne[i]], j)) == 0)
		{
			printf("Echec de l'ecriture dans la derniere colonne de la sauvegarde\n\n");
			exit(EXIT_FAILURE);
		}
	}
	fclose(save_file);
	printf("Sauvegarde effectue (annuaire_sauvegarde.csv)\n\n");
}

void Tri(infos personne[], unsigned int indice_personne[], unsigned int nb_colonne, unsigned int cpt_ligne)
{
	clock_t start = clock();
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
	clock_t end = clock();
	printf("Duree tri : %.lf ms\n\n",((double)(end - start) / CLOCKS_PER_SEC) * 1000);
}

int Recherche(infos personne[], unsigned int indice_personne[], unsigned int cpt_ligne, char str_prenom[], char str_nom[], char str_third[], unsigned int nb_colonne)
{
	clock_t start = clock(), end;
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
			end = clock();
			printf("Duree Recherche : %.lf ms\n\n",((double)(end - start) / CLOCKS_PER_SEC) * 1000);
			return i;
		}
		i++;
	}
	end = clock();
	printf("Duree Recherche : %.lf ms\n\n",((double)(end - start) / CLOCKS_PER_SEC) * 1000);
	return -1;
}

void FiltreTrie(infos personne[], unsigned int indice_personne[], unsigned int cpt_ligne, unsigned int nb_colonne, char str_filtre[])
{
	clock_t start = clock();
	int i = 0;
	if (str_filtre[0] != '*' && str_filtre[strlen(str_filtre) - 1] != '*') // Séquentielle triée
	{
		while (i < cpt_ligne && strcasecmp(ChoixColonne(&personne[indice_personne[i]], nb_colonne), str_filtre) < 0)
		{
			i++;
		}
		while (i < cpt_ligne && strcasecmp(ChoixColonne(&personne[indice_personne[i]], nb_colonne), str_filtre) == 0)
		{
			AffichageComplet(personne[indice_personne[i]], indice_personne[i]);
			i++;
		}
	}
	else // Filtre de début de chaine (séquentielle triée)
	{
		while (i < cpt_ligne && strncasecmp(ChoixColonne(&personne[indice_personne[i]], nb_colonne), str_filtre, strlen(str_filtre) - 1) < 0)
		{
			i++;
		}
		while (i < cpt_ligne && strncasecmp(ChoixColonne(&personne[indice_personne[i]], nb_colonne), str_filtre, strlen(str_filtre) - 1) == 0)
		{
			AffichageComplet(personne[indice_personne[i]], indice_personne[i]);
			i++;
		}
	}
	clock_t end = clock();
	printf("\nDuree filtre : %.lf ms\n\n",((double)(end - start) / CLOCKS_PER_SEC) * 1000);
}

void FinDeChaine(infos personne[], unsigned int indice_personne[], unsigned int cpt_ligne, unsigned int nb_colonne, char str_filtre[])
{
	clock_t start = clock();
	int i = 0;
	while (i < cpt_ligne)
	{
		int diff;
		char elem[taille];
		strcpy(elem, ChoixColonne(&personne[indice_personne[i]], nb_colonne));
		diff = strlen(elem) - strlen(str_filtre);
		if (diff >= 0)
		{
			if (strcasecmp(&elem[diff], str_filtre) == 0)
			{
				AffichageComplet(personne[indice_personne[i]], indice_personne[i]);
			}
		}
		i++;
	}
	clock_t end = clock();
	printf("\nDuree filtre : %.lf ms\n\n",((double)(end - start) / CLOCKS_PER_SEC) * 1000);
}

void SousChaine(infos personne[], unsigned int indice_personne[], unsigned int cpt_ligne, unsigned int nb_colonne, char str_filtre[])
{
	clock_t start = clock();
	int i = 0;
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
	clock_t end = clock();
	printf("\nDuree filtre : %.lf ms\n\n",((double)(end - start) / CLOCKS_PER_SEC) * 1000);
}