#ifndef DATE_H
#define DATE_H

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct{
    int annee;
    int mois;
    int jour;
}Date;

Date * CreerDate(int annee, int mois, int jour);
void FreeDate(Date * d);
Date * DateCourante();
Date * AjoutMoisDateCourante(int nb_mois); /*pour ajouter nbmois mois � la date courante (utile pour ordonnance par exemple*/
char* getJourChar(Date *d);
char* getMoisChar(Date *d);
char* getAnneeChar(Date *d);

#endif
