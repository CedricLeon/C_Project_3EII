#ifndef DATE_H
#define DATE_H

#include <time.h>

typedef struct{
    int annee;
    int mois;
    int jour;
}Date;

Date * CreerDate(int annee, int mois, int jour);
Date * DateCourante();
Date * AjoutMoisDateCourante(int nb_mois); /*pour ajouter nbmois mois à la date courante (utile pour ordonnance par exemple*/

#endif
