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
Date * CreerDateCourante();
Date * AjoutMoisDateCourante(int nb_mois); /*pour ajouter nbmois mois � la date courante (utile pour ordonnance par exemple*/
char * getJourDate(Date * d);
char * getMoisDate(Date * d);
char * getAnneeDate(Date * d);
char * getInfosDate(Date * d);
int DateEgales(Date * d1, Date * d2);

#endif
