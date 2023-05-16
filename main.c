/**
 *@file main.c
 *@brief Fichier principal du programme MyGrep
 *Ce programme cherche un motif dans un ou plusieurs fichiers ou sur l'entrée standard 
 *et affiche les corespondances sur l'entrée standard.
 *@date 2023
 *@author Lina Merazga
 */

#include<stdio.h>
#include<stdlib.h>
#include<getopt.h>
#include<string.h>
#include"fonction.h"
#include <stdbool.h>


int main(int argc, char **argv){
    int opt, i, j;
    FILE *fichier;    
    option_g options = {false,false,false,false,0,false,0,false,false,false,false,false,false};

    opt = verif_option(argv,argc,&options);
    afficher_liste(&options.motifs);
    afficher_liste(&options.fichiers);


    if(options.fichiers.taille == 0){      //si pas de fichier : lecture sur entré standard
        recherche_fichier(&options.motifs,stdin,options);
    }else{
        for (i = 0; i < options.fichiers.taille; i++) {
            fichier = fopen(options.fichiers.items[i], "r");
           for (j = 0; j < options.motifs.taille; j++) {
            recherche_fichier(&options.motifs,fichier,options);
           }
        }
    }
        
        
    exit(EXIT_SUCCESS);
}
