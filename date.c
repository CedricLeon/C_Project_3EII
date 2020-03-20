#include "date.h"

Date * CreerDate(int annee, int mois, int jour){
    Date * d;
    d->annee = annee;
    d->mois = mois;
    d->jour = jour;
    return d;
}
