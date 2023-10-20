Programme Takuzu - Informations 

Rapport projet Takuzu 
 
Préambubule: 
    Le Takuzu est un jeu de grilles dans l’esprit du Sudoku, mais les chiffres utilisés pour remplir une 
grille sont suniquement le 0 et le 1. 
    Les règles du Takuzu sont extrêmement simples :  
    1. Dans une ligne, il doit y avoir autant de 0 que de 1 
    2. Dans une colonne, il doit y avoir autant de 0 que de 1 
    3. Il ne peut pas y avoir deux lignes identiques dans une grille 
    4. Il ne peut pas y avoir deux colonnes identiques dans une grille 
    5. Dans une ligne ou une colonne, il ne peut y avoir plus de deux 0 ou deux 1 à la suite (on ne peut 
pas avoir trois 0 de suite ou trois 1 de suite) 
 
Implémentation du jeu : 
    1) Choix de la partie : 
        -L'utilisateur a le choix entre 3 tailles de parties : 4*4, 8*8, 16*16 
        -Le programme génère une grille soltion aléatoirement en fonction de la taille choisie (16*16 la 
génération prend plusieurs minutes) 
 
Structure du projet : 
 
-main :  
Description du fichier : 
    Exécution du menu de démarrage et possibilité de décommenter les tests. 
    Le menu de démarrage permet l'exécution du programme de jeu à l'aide de la fonction       
menue_demarrage() 
 
 
-plateau : 
Description du fichier : 
    Toute l'implémentation logique du programme de Takuzu: 
        -implémentation de la structure de Grille et de Partie 
        -Génération d'une partie et d'un masque aléatoire 
        -Vérification des règles du jeu 
        -Résolution automatique d'une grille jeu 
        -Génération automatique d'une grille de jeu 
Liste des fonctions : 
    int creation_grille(int taille, GRILLE * p_grille); 
    int creation_partie(int taille, PARTIE ** p_p_partie); 
    int efface_partie(PARTIE *p_partie); 
    int joue(int ligne, char colonne, int coup, PARTIE * p_partie); 
    int coup_joue_correct(PARTIE partie, int ligne, char colonne, int coup); 
    int coup_sur_cases_non_initiales(int ligne, char colonne, PARTIE * p_partie); 
    int grille_valide(GRILLE grille); 
    int grille_corecte(PARTIE partie); 
    int affiche_grille(GRILLE grille); 
    int copie_grille(GRILLE * p_grille_a_copier, GRILLE * p_grille_receveuse); 
    int generation_grille_jeu(PARTIE * p_partie); 
    int colonne_to_nombre(char colonne); 
    char nombre_to_colonne(int nombre); 
    int affiche_grille_jeu(GRILLE grille); 
    int * convertion_tab_binaire(int * tab, int nombre_a_convertir, int taille); 
    int creation_partie_test(PARTIE ** p_p_partie); 
    int creation_partie_test_grille_solution(PARTIE * p_partie); 
    int saisie_manuelle_masque(PARTIE * p_partie); 
    int generation_automatique_masque(PARTIE * p_partie); 
    int resolution_automatique(PARTIE * p_partie); 
    int generation_grille_solution(PARTIE * p_partie); 
    int test_ligne(int * ligne, int num_ligne, int *tableau_ligne, int nb_binaire, int taille); 
    int test_ligne_colonne(GRILLE grille, int verif_colonne_identique); 
Structure crées : 
    -GRILLE 
    -PARTIE 
 
 
-interface : 
Description du fichier : 
    Toutes fonctions qui gèrent l'interface utilisateur avec les saisies de ce dernier et le déroulement 
d'une partie 


Liste des fonctions :  
    int menue_demarrage(void); 
    int choix_taille(void); 
    int choix_masque(PARTIE * p_partie); 
    int joue_partie(PARTIE * p_partie); 
    int donnee_jeu(int ligne, char colonne, int coup, int taille); 
    int choix_automatique_ou_non(void);

Compilation :
    main.c plateau.c interface.c test.c --> main.exe

Utilisation:
    1) ./main.exe
    2) Suivre les consignes textuelles indiquées dans le terminal.

