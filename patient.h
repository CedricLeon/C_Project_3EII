#ifndef PATIENT_H
#define PATIENT_H

#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#include "Structures.h"
#include "date.h"

/**
 * Structure patient représentant un patient qui vient consulté dans l'application
 */
struct Patient{
    char * nom;
    char * prenom;
    Date * date_naissance;
    char * adresse_mail;
    char * numero_telephone;
    struct ListMedecin * medecins_consultes;
};


Patient * CreerPatient(char * nom, char * prenom, int annee_naissance, int mois_naissance, int jour_naissance, char * mail, char * num_tel);
void DeletePatient(Patient * patient);

void AffichePatient(Patient * p);

//int InscriptionPatient(Patient * patient, RendezVous * rdv);              //A implémenter quand toutes les structures seront completes et testées

/* Setteurs */
void SetNomPatient(Patient * p, char * nom);
void SetPrenomPatient(Patient * p, char * prenom);
void SetDateNaissancePatient(Patient * p, int an, int mois, int jour);
void SetAdresseMailPatient(Patient * p, char * mail);
void SetNumeroTelephonePatient(Patient * p, char * tel);

char * getNomPatient(Patient * p);
char * getDateNaissancePatient(Patient * p);
char * getAdresseMailPatient(Patient * p);
char * getNumeroTelephonePatient(Patient * p);
char * getInfoPatient(Patient * p);

int AddMedecinConsultePatient(Patient * p, Medecin * medecin);
int DeleteMedecinConsultePatient(Patient * p, Medecin * medecin);

/**********************************************************************************************************************/
                                                /*ListPatient*/
/**********************************************************************************************************************/

/**
 * Structure NodePatient permettant de créer une Doubly linked list avec des sentinels pour la liste des Medecins consultés par un patient
 */
typedef struct NodePatient{
    Patient * patient;
    struct NodePatient * previous;
    struct NodePatient * next;
}NodePatient;

struct ListPatient{
    NodePatient sentinel_begin;
    NodePatient * current;
    NodePatient sentinel_end;
};

NodePatient * newNodePatient(Patient * patient, NodePatient * previous, NodePatient * next);
void freeNodePatient(NodePatient * n);

void ListPatient_init(ListPatient * l);
void ListPatient_free(ListPatient * l);

int ListPatient_isEmpty(ListPatient * l);
int ListPatient_isFirst(ListPatient * l);
int ListPatient_isLast(ListPatient * l);
int ListPatient_isOutOfList(ListPatient * l);

void ListPatient_setOnFirst(ListPatient * l);
void ListPatient_setOnLast(ListPatient * l);
void ListPatient_setOnNext(ListPatient * l);
void ListPatient_setOnPrevious(ListPatient * l);
Patient * ListPatient_getCurrent(ListPatient * l);

//void ListPatient_printList(ListPatient * l);          A voir si c'est nécessaire

#endif