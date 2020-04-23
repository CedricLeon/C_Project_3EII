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
Date * AjoutMoisDate(Date * d, int nb_mois); /*pour ajouter nbmois mois à une date (utile pour ordonnance par exemple*/
void getJourDate(char * infos, Date * d);
void getMoisDate(char * infos, Date * d);
void getAnneeDate(char * infos, Date * d);
void getInfosDate(char * infos, Date * d);
int DateEgales(Date * d1, Date * d2);

#endif
