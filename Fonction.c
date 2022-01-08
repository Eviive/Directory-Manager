#include "Fonction.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

/**
:postcondition : détermine la commande a effectuer pour clear en fonction de l'OS
*/
void Clear()
{
	#ifdef _WIN32
		system("cls");
	#elif defined __unix__ || __APPLE__
		system("clear");
	#endif
}

/**
:postcondition : détermine la commande a effectuer pour effectuer une pause en fonction de l'OS
*/
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

/**
:entrée personne : pointeur d'une structure de type infos
:entrée value : int
:pré-condition : value est entre 0 et 6
:postcondition : renvoie le pointeur d'une des catégorie de la personne
*/
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

/**
:entrée value : int
:pré-condition : value est entre 0 et 6
:postcondition : renvoie la chaine de caractères correspondant au nom de la catégorie
*/
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
		printf("Erreur switch");
	}
}

/**
:entrée personne : tableau de structures de type infos
:entrée indice_personne : tableau d'int
:entrée cpt_ligne : pointeur d'int
:pré-condition : cpt_ligne égal 0
:postcondition : lit l'annuaire, stock toutes les informations dans le tableau de structures infos, cpt_ligne est égal au nombre de personne
*/
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

/**
:entrée personne : structure de type infos
:entrée indice : int
:pré-condition : indice égal à l'indice de la personne dans l'annuaire
:postcondition : affiche toutes les informations sur la personne
*/
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

/**
:entrée value : pointeur de char
:postcondition : affiche la valeur d'entrée si elle est non-nul, sinon affiche N/A
*/
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

/**
:entrée personne : pointeur de structure de type infos
:entrée indice_personne : tableau d'int
:entrée cpt_ligne : pointeur d'int
:postcondition : ajoute une personne à la dernière ligne de l'annuaire
*/
void Ajout(infos * personne, int indice_personne[], int * cpt_ligne)
{
	Clear();
	for (int i = 0; i <= 6; i++)
	{
		printf("Saisir %s : ", NomColonne(i));
		scanf("%s", ChoixColonne(personne, i));
		fflush(stdin);
	}
	indice_personne[(*cpt_ligne)] = (*cpt_ligne);
	(*cpt_ligne)++;
}

/**
:entrée personne : tableau de structures de type infos
:entrée indice_personne : tableau d'int
:entrée cpt_ligne : pointeur d'int
:entrée nb_suppression : int
:pré-condition : nb_suppression égal à l'indice de la personne à supprimer
:postcondition : décale toutes les personnes après l'indice passé en paramètre, permet d'écraser la personne à supprimer
*/
void Suppression(infos personne[], int indice_personne[], int * cpt_ligne, int nb_suppression)
{
	for (int i = nb_suppression; i < *(cpt_ligne) - 1; i++)
	{
		personne[indice_personne[i]] = personne[indice_personne[i + 1]];
	}
	(*cpt_ligne)--;
}

/**
:entrée/sortie personne : pointeur de structure de type infos
:pré-condition : personne est la structure à modifier
:postcondition : modifie une des valeurs de la structure passé en entrée
*/
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
		scanf("%s", ChoixColonne(personne, nb_col-1));
		fflush(stdin);
		printf("\n");
	}
	else if (nb_col != 0)
	{
		printf("\nErreur de saisie\n\n");
	}
}

/**
:entrée personne : tableau de structures de type infos
:entrée indice_personne : tableau d'int
:entrée cpt_ligne : int
:postcondition : Affiche les données sur une personne si la fonction DonneeEmpty renvoie 1
*/
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

/**
:entrée personne : structure de type infos
:postcondition : renvoie 1 si une des chaines de caractères de la structure est vide, sinon renvoie 0
*/
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

/**
:entrée personne : tableau de structures de type infos
:entrée indice_personne : tableau d'int
:entrée cpt_ligne : int
:postcondition : écrit dans un fichier de sauvegarde le contenu de chaque structure sur une ligne
*/
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

/**
:entrée personne : tableau de structures de type infos
:entrée indice_personne : tableau d'int
:entrée cpt_ligne : int
:entrée nb_colonne : unsigned int
:pré-condition : nb_colonne entre 0 et 6
:postcondition : tri le tableau selon la colonne passé en paramètre
*/
void Tri(infos personne[], int indice_personne[], unsigned int nb_colonne, int cpt_ligne)
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

/**
:entrée personne : tableau de structures de type infos
:entrée indice_personne : tableau d'int
:entrée cpt_ligne : int
:entrée str_prenom, str_nom, str_third : tableau de caractères
:entrée nb_colonne : unsigned int
:pré-condition : nb_colonne entre 0 et 6
:postcondition : renvoie l'indice de la personne si elle est trouvée dans le tableau de structure, sinon renvoie -1
*/
int Recherche(infos personne[], int indice_personne[], int cpt_ligne, char str_prenom[], char str_nom[], char str_third[], unsigned int nb_colonne)
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

/**
:entrée personne : tableau de structures de type infos
:entrée indice_personne : tableau d'int
:entrée cpt_ligne : pointeur d'int
:entrée nb_colonne : unsigned int
:entrée str_filtre : tableau de caractères
:pré-condition : nb_colonne entre 0 et 6
:postcondition : effectue une recherche filtrée triée ("contient" et "début de chaine") et affiche les données des occurences trouvées
*/
void FiltreTrie(infos personne[], int indice_personne[], int cpt_ligne, unsigned int nb_colonne, char str_filtre[])
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

/**
:entrée personne : tableau de structures de type infos
:entrée indice_personne : tableau d'int
:entrée cpt_ligne : pointeur d'int
:entrée nb_colonne : unsigned int
:entrée str_filtre : tableau de caractères
:pré-condition : nb_colonne entre 0 et 6
:postcondition : effectue une recherche filtrée ("fin de chaine") et affiche les données des occurences trouvées
*/
void FinDeChaine(infos personne[], int indice_personne[], int cpt_ligne, unsigned int nb_colonne, char str_filtre[])
{
	clock_t start = clock();
	int i = 0, j;
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

/**
:entrée personne : tableau de structures de type infos
:entrée indice_personne : tableau d'int
:entrée cpt_ligne : pointeur d'int
:entrée nb_colonne : unsigned int
:entrée str_filtre : tableau de caractères
:pré-condition : nb_colonne entre 0 et 6
:postcondition : effectue une recherche filtrée ("sous-chaine") et affiche les données des occurences trouvées
*/
void SousChaine(infos personne[], int indice_personne[], int cpt_ligne, unsigned int nb_colonne, char str_filtre[])
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