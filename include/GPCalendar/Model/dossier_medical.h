#ifndef DOSSIER_MEDICAL_H
#define DOSSIER_MEDICAL_H

#include "GPCalendar/Model/ordonnance.h"

#include <string.h>
#include <stdlib.h>
#include <stdio.h>

/**********************************************************************************************************************/
                                                /*DossierMedical*/
/**********************************************************************************************************************/

typedef struct ListAntecedent ListAntecedent;

typedef struct DossierMedical{
    ListMedecin* medecins_consultes; //Liste des m�decins consult�s pour ce dossier
    ListOrdonnance* ordonnances;
    /**
     * Pas d'antécédents pour l'instant (pas implémenté dans dossier médical.c et dans Json.c
     */
    ListAntecedent* antecedents;//CR des précédents passages à l'hopital pour les prochaines versions
}DossierMedical;

DossierMedical * CreerDossierMedical();
void FreeDossierMedical(DossierMedical * d);

int AddOrdonnanceDossierMedical(DossierMedical * dm, Ordonnance * ordonnance);
int AddAntecedentDossierMedical(DossierMedical * dm, char * ant);
void printAntecedent(char* infos, char * ante);

/**********************************************************************************************************************/
                                                /*ListAntecedent*/
/**********************************************************************************************************************/

/**
 * Structure NodeAntecedent
 */
typedef struct NodeAntecedent NodeAntecedent;
struct NodeAntecedent{
    char* ante;
    NodeAntecedent * previous;
    NodeAntecedent * next;
};

struct ListAntecedent{
    NodeAntecedent sentinel_begin;
    NodeAntecedent * current;
    NodeAntecedent sentinel_end;
};

NodeAntecedent * newNodeAntecedent(char * ante, NodeAntecedent * previous, NodeAntecedent * next);
void freeNodeAntecedent(ListAntecedent *l, NodeAntecedent * n);

void ListAntecedent_init(ListAntecedent * l);
void ListAntecedent_free(ListAntecedent * l);

int ListAntecedent_add(ListAntecedent* l, char* ante);

int ListAntecedent_isEmpty(ListAntecedent * l);
int ListAntecedent_isOutOfList(ListAntecedent * l);

void ListAntecedent_setOnFirst(ListAntecedent * l);
void ListAntecedent_setOnNext(ListAntecedent * l);
void ListAntecedent_setOnPrevious(ListAntecedent * l);
char * ListAntecedent_getCurrent(ListAntecedent * l);

#endif
