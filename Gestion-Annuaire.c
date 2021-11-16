#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define nom_fichier "Annuaire/annuaire5000.csv"

typedef struct informations
{
	char prenom[20], nom[20], ville[40], code_postal[6], telephone[15], email[30], metier[20];
} infos;

void Affichage(infos *personne, int indice)
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

void Sauvegarde(infos  (*personne)[])
{
	FILE * save = fopen("sauvegarde.csv", "w");
	if (save == NULL)
	{
		printf("Echec creation du fichier de sauvegarde\n");
		exit(EXIT_FAILURE);
	}
}

int main()
{
	int cpt_ligne = 0, i = 0, cpt_virgule = 0, cpt_var = 0;
	int choix_menu;
	int nb_recherche;
	char ligne[200];
	infos personne[6000];
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
		i = 0;
		cpt_virgule = 0;
		while (ligne[i] != '\n')
		{
			if (ligne[i] == ',')
			{
				cpt_virgule++;
				cpt_var = 0;
			}
			else
			{
				switch(cpt_virgule)
				{
				case 0:
					personne[cpt_ligne].prenom[cpt_var] = ligne[i];
					break;

				case 1:
					personne[cpt_ligne].nom[cpt_var] = ligne[i];
					break;
				
				case 2:
					personne[cpt_ligne].ville[cpt_var] = ligne[i];
					break;
				
				case 3:
					personne[cpt_ligne].code_postal[cpt_var] = ligne[i];
					break;
				
				case 4:
					personne[cpt_ligne].telephone[cpt_var] = ligne[i];
					break;
				
				case 5:
					personne[cpt_ligne].email[cpt_var] = ligne[i];
					break;
				
				case 6:
					personne[cpt_ligne].metier[cpt_var] = ligne[i];
					break;
				}
				cpt_var++;
			}
			i++;
		}
		cpt_ligne++;
	}
	fclose(fichier);
	/****************Menu****************/
	do
	{
		// system("cls");  // en commentaire pour pouvoir voir les erreurs
		printf("Bienvenue dans le menu du gestionnaire d'annuaire\n");
		printf("	-Saisir 1 pour effectuer une recherche par indice\n");
		printf("	-Saisir 2 pour effectuer une fonctionnalite que je n'ai pas encore code\n");
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
						Affichage(&personne[nb_recherche-1], nb_recherche);
					}
				}
				while (nb_recherche != 0);
				break;
			
			/****************Fonctionnalité pas encore codé****************/
			case 2:
				system("cls");
				printf("Creation du fichier de sauvegarde\n\n");

				infos (*pt_info)[] = &personne;

				Sauvegarde(pt_info);
				system("pause > nul | echo Appuyez sur une touche pour continuer...");
				system("cls");
				break;
			}
		}
	}
	while (choix_menu != 3);
	return 0;
}