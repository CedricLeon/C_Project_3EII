#ifndef MEDECIN_H
#define MEDECIN_H

#include "GPCalendar/Model/Structures.h"

#include <string.h>
#include <stdlib.h>
#include <stdio.h>

/**
 * Structure Medecin représentant un Medecin exercant dans l'hopital
 */
struct Medecin{
    char * nom;
    char * prenom;
    char * adresse_mail;
    char * numero_telephone;
    char * numero_RPS;
    struct ListPatient * patients_recus;
};

Medecin * CreerMedecin(char * nom, char * prenom,  char * mail, char * num_tel, char * num_RPS);
void DeleteMedecin(Medecin * medecin);

void getNomMedecin(char* nom, Medecin * m);
char * getAdresseMailMedecin(Medecin * medecin);
char * getNumeroTelephoneMedecin(Medecin * medecin);
char * getNumeroRPSMedecin(Medecin * medecin);
void getInfoMedecin(char * infos, Medecin * medecin);

int AddPatientRecuMedecin(Medecin * m, Patient * patient);
int DeletePatientRecuMedecin(Medecin * m, Patient * patient);

/**********************************************************************************************************************/
                                                /*ListMedecin*/
/**********************************************************************************************************************/

/**
 * Structure NodeMedecin permettant de créer une Doubly linked list pour la liste des medecins consultés par un patient
 */
typedef struct NodeMedecin NodeMedecin;

struct NodeMedecin{
    Medecin * medecin;
    struct NodeMedecin * previous;
    struct NodeMedecin * next;
};

struct ListMedecin{
    NodeMedecin sentinel_begin;
    NodeMedecin * current;
    NodeMedecin sentinel_end;
};

NodeMedecin * newNodeMedecin(Medecin * medecin, NodeMedecin * previous, NodeMedecin * next);
void freeNodeMedecin(ListMedecin *l, NodeMedecin * n);
void freeNodeMedecin_withoutDeletingMedecin(ListMedecin *l, NodeMedecin * n);

ListMedecin * CreerListMedecin();

void printListMedecin(ListMedecin* l);

void ListMedecin_init(ListMedecin * l);
void ListMedecin_free(ListMedecin * l);
void ListMedecin_free_withoutDeletingMedecin(ListMedecin * l);

int ListMedecin_add(ListMedecin * l, Medecin * m);

Medecin* ListMedecin_seek(ListMedecin* lP, char* IDMedecin);

int ListMedecin_isEmpty(ListMedecin * l);
int ListMedecin_isOutOfList(ListMedecin * l);

void ListMedecin_setOnFirst(ListMedecin * l);
void ListMedecin_setOnNext(ListMedecin * l);
void ListMedecin_setOnPrevious(ListMedecin * l);
Medecin * ListMedecin_getCurrent(ListMedecin * l);

#endif
