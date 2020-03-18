#ifndef DATE_H
#define DATE_H

typedef struct{
    int annee;
    int mois;
    int jour;
}Date;

Date * CreerDate(int annee, int mois, int jour);

#endif
