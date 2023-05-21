/**
 * @file recherche.h
 * @brief Definition des fonctions de recherche de motifs.
 *
 * Ce fichier contient les fonctions permettant de rechercher des motifs dans un fichier.
 * Les fonctions fournies ici permettent de lire le fichier ligne par ligne, d'effectuer
 * la recherche des motifs dans chaque ligne, et de compter le nombre de correspondances.
 * Les motifs peuvent être recherchés de manière sensible ou insensible à la casse, en debut, à la fin ou à l'interieur de la ligne, et différentes options de recherche peuvent être spécifiées.
 *
 */

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"fonction.h"

/**
 * @brief Recherche un motif dans une ligne de texte.
 * @param[in] ligne Le texte de la ligne dans lequel effectuer la recherche.
 * @param[in] motifs La liste des motifs à rechercher.
 * @param[in] ignore_case Indique si la recherche doit être insensible à la casse.
 * @return Retourne true si au moins l'un des motifs est trouvé dans la ligne, sinon false.
 */
bool recherche_dans_ligne(char *ligne, StringList *motifs, bool ignore_case);


/**
 * @brief Recherche les motifs dans un fichier spécifié.
 * @param[in] motifs  La liste des motifs à rechercher.
 * @param[in] nom_fichier Le nom du fichier dans le quel effectuer la recherche.
 * @param[in] option  Les options spécifiées pour la recherche.
 */
void recherche_fichier(StringList *motifs,char *nom_fichier,option_g option);


/**
 * @brief Recherche un motif dans un fichier.
 * @param[in] motifs   La liste des motifs à rechercher.
 * @param[in] fichier Le fichier dans lequel effectuer la recherche.
 * @param[in] option  Les options de recherche.
 * @return[in] Le nombre de correspondances trouvées.
 */
int recherche_motif(StringList *motifs, FILE *fichier, option_g option,char * prefixe);