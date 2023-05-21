/**
 * @file fonction.c
 * @brief Implementation des fonctions utilitaires pour la traitement des ligne d'un fichier.
 *
 * Ce fichier contient les fonctions utilitaires pour effectuer la recherche de motifs dans une ligne de texte et dans un fichier, en utilisant différentes options de recherche.

 */

#include<stdio.h>
#include<stdlib.h>
#include<getopt.h>
#include<string.h>
#include <ctype.h>
#include"fonction.h"


 /**
 * @brief Convertit une chaîne de caractères en minuscules.
 * @param[in] str La chaîne de caractères à convertir en minuscules.
 */
void str_to_lower(char *str){
    int i;
    // Obtenir la longueur de la chaîne de caractères
    int len_str = strlen(str);
    
    for (i = 0; i < len_str; i++) {
        // Convertir le caractère en minuscule avec la fonction tolower()
        str[i] = tolower(str[i]);
    }
}



/**
 * @brief Affiche une ligne de texte avec un préfixe, le numéro de ligne et selon les options spécifiées.
 * @param[in] ligne  La ligne de texte à afficher.
 * @param[in] prefixe  Le préfixe à afficher avant la ligne.
 * @param[in] option   Les options spécifiées.
 * @param[in] ligne_num  Le numéro de ligne.
 */
void affiche_ligne(char *ligne, char *prefixe,option_g option, int ligne_num){
    // Vérifier si l'affichage de la ligne est activé
    if(option.affiche_ligne==1){
        if(option.fichiers.taille > 1 && !option.h_flag){
            // Si plusieurs fichiers sont traités et -h n'est pas activé, afficher le préfixe.
           printf("%s:",prefixe);
        }
        if(option.n_flag){
             // Si l'option -n est activée, afficher le numéro de ligne 
            printf("%d:",ligne_num);
        }
        // Afficher la ligne de texte
        printf("%s",ligne);           
    }
}