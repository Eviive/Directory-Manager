#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define nom_fichier "Annuaire/annuaire5000.csv"

typedef struct informations
{
	char prenom[30], nom[30], ville[50], code_postal[10], telephone[20], email[50], metier[30];
} infos;

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

void AffichageRecherche(infos *personne, int indice)
{
	system("cls");
	printf("Personne %d", indice);
	printf("\nPrenom : ");
	if (strlen((*personne).prenom) != 0)
	{
		printf("%s\n", (*personne).prenom);
	}
	else
	{
		printf("N/A\n");
	}
	printf("Nom : ");
	if (strlen((*personne).nom) != 0)
	{
		printf("%s\n", (*personne).nom);
	}
	else
	{
		printf("N/A\n");
	}
	printf("Ville : ");
	if (strlen((*personne).ville) != 0)
	{
		printf("%s\n", (*personne).ville);
	}
	else
	{
		printf("N/A\n");
	}
	printf("Code postal : ");
	if (strlen((*personne).code_postal) != 0)
	{
		printf("%s\n", (*personne).code_postal);
	}
	else
	{
		printf("N/A\n");
	}
	printf("Telephone : ");
	if (strlen((*personne).telephone) != 0)
	{
		printf("%s\n", (*personne).telephone);
	}
	else
	{
		printf("N/A\n");
	}
	printf("Email : ");
	if (strlen((*personne).email) != 0)
	{
		printf("%s\n", (*personne).email);
	}
	else
	{
		printf("N/A\n");
	}
	printf("Metier : ");
	if (strlen((*personne).metier) != 0)
	{
		printf("%s\n\n", (*personne).metier);
	}
	else
	{
		printf("N/A\n\n");
	}
	system("pause > nul | echo Appuyez sur une touche pour continuer...");
	system("cls");
}

void Sauvegarde(infos  (*personne)[], int cpt_ligne)
{
	FILE * save_file = fopen("sauvegarde.csv", "w");
	if (save_file == NULL)
	{
		printf("Echec creation du fichier de sauvegarde\n");
		exit(EXIT_FAILURE);
	}
	for (int i = 0; i <= cpt_ligne; i++)
	{
		fprintf(save_file, "%s,", (*personne)[i].prenom);
		fprintf(save_file, "%s,", (*personne)[i].nom);
		fprintf(save_file, "%s,", (*personne)[i].ville);
		fprintf(save_file, "%s,", (*personne)[i].code_postal);
		fprintf(save_file, "%s,", (*personne)[i].telephone);
		fprintf(save_file, "%s,", (*personne)[i].email);
		fprintf(save_file, "%s\n", (*personne)[i].metier);
	}
	fclose(save_file);
}

int main()
{
	char ligne[300];
	infos personne[6000];
	int cpt_ligne = 0, cpt_char = 0, cpt_virgule = 0, cpt_var = 0;
	int choix_menu;
	int nb_recherche;
	/****************Lecture du fichier****************/
	FILE * fichier = fopen(nom_fichier, "r");
	if (fichier == NULL)
	{
		printf("Echec ouverture fichier\n");
		exit(EXIT_FAILURE);
	}
	/****************Assignation de toutes les cellules à des variables****************/
	while (fgets(ligne, sizeof(ligne), fichier) != NULL)
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
	fclose(fichier);
	/****************Menu****************/
	do
	{
		system("cls");  // en commentaire pour pouvoir voir les erreurs
		printf("Bienvenue dans le menu du gestionnaire d'annuaire\n");
		printf("	-Saisir 1 pour effectuer une recherche par indice\n");
		printf("	-Saisir 2 pour effectuer une sauvegarde dans un nouveau fichier\n");
		printf("	-Saisir 3 pour quitter\n\n");
		scanf("%d", &choix_menu);
		fflush(stdin);
		if (choix_menu < 1 || choix_menu > 3)
		{
			printf("\nErreur de saisie\n\n");
			system("pause > nul | echo Appuyez sur une touche pour continuer...");
		}
		else
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
					if (nb_recherche < 0 || nb_recherche > cpt_ligne)
					{
						printf("\nErreur de saisie\n\n");
						system("pause > nul | echo Appuyez sur une touche pour continuer...");
					}
					else if (nb_recherche != 0)
					{
						AffichageRecherche(&personne[nb_recherche-1], nb_recherche);
					}
				}
				while (nb_recherche != 0);
				break;
			
			/****************Sauvegarde dans un nouveau fichier****************/
			case 2:
				system("cls");
				printf("Creation du fichier de sauvegarde\n\n");
				infos (*pt_info)[] = &personne;
				Sauvegarde(pt_info, cpt_ligne - 1);
				system("pause > nul | echo Appuyez sur une touche pour continuer...");
				system("cls");
				break;
			}
		}
	}
	while (choix_menu != 3);
	return 0;
}