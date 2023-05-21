/**
 * @file recherche.c
 * @brief Implementation des fonctions de recherche de motifs dans un ou plusieurs fichier et sur l'entrée standard
 *
 * Ce fichier contient les fonctions permettant de rechercher des motifs dans un fichier.
 * Les fonctions fournies ici permettent de lire le fichier ligne par ligne, d'effectuer
 * la recherche des motifs dans chaque ligne, et de compter le nombre de correspondances.
 * Les motifs peuvent être recherchés de manière sensible ou insensible à la casse, en debut, à la fin ou à l'interieur de la ligne, et différentes options de recherche peuvent être spécifiées.
 *
 */

#include"recherche.h"

/**
 * @brief Recherche un motif dans une ligne de texte.
 * @param[in] ligne Le texte de la ligne dans lequel effectuer la recherche.
 * @param[in] motifs La liste des motifs à rechercher.
 * @param[in] ignore_case Indique si la recherche doit être insensible à la casse.
 * @return Retourne true si au moins l'un des motifs est trouvé dans la ligne, sinon false.
 */
bool recherche_dans_ligne(char *ligne, StringList *motifs, bool ignore_case) {
    char *motif, *new_motif, *new_ligne;
    int len_motif, len_ligne = strlen(ligne);
    int i;
    // Vérifier si la liste de motifs est vide
    if (motifs == NULL || motifs->taille == 0) {
        return false;
    }
    
    // Récupérer le motif de la liste 
    for (i = 0; i < motifs->taille; i++) {
        motif = motifs->items[i];
        // Vérifier si le motif est NULL
        if (motif == NULL) {
            continue;
        }   
        // Copier les motifs et la ligne dans de nouvelles variables
        new_motif = strdup(motif);
        new_ligne = strdup(ligne);
        // Obtenir les longueurs du motif et de la ligne
        len_motif = strlen(new_motif);
        len_ligne = strlen(new_ligne);
        // Convertir en minuscules si l'option -i est activée
        if(ignore_case == true){
            str_to_lower(new_motif);
            str_to_lower(new_ligne);
        }
        
        if(strlen(new_motif)  > 0 ) {                      
            if (new_motif[0] == '^' && new_motif[len_motif - 1] == '$'){
                new_motif[len_motif - 1] = '\0';     //supression du carcatere '$'        
                // Rechercher la ligne qui contient uniquement le motif
                if (len_ligne == len_motif - 1 && strncmp(&new_ligne[0], &new_motif[1], len_ligne-1) == 0) {
                    return true;
                }
            }
            else if (new_motif[0] == '^') { // chercher le motif en début de ligne
                if (strncmp(new_ligne, &new_motif[1], len_motif - 1) == 0) {
                        //   printf("motif présent en début de ligne");
                    return true;
                }
                }
            else if( len_ligne >= len_motif && new_motif[len_motif - 1] == '$'){ // chercher le motif en fin de ligne
                if (strncmp(&new_ligne[len_ligne - len_motif], new_motif, len_motif - 1) == 0) {
                    //  printf("motif présent en fin de ligne");
                    return true;
                }
            }
            else { // chercher le motif dans la ligne 
                if (strstr(new_ligne, new_motif) != NULL) {
                    //   printf("motif présent dans la ligne\n");
                    return true;
                }
            }
            
            free(new_motif);
        }
    }
    
    free(new_ligne);
    return false; //Aucun motif trouvé dans la ligne
}

/**
 * @brief Recherche les motifs dans un fichier spécifié.
 * @param[in] motifs  La liste des motifs à rechercher.
 * @param[in] nom_fichier Le nom du fichier dans le quel effectuer la recherche.
 * @param[in] option  Les options spécifiées pour la recherche.
 */
void recherche_fichier(StringList *motifs,char *nom_fichier,option_g option){
    int matchs = 0;
    FILE *fichier = fopen(nom_fichier,"r");
    if (fichier == NULL){
        printf("mygrep %s : Aucun fichier ou dossier de ce type\n",nom_fichier);
        return;
    }
    //Effectuer la recherche des motifs dans le fichier et recuperer le nombre de matchs
    matchs = recherche_motif(motifs,fichier,option,nom_fichier);
    fclose(fichier);
    
    //Afficher les résultats en fonction des options spécifiées
    if(!option.affiche_ligne){
        if(option.L_flag) {
            if (matchs ==0) { //Afficher le nom du fichier s'il contient au moins un motif
                printf("%s\n", nom_fichier);
            }       
        }else if (option.l_flag) {
            if (matchs >= 1) { // Afficher le nom du fichier s'il ne contient aucun motif
                printf("%s\n ",nom_fichier); 
            }
        }else if(option.c_flag && option.fichiers.taille > 1 && !option.h_flag){
            printf("%s:%d\n",nom_fichier,matchs); // Afficher le nombre de matchs avec le nom du fichier si il y a plusieurs fichiers et que l'option -h n'est pas activé.
        }else
            printf("%d\n",matchs); //Afficher le nombre de matchs uniquement.
    }   
}
    

/**
 * @brief Recherche un motif dans un fichier.
 * @param[in] motifs  La liste des motifs à rechercher.
 * @param[in] fichier Le fichier dans lequel effectuer la recherche.
 * @param[in] option Les options de recherche.
 * @return[in] Le nombre de correspondances trouvées.
 */
int recherche_motif(StringList *motifs, FILE *fichier, option_g option, char * prefixe){
    char *ligne = NULL;
    char *nouvelle_ligne;
    size_t line_size = 0;
    size_t line_len;
    bool match = false;
    int nb_match=0,i;
    int option_A=0;
    StringList liste_B;
    int ligne_num = 1;
    
    // Initialiser la liste des lignes pour l'option -B
    liste_B.taille = 0;
    liste_B.items = malloc(sizeof(char*) * option.arg_B);

    //Parcourir les lignes d'un fichier
    while ((line_len = getline(&ligne, &line_size, fichier)) != -1) {
        //Renvoie true si il y a un match, false sinon
        match = recherche_dans_ligne(ligne, motifs, option.i_flag);
        if ((!option.v_flag && match) || (option.v_flag && !match)) {
            nb_match++; //Incrementer le nombre de match
            if (option.arg_B > 0) {
                for (i = 0; i < liste_B.taille; i++) {
                    // Afficher la ligne correspondante
                     affiche_ligne(liste_B.items[i],prefixe,option,ligne_num);
                }
                vider_liste(&liste_B);
            }
            option_A= option.arg_A;
             affiche_ligne(ligne,prefixe,option,ligne_num);
        }          
        else{
            if(option_A > 0){
                option_A --;
                // Afficher la ligne correspondante
                 affiche_ligne(ligne,prefixe,option,ligne_num);
            }
            else if(option.arg_B > 0){
                if (liste_B.taille >= option.arg_B) {
                    supprime_ligne(&liste_B, 0);
                }
                nouvelle_ligne = malloc(line_len + 1); // Allouer de la mémoire pour la ligne
                strcpy(nouvelle_ligne, ligne); // Copier la ligne dans la mémoire allouée
                push_string(&liste_B, nouvelle_ligne); //Ajouter une nouvelle ligne à la liste
            }
        }
        
        ligne_num++; //Incrmenter le numero de la ligne        
    }
    //liberation de la memoire
    free(liste_B.items); 
    free(ligne);
    return nb_match;
}


            