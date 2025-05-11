/**
 * \file monstres.c
 * \brief Fonctions principales pour les monstres
 * \author Jouve Enzo
 * \date 02/01/2025
 */
#include "monstres.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


//Partie Pile

/**
 * \brief Création d'une pile de monstres
 *
 * \return Une pile de monstres vide (NULL)
 */
PileMonstre creerPile(void){
    return NULL;
}

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
PileMonstre pushPile(PileMonstre p, Monstre *x){
    MaillonMonstre *m;

	m = malloc(sizeof(*m));

	if(m == NULL)
	{
		fprintf(stderr, "Probleme allocation dynamique.\n");
		exit(1);
	}

	m->monstre = creerMonstre(x->nom, x->niveau);
	m->suiv = p;


	return m;
}

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
PileMonstre popPile(PileMonstre p){
    MaillonMonstre *m;

	if(p == NULL)
		return NULL;

	m = p->suiv;
	free(p);

	return m;
}

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
PileMonstre clearPile(PileMonstre p){
    while(p != NULL)
		p = popPile(p);

	return NULL;
}

/*---------------------------------------------------------------------------------------------------------------------------------*/

//Partie File

/**
 * \brief Crée une file de monstres vide
 *
 * Crée une file de monstres avec un maillon tête et un maillon queue
 * initialisés à NULL.
 *
 * \return Une file de monstres vide
 */
FileMonstre creerFileMonstre(void){
    FileMonstre f;
    f.tete = NULL;
    f.queue = NULL;
    return f;
}

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
FileMonstre enfilerMonstre(FileMonstre f, Monstre *x){
    MaillonMonstre *m;
    m = malloc(sizeof(*m));
    if (m == NULL) {
        perror("Erreur d'allocation mémoire");
        exit(EXIT_FAILURE);
    }
    m->monstre = x;
    m->suiv = NULL;
    if (f.tete == NULL) {
        f.tete = m;
        f.queue = m;
    } else {
        f.queue->suiv = m;
        f.queue = m;
    }

    return f;
}

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
FileMonstre defilerMonstre(FileMonstre f){
    MaillonMonstre *m;
    if (f.tete == NULL) {
        return f;
    }
    m = f.tete;
    f.tete = f.tete->suiv;
    free(m);
    return f;
}

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
FileMonstre clearFileMonstre(FileMonstre f){
    while (f.tete != NULL) {
        f = defilerMonstre(f);
    }
    return f;
}

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
Monstre *creerMonstre(char *nom, int niveau) {
    Monstre *monstre = malloc(sizeof(Monstre));
    if (monstre == NULL) {
        perror("Erreur du malloc\n");
        exit(1);
    }
    monstre->nom = strdup(nom);
    monstre->niveau = niveau;

    switch (niveau) {
        case 1:
            monstre->pv = 4;
            monstre->dmg = 1;
            monstre->nbArmes = 4;
            break;
        case 2:
            monstre->pv = 6;
            monstre->dmg = 1;
            monstre->nbArmes = 3;
            break;
        case 3:
            monstre->pv = 4;
            monstre->dmg = 2;
            monstre->nbArmes = 5;
            break;
        default:
            printf("Niveau %d incorrect, veuillez choisir un niveau entre 1 et 3\n", niveau);
            free(monstre);
            return NULL;
    }
    return monstre;
}

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
void ajouterMonstresPersonnalise(PileMonstre *vague1, FileMonstre *vague2) {
    char choix, *nom = NULL;
    int niveau, vague;

    MaillonMonstre m;

    while (1) {
        printf("\nEntrez la vague (1 ou 2, 0 pour quitter) : ");
        scanf("%d", &vague);

        if (vague == 0) break;
        if (vague != 1 && vague != 2) {
            printf("Choix de vague invalide. Réessayez.\n");
            continue;
        }

        printf("\nMenu des monstres :\n");
        printf("- A. Chouin-Chouin\n");
        printf("- B. Lutin Cordial\n");
        printf("- C. Chimere\n");
        printf("- D. Petite Pustule\n");
        printf("- E. Dragonus\n");
        printf("Choix : ");
        scanf(" %c", &choix);

        switch (choix) {
            case 'A': case 'a':
                nom = "Chouin-Chouin";
                break;
            case 'B': case 'b':
                nom = "Lutin Cordial";
                break;
            case 'C': case 'c':
                nom = "Chimere";
                break;
            case 'D': case 'd':
                nom = "Petite Pustule";
                break;
            case 'E': case 'e':
                nom = "Dragonus";
                break;
            default:
                printf("Choix invalide. Réessayez.\n");
                continue;
        }

        printf("Entrez le niveau (1-3) : ");
        scanf("%d", &niveau);

        if (niveau < 1 || niveau > 3) {
            printf("Niveau invalide. Réessayez.\n");
            continue;
        }

        m.monstre = creerMonstre(nom, niveau);
        if (m.monstre != NULL) {
            if (vague == 1){
                *vague1 = pushPile(*vague1, m.monstre); 
            } else if (vague == 2) {
                *vague2 = enfilerMonstre(*vague2, m.monstre);
            }
            printf("%s (Niveau %d) ajouté à la Vague %d.\n", nom, niveau, vague);
        } else {
            printf("Erreur : le monstre %s n'a pas pu être créé.\n", nom);
        }
    }
}

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
void lireMonstres(char *nomFichier, PileMonstre *vague1, FileMonstre *vague2) {
    char tmpFichier[] = "src/fichier/";
    strcat(tmpFichier, nomFichier);
    FILE *fichier = fopen(tmpFichier, "r");
    if (fichier == NULL) {
        perror("Erreur lors de l'ouverture du fichier");
        exit(1);
    }

    int contexteActuel = 0; // 1 = vague 1, 2 = vague 2
    char nom[50]; 
    int niveau, nbMonstre;

    while (fscanf(fichier, "%49s", nom) == 1) {
        if (strcmp(nom, "Contexte") == 0) {
            contexteActuel++;
            fscanf(fichier, "%d", &nbMonstre);
            if (contexteActuel == 1) {
                *vague1 = creerPile();
            } else if (contexteActuel == 2) {
                *vague2 = creerFileMonstre();
            }
            continue;
        }

        if (fscanf(fichier, "%d", &niveau) == 1) {
            MaillonMonstre *m = malloc(sizeof(*m));
            if (m == NULL) {
                perror("Erreur d'allocation mémoire");
                exit(1);
            }
            m->monstre = creerMonstre(nom, niveau);

            if (contexteActuel == 1) {
                *vague1 = pushPile(*vague1, m->monstre);
                printf("%s (Niveau %d) ajouté à la Vague 1.\n", nom, niveau);
            } else if (contexteActuel == 2) {
                *vague2 = enfilerMonstre(*vague2, m->monstre);
                printf("%s (Niveau %d) ajouté à la Vague 2.\n", nom, niveau);
            }
        }
    }

    fclose(fichier);
    printf("Lecture des monstres depuis le fichier '%s' terminée.\n", nomFichier);
}


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
int choixArmeMonstre(Monstre *monstre){
    srand(time(NULL)); // Utilise l'heure actuelle comme graine pour la fonction rand
    int random_number;
    switch (monstre->niveau)
    {
    case 1:
        // Génération d'un nombre aléatoire entre 0 et 3
        random_number = rand() % 4;
        break;

    case 2:
        // Génération d'un nombre aléatoire entre 0 et 3
        random_number = rand() % 3;
        break;

    case 3:
        // Génération d'un nombre aléatoire entre 0 et 3
        random_number = rand() % 5;
        break;
    
    default:
        if (monstre->niveau > 3 || monstre->niveau < 1){
            printf("Le niveau du monstre est incorrect\n");
            exit(EXIT_FAILURE);
        }
        break;
    }
    return random_number;
}

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
void afficherMonstre(Monstre *monstre) {
    if (monstre == NULL)
        return;
    printf("Monstre : %s (Niveau %d)\n", monstre->nom, monstre->niveau);
    printf("- Points de Vie : %d\n", monstre->pv);
    printf("- Points de Dégât : %d\n", monstre->dmg);
    printf("- Nombre d'armes : %d\n", monstre->nbArmes);
}

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
void afficherVague1(PileMonstre vague1) {
    PileMonstre current = vague1;
    if (current == NULL) {
        printf("La Pile est vide.\n");
        return; // Quitter si la pile est vide
    }
    
    int compteur = 0; // Pour limiter les affichages en cas de boucle infinie
    while (current != NULL) {
        afficherMonstre(current->monstre);
        current = current->suiv;
        compteur++;
        if (compteur > 100) { // Sécurité
            printf("Erreur : boucle infinie détectée dans la pile.\n");
            break;
        }
    }
}


/*---------------------------------------------------------------------------------------------------------------------------------*/

/**
 * \brief Affiche tous les monstres de la deuxième vague
 * 
 * Parcourt la file de monstres \c vague2 et affiche les informations de chaque monstre
 * en utilisant la fonction \c afficherMonstre.
 * 
 * \param[in] vague2 La file de monstres de la deuxième vague à afficher
 */
void afficherVague2(FileMonstre vague2) {
    MaillonMonstre *current = vague2.tete; // Pointeur temporaire pour parcourir la file
    if (current == NULL) {
        printf("La File est vide.\n");
        return; // Quitter si la file est vide
    }

    int compteur = 0; // Pour limiter les affichages en cas de boucle infinie
    while (current != NULL) {
        afficherMonstre(current->monstre);
        current = current->suiv;
        compteur++;
        if (compteur > 100) { // Sécurité
            printf("Erreur : boucle infinie détectée dans la file.\n");
            break;
        }
    }
}

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
void libererMonstre(Monstre *monstre) {
    if (monstre != NULL) {
        free(monstre->nom); 
        free(monstre);
    } else {
        printf("Erreur de free.\n");
    }
}


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
void libererVague1(PileMonstre vague1) {
    PileMonstre current = vague1;
    while (current != NULL) {
        PileMonstre suivant = current->suiv;
        if (current->monstre != NULL) {
            libererMonstre(current->monstre); 
        }
        free(current); 
        current = suivant; 
    }
}


/*---------------------------------------------------------------------------------------------------------------------------------*/

/**
 * \brief Libère la mémoire allouée pour la vague 2
 *
 * Libère la mémoire allouée pour la vague 2 en libérant chaque monstre
 * puis en libérant les maillons de la file.
 *
 * \param[in] vague2 La file de monstres de la vague 2 à libérer
 *
 */
void libererVague2(FileMonstre vague2) {
    MaillonMonstre *current = vague2.tete;
    while (current != NULL) {
        MaillonMonstre *suivant = current->suiv;
        if (current->monstre != NULL) {
            libererMonstre(current->monstre);
        }
        free(current);
        current = suivant;
    }
}


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
int estMort(Monstre* monstre) {
    if (monstre->pv <= 0) {
        return VIVANT; // Return 0
    } else {
        return MORT; // Return 1
    }
}
