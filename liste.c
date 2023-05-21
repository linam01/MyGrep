#include<stdio.h>
#include<stdlib.h>
#include"liste.h"

/**
 * @brief Ajoute une chaîne de caractères à la liste.
 * @param[in] liste La liste dans laquelle ajouter la chaîne.
 * @param[in]  chaine La chaîne de caractères à ajouter.
 */
void push_string(StringList *liste, char *chaine){
    if(liste == NULL || chaine == NULL) {
        return;
    }
    liste->taille++;
    liste->items = realloc(liste->items,liste->taille * sizeof(char *));
    liste->items[liste->taille - 1] = chaine;
}

/**
 * @brief Vide la liste sans libérer la mémoire utilisée par les chaînes de caractères.
 * @param[in] liste La liste à vider.
 */
void vider_liste(StringList *liste){
    int i;
    if (liste == NULL) {
        return;
    }
    for(i = 0; i < liste->taille; i++){
        if (liste->items[i] != NULL) {
            free(liste->items[i]);
            liste->items[i] = NULL;
        }
    }
    liste->taille = 0;
}

/**
 * @brief Affiche le contenu de la liste.
 * @param[in] liste La liste à afficher.
 */
void afficher_liste(StringList* liste) {
    int i;
    for(i = 0; i < liste->taille; i++){
        printf("%s\n", liste->items[i]);
    }
}


/**
 * @brief Libère la mémoire utilisée par la liste et ses chaînes de caractères.
 * @param[in,out] liste La liste de chaînes de caractères a libérer.
 */
void free_list(StringList *liste){
    vider_liste(liste);
    free(liste->items);
    liste->items = NULL;
    free(liste);
    liste = NULL;
}


/**
 * @brief Supprime une ligne spécifique d'une liste de chaînes de caractères.
 * @param[in,out] liste La liste de chaînes de caractères.
 * @param[in] index L'index de la ligne à supprimer.
 */
void supprime_ligne(StringList *liste, int index){
    int i;
    if(index < 0 || index >= liste->taille){
        return;
    }
    free(liste->items[index]);
    liste->items[index] = NULL;
    for(i = index ; i < liste->taille -1; i++){
        liste->items[i] = liste->items[i+1];
    }
    liste->taille--;
}