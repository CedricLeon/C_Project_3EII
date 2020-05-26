#ifndef PATIENT_H
#define PATIENT_H

#include "GPCalendar/Model/Structures.h"
#include "GPCalendar/Model/date.h"
#include "GPCalendar/Model/dossier_medical.h"

#include <string.h>
#include <stdlib.h>
#include <stdio.h>

/**
 * Structure patient représentant un patient qui vient consulté dans l'application
 */
struct Patient{
    char * nom;
    char * prenom;
    Date * date_naissance;
    char * adresse_mail;
    char * numero_telephone;
    char * numero_secu_social;
    DossierMedical * dossierMedical;
};


Patient * CreerPatient(char * nom, char * prenom, int annee_naissance, int mois_naissance, int jour_naissance, char * mail, char * num_tel, char * numero_secu_social);
void DeletePatient(Patient * patient);

void printPatient(char* infos, Patient * p);
void AccesDossierMedical(char* infos, Patient * p);
void PrintListOrdonnances(char* infos, Patient* p);
void PrintListAntecedents(char* infos, Patient* p);

/* Getteurs */ /*idem*/
void getNomPatient(char * nom, Patient *p);
void getDateNaissancePatient(char* infos, Patient* p);
char * getAdresseMailPatient(Patient * p);
char * getNumeroTelephonePatient(Patient * p);
char * getNumeroSecuSocialePatient(Patient * p);

int AddMedecinConsultePatient(Patient * p, Medecin * medecin);
int DeleteMedecinConsultePatient(Patient * p, Medecin * medecin);

/**********************************************************************************************************************/
                                                /*ListPatient*/
/**********************************************************************************************************************/

/**
 * Structure NodePatient permettant de créer une Doubly linked list avec des sentinels pour la liste des Medecins consultés par un patient
 */
typedef struct NodePatient NodePatient;
struct NodePatient{
    Patient * patient;
    struct NodePatient * previous;
    struct NodePatient * next;
};

struct ListPatient{
    NodePatient sentinel_begin;
    NodePatient * current;
    NodePatient sentinel_end;
};

NodePatient * newNodePatient(Patient * patient, NodePatient * previous, NodePatient * next);
void freeNodePatient(ListPatient *l, NodePatient * n);
void freeNodePatient_withoutDeletingPatient(ListPatient *l, NodePatient * n);

ListPatient * CreerListPatient();

void printListPatient(ListPatient* l);

void ListPatient_init(ListPatient * l);
void ListPatient_free(ListPatient * l);
void ListPatient_free_withoutDeletingPatient(ListPatient * l);

int ListPatient_add(ListPatient * l, Patient * p);

Patient* ListPatient_seek(ListPatient* lP, char* IDPatient);

int ListPatient_isEmpty(ListPatient * l);
int ListPatient_isOutOfList(ListPatient * l);

void ListPatient_setOnFirst(ListPatient * l);
void ListPatient_setOnNext(ListPatient * l);
void ListPatient_setOnPrevious(ListPatient * l);
Patient* ListPatient_getCurrent(ListPatient * l);

#endif
