#ifndef ORDONNANCE_H
#define ORDONNANCE_H

#include "GPCalendar/Model/date.h"
#include "GPCalendar/Model/medecin.h"

#include <string.h>
#include <stdlib.h>
#include <stdio.h>

typedef struct{
    //Patient * patient;
    Medecin* medecin;
    //char* numRPSMedecin;    //Pour loader un projet : par défaut vaut NULL sauf lors du load d'un projet (remis à NULL après utilisation)
    Date* date_edition;
    Date* date_expiration;
    char* description;
}Ordonnance;

Ordonnance* CreerOrdonnance(Medecin * m, char * description);
Ordonnance* LoadOrdonnance(Medecin* medecin, int date_edi_jour, int date_edi_mois, int date_edi_annee, int date_expi_jour, int date_expi_mois, int date_expi_annee, char* description);

void DeleteOrdonnance(Ordonnance * o);
int modifierOrdonnance(Ordonnance * ordo, Medecin * m, char * description);
void printOrdonnance(char* infos, Ordonnance * ordo);

/**********************************************************************************************************************/
                                                /*ListOrdonnance*/
/**********************************************************************************************************************/

/**
 * Structure NodeOrdonnance
 */
typedef struct NodeOrdonnance NodeOrdonnance;
struct NodeOrdonnance{
    Ordonnance * ordo;
    NodeOrdonnance * previous;
    NodeOrdonnance * next;
};

typedef struct{
    NodeOrdonnance sentinel_begin;
    NodeOrdonnance * current;
    NodeOrdonnance sentinel_end;
}ListOrdonnance;

NodeOrdonnance * newNodeOrdonnance(Ordonnance * o, NodeOrdonnance * previous, NodeOrdonnance * next);
void freeNodeOrdonnance(ListOrdonnance *l, NodeOrdonnance * n);

void ListOrdonnance_init(ListOrdonnance * l);
void ListOrdonnance_free(ListOrdonnance * l);

int ListOrdonnance_isEmpty(ListOrdonnance * l);
int ListOrdonnance_isOutOfList(ListOrdonnance * l);

void ListOrdonnance_setOnFirst(ListOrdonnance * l);
void ListOrdonnance_setOnNext(ListOrdonnance * l);
void ListOrdonnance_setOnPrevious(ListOrdonnance * l);
Ordonnance * ListOrdonnance_getCurrent(ListOrdonnance * l);

#endif // ORDONNANCE_H
