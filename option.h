/**
 * @file option.h
 * @brief Définition de la fonction de vérification des options.
 * Ce fichier contient la définition de la fonction utilisée pour vérifier et traiter les options spécifiées en ligne de commande.
 */
#include<ctype.h>
#include <stdbool.h>
#include"liste.h"

/**
 * @brief Structure contenant les options spécifiées en ligne de commande.
 */
typedef struct option_g{
    bool c_flag;           /** Afficher le nombre de matchs */
    bool l_flag;           /** Afficher uniquement les noms des fichiers ayant au moins une corespondance */
    bool i_flag;           /** Ignorer les diferences de casse */
    bool A_flag;           /** Afficher après chaque correspondance les n lignes se trouvant aprés la corespondance */
    int arg_A;             /** Nombre de n ligne à afficher apres */
    bool B_flag;           /** Afficher avant chaque correspondance les n lignes se trouvant avant la corespondance */
    int arg_B;             /** Nombre de n ligne à afficher avant */
    bool v_flag;           /** Inverser la mise en corespondance */
    bool n_flag;           /** Prefixer chaque lignes de sortie par son numero dans le fichier */
    bool h_flag;           /** Ne pas afficher le nom des fichiers */
    bool H_flag;           /** Afficher l'aide d'utilisation */
    bool L_flag;           /** Afficher les noms des fichiers ne contennant aucune corespondance */
    bool affiche_ligne;    /** Permet de savoir si on va afficher les lignes correspondance ou pas : vrai si option -c, -L, -l sont specifiés */
    StringList motifs;     /** Permet de stocker les motifs */
    StringList fichiers;   /** Permet de stocker les noms de fichiers */
}option_g;


/**
 * @brief Vérifie et traite les options spécifiées en ligne de commande.
 * @param[in] argv  Le tableau des arguments de la ligne de commande.
 * @param[in] argc  Le nombre d'arguments de la ligne de commande.
 * @param[in] option  Les options traitées et stockées dans la structure option
 * @return 0 si les options sont traitées avec succès, -1 si aucune option n'est trouvée.
 */
int verif_option(char **argv,int argc,option_g *option);
