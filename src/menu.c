/**
 * \file menu.c
 * \brief  Fontions de menus et globales
 * \author Delinac Inès
 * \date 20/12/2024 au 10/01/2025
 */

#include "menu.h"


/**
 * \brief Affiche le menu principal
 * 
 * Affiche le menu principal avec les choix suivants :
 * - 1. Jouer une partie prédéfinie
 * - 2. Jouer une partie personnalisee
 * - 3. Afficher la liste des joueurs triée par nom
 * - 4. Afficher la liste des joueurs triée par meilleur score
 * - 5. Afficher les statistiques d'un joueur
 * - 9. Quitter
 * 
 * \param[out] void
 */
void afficherMenu(void){
printf("------------- Menu -------------\n");
printf("    1. Jouer une partie prédéfinie \n");
printf("    2. Jouer une partie personnalisee\n");
printf("    3. Afficher la liste des joueurs triée par nom\n"); 
printf("    4. Afficher la liste des joueurs triée par meilleur score\n"); 
printf("    5. Afficher les statistiques d'un joueur\n");
printf("    9. Quitter \n");
printf("--------------------------------\n"); 
printf("Votre choix : ");
}

/*---------------------------------------------------------------------------------------------------------------------------------*/

/**
 * \brief Fonction principale qui execute le jeu
 *
 * Fonction qui contient la boucle principale du jeu. Elle affiche le menu,
 * lit le choix du joueur, et execute la fonction correspondante.
 * Si le joueur quitte, une sauvegarde du tableau de joueurs est effectuée.
 * 
 * \param[out] void
 */
void global(void){
    int choix=0, nbChevaliers=0, score=0, index;
    char pseudo[40];
    char nomFichier[40];
    Chevalier joueur;

    // Variable de bon déroulement du jeu
    int exist=0;

    // Création de la Pile de monstres
    PileMonstre v1Monstre=creerPile();
    // Création de la File de monstres
    FileMonstre v2Monstre=creerFileMonstre();

    // Chargement du Tableau de chevaliers
    TableauChevaliers *tableau = chargerTableauChevaliers(&nbChevaliers);
    

    do{
        afficherMenu();
        scanf("%d", &choix);
        switch(choix){
            case 1:
                printf ("Entrez le nom du fichier correspondant à la partie :  ");
                scanf("%s", nomFichier);
                lireMonstres(nomFichier, &v1Monstre, &v2Monstre);
                printf("Entrez votre pseudo de chevalier (40 caractère max) : ");
                scanf("%s", pseudo);
                joueur = creerChevalier(pseudo);
                score = jouerPartie(&joueur, v1Monstre, v2Monstre);
                exist = chevalierExiste(tableau, &joueur);
                if(exist == 0){
                    ajouterChevalier(tableau, joueur);
                    sauvegarderTableauChevaliers(tableau);
                }else{
                    triBulleTableauChevaliers(tableau);
                    index = rechDichotomiqueJoueur(tableau, joueur.pseudo, &exist);
                    ajouterScore(tableau[index].chevaliers, score);
                    sauvegarderTableauChevaliers(tableau);
                }
                break;

            case 2:
                printf("Entrez votre pseudo de chevalier (40 caractère max) : ");
                scanf("%s", pseudo);
                joueur = creerChevalier(pseudo);
                ajouterMonstresPersonnalise(&v1Monstre, &v2Monstre);
                score = jouerPartie(&joueur, v1Monstre, v2Monstre);
                exist = chevalierExiste(tableau, &joueur);
                if(exist == 0){
                    ajouterChevalier(tableau, joueur);
                    sauvegarderTableauChevaliers(tableau);
                }else{
                    triBulleTableauChevaliers(tableau);
                    index = rechDichotomiqueJoueur(tableau, joueur.pseudo, &exist);
                    ajouterScore(tableau[index].chevaliers, score);
                    sauvegarderTableauChevaliers(tableau);
                }
                break;

            case 3:
                triBulleTableauChevaliers(tableau);
                afficherTableauChevaliers(*tableau);
                break;

            case 4:
                triRapideChevaliers(tableau->chevaliers, 0, tableau->nbChevaliers - 1);
                afficherTableauChevaliers(*tableau); 
                break;

            case 5:
                printf("Entrez votre pseudo de chevalier (40 caractère max) : ");
                scanf("%s", pseudo);
                triBulleTableauChevaliers(tableau);
                index = rechDichotomiqueJoueur(tableau, pseudo, &exist);
                if(exist == 0){
                    printf("Le joueur n'existe pas\n");
                }else if (exist == 1) {
                    afficherStatistiques(tableau[index].chevaliers);
                }
                break;
            
            default:
                if(choix != 9){
                    printf("Choix incorrect, veuillez recommencer\n");
                }
                printf("Au revoir...\n");
                break;
        }
    }while(choix != 9);
}