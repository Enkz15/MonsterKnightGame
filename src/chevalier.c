/**
 * \file chevalier.c
 * \brief Fonctions principales pour les joueurs
 * \author Delinac Inès
 * \date 15/12/2024 au 10/01/2025
 */
#include "chevalier.h"

/**
 * \brief Crée un nouveau chevalier
 *
 * \param[in] pseudo pseudo du chevalier
 * \return un chevalier avec : 
 *                      - un pseudo, 
 *                      - 20 points de vie, 
 *                      - 1 point de dégât,
 *                      - 0 partie jouée 
 *                      - et une liste de scores vide
 */
Chevalier creerChevalier(char *pseudo){
    Chevalier chevalier;

    if (strlen(pseudo) >= sizeof(chevalier.pseudo)) { // chaîne trop grande -> raccourcir
        strncpy(chevalier.pseudo, pseudo, sizeof(chevalier.pseudo) - 1);
        chevalier.pseudo[sizeof(chevalier.pseudo) - 1] = '\0';
    } else {
        strcpy(chevalier.pseudo, pseudo);
    }

    chevalier.pv = PV_MIN;
    chevalier.dmg = DMG_MIN;
    chevalier.nbParties = 0;
    chevalier.firstScore = NULL;
    chevalier.lastScore = NULL;

    return chevalier;
}

/*---------------------------------------------------------------------------------------------------------------------------------*/

/**
 * \brief Crée un nouveau tableau de chevaliers
 *
 * Alloue dynamiquement un tableau de chevaliers et l'initialise avec
 * une taille de 0 et un pointeur de chevaliers NULL.
 *
 * \return Un pointeur vers le tableau de chevaliers crée
 */
TableauChevaliers *creerTableauChevaliers() {
    // Allouer dynamiquement la structure
    TableauChevaliers *tableau = (TableauChevaliers *)malloc(sizeof(TableauChevaliers));
    if (tableau == NULL) {
        perror("Erreur d'allocation mémoire");
        exit(EXIT_FAILURE);
    }

    // Initialiser les champs
    tableau->chevaliers = NULL; // Pas de chevaliers au départ
    tableau->nbChevaliers = 0;        // Taille initiale de 0

    return tableau;
}

/*--------------------------------------------------------------------------------------------------------------------------------*/
/* Fonction d'échange */
void echangerChevaliers(Chevalier *a, Chevalier *b) {
    Chevalier temp = *a;
    *a = *b;
    *b = temp;
}

/* Partition pour le tri rapide */
int partition(Chevalier *chevaliers, int gauche, int droite) {
    int pivotScore = (chevaliers[droite].lastScore) ? chevaliers[droite].lastScore->score : 0;
    int i = gauche - 1;

    for (int j = gauche; j < droite; j++) {
        int scoreJ = (chevaliers[j].lastScore) ? chevaliers[j].lastScore->score : 0;
        if (scoreJ >= pivotScore) { // Descendant
            i++;
            echangerChevaliers(&chevaliers[i], &chevaliers[j]);
        }
    }
    echangerChevaliers(&chevaliers[i + 1], &chevaliers[droite]);
    return i + 1;
}


/* Quicksort */
void triRapideChevaliers(Chevalier *chevaliers, int gauche, int droite) {
    if (gauche < droite) {
        int pivot = partition(chevaliers, gauche, droite);
        triRapideChevaliers(chevaliers, gauche, pivot - 1);
        triRapideChevaliers(chevaliers, pivot + 1, droite);
    }
}


/*---------------------------------------------------------------------------------------------------------------------------------*/

/**
 * \brief Trie un tableau de chevaliers par ordre alphabétique
 *
 * Utilise l'algorithme de tri à bulles pour trier les chevaliers
 * dans le tableau par ordre alphabétique croissant de leurs pseudos.
 *
 * \param[in,out] tableau Le tableau de chevaliers à trier
 */
void triBulleTableauChevaliers(TableauChevaliers *tableau){
    int i, j;
    for (i = 0; i < tableau->nbChevaliers - 1; i++) {
        for (j = 0; j < tableau->nbChevaliers-1 ; j++) {
            if (strcmp(tableau->chevaliers[j].pseudo, tableau->chevaliers[j + 1].pseudo) > 0) {
                Chevalier temp = tableau->chevaliers[j];
                tableau->chevaliers[j] = tableau->chevaliers[j + 1];
                tableau->chevaliers[j + 1] = temp;
            }
        }
    }
}

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
int rechDichotomiqueJoueur(TableauChevaliers *tableau, char *pseudo, int *trouve){
    int debut = 0, milieu, fin = tableau->nbChevaliers - 1;

    while (debut <= fin) {
        milieu = (debut + fin) / 2;
        if (strcmp(tableau->chevaliers[milieu].pseudo, pseudo) == 0) {
            *trouve = 1;
            return milieu;
        } else if (strcmp(tableau->chevaliers[milieu].pseudo, pseudo) < 0) {
            debut = milieu + 1;
        } else {
            fin = milieu - 1;
        }
    }
    *trouve = 0;
    return debut;
}

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
void ajouterChevalier(TableauChevaliers *tableau, Chevalier chevalier){
    if (tableau->chevaliers == NULL) {
        // Premier ajout
        tableau->chevaliers = (Chevalier *)malloc(sizeof(Chevalier));
        if (tableau->chevaliers == NULL) {
            perror("Erreur d'allocation mémoire");
            exit(EXIT_FAILURE);
        }
    } else {
        // Réallocation pour étendre la taille
        tableau->chevaliers = (Chevalier *)realloc(tableau->chevaliers, (tableau->nbChevaliers + 1) * sizeof(Chevalier));
        if (tableau->chevaliers == NULL) {
            perror("Erreur de réallocation mémoire");
            exit(EXIT_FAILURE);
        }
    }

    // Ajouter le chevalier
    tableau->chevaliers[tableau->nbChevaliers] = chevalier;
    tableau->nbChevaliers++;
}

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
void supprimerChevalier(TableauChevaliers *tableau, int index){
    if (index < 0 || index >= tableau->nbChevaliers) {
        perror("Index invalide\n");
        exit(EXIT_FAILURE);
    }
    for (int i = index; i < tableau->nbChevaliers - 1; i++) {
        tableau->chevaliers[i] = tableau->chevaliers[i + 1];
    }
    tableau->nbChevaliers--;
}

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
TableauChevaliers *chargerTableauChevaliers(int *nbChevaliers) {
    char pseudo[40];
    int nb_scores = 0;
    int score;
    FILE *fe;

    // Ouvrir le fichier
    if ((fe = fopen("src/fichier/scores.txt", "r")) == NULL) {
        perror("Impossible d'ouvrir le fichier");
        exit(EXIT_FAILURE);
    }

    // Lire le nombre de chevaliers
    if (fscanf(fe, "%d", nbChevaliers) != 1) {
        fprintf(stderr, "Erreur : format du fichier invalide (nombre de chevaliers).\n");
        fclose(fe);
        exit(EXIT_FAILURE);
    }

    // Créer le tableau dynamique de chevaliers
    TableauChevaliers *tableau = creerTableauChevaliers(*nbChevaliers);

    // Lecture des chevaliers
    for (int i = 0; i < *nbChevaliers; i++) {
        if (fscanf(fe, "%s %d", pseudo, &nb_scores) != 2) {
            fprintf(stderr, "Erreur : format du fichier invalide (chevalier %d).\n", i + 1);
            fclose(fe);
            libererTableauChevaliers(tableau);  // Libérer la mémoire du tableau en cas d'erreur
            exit(EXIT_FAILURE);
        }

        // Créer un nouveau chevalier
        Chevalier chevalier = creerChevalier(pseudo);

        // Lire les scores du chevalier
        for (int j = 0; j < nb_scores; j++) {
            if (fscanf(fe, "%d", &score) != 1) {
                fprintf(stderr, "Erreur : format du fichier invalide (score du chevalier %s).\n", pseudo);
                fclose(fe);
                libererTableauChevaliers(tableau);  // Libérer la mémoire du tableau en cas d'erreur
                exit(EXIT_FAILURE);
            }
            ajouterScore(&chevalier, score);
        }

        // Ajouter le chevalier au tableau
        ajouterChevalier(tableau, chevalier);
    }

    fclose(fe);
    return tableau;
}


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
void sauvegarderTableauChevaliers(TableauChevaliers *tableau) {
    FILE *fe;

    // Ouvrir le fichier en mode écriture
    if ((fe = fopen("src/fichier/scores.txt", "w")) == NULL) {
        perror("Impossible d'ouvrir le fichier");
        exit(EXIT_FAILURE);
    }

    // Écrire le nombre total de chevaliers
    fprintf(fe, "%d\n", tableau->nbChevaliers);

    // Parcourir chaque chevalier dans le tableau
    for (int i = 0; i < tableau->nbChevaliers; i++) {
        // Écrire le pseudo et le nombre de parties
        fprintf(fe, "%s %d\n", tableau->chevaliers[i].pseudo, tableau->chevaliers[i].nbParties);

        // Parcourir et écrire les scores
        MaillonScore *currentScore = tableau->chevaliers[i].firstScore;
        while (currentScore != NULL) {
            fprintf(fe, "%d ", currentScore->score);
            currentScore = currentScore->next;
        }
        fprintf(fe, "\n"); // Saut de ligne après les scores d'un chevalier
    }

    // Fermer le fichier
    fclose(fe);
}


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
int rechercheChevalierExiste(TableauChevaliers *tableau, Chevalier *chevalier){
    for (int i = 0; i < tableau->nbChevaliers; i++) {
        if (strcmp(tableau->chevaliers[i].pseudo, chevalier->pseudo) == 0) {
            return i;
        }
    }
    return -1;
}

/*---------------------------------------------------------------------------------------------------------------------------------*/

/**
 * \brief Lit le fichier scores.txt et ajoute les scores associés au chevalier à sa liste de scores si il en a
 *
 * \param[in,out] chevalier le chevalier
 * \return 1(true) si le chevalier a été identifié, 0(false) sinon
 */
Bool chevalierExiste(TableauChevaliers *tableau, Chevalier *chevalier) {
    int index= rechercheChevalierExiste(tableau, chevalier);

    if (index == -1) {
        return 0;
    }else{
        chevalier = &tableau->chevaliers[index];
    }
        
    return 1; 
}

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
void ajouterScore(Chevalier *chevalier, int score) {
    MaillonScore *newScore = (MaillonScore *)malloc(sizeof(MaillonScore));
    if (newScore == NULL) {
        perror("Erreur d'allocation mémoire\n");
        exit(EXIT_FAILURE);
    }

    newScore->score = score;
    newScore->next = NULL;

    // Si la liste est vide, on insère directement le premier maillon
    if (chevalier->firstScore == NULL) {
        chevalier->firstScore = newScore;
        chevalier->lastScore = newScore;  
    } else {// Insertion dans l'ordre décroissant (fonction de tri ?)
        MaillonScore *current = chevalier->firstScore;

        // Cas où le nouveau score est le meilleur
        if (score > chevalier->firstScore->score) {
            newScore->next = chevalier->firstScore;
            chevalier->firstScore = newScore;
        } else { // Cas où le nouveau score est plus petit que le meilleur
            while (current->next != NULL && current->next->score > score) {
                current = current->next;  // On parcourt la liste
            }
            
            newScore->next = current->next;
            current->next = newScore;

            // Si le maillon est inséré à la fin, mettez à jour lastScore
            if (newScore->next == NULL) {
                chevalier->lastScore = newScore;
            }
        }
    }

    chevalier->nbParties++;
}

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
void afficherStatistiques(Chevalier *chevalier){
    if (chevalier->firstScore == NULL) {
        printf("Le chevalier %s n'a aucun score enregistré.\n", chevalier->pseudo);
        return;
    }
    float scoreMoyen;
    int nbScores = 0;
    int sommeScores = 0;

    MaillonScore *current = chevalier->firstScore;
    while (current != NULL) {
        sommeScores += current->score;
        nbScores++;
        current = current->next;
    }

    // Calcul du score moyen en virgule flottante
    scoreMoyen = (float)sommeScores / nbScores; // Calcul du score moyen en virgule flottante

    // Affichage des statistiques
    printf("Statistiques pour %s :\n", chevalier->pseudo);
    printf("- Nombre de scores : %d\n", nbScores);
    printf("- Meilleur score : %d\n", chevalier->firstScore->score);
    printf("- Moins bon score : %d\n", chevalier->lastScore->score);
    printf("- Score moyen : %.2f\n", scoreMoyen);
}

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
void libererScores(Chevalier *chevalier) {
    MaillonScore *current = chevalier->firstScore;
    while (current != NULL) {
        MaillonScore *tmp = current;
        current = current->next;
        free(tmp);
    }
    chevalier->firstScore = NULL;
    chevalier->lastScore = NULL;
}

/*---------------------------------------------------------------------------------------------------------------------------------*/

/**
 * \brief Libère la mémoire allouée pour un chevalier
 * 
 * Réinitialise les champs du chevalier et libère la mémoire
 * allouée pour la liste des scores.
 *
 * \param[in] chevalier Le chevalier à libérer
 */
void libererChevalier(Chevalier *chevalier){
    if (chevalier == NULL) return;

    // Libérer la liste des scores en utilisant la fonction libererScores
    libererScores(chevalier);

    // Réinitialiser les champs du chevalier
    chevalier->pseudo[0] = '\0';
    chevalier->pv = 0;
    chevalier->dmg = 0;
    chevalier->nbParties = 0;
    chevalier->firstScore = NULL;
    chevalier->lastScore = NULL;
}

/*---------------------------------------------------------------------------------------------------------------------------------*/

/**
 * \brief Libère la mémoire allouée pour un tableau de chevaliers
 * 
 * Libère la mémoire allouée pour chaque chevalier du tableau et
 * réinitialise les champs du tableau.
 *
 * \param[in] tableau Le tableau de chevaliers à libérer
 */
void libererTableauChevaliers(TableauChevaliers *tableau){
    for (int i = 0; i < tableau->nbChevaliers; i++) {
        libererScores(&(tableau->chevaliers[i])); // Libérer les scores si nécessaire
    }
    free(tableau->chevaliers);
    tableau->chevaliers = NULL;
    tableau->nbChevaliers = 0;
}

/*---------------------------------------------------------------------------------------------------------------------------------*/

/**
* \brief Affiche un tableau de chevaliers
*
* \param[in] tableau Le tableau de chevaliers à afficher
*/
void afficherTableauChevaliers(TableauChevaliers tableau){
    if (tableau.nbChevaliers == 0) {
        printf("Aucun chevalier enregistré.\n");
        return;
    }

    printf("Tableau de chevaliers :\n");
    
    for (int i = 0; i < tableau.nbChevaliers; i++) {
        Chevalier *chevalier = &(tableau.chevaliers[i]);

        printf("Chevalier %d :\n", i + 1);
        printf("Pseudo : %s\n", chevalier->pseudo);
        printf("PV : %d\n", chevalier->pv);
        printf("DMG : %d\n", chevalier->dmg);
        printf("Parties jouées : %d\n", chevalier->nbParties);

        if (chevalier->firstScore == NULL) {
            printf("- Scores : Aucun score enregistré\n");
        } else {
            printf("- Scores :\n");
        }
        
        MaillonScore *current = chevalier->firstScore;
            while (current != NULL) {
                printf("  - %d\n", current->score);
                current = current->next;
            }

    }
    
    printf("\n");
}