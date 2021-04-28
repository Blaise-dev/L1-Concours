#ifndef FONCTION_H_INCLUDED
#define FONCTION_H_INCLUDED

int saisir();
void ajouter();
int Admis();
void modifier();
void supprimer(const unsigned int NCIN);
int attente();
void securite_NCIN(unsigned int *NCIN);
void securite_NP(char *Name ,char *text);
void securite_AGE(int *AGE);
void securite_NOTE(float *NOTE ,int indice);
void securite_choix(char *choix ,char *question);
float statistiques(decision dec);
candidat recuperation(char *ligne);
int valid(char *chaine ,int option);
int exist(const unsigned int NCIN_a_rchr ,const char *file_name);
int is_Already_In(candidat *tab_Cd, int t, int NCIN);
void warning(char *texte);
float average(candidat *edit_cd);
int all_grades_gt_10(const float *grades);
char *dec_to_varchar(decision dec);
void lire(char *tab);
void viderBuffer();
int Supprimer();
int affiche_merite();
int recherche(unsigned int NCIN);
void color(int t ,int f);

#endif
