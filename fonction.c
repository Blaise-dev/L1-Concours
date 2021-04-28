#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include "candidat.h"
#include "fonction.h"

//ici on écri une fonction qui nous permettra d'entrer les differentes informations concernant chaque candidat et pour celà, on prend en paramètre un tableau de candidats ainsi que le nombre de ces derniers
int exist(const unsigned int NCIN_a_rchr ,const char *file_name)
{
    int state = 0;
    char chaine_lecture[MAX_BYTES] = "";
    FILE *f_rchr = NULL;
    candidat candidat_lu;
    f_rchr = fopen(file_name ,"r");
    if(f_rchr == NULL)
    {
        char text[100] = "";
        sprintf(text ,"\n\tImpossible d'ouvrir le fichier : Erreur %d\n" ,errno);
        warning(text);
        exit(0);
    }
    rewind(f_rchr);
    while(fgets(chaine_lecture ,MAX_BYTES ,f_rchr) != NULL)
    {
        candidat_lu = recuperation(chaine_lecture);
        if(candidat_lu.NCIN == NCIN_a_rchr)
            state = 1;
    }
    fclose(f_rchr);
    return state;
}

int is_Already_In(candidat *tab_Cd, int t, int NCIN)
{
    int i = 0;
    while(i<t && tab_Cd[i].NCIN != NCIN)
        i++;
    if(i == t)
        return 0;
    else
        return 1;
}

int saisir()
{
    unsigned int nbr_admis = 0 ,nb_candidats = 1;
    /*
        On fait une allocation dynamique
        Afin d'avoir une taille de tableau égale aux nombre de candidats entré par l'utilisateur
    */
    candidat *TAB = NULL;
    int i = 0;
    char nbr_candidats_char[7] = "100";
    system("CLS");
    do
    {
        printf("Entrez le nombre de candidats > ");
        lire(nbr_candidats_char);
        if(!valid(nbr_candidats_char ,5))
            warning("\n\n\tVeuillez saisir un nombre valide !\n\n");
    }while(!valid(nbr_candidats_char ,5));
    TAB = malloc(sizeof(candidat)*nb_candidats);
    FILE *fichier = NULL;
    fichier=fopen("concours.txt","w");
    //ici on ouvre le fichier crée en utilisant tout simplement la syntaxe approprié le fichier a été crée juste au dessus du commentaire précédent
    for(i=0;i<nb_candidats;i++) //ici on parcours le tableau de candidats pour pouvoir entrer les donner correspondantes pour chacun d'eux ces données sont indiquées dans le bloc suivant
    {
        system("CLS");
        printf("\t\t\tREMPLISSAGE DES DONNEES RELATIVES\n\n ---------------------    AU(X) CANDIDAT(S) DE L'EXAMEN    --------------------\n\n");
        printf("\n\t\tCANDIDAT NUMERO %u\n" ,i+1);
        color(4 ,0);
        printf("\n°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°\n");
        color(7 ,0);
        do
        {
            printf("\tEntrer le Numero de CNI > ");
            securite_NCIN(&TAB[i].NCIN);
            if(is_Already_In(TAB ,i ,TAB[i].NCIN))
            {
                warning("\n\t(Attention !!!! Identifiant unique)\n");
                printf("Vous avez deja saisi ce Numero de CNI\n\n");
            }
        }while(is_Already_In(TAB ,i ,TAB[i].NCIN));
        printf("\tEntrer le Nom > ");
        securite_NP(TAB[i].NOM ,"Nom");
        printf("\tEntrer le Prenom > ");
        securite_NP(TAB[i].PRENOM ,"Prenom");
        printf("\tEntrer l'Age > ");
        securite_AGE(&TAB[i].AGE);
        printf("\tEntrer les Notes > \n");
        //ici on entre les notes des differntes matières puisqu'il  s'agit d'un tableau de 10 notes mais nous avons voulu globalisé en definissant NBR_NOTES dans le tout début de notre code_source ce qui fait qu'en entrant un nombre de notes quelconque on ne pourra remplir que ce nombre là sans toutefois déborder
        for(int j=0; j<NBR_NOTES; j++)
        {
            printf("\t\tEntrer la note %d > " ,j+1);
            securite_NOTE(&TAB[i].NOTES[j] ,j);
        }
        printf("  \tLa MOYENNE est : %2.2f/20\n" ,average(&TAB[i]));
        printf("  \tDECISION : %s\n\n" ,dec_to_varchar(TAB[i].DECISION));
        //ici si le fichier s'est bien ouvert, on aura la possiblité d'ajouter les differentes informations d'un candidat en respectant ce qu'a dit le projet chaque information doit etre séparé de l'autre par le point virgule et pour pouvoir ajouter on a utilisé la fontion fprintf en respectant la syntaxe
        if(TAB[i].DECISION == admis)
            nbr_admis++;
        fprintf(fichier ,"%d;%s;%s;%d;" ,TAB[i].NCIN ,TAB[i].NOM ,TAB[i].PRENOM ,TAB[i].AGE);
        for(int j = 0;j<NBR_NOTES ;j++)
            fprintf(fichier ,"%2.2f;" ,TAB[i].NOTES[j]);
        fprintf(fichier ,"%d\n" ,TAB[i].DECISION);
        if(i != nb_candidats - 1)
            system("pause");
        else
        {
            color(8 ,0);
            printf("\n\tLES %u CANDIDATS ONT ETE ENREGISTRES AVEC SUCCES !\n\n" ,nb_candidats);
            color(7 ,0);
            system("pause");
        }
    }
    fclose(fichier);
    return nbr_admis;
}

int Admis()
{
    system("CLS");
    FILE *fichier1 = NULL;
    FILE *fichier2 = NULL;
    fichier1 = fopen("admis.txt","w");
    candidat cd_recuperation;
    char chaine[MAX_BYTES] = "";
    int nbr_admis = 0;
    if((fichier2 = fopen("concours.txt","r")) == NULL)
    {
        char text[100] = "";
        sprintf(text ,"\n\tImpossible d'ouvrir le fichier : Erreur %d\n" ,errno);
        warning(text);
        exit(0);
    }
    printf("\t\t\t  ECRITURE DES CANDIDATS ADMIS\n\n\t---------------------    DU CONCOURS    --------------------\n\n");
    color(4 ,0);
    printf("\n°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°\n");
    color(7 ,0);
    while(fgets(chaine,MAX_BYTES,fichier2) != NULL)
    {
        cd_recuperation = recuperation(chaine);
        if(cd_recuperation.DECISION == admis)
        {
            nbr_admis++;
            fprintf(fichier1 ,"%u;%s;%s;%d;" ,cd_recuperation.NCIN ,cd_recuperation.NOM ,cd_recuperation.PRENOM ,cd_recuperation.AGE);
            for(int j = 0;j<NBR_NOTES ;j++)
                fprintf(fichier1 ,"%2.2f;" ,cd_recuperation.NOTES[j]);
            fprintf(fichier1 ,"%d\n" ,cd_recuperation.DECISION);
        }
    }
    fclose(fichier2);
    fclose(fichier1);
    color(11 ,0);
    printf("\n\n\t%u CANDIDATS AYANT ETE RETENUS DANS LE CONCOURS\n\n" ,nbr_admis);
    color(7 ,0);
    system("PAUSE");
    return nbr_admis;
}

// Procédure ajouter() ,permettant d'ajouter des donnees relatives à un candidat.

void ajouter()
{
    /*
        On fait une allocation dynamique
        Afin d'avoir une taille de tableau égale aux nombre de candidats entré par l'utilisateur
    */
    char continuer_ajouter[] = "N" ,NCIN_char[10] = "" ,AGE_char[3] = "" ,NOTE_char[3] = "";
    do
    {
        system("CLS");
        candidat cd_ajout;
        FILE *fichier = NULL;
        fichier = fopen("concours.txt" ,"a");
        //ici on ouvre le fichier crée en utilisant tout simplement la syntaxe approprié le fichier a été crée juste au dessus du commentaire précédent
        color(3 ,0);
        printf("\n\t\t\xDB \xDB \xDB \xDB \xDB\xDB \xDB \xDB \xDB \xDB\xDB \xDB \xDB \xDB \xDB\xDB \xDB \xDB \xDB \xDB\xDB \xDB \xDB \xDB \xDB\n\n");
        color(7 ,0);
        printf("________________________________________________________________________________\n\t\tEntrer les donnees relatives du candidat a ajouter\n________________________________________________________________________________\n\n");
        do
        {
            printf("\tEntrer le Numero de CNI > ");
            securite_NCIN(&cd_ajout.NCIN);
            if(exist(cd_ajout.NCIN ,"concours.txt"))
                warning("\n\t(Un candidat possede deja ce Numero de CNI)\n");
        }while(exist(cd_ajout.NCIN ,"concours.txt"));
        printf("\tEntrer le Nom > ");
        securite_NP(cd_ajout.NOM ,"Nom");
        printf("\tEntrer le Prenom > ");
        securite_NP(cd_ajout.PRENOM ,"Prenom");
        printf("\tEntrer l'Age > ");
        securite_AGE(&cd_ajout.AGE);
        printf("\tEntrer les Notes > \n");
        //ici on entre les notes des differntes matières puisqu'il  s'agit d'un tableau de 10 notes mais nous avons voulu globalisé en definissant NBR_NOTES dans le tout début de notre code_source ce qui fait qu'en entrant un nombre de notes quelconque on ne pourra remplir que ce nombre là sans toutefois déborder
        for(int j=0; j<NBR_NOTES; j++)
        {
            printf("\t\tEntrer la note %d > " ,j+1);
            securite_NOTE(&cd_ajout.NOTES[j] ,j);
        }
        printf("  La Moyenne est : %2.2f\n" ,average(&cd_ajout));
        printf("  DECISION : %s\n" ,dec_to_varchar(cd_ajout.DECISION));
        //ici si le fichier s'est bien ouvert, on aura la possiblité d'ajouter les differentes informations d'un candidat en respectant ce qu'a dit le projet chaque information doit etre séparé de l'autre par le point virgule et pour pouvoir ajouter on a utilisé la fontion fprintf en respectant la syntaxe
        fprintf(fichier ,"%d;%s;%s;%d;" ,cd_ajout.NCIN ,cd_ajout.NOM ,cd_ajout.PRENOM ,cd_ajout.AGE);
        for(int j = 0;j<NBR_NOTES ;j++)
            fprintf(fichier ,"%2.2f;" ,cd_ajout.NOTES[j]);
        fprintf(fichier ,"%d\n" ,cd_ajout.DECISION);
        fclose(fichier);
        printf("\n\nVoulez - vous continuer a ajouter ? (O/N) > ");
        securite_choix(continuer_ajouter ,"\n\nVoulez - vous continuer a ajouter?(O/N) > ");
    }while(strcmp(strupr(continuer_ajouter) ,"O") == 0);
}

void modifier()
{
    system("CLS");
    FILE *f_modifier = NULL;
    FILE *f_modifier_admis_tmp = NULL;
    FILE *f_modifier_attente_tmp = NULL;
    FILE *f_lecture = NULL;
    FILE *f_lecture_admis = NULL;
    FILE *f_lecture_attente = NULL;
    unsigned int id = 0;
    char chaine[MAX_BYTES] ,choix[] = "N";
    candidat cd_modifier;
    printf("Entrez le numero de CNI du candidat a modifier > ");
    securite_NCIN(&id);
    system("CLS");
    f_modifier = fopen("concours_new.txt" ,"w");
    f_modifier_admis_tmp = fopen("admis_new.txt" ,"w");
    f_modifier_attente_tmp = fopen("attente_new.txt" ,"w");
    if((f_lecture = fopen("concours.txt" ,"r")) == NULL)
    {
        char text[100] = "";
        sprintf(text ,"\n\tImpossible d'ouvrir le fichier : Erreur %d\n" ,errno);
        warning(text);
        goto cancel;
    }
    if((f_lecture_admis = fopen("admis.txt" ,"r")) == NULL)
    {
        char text[100] = "";
        sprintf(text ,"\n\tImpossible d'ouvrir le fichier : Erreur %d\n" ,errno);
        warning(text);
        goto cancel2;
    }
    if((f_lecture_attente = fopen("attente.txt" ,"r")) == NULL)
    {
        char text[100] = "";
        sprintf(text ,"\n\tImpossible d'ouvrir le fichier : Erreur %d\n" ,errno);
        warning(text);
        goto cancel1;
    }
    printf("\t\t\t  MODIFICATION DES INFORAMATIONS\n\n\t---------------------    D'UN CANDIDAT    --------------------\n\n");
    color(4 ,0);
    printf("\n°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°\n");
    color(7 ,0);
    while(fgets(chaine ,MAX_BYTES ,f_lecture) != NULL)
    {
        cd_modifier = recuperation(chaine);
        // Si le Numero de CNI correspond on modifie selon le choix de l' utilisateur !
        if(cd_modifier.NCIN == id)
        {
            printf("Vous allez modifier les donnees du candidat ");
            color(15 ,0);
            printf("%s %s\n" ,cd_modifier.NOM ,cd_modifier.PRENOM);
            color(3 ,0);
            printf("\nDonnees Actuelles :\n\n");
            printf("\t\t>> Numero de CNI : %u\n" ,cd_modifier.NCIN);
            printf("\t\t>> Nom : %s\n" ,cd_modifier.NOM);
            printf("\t\t>> Prenom : %s\n" ,cd_modifier.PRENOM);
            printf("\t\t>> Age : %d\n" ,cd_modifier.AGE);
            for(int i = 0; i<NBR_NOTES ;i++)
                printf("\t\t>> %de Note : %.2f\n" ,i+1 ,cd_modifier.NOTES[i]);
            color(7 ,0);
            printf("\n\tModifier le 'Numero' de CNI ? (O/N) >\t");
            securite_choix(choix ,"\n\tModifier le 'Numero' de CNI ? (O/N) >\t");
            if(strcmp(strupr(choix) ,"O") == 0)
            {
                printf("\tNOUVEAU NUMERO DE CNI > ");
                securite_NCIN(&cd_modifier.NCIN);
            }
            printf("\tModifier le 'Nom' de %s ? (O/N) >\t" ,cd_modifier.NOM);
            securite_choix(choix ,"\tModifier le 'Nom' de %s ? (O/N) >\t");
            if(strcmp(strupr(choix) ,"O") == 0)
            {
               printf("\tNOUVEAU NOM > ");
               securite_NP(cd_modifier.NOM ,"\tNouveau nom > ");
            }
            printf("\tVoulez - vous editer le 'Prenom' de %s ? (O/N) >\t" ,cd_modifier.NOM);
            securite_choix(choix ,"\tVoulez - vous editer le 'Prenom' de %s ? (O/N) >\t");
            if(strcmp(strupr(choix) ,"O") == 0)
            {
                printf("\tNOUVEAU PRENOM > ");
                securite_NP(cd_modifier.PRENOM ,"\tNouveau prenom > ");
            }
            printf("\tEditer l'Age de %s ? (O/N) >\t",cd_modifier.NOM);
            securite_choix(choix ,"\tEditer l'Age de %s ? (O/N) >\t");
            if(strcmp(strupr(choix) ,"O") == 0)
            {
                printf("\tNOUVEL AGE > ");
                securite_AGE(&cd_modifier.AGE);
            }
            printf("\tVoulez - vous modifier les 'Notes' de %s ? (O/N) >\t" ,cd_modifier.NOM);
            securite_choix(choix ,"\tVoulez - vous modifier les 'Notes' de %s ? (O/N) >\t");
            if(strcmp(strupr(choix) ,"O") == 0)
            {
                //ici on entre les notes des differntes matières puisqu'il  s'agit d'un tableau de 10 notes mais nous avons voulu globalisé en definissant NBR_NOTES dans le tout début de notre code_source ce qui fait qu'en entrant un nombre de notes quelconque on ne pourra remplir que ce nombre là sans toutefois déborder
                for(int j=0; j<NBR_NOTES; j++)
                {
                    printf("\t\tNote de la %de matiere > " ,j+1);
                    securite_NOTE(&cd_modifier.NOTES[j] ,j);
                }
                average(&cd_modifier);
            }
            color(11 ,0);
            printf("\n\n\tMODIFICATION(S) EFFECTUEE(S) AVEC SUCCES !\n\n");
            color(7 ,0);
        }
        fprintf(f_modifier ,"%u;%s;%s;%d;" ,cd_modifier.NCIN ,cd_modifier.NOM ,cd_modifier.PRENOM ,cd_modifier.AGE);
        for(int j = 0;j<NBR_NOTES ;j++)
            fprintf(f_modifier ,"%.2f;" ,cd_modifier.NOTES[j]);
        fprintf(f_modifier ,"%d\n" ,cd_modifier.DECISION);
        if(exist(id ,"admis.txt"))
        {

        }
        while(fgets(chaine ,MAX_BYTES ,f_lecture_admis) != NULL)
        {
            cd_modifier = recuperation(chaine);
        }
    }
    if(!exist(id ,"concours.txt"))
        warning("\n\tNUMERO DE CNI INEXISTANT !\n\n");
    fclose(f_lecture);
    remove("concours.txt");
    fclose(f_lecture_admis);
    remove("admis.txt");
    fclose(f_lecture_attente);
    remove("attente.txt");
    cancel:
        fclose(f_modifier);
        rename("concours_new.txt" ,"concours.txt");
    cancel1:
        fclose(f_modifier_attente_tmp);
        rename("attente_new.txt" ,"attente.txt");
    cancel2:
        fclose(f_modifier_admis_tmp);
        rename("admis_new.txt" ,"admis.txt");
    system("PAUSE");
}

void supprimer(const unsigned int NCIN)
{
    system("CLS");
    FILE *f_supprimer = NULL;
    FILE *f_lecture = NULL;
    char chaine[MAX_BYTES] ,choix[] = "N";
    int candidat_ok = 0 ,candidat_existant = 0;
    candidat cd_supprimer;
    f_supprimer = fopen("concours_new.txt" ,"w");
    if((f_lecture = fopen("concours.txt" ,"r+")) == NULL)
    {
        char text[100] = "";
        sprintf(text ,"Impossible d'ouvrir le fichier : Erreur %d\n" ,errno);
        warning(text);
        goto cancel;
    }
    printf("\t\t\t  SUPPRESSION D'UN CANDIDAT\n\n\t---------------------    DU CONCOURS    --------------------\n\n");
    color(4 ,0);
    printf("\n°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°\n");
    color(7 ,0);
    while(fgets(chaine ,MAX_BYTES ,f_lecture) != NULL)
    {
        cd_supprimer = recuperation(chaine);
        // Si le Numero de CNI correspond on modifie selon le choix de l' utilisateur !
        if(cd_supprimer.NCIN == NCIN)
        {
            candidat_existant = 1;
            printf("Vous allez retirer les donnees du candidat '%s %s' d'identificatif '%u'\n\n\t" ,cd_supprimer.NOM ,cd_supprimer.PRENOM ,cd_supprimer.NCIN);
            warning("(Attention : Vous ne pourrez plus recuperer les donnees de ce candidat une fois supprime!)\n");
            printf("\tConfirmez - vous cette action ? (O/N) >\t");
            securite_choix(choix ,"\tConfirmez - vous cette action ? (O/N) >\t");
            if(strcmp(strupr(choix) ,"O") == 0)
                candidat_ok = 1;
        }
        if((cd_supprimer.NCIN == NCIN && !candidat_ok) || cd_supprimer.NCIN != NCIN)
        {
            fprintf(f_supprimer ,"%u;%s;%s;%d;" ,cd_supprimer.NCIN ,cd_supprimer.NOM ,cd_supprimer.PRENOM ,cd_supprimer.AGE);
            for(int j = 0;j<NBR_NOTES ;j++)
                fprintf(f_supprimer ,"%2.2f;" ,cd_supprimer.NOTES[j]);
            fprintf(f_supprimer ,"%d\n" ,cd_supprimer.DECISION);
        }
    }
    if(candidat_existant && candidat_ok)
    {
        color(11 ,0);
        printf("\n\tSUPPRESSION DU CANDIDAT EFFECTUEE AVEC SUCCES !\n\n");
        color(7 ,0);
    }
    else if(!candidat_existant)
    {
        warning("\n\tIL N'EXISTE AUCUN CANDIDAT DE CE NUMERO CNI!\n\n");
        char text[100] = "" ,vide = 1;
        sprintf(text ,"\nLe candidat au numero de CNI \"%u\" n'existe pas !\n" ,NCIN);
        warning(text);
        printf("\nVoulez - vous consulter l'ensemble des numeros de CNI existants ?(O/N) > ");
        securite_choix(choix ,"\nVoulez - vous consulter l'ensemble des numeros de CNI existants ?(O/N) > ");
        if(strcmp(strupr(choix) ,"O") == 0)
        {
            rewind(f_lecture);
            printf("\n");
            while(fgets(chaine,MAX_BYTES,f_lecture) != NULL)
            {
                vide = 0;
                cd_supprimer = recuperation(chaine);
                printf("[%d]\t" ,cd_supprimer.NCIN);
            }
            if(vide)
                warning("\n\tAucun candidat enregistre !\n\n\t");
        }
        else
            printf("\nD'accord !\n");
    }
    else
        printf("\n\tSUPPRESSION ANNULEE!\n\n");
    fclose(f_lecture);
    remove("concours.txt");
    cancel:
        fclose(f_supprimer);
        rename("concours_new.txt" ,"concours.txt");
}

int valid(char *chaine ,int option)
{
    if(option == 1)
    {
        if(strlen(chaine) > 9)
            return 0;
        int items_in_array = 0;
        char caracteres_autorises[] = "0123456789";
        for(int j = 0; j<9 ;j++)
        {
            for(int k = 0; k<10 ;k++)
            {
                if(chaine[j] == caracteres_autorises[k])
                {
                    items_in_array++;
                    break;
                }
            }
        }
        if(items_in_array == 9)
            return 1;
        else
            return 0;
    }
    else if(option == 2)
    {
        for(int j = 0 ;j<strlen(chaine) ;j++)
        {
            if((chaine[j] < 65 || chaine[j] > 91) && (chaine[j] < 97 || chaine[j] > 123 || strlen(chaine) < 3 || strlen(chaine) > 49))
                return 0;
        }
        return 1;
    }
    else if(option == 3)
    {
        if((atoi(chaine) < 13 || atoi(chaine) > 35))
            return 0;
        else
            return 1;
    }
    else if(option == 4)
    {
        char caracteres_autorises[] = "0123456789.";
        for(int j = 0; j<strlen(chaine) ;j++)
        {
            if(!strrchr(caracteres_autorises ,chaine[j]) || (atof(chaine) < 0 || atof(chaine) > 20))
                return 0;
        }
        return 1;
    }
    else if(option == 5)
    {
        if((atoi(chaine) < 1 || atoi(chaine) > NBR_MAX_CANDIDATS))
            return 0;
        else
            return 1;
    }
}

void securite_choix(char *choix ,char *question)
{
    do
    {
        lire(choix);
        if(strcmp(strupr(choix) ,"O") != 0 && strcmp(strupr(choix) ,"N") != 0)
        {
            warning("\n\n\tEntrez un caractere valide !\n");
            printf("%s" ,question);
        }
    }while(strcmp(strupr(choix) ,"O") != 0 && strcmp(strupr(choix) ,"N") != 0);
}

void securite_NCIN(unsigned int *NCIN)
{
    char NCIN_char[15] = "";
    do
    {
        lire(NCIN_char);
        if(!valid(NCIN_char ,1))
        {
            warning("\n\n\tNumero de CNI Invalide(ne doit contenir que 9 chiffres de 0 a 9) !\n\n");
            printf("\tEntrer le Numero de CNI > ");
        }
    }while(!valid(NCIN_char ,1));
    *NCIN = atoi(NCIN_char);
}

void securite_NP(char *Name ,char *text)
{
    char format_t[100] = "";
    sprintf(format_t ,"\n\tVeuillez saisir un %s valide(Uniquement des lettres ,min 3 lettres et max 49 lettres)\n\n" ,text);
    do
    {
        lire(Name);
        if(!valid(Name ,2) && !valid(Name ,49))
        {
            warning(format_t);
            printf("\tEntrer le %s > " ,text);
        }
    }while(!valid(Name ,2) && !valid(Name ,49));
}

void securite_AGE(int *AGE)
{
    char AGE_char[3] = "";
    do
    {
        lire(AGE_char);
        if(!valid(AGE_char ,3))
        {
            warning("\n\tVeuillez saisir un age valide(Uniquement des chiffres et entre 13 et 35)\n\n");
            printf("\tEntrer l'Age > ");
        }
    }while(!valid(AGE_char ,3));
    *AGE = atoi(AGE_char);
}

void securite_NOTE(float *NOTE ,int indice)
{
    char NOTE_char[3] = "";
    do
    {
        lire(NOTE_char);
        if(!valid(NOTE_char ,4))
        {
            warning("\n\tVeuillez saisir des notes valides\n\n");
            printf("\t\tEntrer la note %d > " ,indice+1);
        }
    }while(!valid(NOTE_char ,4));
    *NOTE = atof(NOTE_char);
}

candidat recuperation(char *ligne)
{
    candidat donnees_candidat;
    unsigned int cpt = 0;
    char *jeton = NULL;
    jeton = strtok(ligne ,";");
    while(jeton != NULL)
    {
        if(cpt == 0)
            donnees_candidat.NCIN = atoi(jeton);
        else if(cpt == 1)
            strcpy(donnees_candidat.NOM ,jeton);
        else if(cpt == 2)
            strcpy(donnees_candidat.PRENOM ,jeton);
        else if(cpt == 3)
            donnees_candidat.AGE = atoi(jeton);
        else if(cpt == 4)
        {
            for(int j = 0; j<NBR_NOTES ;j++)
            {
                donnees_candidat.NOTES[j] = atof(jeton);
                jeton = strtok(NULL ,";");
            }
            donnees_candidat.DECISION = atoi(jeton);
        }
        cpt++;
        jeton = strtok(NULL ,";");
    }
    return donnees_candidat;
}

float average(candidat *cd_modifier)
{
    float moy_candidat = 0.0;
    for(int j=0; j<NBR_NOTES; j++)
        moy_candidat += cd_modifier->NOTES[j]/(float)NBR_NOTES;
    //ici, si le nombre de notes est bien supérieure ou egale à 10, notre variable nbr_notes_gt_10 prend bien evidemment la valeur 10 et dans ce cas si la moyenne est également supérieure ou égale à 10 on dira tout simplement que le candidat en question est admis pour son concours au fure et à mesure on continu aà verifier les autres cas éventuels comme l'a indiqué le projet et à la fin pour rendre le verdict plus claire chez le candidat on affiche sa moyenne
    if(moy_candidat>=10.0 && all_grades_gt_10(cd_modifier->NOTES))
        cd_modifier->DECISION = admis;
    else if(moy_candidat>=10.0 && !all_grades_gt_10(cd_modifier->NOTES))
        cd_modifier->DECISION = ajourne;
    else
        cd_modifier->DECISION = refuse;
    return moy_candidat;
}

int all_grades_gt_10(const float *grades)
{
    unsigned int i = 0;
    for(i = 0 ;i<NBR_NOTES ;i++)
    {
        if(grades[i]<10.0)
            return 0;
    }
    return 1;
}

void viderBuffer()
{
    char c = 0;
    while(c != '\n' && c != EOF)
        c = getchar();
}

void lire(char *tab)
{
    fgets(tab ,200 ,stdin);
    int j = 0;
    while(tab[j] != '\n')
        j++;
    tab[j] = '\0';
}

int attente()
{
    system("CLS");
    FILE *fichier = NULL;
    FILE *fichen = NULL;
    fichier = fopen("attente.txt","w");
    candidat cd_attente;
    int nbr_attente = 0;
    char chaine[MAX_BYTES];
    if((fichen = fopen("admis.txt","r+")) == NULL)
    {
        char text[100] = "";
        sprintf(text ,"\n\tImpossible d'ouvrir le fichier : Erreur %d\n" ,errno);
        warning(text);
        exit(0);
    }
    printf("\t\t\tMISE EN ATTENTE DES CANDIDATS AGES\n\n\t---------------------    DE PLUS DE 20 ANS    --------------------\n\n");
    color(4 ,0);
    printf("\n°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°\n");
    color(7 ,0);
    while(fgets(chaine,MAX_BYTES,fichen) != NULL)
    {
        cd_attente = recuperation(chaine);
        if(cd_attente.AGE>20)
        {
            fprintf(fichier,"%u;%s;%s\n",cd_attente.NCIN,cd_attente.NOM,cd_attente.PRENOM);
            nbr_attente++;
        }
    }
    fclose(fichen);
    fclose(fichier);
    color(11 ,0);
    printf("\n\n\t%u CANDIDATS DONT L'AGE EST SUPERIEURE A 20 ONT ETE MIS EN ATTENTE\n\n" ,nbr_attente);
    color(7 ,0);
    system("PAUSE");
    return 0;
}

float statistiques(decision dec)
{
    float nb_admis = 0., nb_ajourne = 0., nb_refuse = 0.;
    unsigned int nb_candidats = 0;
    char chaine[MAX_BYTES] = "";
    candidat cd_recuperation;
    FILE *fichier = NULL;
    if((fichier = fopen("concours.txt","r")) == NULL)
    {
        char text[100] = "";
        sprintf(text ,"\n\tImpossible d'ouvrir le fichier : Erreur %d\n" ,errno);
        warning(text);
        exit(0);
    }
    while(fgets(chaine,MAX_BYTES,fichier) != NULL)
    {
        cd_recuperation = recuperation(chaine);
        if (cd_recuperation.DECISION == admis)
            nb_admis++;
        else if(cd_recuperation.DECISION == ajourne)
            nb_ajourne++;
        else
            nb_refuse++;
    }
    nb_candidats = nb_admis + nb_ajourne + nb_refuse;
    if(!nb_candidats)
        return 0.0;
    switch(dec)
    {
        case admis:
            return (nb_admis/nb_candidats)*100;
            break;
        case ajourne:
            return (nb_ajourne/nb_candidats)*100;
            break;
        case refuse:
            return (nb_refuse/nb_candidats)*100;
            break;
        default:
            return 0.0;
            break;
    }
}

int Supprimer()
{
    system("CLS");
    FILE *fichier1 = NULL;
    FILE *fichier2 = NULL ;
    fichier2 = fopen("admis_new.txt","w");
    candidat cd_age_supp_20;
    char chaine[MAX_BYTES];
    int nbr_supr = 0;
    if ((fichier1 = fopen("admis.txt","r")) == NULL)
    {
        char text[100] = "";
        sprintf(text ,"\n\tImpossible d'ouvrir le fichier : Erreur %d\n" ,errno);
        warning(text);
        goto cancel;
    }
    printf("\t\t\t    SUPPRESSION DES ADMIS LES\n\n\t---------------------    PLUS DE 20 ANS    --------------------\n\n");
    color(4 ,0);
    printf("\n°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°\n");
    color(7 ,0);
    while(fgets(chaine,MAX_BYTES,fichier1) != NULL)
    {
        cd_age_supp_20 = recuperation(chaine);
        // Si le Numero de CNI correspond on modifie selon le choix de l' utilisateur !
        if(cd_age_supp_20.AGE<=20)
        {
            fprintf(fichier2,"%u;%s;%s;%d;" ,cd_age_supp_20.NCIN ,cd_age_supp_20.NOM ,cd_age_supp_20.PRENOM ,cd_age_supp_20.AGE);
            for(int j = 0;j<NBR_NOTES ;j++)
                fprintf(fichier2 ,"%2.2f;" ,cd_age_supp_20.NOTES[j]);
            fprintf(fichier2 ,"%d\n" ,cd_age_supp_20.DECISION);
        }
        else
            nbr_supr++;
    }
    color(11 ,0);
    printf("\n\n\t%u CANDIDATS AGES DE PLUS DE 20 ANS ONT ETE SUPPRIMES !\n\n" ,nbr_supr);
    color(7 ,0);
    fclose(fichier1);
    remove("admis.txt");
    cancel:
        fclose(fichier2);
        rename("admis_new.txt" ,"admis.txt");
        system("pause");
        return 0;
}

int affiche_merite()
{
    system("CLS");
    FILE *fichier = NULL;
    char chaine[MAX_BYTES] ,ligne_ecrire[50] = "";
    int i = 0 ,j = 0 ,nb_admis = 0 ,r = 0;
    float percent = 0.;
    candidat TAB_admis[MAX_BYTES] ,permut;
    if((fichier = fopen("admis.txt" ,"r")) == NULL)
    {
        char text[100] = "";
        sprintf(text ,"\n\tImpossible d'ouvrir le fichier : Erreur %d\n" ,errno);
        warning(text);
        exit(0);
    }
    printf("\t\t\t    AFFICHAGE DES CANDIDATS PAR\n\n\t---------------------    ORDRE DE MERITE    --------------------\n\n");
    color(4 ,0);
    printf("\n°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°\n");
    color(7 ,0);
    while(fgets(chaine,MAX_BYTES,fichier) != NULL)
    {
        TAB_admis[i] = recuperation(chaine);
        i++;
    }
    nb_admis = i;
    if(nb_admis)
    {
        printf("\nChargement : \n");
        for(i = 0;i<nb_admis-1;i++)
        {
            percent = (i+1)*100/(double)(nb_admis-1);
            gcvt(percent, 3, ligne_ecrire);
            strcat(ligne_ecrire ,"% ");
            for(j = 0; j<percent; j = j + 5 )
                strcat(ligne_ecrire ,"\xDB");
            while(r<102311211)
                r++;
            color(8 ,0);
            printf("\r%s" ,ligne_ecrire);
            color(7 ,0);
            r = 0;
            for(int j = i+1; j<nb_admis; j++)
            {
                if(average(&TAB_admis[i])<average(&TAB_admis[j]))
                {
                    permut = TAB_admis[i];
                    TAB_admis[i] = TAB_admis[j];
                    TAB_admis[j] = permut;
                }
            }
        }
        printf("\n\n\n");
        color(8 ,4);
        color(4 ,4);
        printf("___________________________________________________________________________________________________________________________");
        color(0 ,4);
        printf("\tNUMERO DE CNI\t\tNOM\t\tPRENOM\t        MOYENNE\t\tRANG    ");
        color(4 ,4);
        printf("________________________________________________________________________________________________________________________________________________________");
        color(8 ,4);
        color(7 ,0);
        for(int k=0; k<nb_admis; k++)
        {
            color(7 ,3);
            printf("\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t   %u\t\t%s\t\t%s\t          " ,TAB_admis[k].NCIN,TAB_admis[k].NOM,TAB_admis[k].PRENOM);
            printf("%2.2f\t\t%de\t\t\t\t\t" ,average(&TAB_admis[k]) ,k+1);
            printf("________________________________________________________________________________________________________________________");
            color(1 ,12);
        }
    }
    else
        warning("\t\t(Fichier Vide)\n");
    color(7 ,0);
    printf("\n");
    fclose(fichier);
    system("pause");
    return 0;
}

int recherche(unsigned int NCIN)
{
    system("CLS");
    FILE *fichier = NULL;
    char chaine[MAX_BYTES] = "";
    int candidat_non_trouve = 1;
    candidat cd_recherche;
    unsigned int i = 0;
    if((fichier = fopen("concours.txt" ,"r")) == NULL)
    {
        char text[100] = "";
        sprintf(text ,"\n\tImpossible d'ouvrir le fichier : Erreur %d\n" ,errno);
        warning(text);
        exit(0);
    }
    printf("\t\t\t  RECHERCHE D'UN CANDIDAT \n\n\t---------------------    DU CONCOURS    --------------------\n\n");
    color(4 ,0);
    printf("\n°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°\n");
    color(7 ,0);
    while(fgets(chaine,MAX_BYTES,fichier) != NULL)
    {
        cd_recherche = recuperation(chaine);
        if(cd_recherche.NCIN == NCIN)
        {
            candidat_non_trouve = 0;
            printf("Les donnees du candidat correspondant sont : \n\n");
            color(11 ,0);
            printf("\t\t>> Nom\t\t\t\t%s\n_____________________________________________________________________\n\n" ,cd_recherche.NOM);
            printf("\t\t>> Prenom\t\t\t%s\n_____________________________________________________________________\n\n",cd_recherche.PRENOM);
            printf("\t\t>> Numero de CNI\t\t%u\n_____________________________________________________________________\n\n" ,cd_recherche.NCIN);
            printf("\t\t>> Age\t\t\t\t%u ans\n_____________________________________________________________________\n\n" ,cd_recherche.AGE);
            for(i = 0; i<NBR_NOTES ;i++)
                printf("\t\t>> %de Note\t\t\t%2.2f\n_____________________________________________________________________\n\n" ,i+1,cd_recherche.NOTES[i]);
            printf("\t\t>> Decision\t\t\t%s\n\n" ,dec_to_varchar(cd_recherche.DECISION));
            color(7 ,0);
            break;
        }
    }
    rewind(fichier);
    if(candidat_non_trouve)
    {
        char text[100] = "" ,choix[] = "O" ,vide = 1;
        sprintf(text ,"\nLe candidat au numero de CNI \"%u\" n'existe pas !\n" ,NCIN);
        warning(text);
        printf("\nVoulez - vous consulter l'ensemble des numeros de CNI existants ?(O/N) > ");
        securite_choix(choix ,"\nVoulez - vous consulter l'ensemble des numeros de CNI existants ?(O/N) > ");
        if(strcmp(strupr(choix) ,"O") == 0)
        {
            printf("\n");
            while(fgets(chaine,MAX_BYTES,fichier) != NULL)
            {
                vide = 0;
                cd_recherche = recuperation(chaine);
                printf("[%d]\t" ,cd_recherche.NCIN);
            }
            if(vide)
                printf("\n\tAucun Candidat enregistre !\n");
        }
        else
            printf("\nD'accord !\n");
    }
    fclose(fichier);
    printf("\n\n");
    system("pause");
    return 0;
}

void warning(char *texte)
{
    color(4 ,0);
    printf("%s" ,texte);
    color(7 ,0);
}

char *dec_to_varchar(decision dec)
{
    if(dec == admis)
        return "Admis";
    else if(dec == ajourne)
        return "Ajourne";
    else if(dec == refuse)
        return "Refuse";
    else
        return "None";
}

void color(int t ,int f)
{
    HANDLE H = GetStdHandle(STD_OUTPUT_HANDLE);
        SetConsoleTextAttribute(H ,f*16+t);
}
