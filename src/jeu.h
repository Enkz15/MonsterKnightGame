/**
 * \file jeu.h
 * \brief En-tête pour le fichier jeu.c
 * \author Delinac Inès
 * \date 16/12/2024 au 10/01/2025
 */

#ifndef JEU_H
#define JEU_H

    #include "chevalier.h"
    #include "monstres.h"

    /**
     * \def SCORE_VICTOIRE_ATTAQUE
     * \brief point acquis si l'on gagne une attaque contre un monstre
     */
    #define SCORE_VICTOIRE_ATTAQUE 10

    /*---------------------------------------------------------------------------------------------------------------------------------*/

    /**
     * \def SCORE_VICTOIRE_V1
     * \brief point acquis si l'on tue un monstre de la vague 1
     *
     * Il sera par la suite multiplié par le niveau du monstre
     */
    #define SCORE_VICTOIRE_V1 50

    /*---------------------------------------------------------------------------------------------------------------------------------*/

    /**
     * \def SCORE_VICTOIRE_V2
     * \brief point acquis si l'on tue un monstre de la vague 2
     *
     * Il sera par la suite multiplié par le niveau du monstre
     */
    #define SCORE_VICTOIRE_V2 100

    /*---------------------------------------------------------------------------------------------------------------------------------*/

    // Couleur pour l'affichage
    #define VERT "\e[0;32m"
    #define ORANGE "\e[0;33m"
    #define ROUGE "\e[0;31m"
    #define BLEU "\e[0;34m"
    #define RESET "\e[0;m"

    /*---------------------------------------------------------------------------------------------------------------------------------*/

    /**
     * \enum combat
     * \brief Type de combat
     * 
     * Un type \c combat indiquant le résultat d'une manche : 
     * - \c victoire si le joueur a gagné, 
     * - \c defaite si le joueur a perdu, 
     * - \c egalite si les deux joueurs ont fait une égalité.
     */
    typedef enum
    {
        defaite = 0,
        egalite = 1,
        victoire = 2
    }Combat;

    /*---------------------------------------------------------------------------------------------------------------------------------*/

    /**
     * \brief Calcul les points gagnés suite à la mort d'un monstre de la vague 1
     * 
     * Cette fonction calcule les points gagnés suite à la mort d'un monstre
     * de la vague 1 en fonction du niveau du monstre.
     * 
     * \param[in] chevalier Le chevalier qui joue
     * \param[in] score Le score actuel du chevalier
     * \param[in] monstre La pile de monstres actuelle
     * \return Le score mis à jour en fonction des points gagnés
     */
    int calculPointsVague1(Chevalier *chevalier, int score, Monstre *monstre);

    /*---------------------------------------------------------------------------------------------------------------------------------*/

    /**
     * \brief Affiche l'introduction d'une manche
     * 
     * Affiche un message qui introduit la manche en cours, en indiquant le nom, les points de vie et les points de dégâts du monstre, ainsi que le pseudo, les points de vie et les points de dégâts du chevalier.
     * 
     * \param[in] chevalier Le chevalier qui joue
     * \param[in] monstre La pile de monstres actuelle
     */
    void afficheintro(Chevalier *chevalier, Monstre *monstre);

    /*---------------------------------------------------------------------------------------------------------------------------------*/

    /**
     * \brief Affiche le résultat d'une manche gagnée
     * 
     * Affiche un message qui indique que le chevalier a gagné la manche
     * contre le monstre, en indiquant les points de vie du chevalier
     * et du monstre, ainsi que le score gagné.
     * 
     * \param[in] chevalier Le chevalier qui joue
     * \param[in] score Le score actuel du chevalier
     * \param[in] monstre La pile de monstres actuelle
     */
    void afficheoutrovictoire(Chevalier *chevalier, int score, Monstre *monstre);

    /*---------------------------------------------------------------------------------------------------------------------------------*/

    /**
     * \brief Affiche le résultat d'une manche perdue
     * 
     * Affiche un message qui indique que le chevalier a perdu la manche
     * contre le monstre, en indiquant les points de vie du chevalier
     * et du monstre, ainsi que le score gagné.
     * 
     * \param[in] chevalier Le chevalier qui joue
     * \param[in] score Le score actuel du chevalier
     * \param[in] monstre La pile de monstres actuelle
     */
    void afficheoutrodefaite(Chevalier *chevalier, int score, Monstre *monstre);

    /*---------------------------------------------------------------------------------------------------------------------------------*/

    /**
     * \brief Fait choisir son arme au joueur
     * 
     * Fait choisir son arme au joueur en demandant une entrée de type char
     * parmi les options P, F et C. Fait une boucle jusqu'à ce que le joueur
     * fasse un choix correct.
     * 
     * \return Un entier représentant l'arme choisie : 0 pour Pierre, 1 pour Feuille, 2 pour Ciseaux
     */
    int choixArme(Chevalier *c);

    char TradArme(int choix);

    /*---------------------------------------------------------------------------------------------------------------------------------*/

    /**
     * \brief Compare les choix d'armes entre le monstre et le joueur
     * 
     * Cette fonction détermine le résultat d'une manche en comparant les choix d'armes
     * du monstre (choixarmeM) et du joueur (choixarmeJ). Le résultat est déterminé selon
     * une logique de jeu où chaque arme bat une autre.
     * 
     * — la Pierre bât les Ciseaux (car elle ”casse” les ciseaux) ; 
     * — la Feuille bât la Pierre (car elle ”balaye” la pierre) ; 
     * — les Ciseaux bâtent la Feuille (car ils ”coupent” la feuille) ; 
     * — l’arme bonne à rien se fait battre par toutes les autres armes ; 
     * — l’arme avec un super pouvoir bât toutes les autres armes ; 
     * 
     * \param[in] choixarmeM Le choix d'arme du monstre (0: Pierre, 1: Feuille, 2: Ciseaux, etc.)
     * \param[in] choixarmeJ Le choix d'arme du joueur (0: Pierre, 1: Feuille, 2: Ciseaux, etc.)
     * \return Un type \c combat indiquant le résultat : \c victoire si le joueur gagne, 
     * \c defaite si le joueur perd, ou \c egalite si les deux choix sont identiques.
     */
    Combat comparaison(int choixarmeM, int choixarmeJ);

    /*---------------------------------------------------------------------------------------------------------------------------------*/

    /**
     * \brief Affiche le résultat d'une attaque entre un chevalier et un monstre
     * 
     * Cette fonction affiche le résultat d'une attaque, indiquant si le chevalier
     * a gagné, perdu ou si l'attaque est à égalité contre le monstre. Les informations
     * incluent le pseudo et les points de vie du chevalier, ainsi que le nom
     * et les points de vie du monstre.
     * 
     * \param[in] chevalier Le chevalier qui participe à l'attaque
     * \param[in] monstre Le monstre contre lequel le chevalier se bat
     * \param[in] resultat Le résultat de l'attaque, qui peut être \c victoire,
     * \c defaite, ou \c egalite
     */
    void afficherResultatAttaque(Chevalier *chevalier, Monstre *monstre, Combat resultat);

    /*---------------------------------------------------------------------------------------------------------------------------------*/

    /**
     * \brief Fait jouer le chevalier contre une vague de monstres
     * 
     * Cette fonction fait jouer le chevalier contre une vague de monstres
     * en séquence. Pour chaque monstre, le chevalier et le monstre font
     * un choix d'arme en même temps. Le résultat est déterminé par la
     * fonction de compraison.
     * 
     * Si le chevalier gagne, le monstre perd des points de vie, sinon le
     * chevalier gagne des points de score, et on passe au monstre
     * suivant. Si le chevalier perd, sa vie diminue, et si elle atteint
     * 0, on sort de la fonction.
     * 
     * Si le chevalier gagne contre tous les monstres, on sort de la
     * fonction en indiquant la victoire.
     * 
     * \param[in,out] chevalier Le chevalier qui joue
     * \param[in,out] score Le score actuel du chevalier
     * \param[in,out] pmonstre La pile de monstres
     * \return Un type \c combat indiquant le résultat : \c victoire si le
     * joueur a gagné, \c defaite si le joueur a perdu, ou \c egalite si
     * les deux joueurs ont fait une égalité.
     */
    Combat vague1(Chevalier *chevalier, int *score, PileMonstre pmonstre);

    /*---------------------------------------------------------------------------------------------------------------------------------*/

    /**
     * \brief Fait jouer le chevalier contre une vague de monstres de la vague 2
     * 
     * Cette fonction permet au chevalier de combattre une série de monstres contenus
     * dans une file jusqu'à ce que tous soient vaincus ou que le chevalier perde tous
     * ses points de vie. Pour chaque monstre, le chevalier et le monstre choisissent
     * une arme et le résultat du combat est déterminé.
     * 
     * Si le chevalier gagne, le monstre perd des points de vie et des points de score
     * sont ajoutés au chevalier. Si le monstre est vaincu, il est retiré de la file.
     * Si le chevalier perd, il perd des points de vie. Si tous les monstres sont vaincus,
     * la fonction retourne la victoire. Si le chevalier est vaincu, la fonction retourne
     * la défaite.
     * 
     * \param[in,out] chevalier Le chevalier qui joue
     * \param[in,out] vague2 La file de monstres de la vague 2
     * \return Un type \c combat indiquant le résultat final : \c victoire si le joueur
     * a vaincu tous les monstres, ou \c defaite si le joueur a été vaincu.
     */
    Combat vague2(Chevalier *chevalier, int *score,FileMonstre vague2);

    /*---------------------------------------------------------------------------------------------------------------------------------*/

    /**
     * \brief Fonction qui permet de jouer une partie
     * 
     * Cette fonction permet de jouer une partie en appelant les fonctions
     * \c vague1 et \c vague2. Si le joueur perd contre la vague 1, il perd
     * la partie et le programme s'arrête. Si le joueur gagne, il affiche
     * un message de victoire et le score.
     * 
     * \param[in,out] tableauJ Le tableau des joueurs
     * \param[in,out] joueur Le joueur qui joue
     * \param[in,out] v1Monstre La pile de monstres de la vague 1
     * \param[in,out] v2Monstre La file de monstres de la vague 2
     */
    int jouerPartie(Chevalier *joueur, PileMonstre v1Monstre, FileMonstre v2Monstre);


#endif