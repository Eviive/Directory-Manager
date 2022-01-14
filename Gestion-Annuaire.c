#include "Fonction.h"
#include <stdio.h>
#include <string.h>

#define tableau 5200
#define taille 70

int main()
{
	unsigned int cpt_ligne = 0, indice_personne[tableau];
	infos personne[tableau];
	
	int colonne, current_tri = -1;
	char menu, recherche, rech_action;
	char str_filtre[taille];
	char str_rech_prenom[taille], str_rech_nom[taille], str_rech_third[taille];
	unsigned int return_recherche;
	/***************Lecture du csv, rempli le tableau de structure***************/
	Ouverture(personne, indice_personne, &cpt_ligne);
	/***************Menu***************/
	Clear();
	do
	{
		printf("Bienvenue dans le menu du gestionnaire d'annuaire\n");
		printf("\t1- ajouter un client\n");
		printf("\t2- effectuer une recherche\n");
		printf("\t3- afficher le contenu de l'annuaire\n");
		printf("\t4- rechercher des clients via un filtre\n");
		printf("\t5- afficher les clients avec des donnees manquantes\n");
		printf("\t6- sauvegarder l'annuaire\n");
		printf("\t7- quitter\n> ");
		scanf("%c", &menu);
		fflush(stdin);
		if (menu >= '1' && menu <= '6')
		{
			switch (menu)
			{
			/***************Ajout***************/
			case '1':
				Clear();
				Ajout(&personne[cpt_ligne], indice_personne, &cpt_ligne);
				current_tri = -1;
				printf("\n");
				Pause();
				Clear();
				break;

			/***************Recherche***************/
			case '2':
				Clear();
				printf("1: Prenom / Nom / Email, 2: Prenom / Nom / Telephone\n(0 pour quitter)\n\nSaisir le triplet a rechercher : ");
				scanf("%c", &recherche);
				fflush(stdin);
				printf("\n");
				if (recherche == '1' || recherche == '2')
				{
					printf("Saisir le prenom a rechercher : ");
					Saisi(str_rech_prenom, taille);
					printf("Saisir le nom a rechercher : ");
					Saisi(str_rech_nom, taille);
					if (recherche == '1')
					{
						colonne = 5;
						printf("Saisir l'email a rechercher : ");
						Saisi(str_rech_third, taille);
					}
					else
					{
						colonne = 4;
						printf("Saisir le telephone a rechercher : ");
						Saisi(str_rech_third, taille_telephone);
					}
					Clear();
					if (current_tri != 0)
					{
						Tri(personne, indice_personne, 0, cpt_ligne);
						current_tri = 0;
					}
					return_recherche = Recherche(personne, indice_personne, cpt_ligne, str_rech_prenom, str_rech_nom, str_rech_third, colonne);
					if (return_recherche != -1)
					{
						printf("\n0: Ne rien faire, 1: Modifier ce client, 2: Supprimer ce client\n\nQuelle action souhaitez-vous effectuer : ");
						scanf("%c", &rech_action);
						fflush(stdin);
						if (rech_action == '1')
						{
							Clear();
							AffichageComplet(personne[indice_personne[return_recherche]], indice_personne[return_recherche]);
							Modif(&personne[indice_personne[return_recherche]]);
						}
						else if (rech_action == '2')
						{
							printf("\n");
							Suppression(personne, indice_personne, &cpt_ligne, return_recherche);
							current_tri = -1;
						}
						else if (rech_action == '0')
						{
							printf("\n");
						}
						else
						{
							printf("\nErreur de saisie\n\n");
						}
						
					}
					else
					{
						printf("\nAucune correspondance n'a ete trouvee\n\n");
					}
				}
				else if (recherche != '0')
				{
					printf("Erreur de saisie\n\n");
				}
				Pause();
				Clear();
				break;

			/***************Afficher l'annuaire***************/
			case '3':
				Clear();
				for (int i = 0; i < 7; i++)
				{
					printf("%d: %s, ", i, NomColonne(i));
				}
				printf("7: %s\n\n", NomColonne(7));
				printf("Quelle colonne souhaitez-vous trier avant d'afficher l'annuaire : ");
				scanf("%d", &colonne);
				fflush(stdin);
				printf("\n");
				if (colonne >= 0 && colonne <= 7)
				{
					if (colonne != 0)
					{
						if (current_tri != colonne - 1)
						{
							Tri(personne, indice_personne, colonne - 1, cpt_ligne);
							current_tri = colonne - 1;
						}
						for (unsigned int i = 0; i < cpt_ligne; i++)
						{
							AffichageComplet(personne[indice_personne[i]], indice_personne[i]);
						}
					}
					else
					{
						for (unsigned int i = 0; i < cpt_ligne; i++)
						{
							AffichageComplet(personne[i], i);
						}
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
				for (int i = 1; i < 7; i++)
				{
					printf("%d: %s, ", i, NomColonne(i));
				}
				printf("7: %s\n", NomColonne(7));
				printf("(0 pour quitter)\n\nSaisir le numero de la colonne a filtrer : ");
				scanf("%d", &colonne);
				fflush(stdin);
				printf("\n");
				if (colonne >= 1 && colonne <= 7)
				{
					do
					{
						printf("Chaine exacte : chaine\nCommence par : chaine*\nFini par : *chaine\nSous-chaine : *chaine*\n\nSaisir la valeur qui servira de filtre : ");
						Saisi(str_filtre, taille);
					}
					while (strlen(str_filtre) == 0);
					Clear();
					if (str_filtre[0] == '*' && str_filtre[strlen(str_filtre) - 1] == '*')
					{
						for (int i = 0; i < strlen(str_filtre); i++)
						{
							/***************To lower car strstr est sensible à la casse***************/
							if (str_filtre[i + 1] >= 'A' && str_filtre[i + 1] <= 'Z')
							{	
								str_filtre[i] = str_filtre[i + 1] + 32;
							}
							else
							{
								str_filtre[i] = str_filtre[i + 1];
							}
						}
						str_filtre[strlen(str_filtre) - 1] = '\0';
						SousChaine(personne, indice_personne, cpt_ligne, colonne - 1, str_filtre);
						printf("La recherche via le filtre *%s* a ete effectue\n\n", str_filtre);
					}
					else if (str_filtre[strlen(str_filtre) - 1] == '*')
					{
						if (current_tri != colonne - 1)
						{
							Tri(personne, indice_personne, colonne - 1, cpt_ligne);
							current_tri = colonne - 1;
						}
						FiltreTrie(personne, indice_personne, cpt_ligne, colonne - 1, str_filtre);
						printf("Le recherche via le filtre %s a ete effectue\n\n", str_filtre);
					}
					else if (str_filtre[0] == '*')
					{
						for (int i = 0; i < strlen(str_filtre); i++)
						{
							str_filtre[i] = str_filtre[i + 1];
						}
						FinDeChaine(personne, indice_personne, cpt_ligne, colonne - 1, str_filtre);
						printf("Le recherche via le filtre *%s a ete effectue\n\n", str_filtre);
					}
					else
					{
						if (current_tri != colonne - 1)
						{
							Tri(personne, indice_personne, colonne - 1, cpt_ligne);
							current_tri = colonne - 1;
						}
						FiltreTrie(personne, indice_personne, cpt_ligne, colonne - 1, str_filtre);
						printf("Le recherche via le filtre %s a ete effectue\n\n", str_filtre);
					}
				}
				else if (colonne != 0)
				{
					printf("Erreur de saisie\n\n");
				}
				Pause();
				Clear();
				break;

			/***************Données manquantes***************/
			case '5':
				Clear();
				DonneeManquante(personne, cpt_ligne - 1);
				Pause();
				Clear();
				break;

			/***************Sauvegarde***************/
			case '6':
				Clear();
				Sauvegarde(personne, cpt_ligne - 1);
				Pause();
				Clear();
				break;

			default:
				printf("Erreur switch Menu");
			}
		}
		else if (menu < '1' || menu > '7')
		{
			printf("\nErreur de saisie\n\n");
			Pause();
			Clear();
		}
	}
	while (menu != '7');
	return 0;
}