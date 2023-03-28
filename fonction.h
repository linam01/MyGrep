#define MAX 20
/*
typedef struct Option{
    char opt;
    char arg_opt;
}Option;
*/

typedef struct Correspondance{
    int num_ligne;
    char *ligne;
    char *fichier;
}Correspondance;


int usage(char *s);
void err(char *message);
void recherche_motif(char *motif, char *fichier);
void recherche_motif_std(char *motif);
//void recup_opt(Option *tab_opt,int argc, char **argv);
void recherche_motif_opt(char *motif, char *fichier);
