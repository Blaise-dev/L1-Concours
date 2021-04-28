#ifndef CANDIDAT_H_INCLUDED
#define CANDIDAT_H_INCLUDED

#define NBR_NOTES 10
#define MAX_BYTES 500
#define NBR_MAX_CANDIDATS 5000

typedef enum {admis,ajourne,refuse} decision;
typedef struct
{
    unsigned int NCIN;
    char NOM[50];
    char PRENOM[50];
    unsigned int AGE;
    float NOTES[NBR_NOTES];
    decision DECISION;
}candidat;

#endif // CANDIDAT_H_INCLUDED}*
