/**
 * \file chevalier.h
 * \brief En-tête pour le fichier chevalier.c
 * \author Delinac Inès
 * \date 15/12/2024 au 10/01/2025
 */

#ifndef CHEVALIER_H
#define CHEVALIER_H

    #include <stdio.h>
    #include <stdlib.h>
    #include <string.h>

    /**
     * \def PV_MIN
     * \brief Points de vie minimum pour un chevalier.
     *
     * Cette constante est utilisée pour initialiser les points de vie
     * des chevaliers à leur création.
     */
    #define PV_MIN 20

    /*---------------------------------------------------------------------------------------------------------------------------------*/

    /**
     * \def DMG_MIN
     * \brief Points de dégâts minimum pour un chevalier.
     *
     * Les chevaliers commencent toujours avec ce nombre de dégâts de base.
     */
    #define DMG_MIN 1

    /*---------------------------------------------------------------------------------------------------------------------------------*/
    /**
     * \enum Bool
     * \brief Type boléen qui permet de savoir si une condition est vraie ou fausse.
     *
     */
    typedef enum{
        false,
        true
    }Bool;

    /*---------------------------------------------------------------------------------------------------------------------------------*/

    /**
     * \struct Maillon
     * \brief Représente un élément de la liste chainée des scores.
     *
     * La structure `Maillon` est utilisée pour stocker un score individuel
     * ainsi qu'un pointeur vers le prochain maillon de la liste.
     */
    typedef struct maillon
    {
        int score;
        struct maillon *next;
    }MaillonScore;

    /*---------------------------------------------------------------------------------------------------------------------------------*/

    /**
     * \struct Chevalier
     * \brief Représente un chevalier avec ses informations et ses scores.
     *
     * La structure `Chevalier` contient les informations de base pour un joueur,
     * notamment son pseudo, ses statistiques de parties jouées et une liste de scores.
     */
    typedef struct 
    {
        char pseudo[41];
        int pv;
        int dmg;
        int nbParties;
        MaillonScore *firstScore;
        MaillonScore *lastScore;
    }Chevalier;

    /*---------------------------------------------------------------------------------------------------------------------------------*/

    /**
     * \struct Chevalier
     * \brief Représente un chevalier avec ses informations et ses scores.
     *
     * La structure `Chevalier` contient les informations de base pour un joueur,
     * notamment son pseudo, ses statistiques de parties jouées et une liste de scores.
     */
    typedef struct {
        Chevalier *chevaliers; // Tableau dynamique de chevaliers
        int nbChevaliers;            // Nombre de chevaliers dans le tableau
    } TableauChevaliers;

    /*---------------------------------------------------------------------------------------------------------------------------------*/

    /**
     * \brief Crée un nouveau chevalier
     *
     * \param pseudo pseudo du chevalier
     * \return un chevalier avec : 
     *                      - un pseudo, 
     *                      - 20 points de vie, 
     *                      - 1 point de dégât,
     *                      - 0 partie jouée 
     *                      - et une liste de scores vide
     */
    Chevalier creerChevalier(char *pseudo);

    /*---------------------------------------------------------------------------------------------------------------------------------*/

    /**
     * \brief Crée un nouveau tableau de chevaliers
     *
     * Alloue dynamiquement un tableau de chevaliers et l'initialise avec
     * une taille de 0 et un pointeur de chevaliers NULL.
     *
     * \return Un pointeur vers le tableau de chevaliers crée
     */
    TableauChevaliers *creerTableauChevaliers();

    /*---------------------------------------------------------------------------------------------------------------------------------*/

    /**
     * \brief Ajoute un chevalier à la liste
     *
     * Ajoute le chevalier donné en argument à la liste des chevaliers
     * du tableau. Si c'est le premier ajout, on alloue un tableau de
     * chevaliers de taille 1. Sinon, on réalloue pour étendre la taille
     * du tableau.
     *
     * \param[in,out] tableau le tableau de chevaliers à modifier
     * \param[in] chevalier le chevalier à ajouter
     */
    void ajouterChevalier(TableauChevaliers *tableau, Chevalier chevalier);
    
    /*---------------------------------------------------------------------------------------------------------------------------------*/

    /**
     * \brief Supprime un chevalier du tableau
     *
     * Supprime le chevalier situé à l'index donné du tableau de chevaliers.
     * Réduit la taille du tableau après la suppression et décale les chevaliers
     * suivants pour combler l'espace laissé par le chevalier supprimé.
     *
     * \param[in,out] tableau Le tableau de chevaliers à modifier
     * \param[in] index L'index du chevalier à supprimer
     * \note Si l'index est invalide, le programme termine avec un message d'erreur.
     */
    void supprimerChevalier(TableauChevaliers *tableau, int index);

    /*---------------------------------------------------------------------------------------------------------------------------------*/

    /**
     * \brief Charge un tableau de chevaliers à partir d'un fichier
     *
     * Lit le fichier "scores.txt" et charge les chevaliers avec leurs scores
     * dans un tableau de chevaliers.
     *
     * \param[out] nbChevaliers Le nombre de chevaliers lus
     * \return Un pointeur vers le tableau de chevaliers chargé
     */
    TableauChevaliers *chargerTableauChevaliers(int *nbChevaliers);

    /*---------------------------------------------------------------------------------------------------------------------------------*/

    /**
     * \brief Sauvegarde un tableau de chevaliers dans un fichier
     * 
     * Écrit les informations du tableau de chevaliers, comprenant le pseudo
     * le nombre de parties de chaque chevalier avec leurs scores, dans le fichier "scores.txt".
     * 
     * \param[in] tableau Le tableau de chevaliers à sauvegarder
     * \note Si le fichier ne peut pas être ouvert, le programme termine avec un message d'erreur.
     */
    void sauvegarderTableauChevaliers(TableauChevaliers *tableau);

    /*---------------------------------------------------------------------------------------------------------------------------------*/

    /**
     * \brief Cherche si un chevalier existe dans le tableau
     *
     * Cherche si le chevalier passé en argument existe dans le tableau de chevaliers.
     * Si le chevalier existe, la fonction renvoie l'index du chevalier dans le tableau.
     * Sinon, la fonction renvoie -1.
     *
     * \param[in] tableau Le tableau de chevaliers à chercher
     * \param[in] chevalier Le chevalier à chercher
     * \return L'index du chevalier dans le tableau si il existe, -1 sinon
     */
    int rechercheChevalierExiste(TableauChevaliers *tableau, Chevalier *chevalier);

    /*---------------------------------------------------------------------------------------------------------------------------------*/

    /**
     * \brief Lit le fichier scores.txt et ajoute les scores associés au chevalier à sa liste de scores si il en a
     *
     * \param[in,out] chevalier le chevalier
     * \return 1 si le chevalier a été identifié, 0 sinon
     */
    Bool chevalierExiste(TableauChevaliers *tableau, Chevalier *chevalier);

    /*---------------------------------------------------------------------------------------------------------------------------------*/

    /**
     * \brief Ajoute un score à la liste des scores du chevalier
     *
     * \param   Chevalier    chevalier à modifier
     * \param   score        score à ajouter
     *
     * Ajoute un score à la liste des scores du chevalier en l'insérant
     * dans l'ordre décroissant. Si la liste est vide, on ajoute le score
     * directement.
     */
    void ajouterScore(Chevalier *Chevalier, int score);

    /*---------------------------------------------------------------------------------------------------------------------------------*/
    
    /**
     * \brief Recherche un chevalier dans un tableau de chevaliers trié
     *
     * Recherche un chevalier dans le tableau de chevaliers trié par ordre
     * alphabétique croissant de leurs pseudos. Renvoie l'indice du chevalier
     * si il est trouvé, indice de debut sinon.
     *
     * \param[in] tableau le tableau de chevaliers à chercher
     * \param[in] pseudo le pseudo du chevalier à chercher
     * \param[out] trouve 1 si le chevalier est trouvé, 0 sinon
     * \return l'indice du chevalier si il est trouvé, indice de debut sinon
     */
    int rechDichotomiqueJoueur(TableauChevaliers *tableau, char *pseudo, int *trouve); //A faire (il n'est pas encore dans le .c)

    /*---------------------------------------------------------------------------------------------------------------------------------*/

    /**
     * \brief Affiche les statistiques du chevalier
     * 
     * Affiche les statistiques du chevalier, à savoir : 
     * - Le nombre de scores
     * - Le meilleur score
     * - Le moins bon score
     * - Le score moyen 
     * 
     * Si le chevalier n'a pas de score, un message d'erreur est affiché
     * 
     * \param[in] chevalier Le chevalier à qui on affiche les statistiques
     */
    void afficherStatistiques(Chevalier *chevalier);
    
    /*---------------------------------------------------------------------------------------------------------------------------------*/

    /**
     * \brief Libère la mémoire allouée pour la liste des scores d'un chevalier
     * 
     * Parcourt la liste des scores du chevalier et libère la mémoire
     * allouée pour chaque maillon. Après cet appel, la liste des scores
     * du chevalier sera vide.
     *
     * \param[in] chevalier Le chevalier dont les scores doivent être libérés
     */
    void libererScores(Chevalier *chevalier);

    /*---------------------------------------------------------------------------------------------------------------------------------*/

    /**
     * \brief Libère la mémoire allouée pour un chevalier
     * 
     * Réinitialise les champs du chevalier et libère la mémoire
     * allouée pour la liste des scores.
     *
     * \param[in] chevalier Le chevalier à libérer
     */
    void libererChevalier(Chevalier *chevalier);

    /*---------------------------------------------------------------------------------------------------------------------------------*/

    /**
     * \brief Libère la mémoire allouée pour un tableau de chevaliers
     * 
     * Libère la mémoire allouée pour chaque chevalier du tableau et
     * réinitialise les champs du tableau.
     *
     * \param[in] tableau Le tableau de chevaliers à libérer
     */
    void libererTableauChevaliers(TableauChevaliers *tableau);

    /*---------------------------------------------------------------------------------------------------------------------------------*/

    /**
    * \brief Trie un tableau de chevaliers par ordre alphabétique
    * 
    * Tri un tableau de chevaliers en ordre alphabétique croissant
    * en utilisant l'algorithme du tri à bulles.
    *
    * \param[in] tableau Le tableau de chevaliers à trier
    */
    void triBulleTableauChevaliers(TableauChevaliers *tableau);

    void echangerChevaliers(Chevalier *a, Chevalier *b);

    /* Partition pour le tri rapide */
    int partition(Chevalier *chevaliers, int gauche, int droite);

    /* Quicksort */
    void triRapideChevaliers(Chevalier *chevaliers, int gauche, int droite);


    /*---------------------------------------------------------------------------------------------------------------------------------*/

    /**
     * \brief Affiche un tableau de chevaliers
     *
     * \param[in] tableau Le tableau de chevaliers à afficher
     */
    void afficherTableauChevaliers(TableauChevaliers tableau);

#endif