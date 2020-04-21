#ifndef ORDONNANCE_H
#define ORDONNANCE_H

#include "date.h"
#include "medecin.h"
#include "patient.h"

typedef struct{
    Patient * patient;
    Medecin * medecin;
    Date * date_edition;
    Date * date_expiration;
    char * description;
}Ordonnance;

Ordonnance * CreerOrdonnance(Patient * p, Medecin * m, char * description);
void DeleteOrdonnance(Ordonnance * o);
int ModifierOrdonnance(Ordonnance * ordo, Patient * p, Medecin * m, char * description);
void AfficherOrdonnance(Ordonnance * ordo);


#endif // ORDONNANCE_H
