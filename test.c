#include "test.h"

int test_affichage(void){

    PARTIE * p_partie1;

    // reserve la place pour la partie
    creation_partie(4, &p_partie1);

    for (int i = 0; i<p_partie1->taille*p_partie1->taille; i++){
        p_partie1->grille_jeu.grille[i] = 0;
    }
    
    affiche_grille(p_partie1->grille_jeu);

    //désaloue la place pour la partie
    efface_partie(p_partie1);
}

int test_colonne_to_nombre(void){

    printf("%c deviens -> %d (reponse 0)\n", 'a', colonne_to_nombre('a'));
    printf("%c deviens -> %d (reponse 3)\n" , 'd', colonne_to_nombre('d'));
    printf("%c deviens -> %d (reponse 5)\n", 'f', colonne_to_nombre('f'));

    return 1;
}

int test_creation_partie_test(void){

    PARTIE * p_partie = NULL;
    creation_partie_test(&p_partie);
    
    printf("affichage de la grille solution :\n");
    affiche_grille(p_partie->solution);

    printf("affichage de la grille masque :\n");
    affiche_grille(p_partie->masque);

    printf("affichage de la grille jeu :\n");
    affiche_grille(p_partie->grille_jeu);

    printf("affichage de la grille jeu coup joue :\n");
    affiche_grille(p_partie->grille_jeu_coup_joue);

    efface_partie(p_partie);
}

int test_binaire(void){
    int taille = 8;
    int tab[taille];
    convertion_tab_binaire(tab, 25, taille);
    for (int i = 0; i<taille; i++){
        printf("%d ", tab[i]);
    }
    return 1;
}
