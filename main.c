#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include "candidat.h"
#include "fonction.h"

int main()
{
    char choix[10] = "";
    do
    {
        char continuer[10] = "N" ,options_valides[] = "012345678910";
        system("CLS");
        printf("\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB");
        printf("\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB");
        printf("\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB");
        printf("\n\xDB\xDB\t\xDB\xDB\xDB\xDB\xDB\xDB      \xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB");
        printf("\xDB\xDB\n\xDB\xDB\xDB\xDB  \xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB   \xDF  \xDB\xDB\xDB\xDB\xDB\xDB\xDB    1031   \xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB");
        printf("\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\n\xDB\xDB\xDB\xDB  \xDB\xDB\xDB\xDB\xDB");
        printf("\xDB\xDB\xDB  \xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB");
        printf("\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB");
        printf("\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB");
        color(6 ,0);
        printf("\n###############################################################################\n#\t\t\t###\t\t\t\t\t\t      #\n");
        printf("#  EXAMINATEUR\t\t###  DR. TSOPZE.\t\t\t\t      #\n");
        printf("#  SUJET\t\t###  PROGRAMME DE GESTION DE CONCOURS.\t\t      #\n");
        printf("#  BINOME\t\t###  MBASSI ATANGANA BLAISE - 2nd Membre.\t      #\n#\t\t\t###\t\t\t\t\t\t      #\n");
        printf("###############################################################################\n");
        color(7 ,0);
        unsigned int NCIN = 100000000;
        decision dec = admis;
        printf("Choisissez une option (Taper le numero) :\n");
        printf("\n0  -> Saisir\n____________________\n1  -> Ajouter\n____________________\n2  -> Modifier\n____________________\n3  -> Supprimer\n____________________\n4  -> Admis\n____________________\n5  -> Attente\n____________________\n6  -> Statistiques\n____________________\n7  -> Supprimer\n____________________\n8  -> Affiche_merite\n____________________\n9  -> Recherche\n____________________\n10 -> Quitter\n\n");
        do
        {
            printf("Prompt > ");
            lire(choix);
            if(strstr(options_valides ,choix) == 0)
                warning("\n\tEntrer une option valide\n\n");
        }while(strstr(options_valides ,choix) == 0);
        switch(atoi(choix))
        {
            case 0 :
                    saisir();
                    break;
            case 1 :
                    ajouter();
                    break;
            case 2 :
                    modifier();
                    break;
            case 3 :
                    do
                    {
                        system("CLS");
                        printf("\tEntrer le NCIN du candidat a supprimer > ");
                        securite_NCIN(&NCIN);
                        supprimer(NCIN);
                        printf("\nVoulez - vous supprimer un autre candidat ? (O/N) > ");
                        securite_choix(continuer ,"\nVoulez - vous supprimer un autre candidat ? (O/N) > ");
                    }while(strcmp(strupr(continuer) ,"O") == 0);
                    break;
            case 4 :
                    Admis();
                    break;
            case 5 :
                    attente();
                    break;
            case 6 :
                    // L' entete du programme
                    system("CLS");
                    printf("\t\t\t\t  STATISTIQUES\n\n\t   ---------------------    CONCOURS    --------------------\n\n");
                    color(4 ,0);
                    printf("\n같같같같같같같같같같같같같같같같같같같같같같같같같같같같같같같같같같같같같같같같\n");
                    color(7 ,0);
                    // Affichage des Pourcentages
                    printf("\n   같같같같같같같같같    Le pourcentage des admis : %3.2f%%     같같같같같같같같같\n\n" ,statistiques(dec));
                    dec = ajourne;
                    printf("   같같같같같같같같같   Le pourcentage des ajournes : %3.2f%%   같같같같같같같같같\n\n" ,statistiques(dec));
                    dec = refuse;
                    printf("   같같같같같같같같같  Le pourcentage des refuses est : %3.2f%%  같같같같같같같같�\n\n" ,statistiques(dec));
                    statistiques(dec);
                    system("PAUSE");
                    break;
            case 7 :
                    Supprimer();
                    break;
            case 8 :
                    affiche_merite();
                    break;
            case 9:
                    do
                    {
                        system("CLS");
                        printf("Entrer le Numero de CNI du Candidat a rechercher > ");
                        securite_NCIN(&NCIN);
                        recherche(NCIN);
                        viderBuffer();
                        printf("\n\nVoulez - vous faire la recherche de nouveau ? (O/N) > ");
                        securite_choix(continuer ,"\n\nVoulez - vous faire la recherche de nouveau ? (O/N) > ");
                    }while(strcmp(strupr(continuer) ,"O") == 0);
                    break;
            case 10:
                break;
            default:
                    warning("\n\tPas de choix correspondant !!!\n\n");
                    system("pause");
                    break;
        }
    }while(atoi(choix) != 10);
    return 0;
}
