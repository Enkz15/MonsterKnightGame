/**
 * \file jeu.c
 * \brief Fonctions principales pour le déroulement du jeu
 * \author Delinac Inès | Jouve Enzo
 * \date 16/12/2024 au 10/01/2025
 */

#include "jeu.h"


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
int calculPointsVague1(Chevalier *chevalier, int score, Monstre *monstre){
    return score += SCORE_VICTOIRE_V1 * monstre->niveau;
}

/*---------------------------------------------------------------------------------------------------------------------------------*/

/**
 * \brief Affiche l'introduction d'une manche
 * 
 * Affiche un message qui introduit la manche en cours, en indiquant le nom, les points de vie et les points de dégâts du monstre, ainsi que le pseudo, les points de vie et les points de dégâts du chevalier.
 * 
 * \param[in] chevalier Le chevalier qui joue
 * \param[in] monstre La pile de monstres actuelle
 */
void afficheintro(Chevalier *chevalier, Monstre *monstre){
    if (chevalier == NULL) {
        printf("Erreur : Chevalier introuvable.\n");
        return;
    }

    printf("%sLe monstre %s(%dptV, %dAtt) accoure et se prépare à t'attaquer %s(%dptV, %dAtt)%s%s\n", 
        BLEU,monstre->nom, monstre->pv, monstre->dmg, chevalier->pseudo, chevalier->pv, chevalier->dmg,BLEU, RESET);
}

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
void afficheoutrovictoire(Chevalier *chevalier, int score, Monstre *monstre){
    printf("%s%s(%dptV) gagne l'attaque contre %s(%dptV) + %dpts %s meurt sous le coup de l'attaque + %dpts %s%s\n",
        VERT,chevalier->pseudo, chevalier->pv, monstre->nom, monstre->pv, SCORE_VICTOIRE_ATTAQUE, monstre->nom, SCORE_VICTOIRE_V1 * monstre->niveau,VERT,RESET);
}

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
void afficheoutrodefaite(Chevalier *chevalier, int score, Monstre *monstre){
    printf("%s%s(%dptV) perd l'attaque contre %s(%dptV) \nPERDU... nombre de pts acquis : %d %s%s\n",
        ROUGE,chevalier->pseudo, chevalier->pv,monstre->nom, monstre->pv, score,ROUGE,RESET);
}

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
int choixArme(Chevalier *c) {
    char choix[2];  // Taille 2 pour pouvoir stocker le caractère + le '\0'
    
    while (1) {
        printf("%s (%dpts), choisis ton arme parmi P, F, C : ", c->pseudo, c->pv);
        scanf("%s%*c", choix);  // Lecture de la chaîne de caractères

        // Vérification de la validité du choix
        if (choix[0] == 'P' || choix[0] == 'F' || choix[0] == 'C') {
            break;  // Sortir de la boucle si le choix est valide
        } else {
            printf("Choix incorrect\n");
        }
    }

    // Traduction de l'arme en numérique
    switch (choix[0]) {
        case 'P':
            return 0;
        case 'F':
            return 1;
        case 'C':
            return 2;
        default:
            return -1;  // En cas de choix invalide, ce cas ne devrait pas être atteint
    }
}



char TradArme(int choix){
    switch (choix)
    {
    case 0:
        return 'P';
        break;

    case 1:
        return 'F';
        break;

    case 2:
        return 'C';
        break;
    case 3:
        return 'O';
        break;
    case 4:
        return '#';
        break;
    }
    return NULL;
}

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
Combat comparaison(int choixarmeM, int choixarmeJ){
   if(choixarmeM == 3)
        return victoire;
    if(choixarmeM == 4)
        return defaite;

    int res=((choixarmeM - choixarmeJ+3)%3);

    if (res==2)
        return victoire;
    if (res==1)
        return defaite;

    return egalite;
}

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
void afficherResultatAttaque(Chevalier *chevalier, Monstre *monstre, Combat resultat) {
    if (resultat == victoire) {
        printf("%s%s(%dptV) gagne l'attaque contre %s(%dptV) + %dpts%s%s\n",
               VERT,chevalier->pseudo, chevalier->pv, monstre->nom, monstre->pv, SCORE_VICTOIRE_ATTAQUE,VERT,RESET);
    } else if (resultat == defaite) {
        printf("%s%s(%dptV) perd l'attaque contre %s(%dptV)%s%s\n", 
                ROUGE,chevalier->pseudo, chevalier->pv, monstre->nom, monstre->pv,ROUGE,RESET);
    } else if (resultat == egalite){
        printf("%sAucun de %s(%dptV) et %s(%dptV) ne gagne l'attaque%s%s\n",
               ORANGE,chevalier->pseudo, chevalier->pv, monstre->nom, monstre->pv,ORANGE,RESET);
    } else {
        perror("Resultat inconnu");
        exit(EXIT_FAILURE);
    }
}

/*---------------------------------------------------------------------------------------------------------------------------------*/

/**
 * \brief Fait jouer le chevalier contre une vague de monstres
 * 
 * Cette fonction fait jouer le chevalier contre une vague de monstres
 * en séquence. Pour chaque monstre, le chevalier et le monstre font
 * un choix d'arme en même temps. Le résultat est déterminé par la
 * fonction de comparaison.
 * 
 * Si le chevalier gagne, le monstre perd des points de vie, sinon le
 * chevalier gagne des points de score, et on passe au monstre
 * suiv. Si le chevalier perd, sa vie diminue, et si elle atteint
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
Combat vague1(Chevalier *chevalier, int *score, PileMonstre pmonstre){
    int choixarmeJ;
    int choixarmeM;
    char choixJ, choixM;
    int result;
    while(pmonstre != NULL){
        choixarmeJ = choixArme(chevalier);
        choixarmeM = choixArmeMonstre(pmonstre->monstre);
        
        choixJ = TradArme(choixarmeJ);
        choixM = TradArme(choixarmeM);

        
        printf("%s (%c) attaque %s (%c)\n", chevalier->pseudo, choixJ, pmonstre->monstre->nom, choixM);

        result = comparaison(choixarmeM, choixarmeJ);

        afficherResultatAttaque(chevalier, pmonstre->monstre, result);

        if(result == victoire){
            pmonstre->monstre->pv -= chevalier->dmg;
            score += SCORE_VICTOIRE_ATTAQUE;
            if(pmonstre->monstre->pv > 0){
                *score = calculPointsVague1(chevalier, *score, pmonstre->monstre);
                afficheoutrovictoire(chevalier, *score, pmonstre->monstre);
                pmonstre = popPile(pmonstre);
                if (pmonstre != NULL){
                    afficheintro(chevalier, pmonstre->monstre);
                }
            }
        }else if(result == defaite){
            chevalier->pv -= pmonstre->monstre->dmg;
            if(chevalier->pv <= 0){
                afficheoutrodefaite(chevalier, *score, pmonstre->monstre);
                clearPile(pmonstre);
                return defaite;
            }
        }
            
    }
    return victoire;
    
}

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
Combat vague2(Chevalier *chevalier, int *score,FileMonstre vague2) {
    int resultat;
    int choixArmeJ = 0, choixArmeM = 0;

    printf("Tous les monstres sont morts... \n");
    printf("\n");
    printf("Vous arrivez au bout du corridor, une plaine herbeuse apparaît. \n");
    printf("Malheureusement des monstres sortent de partout pour tous vous attaquer en même temps ou presque...\n"); //contexte

    while (vague2.tete != NULL) {
        MaillonMonstre *monstreCourant = vague2.tete;
        
        afficheintro(chevalier, monstreCourant->monstre);

        choixArmeJ = choixArme(chevalier);
        choixArmeM = choixArmeMonstre(monstreCourant->monstre);

        resultat = comparaison(choixArmeM, choixArmeJ);

        if (resultat == victoire) {
            *score += SCORE_VICTOIRE_ATTAQUE;
            monstreCourant->monstre->pv -= chevalier->dmg;
            if (monstreCourant->monstre->pv <= 0) {
                *score += monstreCourant->monstre->niveau * SCORE_VICTOIRE_V2;
            } 
        } else if (resultat == defaite) {
            chevalier->pv -= monstreCourant->monstre->dmg;
        }

        afficherResultatAttaque(chevalier, monstreCourant->monstre, resultat);

        if (monstreCourant->monstre->pv <= 0) {
            printf("%s meurt sous le coup de l'attaque + %dpts !\n", monstreCourant->monstre->nom, SCORE_VICTOIRE_ATTAQUE*monstreCourant->monstre->niveau);

            if (vague2.tete == vague2.queue) {
                libererMonstre(vague2.tete->monstre);
                vague2.tete = NULL;
                vague2.queue = NULL;
            } else {
                Monstre *tmp = vague2.tete->monstre;
                vague2.tete = (vague2.tete)->suiv;
                (vague2.queue)->suiv = vague2.tete;
                libererMonstre(tmp);
            }
        } else {
            vague2.queue = vague2.tete;
            vague2.tete = (vague2.tete)->suiv;
        }

        if (chevalier->pv <= 0) {
            afficheoutrodefaite(chevalier, *score, monstreCourant->monstre);
            return defaite;
        }
    }

    if (chevalier->pv > 0) {
        printf("\nBravo %s, vous avez vaincu tous les monstres !\n", chevalier->pseudo);
    }
    return victoire;
}


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
int jouerPartie(Chevalier *joueur, PileMonstre v1Monstre, FileMonstre v2Monstre){
    Combat result;
    int score=0;
    result = vague1(joueur, &score, v1Monstre);
    if (result == defaite) {
        afficheoutrodefaite(joueur, score, v1Monstre->monstre);
        return score;
    }

    result = vague2(joueur, &score, v2Monstre);
    if (result == victoire) {
        afficheoutrovictoire(joueur, score, v2Monstre.tete->monstre);
    }else{
        afficheoutrodefaite(joueur, score, v2Monstre.tete->monstre);
        return score;
    }

    return score;
}