typedef struct StringList {
    int taille;
    char **items;
} StringList;

void push_string(StringList *liste, char *chaine);
void clear_list(StringList *liste);
void free_list(StringList *liste);
void supprime_ligne(StringList *liste, int index);
void vider_liste(StringList *liste);
void afficher_liste(StringList* liste);
