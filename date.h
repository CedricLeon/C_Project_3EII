#ifndef DATE_H
#define DATE_H

#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>

typedef struct{
    int annee;
    int mois;
    int jour;
}Date;

Date * CreerDate(int annee, int mois, int jour);
Date * DateCourante();
void FreeDate(Date * d);
Date * AjoutMoisDateCourante(int nb_mois);

#endif
