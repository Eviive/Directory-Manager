#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define chemin_annuaire "Annuaire/annuaire_test.csv"
#define chemin_annuaire_sauvegarde "Annuaire/annuaire_sauvegarde.csv"
#define chemin_annuaire_case_vide "Annuaire/annuaire_case_vide.csv"

typedef struct informations
{
	char prenom[30], nom[30], ville[50], code_postal[20], telephone[20], email[50], metier[30];
} infos;

void AttributionCSV(infos * personne, int cpt_virgule, int cpt_var, char caractere);
void AffichageRecherche(infos *personne, int indice);
void AffichageEmpty(char * value);
void Sauvegarde(infos  (*personne)[], int cpt_ligne);
void DonneeManquante(infos (*personne)[], int cpt_ligne);
int DonneeEmpty(infos * personne);
void EcritureFichier(FILE * fichier, infos * personne);
void Ajout(infos (*personne)[], int * cpt_ligne);

void AttributionCSV(infos * personne, int cpt_virgule, int cpt_var, char caractere)
{
	switch(cpt_virgule)
	{
	case 0:
		(*personne).prenom[cpt_var] = caractere;
		break;

	case 1:
		(*personne).nom[cpt_var] = caractere;
		break;
	
	case 2:
		(*personne).ville[cpt_var] = caractere;
		break;

	case 3:
		(*personne).code_postal[cpt_var] = caractere;
		break;
	
	case 4:
		(*personne).telephone[cpt_var] = caractere;
		break;
	
	case 5:
		(*personne).email[cpt_var] = caractere;
		break;
	
	case 6:
		(*personne).metier[cpt_var] = caractere;
		break;
	}
}

void AffichageRecherche(infos *personne, int indice) // créer un affichage réduit si jamais je doit afficher plusieurs clients
{
	system("cls");
	printf("Personne %d", indice);
	printf("\nPrenom : ");
	AffichageEmpty((*personne).prenom);
	printf("Nom : ");
	AffichageEmpty((*personne).nom);
	printf("Ville : ");
	AffichageEmpty((*personne).ville);
	printf("Code postal : ");
	AffichageEmpty((*personne).code_postal);
	printf("Telephone : ");
	AffichageEmpty((*personne).telephone);
	printf("Email : ");
	AffichageEmpty((*personne).email);
	printf("Metier : ");
	AffichageEmpty((*personne).metier);
	printf("\n");
	system("pause > nul | echo Appuyez sur une touche pour continuer...");
	system("cls");
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

void DonneeManquante(infos (*personne)[], int cpt_ligne) // printf les 3478 personnes ? fprintf dans un csv ?
{														  // doublon de certaines personnes ? différentes adresses pour le même ?
	FILE * case_vide_file = fopen(chemin_annuaire_case_vide, "w");
	if (case_vide_file == NULL)
	{
		printf("Echec creation du fichier des clients avec au moins une donnee manquante\n");
		exit(EXIT_FAILURE);
	}
	int indice = 0, cpt_clientvide = 0;
	for (indice = 0; indice <= cpt_ligne; indice++)
	{
		if (DonneeEmpty(&((*personne)[indice])) == 1)
		{
			cpt_clientvide++;
			EcritureFichier(case_vide_file, &((*personne)[indice]));
		}
	}
	fclose(case_vide_file);
	printf("\nIl y a %d client ayant au moins une case vide\n\n", cpt_clientvide);
	printf("Tout ces clients ont ete places dans un annuaire speciale (annuaire_case_vide.csv)\n\n");
}

int DonneeEmpty(infos * personne)
{
	if (strlen((*personne).prenom) == 0)
	{
		return 1;
	}
	if (strlen((*personne).nom) == 0)
	{
		return 1;
	}
	if (strlen((*personne).ville) == 0)
	{
		return 1;
	}
	if (strlen((*personne).code_postal) == 0)
	{
		return 1;
	}
	if (strlen((*personne).telephone) == 0)
	{
		return 1;
	}
	if (strlen((*personne).email) == 0)
	{
		return 1;
	}
	if (strlen((*personne).metier) == 0)
	{
		return 1;
	}
	return 0;
}

void EcritureFichier(FILE * fichier, infos * personne)
{
	fprintf(fichier, "%s,", (*personne).prenom);
	fprintf(fichier, "%s,", (*personne).nom);
	fprintf(fichier, "%s,", (*personne).ville);
	fprintf(fichier, "%s,", (*personne).code_postal);
	fprintf(fichier, "%s,", (*personne).telephone);
	fprintf(fichier, "%s,", (*personne).email);
	fprintf(fichier, "%s\n", (*personne).metier);
}

void Ajout(infos (*personne)[], int * cpt_ligne)
{
	printf("Saisir le prenom de la personne : ");
	fgets((*personne)[(*cpt_ligne)].prenom, sizeof((*personne)[(*cpt_ligne)].prenom), stdin);
	fflush(stdin);
	(*personne)[(*cpt_ligne)].prenom[strlen((*personne)[(*cpt_ligne)].prenom) - 1] = '\0';
	printf("Saisir le nom de la personne : ");
	fgets((*personne)[(*cpt_ligne)].nom, sizeof((*personne)[(*cpt_ligne)].nom), stdin);
	fflush(stdin);
	(*personne)[(*cpt_ligne)].nom[strlen((*personne)[(*cpt_ligne)].nom) - 1] = '\0';
	printf("Saisir la ville de la personne : ");
	fgets((*personne)[(*cpt_ligne)].ville, sizeof((*personne)[(*cpt_ligne)].ville), stdin);
	fflush(stdin);
	(*personne)[(*cpt_ligne)].ville[strlen((*personne)[(*cpt_ligne)].ville) - 1] = '\0';
	printf("Saisir le code postal de la personne : ");
	fgets((*personne)[(*cpt_ligne)].code_postal, sizeof((*personne)[(*cpt_ligne)].code_postal), stdin);
	fflush(stdin);
	(*personne)[(*cpt_ligne)].code_postal[strlen((*personne)[(*cpt_ligne)].code_postal) - 1] = '\0';
	printf("Saisir le numero de telephone de la personne : ");
	fgets((*personne)[(*cpt_ligne)].telephone, sizeof((*personne)[(*cpt_ligne)].telephone), stdin);
	fflush(stdin);
	(*personne)[(*cpt_ligne)].telephone[strlen((*personne)[(*cpt_ligne)].telephone) - 1] = '\0';
	printf("Saisir le email de la personne : ");
	fgets((*personne)[(*cpt_ligne)].email, sizeof((*personne)[(*cpt_ligne)].email), stdin);
	fflush(stdin);
	(*personne)[(*cpt_ligne)].email[strlen((*personne)[(*cpt_ligne)].email) - 1] = '\0';
	printf("Saisir le metier de la personne : ");
	fgets((*personne)[(*cpt_ligne)].metier, sizeof((*personne)[(*cpt_ligne)].metier), stdin);
	fflush(stdin);
	(*personne)[(*cpt_ligne)].metier[strlen((*personne)[(*cpt_ligne)].metier) - 1] = '\0';
	(*cpt_ligne)++;
}

int main()
{
	char ligne[300];
	infos personne[6000];
	infos (*pt_infos)[] = &personne;
	int cpt_ligne = 0, cpt_char = 0, cpt_virgule = 0, cpt_var = 0;
	int choix_menu;
	int nb_recherche;
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
				AttributionCSV(&personne[cpt_ligne], cpt_virgule, cpt_var, '\0');
				cpt_virgule++;
				cpt_var = 0;
			}
			else
			{
				AttributionCSV(&personne[cpt_ligne], cpt_virgule, cpt_var, ligne[cpt_char]);
				cpt_var++;
			}
			cpt_char++;
		}
		cpt_char = 0;
		cpt_virgule = 0;
		cpt_ligne++;
	}
	fclose(annuaire_file);
	/****************Menu****************/
	do
	{
		// system("cls");  // en commentaire pour pouvoir voir les erreurs
		printf("Bienvenue dans le menu du gestionnaire d'annuaire\n");
		printf("\t-Saisir 1 pour effectuer une recherche par indice\n");
		printf("\t-Saisir 2 pour effectuer une sauvegarde dans un nouveau fichier\n");
		printf("\t-Saisir 3 pour lister les personnes avec au moins une donnee manquante\n");
		printf("\t-Saisir 4 pour ajouter une personne a l'annuaire\n");
		printf("\t-Saisir 5 pour quitter\n\n");
		scanf("%d", &choix_menu);
		fflush(stdin);
		if (choix_menu >= 1 && choix_menu <= 5)
		{
			switch (choix_menu)
			{
			/****************Recherche par indice****************/
			case 1:
				do
				{
					system("cls");
					printf("Saisir le numero de la personne a rechercher, il y a %d personnes rensignees (0 pour quitter) : ", cpt_ligne);
					scanf("%d", &nb_recherche);
					fflush(stdin);
					if (nb_recherche > 0 && nb_recherche <= cpt_ligne)
					{
						AffichageRecherche(&personne[nb_recherche-1], nb_recherche);
					}
					else if (nb_recherche != 0)
					{
						printf("\nErreur de saisie\n\n");
						system("pause > nul | echo Appuyez sur une touche pour continuer...");
					}
				}
				while (nb_recherche != 0);
				break;
			
			/****************Sauvegarde dans un nouveau fichier****************/
			case 2:
				system("cls");
				Sauvegarde(pt_infos, cpt_ligne - 1);
				system("pause > nul | echo Appuyez sur une touche pour continuer...");
				system("cls");
				break;

			case 3:
				system("cls");
				DonneeManquante(pt_infos, cpt_ligne - 1);
				system("pause > nul | echo Appuyez sur une touche pour continuer...");
				system("cls");
				break;

			case 4:
				system("cls");
				Ajout(pt_infos, &cpt_ligne);
				system("pause > nul | echo Appuyez sur une touche pour continuer...");
				system("cls");
				break;
			}

		}
		else
		{
			printf("\nErreur de saisie\n\n");
			system("pause > nul | echo Appuyez sur une touche pour continuer...");
		}
	}
	while (choix_menu != 5);
	return 0;
}