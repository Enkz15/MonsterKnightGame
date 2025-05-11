/**
 * \file menu.h
 * \brief Entếte pour les fontions de menus et globales
 * \author Delinac Inès
 * \date 20/12/2024 au 10/01/2025
 */

#ifndef MENU_H
#define MENU_H

    #include "jeu.h"

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
    void afficherMenu(void);

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
    void global(void);

#endif