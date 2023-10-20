#ifndef PLATEAU_H
#define PLATEAU_H


#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#ifdef _WIN32
#include <Windows.h>
#else
#include <unistd.h>
#endif



//-------Implémenation des structures--------//

// Création du type GRILLE
typedef struct{
    int taille; //taille de la grille 
    int * grille; // pointeur vers le premier élément de la grille
}GRILLE;



// Création du type PARTIE
typedef struct{
    int vie; //nombre vie
    int taille; //taille de la grille de la partie
    GRILLE solution; //grille solution
    GRILLE masque; //grille masque 
    GRILLE grille_jeu;// grille jeu
    GRILLE grille_jeu_coup_joue; //grille du coup du joueur
}PARTIE;




//-------Allocation en mémoire--------//

// Réserve la mémoire pour l'implémentation du tableau représentant une grille
int creation_grille(int taille, GRILLE * p_grille);

//Réserve la mémoire pour l'ipmplémenation du type partie
int creation_partie(int taille, PARTIE ** p_p_partie);

//fonction qui libère la mémoire pour une partie (libère aussi la mémoire des différentes grilles)
int efface_partie(PARTIE *p_partie);



//-------Modification et vérification des grilles--------//

// Modifie une la grille jeu d'une partie pour y placer le coup
int joue(int ligne, char colonne, int coup, PARTIE * p_partie);

// Vérifie que le coup joué est correcte (est la solution) 
// -Renvoie 1 si coup correcte
// -0 si coup incorrecte
int coup_joue_correct(PARTIE partie, int ligne, char colonne, int coup);

// Vérifie que le coup n'est pas joué sur les cases initiales
// -Renvoie 1 si coup n'est pas joué sur les cases initiales
// -0 sinon
int coup_sur_cases_non_initiales(int ligne, char colonne, PARTIE * p_partie);

// Vérifie que la grille est valide (respecte les règles) 
// -Renvoie 1 si valide
// - -i avec i le numéro de la règle non respectée sinon
int grille_valide(GRILLE grille);

// Vérifie que la grille est correcte (est solution)
// -Renvoie 1 si correcte
// -0 sinon
int grille_corecte(PARTIE partie);




//-------Fonctions auxiliaires et affichage--------//

// Affiche la grille dans le terminal
int affiche_grille(GRILLE grille);

// Copie la grille à copier dans l'espace mémoire de la grille receveuse
int copie_grille(GRILLE * p_grille_a_copier, GRILLE * p_grille_receveuse);

// Génère la grille jeu à l'aide de la grille solution et du masque
int generation_grille_jeu(PARTIE * p_partie);

// Transforme le caractère correspondant à une colonne en nombre
int colonne_to_nombre(char colonne);

// Transforme le numéro de la colonne en son caractère associé
char nombre_to_colonne(int nombre);

// Affiche la grille jeu dans le terminal
int affiche_grille_jeu(GRILLE grille);

//Remplir le tableau d'entier par le nombre en binaire
int * convertion_tab_binaire(int * tab, int nombre_a_convertir, int taille);



//-------Création rapide de parties tests déjà définies--------//

// Création totale d'une partie de test avec implémentation mémoire de tous les composants
int creation_partie_test(PARTIE ** p_p_partie);

// Remplissage d'une grille solution dans une partie déjà implémentée en mémoire
int creation_partie_test_grille_solution(PARTIE * p_partie);



//-------Gestion du masque--------//

// Modifie le masque d'une partie en fonction de la saisie manuelle
int saisie_manuelle_masque(PARTIE * p_partie);

// Génère aléatoire un masque dans une partie (probabilté d'avoir un numéro caché = 62,5/100)
int generation_automatique_masque(PARTIE * p_partie);




//-------Resolution automatique--------//

// Résout automatiquement une partie en affichant les étapes de résolution
int resolution_automatique(PARTIE * p_partie);




//-------Génération automatique d'une grille solution--------//

// Génère et remplie la grille solution de la partie aléatoirement
int generation_grille_solution(PARTIE * p_partie);

// Teste si une ligne respecte les règles du Takuzu
int test_ligne(int * ligne, int num_ligne, int *tableau_ligne, int nb_binaire, int taille);

// Teste si les colonnes déja implémenter respectent les règles du Takuzu
int test_ligne_colonne(GRILLE grille, int verif_colonne_identique);

#endif