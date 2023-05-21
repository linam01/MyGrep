/**
 * @file fonction.h
 * @brief Definition des fonctions utilitaires pour la traitement des ligne d'un fichier.
 *
 * Ce fichier contient les fonctions utilitaires pour effectuer la recherche de motifs dans une ligne de texte et dans un fichier, en utilisant différentes options de recherche.
 */
#include <stdbool.h>
#include"option.h"


/**
 * @brief Convertit une chaîne de caractères en minuscules.
 * @param[in] str La chaîne de caractères à convertir en minuscules.
 */
void str_to_lower(char *str);

/**
 * @brief Affiche une ligne de texte avec un préfixe, le numéro de ligne et selon les options spécifiées.
 * @param[in] ligne  La ligne de texte à afficher.
 * @param[in] prefixe  Le préfixe à afficher avant la ligne.
 * @param[in] option   Les options spécifiées.
 * @param[in] ligne_num  Le numéro de ligne.
 */
void affiche_ligne(char *ligne, char *prefixe,option_g option, int ligne_num);


