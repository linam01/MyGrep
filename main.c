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
#include<string.h>
#include"recherche.h"


int main(int argc, char **argv){
    int opt, i, j;
    // Structure contenant les options spécifiées en ligne de commande
    option_g options = {false,false,false,false,0,false,0,false,false,false,false,false,false};
    // Vérification des options spécifiées en ligne de commande
    opt = verif_option(argv,argc,&options);

    // Vérifier s'il n'y a pas de fichiers spécifiés 
    if(options.fichiers.taille == 0){
        // Recherche du motif sur l'entrée standard
        recherche_motif(&options.motifs,stdin,options,NULL);
    }else{
        // Parcourir tous les fichiers spécifiés
        for (i = 0; i < options.fichiers.taille; i++) {
            // Effectuer la recherche du motif dans le fichier actuel
            recherche_fichier(&options.motifs,options.fichiers.items[i],options);
        }
    }
    exit(EXIT_SUCCESS);
}
