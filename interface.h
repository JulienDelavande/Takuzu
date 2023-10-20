#ifndef INTERFACE_H
#define INTERFACE_H

#include <stdio.h>
#include <stdlib.h>
#include "plateau.h"

// Génère les menus et gère la gestion du jeu
int menue_demarrage(void);

// Permets au joueur de choisir la taille de sa partie : renvoie cette dernière
int choix_taille(void);

// Permet au joueur de saisir un masque ou de le générer aléatoirement
int choix_masque(PARTIE * p_partie);

// Gère l'interface avec l'utilsateur lorsqu'il joue une partie
int joue_partie(PARTIE * p_partie);

// Vérifie que les données rentrées par l'utilisateur sont valides
// -Renvoie 1 si valide
// -Renvoie 0 sinon avec message d'erreur
int donnee_jeu(int ligne, char colonne, int coup, int taille);

//Choix de la résolution automatique ou non
int choix_automatique_ou_non(void);


#endif