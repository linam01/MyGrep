/**
 *@file fonction.c
 *@brief Fichier contenant les fonctions de recherche de motif
 */
#include<stdio.h>
#include<stdlib.h>
#include<getopt.h>
#include<string.h>
#include <ctype.h>
#include"fonction.h"


  
int usage(char *s){
    printf("Usage : %s <-option> motif <fichier1> <fichier2>... \nExécutez «grep --help » pour obtenir des renseignements complémentaires.\n",s);
    exit(EXIT_FAILURE);
}

void err(char *message){
    printf("Erreur: %s\n",message);
}


void str_to_lower(char *str){
    int i;
    int len_str = strlen(str);
    for (i = 0; i < len_str; i++) {
        str[i] = tolower(str[i]);
    }
}

bool recherche_dans_ligne(char *ligne, StringList *motifs, bool ignore_case) {
    char *motif, *new_motif, *new_ligne;
    int len_motif, len_ligne = strlen(ligne);
    int i;

    if (motifs == NULL || motifs->taille == 0) {
        return false;
    }
        motif = motifs->items[0];

    if (motif == NULL) {
        return false;
    }
    new_motif = strdup(motif);
    new_ligne = strdup(ligne);
    len_motif = strlen(new_motif);
    len_ligne = strlen(new_ligne);
    // Convertir  en minuscules si l'option -i est activée
    if(ignore_case == true){
        str_to_lower(new_motif);
        str_to_lower(new_ligne);
    }
   
    if (strlen(new_motif)  > 0 ) {
        if (new_motif[0] == '^') { // chercher le motif en début de ligne
            if (strncmp(new_ligne, &new_motif[1], len_motif - 1) == 0) {
                //   printf("motif présent en début de ligne");
                return true;
            }
        }
        else if ( len_ligne >= len_motif && new_motif[len_motif - 1] == '$') { // chercher le motif en fin de ligne
            if (strncmp(&new_ligne[len_ligne - len_motif], new_motif, len_motif - 1) == 0) {
                //  printf("motif présent en fin de ligne");
                return true;
            }
        }
        else { // chercher le motif dans la ligne entière
            if (strstr(new_ligne, new_motif) != NULL) {
                //   printf("motif présent dans la ligne\n");
                return true;
            }
        }
    }
    
    return false;
}

void recherche_fichier(StringList *motifs,FILE *fichier,option_g option){
    if (fichier == NULL){
        printf("mygrep: Aucun fichier ou dossier de ce type\n");
    }
 
    recherche_motif(motifs,fichier,option);
    fclose(fichier);

}

int recherche_motif(StringList *motifs, FILE *fichier, option_g option){
    char *ligne = NULL;
    char *nouvelle_ligne;
    size_t line_size = 0;
    size_t line_len;
    bool match = false;
    int nb_match=0,i;
    int option_A;
    StringList liste_B;
    
    liste_B.taille = 0;
    liste_B.items = malloc(sizeof(char*) * option.arg_B);
    
   while ((line_len = getline(&ligne, &line_size, fichier)) != -1) {
        match = recherche_dans_ligne(ligne, motifs, option.i_flag);
       if ((!option.v_flag && match) || (option.v_flag && !match)) {
            nb_match++;
            if (option.arg_B > 0) {
                for (i = 0; i < liste_B.taille; i++) {
                    printf("%s", liste_B.items[i]);
                }
                printf("%s", ligne);
                vider_liste(&liste_B);
            }
        } else if (!match && option.arg_B > 0 && option.B_flag) {
            if (liste_B.taille >= option.arg_B) {
                supprime_ligne(&liste_B, 0);
            }
            nouvelle_ligne = malloc(line_len + 1); // Allouer de la mémoire pour la ligne
             strcpy(nouvelle_ligne, ligne); // Copier la ligne dans la mémoire allouée
            push_string(&liste_B, nouvelle_ligne);
        }
        if(option.A_flag && match) {
            option_A = option.arg_A;
            printf("%s", ligne);
        } else if (option_A > 0 && option.A_flag ) {
            option_A--;
            printf("%s", ligne);
        }
        if(match && !option.A_flag && !option.B_flag){
            printf("%s",ligne);
        }
   }
   
   free(ligne);
   return nb_match;
}


int verif_option(char **argv,int argc,option_g *option){
    int i;
    char *optstring="e:icvhLHlnA:B:";
    int opt=getopt(argc,argv,optstring);
    int arg_AB;
    option->motifs.taille=0;
    option->motifs.items=NULL;
    option->arg_A =0;
    option->arg_B =0;
    if(opt==-1)
        return -1;
    
    while(opt!=EOF){
        switch(opt){
        case 'L':
            option->L_flag= true;
            break;
        case 'H':
            option->H_flag =true;
            break;
        case 'e':
            push_string(&option->motifs,optarg);
            break;
        case 'c' :
            option->c_flag=true;
            break;
        case 'l' :
            option->l_flag=true;
            break;
        case 'A' :
        case 'B':
            arg_AB = atoi(optarg);
            if ((arg_AB == 0 && strcmp(optarg, "0") != 0) || arg_AB < 0){
                fprintf(stderr, "mygrep: %s: argument de longueur de contexte incorrect\n",optarg);
                exit(EXIT_FAILURE);
            }
            if(opt == 'A'){
                option->arg_A = arg_AB;
                option->A_flag= true;
            }
            else{
                option->arg_B = arg_AB;
                option->B_flag= true;
            }
            break;            
        case 'v' :
            option->v_flag=true;
            break;
        case 'n' :
            option->n_flag=true;
            break;
        case 'h' :
            option->h_flag=true;
            break;
        default :
            usage(argv[0]);
            exit(EXIT_FAILURE);
        }
        opt = getopt(argc,argv,optstring);
    }
    if(!option->L_flag && !option->l_flag && !option->c_flag){
        option->affiche_ligne= true;
    }else{
        option->affiche_ligne= false;
    }   
    for (i = optind; i < argc; i++) {
        push_string(&(option->fichiers), argv[i]);
    }
    return 0;
}