#include <stdbool.h>
#include"liste.h"
#define MAX 20


typedef struct option_g{
    bool c_flag;
    bool l_flag;
    bool i_flag;
    bool A_flag;
    int arg_A;
    bool B_flag;
    int arg_B;
    bool v_flag;
    bool n_flag;
    bool h_flag;
    bool H_flag;
    bool L_flag;
    bool affiche_ligne;
    StringList motifs;
    StringList fichiers;
}option_g;


int usage(char *s);
void err(char *message);
void recherche_fichier(StringList *motifs,FILE *fichier,option_g option);
int recherche_motif(StringList *motifs,FILE *fichier,option_g option);




int usage(char *s);
void err(char *message);
void str_to_lower(char *str);
bool recherche_dans_ligne(char *ligne, StringList *motifs, bool ignore_case);
void recherche_fichier(StringList *motifs,FILE *fichier,option_g option);
int recherche_motif(StringList *motifs, FILE *fichier, option_g option);
bool recherche_dans_ligne(char *ligne, StringList *motifs, bool ignore_case);
int verif_option(char **argv,int argc,option_g *option);

