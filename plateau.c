#include "plateau.h"
#define CASE_DEPART 625

/**
 * Réserve l'espace mémoire pour une grille
**/

int creation_grille(int taille, GRILLE * p_grille){
    p_grille->taille = taille;
    p_grille->grille = (int *) malloc(taille*sizeof(int)*taille*sizeof(int));
    return 1;
}


/**
 * Réserve l'espace mémoire pour une partie
**/
int creation_partie(int taille, PARTIE ** p_p_partie){
    *p_p_partie = malloc(sizeof(PARTIE));
    PARTIE * p_partie = *p_p_partie;
    p_partie->taille = taille;
    creation_grille(taille, &(p_partie->grille_jeu));
    creation_grille(taille, &(p_partie->grille_jeu_coup_joue));
    creation_grille(taille, &(p_partie->solution));
    creation_grille(taille, &(p_partie->masque));
    return 1;
}

/**
 * Désaloue l'espace mémoire pour une partie
**/
int efface_partie(PARTIE * p_partie){
    free(p_partie->grille_jeu.grille);
    free(p_partie->grille_jeu_coup_joue.grille);
    free(p_partie->masque.grille);
    free(p_partie->solution.grille);

    free(p_partie);
    return 1;
}

//attention n'efface pas la partie
int creation_partie_test(PARTIE ** p_p_partie){
    creation_partie(4, p_p_partie);

    PARTIE * p_partie = *p_p_partie;
    p_partie->solution.grille[0] = 1;
    p_partie->solution.grille[1] = 0;
    p_partie->solution.grille[2] = 0;
    p_partie->solution.grille[3] = 1;
    p_partie->solution.grille[4] = 1;
    p_partie->solution.grille[5] = 0;
    p_partie->solution.grille[6] = 1;
    p_partie->solution.grille[7] = 0;
    p_partie->solution.grille[8] = 0;
    p_partie->solution.grille[9] = 1;
    p_partie->solution.grille[10] = 1;
    p_partie->solution.grille[11] = 0;
    p_partie->solution.grille[12] = 0;
    p_partie->solution.grille[13] = 1;
    p_partie->solution.grille[14] = 0;
    p_partie->solution.grille[15] = 1;

    p_partie->masque.grille[0] = 1;
    p_partie->masque.grille[1] = 0;
    p_partie->masque.grille[2] = 0;
    p_partie->masque.grille[3] = 0;
    p_partie->masque.grille[4] = 0;
    p_partie->masque.grille[5] = 0;
    p_partie->masque.grille[6] = 1;
    p_partie->masque.grille[7] = 0;
    p_partie->masque.grille[8] = 1;
    p_partie->masque.grille[9] = 0;
    p_partie->masque.grille[10] = 1;
    p_partie->masque.grille[11] = 1;
    p_partie->masque.grille[12] = 0;
    p_partie->masque.grille[13] = 1;
    p_partie->masque.grille[14] = 0;
    p_partie->masque.grille[15] = 0;

    generation_grille_jeu(*p_p_partie);

}


//génère une grille solution
int creation_partie_test_grille_solution(PARTIE * p_partie){

    p_partie->solution.grille[0] = 1;
    p_partie->solution.grille[1] = 0;
    p_partie->solution.grille[2] = 0;
    p_partie->solution.grille[3] = 1;
    p_partie->solution.grille[4] = 1;
    p_partie->solution.grille[5] = 0;
    p_partie->solution.grille[6] = 1;
    p_partie->solution.grille[7] = 0;
    p_partie->solution.grille[8] = 0;
    p_partie->solution.grille[9] = 1;
    p_partie->solution.grille[10] = 1;
    p_partie->solution.grille[11] = 0;
    p_partie->solution.grille[12] = 0;
    p_partie->solution.grille[13] = 1;
    p_partie->solution.grille[14] = 0;
    p_partie->solution.grille[15] = 1;

}

//générer la grille jeu grace au masque et à la solution
int generation_grille_jeu(PARTIE * p_partie){
    int taille = p_partie->taille;
    for (int i = 0; i<taille*taille; i++){
        if(p_partie->solution.grille[i]==1 && p_partie->masque.grille[i]==1){
            p_partie->grille_jeu.grille[i]=1;
            p_partie->grille_jeu_coup_joue.grille[i]=1;
        }
        if(p_partie->solution.grille[i]==0 && p_partie->masque.grille[i]==1){
            p_partie->grille_jeu.grille[i]=0;
            p_partie->grille_jeu_coup_joue.grille[i]=0;
        }
        if(p_partie->masque.grille[i]==0){
            p_partie->grille_jeu.grille[i]=-1;
            p_partie->grille_jeu_coup_joue.grille[i]=-1;
        }
    }
    return 1;

}
//*
/**
 * Joue : fonction qui prend en entrée la cause où le joueur souhaite jouer et le coup (0 ou 1) désiré
 * On recopie la grille du coup du joueur dans la grille jeu si le coup est valide
 * 
 * return -1 si le joueur à joué sur une case initiale
 * return -2 si le coup est incorrecte
 * return  1 si coup est valide mais incorrecte et modifie la partie
 * return  2 si le coup est correcte et modifie la partie
 * correcte = coup solution
 * valide = coup qui respecte les règles du jeu
**/


int joue(int ligne, char colonne, int coup, PARTIE * p_partie){

    int taille = p_partie->taille;
    if (coup_sur_cases_non_initiales(ligne, colonne, p_partie) == 0){
        return -1;
    }

    
    if (coup_joue_correct(*p_partie, ligne, colonne, coup) ==  1){
        p_partie->grille_jeu_coup_joue.grille[ligne*taille+colonne_to_nombre(colonne)] = coup;
        copie_grille(&(p_partie->grille_jeu_coup_joue), &(p_partie->grille_jeu));
        return 2;
    }

    p_partie->grille_jeu_coup_joue.grille[ligne*taille+colonne_to_nombre(colonne)] = coup;

    if (grille_valide(p_partie->grille_jeu_coup_joue) ==  1){
        copie_grille(&(p_partie->grille_jeu_coup_joue), &(p_partie->grille_jeu));
        return 1;
    }

    copie_grille(&(p_partie->grille_jeu), &(p_partie->grille_jeu_coup_joue));

    return -1;
}


/**
 * regarde si on a pas touché aux cases initiales
 * si touché -> return 0
 * sinon return 1
**/

int coup_sur_cases_non_initiales(int ligne, char colonne, PARTIE * p_partie){
    int taille = p_partie->taille;
    int position = ligne*taille + colonne_to_nombre(colonne);
    if (p_partie->masque.grille[position] == 1){
        return 0;
    }
    return 1;
}


//coup joué correcte
int coup_joue_correct(PARTIE partie, int ligne, char colonne, int coup){
    int taille = partie.taille;
    if(partie.solution.grille[ligne*taille + colonne_to_nombre(colonne)] != coup){
        return 0;
    }        
    return 1;
}

int grille_corecte(PARTIE partie){
    int taille = partie.taille;
    for (int i = 0; i<taille*taille; i++){
        if(partie.solution.grille[i] != partie.grille_jeu.grille[i]){
            return 0;
        }     
    }
    return 1;
}

int grille_valide(GRILLE grille){
    int taille = grille.taille;

    //regle 1 : Dans une ligne, il doit y avoir autant de 0 que de 1
    int nb_un_ligne = 0;
    int nb_zero_ligne = 0;
    for(int i = 0; i<taille; i++){
        nb_un_ligne = 0;
        nb_zero_ligne = 0;
        for(int j = 0; j<taille; j++){
            if(grille.grille[i*taille + j] ==  1){
                nb_un_ligne++;
            }
            if(grille.grille[i*taille + j] ==  0){
                nb_zero_ligne++;
            }
            
        }
        if(nb_un_ligne > taille/2 || nb_zero_ligne > taille/2){
            printf("Regle non respectee : Dans une ligne, il doit y avoir autant de 0 que de 1\n");
            return -1;
        }
    }

    //regle 2 :  Dans une colonne, il doit y avoir autant de 0 que de 1
    int nb_un_colonne = 0;
    int nb_zero_colonne = 0;
    for (int j = 0; j<taille; j++){
        nb_un_colonne = 0;
        nb_zero_colonne = 0;
        for(int i = 0; i<taille; i++){
            if(grille.grille[i*taille+j]==1){
                nb_un_colonne++;
            }
            if(grille.grille[i*taille+j]==0){
                nb_zero_colonne++;
            }
        }
        if(nb_un_colonne > taille/2 || nb_zero_colonne > taille/2){
            printf("Regle non respectee : Dans une colonne, il doit y avoir autant de 0 que de 1\n");
            return -2;
        }
    }

    //regle 3 : Il ne peut pas avoir deux lignes identique dans une grille
    int * ligne_a_comparer; //ligne qui va tester toutes les lignes
    int * ligne_comparante; //ligne stock la ligne à comparer
    for(int i = 0; i<taille-1; i++){//ligne à comparer
        ligne_a_comparer = &(grille.grille[i*taille]);
        for(int k = i+1; k<taille; k++){//ligne comparante
            ligne_comparante = &(grille.grille[k*taille]);
            int test_meme_val = 0;
            for(int a = 0; a<taille; a++){//parcours les deux lignes pour comparer
                if(ligne_a_comparer[a]==ligne_comparante[a] && ligne_a_comparer[a]!=-1){
                    test_meme_val++;
                }
            }
            if (test_meme_val==taille){
                printf("Règle non respectée : Il ne peut pas avoir deux lignes identique dans une grille\n");
                return -3;
            }
        }
    }

    //regle 4: Il ne peut pas y avoir deux colonnes identiques dans une grille
    int colonne_a_comparer[taille]; //colonne qui va tester toutes les autres colonnes
    int colonne_comparante[taille]; //colonne qui stock la colone à comparer
    for(int j = 0; j<taille-1; j++){//colonne à comparer
        for(int i = 0; i<taille; i++){//remplissage de la colonne
            colonne_a_comparer[i] = grille.grille[i*taille + j];
        }
        for(int k = j+1; k<taille; k++){//parcours des collones comparantes
            for(int i = 0; i<taille; i++){//remplissage de la colonne
                colonne_comparante[i] = grille.grille[i*taille + k];
            }
            int test_meme_val2 = 0;
            for(int a = 0; a<taille; a++){//parcours les cases des deux colonnes à comparer
                if(colonne_a_comparer[a]==colonne_comparante[a] && colonne_a_comparer[a]!=-1){
                    test_meme_val2++;
                }
            }
            if(test_meme_val2==taille){
                printf("Règle non respectée : Il ne peut pas y avoir deux colonnes identiques dans une grille\n");
                return -4;
            }
        }
    }

    //regle 5:  Dans une ligne ou une colonne, il ne peut y avoir plus de deux 0 ou deux 1 à la suite (on ne peut pas avoir 
    //trois 0 de suite ou trois 1 de suite)
    //lignes:
    int nb_un_a_la_suite = 0;
    int nb_zero_a_la_suite = 0;
    int case_avant = -1;
    int case_actuelle = -1;
    for(int i = 0; i<taille; i++){
        nb_un_a_la_suite = 0;
        nb_zero_a_la_suite = 0;
        case_avant = -1;
        case_actuelle = -1;
        for(int j = 0; j<taille; j++){
            case_actuelle = grille.grille[i*taille + j];
            if (case_actuelle == case_avant){
                if(case_actuelle == 1){
                    nb_un_a_la_suite++;
                }
                if(case_actuelle == 0){
                    nb_zero_a_la_suite++;
                }
            }
            if (case_actuelle != case_avant){
                if(case_actuelle == 1){
                    nb_un_a_la_suite = 1;
                    nb_zero_a_la_suite = 0;
                }
                if(case_actuelle == 0){
                    nb_un_a_la_suite = 0;
                    nb_zero_a_la_suite = 1;
                }
            }
            if (nb_un_a_la_suite > 2 || nb_zero_a_la_suite > 2){
                printf("Règle non respectée : Dans une ligne ou une colonne, il ne peut y avoir plus de deux 0 ou deux 1 à la suite (on ne peut pas avoir trois 0 de suite ou trois 1 de suite)\n");
                return -5; 
            }
        }
            case_avant = case_actuelle;        
    }

    //colonne:
    nb_un_a_la_suite = 0;
    nb_zero_a_la_suite = 0;
    case_avant = -1;
    case_actuelle = -1;
    for(int j = 0; j<taille; j++){
        nb_un_a_la_suite = 0;
        nb_zero_a_la_suite = 0;
        case_avant = -1;
        case_actuelle = -1;
        for(int i = 0; i<taille; i++){
            case_actuelle = grille.grille[i*taille + j];
            if (case_actuelle == case_avant){
                if(case_actuelle == 1){
                    nb_un_a_la_suite++;
                }
                if(case_actuelle == 0){
                    nb_zero_a_la_suite++;
                }
            }
            if (case_actuelle != case_avant){
                if(case_actuelle == 1){
                    nb_un_a_la_suite = 1;
                    nb_zero_a_la_suite = 0;
                }
                if(case_actuelle == 0){
                    nb_un_a_la_suite = 0;
                    nb_zero_a_la_suite = 1;
               }
            }
            if (nb_un_a_la_suite > taille/2 || nb_zero_a_la_suite>taille/2){
                return 0; 
            }
            case_avant = case_actuelle; 
        }
    }

    return 1;

}

/**
 * copie une grille dans une autre
**/
int copie_grille(GRILLE * p_grille_a_copier, GRILLE * p_grille_receveuse){
    int taille = p_grille_a_copier->taille;
    for (int i = 0; i<taille*taille; i++){
        p_grille_receveuse->grille[i] = p_grille_a_copier->grille[i];
    }
    return 1;
}

int affiche_grille(GRILLE grille){
    printf("\n");
    for(int i = 0; i<grille.taille; i++){
        for(int j = 0; j<grille.taille; j++){
            printf(" %d", grille.grille[i*grille.taille+j]);
        }
        printf("\n");
    }
}

/**
 * transforme la lettre de la colonne en nombre
**/
int colonne_to_nombre(char colonne){
    if (colonne == 'a' || colonne == 'A'){
        return 0;
    }
    if (colonne == 'b' || colonne == 'B'){
        return 1;
    }
    if (colonne == 'c' || colonne == 'C'){
        return 2;
    }
    if (colonne == 'd' || colonne == 'D'){
        return 3;
    }
    if (colonne == 'e' || colonne == 'E'){
        return 4;
    }
    if (colonne == 'f' || colonne == 'F'){
        return 5;
    }
    if (colonne == 'g' || colonne == 'G'){
        return 6;
    }
    if (colonne == 'h' || colonne == 'H'){
        return 7;
    }
    if (colonne == 'i' || colonne == 'I'){
        return 8;
    }
    if (colonne == 'J' || colonne == 'J'){
        return 9;
    }
    if (colonne == 'k' || colonne == 'K'){
        return 10;
    }
    if (colonne == 'l' || colonne == 'L'){
        return 11;
    }
    if (colonne == 'M' || colonne == 'M'){
        return 12;
    }
    if (colonne == 'n' || colonne == 'N'){
        return 13;
    }
    if (colonne == 'O' || colonne == 'O'){
        return 14;
    }
    if (colonne == 'P' || colonne == 'P'){
        return 15;
    }
    return -1;
}

/**
 * transforme le numero de la colonne en lettre
**/
char nombre_to_colonne(int nombre){
    if (nombre == 0){
        return 'A';
    }
    if (nombre == 1){
        return 'B';
    }
    if (nombre == 2){
        return 'C';
    }
    if (nombre == 3){
        return 'D';
    }
    if (nombre == 4){
        return 'E';
    }
    if (nombre == 5){
        return 'F';
    }
    if (nombre == 6){
        return 'G';
    }
    if (nombre == 7){
        return 'H';
    }
    if (nombre == 8){
        return 'I';
    }
    if (nombre == 9){
        return 'J';
    }
    if (nombre == 10){
        return 'K';
    }
    if (nombre == 11){
        return 'L';
    }
    if (nombre == 12){
        return 'M';
    }
    if (nombre == 13){
        return 'N';
    }
    if (nombre == 14){
        return 'O';
    }
    if (nombre == 15){
        return 'P';
    }

}

int saisie_manuelle_masque(PARTIE * p_partie){
    int taille = p_partie->taille;
    printf("Lorsque ca vous sera demande, saisir 1 pour une case visible et 0 pour une case invisible\n");
    char saisie[10];
    int choix = -1;
    int ligne = 0;
    char colonne = 0;
    for (int i = 0; i<taille*taille; i++){
        ligne = i/taille;
        colonne = nombre_to_colonne(i%taille);
        while(choix != 1 && choix != 0){
            printf("Veuillez saisir la valeur de la case ligne:%d, colonne:%c \n", ligne, colonne);
            scanf("%s", saisie);
            choix = ((int) saisie[0]) - 48;
            printf("choix : %d\n", choix);
        }
        p_partie->masque.grille[i] = choix;
        choix = -1;
    }
    printf("Grille masque remplie !\n");
    return 1;
}
int generation_automatique_masque(PARTIE * p_partie){
    int taille = p_partie->taille;
    int pourcentage = 0;
    int pourcentage_case_invisible_au_depart = CASE_DEPART;

    //initialisation de la fonction rand() pour générer de l'aléatoire
    srand(time(NULL));
    
    //printf("Generation aléatoire du masque initial\n");
    for (int i = 0; i<taille*taille; i++){
        pourcentage = rand()%1000;
        if(pourcentage < pourcentage_case_invisible_au_depart){
            p_partie->masque.grille[i] = 0;
        }
        else{
            p_partie->masque.grille[i] = 1;
        }
    }
    //printf("Grille masque remplie !\n");
    return 1;
}

int affiche_grille_jeu(GRILLE grille){
    printf("\n");
    for(int i = 0; i<grille.taille; i++){
        for(int j = 0; j<grille.taille; j++){
            int val =  grille.grille[i*grille.taille+j];
            if(val == -1){
                printf(" .");
            }
            else{
               printf(" %d", val); 
            }
        }
        printf("\n");
    }
}

int resolution_automatique(PARTIE * p_partie){
    int taille = p_partie->taille;
    char colonne_char;
    int coup = 0;

    //initialisation de la fonction rand() pour générer de l'aléatoire
    srand(time(NULL));

    //On parcours la grille de jeu
    for(int i = 0; i<taille; i++){
        for(int j = 0; j<taille; j++){

            colonne_char = nombre_to_colonne(j);
            coup = 0;
            

            //on vérifie qu'on n'est pas sur une case initiale
            if(coup_sur_cases_non_initiales(i, colonne_char, p_partie) == 1){

                //On verifie que le coup est correcte

                coup = rand()%2;
                int test_coup_correcte = coup_joue_correct(*p_partie, i, colonne_char, coup);
                if(test_coup_correcte == 1){
                    printf("\nJe joue dans la case %c%d le coup : %d\n", colonne_char, i, coup);
                    printf("Coup correcte !!!!\n");
                    p_partie->grille_jeu.grille[i*taille +j] = coup;
                }
                else{
                    printf("\nJe joue dans la case %c%d le coup : %d\n", colonne_char, i, coup);
                    joue(i, colonne_char, coup, p_partie);
                    printf("Coup incorrecte :( \n");
                    coup = 1-coup;
                    printf("Je joue alors dans la case %c%d le coup : %d\n", colonne_char, i, coup);
                    printf("Coup correcte !!!!\n");
                    p_partie->grille_jeu.grille[i*taille +j] = coup;
                    }

                affiche_grille_jeu(p_partie->grille_jeu);
                copie_grille(&(p_partie->grille_jeu), &(p_partie->grille_jeu_coup_joue));

                Sleep(1500); 
            }
        
        }

    }
}

int * convertion_tab_binaire(int * tab, int nombre_a_convertir, int taille){

    int tab_envers[taille];

    for(int i = 0; i < taille; i++){
        tab_envers[i] = 0;
    }

    for(int i = 0; nombre_a_convertir > 0; i++)  
    {  
        tab_envers[i] = nombre_a_convertir%2;  
        nombre_a_convertir = nombre_a_convertir/2;

    }
    for(int i = 0; i < taille; i++){
        tab[i] = 0;
    }
    
    for(int i = 0; i < taille; i++){
        tab[i] = tab_envers[taille-i-1];
    }

    return tab;  
        
}

int generation_grille_solution(PARTIE * p_partie){
    int taille = p_partie->taille;
    int test_ligne_valide = 0;
    int test_ligne_colonne_valide = 0;
    int max_nombre_binaire = 0;
    int tableau_ligne[taille];
    int chargement = 0;
    for (int m = 0; m<taille; m++){
        tableau_ligne[m] = -1;
    }

    int tableau[taille*taille];
    for (int m = 0; m<taille*taille; m++){
        tableau[m] = -1;
    }

    GRILLE grille;
    grille.taille = taille;
    grille.grille = tableau;

    int ligne[taille];//tableau binaire du nombre généré aléatoirement
    int nb_binaire;

    // nombre binaire max en fonction de la taille
    if(taille == 4){
        max_nombre_binaire = 15;
    }
    if(taille == 8){
        max_nombre_binaire = 255;
    }
    if(taille == 16){
        max_nombre_binaire = 65536;
    }

    //initialisation de la fonction rand() pour générer de l'aléatoire
    srand(time(NULL));

    int i = 0;
    int impasse = 1;
    int compteur = 0;
    
    //on génère chaque ligne
    while(i<taille){
        

        test_ligne_colonne_valide = 0;

        compteur = 0;
        

        //Tant que la ligne n'est pas valide ou que la la grille n'est pas valide
        while(test_ligne_colonne_valide == 0){

            test_ligne_valide = 0;

            while(test_ligne_valide == 0 ){
                //Génération automatique d'une ligne
                
                nb_binaire = (rand()+rand()+rand())%max_nombre_binaire;
                //printf("nb_binaire: %d", nb_binaire);
                convertion_tab_binaire(ligne, nb_binaire,taille);


                //Teste si la ligne générée respecte les règles du Takazu
                test_ligne_valide = test_ligne(ligne, i, tableau_ligne, nb_binaire, taille);
                //printf("test_ligne_valide : %d\n", test_ligne_valide);
            }



            //Placer la ligne dans la matrice
            for (int j = 0; j<taille; j++){
                grille.grille[i*taille+j] = ligne[j];
            }

            //Teste si la ligne générée permet de respecter les règles aux niveau des colonnes
            int verif_colonne_identique = 0;
            if( i == taille/2 ){
                verif_colonne_identique = 1;
            }
            test_ligne_colonne_valide = test_ligne_colonne(grille, verif_colonne_identique);        

            // Si le compteur dépasse un certain nombre (impasse), on recommence la génération
            compteur++;
            if (compteur > max_nombre_binaire){

                //Barre de chargement
                if(chargement%3 == 0){
                    printf("\rChargement .  ");
                }
                if(chargement%3 == 1){
                    printf("\rChargement .. ");
                }
                if(chargement%3 == 2){
                    printf("\rChargement ...");
                }
                chargement++;

                //On réinitialise la grille avec des -1
                for (int m = 0; m<taille; m++){
                    for (int j = 0; j<taille; j++){
                        grille.grille[m*taille+j] = -1;
                    }
                }
                //On réinitialise le tableau contenant les ligne précédentes en décimal
                for (int k = 0; k<taille; k++){
                    tableau_ligne[k] = -1;
                }
                //On dit qu 'il y a une impasse
                impasse = 0;
                //Pareil pour le compteur
                compteur = 0;
                //on sort de la boucle qui vérifie que les colonnes sont valides
                test_ligne_colonne_valide = 1;

            }  
        }
        
        //Si impasse on reviens on recommence à la ligne 0
        if(impasse == 0){
            i = 0;
            impasse = 1;
        }
        //Si pas d'impasse on a réussi la génération de la ligne
        else{
            //On ajoute le nombre binaire en décimal dans le tableau
            tableau_ligne[i] = nb_binaire; 
            //on passe à la ligne suivante      
            i++;
        }
    
    }
    for(int i = 0; i<taille*taille; i++){
        p_partie->solution.grille[i] = grille.grille[i];
    }
    p_partie->solution.taille = taille;

}

int test_ligne(int * ligne, int num_ligne, int *tableau_ligne, int nb_binaire, int taille){

    //Vérifie que le nombre généré est différent des autres
    for(int i = 0; i<num_ligne; i++){
        if(tableau_ligne[i] == nb_binaire){
            //même ligne qu'une autre
            return 0;
        }
    }
    //Vérifie qu'il n'y pas plus de deux 0 ou deux 1 à la suite
    int max_suite = 2;

    int nb_un_a_la_suite = 0;
    int nb_zero_a_la_suite = 0;
    int case_avant = -1;
    int case_actuelle = -1;
    for (int i = 0; i<taille; i++){
        case_actuelle = ligne[i];
        if (case_actuelle== 0){
            if (case_avant == 0){
                nb_zero_a_la_suite++;
            }
            else{
                nb_zero_a_la_suite = 1;
                nb_un_a_la_suite = 0;
            }
        }
        if (case_actuelle == 1){
            if (case_avant == 1){
                nb_un_a_la_suite++;
            }
            else{
                nb_zero_a_la_suite = 0;
                nb_un_a_la_suite = 1;
            }
        }
        case_avant = case_actuelle;
        
        if (nb_un_a_la_suite > max_suite || nb_zero_a_la_suite > max_suite){
            return 0;
        }
    }

    //Vérifie qu'il y a autant de 1 que de 0
    int nombre_zeros = 0;
    int nombre_uns = 0;
    for (int i = 0; i<taille; i++){
        if(ligne[i] == 0){
            nombre_zeros++;
        }
        else{
            nombre_uns++;
        }
    }
    if (nombre_uns != nombre_zeros){
        return 0;
    }

    return 1;

}

//return 0 si pb
//return 1 si bon
int test_ligne_colonne(GRILLE grille, int verif_colonne_identique){



    //Règle 1 : nombre de 0 ou de 1 à la suite inférieurs ou égal à 2
    int case_avant = 2;
    int case_actuelle = 2;
    int nb_zero_a_la_suite = 0;
    int nb_un_a_la_suite = 0;
    int max_suite = 2;
    for (int j = 0; j<grille.taille; j++){
        case_avant = 2;
        case_actuelle = 2;
        nb_zero_a_la_suite = 0;
        nb_un_a_la_suite = 0;
        for(int i = 0; i<grille.taille; i++){
            case_actuelle = grille.grille[i*grille.taille + j];
            if(case_actuelle == 0){
                if(case_avant == 0){
                    nb_zero_a_la_suite++;
                    nb_un_a_la_suite = 0;
                }
                else{
                    nb_zero_a_la_suite = 1;
                    nb_un_a_la_suite = 0;
                }
            }
            if(case_actuelle == 1){
                if(case_avant == 1){
                    nb_un_a_la_suite++;
                    nb_zero_a_la_suite=0;
                }
                else{
                    nb_un_a_la_suite = 1;
                    nb_zero_a_la_suite = 0;
                }
            }
            if(nb_un_a_la_suite > max_suite || nb_zero_a_la_suite > max_suite){
                return 0;
            }
            case_avant = case_actuelle;
        }
    }

    //Regle 2: Le nombre de 0 et de 1 dans une colonne <= taille/2
    int nb_uns = 0;
    int nb_zeros = 0;
    for (int j = 0; j<grille.taille; j++){
        nb_uns = 0;
        nb_zeros = 0;
        for(int i = 0; i<grille.taille; i++){
            if (grille.grille[i*grille.taille +j] == 0){
                nb_zeros++;
            }
            if (grille.grille[i*grille.taille +j] == 1){
                nb_uns++;
            }
        }
        if(nb_zeros > grille.taille/2 || nb_uns > grille.taille/2){
            return 0;
        }
    }

    if (verif_colonne_identique == 1){
        int colonne_a_comparer[grille.taille]; //colonne qui va tester toutes les autres colonnes
        int colonne_comparante[grille.taille]; //colonne qui stock la colone à comparer
        for(int j = 0; j<grille.taille-1; j++){//colonne à comparer
            for(int i = 0; i<grille.taille; i++){//remplissage de la colonne
                colonne_a_comparer[i] = grille.grille[i*grille.taille + j];
            }
            for(int k = j+1; k<grille.taille; k++){//parcours des collones comparantes
                for(int i = 0; i<grille.taille; i++){//remplissage de la colonne
                    colonne_comparante[i] = grille.grille[i*grille.taille + k];
                }
                int test_meme_val2 = 0;
                for(int a = 0; a<grille.taille; a++){//parcours les cases des deux colonnes à comparer
                    if(colonne_a_comparer[a]==colonne_comparante[a]){
                        test_meme_val2++;
                    }
                }
                if(test_meme_val2==grille.taille){
                    return 0;
                }
            }
        }
    }
    return 1;
}