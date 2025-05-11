/**
 * \file monstres.h
 * \brief Header pour les monstres
 * \author Jouve Enzo
 * \date 02/01/2025
 */

#ifndef MONSTRES_H
#define MONSTRES_H

    #include <time.h>
    #define VIVANT 0
    #define MORT 1

    /**
    * \struct Monstre
    * \brief Représente un monstre avec ses caractéristiques.
    *
    * La structure `Monstre` contient :
    * - son nom,
    * - ses points de vie (PV),
    * - ses dégâts,
    * - le nombre d'armes qu'il possède,
    * - son niveau.
    */
    typedef struct Monstre {
        char *nom;
        int pv;
        int dmg;
        int nbArmes;
        int niveau;
    } Monstre;

    /*---------------------------------------------------------------------------------------------------------------------------------*/

    /**
    * \struct MaillonMonstre
    * \brief Représente un maillon de pile ou de file contenant un monstre.
    *
    * La structure `MaillonMonstre` est utilisée pour créer des listes chainées,
    * que ce soit pour une pile (vague 1) ou une file (vague 2). Chaque maillon
    * contient un pointeur vers un monstre et un pointeur vers le maillon suivant.
    */
    typedef struct MaillonMonstre {
        Monstre *monstre;
        struct MaillonMonstre *suiv;
    }MaillonMonstre, *PileMonstre;
    
    /*---------------------------------------------------------------------------------------------------------------------------------*/

    /**
    * \struct FileMonstre
    * \brief Représente une file de monstres.
    *
    * La structure `FileMonstre` contient des pointeurs vers le premier
    * (tête) et le dernier (queue) maillon de la file, permettant des opérations
    * d'enfilement et de défilement.
    */
    typedef struct File {
        MaillonMonstre *tete;
        MaillonMonstre *queue;
    } FileMonstre;

    /*---------------------------------------------------------------------------------------------------------------------------------*/

    /**
     * \brief Création d'une pile de monstres
     *
     * \return Une pile de monstres vide (NULL)
     */
    PileMonstre creerPile(void);
    /*---------------------------------------------------------------------------------------------------------------------------------*/


    /**
     * \brief Ajoute un maillon à la pile de monstres
     *
     * Alloue dynamiquement un nouveau maillon contenant un monstre et 
     * l'ajoute au sommet de la pile existante.
     *
     * \param[in] p La pile de monstres existante
     * \param[in] x Le maillon monstre à ajouter à la pile
     * \return Un pointeur vers le nouveau sommet de la pile
     *
     * \note Si l'allocation dynamique échoue, le programme termine avec un message d'erreur.
     */
    PileMonstre pushPile(PileMonstre p, Monstre *x);

    /*---------------------------------------------------------------------------------------------------------------------------------*/

    /**
     * \brief Supprime le maillon au sommet de la pile de monstres
     *
     * Supprime le maillon au sommet de la pile de monstres et renvoie le maillon
     * qui suit.
     *
     * \param[in] p La pile de monstres existante
     * \return Un pointeur vers le maillon qui suit le maillon supprimé
     *
     */
    PileMonstre popPile(PileMonstre p);

    /*---------------------------------------------------------------------------------------------------------------------------------*/

    /**
     * \brief Supprime tous les maillons de la pile de monstres
     *
     * La fonction clearPile supprime tous les maillons de la pile de monstres
     * en appelant la fonction pop_Pile sur chaque maillon.
     *
     * \param[in] p La pile de monstres à supprimer
     * \return Un pointeur NULL
     *
     */
    PileMonstre clearPile(PileMonstre p);

    /*---------------------------------------------------------------------------------------------------------------------------------*/

    /**
     * \brief Crée une file de monstres vide
     *
     * Crée une file de monstres avec un maillon tête et un maillon queue
     * initialisés à NULL.
     *
     * \return Une file de monstres vide
     */
    FileMonstre creerFileMonstre(void);

    /*---------------------------------------------------------------------------------------------------------------------------------*/

    /**
     * \brief Enfile un monstre dans une file de monstres
     *
     * Enfile le monstre \c x dans la file de monstres \c f.
     *
     * \param[in] f La file de monstres
     * \param[in] x Le monstre à enfiler
     * \return La file de monstres modifiée
     *
     */
    FileMonstre enfilerMonstre(FileMonstre f, Monstre *x);

    /*---------------------------------------------------------------------------------------------------------------------------------*/

    /**
     * \brief Défile un monstre dans une file de monstres
     *
     * Défile le premier monstre de la file de monstres \c f.
     *
     * \param[in] f La file de monstres
     * \return La file de monstres modifiée
     *
     */
    FileMonstre defilerMonstre(FileMonstre f);

    /*---------------------------------------------------------------------------------------------------------------------------------*/

    /**
     * \brief Vide une file de monstres
     *
     * La fonction clearFileMonstre supprime tous les monstres de la file de monstres
     * en appelant la fonction defilerMonstre sur chaque maillon.
     *
     * \param[in] f La file de monstres à vider
     * \return La file de monstres vidée (i.e. une file vide)
     *
     */
    FileMonstre clearFileMonstre(FileMonstre f);

    /*---------------------------------------------------------------------------------------------------------------------------------*/

    /**
     * \brief Crée un monstre
     *
     * Crée un monstre en fonction de son nom et de son niveau.
     *
     * Si le niveau est incorrect, la fonction renvoie \c NULL.
     * La fonction utilise des valeurs par défaut pour les attributs du monstre
     * en fonction de son niveau.
     * Pour le niveau 1, les attributs sont :
     * - 4 points de vie
     * - 1 point de dégât
     * - 4 armes
     * Pour le niveau 2, les attributs sont :
     * - 6 points de vie
     * - 1 point de dégât
     * - 3 armes
     * Pour le niveau 3, les attributs sont :
     * - 4 points de vie
     * - 2 points de dégât
     * - 5 armes
     * 
     * \param[in] nom Le nom du monstre
     * \param[in] niveau Le niveau du monstre (entre 1 et 3)
     * \return Un pointeur vers le monstre créé
     *
     */
    Monstre *creerMonstre(char *nom, int niveau);

    /*---------------------------------------------------------------------------------------------------------------------------------*/

    /**
     * \brief Ajoute des monstres personnalisés à une vague
     *
     * Cette fonction permet à l'utilisateur d'ajouter des monstres personnalisés
     * à l'une ou au deux vagues de monstres. L'utilisateur peut choisir parmi une
     * sélection de monstres prédéfinis et spécifier le niveau du monstre.
     *
     * L'utilisateur est invité à choisir la vague (1 ou 2) à laquelle ajouter
     * le monstre et à sélectionner un monstre parmi les options disponibles.
     * Le niveau du monstre doit être compris entre 1 et 3. Si les entrées de
     * l'utilisateur sont valides, le monstre est créé et ajouté à la vague
     * spécifiée.
     *
     * \param[in,out] vague1 La pile de monstres pour la première vague
     * \param[in,out] vague2 La file de monstres pour la deuxième vague
     */
    void ajouterMonstresPersonnalise(PileMonstre *vague1, FileMonstre *vague2);

    /*---------------------------------------------------------------------------------------------------------------------------------*/

    /**
     * \brief Lit les monstres depuis un fichier
     *
     * Lit les monstres depuis un fichier texte et les ajoute
     * à la vague correspondante.
     *
     * Le format du fichier est le suivant :
     * - Une ligne contenant le mot "Vague" suivi du numéro de vague
     *   (1 ou 2) pour indiquer le contexte.
     * - Une ligne contenant le nombre de monstres pour la vague.
     * - Pour chaque monstre, une ligne contenant le nom du monstre
     *   suivi de son niveau.
     *
     * \param[in] nomFichier Le nom du fichier à lire
     * \param[in,out] vague1 La pile de monstres pour la vague 1
     * \param[in,out] vague2 La file de monstres pour la vague 2
     *
     */
    void lireMonstres(char *nomFichier, PileMonstre *vague1, FileMonstre *vague2) ;

    /*---------------------------------------------------------------------------------------------------------------------------------*/

    /**
     * \brief Sélectionne aléatoirement une arme pour un monstre
     *
     * Cette fonction génère un choix d'arme aléatoire pour un monstre en fonction
     * de son niveau. Le niveau du monstre détermine l'intervalle des valeurs
     * aléatoires possibles :
     * - Pour le niveau 1, le choix est entre 0 et 3
     * - Pour le niveau 2, le choix est entre 0 et 2
     * - Pour le niveau 3, le choix est entre 0 et 4
     *
     * \param[in] monstre Un pointeur vers le monstre pour lequel choisir une arme
     * \return Un entier représentant le choix d'arme aléatoire
     *
     * \note Si le niveau du monstre est en dehors de l'intervalle 1-3, la fonction
     * affiche un message d'erreur et termine le programme.
     */
    int choixArmeMonstre(Monstre *monstre);

    /*---------------------------------------------------------------------------------------------------------------------------------*/

    /**
     * \brief Affiche les informations d'un monstre
     * 
     * Affiche le nom, le niveau, les points de vie, les points de dégâts et le
     * nombre d'armes d'un monstre.
     * 
     * \param[in] monstre Un pointeur vers le monstre à afficher
     * 
     */
    void afficherMonstre(Monstre *monstre);

    /*---------------------------------------------------------------------------------------------------------------------------------*/

    /**
     * \brief Affiche tous les monstres de la première vague
     * 
     * Parcourt la pile de monstres \c vague1 et affiche les informations de chaque monstre
     * en utilisant la fonction \c afficherMonstre.
     * 
     * \param[in] vague1 La pile de monstres de la première vague à afficher
     *
     */
    void afficherVague1(PileMonstre vague1);

    /*---------------------------------------------------------------------------------------------------------------------------------*/

    /**
     * \brief Affiche tous les monstres de la deuxième vague
     * 
     * Parcourt la file de monstres \c vague2 et affiche les informations de chaque monstre
     * en utilisant la fonction \c afficherMonstre.
     * 
     * \param[in] vague2 La file de monstres de la deuxième vague à afficher
     */
    void afficherVague2(FileMonstre vague2);

    /*---------------------------------------------------------------------------------------------------------------------------------*/

    /**
     * \brief Libère la mémoire allouée pour un monstre
     *
     * Si le monstre n'est pas NULL, libère la mémoire allouée pour le monstre
     * en appelant la fonction free. Si le monstre est NULL, affiche un message
     * d'erreur.
     *
     * \param[in] monstre Un pointeur vers le monstre à libérer
     *
     */
    void libererMonstre(Monstre *monstre);

    /*---------------------------------------------------------------------------------------------------------------------------------*/

    /**
     * \brief Libère la mémoire allouée pour la vague 1
     *
     * Libère la mémoire allouée pour la vague 1 en libérant chaque monstre
     * puis en libérant les maillons de la pile.
     *
     * \param[in] vague1 La pile de monstres de la vague 1 à libérer
     *
     */
    void libererVague1(PileMonstre vague1);

    /*---------------------------------------------------------------------------------------------------------------------------------*/

    /**
     * \brief Libère la mémoire allouée pour la vague 2
     *
     * Libère la mémoire allouée pour la vague 2 en libérant chaque monstre
     * puis en libérant les maillons de la file.
     *
     * \param[in] vague2 La file de monstres de la vague 2 à libérer
     */
    void libererVague2(FileMonstre vague2);

    /*---------------------------------------------------------------------------------------------------------------------------------*/

    /**
     * \brief Vérifie si un monstre est mort
     *
     * Cette fonction vérifie si les points de vie d'un monstre sont inférieurs
     * ou égaux à zéro pour déterminer si le monstre est mort.
     *
     * \param[in] monstre Un pointeur vers le monstre à vérifier
     * \return Un entier indiquant l'état du monstre : \c MORT si le monstre
     * est mort, \c VIVANT sinon.
     */
    int estMort(Monstre* monstre);

#endif // MONSTRES_H
