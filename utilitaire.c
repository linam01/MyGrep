/**
 * @file utilitaire.c
 * @brief Implémentation des fonctions utilitaires.
 * @date 2023
 */

#include"utilitaire.h"

/**
 * @brief Affiche un message d'utilisation et termine le programme.
 * @param[in] s Le nom du programme.
 */
void aide_utilisation(char *s){
    printf("Utilisation : %s [OPTION]... MOTIF [FICHIER]...\n",s);
    printf("Rechercher un MOTIF dans chaque FICHIER \n");
    printf("Exemple: mygrep -i 'hello word' menu.h main.c\n\n");
    printf("Sélection et interprétation des motifs : \n");
    printf("   -e,     utiliser MOTIF comme expression rationnelle\n");
    printf("   -i,     ignorer la distinction de la casse\n");
    printf("\n");
    printf("Divers\n");
    printf("   -v,     sélectionner les lignes sans correspondance\n");
    printf("\n");
    printf("Contrôle de la sortie :\n");
    printf("   -n,      afficher le numéro de ligne avec la sortie\n");
    printf("   -H,      afficher l'aide d'utilisation \n");
    printf("   -h,      supprimer le préfixe de nom de fichier en sortie\n");
    printf("   -L,      n'afficher que les fichiers sans lignes sélectionnées\n");
    printf("   -l,      n'afficher que les fichiers avec des lignes sélectionnées\n");
    printf("   -c,      n'afficher que le nombre de lignes sélectionnées par FICHIER\n");
    printf("\n");
    printf("Contrôle de contexte :\n");
    printf("   -B,      afficher NBRE lignes de contexte avant\n");
    printf("   -A,      afficher NBRE lignes de contexte après\n");
    printf("\n\nSi le caractère '^' est specifier au debut du motif alors le motif est rechercher en debut de ligne.\nSi le caractère '$' est specifiés en fin de motif alors le motif est rechercher en fin de ligne.\nSinon si les deux sont specifiés alors chercher les lignes qui contiennnent uniquement le motif. \n");
    printf("Si aucun fichier n'est specifiés alors la lecture se fait sur l'entrée standard\n");
   
    exit(-1);
}

        

    










    
