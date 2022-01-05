// Spécification formelle : Précondition doit être très courte car une fonction fait quelque chose de très précis
// Interdire les ',' dans les input
// Enlever les pointeurs dans les fonctions où je n'ai pas besoin de modifier les valeurs (dans ChoixColonne par exemple)
// en gros partout où il y a "infos * personne"
// fflush avec la méthode du TP6 si jamais ça marche pas sur un certain OS
// nombre d'occurrences trouvées (permet d'afficher 0 occurrence trouvée si pas de résultat)

// La recherche et l'affichage des données sur un client à partir de son nom, son prénom et son numéro de téléphone ou son adresse mél (une occurrence car ces couples sont uniques => recherche dichotomique => trié ?)
// Nom Prénom Tel / Nom Prénom Mail
// OU
// Nom Prénom Tel / Mail

// strncasecmp pour les filtres, même chose que strcasecmp sauf que il y a une limite
// strstr => sous-chaines

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define chemin_annuaire "Annuaire/annuaire_test.csv"
#define chemin_annuaire_sauvegarde "Annuaire/annuaire_sauvegarde.csv"

#define tableau 5200
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
void Ouverture(infos personne[tableau], int indice_personne[tableau], int * cpt_ligne);
void AffichageComplet(infos personne, int indice);
void AffichageUnique(char * value);
void Ajout(infos * personne, int indice_personne[tableau], int * cpt_ligne);
void Modif(infos * personne, int indice);
void SaisiInfo(char * value, int size);
void EcritureFichier(FILE * annuaire, infos personne);
void DonneeManquante(infos personne[tableau], int indice_personne[tableau], int cpt_ligne);
char DonneeEmpty(infos personne);
void Sauvegarde(infos personne[tableau], int indice_personne[tableau], int cpt_ligne);
void Tri(infos personne[tableau], int indice_personne[tableau], int nb_colonne, int cpt_ligne);
void Filtre(infos personne[tableau], int indice_personne[tableau], int cpt_ligne, int nb_colonne, char str_filtre[taille], int nb_mode);

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

void Ouverture(infos personne[tableau], int indice_personne[tableau], int * cpt_ligne)
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

void Ajout(infos * personne, int indice_personne[tableau], int * cpt_ligne)
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

void Suppression(infos personne[tableau], int indice_personne[tableau], int * cpt_ligne, int nb_suppression)
{
	for (int i = 0; i <= 6; i++)
	{
		ChoixColonne(&personne[indice_personne[nb_suppression]], i)[0] = '\0';
	}
	for (int i = nb_suppression; i < *(cpt_ligne) - 1; i++)
	{
		personne[indice_personne[i]] = personne[indice_personne[i + 1]];
	}
	(*cpt_ligne)--;
}

void Modif(infos * personne, int indice)
{
	int nb_col;
	printf("\n1: Prenom, 2: Nom, 3: Ville Code, 4: postal, 5: Telephone, 6: Email, 7: Metier\n\nSaisissez le numero de la colonne a modifier (0 pour quitter) : ");
	scanf("%d", &nb_col);
	fflush(stdin);
	if (nb_col >= 1 && nb_col <= 7)
	{
		printf("\nPersonne : %d\n", indice);
		printf("Valeur actuelle : ");
		AffichageUnique(ChoixColonne(personne, nb_col-1));
		printf("\nSaisir la nouvelle valeur : ");
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

void EcritureFichier(FILE * fichier, infos personne)
{
	int i = 0;
	for (i; i <= 5; i++)
	{
		fprintf(fichier, "%s,", ChoixColonne(&personne, i));
	}
	fprintf(fichier, "%s\n", ChoixColonne(&personne, i));
}

void DonneeManquante(infos personne[tableau], int indice_personne[tableau], int cpt_ligne)
{
	int indice = 0, cpt_clientvide = 0;
	for (indice = 0; indice <= cpt_ligne; indice++)
	{
		if (DonneeEmpty(personne[indice_personne[indice]]) == 1)
		{
			cpt_clientvide++;
			AffichageComplet(personne[indice_personne[indice]], indice);
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

void Sauvegarde(infos personne[tableau], int indice_personne[tableau], int cpt_ligne)
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
		EcritureFichier(save_file, personne[indice_personne[i]]);
	}
	fclose(save_file);
	printf("Sauvegarde effectue (annuaire_sauvegarde.csv)\n\n");
}

void Tri(infos personne[tableau], int indice_personne[tableau], int nb_colonne, int cpt_ligne)
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

void Filtre(infos personne[tableau], int indice_personne[tableau], int cpt_ligne, int nb_colonne, char str_filtre[taille], int nb_mode)
{
	/***************Créer une fonction pour chaque groupe de recherche (case 1 + case 3 / case 2 / case 4)***************/
	int i = 0, j;
	char elem[taille], elem_etu[taille] = "";
	switch (nb_mode)
	{
	case 1: // Séquentielle triée
		while (i < cpt_ligne && strcasecmp(ChoixColonne(&personne[indice_personne[i]], nb_colonne), str_filtre) < 0)
		{
			i++;
		}
		while (i < cpt_ligne && strcasecmp(ChoixColonne(&personne[indice_personne[i]], nb_colonne), str_filtre) == 0)
		{
			AffichageComplet(personne[indice_personne[i]], i);
			i++;
		}
		break;
	
	case 2: // Filtre sous-chaine (strstr est sensible à la casse)
		while (i < cpt_ligne)
		{
			if (strstr(ChoixColonne(&personne[indice_personne[i]], nb_colonne), str_filtre) != NULL)
			{
				AffichageComplet(personne[indice_personne[i]], i);
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
			AffichageComplet(personne[indice_personne[i]], i);
			i++;
		}
		break;

	case 4: // Filtre de fin de chaine
		while (i < cpt_ligne)
		{
			strcpy(elem, ChoixColonne(&personne[indice_personne[i]], nb_colonne));
			int diff = strlen(elem) - strlen(str_filtre);
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
					AffichageComplet(personne[indice_personne[i]], i);
				}
			}
			i++;
		}
		break;
	}
}

int main()
{
	int cpt_ligne = 0;
	infos personne[tableau];
	int indice_personne[tableau];

	char nb_menu;
	int nb_colonne;
	char str_filtre[taille];
	int nb_recherche;
	char str_rech_prenom[taille], str_rech_nom[taille], str_rech_tel[taille_telephone], str_rech_email[taille];
	/***************Lecture du csv, rempli le tableau de structure***************/
	Ouverture(personne, indice_personne, &cpt_ligne);
	/***************Menu***************/
	do
	{


		// 4/ L’affichage de la liste de tous les clients (toutes les données : nom, prénom, adresse,
		// 		numéro de téléphone, adresse mél, profession), avec la possibilité de trier cette liste sur
		// 		le nom, le prénom, le code postal, la profession
		// 5/ Un filtre sur le nom, le prénom, la profession, le code postal permettant d’afficher la liste
		// 		des clients répondant au critère donné. Par exemple, on peut vouloir afficher la liste des
		// 		clients dont le prénom commence par la lettre “J” ou dont le nom est “Leroy” ou encore
		// 		dont la profession est “enseignant”


		printf("Bienvenue dans le menu du gestionnaire d'annuaire\n");
		printf("\t-Saisir 1 pour ajouter un client\n");
		// 2- Rechercher un client via nom/prénom/mail ou tel, l'afficher	=> Modifier ce client
		// 						   			   								=> Supprimer ce client
		// Trier par prénom, recherche séquentielle du prénom, tester à chaque fois si le nom / mail ou tel correspond aux valeurs recherché
		printf("\t-Saisir 2 pour effectuer une recherche\n");
		printf("\t-Saisir 3 pour afficher le contenu de l'annuaire\n");
		printf("\t-Saisir 4 pour rechercher des clients via un filtre\n");
		printf("\t-Saisir 5 pour afficher les clients avec des donnees manquantes\n");
		printf("\t-Saisir 6 pour sauvegarder l'annuaire\n");
		printf("\t-Saisir 7 pour quitter\n");
		scanf("%c", &nb_menu);
		fflush(stdin);
		if (nb_menu < '1' || nb_menu > '7')
		{
			printf("\nErreur de saisie\n\n");
			Pause();
			Clear();
		}
		else if (nb_menu >= '1' && nb_menu <= '6')
		{
			switch (nb_menu)
			{
			/***************Ajout***************/
			case '1':
				Clear();
				Ajout(&personne[cpt_ligne], indice_personne, &cpt_ligne);
				printf("\n");
				Pause();
				Clear();
				break;

			/***************Recherche***************/
			case '2':
				Clear();
				printf("1: Prenom / Nom / Email, 2: Prenom / Nom / Telephone\n(0 pour quitter)\n\nSaisir le triplet a rechercher : ");
				scanf("%d", &nb_recherche);
				fflush(stdin);
				printf("\n");
				if (nb_recherche == 1 || nb_recherche == 2)
				{
					printf("Saisir le prenom a rechercher : ");
					scanf("%s", &str_rech_prenom);
					fflush(stdin);
					printf("Saisir le nom a rechercher : ");
					scanf("%s", &str_rech_prenom);
					fflush(stdin);
					if (nb_recherche == 1)
					{
						printf("Saisir l'email a rechercher : ");
						scanf("%s", &str_rech_email);
						fflush(stdin);
					}
					else
					{
						printf("Saisir le telephone a rechercher : ");
						scanf("%s", &str_rech_tel);
						fflush(stdin);
					}
					printf("\n");
					Tri(personne, indice_personne, 0, cpt_ligne);
					// Recherche(personne, indice_personne, cpt_ligne, 0, str_recherche, 1);
					printf("\nLa recherche a ete effectue\n\n");
				}
				else if (nb_colonne != 0)
				{
					printf("Erreur de saisie\n\n");
				}
				Pause();
				Clear();
				break;

			/***************Afficher l'annuaire***************/
			case '3':
				Clear();
				printf("0: Ne pas trier, 1: Prenom, 2: Nom, 3: Ville, 4: Code postal, 5: Telephone, 6: Email, 7: Metier\n\nQuelle colonne souhaitez-vous trier avant d'afficher l'annuaire : ");
				scanf("%d", &nb_colonne);
				fflush(stdin);
				printf("\n");
				if (nb_colonne >= 0 && nb_colonne <= 7)
				{
					if (nb_colonne != 0)
					{
						Tri(personne, indice_personne, nb_colonne - 1, cpt_ligne);
					}
					for (int i = 0; i < cpt_ligne; i++)
					{
						AffichageComplet(personne[indice_personne[i]], i);
					}
					printf("\nL'affichage de l'annuaire a ete effectue\n\n");
				}
				else
				{
					printf("Erreur de saisie\n\n");
				}
				Pause();
				Clear();
				break;

			/***************Filtre***************/
			case '4':
				Clear();
				printf("1: Prenom, 2: Nom, 3: Ville, 4: Code postal, 5: Telephone, 6: Email, 7: Metier\n(0 pour quitter)\n\nSaisir le numero de la colonne a filtrer : ");
				scanf("%d", &nb_colonne);
				fflush(stdin);
				printf("\n");
				if (nb_colonne >= 1 && nb_colonne <= 7)
				{
					do
					{
						printf("Chaine exacte : chaine\nCommence par : chaine*\nFini par : *chaine\nSous-chaine : *chaine*\n\nSaisir la valeur qui servira de filtre : ");
						scanf("%s", &str_filtre);
						fflush(stdin);
					}
					while (strlen(str_filtre) == 0);
					printf("\n");
					if (str_filtre[0] == '*' && str_filtre[strlen(str_filtre) - 1] == '*')
					{
						for (int i = 0; i < strlen(str_filtre); i++)
						{
							str_filtre[i] = str_filtre[i + 1];
						}
						str_filtre[strlen(str_filtre) - 1] = '\0';
						Filtre(personne, indice_personne, cpt_ligne, nb_colonne - 1, str_filtre, 2);
						printf("\nLa recherche via le filtre \"*%s*\" a ete effectue\n\n", str_filtre);
					}
					else if (str_filtre[strlen(str_filtre) - 1] == '*')
					{
						Tri(personne, indice_personne, nb_colonne - 1, cpt_ligne);
						Filtre(personne, indice_personne, cpt_ligne, nb_colonne - 1, str_filtre, 3);
						printf("\nLe recherche via le filtre \"%s\" a ete effectue\n\n", str_filtre);
					}
					else if (str_filtre[0] == '*')
					{
						for (int i = 0; i < strlen(str_filtre); i++)
						{
							str_filtre[i] = str_filtre[i + 1];
						}
						Filtre(personne, indice_personne, cpt_ligne, nb_colonne - 1, str_filtre, 4);
						printf("\nLe recherche via le filtre \"*%s\" a ete effectue\n\n", str_filtre);
					}
					else
					{
						Tri(personne, indice_personne, nb_colonne - 1, cpt_ligne);
						Filtre(personne, indice_personne, cpt_ligne, nb_colonne - 1, str_filtre, 1);
						printf("\nLe recherche via le filtre \"%s\" a ete effectue\n\n", str_filtre);
					}
				}
				else if (nb_colonne != 0)
				{
					printf("Erreur de saisie\n\n");
				}
				Pause();
				Clear();
				break;

			/***************Données manquantes***************/
			case '5':
				Clear();
				DonneeManquante(personne, indice_personne, cpt_ligne - 1);
				Pause();
				Clear();
				break;

			/***************Sauvegarde***************/
			case '6':
				Clear();
				Sauvegarde(personne, indice_personne, cpt_ligne - 1);
				Pause();
				Clear();
				break;

			default:
				printf("Erreur switch");
				break;
			}
		}
	}
	while (nb_menu != '7');
	return 0;
}

// lister les tris existant et les références de où on les a trouvés
// le choix peut dépendre de théorique => complexité théorique
// 							 pratique => implémentation facile
// il faut trouver le juste milieu

// présentation succinte, afficher la complexité sans explication des calculs (dire où on l'a trouvé)

// tri fusion : complexité quadratique, très efficace mais pas adapté pour les tableaux car cela nécessite de dupliquer le tableau
// plus adapter pour les liste

// lister les diff tris possible, les regrouper par classe suivant les avantages et inconvénients
// les éliminer peu à peu

// présentation courte => le principe (1 phrase), complexité théorique

// Recherche dichotomique : complexité logarithmique
// Tri par sélection : complexité taille²
// Recherche linéaire : O de n



// 2ème rapport : 1er rapport + le programme C
// comparaison théorique des choix
// exécuter les deux prog et comparer les benchmarks