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

typedef struct option_g{
    int c_flag;
    int l_flag;
    int A_flag;
    int v_flag;
    int n_flag;
    int h_flag;
}option_g;

option_g verif_compatibilite(option_g option){
    if(option.c_flag){
        option.n_flag=0;
        option.A_flag=0;
        option.h_flag=0;
    }
    if(option.l_flag){
        option.c_flag=0;
        option.n_flag=0;
        option.A_flag=0;
        option.h_flag=0;
    }  
}
        
int verif_option(char **argv,int argc){
    char *optstring="icvlnA:";
    int opt=getopt(argc,argv,optstring);
    int arg_A;
    if(opt==-1)
        return -1;
    
    while(opt!=EOF){
        switch(opt){
        case 'c' :
            option.c_flag=1;
            break;
        case 'l' :
            option.l_flag=1;
            break;
        case 'A' :
            arg_A= atoi(optarg);
            if ((arg_A == 0 && strcmp(optarg, "0") != 0) || arg_A < 0){
                fprintf(stderr, "mygrep: %s: argument de longueur de contexte incorrect\n",optarg);
                exit(EXIT_FAILURE);
            }
            printf("cc %d\n",arg_A);
            option.A_flag =1;
            break;
        case 'v' :
            option.v_flag=1;
            break;
        case 'n' :
           option.n_flag=1;
            break;
        case 'h' :
            option.h_flag=1;
            break;
        default :
            usage(argv[0]);
            exit(EXIT_FAILURE);
        }
        opt = getopt(argc,argv,optstring);
    }
    return 0;
}

int main(int argc, char **argv){
    char *motif;
    int opt;
    option_g options;
    option={0,0,0,0,0,0};
    opt = verif_option(argv,argc,options);
    verif_compatibilite(options);

    if (optind >= argc) {
        usage(argv[0]);
        exit(EXIT_FAILURE);
    }
    motif=argv[optind]; 
    optind++;             /*argment suivant a traiter = liste de fichiers*/
  
    if (opt==-1 && optind==argc){          /*Pas d'option + pas de fichier -> lecture entré standard*/
        recherche_motif_std(motif);
    }
    else if(opt==-1 && optind<argc){               /*Pas d'option + fichier*/
        while (optind < argc) {
            recherche_motif(motif,argv[optind]);
            optind++;
        }
    }
    else if (opt!=-1 && optind==argc){             /*Option + pas de fichier -> lecture sur entrée standard*/
        printf("recherche stdin\n");               /* -e */
    }
    else{                                          /*Option + fichier */
        while (optind < argc) {
            recherche_motif_opt(motif,argv[optind]);
            optind++;
        }
    }
    
    exit(EXIT_SUCCESS);
}
