#ifndef CALENDRIER_H
#define CALENDRIER_H

#include "rendezvous.h"

/**
 * Pour le fonctionnement du calendrier je pense que pour que ça reste simple au maximum mais sans qu'il soit
 * quand même trop compliqué d'aller chercher un rdv en particulier, il faut fonctionner avec une liste de liste.
 *
 * Par exemple, on fait des listes JOUR qui contiennent donc une date (un seul jour), 2 sentinnelles et un pointeur
 * courant permettant de se déplacer dans les rdv de ce jour.
 * Il est ainsi facile d'aller chercher le rdv de 16h30 pouisqu'ils seront insérés dans la liste JOUR dans l'ordre
 * chronologique. Cela a aussi l'avantage de faire des petites listes et non des listes avec tout les rdv de l'année
 *
 * Ensuite on peut une grosse liste ANNEE par exemple qui à chaque fois qu'on ajoutera un rdv à un nouveau jour
 * se verra ajouter une liste JOUR. (On peut également pousser le raisonnement plus loin avec des listes MOIS) et
 * des listes ANNEES).
 *
 * Ce raisonnement a aussi l'avantage de pouvoir facilement créer plusieurs calendrier si plus tard on permet à
 * l'application de gérer l'emploi du temps de plusieurs mèdecin etc...
 */

/**********************************************************************************************************************/
                                        /*List de RendezVous pour un Jour*/
/**********************************************************************************************************************/
typedef struct NodeRendezVous{
    RendezVous * rdv;
    struct NodeRendezVous * next;
    struct NodeRendezVous * previous;
}NodeRendezVous;

typedef struct{
    Date * date;
    NodeRendezVous sentinel_begin;
    NodeRendezVous * current;
    NodeRendezVous sentinel_end;
}ListRendezVous;

typedef ListRendezVous * Jour;

NodeRendezVous * newNodeRendezVous(RendezVous * rdv , NodeRendezVous * previous, NodeRendezVous * next);
void freeNodeRendezVous(NodeRendezVous * n);

void ListRendezVous_init(ListRendezVous * l);
void ListRendezVous_free(ListRendezVous * l);

int ListRendezVous_isEmpty(ListRendezVous * l);
int ListRendezVous_isFirst(ListRendezVous * l);
int ListRendezVous_isLast(ListRendezVous * l);
int ListRendezVous_isOutOfList(ListRendezVous * l);

void ListRendezVous_setOnFirst(ListRendezVous * l);
void ListRendezVous_setOnLast(ListRendezVous * l);
void ListRendezVous_setOnNext(ListRendezVous * l);
void ListRendezVous_setOnPrevious(ListRendezVous * l);
RendezVous * ListRendezVous_getCurrent(ListRendezVous * l);

/**********************************************************************************************************************/
                                        /*List de RendezVous pour une Année*/
/**********************************************************************************************************************/
typedef struct{
    Jour jour;
    struct NodeJour * next;
    struct NodeJour * previous;
}NodeJour;

typedef struct{
    int Annee;
    NodeJour sentinel_begin;
    NodeJour * current;
    NodeJour sentinel_end;
}ListJour;

typedef ListJour * Annee;
#endif