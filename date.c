#include "date.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>


Date * CreerDate(int annee, int mois, int jour){
    Date * d = (Date *) malloc(sizeof(Date));
    d->annee = annee;
    d->mois = mois;
    d->jour = jour;
    return d;
}

void FreeDate(Date * d){
    free((void *) d);
}
