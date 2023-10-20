#include "interface.h"

int menue_demarrage(void){
    printf("Bienvenue dans le jeu TAKUZU ! \n");

    //choix de la taille de la partie
    int taille = choix_taille();
    PARTIE * p_partie;

    //préparation de la place mémoire
    creation_partie(taille, &p_partie);
    p_partie->vie = 3; //nombre de vie égale à 3 au début

    //génration d'une grille solution
    generation_grille_solution(p_partie);
    //affiche_grille(p_partie->solution);

    //choix du masque
    choix_masque(p_partie);

    //choix automatique ou jouer
    int choix = 0;
    choix = choix_automatique_ou_non();

    if (choix == 0){
        //lance et joue la partie
        joue_partie(p_partie);
    }
    if (choix == 1){
        //lance et joue la partie
        resolution_automatique(p_partie);
    }

    efface_partie(p_partie);


}

int choix_taille(void){
    printf("Veuillez choisir votre la taille : \n -tappez a pour 4*4\n -tappez b pour 8*8\n");
    printf(" -tappez c pour 16*16 (chargement long)\n");
    int choix = 0;
    int taille = 0;
    char saisie[10];


    while( choix != 97 && choix != 98 && choix != 99){

        scanf("%s", saisie);
        choix = (int) saisie[0];

        if(choix == 97){
            taille = 4;
        }
        if(choix == 98){
            taille = 8;
        }
        if(choix == 99){
            taille = 16;
        }
        if((choix != 97) && (choix != 98) && choix != 99){
            printf("le choix est : %d", choix);
            printf("veuillez saisir a, b ou c :\n");
            printf("Veuillez choisir votre la taille : \n -tappez a pour 4*4\n -tappez b pour 8*8\n");
            //printf(" -tappez c pour 16*16\n");
            scanf("%s", saisie);
            choix = (int) saisie[0];
        }
    }
    printf("la taille choisie est : %d\n", taille);
    return taille;
}

int choix_masque(PARTIE * p_partie){
    char saisie[10];
    int choix = 0;
    printf("Veuillez choisir parmis les choix suivant:\n");
    printf("tappez a pour : Saisir manuellement un masque\n");
    printf("tappez b pour : Generer automatiquement un masque\n");
    printf("tappez c pour : Jouer\n");

    while ( choix != 97 && choix != 98 && choix != 99){
        
        scanf("%s", saisie);
        choix = (int) saisie[0];

        if(choix == 97){
            printf("Vous avez choisi saisie manuelle du masque\n");
            saisie_manuelle_masque(p_partie);
        }
        if(choix == 98){
            printf("Vous avez choisi generation automatique du masque\n");
            generation_automatique_masque(p_partie);
        }
        if(choix == 99){
            printf("Vous avez choisi de jouer\n");
            generation_automatique_masque(p_partie);
        }
        if(choix != 97 && choix != 98 && choix != 99){
            printf("choix = %d\n", choix);
            printf("veuillez saisir a, b ou c :\n");
            printf("Veuillez choisir parmis les choix suivant:\n");
            printf("tappez a pour : Saisir manuellement un masque\n");
            printf("tappez b pour : Generer automatiquement un masque\n");
            printf("tappez c pour : Jouer\n");
            scanf("%s", saisie);
            choix = (int) saisie[0];
        }
    }

    generation_grille_jeu(p_partie);

    if(choix == 'a' || choix == 'b'){
        printf("affichage du masque");
        affiche_grille(p_partie->masque);
        printf("affichage de la grille resultante");
        affiche_grille_jeu(p_partie->grille_jeu);
    }
}


int joue_partie(PARTIE * p_partie){


    int taille = p_partie->taille;
    
    //continue à jouer tant que la grille n'est pas entièrement correcte
    while(grille_corecte(*p_partie) != 1){

        //affichage de la grille de jeu
        printf("Affichage de la grille de jeu\n");
        affiche_grille_jeu(p_partie->grille_jeu);

        //Quel coup coup le joueur souhaite jouer
        char colonne = 'Z';
        int ligne = -1;
        int coup = -1;


        int test_coup_valide = 0;
        while(test_coup_valide == 0){

            int test_case_init = 0;
            while(test_case_init == 0 ){

                int test_saisie = 0;
                while(test_saisie == 0){

                    printf("Veuillez saisir la case dans laquelle vous souhaitez jouer\n");

                    char saisie[10];
                    printf("Saisir la colonne (en lettre):");
                    scanf("%s", saisie);
                    colonne = saisie[0];

                    char saisie1[10];
                    printf("\nSaisir la ligne (en chiffre):");
                    scanf("%s", saisie1);
                    ligne = (int) saisie1[0] -48;

                    char saisie2[10];     
                    printf("\nVeuillez saisir votre coup (0 ou 1):");
                    scanf("%s", saisie2);
                    coup = (int) saisie2[0] -48;

                    //Vérification que les données d'entrées sont valides
                    if (donnee_jeu(ligne, colonne, coup, taille) == 1){
                        test_saisie = 1;
                    }
                    else{
                        //affichage de la grille de jeu
                        printf("Affichage de la grille de jeu\n");
                        affiche_grille_jeu(p_partie->grille_jeu);
                    }
                    
                }
                printf("\nVous avez choisi la case %c%d pour jouer %d\n", colonne, ligne, coup);


                //vérification que le joueur n'a pas joué sur les cases initiales
                if(coup_sur_cases_non_initiales(ligne, colonne, p_partie) == 1){
                    test_case_init = 1;
                }
                else{
                    //affichage de la grille de jeu
                    printf("Vous avez joue sur une case initiale\n");
                    printf("\nAffichage de la grille de jeu\n");
                    affiche_grille_jeu(p_partie->grille_jeu);
                }
            }


            //on place le coup du joueur dans la grille_jeu_coup_joue
            p_partie->grille_jeu_coup_joue.grille[ligne*taille + colonne_to_nombre(colonne)] = coup;

            //On verifie que la grille_jeu_coup_joue respecte les règles du Takuzu
            int regle_non_respectee = grille_valide(p_partie->grille_jeu_coup_joue);
            if(regle_non_respectee == 1){
                test_coup_valide = 1;
                copie_grille(&(p_partie->grille_jeu_coup_joue), &(p_partie->grille_jeu));
            }
            else{
                copie_grille( &(p_partie->grille_jeu), &(p_partie->grille_jeu_coup_joue));
                printf("le coup est invalide\n");
                p_partie->vie--; 
                printf("Il vous reste %d vie(s) \n", p_partie->vie);
                if(p_partie->vie == 0){
                    printf("Vous avez perdu !");
                    return 0;

                }

                //affichage de la grille de jeu
                printf("Affichage de la grille de jeu\n");
                affiche_grille_jeu(p_partie->grille_jeu);
            }
        }

        if(coup_joue_correct(*p_partie, ligne, colonne, coup) == 0){
            
            printf("Coup joue valide mais incorrecte\n");
        }
        else{
            printf("Coup correcte Bravo !\n\n");
        }

    }
    //affichage de la grille de jeu
    printf("Affichage de la grille de jeu\n");
    affiche_grille_jeu(p_partie->grille_jeu);

    printf("Bravo vous avez gagne !!!!\n");

}

int donnee_jeu(int ligne, char colonne, int coup, int taille){
    int col = colonne_to_nombre(colonne);
    if( ligne<0 || ligne>=taille){
        printf("/!\\ La ligne doit etre entre 0 et %d\n", taille-1);
        return 0;
    }
    if( col<0 || col>=taille){
        printf("/!\\ La colonne doit etre entre A et %c\n", nombre_to_colonne(taille-1));
        return 0;
    }
    if(coup!=1 && coup!= 0){
        printf("/!\\ Le coup doit etre égal à 0 ou 1\n");
        return 0;
    }
    return 1;
}

int choix_automatique_ou_non(void){


    char saisie[10];
    int choix = 0;
    printf("Veuillez choisir parmis les choix suivant:\n");
    printf("tappez a pour : Jouer manuellement\n");
    printf("tappez b pour : Resolution de la grille par l'ordinateur\n");

    while ( choix != 97 && choix != 98){
        
        scanf("%s", saisie);
        choix = (int) saisie[0];

        if(choix == 97){
            printf("Vous avez choisi de jouer manuellement\n");
            return 0;
        }
        if(choix == 98){
            printf("Vous avez choisi la resolution de la grille par l'ordinateur\n");
            return 1;
            
        }
    
        if(choix != 97 && choix != 98){
            printf("choix = %d\n", choix);
            printf("veuillez saisir a ou b\n");
            printf("Veuillez choisir parmis les choix suivant:\n");
            printf("tappez a pour : Jouer manuellement\n");
            printf("tappez b pour : Resolution de la grille par l'ordinateur\n");

            scanf("%s", saisie);
            choix = (int) saisie[0];
        }
    }

}
