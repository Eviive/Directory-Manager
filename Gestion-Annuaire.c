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
#include "Fonction.h"

#define tableau 5200
#define taille 70

/***************Split la fonction filtre pour que ce soit plus précis***************/
int main()
{
	unsigned int cpt_ligne = 0, indice_personne[tableau];;
	infos personne[tableau];

	char menu, colonne, recherche, action;
	char str_filtre[taille];
	char str_rech_prenom[taille], str_rech_nom[taille], str_rech_third[taille];
	unsigned int return_recherche;
	/***************Lecture du csv, rempli le tableau de structure***************/
	Ouverture(personne, indice_personne, &cpt_ligne);
	/***************Menu***************/
	do
	{
		printf("Bienvenue dans le menu du gestionnaire d'annuaire\n");
		printf("\t-Saisir 1 pour ajouter un client\n");
		printf("\t-Saisir 2 pour effectuer une recherche\n");
		printf("\t-Saisir 3 pour afficher le contenu de l'annuaire\n");
		printf("\t-Saisir 4 pour rechercher des clients via un filtre\n");
		printf("\t-Saisir 5 pour afficher les clients avec des donnees manquantes\n");
		printf("\t-Saisir 6 pour sauvegarder l'annuaire\n");
		printf("\t-Saisir 7 pour quitter\n");
		scanf("%d", &menu);
		fflush(stdin);
		if (menu >= 1 && menu <= 6)
		{
			switch (menu)
			{
			/***************Ajout***************/
			case 1:
				Clear();
				Ajout(&personne[cpt_ligne], indice_personne, &cpt_ligne);
				printf("\n");
				Pause();
				Clear();
				break;

			/***************Recherche***************/
			case 2:
				Clear();
				printf("1: Prenom / Nom / Email, 2: Prenom / Nom / Telephone\n(0 pour quitter)\n\nSaisir le triplet a rechercher : ");
				scanf("%d", &recherche);
				fflush(stdin);
				printf("\n");
				if (recherche == 1 || recherche == 2)
				{
					printf("Saisir le prenom a rechercher : ");
					scanf("%s", &str_rech_prenom);
					fflush(stdin);
					printf("Saisir le nom a rechercher : ");
					scanf("%s", &str_rech_nom);
					fflush(stdin);
					if (recherche == 1)
					{
						colonne = 5;
						printf("Saisir l'email a rechercher : ");
						scanf("%s", &str_rech_third);
						fflush(stdin);
					}
					else
					{
						colonne = 4;
						printf("Saisir le telephone a rechercher : ");
						scanf("%s", &str_rech_third);
						fflush(stdin);
					}
					Clear();
					Tri(personne, indice_personne, 0, cpt_ligne);
					return_recherche = Recherche(personne, indice_personne, cpt_ligne, str_rech_prenom, str_rech_nom, str_rech_third, colonne);
					if (return_recherche != -1)
					{
						printf("\n0: Ne rien faire, 1: Modifier ce client, 2: Supprimer ce client\n\nQuelle action souhaitez-vous effectuer : ");
						scanf("%d", &action);
						fflush(stdin);
						if (action == 1)
						{
							Clear();
							AffichageComplet(personne[indice_personne[return_recherche]], indice_personne[return_recherche]);
							Modif(&personne[indice_personne[return_recherche]]);
						}
						else if (action == 2)
						{
							printf("\n");
							Suppression(personne, indice_personne, &cpt_ligne, return_recherche);
						}
						else if (action != 0)
						{
							printf("\nErreur de saisie\n\n");
						}
					}
					else
					{
						printf("Aucune correspondance n'a ete trouvee\n\n");
					}
				}
				else if (recherche != 0)
				{
					printf("Erreur de saisie\n\n");
				}
				Pause();
				Clear();
				break;

			/***************Afficher l'annuaire***************/
			case 3:
				Clear();
				printf("0: Ne pas trier, 1: Prenom, 2: Nom, 3: Ville, 4: Code postal, 5: Telephone, 6: Email, 7: Metier\n\nQuelle colonne souhaitez-vous trier avant d'afficher l'annuaire : ");
				scanf("%d", &colonne);
				fflush(stdin);
				printf("\n");
				if (colonne >= 0 && colonne <= 7)
				{
					if (colonne != 0)
					{
						Tri(personne, indice_personne, colonne - 1, cpt_ligne);
					}
					for (int i = 0; i < cpt_ligne; i++)
					{
						AffichageComplet(personne[indice_personne[i]], indice_personne[i]);
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
			case 4:
				Clear();
				printf("1: Prenom, 2: Nom, 3: Ville, 4: Code postal, 5: Telephone, 6: Email, 7: Metier\n(0 pour quitter)\n\nSaisir le numero de la colonne a filtrer : ");
				scanf("%d", &colonne);
				fflush(stdin);
				printf("\n");
				if (colonne >= 1 && colonne <= 7)
				{
					do
					{
						printf("Chaine exacte : chaine\nCommence par : chaine*\nFini par : *chaine\nSous-chaine : *chaine*\n\nSaisir la valeur qui servira de filtre : ");
						scanf("%s", &str_filtre);
						fflush(stdin);
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
						Filtre(personne, indice_personne, cpt_ligne, colonne - 1, str_filtre, 2);
						printf("\nLa recherche via le filtre *%s* a ete effectue\n\n", str_filtre);
					}
					else if (str_filtre[strlen(str_filtre) - 1] == '*')
					{
						Tri(personne, indice_personne, colonne - 1, cpt_ligne);
						Filtre(personne, indice_personne, cpt_ligne, colonne - 1, str_filtre, 3);
						printf("\nLe recherche via le filtre %s a ete effectue\n\n", str_filtre);
					}
					else if (str_filtre[0] == '*')
					{
						for (int i = 0; i < strlen(str_filtre); i++)
						{
							str_filtre[i] = str_filtre[i + 1];
						}
						Filtre(personne, indice_personne, cpt_ligne, colonne - 1, str_filtre, 4);
						printf("\nLe recherche via le filtre *%s a ete effectue\n\n", str_filtre);
					}
					else
					{
						Tri(personne, indice_personne, colonne - 1, cpt_ligne);
						Filtre(personne, indice_personne, cpt_ligne, colonne - 1, str_filtre, 1);
						printf("\nLe recherche via le filtre %s a ete effectue\n\n", str_filtre);
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
			case 5:
				Clear();
				DonneeManquante(personne, indice_personne, cpt_ligne - 1);
				Pause();
				Clear();
				break;

			/***************Sauvegarde***************/
			case 6:
				Clear();
				Sauvegarde(personne, indice_personne, cpt_ligne - 1);
				Pause();
				Clear();
				break;

			default:
				printf("Erreur switch");
			}
		}
		else if (menu < 1 || menu > 7)
		{
			printf("\nErreur de saisie\n\n");
			Pause();
			Clear();
		}
	}
	while (menu != 7);
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