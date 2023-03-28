
/**
 *@file fonction.c
 *@brief Fichier contenant les fonctions de recherche de motif
 */

#include<stdio.h>
#include<stdlib.h>
#include<getopt.h>
#include<string.h>
#include"fonction.h"

  
int usage(char *s){
    printf("Usage : %s <-option> motif <fichier1> <fichier2>... \nExécutez «grep --help » pour obtenir des renseignements complémentaires.\n",s);
    exit(EXIT_FAILURE);
}

void err(char *message){
    printf("Erreur: %s\n",message);
}

/*Note
 *size_t pour des valeur positive
 *ssize_t pour valeur positive et negative
 *getline lit et stock l'adresse de la ligne dans la variable ligne
 */

/*
void recup_opt(Option *tab_opt,int argc, char **argv){
    char *optstring="ic";
    int option, j=0,i=0;
    int nb_opt;
    printf("option %d \n",option);
    Option opt= (Option) malloc(sizeof(Option));
    if(opt == NULL){
        err("Allocation dynamique impossible\n");
        exit(-1);
    }
    while((option=getopt(argc,argv,optstring))!=-1){
        nb_opt++;
        printf("option %d \n",option);
        switch(option){
        case 'c' :
            tab_opt[j].opt = 'c';
            tab_opt[j].opt_arg = optarg;
            printf("option c\n");
            break;
        default : printf("exit");
            exit(EXIT_FAILURE);
        }
       j++ 
                }
    for(i=0;i<j;i++){
        printf(" %c nb opt = %d \n",tab_opt[i].opt,nb_opt);
    }
}
*/

void recherche_motif(char *motif, char *fichier){
    FILE *fic = fopen(fichier, "r");
    char *ligne = NULL;
    size_t line_size = 0;
    size_t line_len;
    if (fic == NULL){
        printf("mygrep: %s: Aucun fichier ou dossier de ce type\n",fichier);
        return;
    }
    
    while ((line_len = getline(&ligne, &line_size, fic)) !=-1){
        if(strstr(ligne,motif) != NULL){
            printf("%s: %s",fichier,ligne);
        }
    }
    free(ligne);
    fclose(fic);
}

void recherche_motif_std(char *motif) {
    char ligne[1000];
    while (fgets(ligne, sizeof(ligne), stdin) != NULL) {
        if (strstr(ligne, motif)!= NULL) {
            printf("%s", ligne);
        }
    }
}

void recherche_motif_opt(char *motif, char *fichier){
    FILE *fic = fopen(fichier, "r");
    char *ligne = NULL;
    size_t line_size = 0;
    size_t line_len;
    int nb_ligne=0;
    int num_ligne=1;
    int fic_trouver;
    if (fic == NULL){
        printf("mygrep: %s: Aucun fichier ou dossier de ce type\n",fichier);
        return;
    }
    while ((line_len = getline(&ligne, &line_size, fic)) !=-1){

        //option c
         if(strstr(ligne,motif) != NULL){
           nb_ligne++; 
           }
        
        
        //option -v
        /*if(strstr(ligne,motif) == NULL){ 
          printf("%s",ligne);
          }
        */
        
        //option -n
        /*  if(strstr(ligne,motif) != NULL){
            printf("%d:%s",num_ligne,ligne);
            }
            num_ligne++;
        */
        
        //option -l
        /* if(strstr(ligne,motif) != NULL){
            fic_trouver=1;
            }
            */

        //option -h
        /* if(strstr(ligne,motif) != NULL){
           printf("%s",ligne);
           }
        */
         
    }
    /*  if(fic>0){ //-l
            printf("%s \n",fichier);
            }*/
    printf("%s:%d\n",fichier,nb_ligne); //-c

    free(ligne);
    fclose(fic);
}

