/**
 * @file option.c
 * @brief Implémentation de la fonction de vérification des options.
 * Ce fichier contient l'implémentation de la fonction utilisée pour vérifier et charger les options spécifiées en ligne de commande dans la structure option_g.
 * @date 2023
 */

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<getopt.h>
#include"option.h"
#include"utilitaire.h"

/**
 * @brief Vérifie et traite les options spécifiées en ligne de commande.
 * @param[in] argv  Le tableau des arguments de la ligne de commande.
 * @param[in] argc  Le nombre d'arguments de la ligne de commande.
 * @param[in] option  Les options traitées et stockées dans la structure option_g
 * @return 0 si les options sont traitées avec succès, -1 si aucune option n'est trouvée.
 */
int verif_option(char **argv,int argc,option_g *option){
    int i=0;
    char *optstring="e:icvhLHlnA:B:";
    int opt= -1;
    int arg_AB;
    int num=0;
    int Lprio =0; // permet de savoir quelle L est pioritaire (normalment le dernier trouver
    option->motifs.taille=0;
    option->motifs.items=NULL;
    option->arg_A =0;
    option->arg_B =0; 

    // Parcours des options spécifiées en ligne de commande
    while((opt = getopt(argc,argv,optstring))!= -1){
        switch(opt){
        case 'i': option->i_flag =true;
            break;
        case 'L':
            option->L_flag= true;
            option->l_flag= false;
            break;
        case 'H':
            option->H_flag =true;
            aide_utilisation(argv[0]);
            break;
        case 'e':
            // Ajout du motif à la liste des motifs
            push_string(&option->motifs,optarg);
            break;
        case 'c' :
            option->c_flag=true;
            break;
        case 'l' :
            option->l_flag=true;
            option->L_flag= false;
            break;
        case 'A' :
        case 'B':
            // Vérification et conversion de l'argument en entier
            if(strlen(optarg) > 1){
                for(i=0;i<strlen(optarg);i++){
                    if(optarg[i] != '1' && optarg[i] != '2' && optarg[i] != '3' && optarg[i] != '4' && optarg[i] != '5' && optarg[i] != '6' && optarg[i] != '7' && optarg[i] != '8' && optarg[i] != '9' && optarg[i] != '0'){
                        fprintf(stderr, "mygrep: %s: argument de longueur de contexte incorrect\n",optarg);
                        exit(-1);
                        
                    }
                }
            }
            arg_AB = atoi(optarg);
            if ((arg_AB == 0 && strcmp(optarg, "0") != 0) || arg_AB < 0){
                fprintf(stderr, "mygrep: %s: argument de longueur de contexte incorrect\n",optarg);
                exit(EXIT_FAILURE);
            }
            // Attribution de l'argument à l'option correspondante
            if(opt == 'A'){
                option->arg_A = arg_AB;
                option->A_flag= true;
            }
            else if(opt == 'B'){
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
            //Affiche l'aide d'utilisation en cas de mauvais parametres.
            aide_utilisation(argv[0]);

            exit(EXIT_FAILURE);
        }
    }
    
    // Détermination de l'option d'affichage de ligne
    option->affiche_ligne = !option->L_flag && !option->l_flag && !option->c_flag;
    for (i = optind; i < argc; i++) {
        if(option->motifs.taille < 1){
            // Si la taille de la liste des motifs est inférieure à 1, ajoute l'argument à la liste des motifs
            push_string(&(option->motifs), argv[i]);
        }else{
            // Sinon, ajoute l'argument à la liste des fichiers
            push_string(&(option->fichiers), argv[i]);
        }
    }
    return 0;
}