/**
 * \file test.
 * \brief Fontions de Tests
 * \author Delinac Inès
 * \date 08/12/2024 au 10/01/2025
 */

#include "test.h"

// ----------------------------------------------- Partie Chevalier -----------------------------------------------

void afficherScore(Chevalier chevalier){
    printf("\nNom : %s\n", chevalier.pseudo);
    for (int i = 0; i < chevalier.nbParties; i++) {
        printf("Score %d : %d\n", i + 1, chevalier.firstScore->score);
        chevalier.firstScore = chevalier.firstScore->next;
    }
}

void testCreerChevalierEtScore(){
    printf("Test de la fonction ajouterScore\n");
    // Test de la fonction ajouterScore
    Chevalier *chevalier = malloc(sizeof(Chevalier));
    *chevalier = creerChevalier("meow");

    printf("\nAjout des scores\n");
    printf("ajouter 123, 36, 98, 157\n");
    ajouterScore(chevalier, 123);
    ajouterScore(chevalier, 36);
    ajouterScore(chevalier, 98);
    ajouterScore(chevalier, 157);
    
    Chevalier chevalier1 = *chevalier; //crer une copie pour ne pas changer l'index

    printf("\nAffichage\n");
    afficherScore(chevalier1);
    

    printf("\nLibération des scores\n");
    libererScores(chevalier);
    free(chevalier);
}

void testTriBulle(void){
    int nbChevaliers = 0;

    TableauChevaliers *tableau ;
    tableau = chargerTableauChevaliers(&nbChevaliers);

    afficherTableauChevaliers(*tableau);

    printf("\nTest de la fonction triBulle\n");
    
    triBulleTableauChevaliers(tableau);

    printf("\nAffichage du tableau trié\n");
    
    libererTableauChevaliers(tableau);
}

void testRechercheDicho(void){
    int nbChevaliers = 0, index, trouve=0 ;

    TableauChevaliers *tableau ;
    tableau = chargerTableauChevaliers(&nbChevaliers);
    printf("\nTest de la fonction rechercheDicho\n");

    triBulleTableauChevaliers(tableau);
    index =rechDichotomiqueJoueur(tableau, "Amara", &trouve);
    printf("%d : index %d\n", trouve, index);
    afficherStatistiques(tableau[index].chevaliers);

    libererTableauChevaliers(tableau); 
}




void testChargementEtSauvegardeChevaliers(){
    printf("\nTest de la fonction chargeChevaliers et sauvegarderTableauChevaliers\n");
    // Test de la fonction chargeChevaliers 
    int nbChevaliers = 0;

    TableauChevaliers *tableau ;
    tableau = chargerTableauChevaliers(&nbChevaliers);

    sauvegarderTableauChevaliers(tableau);
    printf("\nAffichage du tableau chargé de %d Chevaliers\n", nbChevaliers);
    // Test de la fonction libererListeChevaliers
    for (int i = 0; i < tableau->nbChevaliers; i++) {
        afficherScore(tableau->chevaliers[i]);    
    }
    printf("Libération du tableau après sauvegarde\n");
    libererTableauChevaliers(tableau);


}

// ----------------------------------------------- Partie Monstres -----------------------------------------------

void testArmesAleatoire(){
    // Initialisation du générateur de nombres aléatoires
    srand(time(NULL)); // Utilise l'heure actuelle comme graine

    // Génération d'un nombre aléatoire entre 0 et 3
    int random_number = rand() % 4;

    // Affichage du nombre aléatoire
    printf("Nombre aléatoire entre 0 et 3 : %d\n", random_number);
    
    // Génération d'un nombre aléatoire entre 0 et 3
    random_number = rand() % 4;

    // Affichage du nombre aléatoire
    printf("Nombre aléatoire entre 0 et 3 : %d\n", random_number);
    // Génération d'un nombre aléatoire entre 0 et 3
    random_number = rand() % 4;

    // Affichage du nombre aléatoire
    printf("Nombre aléatoire entre 0 et 3 : %d\n", random_number);
    // Génération d'un nombre aléatoire entre 0 et 3
    random_number = rand() % 4;

    // Affichage du nombre aléatoire
    printf("Nombre aléatoire entre 0 et 3 : %d\n", random_number);
    // Génération d'un nombre aléatoire entre 0 et 3
    random_number = rand() % 4;

    // Affichage du nombre aléatoire
    printf("Nombre aléatoire entre 0 et 3 : %d\n", random_number);
}

void testChargement(){ //Test la fonction creerMonstres puis l'affiche
    printf("\nTest de la fonction creerMonstres\n");
    // Test de la fonction creerMonstres
    Monstre *monstre = creerMonstre("Chouin-Chouin", 1);
    afficherMonstre(monstre);
    monstre = creerMonstre("Lutin Cordial", 2);
    afficherMonstre(monstre);
    monstre = creerMonstre("Chimere", 3);
    afficherMonstre(monstre);
    free(monstre);
}

void testLireMonstres(){
    printf("\nTest de la fonction lireMonstres\n");
    // Test de la fonction lireMonstres
    PileMonstre vague1=creerPile();
    FileMonstre vague2=creerFileMonstre();
    lireMonstres("facile.txt", &vague1, &vague2);
    afficherVague1(vague1);
    afficherVague2(vague2);
    printf("tout bon !");
    libererVague1(vague1);
    libererVague2(vague2);
}

// ----------------------------------------------- Partie Jeu -----------------------------------------------