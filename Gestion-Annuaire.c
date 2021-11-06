#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define nom_fichier "Annuaire/annuaire5000.csv"

typedef struct informations
{
	char prenom[20], nom[20], ville[40], code_postal[6], telephone[15], email[30], metier[20];
} infos;


int main()
{
	int cpt_ligne = 0, i = 0, cpt_virgule = 0, cpt_var = 0, nb_recherche;
	char ligne[200];
	infos personne_[6000];
	FILE * fichier = fopen(nom_fichier, "r");
	if(fichier == NULL)
	{
		printf("Echec ouverture fichier\n");
		exit(EXIT_FAILURE);
	}
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
					personne_[cpt_ligne].prenom[cpt_var] = ligne[i];
					break;

				case 1:
					personne_[cpt_ligne].nom[cpt_var] = ligne[i];
					break;
				
				case 2:
					personne_[cpt_ligne].ville[cpt_var] = ligne[i];
					break;
				
				case 3:
					personne_[cpt_ligne].code_postal[cpt_var] = ligne[i];
					break;
				
				case 4:
					personne_[cpt_ligne].telephone[cpt_var] = ligne[i];
					break;
				
				case 5:
					personne_[cpt_ligne].email[cpt_var] = ligne[i];
					break;
				
				case 6:
					personne_[cpt_ligne].metier[cpt_var] = ligne[i];
					break;
				}
				cpt_var++;
			}
			i++;
		}
		cpt_ligne++;
	}
	fclose(fichier);
	do
	{
		printf("Rentrer le numero de la personne a rechercher, il y a %d personnes rensignees (0 pour quitter) : ", cpt_ligne);
		scanf("%d", &nb_recherche);
		fflush(stdin);
		if (nb_recherche < 0 || nb_recherche > cpt_ligne)
		{
			printf("Erreur de saisie\n");
		}
		else if (nb_recherche != 0)
		{
			printf("\nPrenom : ");
			if (strlen(personne_[nb_recherche-1].prenom) != 0)
			{
				printf("%s\n", personne_[nb_recherche-1].prenom);
			}
			else
			{
				printf("N/A\n");
			}
			printf("Nom : ");
			if (strlen(personne_[nb_recherche-1].nom) != 0)
			{
				printf("%s\n", personne_[nb_recherche-1].nom);
			}
			else
			{
				printf("N/A\n");
			}
			printf("Ville : ");
			if (strlen(personne_[nb_recherche-1].ville) != 0)
			{
				printf("%s\n", personne_[nb_recherche-1].ville);
			}
			else
			{
				printf("N/A\n");
			}
			printf("Code postal : ");
			if (strlen(personne_[nb_recherche-1].code_postal) != 0)
			{
				printf("%s\n", personne_[nb_recherche-1].code_postal);
			}
			else
			{
				printf("N/A\n");
			}
			printf("Telephone : ");
			if (strlen(personne_[nb_recherche-1].telephone) != 0)
			{
				printf("%s\n", personne_[nb_recherche-1].telephone);
			}
			else
			{
				printf("N/A\n");
			}
			printf("Email : ");
			if (strlen(personne_[nb_recherche-1].email) != 0)
			{
				printf("%s\n", personne_[nb_recherche-1].email);
			}
			else
			{
				printf("N/A\n");
			}
			printf("Metier : ");
			if (strlen(personne_[nb_recherche-1].metier) != 0)
			{
				printf("%s\n\n", personne_[nb_recherche-1].metier);
			}
			else
			{
				printf("N/A\n\n");
			}
			system("pause > nul | echo Appuyez sur une touche pour continuer...");
			system("cls");
		}
	}
	while(nb_recherche != 0);
	return 0;
}