#ifndef ORDONNANCE_H
#define ORDONNANCE_H

#include "date.h"
#include "medecin.h"

#include <string.h>
#include <stdlib.h>
#include <stdio.h>

typedef struct{
    //Patient * patient;
    Medecin * medecin;
    Date * date_edition;
    Date * date_expiration;
    char * description;
}Ordonnance;

Ordonnance * CreerOrdonnance(Medecin * m, char * description);
void DeleteOrdonnance(Ordonnance * o);
int modifierOrdonnance(Ordonnance * ordo, Medecin * m, char * description);
void printOrdonnance(Ordonnance * ordo);

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
int ListOrdonnance_isFirst(ListOrdonnance * l);
int ListOrdonnance_isLast(ListOrdonnance * l);
int ListOrdonnance_isOutOfList(ListOrdonnance * l);

void ListOrdonnance_setOnFirst(ListOrdonnance * l);
void ListOrdonnance_setOnLast(ListOrdonnance * l);
void ListOrdonnance_setOnNext(ListOrdonnance * l);
void ListOrdonnance_setOnPrevious(ListOrdonnance * l);
Ordonnance * ListOrdonnance_getCurrent(ListOrdonnance * l);

#endif // ORDONNANCE_H
