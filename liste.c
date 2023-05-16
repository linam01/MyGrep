#include"liste.h"
#include<stdio.h>
#include<stdlib.h>

void push_string(StringList *liste, char *chaine) {
    if (liste == NULL || chaine == NULL) {
        return;
    }
    liste->taille++;
    liste->items = realloc(liste->items,liste->taille * sizeof(char *));
    liste->items[liste->taille - 1] = chaine;
}


void vider_liste(StringList *liste) {
    if (liste == NULL) {
        return;
    }
    for (int i = 0; i < liste->taille; i++) {
        if (liste->items[i] != NULL) {
            free(liste->items[i]);
            liste->items[i] = NULL;
        }
    }
    liste->taille = 0;
}


void afficher_liste(StringList* liste) {
    for (int i = 0; i < liste->taille; i++) {
        printf("%s\n", liste->items[i]);
    }
}

void free_list(StringList *liste) {
    vider_liste(liste);
    free(liste->items);
    liste->items = NULL;
    free(liste);
    liste = NULL;
}



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